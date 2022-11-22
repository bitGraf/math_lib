#ifndef __LAML_H
#define __LAML_H

// include all the standard headers anyone would need
#include <laml/data_types.hpp>
#include <laml/vector.hpp>
#include <laml/matrix.hpp>
#include <laml/quaternion.hpp>
#include <laml/constants.hpp>

#define GET_VERSION_MAJOR 0
#define GET_VERSION_MINOR 1
#define GET_VERSION_PATCH 2

namespace rh {
    namespace laml {
        const char* getVersionString();
        int getVersionComponent(int comp);
    }
}

#endif //__LAML_H