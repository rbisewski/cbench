//! vec.h
/*
 * Description: Header file for the vector class.
 */

// Structure that defines the vector.
struct Vec {

    // Coords, also used as rgb colour values.
    double x;
    double y;
    double z;
};

//! Function to add two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    added result of both vectors 
 */
Vec addVec(const Vec &a, const Vec &b) const;

//! Function to subtract two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    subtracted result of both vectors
 */
Vec subVec(const Vec &a, const Vec &b) const;

//! Function to multiply a vector with a double.
/*
 * @param     Vec       vector to multiply
 * @param     double    amount to multiply by
 *
 * @return    Vec       resulting vector multiplied by "b" times
 */
Vec multiplyVec(const Vec &a, double b) const;

//! Function to multiply two vectors.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    resultant vector
 */
Vec multiplyVectors(const Vec &a, const Vec &b) const;

//! Function to return the normal of a given vector.
/*
 * @param     Vec    original vector 
 *
 * @return    Vec    normal of vector
 */
Vec& norm(const Vec &a);

//! Function to calculate the dot-product of a given vector.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
double dot(const Vec &a, const Vec &b);

//! Function to calculate the modulo of two vectors.
/*
 * @param     Vec    first vector
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
Vec modVec(const Vec &a, const Vec &b) const;
