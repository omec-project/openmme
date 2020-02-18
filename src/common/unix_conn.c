/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
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
*
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>

#include "log.h"
#include "unix_conn.h"

int create_unix_socket()
{
	int fd;
	struct sockaddr_un addr;
	char *socket_path = "/tmp/unix_socket";

	fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (fd == -1)
	{
		log_msg(LOG_ERROR, "Socket creation failed\n");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	if (*socket_path == '\0') {
		*addr.sun_path = '\0';
		strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
	} else {
		strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
		unlink(socket_path);
	}

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("Bind:");
		log_msg(LOG_ERROR, "Bind failed \n");
		close(fd);
		return -1;
	}

	if (listen(fd, MAX_PENDING_CONN) == -1) {
		log_msg(LOG_ERROR, "listen() failed \n");
		close(fd);
		return -1;
	}
	
	return fd;
}

int accept_unix_socket(int connSock)
{
	return accept(connSock, (struct sockaddr *) NULL, (socklen_t *) NULL);
}

int recv_unix_msg(int connSock, unsigned char *buffer, size_t len)
{
	int flags = 0;
	return recv(connSock, buffer, len, flags);
}

int send_unix_msg(int connSock, unsigned char *buffer, size_t len)
{
	return write(connSock, (void *)buffer, len);
}

int close_unix_socket(int connSock)
{
	return close(connSock);
}
