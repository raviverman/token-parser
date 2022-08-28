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

add_library(operator SHARED src/operator.cpp)

add_library(number_parser SHARED src/number_parser.cpp)
target_link_libraries(number_parser PUBLIC parser operator)

add_library(expression SHARED src/expression.cpp)
target_link_libraries(expression PUBLIC operator)

add_library(expression_parser SHARED src/expression_parser.cpp)
target_link_libraries(expression_parser PUBLIC parser number_parser expression operator)

# add the executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC parser number_parser expression_parser operator)

# Benchmark target - not built from by default "cmake --build . --target=benchmark"/"make benchmark"
add_executable(benchmark benchmark/test_number_parser.cpp)
target_link_libraries(benchmark PUBLIC parser number_parser)
SET_TARGET_PROPERTIES(benchmark PROPERTIES EXCLUDE_FROM_ALL True)