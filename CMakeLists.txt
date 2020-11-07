cmake_minimum_required(VERSION 3.16)
project(engine2020)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-3.3.2)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew-cmake-2.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ogl2020 source/main.cpp)
#target_link_libraries(ogl2020 ${PROJECT_SOURCE_DIR}/lib/OPENGL32.LIB)
target_link_libraries(ogl2020 libglew_static)
target_link_libraries(ogl2020 glfw)