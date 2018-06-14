include_directories (${nn_SOURCE_DIR}/src)

add_definitions(-DDATA_DIR="${CMAKE_SOURCE_DIR}/data/")

add_executable (Running EXCLUDE_FROM_ALL running.cc)
target_link_libraries (Running nn)

add_executable (Readfile EXCLUDE_FROM_ALL readfile.cc)
target_link_libraries (Readfile nn)

add_executable (ForwardSimple EXCLUDE_FROM_ALL forward_simple.cc)
target_link_libraries (ForwardSimple nn)

add_executable (ForwardLinear EXCLUDE_FROM_ALL forward_linear.cc)
target_link_libraries (ForwardLinear nn)

add_executable (Forward EXCLUDE_FROM_ALL forward.cc)
target_link_libraries (Forward nn)

add_executable (TorchComparison EXCLUDE_FROM_ALL torch_comparison.cc)
target_link_libraries (TorchComparison nn)

add_executable (Backward EXCLUDE_FROM_ALL backward.cc)
target_link_libraries (Backward nn)

# add_test (NAME RunTest COMMAND Running)
