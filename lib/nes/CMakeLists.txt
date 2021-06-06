# main lib to link against to get the whole emulator
add_library(nes-lib INTERFACE)

function(nes_add_library)
    include(CMakeParseArguments)
    set(prefix NESLIB)
    set(flags )
    set(single_values NAME)
    set(multi_values DEPS SRCS)

    cmake_parse_arguments( 
        "${prefix}"
        "${flags}"
        "${single_values}"
        "${multi_values}"
        ${ARGN}
        )

    if(NOT DEFINED NESLIB_NAME) 
        message(FATAL_ERROR "can't make library withouth name")
    endif()

    add_library(${NESLIB_NAME} ${NESLIB_SRCS})
    target_include_directories(${NESLIB_NAME} PUBLIC include)
    target_link_libraries(${NESLIB_NAME} PUBLIC ${NESLIB_DEPS})
    target_link_libraries(nes-lib INTERFACE ${NESLIB_NAME})
endfunction()

#library creation

nes_add_library(
    NAME nes-clock-lib
    SRCS src/nes/cpu/clock/debug_clock.cpp
)

nes_add_library( 
    NAME nes-peripheral-memory-lib
    SRCS src/nes/peripherals/memory.cpp 
)

nes_add_library(
    NAME nes-bus-lib
    SRCS src/nes/cpu/bus/bus.cpp
)

nes_add_library(
    NAME nes-instructions-lib
    SRCS src/nes/cpu/instructions/instructions.cpp
         src/nes/cpu/instructions/base_instruction.cpp
)

nes_add_library(
    NAME nes-instruction-decoder-lib
    SRCS src/nes/cpu/instructions/instructionset.cpp
         src/nes/cpu/instructions/instruction_decoder.cpp
    DEPS nes-instructions-lib
)


# TODO: adding tests to the build in required
add_subdirectory(tests)