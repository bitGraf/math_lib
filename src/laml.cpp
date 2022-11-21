#include <config.hpp>

// std
#include <iostream>

namespace rh {
    namespace laml {
        void printSomething() {
            printf("laml version: %s\n", version_string);
        }
    }
}