#ifndef __LAML_VECTOR2_H
#define __LAML_VECTOR2_H

#ifdef LAML_STD_INCLUDE
#include <utility>
#include <ostream>
#endif

#include <laml/base.h>

namespace laml {

    struct Vector2 {
		LAML_DELETE_CTRS(Vector2); // Explicitly delete constructors/move/copy oeprators

        // Default (zero) constructor
        Vector2();

        // Component-wise constructor
        Vector2(real_t x_, real_t y_);

        // Construct with float array
        Vector2(const real_t* in_data);

        //// access like an array
        real_t& operator[](size_t idx);
        const real_t& operator[](size_t idx) const;

        const real_t* data() const;
        real_t* data();

        real_t x, y;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector2 operator+(const Vector2& vec, const Vector2& other);
    Vector2 operator-(const Vector2& vec, const Vector2& other);
    Vector2 operator*(const Vector2& vec, const Vector2& other);
    Vector2 operator/(const Vector2& vec, const Vector2& other);

    /*
     * Unary operators
     */
    Vector2 operator-(const Vector2& vec);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector2 operator*(const Vector2& vec, const real_t& factor);
    Vector2 operator/(const Vector2& vec, const real_t& factor);
    Vector2 operator*(const real_t& factor, const Vector2& vec);

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
    real_t dot(const Vector2& v1, const Vector2& v2);
    real_t length_sq(const Vector2& v);
    real_t length(const Vector2& v);
    Vector2 normalize(const Vector2& v);
    real_t min(const Vector2& v);
    real_t max(const Vector2& v);
    Vector2 abs(const Vector2& v);
    Vector2 clamp(const Vector2& v, real_t min_val, real_t max_val);
    Vector2 lerp(const Vector2& v1, const Vector2& v2, real_t factor);

    // Useful shorthands
    typedef Vector2 vec2;

}

#endif // __LAML_VECTOR2_H
