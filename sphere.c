//! sphere.c
/*
 * Description: Functions needed for the sphere class.
 */

#include "sphere.h"

//! Function to initialize a new sphere.
/*
 * @param    double    radius
 * @param    Vec       position
 * @param    Vec       emission
 * @param    Vec       colour
 * @param    int       reflection
 *
 * @return   Sphere    newly generated sphere object
 */
Sphere newSphere(double radius, Vec position, Vec emission, Vec colour,
  unsigned int reflection) {

    // Variable declaration.
    Sphere s;

    // Assign the given values to the sphere in question.
    s.rad  = radius;
    s.p    = position;
    s.e    = emission;
    s.c    = colour;
    s.refl = reflection;

    // Return the newly created sphere.
    return s;
}

// Returns the distance if the given sphere and ray intersect.
/*
 * @param     Sphere    given sphere to test
 * @param     Ray       possible intersecting ray
 *
 * @return    double    if intersect    --> distance
 *                      no intersection --> 0.0
 */
double intersectSphereAndRay(const Sphere s, const Ray r) {

    //
    // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    //
    Vec op     = subVec(s.p, r.o);
    double t   = 0;
    double eps = 1e-4;
    double b   = dot(op, r.d);
    double det = b * b - dot(op, op) + s.rad * s.rad;

    // If the determinant is less than zero, assume these never intersect.
    if (det < 0) {
        return 0;
    }

    // Otherwise just grab the square fo the determinant.
    det = sqrt(det); 

    // Calculate the value of t using the dot product minus the determinant.
    t = b - det;

    // If t is greater than the emission precision, then just use that
    // distance.
    if (t > eps) {
        return t;
    }

    // Attempt to check if they intersect in the opposite direction by
    // adding the determinant.
    t = b + det;

    // If it intersects and is within the given emission precision, then
    // go ahead and use that value.
    if (t > eps) {
        return t;
    }

    // Otherwise the intersection occurred in neither direction, so then
    // we can assume the sphere and the given ray.
    return 0.0;
}
