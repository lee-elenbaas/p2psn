cmake_minimum_required(VERSION 2.8)

project(math)

add_subdirectory(tests)
add_subdirectory(polynomial)
add_subdirectory(modulu)

add_library(tests tests/test_task.cpp tests/full_polynomial_tests.cpp)
add_executable(mathTests modulu/mod.cpp polynomial/full_polynomial_stream_traits.cpp main.cpp)

link_directories(tests)
target_link_libraries(mathTests tests)
