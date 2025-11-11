cmake_minimum_required(VERSION 3.10)
project(POPAnim)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)

add_subdirectory(3rdpartylibs/libgimbal)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.c src/*.h)

add_executable(POPAnim main.c ${SRCS})
target_link_libraries(POPAnim raylib libGimbal)