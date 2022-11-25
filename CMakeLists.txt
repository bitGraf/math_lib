cmake_minimum_required(VERSION 3.20)

project(
  "LAML" 
  VERSION 0.1.0
  DESCRIPTION "A header-only c++ Linear Algebra and Math Library (laml) with an emphasis on 3D game math."
  HOMEPAGE_URL "https://github.com/bitGraf/math_lib"
  LANGUAGES CXX)

include(GNUInstallDirs)
#include (CTest)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_TOPLEVEL_PROJECT TRUE)
else()
  set(IS_TOPLEVEL_PROJECT FALSE)
endif()

option(LAML_INSTALL_LIBRARY
       "Enable installing of library into default locations"
       ${IS_TOPLEVEL_PROJECT})
option(LAML_BUILD_TESTING "Build and run tests " ${IS_TOPLEVEL_PROJECT})

add_library(laml INTERFACE)
add_library(laml::laml ALIAS laml)

target_include_directories(
  laml INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(laml INTERFACE cxx_std_17)

if (BUILD_TESTING AND LAML_BUILD_TESTING)
  add_subdirectory(test)
endif()

if(LAML_INSTALL_LIBRARY)
  install(TARGETS laml
          EXPORT ${PROJECT_NAME}_Targets
          ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  include(CMakePackageConfigHelpers)
  write_basic_package_version_file("LamlConfigVersion.cmake"
                                    VERSION ${PROJECT_VERSION}
                                    COMPATIBILITY SameMajorVersion)

  configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

  configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/laml.config.h.in" 
    "${PROJECT_BINARY_DIR}/laml.config.h")

  install(EXPORT ${PROJECT_NAME}_Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

  install(FILES 
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

  install(FILES 
    "${PROJECT_BINARY_DIR}/laml.config.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/laml)

  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/laml DESTINATION include)
endif()

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

include(CPack)

# dummy project
if(IS_TOPLEVEL_PROJECT)
  add_executable(${PROJECT_NAME}_dev)
  target_sources(${PROJECT_NAME}_dev 
    PRIVATE 
      # testing area
      test/main.cpp
      
      # the actual library files
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
  target_link_libraries(${PROJECT_NAME}_dev INTERFACE laml)
  target_include_directories(${PROJECT_NAME}_dev PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
  target_include_directories(${PROJECT_NAME}_dev PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
  set_target_properties(${PROJECT_NAME}_dev PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/"
                        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/")
  target_compile_features(${PROJECT_NAME}_dev PRIVATE cxx_std_17)
endif()