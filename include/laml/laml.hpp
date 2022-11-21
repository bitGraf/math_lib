#pragma once

// include all the standard headers anyone would need
#include <laml/data_types.hpp>

#define GET_VERSION_MAJOR 0
#define GET_VERSION_MINOR 1
#define GET_VERSION_PATCH 2

namespace rh {
    namespace laml {
        const char* getVersionString();
        int getVersionComponent(int comp);
    }
}