cmake_minimum_required(VERSION 3.16)
project(engine2020)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-3.3.2)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew-cmake-2.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

file (GLOB MATH_FILES ${PROJECT_SOURCE_DIR}/source/Math/*.cpp ${PROJECT_SOURCE_DIR}/source/Math/*.h)
add_library(Math ${MATH_FILES})

file(GLOB GRAPHICS_FILES ${PROJECT_SOURCE_DIR}/source/Graphics/*.cpp ${PROJECT_SOURCE_DIR}/source/Graphics/*.h)
file(GLOB GRAPHICS_SHADER_FILES ${PROJECT_SOURCE_DIR}/source/Graphics/Shaders/*.cpp ${PROJECT_SOURCE_DIR}/source/Graphics/Shaders/*.h)

#game_logic source groups for visual studio
source_group("Graphics" FILES ${GRAPHICS_FILES})
source_group("Graphics\\Shaders" FILES ${GRAPHICS_SHADER_FILES})

add_library(Graphics ${GRAPHICS_FILES} ${GRAPHICS_SHADER_FILES})
target_link_libraries(Graphics libglew_static)
target_link_libraries(Graphics glfw)
target_link_libraries(Graphics Math)
add_dependencies(Graphics Math)

file(GLOB IMGUI_FILES ${PROJECT_SOURCE_DIR}/imgui-1.79/*.cpp ${PROJECT_SOURCE_DIR}/imgui-1.79/*.h)
add_library(ImGui ${IMGUI_FILES})
target_link_libraries(ImGui glfw)
target_link_libraries(ImGui libglew_static)

add_executable(ogl2020 source/main.cpp)
add_dependencies(ogl2020 Graphics)
target_link_libraries(ogl2020 Graphics)

file(GLOB GRAPHICS_TEST_FILES ${PROJECT_SOURCE_DIR}/source/GraphicsTest/*.cpp ${PROJECT_SOURCE_DIR}/source/GraphicsTest/*.h)
add_executable(GraphicsTest ${GRAPHICS_TEST_FILES})
target_link_libraries(GraphicsTest Graphics)
target_link_libraries(GraphicsTest ImGui)
target_include_directories(GraphicsTest PUBLIC ${PROJECT_SOURCE_DIR}/imgui-1.79)
target_include_directories(GraphicsTest PUBLIC ${PROJECT_SOURCE_DIR}/source)
add_dependencies(GraphicsTest Graphics)

add_custom_command(
        TARGET GraphicsTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/Assets
                 $<TARGET_FILE_DIR:ogl2020>/Assets)