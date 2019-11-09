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
* Version - 0.1
* This file has timer implementation.
* Timer library creates one pthread and works in that thread context.
* Callbacks are made in the timer Thread context. Application needs
* to handle the locking mechanism if any. 
* Granularity of timer is in seconds...
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <poll.h>
#include <assert.h>
#include "local_timer.h"

#define INSIDE_APP_CALLBACK 0x0001
#define IS_CONTROL_INSIDE_CALLBACK(node) ((node->flags) & 0x0001)
#define SET_CONTROL_INSIDE_CALLBACK(node) ((node->flags) |= 0x0001)
#define RESET_CONTROL_INSIDE_CALLBACK(node) ((node->flags) &= 0xFFFE)

struct timer 
{
   uint64_t id;
   void *cb_data;
   cbf  cbf;
   uint64_t timeout;
   uint16_t ms_offset;
   struct timer *next, *prev;
   uint16_t flags;
};

static struct timer *head = NULL;
static uint64_t sec_epoch = 0;
static uint16_t ms_epoch=0;
static pthread_mutex_t timer_lock;


/* Doubly link list Code...Manages adding/removing timers 
 */
static void insert_node(struct timer *node)
{
   struct timer *temp=NULL, *prev=NULL;

   pthread_mutex_lock(&timer_lock); 

   if(head == NULL)
   {
     head = node;
     pthread_mutex_unlock(&timer_lock); 
     return;
   }
   temp=head;
   while(temp != NULL) 
   {
     if((node->timeout < temp->timeout) || 
        ((node->timeout == temp->timeout) && (node->ms_offset < temp->ms_offset)))
     {
       node->prev = temp->prev;
       node->next = temp;
       if(temp->prev)
         temp->prev->next = node;
       temp->prev = node;
       if(temp == head)
       {
         head = node;
       }
       pthread_mutex_unlock(&timer_lock); 
       return;
     }
     prev = temp;
     temp = temp->next;
   }
   if(temp == NULL)
   {
     prev->next = node;
     node->prev = prev; 
   }
   pthread_mutex_unlock(&timer_lock); 
   return;
}

static int 
find_node(struct timer *node)
{
  struct timer *temp = NULL; 

  pthread_mutex_lock(&timer_lock); 
  for(temp = head; (temp != NULL) && (temp != node); temp = temp->next);
  pthread_mutex_unlock(&timer_lock); 
  return ((temp != NULL) ? 0 : -1);
}

/* end of doubly link list Code */

static void check_expired_timers()
{
  struct timer *temp=NULL;
  pthread_mutex_lock(&timer_lock); 
  temp = head;
  while(temp != NULL)
  {
    if(temp->timeout > sec_epoch)
    {
      pthread_mutex_unlock(&timer_lock); 
      return; // nothing to timeout 
    }
    if((temp->timeout == sec_epoch) && temp->ms_offset > ms_epoch)
    {
      pthread_mutex_unlock(&timer_lock); 
      return; // nothing to timeout
    }

    head = head->next; 

    if(head)
      head->prev = NULL;

    // temp is now not part of the list  
    SET_CONTROL_INSIDE_CALLBACK(temp);
    pthread_mutex_unlock(&timer_lock); 
    temp->cbf(temp->cb_data);
    RESET_CONTROL_INSIDE_CALLBACK(temp);
    free(temp);
    pthread_mutex_lock(&timer_lock); 
    temp = head;
  } 
  pthread_mutex_unlock(&timer_lock); 
  return;
}


