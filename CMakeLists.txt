
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
