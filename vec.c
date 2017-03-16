//! vec.h
/*
 * Description: Functions needed for the vector class.
 */

//! Function to add two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    added result of both vectors 
 */
Vec addVec(const Vec &a, const Vec &b) const {

    // Input validation, make sure this actually has two vectors.
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Add the (x,y,z) coords of the vectors to vector "a".
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    // Return the added vector result.
    return a;
}

//! Function to subtract two vectors.
/*
 * @param    Vec    first vector 
 * @param    Vec    second vector
 *
 * @return   Vec    subtracted result of both vectors
 */
Vec subVec(const Vec &a, const Vec &b) const {

    // Input validation, make sure this actually has two vectors.
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Subtract the (x,y,z) coords of the vectors to vector "a".
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    // Return the subtracted vector result.
    return a;
}

//! Function to multiply a vector with a double.
/*
 * @param     Vec       vector to multiply
 * @param     double    amount to multiply by
 *
 * @return    Vec       resulting vector multiplied by "b" times
 */
Vec multiplyVec(const Vec &a, double b) const {

    // Input validation, make sure this actually has a vector.
    if (a == NULL) {
        return NULL;
    }

    // Multiply the (x,y,z) coords of the vectors by double "b".
    a.x *= b;
    a.y *= b;
    a.z *= b;

    // Return the subtracted vector result.
    return a;
}

//! Function to multiply two vectors.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    resultant vector
 */
Vec multiplyVectors(const Vec &a, const Vec &b) const {

    // Input validation, make sure this actually has a vector.
    if (a == NULL && b == NULL) {
        return NULL;
    }

    // Multiply the (x,y,z) coords of the vectors by double "b".
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    // Return the subtracted vector result.
    return a;
}

//! Function to return the normal of a given vector.
/*
 * @param     Vec    original vector 
 *
 * @return    Vec    normal of vector
 */
Vec& norm(const Vec &a) {

    // Input validation, make sure this actually has a vector.
    if (a == NULL) {
        return NULL;
    }

    // Calculate the product of squares.
    double ps  = a.x*a.x + a.y*a.y + a.z*a.z;

    // Calculate the inverse product of squares.
    double ips = 0;
    
    // Safety check, prevent possible divide-by-zero errors.
    if (ps != 0) {
        ips = 1 / sqrt(ps);
    }

    // Return a reference to the multiply.
    return multiplyVector(a, ips);
}

//! Function to calculate the dot-product of a given vector.
/*
 * @param     Vec    first vector 
 * @param     Vec    second vector
 *
 * @return    Vec    dot-product of vectors
 */
double dot(const Vec &a, const Vec &b) const {

    // Input validation, make sure this actually has a vector.
    if (a == NULL && b == NULL) {
        return NULL;
    }

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
Vec modVec(const Vec &a, const Vec &b) {

    // Input validation, make sure this actually has a vector.
    if (a == NULL && b == NULL) {
        return NULL;
    }

    // Assemble the module of each coord dimension.
    a.x = a.y * b.z - a.z * b.y;
    a.y = a.z * b.x - a.x * b.z;
    a.z = a.x * b.y - a.y * b.x;

    // Return the dot-product vector result.
    return a;
}
