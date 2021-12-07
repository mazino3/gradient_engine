#LevelEditor CMakeLists.txt

file(GLOB LEVEL_EDITOR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditor/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditor/*.h)
add_executable(LevelEditor ${LEVEL_EDITOR_FILES})
target_link_libraries(LevelEditor Graphics)
target_link_libraries(LevelEditor ImGui)

target_include_directories(LevelEditor PRIVATE ${PROJECT_SOURCE_DIR}/source/LevelEditor)

add_custom_command(
        TARGET LevelEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/Assets
                 $<TARGET_FILE_DIR:LevelEditor>/Assets)