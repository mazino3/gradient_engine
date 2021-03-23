cmake_minimum_required(VERSION 3.16)
project(engine2020)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-3.3.2)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew-cmake-2.1.0)
add_subdirectory(${PROJECT_SOURCE_DIR}/imgui-1.79)

add_subdirectory(${PROJECT_SOURCE_DIR}/source/Math)
add_subdirectory(${PROJECT_SOURCE_DIR}/source/Graphics)
add_subdirectory(${PROJECT_SOURCE_DIR}/source/GraphicsTest)