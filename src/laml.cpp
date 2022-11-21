#include <laml/laml.hpp>

#include <laml.config.h>

// std
#include <iostream>

namespace rh {
    namespace laml {
        const char* getVersionString() {
            return laml_version_string;
        }

        int getVersionComponent(int comp) {
            switch (comp) {
            case GET_VERSION_MAJOR:
                    return LAML_VERSION_MAJOR;
            case GET_VERSION_MINOR:
                return LAML_VERSION_MAJOR;
            case GET_VERSION_PATCH:
                return LAML_VERSION_MAJOR;
            }

            return -1;
        }
    }
}