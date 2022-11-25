cmake_minimum_required(VERSION 3.20)

project("LAML" VERSION 0.1.0
             DESCRIPTION "A header-only c++ Linear Algebra and Math Library (laml) with an emphasis on 3D game math."
             HOMEPAGE_URL "https://github.com/bitGraf/math_lib")

include(GNUInstallDirs)

add_library(laml INTERFACE)

target_include_directories(
  laml
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(laml INTERFACE cxx_std_17)

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