#ifndef __LAML_FUNCTIONS_H
#define __LAML_FUNCTIONS_H


#ifdef LAML_STD_INCLUDE
#include <utility>
#include <ostream>
#endif

#include <laml/Data_types.hpp>
#include <laml/Constants.hpp>
#include <math.h>

namespace laml {

    template<typename T>
    T abs(T value) {
        if (value > 0)
            return value;
        else
            return -value;
    }

    template <typename T> 
    int sign(T val) {
        return (T(0) < val) - (val < T(0));
    }

    template<typename T>
    T clamp(T v, T min_val, T max_val) {
        return v > max_val ? max_val : (v < min_val ? min_val : v);
    }

    template<typename T>
    bool epsilon_equal(T value, T target, T eps) {
        return  (abs<T>(value - target) < eps);
    }

    template<typename T>
    T sin(T x) {
        return  ::sin(x);
    }
    template<typename T>
    T sind(T x) {
        return  ::sin(x * laml::constants::deg2rad<T>);
    }
    template<typename T>
    T cos(T x) {
        return  ::cos(x);
    }
    template<typename T>
    T cosd(T x) {
        return  ::cos(x * laml::constants::deg2rad<T>);
    }
    template<typename T>
    T tan(T x) {
        return  ::tan(x);
    }
    template<typename T>
    T tand(T x) {
        return  ::tan(x * laml::constants::deg2rad<T>);
    }


    template<typename T>
    T asin(T x) {
        return  ::asin(x);
    }
    template<typename T>
    T asind(T x) {
        return  ::asin(x) * laml::constants::rad2deg<T>;
    }
    template<typename T>
    T acos(T x) {
        return  ::acos(x);
    }
    template<typename T>
    T acosd(T x) {
        return  ::acos(x) * laml::constants::rad2deg<T>;
    }
    template<typename T>
    T atan(T x) {
        return  ::atan(x);
    }
    template<typename T>
    T atand(T x) {
        return  ::atan(x) * laml::constants::rad2deg<T>;
    }
    template<typename T>
    T atan2(T x, T y) {
        return  ::atan2(x, y);
    }
    template<typename T>
    T atan2d(T x, T y) {
        return  ::atan2(x, y) * laml::constants::rad2deg<T>;
    }

    // safe versions within a tolerance
    template<typename T>
    T asin_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::asin(x);
    }
    template<typename T>
    T asind_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::asin(x) * laml::constants::rad2deg<T>;
    }
    template<typename T>
    T acos_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::acos(x);
    }
    template<typename T>
    T acosd_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::acos(x) * laml::constants::rad2deg<T>;
    }
    template<typename T>
    T atan_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::atan(x);
    }
    template<typename T>
    T atand_safe(T x, T tol) {
        if (x > T( 1.0) && x < (T( 1.0) + tol)) x = T( 1.0);
        if (x < T(-1.0) && x > (T(-1.0) - tol)) x = T(-1.0);
        return  ::atan(x) * laml::constants::rad2deg<T>;
    }
    //template<typename T>
    //T atan2_safe(T x, T y) {
    //    return  ::atan2(x, y);
    //}
    //template<typename T>
    //T atan2d_safe(T x, T y) {
    //    return  ::atan2(x, y) * laml::constants::rad2deg<T>;
    //}

    inline Vec3 rgb8_to_rgba32f(uint8 r, uint8 g, uint8 b) {
        return laml::Vec3(((real32)r) / 255.0f, ((real32)g) / 255.0f, ((real32)b) / 255.0f);
    }

}

#endif // __LAML_FUNCTIONS_H