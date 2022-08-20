cmake_minimum_required(VERSION 3.10)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project name
project(token-parser VERSION 0.0.1)

# set directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bld) 

# add the executable
add_executable(parser parser.cpp)

# install(TARGETS parser DESTINATION bld)