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
        constexpr Matrix(const Vector<T, 3>& v1, const Vector<T, 3>& v2, const Vector<T, 3>& v3) : _cols{v1, v2, v3} {}

        union {
            T _data[9];
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

    template<typename T>
    void fill(Matrix<T, 3, 3>& mat, T value) {
        mat.c_11 = value;
        mat.c_12 = value;
        mat.c_13 = value;
        mat.c_21 = value;
        mat.c_22 = value;
        mat.c_23 = value;
        mat.c_31 = value;
        mat.c_32 = value;
        mat.c_33 = value;
    }

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

    // determinant - 3x3 case
    template<typename T>
    T det(const Matrix<T, 3, 3>& mat) {
        return mat[0][0] * mat[1][1] * mat[2][2] -
            mat[0][0] * mat[1][2] * mat[2][1] -
            mat[0][1] * mat[1][0] * mat[2][2] +
            mat[0][1] * mat[1][2] * mat[2][0] +
            mat[0][2] * mat[1][0] * mat[2][1] -
            mat[0][2] * mat[1][1] * mat[2][0];
    }

    // inverse
    template<typename T>
    Matrix<T, 3, 3> inverse(const Matrix<T, 3, 3>& mat) {
        /*
        * inv(m) = adj(m)/det(m)
        * only valid if det(m) != 0, so calculate that first.
        *
        * to calculate adj(m):
        *  - transpose m ->mT
        *  - replace every element (i,j) of mT with the det(minor(m,i,j))
        *  - multiply every element by its cofactor (+/- 1 alternating)
        */

        T determinant = det(mat);
        if (fabs(determinant) < 1e-8) {
            std::cout << "Cannot inverse matrix: determinant = " << determinant << std::endl;
            return mat;
        }

        Matrix<T, 3, 3> adj(
            (mat.c_22 * mat.c_33 - mat.c_32 * mat.c_23),
            (mat.c_31 * mat.c_23 - mat.c_21 * mat.c_33),
            (mat.c_21 * mat.c_32 - mat.c_22 * mat.c_31),

            (mat.c_32 * mat.c_13 - mat.c_12 * mat.c_33),
            (mat.c_11 * mat.c_33 - mat.c_31 * mat.c_13),
            (mat.c_31 * mat.c_12 - mat.c_11 * mat.c_32),

            (mat.c_12 * mat.c_23 - mat.c_22 * mat.c_13),
            (mat.c_21 * mat.c_13 - mat.c_11 * mat.c_23),
            (mat.c_11 * mat.c_22 - mat.c_21 * mat.c_12));

        return adj / determinant;
    }

}

#endif