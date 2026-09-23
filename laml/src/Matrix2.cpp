#include <laml/Matrix2.hpp>

namespace laml {

    constexpr Matrix2x2::Matrix2x2() : _data{ 0.0, 0.0, 0.0, 0.0 } {}
    constexpr Matrix2x2::Matrix2x2(real_t _11, real_t _21, 
                        real_t _12, real_t _22) : 
        _data{ _11, _21, _12, _22 } {}
    constexpr Matrix2x2::Matrix2x2(real_t _diag) : _data{ _diag, 0, 0, _diag } {}
    Matrix2x2::Matrix2x2(const float* in_data) : 
        _data{ in_data[0], in_data[1], in_data[2], in_data[3] } {}
    constexpr Matrix2x2::Matrix2x2(const Vector2& v1, const Vector2& v2) : _cols{v1, v2} {}

    // access like an array
    Vector2& Matrix2x2::operator[](size_t idx) {
        return _cols[idx];
    }
    const Vector2& Matrix2x2::operator[](size_t idx) const {
        return _cols[idx];
    }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Matrix2x2 operator+(const Matrix2x2& mat, const Matrix2x2& other) {
        Matrix2x2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = mat[n] + other[n];
        }
        return res;
    }
	
    Matrix2x2 operator-(const Matrix2x2& mat, const Matrix2x2& other) {
        Matrix2x2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = mat[n] - other[n];
        }
        return res;
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Matrix2x2 operator*(const Matrix2x2& mat, const real_t& factor) {
        Matrix2x2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = mat[n] * factor;
        }
        return res;
    }

    Matrix2x2 operator/(const Matrix2x2& mat, const real_t& factor) {
        Matrix2x2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = mat[n] / factor;
        }
        return res;
    }

    // Free functions
    void identity(Matrix2x2& mat) {
        fill(mat, static_cast<real_t>(0.0));
        for (size_t i = 0; i < 2; i++) {
            mat[i][i] = static_cast<real_t>(1.0);
        }
    }

    void fill(Matrix2x2& mat, real_t value) {
        mat.c_11 = value;
        mat.c_12 = value;
        mat.c_21 = value;
        mat.c_22 = value;
    }

    // 2x2 * 2x2 multiply specialization
    Matrix2x2 mul(const Matrix2x2& m1, const Matrix2x2& m2) {
        //std::cout << "FAST MUL [" << 2 << "," << 2 << "]x[" << 2 << "," << 2 << "]" << std::endl;
        return Matrix2x2(
            m1.c_11 * m2.c_11 + m1.c_12 * m2.c_21, // col 1
            m1.c_21 * m2.c_11 + m1.c_22 * m2.c_21,
    
            m1.c_11 * m2.c_12 + m1.c_12 * m2.c_22, // col 2
            m1.c_21 * m2.c_12 + m1.c_22 * m2.c_22);
    }

    Matrix2x2 transpose(const Matrix2x2& mat) {
        Matrix2x2 res;
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                res[j][i] = mat[i][j]; // opposite indexing to transpose the values
            }
        }
        return res;
    }

    // determinant - 2x2 case
    real_t det(const Matrix2x2& mat) {
        return mat[0][0] * mat[1][1] -
               mat[1][0] * mat[0][1];
    }

    real_t trace(const Matrix2x2& mat) {
        real_t res = static_cast<real_t>(0.0);
        for (size_t n = 0; n < 2; n++) {
            res = res + mat[n][n];
        }
        return res;
    }

    Vector2 diag(const Matrix2x2& mat) {
        Vector2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = mat[n][n];
        }
        return res;
    }

    // minor matrix
    real_t minor(const Matrix2x2& mat, size_t pick_col, size_t pick_row) {
        real_t minor;
        for (size_t i = 0; i < 2 - 1; i++) {
            size_t new_i = (i + 1 > pick_col) ? i + 1 : i;
            for (size_t j = 0; j < 2 - 1; j++) {
                size_t new_j = (j + 1 > pick_row) ? j + 1 : j;
    
                minor = mat[new_i][new_j];
            }
        }
        return minor;
    }

    // inverse
    Matrix2x2 inverse(const Matrix2x2& mat) {
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

        Matrix2x2 adj(mat.c_22, -mat.c_21, 
                     -mat.c_12,  mat.c_11);

        return adj / determinant;
    }
}