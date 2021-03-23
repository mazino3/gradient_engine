#GraphicsTests CMakeLists.txt

file(GLOB GRAPHICS_TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsTest/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsTest/*.h)
add_executable(GraphicsTest ${GRAPHICS_TEST_FILES})
target_link_libraries(GraphicsTest Graphics)
target_link_libraries(GraphicsTest ImGui)
#target_include_directories(GraphicsTest PRIVATE ${PROJECT_SOURCE_DIR}/imgui-1.79)
target_include_directories(GraphicsTest PRIVATE ${PROJECT_SOURCE_DIR}/source)

add_custom_command(
        TARGET GraphicsTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/Assets
                 $<TARGET_FILE_DIR:GraphicsTest>/Assets)