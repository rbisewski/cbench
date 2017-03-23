//! misc.c
/*
 * Description: Various misc functions that are useful for this project.
 */

#include "misc.h"

//! Force a floating-point number to be between 0 and 1.
/*
 * @param    double    given number
 *
 * @return   double    a value between 0 (min) and 1 (max).
 */
double clamp(double x) {
    return x<0 ? 0 : x>1 ? 1 : x;
}

//! Convert an analog floating-point representation to an integer.
/*
 * @param    double    given number
 *
 * @return   int       value of number as an integer.
 */
int toInt(double x) {
    return (int) pow(clamp(x),1/2.2)*255+.5;
}
