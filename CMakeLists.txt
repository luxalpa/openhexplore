cmake_minimum_required(VERSION 3.15)
project(openhexplore)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY T:/Games/OpenHexplore) # set output to gGame file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) # set output to gGame file

set(CMAKE_CXX_STANDARD 20)

#FILE(GLOB_RECURSE SRCFILES src/*.cpp src/*.h src/*.hpp)

add_compile_definitions(_X86_) # so we can use windef.h instead of windows.h

add_library(openhexplore SHARED
        src/main.cpp src/main.h
        src/interop/interop.cpp src/interop/interop.hpp
        src/init.cpp src/init.h src/globals.h src/game_window.cpp src/game_window.h src/global_fns.h src/game/meta.cpp src/game/meta.h src/filedb.cpp src/filedb.h src/files.cpp src/files.h src/registry.cpp src/registry.h src/game/run.cpp src/game/run.h src/other.cpp src/other.h src/logos.cpp src/logos.h src/pcx.cpp src/pcx.h src/keys.cpp src/keys.h src/sound.cpp src/sound.h src/sounddb.cpp src/sounddb.h src/random.cpp src/random.h)
