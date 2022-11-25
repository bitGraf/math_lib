cmake_minimum_required(VERSION 3.20)

set(namespace "rh")
project("laml"
    VERSION 0.0.1
    DESCRIPTION "Some library"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

configure_file(laml.config.h.in laml.config.h)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable_testing()
# add_subdirectory(tests)

add_library(${PROJECT_NAME} INTERFACE IMPORTED)

target_sources(${PROJECT_NAME}
    INTERFACE
        include/laml/laml.hpp
        #include/laml/utils.hpp
        include/laml/data_types.hpp
        include/laml/constants.hpp
        include/laml/vector.hpp
        include/laml/matrix_base.hpp
        include/laml/matrix2.hpp
        include/laml/matrix3.hpp
        include/laml/matrix4.hpp
        include/laml/quaternion.hpp
        include/laml/transform.hpp
)

message(STATUS "PROJECT_BINARY_DIR = [${PROJECT_BINARY_DIR}]")

target_include_directories(${PROJECT_NAME}
    INTERFACE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}
)

if(MSVC)
  target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic -Werror)
endif()

# without it public headers won't get installed
set(public_headers
    include/laml/laml.hpp
    include/laml/data_types.hpp
)

add_executable(${PROJECT_NAME}-test)
target_sources(${PROJECT_NAME}-test PRIVATE tests/main.cpp)
target_link_libraries(${PROJECT_NAME}-test INTERFACE laml)
#target_include_directories(${PROJECT_NAME}-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${PROJECT_NAME}-test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/")

if(MSVC)
  target_compile_options(${PROJECT_NAME}-test PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME}-test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()