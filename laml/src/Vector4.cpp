#include <laml/Vector4.hpp>

#include <laml/Constants.hpp>
#include <laml/Functions.hpp>
#include <math.h>

namespace laml {

    Vector4::Vector4() 
     : x(0.0), y(0.0), z(0.0), w(0.0)
    {}

    Vector4::Vector4(real_t x_, real_t y_, real_t z_, real_t w_) 
     : x(x_), y(y_), z(z_), w(w_)
    {}

    Vector4::Vector4(const float* in_data)
    : x(in_data[0]), y(in_data[1]), z(in_data[2]), w(in_data[3])
    {}

    //// access like an array
    real_t& Vector4::operator[](size_t idx) {
        return (&x)[idx];
    }
    const real_t& Vector4::operator[](size_t idx) const {
        return (&x)[idx];
    }


    const real_t* Vector4::data() const { return (&x); }
    real_t* Vector4::data() { return (&x); }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector4 operator+(const Vector4& vec, const Vector4& other) {
        return Vector4(vec.x+other.x, vec.y+other.y, vec.z+other.z, vec.w+other.w);
    }

    Vector4 operator-(const Vector4& vec, const Vector4& other) {
        return Vector4(vec.x-other.x, vec.y-other.y, vec.z-other.z, vec.w-other.w);
    }

    Vector4 operator*(const Vector4& vec, const Vector4& other) {
        return Vector4(vec.x*other.x, vec.y*other.y, vec.z*other.z, vec.w*other.w);
    }

    Vector4 operator/(const Vector4& vec, const Vector4& other) {
        return Vector4(vec.x/other.x, vec.y/other.y, vec.z/other.z, vec.w/other.w);
    }

    /*
     * Unary operators
     */
    Vector4 operator-(const Vector4& vec) {
        return Vector4(-vec.x, -vec.y, -vec.z, -vec.w);
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector4 operator*(const Vector4& vec, const real_t& factor) {
        return Vector4(vec.x*factor, vec.y*factor, vec.z*factor, vec.w*factor);
    }

    Vector4 operator/(const Vector4& vec, const real_t& factor) {
        return Vector4(vec.x/factor, vec.y/factor, vec.z/factor, vec.w/factor);
    }

    Vector4 operator*(const real_t& factor, const Vector4& vec) {
        return Vector4(factor*vec.x, factor*vec.y, factor*vec.z, factor*vec.w);
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
    real_t dot(const Vector4& v1, const Vector4& v2) {
        return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z) + (v1.w*v2.w);
    }

    real_t length_sq(const Vector4& v) {
        return (v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w);
    }

    real_t length(const Vector4& v) {
        return static_cast<real_t>(sqrt(length_sq(v)));
    }

    Vector4 normalize(const Vector4& v) {
        real_t mag = length(v);
        if (laml::abs(mag) < laml::eps) {
            return Vector4();
        }
        return (v / mag);
    }

    real_t min(const Vector4& v) {
        real_t min_val = v[0];
        for (size_t n = 1; n < 4; n++) {
            if (v[n] < min_val) min_val = v[n];
        }
        return min_val;
    }

    real_t max(const Vector4& v) {
        real_t max_val = v[0];
        for (size_t n = 1; n < 4; n++) {
            if (v[n] > max_val) max_val = v[n];
        }
        return max_val;
    }

    Vector4 abs(const Vector4& v) {
        Vector4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = v[n] > static_cast<real_t>(0.0) ? v[n] : -v[n];
        }
        return res;
    }

    Vector4 clamp(const Vector4& v, real_t min_val, real_t max_val) {
        Vector4 res;
        for (size_t n = 0; n < 4; n++) {
            res[n] = v[n] > max_val ? max_val : (v[n] < min_val ? min_val : v[n]);
        }
        return res;
    }

    Vector4 lerp(const Vector4& v1, const Vector4& v2, real_t factor) {
        return v2 * factor + v1 * (static_cast<real_t>(1.0) - factor);
    }
}