static void* init_lib(void *t)
{
  struct itimerspec timeout;
  uint64_t buf[2];
  int buf_len;
  
  printf("Inside init lib \n");
  int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
  if(fd < 0) 
  {
    printf("Error in creating timer fd \n");
  }
  printf("Timer FD created %d \n",fd);

  /* We need tick per 100 ms.. (10 ticks/second) */
  timeout.it_interval.tv_nsec = 100000000;  /* Interval for periodic timer */
  timeout.it_interval.tv_sec  = 0 ; /* Interval for periodic timer */
  timeout.it_value.tv_sec = 1;     /* Initial expiration */

  if(timerfd_settime(fd, 0, &timeout, NULL)<0)
  {
    printf("Error in setting timer\n");
  }
  printf("timerfd_Settime success \n");
  struct pollfd fds[1];
  int ret;
  
  fds[0].fd = fd;
  fds[0].events = POLLIN;
  while(1)
  {
    ret = poll(fds, 1, 100); // wait for 100 msec for the event 
    if(ret >= 0)
    {
      if(ret > 0 && fds[0].revents & POLLIN)
      {
        //printf("\nRead event Received \n");
        buf_len = read(fd, &buf, sizeof(uint64_t));
        if(buf_len != sizeof(uint64_t))
        {
          //error
        }
      }
      ms_epoch++;
      ms_epoch = ms_epoch % 10;
      if(ms_epoch == 0)
      {
        sec_epoch++; // 1 sec complete ...
      }
      check_expired_timers();
    }
  }
  return NULL;
}

#ifdef STANDALONE_TIMER_PROGRAM
/* Its upto application to handle this timer event... 
 * Since timer library is creates its own thread,
 * callback is made inside the timerthread context
 */
static uint64_t expired_timers = 0;
static void my_ut_timer(void *p)
{
  expired_timers++;
  return;
}

static void timer_callback_call_timer_stop(void *p)
{
  expired_timers++;
  stop_timer(p);
}

static void timer_callback_call_timer_start(void *p)
{
  expired_timers++;
  start_timer(10, my_ut_timer, NULL);
}


