#ifndef __MATRIX_3_H
#define __MATRIX_3_H

#include <laml/Data_types.hpp>

#include <laml/Matrix2.hpp>
#include <laml/Vector.hpp>

namespace laml {

    struct Matrix3x3 {
        constexpr Matrix3x3();
        constexpr Matrix3x3(real_t _11, real_t _21, real_t _31, 
                            real_t _12, real_t _22, real_t _32, 
                            real_t _13, real_t _23, real_t _33);
        constexpr Matrix3x3(real_t _diag);
        Matrix3x3(const float* in_data);
        constexpr Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3);

        union {
            real_t _data[9];
            laml::Vector3 _cols[3];
            struct { real_t c_11, c_21, c_31, c_12, c_22, c_32, c_13, c_23, c_33; };
        };

        // access like an array
        Vector3& operator[](size_t idx);
        const Vector3& operator[](size_t idx) const;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix3x3 operator+(const Matrix3x3& mat, const Matrix3x3& other);
    Matrix3x3 operator-(const Matrix3x3& mat, const Matrix3x3& other);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix3x3 operator*(const Matrix3x3& mat, const real_t& factor);
    Matrix3x3 operator/(const Matrix3x3& mat, const real_t& factor);

    // Free functions
    void identity(Matrix3x3& mat);
    void fill(Matrix3x3& mat, real_t value);

    // 3x3 * 3x3 multiply specialization
    Matrix3x3 mul(const Matrix3x3& m1, const Matrix3x3& m2);
    Matrix3x3 transpose(const Matrix3x3& mat);

    // determinant - 3x3 case
    real_t det(const Matrix3x3& mat);

    real_t trace(const Matrix3x3& mat);
    Vector3 diag(const Matrix3x3& mat);

    // minor matrix
    Matrix2x2 minor(const Matrix3x3& mat, size_t pick_col, size_t pick_row);

    // inverse
    Matrix3x3 inverse(const Matrix3x3& mat);

    typedef Matrix3x3 Mat3;
}

#endif