#ifndef __LAML_CONSTANTS_H
#define __LAML_CONSTANTS_H

#ifdef MADE_WITH_CMAKE
    #include <laml.config.h>
#endif

#include <laml/base.h>

namespace laml {

    constexpr real_t eps = static_cast<real_t>(1.0e-8);

    namespace constants {

        constexpr real_t pi = static_cast<real_t>(3.14159265358979323846);
        constexpr real_t deg2rad = static_cast<real_t>(pi/180.0);
        constexpr real_t rad2deg = static_cast<real_t>(180.0/pi);
    }
}

#endif
