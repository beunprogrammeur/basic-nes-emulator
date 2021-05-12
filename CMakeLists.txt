cmake_minimum_required(VERSION 3.13)
project(nes-emu VERSION 1.0
                DESCRIPTION "a simple nes emulator for learning purposes"
                LANGUAGES CXX)

enable_testing()

add_subdirectory(lib)

add_executable(nes-emu src/main.cpp)
target_link_libraries(nes-emu nes-lib)