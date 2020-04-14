/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
*
*/

#include "monitor_config.h"
#include "log.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "s1ap_config.h"
#include "s1ap.h"

extern s1ap_instance_t *s1ap_inst;

void s1ap_config_change_cbk(char *config_file, uint32_t flags)
{
	// Run the script with this file. It generates new config for mme
	log_msg(LOG_INFO, "Received %s . File %s Flags %x \n", __FUNCTION__, config_file, flags);

    char cmd[128];  
    sprintf(cmd, "cp %s %s ",config_file, "/openmme/target/conf/s1ap.json"); 
    system(cmd);


	s1ap_config_t *current_config = get_s1ap_config();

	/* Parse the config again */
	s1ap_config_t *new_config = calloc(1, sizeof(s1ap_config_t));;

	s1ap_parse_config(new_config); 

	/* Lets apply changes in the config*/
	if(strcmp(new_config->logging, current_config->logging))
	{
		//Logging level changed 
		set_logging_level(new_config->logging);
		log_msg(LOG_INFO, "logging level %s", new_config->logging);
	}

	switch_config(new_config); 

	/* We dont expect quick updates from configmap..One update per interval */
	watch_config_change("/opt/mme/config/shared/s1ap.json", s1ap_config_change_cbk, false);
}

void register_config_updates(void)
{
	/* I would prefer a complete path than this relative path.
	* Looks like it may break */
	watch_config_change("/opt/mme/config/shared/s1ap.json", s1ap_config_change_cbk, false);
}

s1ap_config_t *get_s1ap_config()
{
	return s1ap_inst->s1ap_config;
}

// new config, prev1-config, prev2 config 
// delete prev2 config and always keep new_config & prev1-config 
void 
switch_config(s1ap_config_t *new_config)
{
	static s1ap_config_t *last_copy;
	if(last_copy != NULL) 
	{
		free(last_copy->logging);
		free(last_copy->mme_name);
		free(last_copy);
	}
	
	last_copy = s1ap_inst->s1ap_config;
	s1ap_inst->s1ap_config = new_config;

}

void set_s1ap_config(s1ap_config_t *cfg)
{
	s1ap_inst->s1ap_config = cfg;
	return;
}
