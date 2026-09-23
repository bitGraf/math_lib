#ifndef __LAML_VECTOR4_H
#define __LAML_VECTOR4_H


#ifdef LAML_STD_INCLUDE
#include <utility>
#include <ostream>
#endif

#include <laml/base.h>

namespace laml {

    struct Vector4 {
		LAML_DELETE_CTRS(Vector4); // Explicitly delete constructors/move/copy oeprators

        // Default (zero) constructor
        Vector4();

        // Component-wise constructor
        Vector4(real_t x_, real_t y_, real_t z_, real_t w_);

        // Construct with float array
        Vector4(const float* in_data);

        //// access like an array
        real_t& operator[](size_t idx);
        const real_t& operator[](size_t idx) const;

        const real_t* data() const;
        real_t* data();

        real_t x, y, z, w;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector4 operator+(const Vector4& vec, const Vector4& other);
    Vector4 operator-(const Vector4& vec, const Vector4& other);
    Vector4 operator*(const Vector4& vec, const Vector4& other);
    Vector4 operator/(const Vector4& vec, const Vector4& other);

    /*
     * Unary operators
     */
    Vector4 operator-(const Vector4& vec);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector4 operator*(const Vector4& vec, const real_t& factor);
    Vector4 operator/(const Vector4& vec, const real_t& factor);
    Vector4 operator*(const real_t& factor, const Vector4& vec);

#ifdef LAML_STD_INCLUDE
    // Printing functions
    template<typename T, size_t size>
    std::ostream& operator<<(std::ostream& os, const Vector<T, size>& vec) {
        os << "[";
        for (size_t n = 0; n < size; n++) {
            os << vec[n];
            if (n != (size - 1))
                os << ", ";
        }
        os << "]";
        return os;
    }

    template<typename T, size_t size>
    void print(const Vector<T, size>& vec) {
        printf("[");
        for (size_t n = 0; n < size; n++) {
            printf("%.2f", vec[n]);
            if (n != (size - 1))
                printf(", ");
        }
        printf("]");
    }
    template<typename T, size_t size>
    void print(const Vector<T, size>& vec, const char* fmt) {
        printf("[");
        for (size_t n = 0; n < size; n++) {
            printf(fmt, vec[n]);
            if (n != (size - 1))
                printf(", ");
        }
        printf("]");
    }
#endif

    // Free functions
    real_t dot(const Vector4& v1, const Vector4& v2);
    real_t length_sq(const Vector4& v);
    real_t length(const Vector4& v);
    Vector4 normalize(const Vector4& v);
    real_t min(const Vector4& v);
    real_t max(const Vector4& v);
    Vector4 abs(const Vector4& v);
    Vector4 clamp(const Vector4& v, real_t min_val, real_t max_val);
    Vector4 lerp(const Vector4& v1, const Vector4& v2, real_t factor);

    // Useful shorthands
    typedef Vector4 Vec4;

}

#endif // __LAML_VECTOR3_H
