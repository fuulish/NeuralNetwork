include_directories (${nn_SOURCE_DIR}/src)

add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data/")

add_executable (Running running.cc)
target_link_libraries (Running nn)

add_executable (Readfile readfile.cc)
target_link_libraries (Readfile nn)

add_executable (Forward forward.cc)
target_link_libraries (Forward nn)

# add_test (NAME RunTest COMMAND Running)
