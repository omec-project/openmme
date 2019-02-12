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

#ifndef __MESSAGE_QUEUES_H_
#define __MESSAGE_QUEUES_H_

#define S1AP_Q_DIR "/tmp/s1ap"
#define MME_APP_Q_DIR "/tmp/mme-app"
#define S6A_Q_DIR "/tmp/s6a"
#define S11_Q_DIR "/tmp/s11"

#define MME_TOTAL_HANDLERS 7

/**
Message queues used across MME, S1ap, S11, S6a
**/

/*******************STAGE 1 BEGIN********************/

/*Stage 1 : Initial UE attah. Form S1ap tp MME*/
#define INITUE_STAGE1_QUEUE "/tmp/mme-app/initue_stage1_Q"

/*Stage 1 : ULR and AIR. From mme-app to S6a*/
#define S6A_REQ_STAGE1_QUEUE "/tmp/s6a/req_Q"
/**************** STAGE1 END *****************/

/*************** STAGE2 BEGIN ****************/
/*Stage to reader : s6a to mmeapp*/
#define S6A_AIA_STAGE2_QUEUE "/tmp/s6a/AIA_Q"
#define S6A_ULA_STAGE2_QUEUE "/tmp/s6a/ULA_Q"

/*Stage to writer: mmeapp to s1ap*/
#define S1AP_AUTHREQ_STAGE2_QUEUE "/tmp/s1ap/authq_stage2_Q"
/**************** STAGE2 END*****************/

/*************** STAGE3 BEGIN ****************/
#define S1AP_AUTHRESP_STAGE3_QUEUE "/tmp/mme-app/authresp_stage3_Q"

#define S1AP_SECREQ_STAGE3_QUEUE "/tmp/s1ap/secreq_stage3_Q"
/**************** STAGE3 END*****************/

/*************** STAGE4 BEGIN ****************/
#define S1AP_SECRESP_STAGE4_QUEUE "/tmp/mme-app/secresp_stage4_Q"

#define S1AP_ESMREQ_STAGE4_QUEUE "/tmp/s1ap/esmreq_stage4_Q"
/**************** STAGE4 END*****************/

/*************** STAGE5 BEGIN ****************/
#define S1AP_ESMRESP_STAGE5_QUEUE "/tmp/mme-app/esmresp_stage5_Q"

#define S11_CSREQ_STAGE5_QUEUE "/tmp/s11/CSreq_stage5_Q"
/**************** STAGE5 END*****************/

/*************** STAGE6 BEGIN ****************/
#define S11_CSRESP_STAGE6_QUEUE "/tmp/s11/CSresp_stage6_Q"

#define S1AP_ICSREQ_STAGE6_QUEUE "/tmp/s1ap/icsreq_stage6_Q"
/**************** STAGE6 END*****************/

/*************** STAGE7 BEGIN ****************/
#define S1AP_ICSRESP_STAGE7_QUEUE "/tmp/s1ap/icsresp_stage7_Q"

#define S11_MBREQ_STAGE7_QUEUE "/tmp/s11/MBreq_stage7_Q"

/**************** STAGE7 END*****************/

/*************** STAGE8 BEGIN ****************/
#define S11_MBRESP_STAGE8_QUEUE "/tmp/s11/MBresp_stage8_Q"

#define S1AP_ATT_COMP_STAGE8_QUEUE "/tmp/mme-app/attcomple_stage8_Q"
/*************** STAGE8 END ****************/

/********* STAGE 1 DETACH BEGIN ***************/

#define S1AP_DTCHREQ_STAGE1_QUEUE  "/tmp/s1ap/s1ap_dtchreq_stage1_Q"

#define S11_DTCHREQ_STAGE1_QUEUE   "/tmp/mme-app/s11_dtchreq_stage1_Q"

#define S6A_DTCHREQ_STAGE1_QUEUE  "/tmp/mme-app/s6a_dtchreq_stage1_Q"

/********* STAGE 1 DETACH END    ***************/

/********* STAGE 2 DETACH BEGIN ***************/

#define S11_DTCHRES_STAGE2_QUEUE  "/tmp/mme-app/s1ap_dtchres_stage2_Q"

#define S1AP_DTCHACCEPT_STAGE2_QUEUE "/tmp/mme-app/s1ap_dtchaccept_stage2_Q"

#define S6A_PURGE_STAGE2_QUEUE "/tmp/s6a/PURGE_Q"

/********* STAGE 2 DETACH END    ***************/

/********* STAGE 3 DETACH BEGIN ***************/

#define S1AP_CTXRELRESP_STAGE3_QUEUE  "/tmp/s1ap/s1ap_ctxrelease_stage3_Q"

/********* STAGE 3 DETACH END    ***************/

#endif /*__MESSAGE_QUEUES_H*/
