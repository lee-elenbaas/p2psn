project(math)

add_executable(math tests/test_task.cpp tests/full_polynomial_tests.cpp polynomial/full_polynomial_stream_traits.cpp tests/main.cpp)


add_subdirectory(tests)
add_subdirectory(polynomial)