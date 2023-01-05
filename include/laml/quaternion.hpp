#ifndef __LAML_QUATERNION_H
#define __LAML_QUATERNION_H

#include <ostream>

namespace rh {
    namespace laml {
    
        template<typename T>
        struct Quaternion {

            typedef T Type;

            union {
                T _data[4];
                struct { T x, y, z, w; };
            };

            constexpr inline size_t num_elements() const { return 4; }

            // Default constructor
            constexpr Quaternion() : _data{ 0, 0, 0, 1.0 } {}
            constexpr Quaternion(const Quaternion<T>& other) : _data{ other.x, other.y, other.z, other.w } {}

            // Construct with float array
            Quaternion(const float* in_data) : _data{static_cast<T>(in_data[0]), static_cast<T>(in_data[1]), static_cast<T>(in_data[2]), static_cast<T>(in_data[3])} {}

            // Initialize with list of components
            constexpr Quaternion(T _x, T _y, T _z, T _w) noexcept : _data{ _x, _y, _z, _w } {}

            //// access like an array
            T& operator[](size_t idx) {
                return _data[idx];
            }
            const T& operator[](size_t idx) const {
                return _data[idx];
            }

            const T* data() const { return _data; }
            T* data() { return _data; }
        };

        // Printing functions
        template<typename T>
        std::ostream& operator<<(std::ostream& os, const Quaternion<T>& quat) {
            return os << "<" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ">";
        }

        template<typename T>
        void print(const Quaternion<T>& quat) {
            printf("<%.2f, %.2f, %.2f, %.2f>", quat.x, quat.y, quat.z, quat.w);
        }
        template<typename T>
        void print(const Quaternion<T>& quat, const char* fmt) {
            printf("<");
            for (size_t n = 0; n < 4; n++) {
                printf(fmt, quat[n]);
                if (n != 3)
                    printf(", ");
            }
            printf(">");
        }

        /* Component-wise operators
	 * typename T needs to implement: +,-
	 * These are all component-wise operations
	 * these operations are strange for quaternions, only really use them to lerp/slerp
	 * */
        template<typename T>
        Quaternion<T> operator+(const Quaternion<T>& quat, const Quaternion<T>& other) {
            return Quaternion<T>(
                quat.x + other.x,
                quat.y + other.y,
                quat.z + other.z,
                quat.w + other.w);
        }

        template<typename T>
        Quaternion<T> operator-(const Quaternion<T>& vec, const Quaternion<T>& other) {
            return Quaternion<T>(
                quat.x - other.x,
                quat.y - other.y,
                quat.z - other.z,
                quat.w - other.w);
        }

        /* Scaling operators
	 * typename T needs to implement: *,/
	 * These are all component-wise operations
	 * */
        template<typename T>
        Quaternion<T> operator*(const Quaternion<T>& quat, const T& factor) {
            Quaternion<T> res;
            for (size_t n = 0; n < 4; n++) {
                res[n] = quat[n] * factor;
            }
            return res;
        }

        template<typename T>
        Quaternion<T> operator/(const Quaternion<T>& quat, const T& factor) {
            Quaternion<T> res;
            for (size_t n = 0; n < 4; n++) {
                res[n] = quat[n] / factor;
            }
            return res;
        }
        template<typename T>
        Quaternion<T> operator*(const T& factor, const Quaternion<T>& quat) {
            Quaternion<T> res;
            for (size_t n = 0; n < 4; n++) {
                res[n] = quat[n] * factor;
            }
            return res;
        }

        template<typename T>
        Quaternion<T> operator/(const T& factor, const Quaternion<T>& quat) {
            Quaternion<T> res;
            for (size_t n = 0; n < 4; n++) {
                res[n] = quat[n] / factor;
            }
            return res;
        }

        // Free functions
        template<typename T>
        T dot(const Quaternion<T>& q1, const Quaternion<T>& q2) {
            return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
        }

        template<typename T>
        T length_sq(const Quaternion<T>& quat) {
            return (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) + (quat.w * quat.w);
        }

        template<typename T>
        T length(const Quaternion<T>& quat) {
            return static_cast<T>(sqrt(length_sq(quat)));
        }

        template<typename T>
        Quaternion<T> normalize(const Quaternion<T>& quat) {
            T mag = length(quat);
            return (quat / mag);
        }

        // Weird quaternion functions
        template<typename T>
        Quaternion<T> inverse(const Quaternion<T>& quat) {
            return Quaternion<T>(quat.x, quat.w, quat.z, quat.w);
        }

        template<typename T>
        Quaternion<T> mul(const Quaternion<T>& q1, const Quaternion<T>& q2) {
            // Hamilton operator

            // really bad, but easy implementation that doe ssome vector math using Vector<T,3>s 
            Vector<T, 3> v1(q1.x, q1.y, q1.z);
            Vector<T, 3> v2(q2.x, q2.y, q2.z);
            Vector<T, 3> v = v1*q2.w + v2*q1.w + laml::cross(v1, v2);

            return Quaternion<T>(v.x, v.y, v.z, q1.w * q2.w - laml::dot(v1, v2));
        }

        template<typename T>
        Quaternion<T> lerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T factor) {
            return q2 * factor + q1 * (static_cast<T>(1.0) - factor);
        }

        template<typename T>
        Quaternion<T> slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T factor) {
            const T eps = 1e-4;

            T cos_omega = dot(q1,q2);
            if (fabs(1.0 - cos_omega) < eps) {
                return q1;
            }
            T omega = acos(std::clamp(cos_omega, -1.0f, 1.0f));
            T s_omega_inv = 1.0 / sin(omega);
            Quaternion<T> q = (static_cast<float>(sin((1.0 - factor) * omega) * s_omega_inv) * q1) + (static_cast<float>(sin(factor * omega) * s_omega_inv) * q2);
            return q;
        }


        // Useful shorthands
        typedef Quaternion<float> Quat;
        typedef Quaternion<double> Quat_highp;
    }
}

#endif // __LAML_QUATERNION_H