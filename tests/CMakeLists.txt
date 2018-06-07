include_directories (${nn_SOURCE_DIR}/src)

add_executable (Running running.cc)
target_link_libraries (Running nn)

# add_test (NAME RunTest COMMAND Running)
