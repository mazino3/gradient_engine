#Math CMakeLists.txt

file (GLOB MATH_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Math/*.h)
file (GLOB MATH_GEOMETRY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Math/Geometry/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Math/Geometry/*.h)
file (GLOB UTILITY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Utility/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Utility/*.h)

source_group("Math" FILES ${MATH_FILES})
source_group("Math\\Geometry" FILES ${MATH_GEOMETRY_FILES})
source_group("Utility" FILES ${UTILITY_FILES})

add_library(Math ${MATH_FILES} ${MATH_GEOMETRY_FILES} ${UTILITY_FILES})

target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})