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

    // If less than zero, go ahead and return zero.
    if (x < 0.0) {
        return 0.0;
    }

    // If greater than 1, go ahead and just return 1.
    if (x > 1.0) {
        return 1.0;
    }

    // If between 0 and 1, go ahead and return x.
    return x;
}

//! Convert an analog floating-point representation to an integer.
/*
 * @param    double    given number
 *
 * @return   int       value of number as an integer.
 */
int toInt(double x) {
    return (int) pow(clamp(x), 0.4545) * 255.0 + 0.5;
}
