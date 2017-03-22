//! vec.c
/*
 * Description: Functions needed for the vector class.
 */

#include "vec.h"

//! Function to initialize a new vector.
/*
 * @param    double    x coord
 * @param    double    y coord
 * @param    double    z coord
 *
 * @return   Vec       newly generated vector object
 */
Vec newVector(double x, double y, double z) {

    // Attempt to allocate memory for a new vector.
    Vec vector;

    // Assign the (x,y,z) coords.
    vector.x = x;
    vector.y = y;
    vector.z = z;

    // Return the newly initialized vector.
    return vector;
}

//! Function to add two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    added result of both vectors 
 */
Vec addVec(const Vec a, const Vec b) {

    // Return the added vector result.
    return newVector(a.x+b.x, a.y+b.y, a.z+b.z);
}

//! Function to subtract two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    subtracted result of both vectors
 */
Vec subVec(const Vec a, const Vec b) {

    // Return the subtracted vector result.
    return newVector(a.x-b.x, a.y-b.y, a.z-b.z);
}

//! Function to multiply a vector with a double.
/*
 * @param     Vec       vector to multiply
 * @param     double    amount to multiply by
 *
 * @return    Vec       resulting vector multiplied by "b" times
 */
Vec multiplyVec(const Vec a, double b) {

    // Return the multiplied vector result.
    return newVector(a.x*b, a.y*b, a.z*b);
}

//! Function to multiply two vectors.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    resultant vector
 */
Vec multiplyVectors(const Vec a, const Vec b) {

    // Return the multiplied vector result.
    return newVector(a.x*b.x, a.y*b.y, a.z*b.z);
}

//! Function to return the normal of a given vector.
/*
 * @param     Vec    original vector 
 *
 * @return    Vec    normal of vector
 */
Vec vectorNormal(const Vec a) {

    // Calculate the product of squares.
    double ps  = a.x*a.x + a.y*a.y + a.z*a.z;

    // Calculate the inverse product of squares.
    double ips = 0;
    
    // Safety check, prevent possible divide-by-zero errors or
    // imaginary-number errors.
    if (ps > 0) {
        ips = 1 / sqrt(ps);
    }

    // Return a reference to the multiply.
    return multiplyVec(a, ips);
}

//! Function to calculate the dot-product of a given vector.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
double dot(const Vec a, const Vec b) {

    // Calculate and return the dot-product.
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

//! Function to calculate the modulo of two vectors.
/*
 * @param     Vec    first vector
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
Vec modVec(const Vec a, const Vec b) {

    // Assemble the module of each coord dimension.
    double x = a.y * b.z - a.z * b.y;
    double y = a.z * b.x - a.x * b.z;
    double z = a.x * b.y - a.y * b.x;

    // Return the dot-product vector result.
    return newVector(x,y,z);
}
