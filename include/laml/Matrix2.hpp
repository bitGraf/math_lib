#ifndef __MATRIX_2_H
#define __MATRIX_2_H

#ifdef LAML_STD_INCLUDE
#include <ostream>
#endif

#include <laml/Data_types.hpp>
#include <laml/Vector.hpp>

namespace laml {

    struct Matrix2x2 {
        
        constexpr Matrix2x2();
        constexpr Matrix2x2(real_t _11, real_t _21, 
                            real_t _12, real_t _22);
        constexpr Matrix2x2(real_t _diag);
        Matrix2x2(const float* in_data);
        constexpr Matrix2x2(const Vector2& v1, const Vector2& v2);

        union {
            real_t _data[4];
            laml::Vector2 _cols[2];
            struct { real_t c_11, c_21, c_12, c_22; };
        };

        // access like an array
        Vector2& operator[](size_t idx);
        const Vector2& operator[](size_t idx) const;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix2x2 operator+(const Matrix2x2& mat, const Matrix2x2& other);
    Matrix2x2 operator-(const Matrix2x2& mat, const Matrix2x2& other);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix2x2 operator*(const Matrix2x2& mat, const real_t& factor);
    Matrix2x2 operator/(const Matrix2x2& mat, const real_t& factor);

    // Free functions
    void identity(Matrix2x2& mat);
    void fill(Matrix2x2& mat, real_t value);

    // 2x2 * 2x2 multiply specialization
    Matrix2x2 mul(const Matrix2x2& m1, const Matrix2x2& m2);
    Matrix2x2 transpose(const Matrix2x2& mat);

    // determinant - 2x2 case
    real_t det(const Matrix2x2& mat);

    real_t trace(const Matrix2x2& mat);
    Vector2 diag(const Matrix2x2& mat);

    // minor matrix
    real_t minor(const Matrix2x2& mat, size_t pick_col, size_t pick_row);

    // inverse
    Matrix2x2 inverse(const Matrix2x2& mat);

    typedef Matrix2x2 Mat2;
}

#endif