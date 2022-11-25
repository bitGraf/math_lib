cmake_minimum_required(VERSION 3.20)

# Google Test
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# Vector basic tests
add_executable(vector_test vector_test.cpp)
target_link_libraries(vector_test PRIVATE GTest::GTest INTERFACE laml)
target_include_directories( vector_test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
          $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_compile_features(vector_test PRIVATE cxx_std_17)
add_test(basic_vector_tests vector_test)

# Matrix basic tests
add_executable(matrix_test matrix_test.cpp)
target_link_libraries(matrix_test PRIVATE GTest::GTest INTERFACE laml)
target_include_directories( matrix_test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_compile_features(matrix_test PRIVATE cxx_std_17)
add_test(basic_matrix_tests matrix_test)
# Matrix spec. tests
add_executable(matrix_test2 matrix_test2.cpp)
target_link_libraries(matrix_test2 PRIVATE GTest::GTest INTERFACE laml)
target_include_directories( matrix_test2
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_compile_features(matrix_test2 PRIVATE cxx_std_17)
add_test(specialization_matrix_tests matrix_test2)