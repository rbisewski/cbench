//! sphere.h
/*
 * Description: Header file for the ray class.
 */

#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "vec.h"
#include "ray.h"

//! Structure to hold the sphere object.
typedef struct Sphere {

    // Radius
    double rad;

    // Position
    Vec p;

    // Emission
    Vec e;

    // Colour
    Vec c;

    // Reflection type
    //
    // 0 --> DIFFuse
    // 1 --> SPECular,
    // 2 --> REFRactive
    //
    unsigned int refl;
} Sphere;

//! Function to initialize a new sphere.
/*
 * @param    double    radius
 * @param    Vec       position
 * @param    Vec       emission
 * @param    Vec       colour
 * @param    uint      reflection
 *
 * @return   Sphere    newly generated sphere object
 */
Sphere newSphere(double, Vec, Vec, Vec, unsigned int);

// Returns the distance if the given sphere and ray intersect.
/*
 * @param     Sphere    given sphere to test
 * @param     Ray       possible intersecting ray
 *
 * @return    double    if intersect    --> distance
 *                      no intersection --> 0.0
 */
double intersect(const Sphere s, const Ray r);

#endif
