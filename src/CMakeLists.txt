include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB sources *.cc)
add_executable (nn  ${sources})

install(TARGETS nn DESTINATION bin)
