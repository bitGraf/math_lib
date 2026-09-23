#include <laml/Functions.hpp>

#include <math.h>

namespace laml {

    real_t abs(real_t value) {
        if (value > 0)
            return value;
        else
            return -value;
    }

    int sign(real_t val) {
        return (0.0 < val) - (val < 0.0);
    }

    real_t clamp(real_t v, real_t min_val, real_t max_val) {
        return v > max_val ? max_val : (v < min_val ? min_val : v);
    }

    real_t map(real_t v, real_t min_val, real_t max_val) {
        real_t range = max_val - min_val;
        while (v < min_val) {
            v += range;
        }
        while (v > max_val) {
            v -= range;
        }
        return v;
    }

    bool epsilon_equal(real_t value, real_t target, real_t eps) {
        return  (abs(value - target) < eps);
    }

    real_t sin(real_t x) {
        return  ::sin(x);
    }
    real_t sind(real_t x) {
        return  ::sin(x * laml::constants::deg2rad);
    }
    real_t cos(real_t x) {
        return  ::cos(x);
    }
    real_t cosd(real_t x) {
        return  ::cos(x * laml::constants::deg2rad);
    }
    real_t tan(real_t x) {
        return  ::tan(x);
    }
    real_t tand(real_t x) {
        return  ::tan(x * laml::constants::deg2rad);
    }


    real_t asin(real_t x) {
        return  ::asin(x);
    }
    real_t asind(real_t x) {
        return  ::asin(x) * laml::constants::rad2deg;
    }
    real_t acos(real_t x) {
        return  ::acos(x);
    }
    real_t acosd(real_t x) {
        return  ::acos(x) * laml::constants::rad2deg;
    }
    real_t atan(real_t x) {
        return  ::atan(x);
    }
    real_t atand(real_t x) {
        return  ::atan(x) * laml::constants::rad2deg;
    }
    real_t atan2(real_t x, real_t y) {
        return  ::atan2(x, y);
    }
    real_t atan2d(real_t x, real_t y) {
        return  ::atan2(x, y) * laml::constants::rad2deg;
    }

    // safe versions within a tolerance
    real_t asin_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::asin(x);
    }
    real_t asind_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::asin(x) * laml::constants::rad2deg;
    }
    real_t acos_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::acos(x);
    }
    real_t acosd_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::acos(x) * laml::constants::rad2deg;
    }
    real_t atan_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::atan(x);
    }
    real_t atand_safe(real_t x, real_t tol) {
        if (x > real_t( 1.0) && x < (real_t( 1.0) + tol)) x = real_t( 1.0);
        if (x < real_t(-1.0) && x > (real_t(-1.0) - tol)) x = real_t(-1.0);
        return  ::atan(x) * laml::constants::rad2deg;
    }
    //template<typename real_t>
    //real_t atan2_safe(real_t x, real_t y) {
    //    return  ::atan2(x, y);
    //}
    //template<typename real_t>
    //real_t atan2d_safe(real_t x, real_t y) {
    //    return  ::atan2(x, y) * laml::constants::rad2deg<real_t>;
    //}

    inline Vector3 rgb8_to_rgba32f(uint8 r, uint8 g, uint8 b) {
        return laml::Vector3(((real32)r) / 255.0f, ((real32)g) / 255.0f, ((real32)b) / 255.0f);
    }

}