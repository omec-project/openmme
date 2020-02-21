/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STIMER_H
#define __STIMER_H

#include <time.h>

typedef long long int stimer_t;

#define STIMER_GET_CURRENT_TP(__now__)                                                 \
({                                                                                     \
   struct timespec __ts__;                                                             \
   __now__ = clock_gettime(CLOCK_REALTIME,&__ts__) ?                                   \
         -1 : (((stimer_t)__ts__.tv_sec) * 1000000000) + ((stimer_t)__ts__.tv_nsec);   \
   __now__;                                                                            \
})

#define STIMER_GET_ELAPSED_NS(_start_)                                                 \
({                                                                                     \
   stimer_t __ns__;                                                                    \
   STIMER_GET_CURRENT_TP(__ns__);                                                      \
   if (__ns__ != -1)                                                                   \
      __ns__ -= _start_;                                                               \
   __ns__;                                                                             \
})

#define STIMER_GET_ELAPSED_US(__start__)                                               \
({                                                                                     \
   stimer_t __us__ = STIMER_GET_ELAPSED_NS(__start__);                                 \
   if (__us__ != -1)                                                                   \
      __us__ = (__us__ / 1000) + (__us__ % 1000 >= 500 ? 1 : 0);                       \
   __us__;                                                                             \
})

#define STIMER_GET_ELAPSED_MS(___start___)                                             \
({                                                                                     \
   stimer_t __ms__ = STIMER_GET_ELAPSED_US(___start___);                               \
   if (__ms__ != -1)                                                                   \
      __ms__ = (__ms__ / 1000) + (__ms__ % 1000 >= 500 ? 1 : 0);                       \
   __ms__;                                                                             \
})

#endif

