#include <laml/Matrix3.hpp>

namespace laml {

    constexpr Matrix3x3::Matrix3x3() : _data{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } {}
    constexpr Matrix3x3::Matrix3x3(real_t _11, real_t _21, real_t _31, 
                        real_t _12, real_t _22, real_t _32, 
                        real_t _13, real_t _23, real_t _33) : 
        _data{ _11, _21, _31, _12, _22, _32, _13, _23, _33 } {}
    constexpr Matrix3x3::Matrix3x3(real_t _diag) : _data{ _diag, 0, 0, 0, _diag, 0, 0, 0, _diag } {}
    Matrix3x3::Matrix3x3(const float* in_data) : 
        _data{ in_data[0], in_data[1], in_data[2], in_data[3], in_data[4], in_data[5], in_data[6], in_data[7], in_data[8] } {}
    constexpr Matrix3x3::Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3) : _cols{v1, v2, v3} {}

    // access like an array
    Vector3& Matrix3x3::operator[](size_t idx) {
        return _cols[idx];
    }
    const Vector3& Matrix3x3::operator[](size_t idx) const {
        return _cols[idx];
    }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix3x3 operator+(const Matrix3x3& mat, const Matrix3x3& other) {
        Matrix3x3 res;
        for (size_t n = 0; n < 3; n++) {
            res[n] = mat[n] + other[n];
        }
        return res;
    }
	
    Matrix3x3 operator-(const Matrix3x3& mat, const Matrix3x3& other) {
        Matrix3x3 res;
        for (size_t n = 0; n < 3; n++) {
            res[n] = mat[n] - other[n];
        }
        return res;
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix3x3 operator*(const Matrix3x3& mat, const real_t& factor) {
        Matrix3x3 res;
        for (size_t n = 0; n < 3; n++) {
            res[n] = mat[n] * factor;
        }
        return res;
    }

    Matrix3x3 operator/(const Matrix3x3& mat, const real_t& factor) {
        Matrix3x3 res;
        for (size_t n = 0; n < 3; n++) {
            res[n] = mat[n] / factor;
        }
        return res;
    }

    // Free functions
    void identity(Matrix3x3& mat) {
        fill(mat, static_cast<real_t>(0.0));
        for (size_t i = 0; i < 3; i++) {
            mat[i][i] = static_cast<real_t>(1.0);
        }
    }

    void fill(Matrix3x3& mat, real_t value) {
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
    Matrix3x3 mul(const Matrix3x3& m1, const Matrix3x3& m2) {
        //std::cout << "FAST MUL [" << 3 << "," << 3 << "]x[" << 3 << "," << 3 << "]" << std::endl;
        return Matrix3x3(
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

    Matrix3x3 transpose(const Matrix3x3& mat) {
        Matrix3x3 res;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                res[j][i] = mat[i][j]; // opposite indexing to transpose the values
            }
        }
        return res;
    }

    // determinant - 3x3 case
    real_t det(const Matrix3x3& mat) {
        return mat[0][0] * mat[1][1] * mat[2][2] -
               mat[0][0] * mat[1][2] * mat[2][1] -
               mat[0][1] * mat[1][0] * mat[2][2] +
               mat[0][1] * mat[1][2] * mat[2][0] +
               mat[0][2] * mat[1][0] * mat[2][1] -
               mat[0][2] * mat[1][1] * mat[2][0];
    }

    real_t trace(const Matrix3x3& mat) {
        real_t res = static_cast<real_t>(0.0);
        for (size_t n = 0; n < 3; n++) {
            res = res + mat[n][n];
        }
        return res;
    }

    Vector3 diag(const Matrix3x3& mat) {
        Vector3 res;
        for (size_t n = 0; n < 3; n++) {
            res[n] = mat[n][n];
        }
        return res;
    }

    // minor matrix
    Matrix2x2 minor(const Matrix3x3& mat, size_t pick_col, size_t pick_row) {
        Matrix2x2 minor;
        for (size_t i = 0; i < 3 - 1; i++) {
            size_t new_i = (i + 1 > pick_col) ? i + 1 : i;
            for (size_t j = 0; j < 3 - 1; j++) {
                size_t new_j = (j + 1 > pick_row) ? j + 1 : j;
    
                minor[i][j] = mat[new_i][new_j];
            }
        }
        return minor;
    }

    // inverse
    Matrix3x3 inverse(const Matrix3x3& mat) {
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

        Matrix3x3 adj(
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