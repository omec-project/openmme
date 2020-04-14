/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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

int send_sctp_msg_with_fd(int connSock, unsigned char *buffer, size_t len, uint16_t stream_no);
int close_sctp_socket(int sockfd);

#endif /*__S1AP_SCTP_CONN_H*/
