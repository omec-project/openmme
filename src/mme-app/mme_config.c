/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include "monitor_config.h"
#include "log.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "mme_app.h"

extern mme_config g_mme_cfg;

void mme_config_change_cbk(char *config_file, uint32_t flags)
{
    // Run the script with this file. It generates new config for mme
	log_msg(LOG_INFO, "Received %s . File %s Flags %x \n", __FUNCTION__, config_file, flags);
    system("sh /opt/mme/config/mme-init.sh");
    /* We dont expect quick updates from configmap..One update per interval */
    watch_config_change("/opt/mme/config/config.json", mme_config_change_cbk, false);

    /* Parse the config again */
    mme_config new_config;
    mme_parse_config(&new_config); 
    if(strcmp(new_config.logging, g_mme_cfg.logging))
    {
        //Logging level changed 
        set_logging_level(new_config.logging);
    }
    free(g_mme_cfg.logging); /* Release old logging level string */
    free(g_mme_cfg.mme_name); /* Relese old mme_name */
    g_mme_cfg = new_config; /* shallow copy of the structure */ 
    log_msg(LOG_INFO, "g_mme_cfg logging level %s");
}

void register_config_updates(void)
{
    /* I would prefer a complete path than this relative path.
     * Looks like it may break */
    watch_config_change("/opt/mme/config/config.json", mme_config_change_cbk, false);
}

