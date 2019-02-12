/*---------------------------------------------------------
* SNOW_3G.h
*---------------------------------------------------------*/
/*
 * The code has been referred from
 * 1. https://www.gsma.com/aboutus/wp-content/uploads/2014/12/snow3gspec.pdf
 * 2. https://www.gsma.com/aboutus/wp-content/uploads/2014/12/uea2uia2d1v21.pdf
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

/* Initialization.
 * Input k[4]: Four 32-bit words making up 128-bit key.
 * Input IV[4]: Four 32-bit words making 128-bit initialization variable.
 * Output: All the LFSRs and FSM are initialized for key generation.
 * See Section 4.1 of
 * (https://www.gsma.com/aboutus/wp-content/uploads/2014/12/snow3gspec.pdf)
 * specs document.
 */


void Initialize(u32 k[4], u32 IV[4]);

/* Generation of Keystream.
* input n: number of 32-bit words of keystream.
* input z: space for the generated keystream, assumes
* memory is allocated already.
* output: generated keystream which is filled in z
* See section 4.2 of
* (https://www.gsma.com/aboutus/wp-content/uploads/2014/12/snow3gspec.pdf)
* specs document.
*/

void GenerateKeystream(u32 n, u32 *z);

