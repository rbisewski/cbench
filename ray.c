//! ray.c
/*
 * Description: Functions needed for the ray class.
 */

#include "ray.h"

//! Function to initialize a new ray.
/*
 * @param    Vec    first vec 
 * @param    Vec    second vec 
 *
 * @return   Ray    newly generated ray object
 */
Ray newRay(Vec o, Vec d) {

    // Variable declaration.
    Ray ray;

    // Assign the given vectors to the ray object.
    ray.o = o;
    ray.d = d;

    // Return a reference to the new ray object.
    return ray;
}
