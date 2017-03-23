//! misc.h
/*
 * Description: Header file for misc functions.
 */

#ifndef __MISC_H_
#define __MISC_H_

// C99 includes.
#include <math.h>

//! Force a floating-point number to be between 0 and 1.
/*
 * @param    double    given number
 *
 * @return   double    a value between 0 (min) and 1 (max).
 */
double clamp(double);

//! Convert an analog floating-point representation to an integer.
/*
 * @param    double    given number
 *
 * @return   int       value of number as an integer.
 */
int toInt(double);

#endif