int main()
{
  init_timer_lib();
  // Execute Our UT when program runs as standalone...
  sleep(2); 
  {
    /* Test 1 - Start timer and let it expire */
    printf("START TEST1- Timer is start/expire test started \n");
    struct timer *tmr = start_timer(10, my_ut_timer, NULL);
    assert(tmr != NULL);
    sleep(1);
    assert(timer_running(tmr) == 0);
    sleep(10);
    assert(timer_running(tmr) == -1);
    printf("END - Timer is start/expire passed\n");
  }

  {
    /* Test 2 - Start timer and stop timer */
    printf("START TEST2 Timer is start/stop test started \n");
    struct timer *tmr = start_timer(10, my_ut_timer, NULL);
    assert(tmr != NULL);
    sleep(1);
    assert(timer_running(tmr) == 0);
    assert(stop_timer(tmr) == 0);
    assert(timer_running(tmr) == -1);
    printf("END Timer is start/stop passed\n");
  }
  {
    /* Test 3 - Start 5 timers */
    printf("START TEST3 -  5 timers start test started \n");
    uint64_t expired_timers_local = expired_timers;
    start_timer(10, my_ut_timer, NULL);
    start_timer(15, my_ut_timer, NULL);
    start_timer(8, my_ut_timer, NULL);
    start_timer(1, my_ut_timer, NULL);
    start_timer(2, my_ut_timer, NULL);
    sleep(16);
    assert(expired_timers == (expired_timers_local + 5));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END - 5 timers start test passed \n");
  }  
  {
    /* Test 4 - Start timer and stop timer in between */
    printf("START TEST4 - 5 timers start & stop one of the timer started \n");
    uint64_t expired_timers_local = expired_timers;
    struct timer *tmr = start_timer(10, my_ut_timer, NULL);
    start_timer(15, my_ut_timer, NULL);
    start_timer(8, my_ut_timer, NULL);
    start_timer(1, my_ut_timer, NULL);
    start_timer(2, my_ut_timer, NULL);
    stop_timer(tmr);
    sleep(16);
    assert(expired_timers == (expired_timers_local + 4));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END 5 timers start & stop 1 timer test passed \n");
  }    
  {
    /* Test 5 - Start timer and stop timer in between */
    printf("START TEST5 - 5 timers start & stop one of the timer started \n");
    uint64_t expired_timers_local = expired_timers;
    struct timer *tmr = start_timer(18, my_ut_timer, NULL);
    start_timer(15, my_ut_timer, NULL);
    start_timer(8, my_ut_timer, NULL);
    start_timer(1, my_ut_timer, NULL);
    start_timer(2, my_ut_timer, NULL);
    stop_timer(tmr);
    sleep(19);
    assert(expired_timers == (expired_timers_local + 4));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END 5 timers start & stop 1 timer test passed \n");
  }  
  {
    /* Test 6 - Start timer and stop timer in between */
    printf("START TEST6 - 5 timers start & stop one of the timer started \n");
    uint64_t expired_timers_local = expired_timers;
    struct timer *tmr;
    start_timer(10, my_ut_timer, NULL);
    start_timer(15, my_ut_timer, NULL);
    start_timer(8, my_ut_timer, NULL);
    start_timer(7, my_ut_timer, NULL);
    tmr = start_timer(2, my_ut_timer, NULL);
    stop_timer(tmr);
    sleep(16);
    assert(expired_timers == (expired_timers_local + 4));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END - 5 timers start & stop 1 timer test passed \n");
  } 
  {
    /* Test 7 - Start timer and expiry callback calls stop timer */
    printf("START TEST7 - start 1 timer and in timer expiry callback, stop timer is called \n");
    uint64_t expired_timers_local = expired_timers;
    struct timer *tmr = start_timer(2, timer_callback_call_timer_stop, NULL);
    tmr->cb_data = tmr; //hack for testcase  
    sleep(6);
    assert(expired_timers == (expired_timers_local + 1));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END - TEST7... test passed \n");
  }  
  {
    /* Test 7 - Start timer and expiry callback calls stop timer */
    printf("START TEST8 - start 1 timer and in timer expiry callback, start one more timer \n");
    uint64_t expired_timers_local = expired_timers;
    struct timer *tmr;
    tmr = start_timer(2, timer_callback_call_timer_start, NULL);
    sleep(16);
    assert(expired_timers == (expired_timers_local + 2));
    // we should have all my_ut_timers must have expired by now.. 
    printf("END - TEST8... test passed \n");
  }  

  while(1) 
  {
    sleep(1);
  }
  return 0;
}
#endif

/* Public Timer APIs*/
void* start_timer(unsigned int timeout, 
            cbf callback, 
            void *callback_data)
{
  struct timer *node;
  static uint64_t id;
  node = calloc(1, sizeof(struct timer));
  node->id = id++;
  node->timeout = sec_epoch + timeout;
  node->ms_offset = ms_epoch;
  node->cb_data = callback_data;
  node->cbf = callback;
  insert_node(node);
  return (void *)(node); 
}

int stop_timer(void *timer )
{
  // stop timer if its running
  // delete the timer from the sorted list
  struct timer *node = (struct timer *)timer;
  struct timer *temp = NULL; 

  if(IS_CONTROL_INSIDE_CALLBACK(node))
    return 0;

  pthread_mutex_lock(&timer_lock); 

  // We still search the timer even if caller has given timer pointer..
  for(temp = head;(temp != NULL) && (temp != node); temp = temp->next);

  if(temp != NULL)
  {
    if(temp == head)
      head = temp->next;

    if(temp->prev)
      temp->prev->next = temp->next;

    if(temp->next)
      temp->next->prev = temp;

    free(temp); 
    
    pthread_mutex_unlock(&timer_lock); 
    return 0;
  }
  pthread_mutex_unlock(&timer_lock); 
  return -1;
}

int timer_running(void *arg)
{
  struct timer *temp = (struct timer *)arg;
  return find_node(temp); 
}

void init_timer_lib()
{
  pthread_mutex_init(&timer_lock, NULL); 
  pthread_t timer_thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&timer_thread, &attr, &init_lib, NULL);
  return;
}

/* END of public APIs */
