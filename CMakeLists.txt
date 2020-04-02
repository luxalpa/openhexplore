cmake_minimum_required(VERSION 3.15)
project(openhexplore)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY T:/Games/OpenHexplore)

set(CMAKE_CXX_STANDARD 20)

#FILE(GLOB_RECURSE SRCFILES src/*.cpp src/*.h src/*.hpp)

set(LIBRARY_OUTPUT_DIRECTORY "C:/Users/Smaug/Desktop/lib")
set(EXECUTABLE_OUTPUT_PATH "C:/Users/Smaug/Desktop/lib")
add_library(openhexplore SHARED
        src/main.cpp src/main.h
        src/interop/interop.cpp src/interop/interop.hpp
        src/interop/memory.cpp src/interop/memory.h
        src/init.cpp src/init.h src/globals.h)
