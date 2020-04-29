/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "monitor_subscriber.h"
#include "unix_conn.h"

extern int g_total_UE_count;
extern struct UE_info * g_UE_list[];
extern struct UE_info *ue_list_head;

/**
* Monitor message Imsi Request processing.
*/
void
handle_monitor_imsi_req(struct monitor_imsi_req *mir, int sock_fd)
{
	struct monitor_imsi_rsp mia = {0};
	struct UE_info *ue_entry = NULL;

    for(ue_entry = ue_list_head;
          ue_entry != NULL && IS_VALID_UE_INFO(ue_entry);
          ue_entry = ue_entry->next_ue)
    {
	    if((ATTACH_DONE == ue_entry->ue_state)
             ||(ECM_IDLE == ue_entry->ecm_state))
        {
           char imsi[16] = {0};
           mia.result = 2;

	       /*Parse and validate  the buffer*/
           imsi_bin_to_str(ue_entry->IMSI, imsi);
           if(strcmp((const char *)imsi,
                     (const char*)mir->imsi) == 0)
           {
               mia.bearer_id = ue_entry->bearer_id;
               mia.result = 1;
               mia.ue_state = ue_entry->ecm_state;
               struct in_addr paa=ue_entry->pdn_addr.ip_type.ipv4;
               mia.paa  = paa.s_addr;
               log_msg(LOG_ERROR, "imsi: %s address %x state %d\n", imsi, mia.paa, mia.ue_state);
               memcpy(mia.imsi, imsi, IMSI_STR_LEN);
               memcpy(&mia.tai, &ue_entry->tai, sizeof(struct TAI));
               memcpy(&mia.ambr, &ue_entry->ambr, sizeof(struct AMBR));
               break;
           }
	    }
	}

	unsigned char buf[BUFFER_SIZE] = {0};
	struct monitor_resp_msg resp;
	resp.hdr = MONITOR_IMSI_RSP;
	memcpy(&resp.data.mia, &mia, 
	      sizeof(struct monitor_imsi_rsp));
	memcpy(buf, &mia, sizeof(struct monitor_imsi_rsp));
	send_unix_msg(sock_fd, buf, sizeof(struct monitor_imsi_rsp));

	return;
}

/**
* Monitor message Imsi list processing.
*/
void
handle_imsi_list_req(struct monitor_imsi_req *mir, int sock_fd)
{
    struct UE_info *ue_entry = NULL;
    uint32_t no_of_ue = 0;
    unsigned char buf[BUFFER_SIZE] = {0};
    uint32_t size = sizeof(uint32_t);
    char* bufPtr = (char*)buf + size;
    log_msg(LOG_DEBUG, "imsi list request, Available UE count %d\n", g_total_UE_count);
    for(ue_entry = ue_list_head; ue_entry != NULL && IS_VALID_UE_INFO(ue_entry) ; ue_entry = ue_entry->next_ue)
    {
        if((ATTACH_DONE == ue_entry->ue_state)
		    || (ECM_IDLE == ue_entry->ecm_state))
        {
            char imsi[16] = {0};
            imsi_bin_to_str(ue_entry->IMSI, imsi);
            log_msg(LOG_DEBUG, "monitor imsi %s\n", imsi);
            memcpy(bufPtr, &imsi[0], IMSI_STR_LEN);
            bufPtr += IMSI_STR_LEN;
            size += IMSI_STR_LEN;
            no_of_ue++;
        }
        
        if(((size + IMSI_STR_LEN) > BUFFER_SIZE))
            break;
    }
    memcpy(buf, &no_of_ue, sizeof(uint32_t));
    send_unix_msg(sock_fd, buf, size);
    return;
}

/**
* Flush Imsis.
*/
void
handle_imsi_flush_req()
{
    struct UE_info *head_entry = ue_list_head;
    log_msg(LOG_DEBUG, "imsi flush request, ue count %d\n", g_total_UE_count);
    while(head_entry)
    {
        release_ue_entry(head_entry);
        head_entry = ue_list_head;
    }

    log_msg(LOG_DEBUG, "ue count after flush %d\n", g_total_UE_count);
    return;
}

/**
* Monitor message processing.
*/
void
handle_monitor_processing(void *message)
{
    log_msg(LOG_INFO, "Monitor Message Received");
	int sock_fd = 0;
	memcpy(&sock_fd, (char*)message, sizeof(int));
	char *msg = ((char *) message) + (sizeof(int));
	struct monitor_imsi_req* mir = (struct monitor_imsi_req*)msg;
    switch(mir->req_type)
    {
        case 0:
            {
                log_msg(LOG_DEBUG, "imsi request");
	            handle_monitor_imsi_req(mir, sock_fd);
                break;
            }
        case 1:
            {
                log_msg(LOG_DEBUG, "imsi list request");
	            handle_imsi_list_req(mir, sock_fd);
                break;
            }
        case 2:
            {
                log_msg(LOG_DEBUG, "imsi flush request");
	            handle_imsi_flush_req();
                break;
            }
    }

	/*free allocated message buffer*/
	free(message);
	return;
}
