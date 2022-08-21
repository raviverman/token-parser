cmake_minimum_required(VERSION 3.10)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project name
project(token-parser VERSION 0.0.1)

# set directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bld)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# create shared libraries
add_library(parser SHARED src/parser.cpp)

add_library(number_parser SHARED src/number_parser.cpp)
target_link_libraries(number_parser PUBLIC parser)

# add the executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC parser number_parser)