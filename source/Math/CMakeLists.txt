#Math CMakeLists.txt

file (GLOB MATH_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Math/*.h)
add_library(Math ${MATH_FILES})
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})