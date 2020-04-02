cmake_minimum_required(VERSION 3.15)
project(openhexplore)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY T:/Games/OpenHexplore) # set output to game file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) # set output to game file

set(CMAKE_CXX_STANDARD 20)

#FILE(GLOB_RECURSE SRCFILES src/*.cpp src/*.h src/*.hpp)

add_compile_definitions(_X86_) # so we can use windef.h instead of windows.h

add_library(openhexplore SHARED
        src/main.cpp src/main.h
        src/interop/interop.cpp src/interop/interop.hpp
        src/interop/memory.cpp src/interop/memory.h
        src/init.cpp src/init.h src/globals.h src/ddraw.cpp src/ddraw.h src/global_fns.h)
