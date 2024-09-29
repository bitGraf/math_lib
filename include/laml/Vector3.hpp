#ifndef __LAML_VECTOR3_H
#define __LAML_VECTOR3_H


#ifdef LAML_STD_INCLUDE
#include <utility>
#include <ostream>
#endif

#include <laml/Data_types.hpp>

namespace laml {

    struct Vector3 {
        // Default (zero) constructor
        Vector3();

        // Component-wise constructor
        Vector3(real_t x_, real_t y_, real_t z_);

        // Construct with float array
        Vector3(const float* in_data);

        //// access like an array
        real_t& operator[](size_t idx);
        const real_t& operator[](size_t idx) const;

        const real_t* data() const;
        real_t* data();

        real_t x, y, z;
    };

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector3 operator+(const Vector3& vec, const Vector3& other);
    Vector3 operator-(const Vector3& vec, const Vector3& other);
    Vector3 operator*(const Vector3& vec, const Vector3& other);
    Vector3 operator/(const Vector3& vec, const Vector3& other);

    /*
     * Unary operators
     */
    Vector3 operator-(const Vector3& vec);

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector3 operator*(const Vector3& vec, const real_t& factor);
    Vector3 operator/(const Vector3& vec, const real_t& factor);
    Vector3 operator*(const real_t& factor, const Vector3& vec);

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
    real_t dot(const Vector3& v1, const Vector3& v2);
    Vector3 cross(const Vector3& v1, const Vector3& v2);
    real_t length_sq(const Vector3& v);
    real_t length(const Vector3& v);
    Vector3 normalize(const Vector3& v);
    real_t min(const Vector3& v);
    real_t max(const Vector3& v);
    Vector3 abs(const Vector3& v);
    Vector3 clamp(const Vector3& v, real_t min_val, real_t max_val);
    Vector3 lerp(const Vector3& v1, const Vector3& v2, real_t factor);

    // Useful shorthands
    typedef Vector3 Vec3;

}

#endif // __LAML_VECTOR3_H