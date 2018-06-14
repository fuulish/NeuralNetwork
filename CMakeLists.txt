
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0012 NEW)

set (CMAKE_CXX_STANDARD 11)

project (nn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -DDEBUG")

add_subdirectory(src)
add_subdirectory(tests)

enable_testing ()

add_test (NAME RunTest COMMAND Running)
add_test (NAME ReadFile COMMAND Readfile)
add_test (NAME ForwardSimple COMMAND ForwardSimple)
add_test (NAME ForwardLinear COMMAND ForwardLinear)
add_test (NAME Forward COMMAND Forward)
add_test (NAME TorchComparison COMMAND TorchComparison)
add_test (NAME Backward COMMAND Backward )

add_custom_target(tests DEPENDS Running Readfile ForwardSimple ForwardLinear Forward TorchComparison Backward )
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests )
