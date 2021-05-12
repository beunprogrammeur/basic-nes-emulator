include(CTest)
include(../GoogleTest.cmake)

function(add_test_executable testname testfile) # add source files after test file, they will be added automatically
    
    add_executable(${testname} ${testfile})
    
    foreach(sourcefile ${ARGN})
        target_sources(${testname} PRIVATE ../src/${sourcefile})
    endforeach()

    target_include_directories(${testname} PUBLIC "../include")
    target_link_libraries(${testname}  PRIVATE ${GMOCK_MAIN_PATH})
    target_link_googletest(${testname})
    
    add_test(NAME ${testname} COMMAND ${testname})
endfunction()

add_test_executable(bus-tests bus-tests.cpp nes/bus/bus.cpp)