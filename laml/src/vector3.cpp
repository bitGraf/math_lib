#include <laml/vector3.h>

#include <laml/constants.h>
#include <math.h>

namespace laml {

    Vector3::Vector3() 
     : x(0.0), y(0.0), z(0.0)
    {}

    Vector3::Vector3(real_t x_, real_t y_, real_t z_) 
     : x(x_), y(y_), z(z_)
    {}

    Vector3::Vector3(const float* in_data)
    : x(in_data[0]), y(in_data[1]), z(in_data[2])
    {}

    //// access like an array
    real_t& Vector3::operator[](size_t idx) {
        return (&x)[idx];
    }
    const real_t& Vector3::operator[](size_t idx) const {
        return (&x)[idx];
    }


    const real_t* Vector3::data() const { return (&x); }
    real_t* Vector3::data() { return (&x); }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector3 operator+(const Vector3& vec, const Vector3& other) {
        return { vec.x+other.x, vec.y+other.y, vec.z+other.z };
    }

    Vector3 operator-(const Vector3& vec, const Vector3& other) {
        return { vec.x-other.x, vec.y-other.y, vec.z-other.z };
    }

    Vector3 operator*(const Vector3& vec, const Vector3& other) {
        return { vec.x*other.x, vec.y*other.y, vec.z*other.z };
    }

    Vector3 operator/(const Vector3& vec, const Vector3& other) {
        return { vec.x/other.x, vec.y/other.y, vec.z/other.z };
    }

    /*
     * Unary operators
     */
    Vector3 operator-(const Vector3& vec) {
        return { -vec.x, -vec.y, -vec.z };
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector3 operator*(const Vector3& vec, const real_t& factor) {
        return { vec.x*factor, vec.y*factor, vec.z*factor };
    }

    Vector3 operator/(const Vector3& vec, const real_t& factor) {
        return { vec.x/factor, vec.y/factor, vec.z/factor };
    }

    Vector3 operator*(const real_t& factor, const Vector3& vec) {
        return { factor*vec.x, factor*vec.y, factor*vec.z };
    }

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
    real_t dot(const Vector3& v1, const Vector3& v2) {
        return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
    }

    Vector3 cross(const Vector3& v1, const Vector3& v2) {
        return {
        	v1.y * v2.z - v1.z * v2.y,
        	v1.z * v2.x - v1.x * v2.z,
        	v1.x * v2.y - v1.y * v2.x
		};
    }

    real_t length_sq(const Vector3& v) {
        return (v.x*v.x) + (v.y*v.y) + (v.z*v.z);
    }

    real_t length(const Vector3& v) {
        return static_cast<real_t>(sqrt(length_sq(v)));
    }

    Vector3 normalize(const Vector3& v) {
        real_t mag = length(v);
        if (std::abs(mag) < laml::eps) {
            return {};
        }
        return { v.x/mag, v.y/mag, v.z/mag };
    }

    real_t min(const Vector3& v) {
        real_t min_val = v[0];
        for (size_t n = 1; n < 3; n++) {
            if (v[n] < min_val) min_val = v[n];
        }
        return min_val;
    }

    real_t max(const Vector3& v) {
        real_t max_val = v[0];
        for (size_t n = 1; n < 3; n++) {
            if (v[n] > max_val) max_val = v[n];
        }
        return max_val;
    }

    Vector3 abs(const Vector3& v) {
        return { 
			std::abs(v.x), 
			std::abs(v.y),
			std::abs(v.z)
		};
    }

    Vector3 clamp(const Vector3& v, real_t min_val, real_t max_val) {
        return {
			v.x > max_val ? max_val : (v.x < min_val ? min_val : v.x),
			v.y > max_val ? max_val : (v.y < min_val ? min_val : v.y),
			v.z > max_val ? max_val : (v.z < min_val ? min_val : v.z)
		};
    }

    Vector3 lerp(const Vector3& v1, const Vector3& v2, real_t factor) {
		return {
			v2.x*factor + v1.x*(static_cast<real_t>(1.0) - factor),
			v2.x*factor + v1.x*(static_cast<real_t>(1.0) - factor),
			v2.z*factor + v1.z*(static_cast<real_t>(1.0) - factor)
		};
    }
}
