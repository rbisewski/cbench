//! cbench.h
/*
 * Description: The main cbench header file.
 */

#ifndef __CBENCH_H_
#define __CBENCH_H_

// C99 includes.
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Project-wide includes.
#include "misc.h"
#include "vec.h"
#include "ray.h"
#include "sphere.h"

// Defines for the different reflection types.
#define DIFF 0
#define SPEC 1
#define REFR 2

// ISO C99 does not require definitions of PI beyond 3.14, ergo define it
// here in the event that some function or equation requests it.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// End of header.
#endif
