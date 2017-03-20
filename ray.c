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

    // Input validation, make sure this actually got an array.
    if (!o || !d) {
        return NULL;
    }

    // Calloc some memory for the new ray object.
    Ray ray = calloc(1, sizeof(Ray));

    // Sanity check, make sure this actually properly allocated memory.
    if (!ray) {
        return NULL;
    }

    // Assign the given vectors to the ray object.
    ray.o = o;
    ray.d = d;

    // Return a reference to the new ray object.
    return ray;
}
