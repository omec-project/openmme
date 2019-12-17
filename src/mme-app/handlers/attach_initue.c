/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
#include "stage1_info.h"
#include "ipc_api.h"
#include "stage1_s6a_msg.h"

/************************************************************************
Current file : Stage 1 handler.
ATTACH stages :
-->	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage1 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage1 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage1 handler]-->create session
	Stage 6 : create session resp-->[stage1 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage1 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_UE_cnt;
extern int g_mme_hdlr_status;

/*source Q : Read feom*/
static int g_Q1_fd;

/*Destination Q : Write to*/
static int g_Q_s6a_air;
//static int g_Q_s6a_ulr;

/*Making global just to avoid stack passing*/
static char buf[INITUE_STAGE1_BUF_SIZE];

static int g_Q_s1ap_attach_reject;
extern uint32_t attach_reject_counter;
extern uint32_t attach_identity_req_counter;

static int g_Q_s1ap_id_request;
extern uint32_t attach_id_req_counter;

extern mme_config g_mme_cfg;
extern uint32_t attach_stage1_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q1_fd  = open_ipc_channel(INITUE_STAGE1_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 1 IPC channel : %s\n",
			INITUE_STAGE1_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 reader - init UE msg: Connected.\n");

	log_msg(LOG_INFO, "Stage1 writer - AIR: waiting.\n");
	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	g_Q_s6a_air = open_ipc_channel(S6A_REQ_STAGE1_QUEUE, IPC_WRITE);

	if (g_Q_s6a_air == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S6A - AIR\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 writer - AIR: Connected\n");

	/*Open destination queue for writing s1ap attach failure */
	g_Q_s1ap_attach_reject = open_ipc_channel(S1AP_REQ_REJECT_QUEUE, IPC_WRITE);
	if (g_Q_s1ap_attach_reject == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S1AP Reject Queue \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 writer - S1AP reject Pipe : Connected\n");
 
	/* Open destination queue for writing s1ap Id Request */
	g_Q_s1ap_id_request = open_ipc_channel(S1AP_ID_REQ_QUEUE, IPC_WRITE);
	if (g_Q_s1ap_id_request == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S1AP Id Request Queue \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 writer - S1AP Id Request Pipe : Connected\n");
 
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, INITUE_STAGE1_BUF_SIZE);
	while (bytes_read < INITUE_STAGE1_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q1_fd, buf, INITUE_STAGE1_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Init UE Message Received: %d\n", bytes_read);
	}

	return bytes_read;
}


/**
* Stage specific message processing.
*/
static int
stage1_processing(struct s6a_Q_msg *s6a_req, struct attachReqRej_info *s1ap_rej, struct attachIdReq_info *s1ap_id_req)
{
    struct ue_attach_info *ue_info = (struct ue_attach_info*)buf;
    struct UE_info *ue_entry = NULL;
    int ret = SUCCESS;

    /*Parse and validate  the buffer*/
    if (NULL == ue_info) {
            /*Error case handling. This should be handled in s1ap only.*/
            return E_FAIL;
    }

    log_msg(LOG_INFO,"%s - UE info flags %x \n",__FUNCTION__, ue_info->flags);

    if(UE_ID_GUTI(ue_info->flags))
    {
      do
      { 
        log_msg(LOG_INFO, "GUTI received....TMSI = %d \n",ue_info->mi_guti.m_TMSI);
        if((ue_info->mi_guti.mme_grp_id != g_mme_cfg.mme_group_id) || 
                        (ue_info->mi_guti.mme_code   != g_mme_cfg.mme_code))
        {
          log_msg(LOG_INFO, "MME GroupId/Code missmatch. My Group(%d) Received "
                          "Group(%d) My code(%d) Received Code(%d)\n",ue_info->mi_guti.m_TMSI,
                          g_mme_cfg.mme_group_id,ue_info->mi_guti.mme_grp_id,g_mme_cfg.mme_code,ue_info->mi_guti.mme_code);
          //map mme_grp_id & mme_code to neighbor MME and fetch IMSI from the neighbor mme
          // REQUIREMENT : MME to support S10 interface for this functionality
          s1ap_id_req->enb_fd  = ue_info->enb_fd;
          s1ap_id_req->s1ap_enb_ue_id = ue_info->s1ap_enb_ue_id;
          s1ap_id_req->ue_type = ID_IMSI ;
          ret = E_MAPPING_FAILED;
          break;
        }

        /* Group id and mme code matches with our groupid and mme code.
         */ 
        ue_entry = GET_UE_ENTRY(ue_info->mi_guti.m_TMSI);
        // Lets find if we have GUTI with us
        if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
        {
          log_msg(LOG_INFO, "GUTI received. NO valid record at given index %x \n", ue_entry);
          //Invalid index..Perhaps crossing our pool count OR
          //m-tmsi within range but UE_INFO is not valid 
          //REQUIREMENT : Initiate Identity Request towards UE
          s1ap_id_req->enb_fd  = ue_info->enb_fd;
          s1ap_id_req->s1ap_enb_ue_id = ue_info->s1ap_enb_ue_id;
          s1ap_id_req->ue_type = ID_IMSI ;
          ret =  E_MAPPING_FAILED;
          break;
        }
        // cross validates with ue_index of the UE_entry
        // We have GUTI and its valid too...any further cross checks ??? 
        log_msg(LOG_INFO, "Valid UE Record found from the GUTI. Pti - %d .  Ue_entry = %p\n", ue_info->pti, ue_entry);
        memcpy(&(ue_entry->pti), &(ue_info->pti), 1);
        memcpy(&(ue_entry->dl_seq_no), &(ue_info->seq_no), 1);
        ue_entry->s1ap_enb_ue_id = ue_info->s1ap_enb_ue_id;
        ue_entry->enb_fd = ue_info->enb_fd;
        ue_entry->esm_info_tx_required = ue_info->esm_info_tx_required;
        memcpy(&(ue_entry->tai), &(ue_info->tai),
                        sizeof(struct TAI));

        memcpy(&(ue_entry->utran_cgi), &(ue_info->utran_cgi),
                        sizeof(struct CGI));
        memcpy(&ue_entry->pco_options[0], &ue_info->pco_options[0], sizeof(ue_info->pco_options)); 
        guti_attach_post_to_next(ue_entry->ue_index);
        return SUCCESS_1;
      }while(0);
    }

	int index = allocate_ue_index();
    if (index == -1) {
      log_msg(LOG_INFO, "Index is  received from the list\n");
      return E_FAIL; /* FEATURE REQUEAST : NO RESOURCE REJECTION */
    } 

	log_msg(LOG_INFO, "Create UE record for IMSI %x %x %x %x %x %x %x %x \n", ue_info->IMSI[0], ue_info->IMSI[1], ue_info->IMSI[2],ue_info->IMSI[3],ue_info->IMSI[4],ue_info->IMSI[5],ue_info->IMSI[6],ue_info->IMSI[7]);
 
	/**TODO
	Find the UE if already exists in hash
	Delete existing UE entry.
	*/

	/*Allocate new UE entry in the hash*/
	/*Copy UE information*/
	ue_entry = GET_UE_ENTRY(index);
	ue_entry->magic = UE_INFO_VALID_MAGIC;  
	ue_entry->ue_index = index;
	ue_entry->ue_state = ATTACH_STAGE1;
	ue_entry->s1ap_enb_ue_id = ue_info->s1ap_enb_ue_id;
	ue_entry->enb_fd = ue_info->enb_fd;
	ue_entry->esm_info_tx_required = ue_info->esm_info_tx_required;

    if(UE_ID_IMSI(ue_info->flags))
    {
	  memcpy(&(ue_entry->IMSI), &(ue_info->IMSI), BINARY_IMSI_LEN);
    }
    else if(UE_ID_GUTI(ue_info->flags))
    {
      //ignore GUTI coming from UE..since we are about to do ID Request now 
    }
	memcpy(&(ue_entry->tai), &(ue_info->tai),
		sizeof(struct TAI));
	memcpy(&(ue_entry->utran_cgi), &(ue_info->utran_cgi),
		sizeof(struct CGI));
	//g_UE_list[0][index].rrc_cause = info->ue_info.rrc_cause;
	memcpy(&(ue_entry->ue_net_capab), &(ue_info->ue_net_capab),
		sizeof(struct UE_net_capab));
	memcpy(&(ue_entry->ms_net_capab), &(ue_info->ms_net_capab),
		sizeof(struct MS_net_capab));
	memcpy(&(ue_entry->pti), &(ue_info->pti), 1);
    log_msg(LOG_INFO, "UE record created Pti - %d .  ", ue_info->pti);

    memcpy(&ue_entry->pco_options[0], &ue_info->pco_options[0], sizeof(ue_info->pco_options)); 
	ue_entry->bearer_id = 5; /* Bearer Management */

    s1ap_id_req->ue_idx = index;
	/* Collect information for next processing*/
    if(ret == SUCCESS)
    {
	  memcpy(&(s6a_req->imsi), &(ue_info->IMSI), BINARY_IMSI_LEN);
	  memcpy(&(s6a_req->tai), &(ue_info->tai), sizeof(struct TAI));
	  s6a_req->ue_idx = index;
    }

	/*post to next processing*/
	return ret;
}

#if 0
void
create_dummy_msg()
{
	memcpy(&(s6a_req.imsi), "208014567891234", 16);
	s6a_req.tai.plmn_id = g_mme_cfg.plmn_id;
	s6a_req.tai.tac = 10;
	//struct PLMN visited_plmn;
	/*e-utran auth info??*/
	s6a_req.ue_idx = 123;
}
#endif

/**
* Post message to next handler of the stage
*/
static int
post_to_next(struct s6a_Q_msg *s6a_req)
{
	/*in case of GUTI attach and subscriber belong to this MME then we dont want to 
	* do the subscriber authorization again. 
	* Refer 23.401 Section - 5.3.2.1 Initial Attach, Step-5. There are good details
	* about when we can skip this stage 
	*/ 
	log_msg(LOG_INFO, "Sending HSS AIR Request \n");
	write_ipc_channel(g_Q_s6a_air, (char *)(s6a_req), S6A_REQ_Q_MSG_SIZE);
	attach_stage1_counter++;
	return SUCCESS;
}

/* Identity request is received and now we need to post HSS transactions
 */

int
post_to_hss_stage(int ue_index)
{
  struct UE_info *ue_entry = NULL;
  ue_entry = GET_UE_ENTRY(ue_index);
  if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
  {
    return E_FAIL;
  }

  /* Multi threading issue..Not a good idea to use global s6a_req */
  struct s6a_Q_msg s6a_req; 

  memcpy(&(s6a_req.imsi), &(ue_entry->IMSI), BINARY_IMSI_LEN);
  memcpy(&(s6a_req.tai), &(ue_entry->tai), sizeof(struct TAI));
  s6a_req.ue_idx = ue_index;
  log_msg(LOG_INFO, "Sending HSS AIR Request \n");
  write_ipc_channel(g_Q_s6a_air, (char *)&(s6a_req), S6A_REQ_Q_MSG_SIZE);
  return SUCCESS;
}
 
/*
* Post message to s1ap handler about the failure of this stage 
*/
static int
post_fail_s1ap(struct attachReqRej_info *s1ap_rej)
{
        /*in case of GUTI attach and subscriber belong to this MME then we dont want to 
         * do the subscriber authorization again. 
         * Refer 23.401 Section - 5.3.2.1 Initial Attach, Step-5. There are good details
         * about when we can skip this stage 
         */ 

	//test create_dummy_msg();
	log_msg(LOG_INFO, "Sending Attach Failure \n");
	write_ipc_channel(g_Q_s1ap_attach_reject, (char *)(s1ap_rej), S1AP_REQ_REJECT_BUF_SIZE );
	attach_reject_counter++;
	return SUCCESS;
}

/*
 * Post identity request to UE
 */
static int
post_identity_req(struct attachIdReq_info *s1ap_id_req)
{
	log_msg(LOG_INFO, "Sending Identity Request \n");
	write_ipc_channel(g_Q_s1ap_id_request, (char *)(s1ap_id_req), S1AP_ID_REQ_BUF_SIZE);
	attach_identity_req_counter++;
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage1()
{
	close_ipc_channel(g_Q1_fd);
	log_msg(LOG_INFO, "Shutdown Stage1 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage1_handler(void *data)
{
	int ret;
	init_stage();
    static struct s6a_Q_msg s6a_req;
    static struct attachIdReq_info s1ap_id_req;
    static struct attachReqRej_info s1ap_rej;

	log_msg(LOG_INFO, "Stage 1 Ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		ret = stage1_processing(&s6a_req, &s1ap_rej, &s1ap_id_req);
		if(ret == SUCCESS)
        {
			post_to_next(&s6a_req);
        }
		else if(ret == E_MAPPING_FAILED)
        {
            post_identity_req(&s1ap_id_req);
        }
		else if(ret == E_FAIL)
        {
			post_fail_s1ap(&s1ap_rej);
        }
	}

	return NULL;
}
