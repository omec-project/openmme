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

#ifndef IPC_API_H_
#define IPC_API_H_

#define		IPC_MAX_BUFFER_SIZE		1024

#define IPC_MODE 0664

enum ipc_access_mode {
	IPC_READ = 01,
	IPC_WRITE = 02,
};

typedef int ipc_handle;

int
create_ipc_channel(char *name);

int
open_ipc_channel(char *name, enum ipc_access_mode access_mode);

int
create_open_ipc_channel(char *name,
		enum ipc_access_mode access_mode);

int
read_ipc_channel(ipc_handle fd, char *buffer, size_t size);

int
write_ipc_channel(ipc_handle fd, char *buffer, size_t size);

int
close_ipc_channel(ipc_handle fd);

#endif /* IPC_API_H_ */
