#graphics CMakeLists.txt

file(GLOB GRAPHICS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.h)
file(GLOB GRAPHICS_SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/Shaders/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/Shaders/*.h)

#game_logic source groups for visual studio
source_group("Graphics" FILES ${GRAPHICS_FILES})
source_group("Graphics\\Shaders" FILES ${GRAPHICS_SHADER_FILES})

add_library(Graphics ${GRAPHICS_FILES} ${GRAPHICS_SHADER_FILES})
target_link_libraries(Graphics libglew_static)
target_link_libraries(Graphics glfw)
target_link_libraries(Graphics Math)

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})