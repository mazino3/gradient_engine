#imgui CMakeLists.txt

file(GLOB IMGUI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(ImGui ${IMGUI_FILES})
target_link_libraries(ImGui glfw)
target_link_libraries(ImGui libglew_static)

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})