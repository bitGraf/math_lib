cmake_minimum_required(VERSION 3.20)

project(
  "LAML" 
  VERSION 0.2.0
  DESCRIPTION "A c++ Linear Algebra and Math Library (laml) with an emphasis on 3D game math."
  HOMEPAGE_URL "https://github.com/bitGraf/math_lib"
  LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_TOPLEVEL_PROJECT TRUE)
else()
  set(IS_TOPLEVEL_PROJECT FALSE)
endif()

set(LAML_SRC
  "src/laml/Functions.cpp"
  "src/laml/Transform.cpp"
  
  "src/laml/Vector2.cpp"
  "src/laml/Vector3.cpp"
  "src/laml/Vector4.cpp"

  "src/laml/Matrix2.cpp"
  "src/laml/Matrix3.cpp"
  "src/laml/Matrix4.cpp"

  "src/laml/Quaternion.cpp"
)

add_library(laml STATIC ${LAML_SRC})

target_include_directories(laml PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR})

target_compile_features(laml PRIVATE cxx_std_17)
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/laml.config.h.in" 
    "${PROJECT_SOURCE_DIR}/include/laml.config.h")

# dummy project
if(IS_TOPLEVEL_PROJECT)
  add_executable(${PROJECT_NAME}_dev)
  target_sources(${PROJECT_NAME}_dev 
    PRIVATE 
      # testing area
      test/main.cpp
    )
  target_link_libraries(${PROJECT_NAME}_dev PUBLIC laml)
  #target_include_directories(${PROJECT_NAME}_dev PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
  #target_include_directories(${PROJECT_NAME}_dev PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
  set_target_properties(${PROJECT_NAME}_dev PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/"
                        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/")
  target_compile_features(${PROJECT_NAME}_dev PRIVATE cxx_std_17)
endif()