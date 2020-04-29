/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
*
*/

#ifndef UNIXSOCK_H_
#define UNIXSOCK_H_

#define BUFFER_LEN  1024
#define MAX_CLIENT  10

void* accept_unix(void *data);
int init_sock();
#endif
