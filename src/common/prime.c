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

#include <math.h>
#include "prime.h"

#if 0
/*****************************************
 * Return whether value is prime or not
 *
 * Returns:
 *   1  = prime
 *   0  = not prime
 *   -1 = undefined (i.e. x < 2)
*****************************************/
int onf_is_prime(const int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}
#endif

/*****************************************
 * Return whether value is prime or not
 *
 * Returns:
 *   true  = prime
 *   false  = not prime
*****************************************/
bool onf_is_prime(int n) 
{ 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    if (n%2 == 0 || n%3 == 0) return false; 
  
    for (int i=5; i*i<=n; i=i+6) 
    {
        if (n%i == 0 || n%(i+2) == 0)
        {
           return false;
        }
    }
  
    return true; 
} 

/*****************************************
 * Return the next prime after x, or x if x is prime
*****************************************/
int onf_next_prime(int x) {
    while (onf_is_prime(x) != true) {
        x++;
    }
    return x;
}
