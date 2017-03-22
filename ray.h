//! ray.h
/*
 * Description: Header file for the ray class.
 */

#ifndef __RAY_H_
#define __RAY_H_

#include "vec.h"

//! Structure to hold the ray object.
typedef struct Ray {
    Vec o;
    Vec d;
} Ray;

//! Function to initialize a new ray.
/*
 * @param    Vec    first vec 
 * @param    Vec    second vec 
 *
 * @return   Ray    newly generated ray object
 */
Ray newRay(Vec, Vec);

#endif
