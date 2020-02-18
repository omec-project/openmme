/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * options.h
 *
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#define REQ_ARGS 0x0000
void parse_args(int argc, char **argv);
void log_buffer_free(char** buffer);

#endif /* OPTIONS_H_ */
