/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __JSON_DATA_H_
#define __JSON_DATA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
get_string_scalar(char *path);

int
get_ip_scalar(char *path);

int
get_int_scalar(char *path);

int
load_json(char *filename);

#endif /**/
