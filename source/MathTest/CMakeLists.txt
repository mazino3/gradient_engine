#Math test 

file (GLOB MATH_TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/MathTest/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/MathTest/*.h)

add_executable(MathTest ${MATH_TEST_FILES})

target_link_libraries(MathTest PRIVATE gtest Math)
target_include_directories(MathTest PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
add_test(NAME MathTest COMMAND MathTest)