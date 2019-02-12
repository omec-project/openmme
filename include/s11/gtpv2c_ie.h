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


#ifndef __GTPV2C_IE_H_
#define __GTPV2C_IE_H_


#include <inttypes.h>
#include <stdlib.h>
#include <netinet/in.h>

#define IPV4_IE_LENGTH          4
#define IPV6_IE_LENGTH          16

/* TODO: Check size */
#define GTPV2C_MAX_LEN          4096

#define AMBR_UPLINK             100000000
#define AMBR_DOWNLINK           50000000

#define MBR_UPLINK              245018193L//245018193976L
#define MBR_DOWNLINK            245018193L//245018193976L

enum gtpv2c_ie_type {
	IE_RESERVED = 0,
	IE_IMSI = 1,
	IE_APN = 71,
	IE_AMBR = 72,
	IE_EBI = 73,
	IE_INDICATION = 77,
	IE_MSISDN = 76,
	IE_PAA = 79,
	IE_BEARER_QOS = 80,
	IE_RAT_TYPE = 82,
	IE_SERVING_NETWORK = 83,
	IE_ULI = 86,
	IE_FTEID = 87,
	IE_BEARER_CONTEXT = 93,
	IE_PDN_TYPE = 99,
	IE_APN_RESTRICTION = 127,
	IE_SELECTION_MODE = 128,
};

enum cause_value {
	GTPV2C_CAUSE_REQUEST_ACCEPTED = 16,
	GTPV2C_CAUSE_REQUEST_ACCEPTED_PARTIALLY = 17,
	GTPV2C_CAUSE_NEW_PDN_TYPE_NETWORK_PREFERENCE = 18,
	GTPV2C_CAUSE_NEW_PDN_TYPE_SINGLE_ADDR_BEARER = 19,
	GTPV2C_CAUSE_CONTEXT_NOT_FOUND = 64,
	GTPV2C_CAUSE_INVALID_MESSAGE_FORMAT = 65,
	GTPV2C_CAUSE_INVALID_LENGTH = 67,
	GTPV2C_CAUSE_SERVICE_NOT_SUPPORTED = 68,
	GTPV2C_CAUSE_MANDATORY_IE_INCORRECT = 69,
	GTPV2C_CAUSE_MANDATORY_IE_MISSING = 70,
	GTPV2C_CAUSE_SYSTEM_FAILURE = 72,
	GTPV2C_CAUSE_NO_RESOURCES_AVAILABLE = 73,
	GTPV2C_CAUSE_MISSING_UNKNOWN_APN = 78,
	GTPV2C_CAUSE_PREFERRED_PDN_TYPE_UNSUPPORTED = 83,
	GTPV2C_CAUSE_ALL_DYNAMIC_ADDRESSES_OCCUPIED = 84,
	GTPV2C_CAUSE_REQUEST_REJECTED = 94,
	GTPV2C_CAUSE_REMOTE_PEER_NOT_RESPONDING = 100,
	GTPV2C_CAUSE_CONDITIONAL_IE_MISSING = 103,
};

#define PDN_IP_TYPE_IPV4                                      1
#define PDN_IP_TYPE_IPV6                                      2
#define PDN_IP_TYPE_IPV4V6                                    3


enum gtpv2c_ie_instance {
	INSTANCE_ZERO = 0,
	INSTANCE_ONE = 1,
	INSTANCE_TWO = 2,
};

#pragma pack(1)


typedef struct gtpv2c_ie_t {
	uint8_t type;
	uint16_t length;
	uint8_t instance;
	uint8_t value[GTPV2C_MAX_LEN];
} gtpv2c_ie;


typedef struct fteid_ie_t {
	uint8_t iface_type :6;
	uint8_t ipv6 :1;
	uint8_t ipv4 :1;
	uint32_t teid;
	union ip_t {
		uint32_t ipv4;
		uint8_t ipv6[INET6_ADDRSTRLEN];
		struct ipv4v6_t_x {
			uint32_t ipv4;
			uint8_t ipv6[INET6_ADDRSTRLEN];
		} ipv4v6;
	} ipaddr;
} fteid_ie;


#pragma pack()

#endif /* __GTPV2C_IE_H_ */
