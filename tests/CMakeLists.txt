add_executable(test_math_utils test_math_utils.cpp)
target_link_libraries(test_math_utils PRIVATE math_utils doctest::doctest_with_main)

add_test(NAME test_math_utils COMMAND test_math_utils)

add_executable(test_read_lines
    test_read_lines.cpp
    ${CMAKE_SOURCE_DIR}/src/learn_unique_ptr.cpp
)
target_link_libraries(test_read_lines PRIVATE doctest::doctest_with_main)

add_test(NAME test_read_lines COMMAND test_read_lines)
