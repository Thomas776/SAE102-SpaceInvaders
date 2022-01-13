cmake_minimum_required(VERSION 3.16)
project(Space)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC src/*)
file(GLOB_RECURSE LIB_HEADERS lib_headers/*)
file(GLOB_RECURSE HEADERS headers/*)

add_executable(Space ${LIB_HEADERS} ${HEADERS} ${SRC})

target_link_directories(Space PUBLIC .)
target_include_directories(Space PUBLIC headers)
target_include_directories(Space PUBLIC lib_headers)

target_link_libraries(Space mingl)
target_link_libraries(Space GL)
target_link_libraries(Space GLU)
target_link_libraries(Space glut)
target_link_libraries(Space pthread)
