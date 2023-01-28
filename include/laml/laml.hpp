#ifndef __LAML_H
#define __LAML_H

// include all the standard headers anyone would need
#include <laml.config.h>

#include <laml/data_types.hpp>

#include <laml/vector.hpp>

#include <laml/matrix_base.hpp>
#include <laml/matrix2.hpp>
#include <laml/matrix3.hpp>
#include <laml/matrix4.hpp>

#include <laml/quaternion.hpp>

#include <laml/constants.hpp>
#include <laml/transform.hpp>

namespace laml {
    template<typename T>
    bool epsilon_equal(T value, double target, double eps) {
        return  (fabs(static_cast<double>(value) - target) < eps);
    }
}

#endif //__LAML_H