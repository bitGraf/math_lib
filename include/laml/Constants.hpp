#ifndef __LAML_CONSTANTS_H
#define __LAML_CONSTANTS_H

#ifdef MADE_WITH_CMAKE
    #include <laml.config.h>
#endif

namespace laml {

    template<typename T>
    constexpr T eps = static_cast<T>(1e-8);

    namespace constants {

        template<typename T>
        constexpr T pi = static_cast<T>(3.14159265358979323846);
        template<typename T>
        constexpr T deg2rad = static_cast<T>(pi<double>/180.0); // do the divide in double precision before conversion just in case
        template<typename T>
        constexpr T rad2deg = static_cast<T>(180.0/pi<double>); // do the divide in double precision before conversion just in case

        // these seem silly, but also useful...
        template<typename T>
        constexpr T zero = static_cast<T>(0.0);
        template<typename T>
        constexpr T one = static_cast<T>(1.0);
        template<typename T>
        constexpr T two = static_cast<T>(2.0);
    }
}

#endif