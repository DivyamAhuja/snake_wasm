cmake_minimum_required(VERSION 3.12)
project(olcPixelGameEngine CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Emscripten")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17 -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sUSE_LIBPNG=1 -O2")
endif()

add_library(${PROJECT_NAME} STATIC "olcPixelGameEngine.cpp")
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if(${BUILD_WASM})
    target_link_libraries(${PROJECT_NAME} INTERFACE)
else()
    if(WIN32)
        message("WIN32")
        target_link_libraries(${PROJECT_NAME} INTERFACE user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs)
    elseif(UNIX)
        target_link_libraries(${PROJECT_NAME} INTERFACE X11 GL pthread png stdc++fs)
    endif()
endif()