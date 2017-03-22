//! vec.h
/*
 * Description: Header file for the vector class.
 */

#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <math.h>
#include <stdlib.h>

// Structure that defines the vector.
typedef struct Vec {

    // Coords, also used as rgb colour values.
    double x;
    double y;
    double z;
} Vec;

//! Function to initialize a new vector.
/*
 * @param    double    x coord
 * @param    double    y coord
 * @param    double    z coord
 *
 * @return   Vec       newly generated vector object
 */
Vec newVector(double, double, double);

//! Function to add two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    added result of both vectors 
 */
Vec addVec(const Vec a, const Vec b);

//! Function to subtract two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    subtracted result of both vectors
 */
Vec subVec(const Vec a, const Vec b);

//! Function to multiply a vector with a double.
/*
 * @param     Vec       vector to multiply
 * @param     double    amount to multiply by
 *
 * @return    Vec       resulting vector multiplied by "b" times
 */
Vec multiplyVec(const Vec a, double b);

//! Function to multiply two vectors.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    resultant vector
 */
Vec multiplyVectors(const Vec a, const Vec b);

//! Function to return the normal of a given vector.
/*
 * @param     Vec    original vector
 *
 * @return    Vec    normal of vector
 */
Vec vectorNormal(const Vec a);

//! Function to calculate the dot-product of a given vector.
/*
 * @param     Vec    first vector
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
double dot(const Vec a, const Vec b);

//! Function to calculate the modulo of two vectors.
/*
 * @param     Vec    first vector
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
Vec modVec(const Vec a, const Vec b);

#endif
