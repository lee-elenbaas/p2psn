cmake_minimum_required(VERSION 2.8)

project(math)

add_subdirectory(tests)
add_subdirectory(polynomial)
add_subdirectory(modulu)
add_subdirectory(bitsetint)

add_library(tests tests/utils/tuple_operations_test.cpp tests/bitsetint/bitsetint_tests.cpp modulu/mod_stream_traits.cpp tests/test_task.cpp tests/modulu/mod_tests.cpp tests/polynomial/full_polynomial_tests.cpp)
add_executable(mathTests modulu/mod.cpp polynomial/full_polynomial_stream_traits.cpp main.cpp)

link_directories(tests)
target_link_libraries(mathTests tests)

add_subdirectory(utils)
