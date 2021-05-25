include(CTest)
include(../../../GoogleTest.cmake)

function(add_test_executable filename lib) # add source files after test file, they will be added automatically
    get_filename_component(testname ${filename} NAME_WE)
    add_executable(${testname} ${filename})

    target_link_libraries(${testname} PRIVATE ${GMOCK_MAIN_PATH})
    target_link_libraries(${testname} PRIVATE ${lib})
    target_link_googletest(${testname})
    
    add_test(NAME ${testname} COMMAND ${testname})
endfunction()

add_test_executable(bus-tests.cpp nes-bus-lib)
add_test_executable(memory-tests.cpp nes-peripheral-memory-lib)
add_test_executable(instruction-decoder-tests.cpp nes-instruction-decoder-lib)
add_test_executable(instruction-tests.cpp nes-instructions-lib)