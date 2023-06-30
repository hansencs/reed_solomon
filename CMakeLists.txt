cmake_minimum_required(VERSION 3.14)

project(reed_solomon LANGUAGES CXX)

# C++ 14 required for google test
# C++ 17 for std::optional
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(
	galois galois/galois_field.cpp galois/polynomial.cpp galois/solve.cpp)
target_include_directories(galois PUBLIC .)

add_library(code code/encoder.cpp code/decoder.cpp)
target_include_directories(code PUBLIC .)
target_link_libraries(code galois)


enable_testing()

add_executable(galois_field_test galois/galois_field_test.cpp)
target_include_directories(galois_field_test PUBLIC .)
target_link_libraries(galois_field_test GTest::gtest_main galois)

add_executable(polynomial_test galois/polynomial_test.cpp)
target_include_directories(polynomial_test PUBLIC .)
target_link_libraries(polynomial_test GTest::gtest_main galois)

add_executable(solve_test galois/solve_test.cpp)
target_include_directories(solve_test PUBLIC .)
target_link_libraries(solve_test GTest::gtest_main galois)

add_executable(encoder_test code/encoder_test.cpp)
target_include_directories(encoder_test PUBLIC .)
target_link_libraries(encoder_test GTest::gtest_main code)

add_executable(decoder_test code/decoder_test.cpp)
target_include_directories(decoder_test PUBLIC .)
target_link_libraries(decoder_test GTest::gtest_main code)

include(GoogleTest)
gtest_discover_tests(galois_field_test)
gtest_discover_tests(polynomial_test)
gtest_discover_tests(solve_test)
gtest_discover_tests(encoder_test)
gtest_discover_tests(decoder_test)
