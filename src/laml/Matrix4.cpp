#include <laml/Matrix4.hpp>

namespace laml {

    Matrix4x4::Matrix4x4() : _data{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } {}
    Matrix4x4::Matrix4x4(real_t _11, real_t _21, real_t _31, real_t _41,
                                   real_t _12, real_t _22, real_t _32, real_t _42,
                                   real_t _13, real_t _23, real_t _33, real_t _43,
                                   real_t _14, real_t _24, real_t _34, real_t _44) : 
        _data{ _11, _21, _31, _41, _12, _22, _32, _42, _13, _23, _33, _43, _14, _24, _34, _44 } {}
    Matrix4x4::Matrix4x4(real_t _diag) : _data{ _diag, 0, 0, 0, 0, _diag, 0, 0, 0, 0, _diag, 0, 0, 0, 0, _diag } {}
    Matrix4x4::Matrix4x4(const float* in_data) : 
        _data{ in_data[0],  in_data[1],  in_data[2],  in_data[3], 
               in_data[4],  in_data[5],  in_data[6],  in_data[7], 
               in_data[8],  in_data[9],  in_data[10], in_data[11], 
               in_data[12], in_data[13], in_data[14], in_data[15] } {}
    Matrix4x4::Matrix4x4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4) : _cols{v1, v2, v3, v4} {}

    // access like an array
    Vector4& Matrix4x4::operator[](size_t idx) {
        return _cols[idx];
    }
    const Vector4& Matrix4x4::operator[](size_t idx) const {
        return _cols[idx];
    }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix4x4 operator+(const Matrix4x4& mat, const Matrix4x4& other) {
        Matrix4x4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = mat[n] + other[n];
        }
        return res;
    }
	
    Matrix4x4 operator-(const Matrix4x4& mat, const Matrix4x4& other) {
        Matrix4x4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = mat[n] - other[n];
        }
        return res;
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix4x4 operator*(const Matrix4x4& mat, const real_t& factor) {
        Matrix4x4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = mat[n] * factor;
        }
        return res;
    }

    Matrix4x4 operator/(const Matrix4x4& mat, const real_t& factor) {
        Matrix4x4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = mat[n] / factor;
        }
        return res;
    }

    // Free functions
    void identity(Matrix4x4& mat) {
        fill(mat, static_cast<real_t>(0.0));
        for (size_t i = 0; i < 4; i++) {
            mat[i][i] = static_cast<real_t>(1.0);
        }
    }

    void fill(Matrix4x4& mat, real_t value) {
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
    Matrix4x4 mul(const Matrix4x4& m1, const Matrix4x4& m2) {
        //std::cout << "FAST MUL [" << 3 << "," << 3 << "]x[" << 3 << "," << 3 << "]" << std::endl;
        return Matrix4x4(
            m1.c_11 * m2.c_11 + m1.c_12 * m2.c_21 + m1.c_13 * m2.c_31 + m1.c_14 * m2.c_41, // col 1
            m1.c_21 * m2.c_11 + m1.c_22 * m2.c_21 + m1.c_23 * m2.c_31 + m1.c_24 * m2.c_41,
            m1.c_31 * m2.c_11 + m1.c_32 * m2.c_21 + m1.c_33 * m2.c_31 + m1.c_34 * m2.c_41,
            m1.c_41 * m2.c_11 + m1.c_42 * m2.c_21 + m1.c_43 * m2.c_31 + m1.c_44 * m2.c_41,
    
            m1.c_11 * m2.c_12 + m1.c_12 * m2.c_22 + m1.c_13 * m2.c_32 + m1.c_14 * m2.c_42, // col 2
            m1.c_21 * m2.c_12 + m1.c_22 * m2.c_22 + m1.c_23 * m2.c_32 + m1.c_24 * m2.c_42,
            m1.c_31 * m2.c_12 + m1.c_32 * m2.c_22 + m1.c_33 * m2.c_32 + m1.c_34 * m2.c_42,
            m1.c_41 * m2.c_12 + m1.c_42 * m2.c_22 + m1.c_43 * m2.c_32 + m1.c_44 * m2.c_42,
    
            m1.c_11 * m2.c_13 + m1.c_12 * m2.c_23 + m1.c_13 * m2.c_33 + m1.c_14 * m2.c_43, // col 3
            m1.c_21 * m2.c_13 + m1.c_22 * m2.c_23 + m1.c_23 * m2.c_33 + m1.c_24 * m2.c_43,
            m1.c_31 * m2.c_13 + m1.c_32 * m2.c_23 + m1.c_33 * m2.c_33 + m1.c_34 * m2.c_43,
            m1.c_41 * m2.c_13 + m1.c_42 * m2.c_23 + m1.c_43 * m2.c_33 + m1.c_44 * m2.c_43,
            
            m1.c_11 * m2.c_14 + m1.c_12 * m2.c_24 + m1.c_13 * m2.c_34 + m1.c_14 * m2.c_44, // col 4
            m1.c_21 * m2.c_14 + m1.c_22 * m2.c_24 + m1.c_23 * m2.c_34 + m1.c_24 * m2.c_44,
            m1.c_31 * m2.c_14 + m1.c_32 * m2.c_24 + m1.c_33 * m2.c_34 + m1.c_34 * m2.c_44,
            m1.c_41 * m2.c_14 + m1.c_42 * m2.c_24 + m1.c_43 * m2.c_34 + m1.c_44 * m2.c_44);
    }

    Matrix4x4 transpose(const Matrix4x4& mat) {
        Matrix4x4 res;
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                res[j][i] = mat[i][j]; // opposite indexing to transpose the values
            }
        }
        return res;
    }

    // determinant - 4x4 case
    real_t det(const Matrix4x4& mat) {
        return mat[0][0] * mat[1][1] * mat[2][2] -
               mat[0][0] * mat[1][2] * mat[2][1] -
               mat[0][1] * mat[1][0] * mat[2][2] +
               mat[0][1] * mat[1][2] * mat[2][0] +
               mat[0][2] * mat[1][0] * mat[2][1] -
               mat[0][2] * mat[1][1] * mat[2][0];
    }

    real_t trace(const Matrix4x4& mat) {
        real_t res = static_cast<real_t>(0.0);
        for (size_t n = 0; n < 4; n++) {
            res = res + mat[n][n];
        }
        return res;
    }

    Vector4 diag(const Matrix4x4& mat) {
        Vector4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = mat[n][n];
        }
        return res;
    }

    // minor matrix
    Matrix3x3 minor(const Matrix4x4& mat, size_t pick_col, size_t pick_row) {
        Matrix3x3 minor;
        for (size_t i = 0; i < 4 - 1; i++) {
            size_t new_i = (i + 1 > pick_col) ? i + 1 : i;
            for (size_t j = 0; j < 4 - 1; j++) {
                size_t new_j = (j + 1 > pick_row) ? j + 1 : j;
    
                minor[i][j] = mat[new_i][new_j];
            }
        }
        return minor;
    }

    // inverse
    Matrix4x4 inverse(const Matrix4x4& mat) {
        /*
        * inv(m) = adj(m)/det(m)
        * only valid if det(m) != 0, so calculate that first.
        *
        * to calculate adj(m):
        *  - transpose m ->mT
        *  - replace every element (i,j) of mT with the det(minor(m,i,j))
        *  - multiply every element by its cofactor (+/- 1 alternating)
        */

        real_t determinant = det(mat);
        if (fabs(determinant) < 1e-8) {
            #if 0
                std::cout << "Cannot inverse matrix: determinant = " << determinant << std::endl;
            #endif
            return mat;
        }

        //Matrix4x4 adj(
        //    (mat.c_22 * mat.c_33 - mat.c_32 * mat.c_23),
        //    (mat.c_31 * mat.c_23 - mat.c_21 * mat.c_33),
        //    (mat.c_21 * mat.c_32 - mat.c_22 * mat.c_31),
//
        //    (mat.c_32 * mat.c_13 - mat.c_12 * mat.c_33),
        //    (mat.c_11 * mat.c_33 - mat.c_31 * mat.c_13),
        //    (mat.c_31 * mat.c_12 - mat.c_11 * mat.c_32),
//
        //    (mat.c_12 * mat.c_23 - mat.c_22 * mat.c_13),
        //    (mat.c_21 * mat.c_13 - mat.c_11 * mat.c_23),
        //    (mat.c_11 * mat.c_22 - mat.c_21 * mat.c_12));
//
        Matrix4x4 adj(1.0);
        return adj / determinant;
    }
}