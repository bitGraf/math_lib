#ifndef __LAML_QUATERNION_H
#define __LAML_QUATERNION_H

#ifdef LAML_STD_INCLUDE
#include <ostream>
#endif

#include <laml/Data_types.hpp>


namespace laml {
    
    struct Quaternion {
        // Default constructor
        Quaternion();
        Quaternion(const Quaternion& other);

        // Construct with float array
        Quaternion(const float* in_data);

        // Initialize with list of components
        Quaternion(real_t _x, real_t _y, real_t _z, real_t _w);

        //// access like an array
        real_t& operator[](size_t idx);
        const real_t& operator[](size_t idx) const;

        const real_t* data() const;
        real_t* data();

        union {
            real_t _data[4];
            struct { real_t x, y, z, w; };
        };
    };

#ifdef LAML_STD_INCLUDE
    // Printing functions
    template<typename real_t>
    std::ostream& operator<<(std::ostream& os, const Quaternion<real_t>& quat) {
        return os << "<" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ">";
    }

    template<typename real_t>
    void print(const Quaternion<real_t>& quat) {
        printf("<%.2f, %.2f, %.2f, %.2f>", quat.x, quat.y, quat.z, quat.w);
    }
    template<typename real_t>
    void print(const Quaternion<real_t>& quat, const char* fmt) {
        printf("<");
        for (size_t n = 0; n < 4; n++) {
            printf(fmt, quat[n]);
            if (n != 3)
            printf(", ");
        }
        printf(">");
    }
#endif

    /* Component-wise operators
     * typename real_t needs to implement: +,-
     * These are all component-wise operations
     * these operations are strange for quaternions, only really use them to lerp/slerp
     * */
    Quaternion operator+(const Quaternion& quat, const Quaternion& other);
    Quaternion operator-(const Quaternion& quat, const Quaternion& other);

    /* Scaling operators
     * typename real_t needs to implement: *,/
     * These are all component-wise operations
     * */
    Quaternion operator*(const Quaternion& quat, const real_t& factor);
    Quaternion operator/(const Quaternion& quat, const real_t& factor);
    Quaternion operator*(const real_t& factor, const Quaternion& quat);
    Quaternion operator/(const real_t& factor, const Quaternion& quat);

    // Free functions
    real_t dot(const Quaternion& q1, const Quaternion& q2);
    real_t length_sq(const Quaternion& quat);
    real_t length(const Quaternion& quat);
    Quaternion normalize(const Quaternion& quat);

    // Weird quaternion functions
    Quaternion inverse(const Quaternion& quat);
    Quaternion mul(const Quaternion& q1, const Quaternion& q2);
    Quaternion lerp(const Quaternion& q1, const Quaternion& q2, real_t factor);
    Quaternion slerp(const Quaternion& q1, const Quaternion& q2, real_t factor);

    // Useful shorthands
    typedef Quaternion Quat;
}

#endif // __LAML_QUATERNION_H