cmake_minimum_required(VERSION 3.14)

project(reed_solomon LANGUAGES CXX)

# C++ 14 required for google test
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(galois_field_test galois/galois_field_test.cpp)
target_include_directories(galois_field_test PUBLIC .)
target_link_libraries(galois_field_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(galois_field_test)
