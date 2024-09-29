#include <laml/Vector.hpp>

#include <laml/Constants.hpp>
#include <laml/Functions.hpp>
#include <math.h>

#include <stdexcept>

namespace laml {

    Vector2::Vector2() 
     : x(0.0), y(0.0)
    {}

    Vector2::Vector2(real_t x_, real_t y_) 
     : x(x_), y(y_)
    {}

    Vector2::Vector2(const real_t* in_data)
    : x(in_data[0]), y(in_data[1])
    {}

    //// access like an array
    real_t& Vector2::operator[](size_t idx) {
        #ifndef NDEBUG
            if (idx >= 2) throw std::out_of_range("Index out of range!");
        #endif

        return (&x)[idx];
    }
    const real_t& Vector2::operator[](size_t idx) const {
        #ifndef NDEBUG
            if (idx >= 2) throw std::out_of_range("Index out of range!");
        #endif

        return (&x)[idx];
    }


    const real_t* Vector2::data() const { return (&x); }
    real_t* Vector2::data() { return (&x); }

    /* Component-wise operators
     * typename T needs to implement: +,-,*,/
     * These are all component-wise operations
     * */
    Vector2 operator+(const Vector2& vec, const Vector2& other) {
        return Vector2(vec.x+other.x, vec.y+other.y);
    }

    Vector2 operator-(const Vector2& vec, const Vector2& other) {
        return Vector2(vec.x-other.x, vec.y-other.y);
    }

    Vector2 operator*(const Vector2& vec, const Vector2& other) {
        return Vector2(vec.x*other.x, vec.y*other.y);
    }

    Vector2 operator/(const Vector2& vec, const Vector2& other) {
        return Vector2(vec.x/other.x, vec.y/other.y);
    }

    /*
     * Unary operators
     */
    Vector2 operator-(const Vector2& vec) {
        return Vector2(-vec.x, -vec.y);
    }

    /* Scaling operators
     * typename T needs to implement: *,/
     * These are all component-wise operations
     * */
    Vector2 operator*(const Vector2& vec, const real_t& factor) {
        return Vector2(vec.x*factor, vec.y*factor);
    }

    Vector2 operator/(const Vector2& vec, const real_t& factor) {
        return Vector2(vec.x/factor, vec.y/factor);
    }

    Vector2 operator*(const real_t& factor, const Vector2& vec) {
        return Vector2(factor*vec.x, factor*vec.y);
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
    real_t dot(const Vector2& v1, const Vector2& v2) {
        return (v1.x*v2.x) + (v1.y*v2.y);
    }

    real_t length_sq(const Vector2& v) {
        return (v.x*v.x) + (v.y*v.y);
    }

    real_t length(const Vector2& v) {
        return static_cast<real_t>(sqrt(length_sq(v)));
    }

    Vector2 normalize(const Vector2& v) {
        real_t mag = length(v);
        if (laml::abs(mag) < laml::eps) {
            return Vector2();
        }
        return (v / mag);
    }

    real_t min(const Vector2& v) {
        real_t min_val = v[0];
        for (size_t n = 1; n < 2; n++) {
            if (v[n] < min_val) min_val = v[n];
        }
        return min_val;
    }

    real_t max(const Vector2& v) {
        real_t max_val = v[0];
        for (size_t n = 1; n < 2; n++) {
            if (v[n] > max_val) max_val = v[n];
        }
        return max_val;
    }

    Vector2 abs(const Vector2& v) {
        Vector2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = v[n] > static_cast<real_t>(0.0) ? v[n] : -v[n];
        }
        return res;
    }

    Vector2 clamp(const Vector2& v, real_t min_val, real_t max_val) {
        Vector2 res;
        for (size_t n = 0; n < 2; n++) {
            res[n] = v[n] > max_val ? max_val : (v[n] < min_val ? min_val : v[n]);
        }
        return res;
    }

    Vector2 lerp(const Vector2& v1, const Vector2& v2, real_t factor) {
        return v2 * factor + v1 * (static_cast<real_t>(1.0) - factor);
    }
}
