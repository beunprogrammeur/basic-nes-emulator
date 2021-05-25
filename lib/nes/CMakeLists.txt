# main lib to link against to get the whole emulator
add_library(nes-lib INTERFACE)

function(nes_add_library libname) # ARGN is source files
    add_library(${libname} ${ARGN})
    target_include_directories(${libname} PUBLIC include)
    target_link_libraries(nes-lib INTERFACE ${libname})
endfunction()


#library creation
nes_add_library(nes-peripheral-memory-lib
    src/nes/peripherals/memory.cpp 
)

nes_add_library(nes-bus-lib
    src/nes/cpu/bus/bus.cpp
)

nes_add_library(nes-instructions-lib
    src/nes/cpu/instructions/instructions.cpp
    src/nes/cpu/instructions/base_instruction.cpp
)

#todo: this lib depends on nes-instructions lib, how can we add lib dependencies too? CMAKE optional parameters? named parameters?
nes_add_library(nes-instruction-decoder-lib
    src/nes/cpu/instructions/instructionset.cpp
    src/nes/cpu/instructions/instruction_decoder.cpp
)


# TODO: adding tests to the build in required
add_subdirectory(tests)