/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "log.h"
#include "err_codes.h"
#include "s1ap.h"
#include "ipc_api.h"
#include "main.h"
#include "stage2_info.h"
#include "message_queues.h"
#include "sctp_conn.h"
#include "s1ap_error.h"

/*Making global just to avoid stack passing*/
static char buf[UE_RESET_INFO_BUF_SIZE];
extern ipc_handle ipcHndl_reset_message;

static struct ue_reset_info *g_errorResetS1apInfo;
static struct Buffer g_buffer;
static struct Buffer g_value_buffer;
static struct Buffer g_reset_buffer;
static struct Buffer g_ue_associations_buf;

/**
* Stage specific message processing.
*/
static int
reset_request_processing()
{
	struct s1ap_PDU s1apPDU;
	g_errorResetS1apInfo = (struct ue_reset_info *) buf;

	/* Assigning values to s1apPDU */
	s1apPDU.procedurecode = id_reset;
	s1apPDU.criticality = CRITICALITY_REJECT;

	/* Copy values to buffer from s1apPDU */

	g_buffer.pos = 0;

	uint8_t initiating_message = 0; 
	buffer_copy(&g_buffer, &initiating_message,
			sizeof(initiating_message));

	buffer_copy(&g_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_buffer, &s1apPDU.criticality,
			sizeof(s1apPDU.criticality));

	/* Copy values in g_value_buffer */
	g_value_buffer.pos = 0;

	unsigned char chProtoIENo[3] = {0,0,2}; /*no extension and 2 IEs */

	buffer_copy(&g_value_buffer, chProtoIENo, sizeof(chProtoIENo));
    /* Add cause */
    {
        unsigned char tmpStr[4];
        uint16_t protocolIe_Id = id_Cause;
        copyU16(tmpStr, protocolIe_Id);
        buffer_copy(&g_value_buffer, tmpStr,
                        sizeof(protocolIe_Id));
        
        uint8_t protocolIe_criticality = CRITICALITY_IGNORE;
        buffer_copy(&g_value_buffer, &protocolIe_criticality,
                        sizeof(protocolIe_criticality));
        
        uint8_t cause_length = 2; 
        buffer_copy(&g_value_buffer, &cause_length, sizeof(cause_length));
        // refer - 36.413 Section 9.1.8.1 
        uint16_t  final = (g_errorResetS1apInfo->failure_layer << 12) | (g_errorResetS1apInfo->cause << 5); 
        uint8_t byte=(final >> 8) & 0xff ;
        buffer_copy(&g_value_buffer, &byte, sizeof(byte));
        byte=(final) & 0xff ;
        buffer_copy(&g_value_buffer, &byte, sizeof(byte));
    }
    /* Add specific tunnel info to be resetted */
    {
        unsigned char tmpStr[4];
        uint16_t protocolIe_Id = id_ResetType;
        copyU16(tmpStr, protocolIe_Id);
        buffer_copy(&g_value_buffer, tmpStr,
                        sizeof(protocolIe_Id));
        
        uint8_t protocolIe_criticality = CRITICALITY_REJECT;
        buffer_copy(&g_value_buffer, &protocolIe_criticality,
                        sizeof(protocolIe_criticality));

	    g_reset_buffer.pos = 0;
        uint8_t reset_type_buf = (1 << 6); 
        buffer_copy(&g_reset_buffer, &reset_type_buf, sizeof(reset_type_buf));
        uint8_t no_of_conns = 0; /* Actual tunnels - 1 */ 
        buffer_copy(&g_reset_buffer, &no_of_conns, sizeof(no_of_conns));
        {
    	  unsigned char tmpStr[4];
	      uint16_t protocolIe_Id = id_ueAssociatedLogicalS1Conn;
	      copyU16(tmpStr, protocolIe_Id);
	      buffer_copy(&g_reset_buffer, tmpStr, sizeof(protocolIe_Id));
	      uint8_t protocolIe_criticality = CRITICALITY_REJECT;
	      buffer_copy(&g_reset_buffer, &protocolIe_criticality, sizeof(protocolIe_criticality));
          g_ue_associations_buf.pos = 0;
          {
            uint8_t enb_mme; 
            uint16_t mmeid = g_errorResetS1apInfo->mme_s1ap_ue_id;
            if(mmeid <= 255) 
            {
              enb_mme = 0x60; // eNB & mme s1ap id present and length 1 byte 
              buffer_copy(&g_ue_associations_buf, &enb_mme, sizeof(enb_mme));
              uint8_t mme_id = mmeid;
              buffer_copy(&g_ue_associations_buf, &mme_id, sizeof(mme_id));
            } 
            else if (mmeid <= 65535)
            {
              enb_mme = 0x64; // eNB & mme s1ap id present and length 1 byte 
              buffer_copy(&g_ue_associations_buf, &enb_mme, sizeof(enb_mme));
              uint8_t mme_id1 = (mmeid >> 8) & 0xff;
              uint8_t mme_id2 = (mmeid) & 0xff;
              buffer_copy(&g_ue_associations_buf, &mme_id1, sizeof(mme_id1));
              buffer_copy(&g_ue_associations_buf, &mme_id2, sizeof(mme_id2));
            } 
          }
          {
            uint16_t enb_id = g_errorResetS1apInfo->enb_s1ap_ue_id;
            if(enb_id <= 255) 
            {
              uint8_t len=0;
              buffer_copy(&g_ue_associations_buf, &len, sizeof(len));
              uint8_t enbid = enb_id;
              buffer_copy(&g_ue_associations_buf, &enbid, sizeof(enbid));
            } 
            else if (enb_id <= 65535)
            {
              uint8_t len=0x40;
              buffer_copy(&g_ue_associations_buf, &len, sizeof(len));
              uint8_t enb_id1 = (enb_id >> 8) & 0xff;
              uint8_t enb_id2 = (enb_id) & 0xff;
              buffer_copy(&g_ue_associations_buf, &enb_id1, sizeof(enb_id1));
              buffer_copy(&g_ue_associations_buf, &enb_id2, sizeof(enb_id2));
            } 
          }        
          // we are done with g_ue_associations_buf. Now lets add that to g_reset_buf  
          // we are always including only 1 end points ..so we are well within 1 byte length 
          uint8_t inner_payload = g_ue_associations_buf.pos;
          buffer_copy(&g_reset_buffer, &inner_payload, sizeof(inner_payload));
          buffer_copy(&g_reset_buffer, &g_ue_associations_buf.buf[0], g_ue_associations_buf.pos);
       }
       uint8_t resettype_payload = g_reset_buffer.pos;
       buffer_copy(&g_value_buffer, &resettype_payload, sizeof(resettype_payload));
       buffer_copy(&g_value_buffer, &g_reset_buffer.buf[0], g_reset_buffer.pos);
    }
    /* Assumed to be 1 byte ?*/
    uint8_t top_payload = g_value_buffer.pos;
    buffer_copy(&g_buffer, &top_payload, sizeof(top_payload));
    buffer_copy(&g_buffer, &g_value_buffer.buf[0], g_value_buffer.pos);
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	send_sctp_msg(g_errorResetS1apInfo->enb_fd, g_buffer.buf, g_buffer.pos, 1);
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_s1ap_reset_pipe()
{
	close_ipc_channel(ipcHndl_reset_message);
	pthread_exit(NULL);
	return;
}

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_reset_message  = open_ipc_channel(
				S1AP_GEN_RESET_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for reset queue IPC"
				"channel : %s\n", S1AP_GEN_RESET_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "s1ap reset queue reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, UE_RESET_INFO_BUF_SIZE);
	while (bytes_read < UE_RESET_INFO_BUF_SIZE) {
		if ((bytes_read = read_ipc_channel(
				ipcHndl_reset_message, buf,
				UE_RESET_INFO_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error reading error reset  Q \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "S1ap error reset message received from enb Q len-%d", bytes_read);
	}

	return bytes_read;
}


/**
* Thread function for stage.
*/
void*
gen_reset_request_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "S1Ap reset message handler ready.\n");

	while(1){
		read_next_msg();

		reset_request_processing();

		post_to_next();
	}

	return NULL;
}

