cmake_minimum_required(VERSION 3.20)

project(
  LAML 
  VERSION 0.3.0
  DESCRIPTION "A c++ Linear Algebra and Math Library (laml) with an emphasis on 3D game math."
  LANGUAGES CXX)

message(STATUS "Config generated with: ${CMAKE_GENERATOR}")
message(STATUS "Project built with C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Project built with C compiler: ${CMAKE_C_COMPILER}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_TOPLEVEL_PROJECT TRUE)
else()
  set(IS_TOPLEVEL_PROJECT FALSE)
endif()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/../bin")
cmake_path(NORMAL_PATH OUTPUT_DIR)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
message(STATUS "Build files going into: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_subdirectory(laml)
