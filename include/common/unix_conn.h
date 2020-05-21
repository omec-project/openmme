/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
*
*/

#ifndef __UNIX_CONN_H_
#define __UNIX_CONN_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#define MAX_PENDING_CONN 5
#define BUF_SIZE 1024

int create_unix_socket();

int accept_unix_socket(int sockfd);

int recv_unix_msg(int sockfd, unsigned char *buf, size_t len);

int send_unix_msg(int sockfd, unsigned char *buf, size_t len);

int close_unix_socket(int sockfd);

#endif /*__UNIX_CONN_H*/
