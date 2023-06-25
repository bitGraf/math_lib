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

    template<typename T>
    T clamp(T& v, T min_val, T max_val) {
        return v > max_val ? max_val : (v < min_val ? min_val : v);
    }

    template<typename T>
    bool epsilon_equal(T value, double target, double eps) {
        return  (abs<T>(static_cast<double>(value) - target) < eps);
    }

    template<typename T>
    T sind(T x) {
        return  ::sin(x * laml::constants::deg2rad<T>);
    }

    template<typename T>
    T cosd(T x) {
        return  ::cos(x * laml::constants::deg2rad<T>);
    }

}

#endif // __LAML_FUNCTIONS_H