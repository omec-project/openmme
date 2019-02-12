/*--------------------------------------------------------
 * f9.h
 *--------------------------------------------------------
*/


/* The code has been referred from
 * 1.https://www.gsma.com/aboutus/wp-content/uploads/2014/12/uea2uia2d1v21.pdf
 * 2.https://www.gsma.com/aboutus/wp-content/uploads/2014/12/snow3gspec.pdf
*/

#ifndef F9_H_
#define F9_H_
#include "snow_3g.h"

/* f9.
 * Input key: 128 bit Integrity Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input fresh: 32-bit Random number.
 * Input dir:1 bit, direction of transmission (in the LSB).
 * Input data: length number of bits, input bit stream.
 * Input length: 64 bit Length, i.e., the number of bits to be MAC'd.
 * Output : 32 bit block used as MAC
 * Generates 32-bit MAC using UIA2 algorithm as defined in Section 4
 * of https://www.gsma.com/aboutus/wp-content/uploads/2014/12/snow3gspec.pdf
 * specs document.
 */


u8* f9( u8* key, u32 count, u32 fresh, u32 dir, u8 *data, u64 length);

#endif

