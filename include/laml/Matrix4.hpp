#ifndef __MATRIX_4_H
#define __MATRIX_4_H

#include <laml/Data_types.hpp>

#include <laml/Matrix3.hpp>
#include <laml/Vector.hpp>

namespace laml {

    struct Matrix4x4 {
        Matrix4x4();
        Matrix4x4(real_t _11, real_t _21, real_t _31, real_t _41, 
                            real_t _12, real_t _22, real_t _32, real_t _42, 
                            real_t _13, real_t _23, real_t _33, real_t _43,
                            real_t _14, real_t _24, real_t _34, real_t _44);
        Matrix4x4(real_t _diag);
        Matrix4x4(real_t _diag1, real_t _diag2, real_t _diag3, real_t _diag4);
        Matrix4x4(const float* in_data);
        Matrix4x4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
        Matrix4x4(const Matrix3x3& mat);

        union {
            real_t _data[16];
            laml::Vector4 _cols[4];
            struct { real_t c_11, c_21, c_31, c_41, c_12, c_22, c_32, c_42, c_13, c_23, c_33, c_43, c_14, c_24, c_34, c_44; };
        };

        // access like an array
        Vector4& operator[](size_t idx);
        const Vector4& operator[](size_t idx) const;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix4x4 operator+(const Matrix4x4& mat, const Matrix4x4& other);
    Matrix4x4 operator-(const Matrix4x4& mat, const Matrix4x4& other);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix4x4 operator*(const Matrix4x4& mat, const real_t& factor);
    Matrix4x4 operator/(const Matrix4x4& mat, const real_t& factor);

    // Free functions
    void identity(Matrix4x4& mat);
    void fill(Matrix4x4& mat, real_t value);

    // 4x4 * 4x4 multiply specialization
    Matrix4x4 mul(const Matrix4x4& m1, const Matrix4x4& m2);
    Matrix4x4 transpose(const Matrix4x4& mat);

    // determinant - 4x4 case
    real_t det(const Matrix4x4& mat);

    real_t trace(const Matrix4x4& mat);
    Vector4 diag(const Matrix4x4& mat);

    // minor matrix
    Matrix3x3 minor(const Matrix4x4& mat, size_t pick_col, size_t pick_row);

    // inverse
    Matrix4x4 inverse(const Matrix4x4& mat);

    typedef Matrix4x4 Mat4;
}

#endif