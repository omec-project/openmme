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
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "log.h"

FILE *json_fp;

static char *
seek_to_tag(char *name)
{
	char *tmp = name;
	char tag[64] = {0};
		char last_iteration = 0;

	rewind(json_fp);

	tmp = strchr(name, '.');
	strncpy(tag, name, tmp-name);
	++tmp;

	while(1) {
		char tag_not_found = 1;
		char *line =(char *) calloc(1, 128);
		char *entry;
		char *tmp2;

		while(tag_not_found) {
			if (NULL == fgets(line, 128, json_fp)) return NULL;
			if(NULL != (entry = strstr(line, tag))) {
				tag_not_found = 0; /*found*/
				if(last_iteration) return line;
				break;
			}
			if(feof(json_fp)) return NULL;
		}
#if 0
		if(NULL == strchr(tmp, '.')) {
					/*This is the last tag*/
					return line;
				}
#endif
		tmp2 = strchr(tmp, '.');
		if(NULL == tmp2) {
			last_iteration = 1;
			tmp2 = tmp+strlen(tmp);
		}
		memset(tag, 0, 64);
		strncpy(tag, tmp, tmp2-tmp);
		tmp = tmp2+1;
		tag_not_found = 1;/*seach for next tag*/
	}

}

char *
get_string_scalar(char *path)
{
	char *entry = seek_to_tag(path);
	char *value = calloc(1, 128);

	if(NULL == entry) {
		log_msg(LOG_ERROR, "%s: entry not found\n", path);
		free(value);
		return NULL;
	}

	if (NULL == value)
	{
		log_msg(LOG_ERROR,"calloc function fail");
		return NULL;
	}
	char *tmp = strchr(entry, ':');
	sscanf(tmp, ": \"%[^\"]", value);
	log_msg(LOG_INFO, "%s = %s\n", path, value);
	return value;
}

int
get_int_scalar(char *path)
{
	char *entry = seek_to_tag(path);
	unsigned int i = 0;

	if(NULL == entry) {
		log_msg(LOG_ERROR, "%s: entry not found\n", path);
		return -1;
	}
	char *tmp = strchr(entry, ':');

	i = atoi(tmp+1);

	free(entry);
	log_msg(LOG_INFO, "%s = %d\n", path, i);
	return i;
}


int
get_ip_scalar(char *path)
{
	char *val = get_string_scalar(path);
	unsigned int addr = 0;

	if(NULL == val) addr = -1;
	else addr = inet_addr(val);

	free(val);
	return ntohl(addr);
}

int
load_json(char *filename)
{
	json_fp = fopen(filename, "r");

	if(NULL == json_fp) {
		log_msg(LOG_ERROR, "Error opening json file\n");
		perror("Error:");
		return -1;
	}

	return 0;
}

/** TEST CODE
void
main()
{

	load_json("test.json");
	get_string_scalar("root.scalar1");
	get_string_scalar("root.scalar2");
	get_string_scalar("root.scalarx");
	get_string_scalar("root.scalar3");
	get_string_scalar("root.scalar4");
	get_string_scalar("root.nested.scalar5");
}
**/
