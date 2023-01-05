#ifndef __LAML_VECTOR_H
#define __LAML_VECTOR_H

#include <utility>
#include <ostream>

#include <laml/data_types.hpp>

namespace rh {
    namespace laml {

        template<typename T, size_t size>
        struct Vector {
            static_assert(size > 0, "Vector cannot be zero-size");

            typedef T Type;
		
            constexpr inline size_t num_elements() const { return size; }

            // Default constructor
            constexpr Vector() : _data { 0 } {}

            // Construct with float array
            Vector(const float* in_data) {
                for (size_t n = 0; n < size; n++) {
                    _data[n] = static_cast<T>(in_data[n]);
                }
            }

            // Initialize with list of components
            template<class ... U, class V = typename std::enable_if<sizeof...(U) + 1 == size, T>::type>
            constexpr Vector(T first, U... next) noexcept : _data { first, next... } {}

            // Initialize with single value for all
            template<class V = typename std::enable_if<size != 1, T>::type>
            Vector(T value) {
                for (size_t n = 0; n < size; n++) {
                    _data[n] = value;
                }
            }

            //// access like an array
            T& operator[](size_t idx) {
                return _data[idx];
            }
            const T& operator[](size_t idx) const {
                return _data[idx];
            }

            const T* data() const { return _data; }
            T* data() { return _data; }

            T _data[size];
        };

        /* Component-wise operators
	 * typename T needs to implement: +,-,*,/
	 * These are all component-wise operations
	 * */
        template<typename T, size_t size>
        Vector<T, size> operator+(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] + other[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator-(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] - other[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator*(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] * other[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator/(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] / other[n];
            }
            return res;
        }

        /*
	* Unary operators
	*/
        template<typename T, size_t size>
        Vector<T, size> operator-(const Vector<T, size>& vec) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = -vec[n];
            }
            return res;
        }

