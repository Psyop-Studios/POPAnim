cmake_minimum_required(VERSION 3.10)
project(SwimGym)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)

add_subdirectory(3rdpartylibs/libgimbal)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.c src/*.h 3rdpartylibs/ui/*.c)

list(APPEND SRCS
	3rdpartylibs/qrcodegen.c
	3rdpartylibs/qrcodegen.h
	3rdpartylibs/uilib/
	3rdpartylibs/CypAnim/CypAnim.c
	3rdpartylibs/CypAnim/CypAnim.h
)

add_executable(swimgym main.c ${SRCS})
target_compile_definitions(swimgym PRIVATE USE_PPP)
target_link_libraries(swimgym raylib libGimbal GL kosutils ppp)

include_directories(${KOS_PORTS}/include/raylib)

if(PLATFORM_DREAMCAST)
    include(kallistios REQUIRED)
endif()
