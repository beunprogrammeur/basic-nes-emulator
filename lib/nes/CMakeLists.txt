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
    src/nes/bus/bus.cpp
)

# TODO: adding tests to the build in required
add_subdirectory(tests)