        /* Scaling operators
	 * typename T needs to implement: *,/
	 * These are all component-wise operations
	 * */
        template<typename T, size_t size>
        Vector<T, size> operator*(const Vector<T, size>& vec, const T& factor) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] * factor;
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator/(const Vector<T, size>& vec, const T& factor) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] / factor;
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator*(const T& factor, const Vector<T, size>& vec) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] * factor;
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> operator/(const T& factor, const Vector<T, size>& vec) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] / factor;
            }
            return res;
        }

        /* Component-wise comparisons
	 * typename T needs to implement: <,<=,>,>=
	 * These are all component-wise operations that return arrays of booleans
	 * */
        template<typename T, size_t size>
        Vector<bool, size> operator>(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<bool, size> res; // fill with falses?
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] > other[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<bool, size> operator<(const Vector<T, size>& vec, const Vector<T, size>& other) {
            Vector<bool, size> res; // fill with falses?
            for (size_t n = 0; n < size; n++) {
                res[n] = vec[n] < other[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<bool, size> operator>=(const Vector<T, size>& vec, const Vector<T, size>& other) {
                                     Vector<bool, size> res; // fill with falses?
                                     for (size_t n = 0; n < size; n++) {
                                         res[n] = vec[n] >= other[n];
                                     }
                                     return res;
        }

        template<typename T, size_t size>
        Vector<bool, size> operator<=(const Vector<T, size>& vec, const Vector<T, size>& other) {
                                     Vector<bool, size> res; // fill with falses?
                                     for (size_t n = 0; n < size; n++) {
                                         res[n] = vec[n] <= other[n];
                                     }
                                     return res;
        }

        // TODO: This should return a Vector<bool,size> to be consistent, but makes more sense otherwise
        //template<typename T, size_t size>
        //Vector<bool, size> operator==(const Vector<T, size>& vec, const Vector<T, size>& other) {
        //	Vector<bool, size> res; // fill with falses?
        //	for (size_t n = 0; n < size; n++) {
        //		res[n] = (vec[n] == other[n]);
        //	}
        //	return res;
        //}
        template<typename T, size_t size>
        bool operator==(const Vector<T, size>& vec, const Vector<T, size>& other) {
                       for (size_t n = 0; n < size; n++) {
                       if (vec[n] != other[n])
                       return false;
                       }
                       return true;
        }
        template<typename T, size_t size>
        bool operator!=(const Vector<T, size>& vec, const Vector<T, size>& other) {
                       for (size_t n = 0; n < size; n++) {
                       if (vec[n] == other[n])
                       return false;
                       }
                       return true;
        }

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

        // Free functions
        template<typename T, size_t size>
        T dot(const Vector<T, size>& v1, const Vector<T, size>& v2) {
            T res = 0;
            for (size_t n = 0; n < size; n++) {
                res = res + (v1[n] * v2[n]);
            }
            return res;
        }

        template<typename T>
        Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) {
            Vector<T, 3> res;
            res[0] = v1[1] * v2[2] - v1[2] * v2[1];
            res[1] = v1[2] * v2[0] - v1[0] * v2[2];
            res[2] = v1[0] * v2[1] - v1[1] * v2[0];
            return res;
        }

        template<typename T, size_t size>
        T length_sq(const Vector<T, size>& v) {
            T res = 0;
            for (size_t n = 0; n < size; n++) {
                res = res + (v[n] * v[n]);
            }
            return res;
        }

        template<typename T, size_t size>
        T length(const Vector<T, size>& v) {
            return static_cast<T>(sqrt(length_sq(v)));
        }

        template<typename T, size_t size>
        Vector<T, size> normalize(const Vector<T, size>& v) {
            T mag = length(v);
            return (v / mag);
        }

        template<typename T, size_t size>
        T min(const Vector<T, size>& v) {
            T min_val = v[0];
            for (size_t n = 1; n < size; n++) {
                if (v[n] < min_val) min_val = v[n];
            }
            return min_val;
        }

        template<typename T, size_t size>
        T max(const Vector<T, size>& v) {
            T max_val = v[0];
            for (size_t n = 1; n < size; n++) {
                if (v[n] > max_val) max_val = v[n];
            }
            return max_val;
        }

        template<typename T, size_t size>
        Vector<T, size> abs(const Vector<T, size>& v) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = v[n] > static_cast<T>(0.0) ? v[n] : -v[n];
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> clamp(const Vector<T, size>& v, T min_val, T max_val) {
            Vector<T, size> res;
            for (size_t n = 0; n < size; n++) {
                res[n] = v[n] > max_val ? max_val : (v[n] < min_val ? min_val : v[n]);
            }
            return res;
        }

        template<typename T, size_t size>
        Vector<T, size> lerp(const Vector<T, size>& v1, const Vector<T, size>& v2, T factor) {
            return v2 * factor + v1 * (static_cast<T>(1.0) - factor);
        }

        template<size_t size>
        bool any(const Vector<bool, size>& v) {
            for (size_t n = 0; n < size; n++) {
                if (v[n]) return true;
            }
            return false;
        }
        template<size_t size>
        bool all(const Vector<bool, size>& v) {
            for (size_t n = 0; n < size; n++) {
                if (!v[n]) return false;
            }
            return true;
        }

        // Specializations
#if 1
        template<typename T> struct Vector<T, 2> {
            constexpr Vector() : _data { 0, 0 } {}
            constexpr Vector(T _x, T _y) : _data { _x, _y } {}
            constexpr Vector(T _x) : _data { _x, _x } {}
            Vector(const float* in_data) : _data { in_data[0], in_data[1] } {}

            union {
                T _data[2];
                struct { T x, y; };
            };

            T& operator[](size_t idx) {
                return _data[idx];
            }
            const T& operator[](size_t idx) const {
                return _data[idx];
            }
        };

        template<typename T> struct Vector<T, 3> {
            constexpr Vector() : _data { 0, 0, 0 } {}
            constexpr Vector(T _x, T _y, T _z) : _data { _x, _y, _z } {}
            constexpr Vector(T _x) : _data { _x, _x, _x } {}
            Vector(const float* in_data) : _data { in_data[0], in_data[1], in_data[2] } {}

            union {
                T _data[3];
                struct { T x, y, z; };
            };

            T& operator[](size_t idx) {
                return _data[idx];
            }
            const T& operator[](size_t idx) const {
                return _data[idx];
            }
        };

        template<typename T> struct Vector<T, 4> {
            constexpr Vector() : _data { 0, 0, 0, 0 } {}
            constexpr Vector(T _x, T _y, T _z, T _w) : _data { _x, _y, _z, _w } {}
            constexpr Vector(T _x) : _data { _x, _x, _x, _x } {}
            Vector(const float* in_data) : _data { in_data[0], in_data[1], in_data[2], in_data[3] } {}
            constexpr Vector(const Vector<T, 3>& v, T w) : _data { v.x, v.y, v.z, w } {}

            union {
                T _data[4];
                struct { T x, y, z, w; };
            };

            T& operator[](size_t idx) {
                return _data[idx];
            }
            const T& operator[](size_t idx) const {
                return _data[idx];
            }
        };
#endif


        // Useful shorthands
        typedef float Scalar;
        typedef Vector<float, 2> Vec2;
        typedef Vector<float, 3> Vec3;
        typedef Vector<float, 4> Vec4;

        typedef double Scalar_highp;
        typedef Vector<double, 2> Vec2_highp;
        typedef Vector<double, 3> Vec3_highp;
        typedef Vector<double, 4> Vec4_highp;

    }

}

#endif // __LAML_VECTOR_H