cmake_minimum_required(VERSION 3.16)
project(engine2020)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-3.3.2)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew-cmake-2.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB GRAPHICS_FILES ${PROJECT_SOURCE_DIR}/source/Graphics/*.cpp ${PROJECT_SOURCE_DIR}/source/Graphics/*.h)
add_library(Graphics ${GRAPHICS_FILES})
target_link_libraries(Graphics libglew_static)
target_link_libraries(Graphics glfw)

add_executable(ogl2020 source/main.cpp)
add_dependencies(ogl2020 Graphics)
target_link_libraries(ogl2020 Graphics)

add_custom_command(
        TARGET ogl2020 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/Assets
                 $<TARGET_FILE_DIR:ogl2020>/Assets)