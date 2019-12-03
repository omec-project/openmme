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

#ifndef __S1AP_SCTP_CONN_H_
#define __S1AP_SCTP_CONN_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#define MAX_STREAM 5
#define MAX_PENDING_CONN 5
#define ENB_PORT 62324

int create_sctp_socket(unsigned int remote_ip, unsigned short port);

int accept_sctp_socket(int sockfd);

int recv_sctp_msg(int sockfd, unsigned char *buf, size_t len);

int send_sctp_msg(int connSock, unsigned char *buffer, size_t len, uint16_t stream_no);

int close_sctp_socket(int sockfd);

#endif /*__S1AP_SCTP_CONN_H*/
