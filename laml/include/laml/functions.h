#ifndef __LAML_FUNCTIONS_H
#define __LAML_FUNCTIONS_H


#ifdef LAML_STD_INCLUDE
#include <utility>
#include <ostream>
#endif

#include <laml/base.h>
#include <laml/constants.h>
// #include <laml/Vector3.h>

namespace laml {

    real_t abs(real_t value);

    int sign(real_t val);

    real_t clamp(real_t v, real_t min_val, real_t max_val);
    real_t map(real_t v, real_t min_val, real_t max_val);

    bool epsilon_equal(real_t value, real_t target, real_t eps);

    real_t sin(real_t x);
    real_t sind(real_t x);
    real_t cos(real_t x);
    real_t cosd(real_t x);
    real_t tan(real_t x);
    real_t tand(real_t x);

    real_t asin(real_t x);
    real_t asind(real_t x);
    real_t acos(real_t x);
    real_t acosd(real_t x);
    real_t atan(real_t x);
    real_t atand(real_t x);
    real_t atan2(real_t x, real_t y);
    real_t atan2d(real_t x, real_t y);

    // safe versions within a tolerance
    real_t asin_safe(real_t x, real_t tol);
    real_t asind_safe(real_t x, real_t tol);
    real_t acos_safe(real_t x, real_t tol);
    real_t acosd_safe(real_t x, real_t tol);
    real_t atan_safe(real_t x, real_t tol);
    real_t atand_safe(real_t x, real_t tol);
    //template<typename real_t>
    //real_t atan2_safe(real_t x, real_t y) {
    //    return  ::atan2(x, y);
    //}
    //template<typename real_t>
    //real_t atan2d_safe(real_t x, real_t y) {
    //    return  ::atan2(x, y) * laml::constants::rad2deg<real_t>;
    //}

    inline Vector3 rgb8_to_rgba32f(uint8 r, uint8 g, uint8 b);

}

#endif // __LAML_FUNCTIONS_H
