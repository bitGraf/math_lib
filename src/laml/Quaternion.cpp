#include <laml/Quaternion.hpp>

#include <laml/Vector3.hpp>
#include <laml/Functions.hpp>

namespace laml {

    // Default constructor
    Quaternion::Quaternion() : _data{ 0, 0, 0, 1.0 } {}
    Quaternion::Quaternion(const Quaternion& other) : _data{ other.x, other.y, other.z, other.w } {}

    // Construct with float array
    Quaternion::Quaternion(const float* in_data) : _data{static_cast<real_t>(in_data[0]), static_cast<real_t>(in_data[1]), static_cast<real_t>(in_data[2]), static_cast<real_t>(in_data[3])} {}

    // Initialize with list of components
    Quaternion::Quaternion(real_t _x, real_t _y, real_t _z, real_t _w) : _data{ _x, _y, _z, _w } {}

    //// access like an array
    real_t& Quaternion::operator[](size_t idx) {
        return _data[idx];
    }
    const real_t& Quaternion::operator[](size_t idx) const {
        return _data[idx];
    }

    const real_t* Quaternion::data() const { return _data; }
    real_t* Quaternion::data() { return _data; }

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
    Quaternion operator+(const Quaternion& quat, const Quaternion& other) {
        return Quaternion(
            quat.x + other.x,
            quat.y + other.y,
            quat.z + other.z,
            quat.w + other.w);
    }

    Quaternion operator-(const Quaternion& quat, const Quaternion& other) {
        return Quaternion(
            quat.x - other.x,
            quat.y - other.y,
            quat.z - other.z,
            quat.w - other.w);
    }

    /* Scaling operators
     * typename real_t needs to implement: *,/
     * These are all component-wise operations
     * */
    Quaternion operator*(const Quaternion& quat, const real_t& factor) {
        Quaternion res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = quat[n] * factor;
        }
        return res;
    }

    Quaternion operator/(const Quaternion& quat, const real_t& factor) {
        Quaternion res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = quat[n] / factor;
        }
        return res;
    }
    Quaternion operator*(const real_t& factor, const Quaternion& quat) {
        Quaternion res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = quat[n] * factor;
        }
        return res;
    }

    Quaternion operator/(const real_t& factor, const Quaternion& quat) {
        Quaternion res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = quat[n] / factor;
        }
        return res;
    }

    // Free functions
    real_t dot(const Quaternion& q1, const Quaternion& q2) {
        return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
    }

    real_t length_sq(const Quaternion& quat) {
        return (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) + (quat.w * quat.w);
    }

    real_t length(const Quaternion& quat) {
        return static_cast<real_t>(sqrt(length_sq(quat)));
    }

    Quaternion normalize(const Quaternion& quat) {
        real_t mag = length(quat);
        return (quat / mag);
    }

    // Weird quaternion functions
    Quaternion inverse(const Quaternion& quat) {
        return Quaternion(quat.x, quat.w, quat.z, quat.w);
    }

    Quaternion mul(const Quaternion& q1, const Quaternion& q2) {
        // Hamilton operator

        // really bad, but easy implementation that doe ssome vector math using Vector3s 
        Vector3 v1(q1.x, q1.y, q1.z);
        Vector3 v2(q2.x, q2.y, q2.z);
        Vector3 v = v1*q2.w + v2*q1.w + laml::cross(v1, v2);

        return Quaternion(v.x, v.y, v.z, q1.w * q2.w - laml::dot(v1, v2));
    }

    Quaternion lerp(const Quaternion& q1, const Quaternion& q2, real_t factor) {
        return q2 * factor + q1 * (static_cast<real_t>(1.0) - factor);
    }

    Quaternion slerp(const Quaternion& q1, const Quaternion& q2, real_t factor) {
        const real_t eps = 1e-4;

        real_t cos_omega = dot(q1,q2);
        if (fabs(1.0 - cos_omega) < eps) {
            return q1;
        }
        real_t omega = acos(laml::clamp(cos_omega, -1.0f, 1.0f));
        real_t s_omega_inv = 1.0 / sin(omega);
        Quaternion q = (static_cast<float>(sin((1.0 - factor) * omega) * s_omega_inv) * q1) + (static_cast<float>(sin(factor * omega) * s_omega_inv) * q2);
        return q;
    }

    // Useful shorthands
    typedef Quaternion Quat;
}