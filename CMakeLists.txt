cmake_minimum_required(VERSION 3.12)


set(CXX_STANDARD 17)
option(BUILD_WASM "Build WebAssembly output" OFF)
    if (${BUILD_WASM})
    add_definitions(-DEMCC_DEBUG=1)
    if(DEFINED ENV{EMSDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
    else()
        message(FATAL_ERROR "emscripten not found. please install emsdk and activate it.")
    endif()
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17 -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sUSE_LIBPNG=1 -O2")
endif()

project(game)

if(${BUILD_WASM})
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

file(GLOB SRCS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp")
file(GLOB HDRS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.h")

add_executable(${PROJECT_NAME} ${SRCS})

# olcPixelGameEngine
add_subdirectory(dependencies/olc)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC olcPixelGameEngine)