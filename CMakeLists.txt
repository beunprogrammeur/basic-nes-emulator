cmake_minimum_required(VERSION 3.13)
project(nes-emu VERSION 1.0
                DESCRIPTION "a simple nes emulator for learning purposes"
                LANGUAGES CXX)

# todo: add conditional build option (with or without tests)
enable_testing() 
add_subdirectory(tests)

add_executable(nes-emu src/main.cpp)
target_include_directories(nes-emu PUBLIC include)

include(SourceList.cmake)