#ifndef __MATRIX_3_H
#define __MATRIX_3_H

#include <laml/matrix_base.hpp>

namespace rh::laml {
#pragma warning(disable : 4201) // complains about unnammed union structs
    template<typename T>
    struct Matrix<T, 3, 3> {
        typedef T Type;

        constexpr inline size_t num_rows() const { return 3; }
        constexpr inline size_t num_cols() const { return 3; }

        constexpr Matrix() : _data{ 0,0,0,0,0,0,0,0,0 } {}
        constexpr Matrix(T _11, T _21, T _31, T _12, T _22, T _32, T _13, T _23, T _33) : 
            _data{ _11, _21, _31, _12, _22, _32, _13, _23, _33 } {}
        constexpr Matrix(T _diag) : _data{ _diag, 0, 0, 0, _diag, 0, 0, 0, _diag } {}
        Matrix(const float* in_data) : 
            _data{ in_data[0], in_data[1], in_data[2], in_data[3], in_data[4], in_data[5], in_data[6], in_data[7], in_data[8] } {}

        union {
            T _data[16];
            laml::Vector<T, 3> _cols[3];
            struct { T c_11, c_21, c_31, c_12, c_22, c_32, c_13, c_23, c_33; };
        };

        // access like an array
        Vector<T, 3>& operator[](size_t idx) {
            return _cols[idx];
        }
        const Vector<T, 3>& operator[](size_t idx) const {
            return _cols[idx];
        }
    };
#pragma warning(default : 4201)

    // 3x3 * 3x3 multiply specialization
    template<typename T>
    Matrix<T, 3, 3> mul(const Matrix<T, 3, 3>& m1, const Matrix<T, 3, 3>& m2) {
        //std::cout << "FAST MUL [" << 3 << "," << 3 << "]x[" << 3 << "," << 3 << "]" << std::endl;
        return Matrix<T, 3, 3>(
            m1.c_11 * m2.c_11 + m1.c_12 * m2.c_21 + m1.c_13 * m2.c_31, // col 1
            m1.c_21 * m2.c_11 + m1.c_22 * m2.c_21 + m1.c_23 * m2.c_31,
            m1.c_31 * m2.c_11 + m1.c_32 * m2.c_21 + m1.c_33 * m2.c_31,
    
            m1.c_11 * m2.c_12 + m1.c_12 * m2.c_22 + m1.c_13 * m2.c_32, // col 2
            m1.c_21 * m2.c_12 + m1.c_22 * m2.c_22 + m1.c_23 * m2.c_32,
            m1.c_31 * m2.c_12 + m1.c_32 * m2.c_22 + m1.c_33 * m2.c_32,
    
            m1.c_11 * m2.c_13 + m1.c_12 * m2.c_23 + m1.c_13 * m2.c_33, // col 3
            m1.c_21 * m2.c_13 + m1.c_22 * m2.c_23 + m1.c_23 * m2.c_33,
            m1.c_31 * m2.c_13 + m1.c_32 * m2.c_23 + m1.c_33 * m2.c_33);
    }

}

#endif