/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "json_data.h"
#include "s11_config.h"
#include "err_codes.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"

s11_config g_s11_cfg;

void
init_parser(char *path)
{
	load_json(path);
}

int
parse_s11_conf()
{
	/*s1ap information*/
	g_s11_cfg.local_egtp_ip = get_ip_scalar("s11.egtp_local_addr");
	if(-1 == g_s11_cfg.local_egtp_ip) return -1;
	g_s11_cfg.egtp_def_port = get_int_scalar("s11.egtp_default_port");
	if(-1 == g_s11_cfg.egtp_def_port) return -1;

	struct local_config { char *name; unsigned int *addr;};
	struct local_config config_addr[] = 
	{
		{ 
		  .name = "s11.sgw_addr",
		  .addr = &g_s11_cfg.sgw_ip,
		},
		{ 
		  .name = "s11.pgw_addr",
		  .addr = &g_s11_cfg.pgw_ip,
		}
	};
	for(int i=0; i<sizeof(config_addr)/sizeof(struct local_config); i++)
	{
	  char *gw_name= get_string_scalar(config_addr[i].name); 
	  if(gw_name != NULL)
	  {
	  	struct addrinfo hints;
	  	struct addrinfo *result=NULL, *rp=NULL; 
	  	int err;

	  	memset(&hints, 0, sizeof(struct addrinfo));
	  	hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
	  	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	  	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	  	hints.ai_protocol = 0;          /* Any protocol */
	  	hints.ai_canonname = NULL;
	  	hints.ai_addr = NULL;
	  	hints.ai_next = NULL;
	  	err = getaddrinfo(gw_name, NULL, &hints, &result);
	  	if (err != 0) 
	  	{
	  		// Keep trying ...May be SGW is not yet deployed 
			// We shall be doing this once timer library is integrated 
	  		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
	  		log_msg(LOG_INFO, "getaddr info failed %s\n",gai_strerror(err));
	  	}
	  	else 
	  	{
	  		for (rp = result; rp != NULL; rp = rp->ai_next) 
	  		{
	  			if(rp->ai_family == AF_INET)
	  			{
	  				struct sockaddr_in *addrV4 = (struct sockaddr_in *)rp->ai_addr;
	  				log_msg(LOG_INFO, "gw address received from DNS response %s\n", inet_ntoa(addrV4->sin_addr));
	  				*config_addr[i].addr = addrV4->sin_addr.s_addr;
	  			}
	  		}
	  	}
	  }
	}

	return SUCCESS;
}
