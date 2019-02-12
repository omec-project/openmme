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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "log.h"
#include "ipc_api.h"
#include "err_codes.h"

int
create_ipc_channel(char *name)
{
	if (mkfifo (name, IPC_MODE) == -1) {
		log_msg(LOG_ERROR, "Error in create_ipc_channel %s\n", name);
		perror("Error:");
		return -1;
	}

	return 0;
}

int
open_ipc_channel(char *name, enum ipc_access_mode access_mode)
{
	int mode = O_RDONLY;
	int fd;

	if (access_mode == IPC_WRITE)
		mode = O_WRONLY;

	if ((fd = open(name, mode)) == -1) {
		log_msg(LOG_ERROR, "Error in create_ipc_channel %s\n",name);
		perror("Error:");
		return -E_FAIL;
	}

	return fd;
}

int
create_open_ipc_channel(char *name, enum ipc_access_mode access_mode)
{
	if (create_ipc_channel(name) != 0)
		return -1;

	return open_ipc_channel(name, access_mode);
}

int
read_ipc_channel(ipc_handle fd, char *buffer, size_t size)
{
	int len = read(fd, buffer, size);
	switch (len) {
	case -1:
            // case -1 means pipe is empty and errono
            // set EAGAIN
		if (errno == EAGAIN) {
		log_msg(LOG_ERROR, "pipe empty \n");
                usleep(5);
                return -1;
            }
            else { perror("read");
                exit(4);
            }

        // case 0 means all bytes are read and EOF(end of conv.)
        case 0:
            log_msg(LOG_ERROR, "End of conversation\n");

            // read link
            //close(p[0]);

            exit(0);
        default:
            // text read
            // by default return no. of bytes
            // which read call read at that time
            return len;
        }
}

int
write_ipc_channel(ipc_handle fd, char *buffer, size_t size)
{
	return write(fd, buffer, size);
}

int
close_ipc_channel(ipc_handle fd)
{
	if (close(fd) == -1)
		return -1;

	return 0;
}
