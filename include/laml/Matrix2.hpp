#ifndef __MATRIX_2_H
#define __MATRIX_2_H

#include <laml/matrix_base.hpp>

namespace rh::laml {
#pragma warning(disable : 4201) // complains about unnammed union structs
    template<typename T> 
    struct Matrix<T, 2, 2> {
        typedef T Type;

        constexpr inline size_t num_rows() const { return 2; }
        constexpr inline size_t num_cols() const { return 2; }

        constexpr Matrix() : _data{0,0,0,0} {}
        constexpr Matrix(T _11, T _21, T _12, T _22) : _data{ _11, _21, _12, _22 } {}
        constexpr Matrix(T _diag) : _data{ _diag, 0, 0,_diag } {}
        Matrix(const float* in_data) : _data{ in_data[0], in_data[1], in_data[2], in_data[3] } {}

        union {
            T _data[4];
            laml::Vector<T, 2> _cols[2];
            struct { T c_11, c_21, c_12, c_22; };
        };

        // access like an array
        Vector<T, 2>& operator[](size_t idx) {
            return _cols[idx];
        }
        const Vector<T, 2>& operator[](size_t idx) const {
            return _cols[idx];
        }
    };
#pragma warning(default : 4201)

    // 2x2 * 2x2 multiply specialization
    template<typename T>
        Matrix<T, 2, 2> mul(const Matrix<T, 2, 2>& m1, const Matrix<T, 2, 2>& m2) {
        //std::cout << "FAST MUL [" << 2 << "," << 2 << "]x[" << 2 << "," << 2 << "]" << std::endl;
        return Matrix<T, 2, 2>(
            m1.c_11 * m2.c_11 + m1.c_12 * m2.c_21,
            m1.c_21 * m2.c_11 + m1.c_22 * m2.c_21,
            m1.c_11 * m2.c_12 + m1.c_12 * m2.c_22, 
            m1.c_21 * m2.c_12 + m1.c_22 * m2.c_22);
    }

}

#endif