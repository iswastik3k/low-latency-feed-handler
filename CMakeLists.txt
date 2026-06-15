cmake_minimum_required(VERSION 3.16)

project(low_latency_feed_handler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable AVX2 optimizations
add_compile_options(-mavx2)

include_directories(include)

# Main executable
add_executable(feed_handler src/main.cpp)

# Unified Benchmarks
add_executable(benchmarks src/benchmarks/benchmarks.cpp)
target_include_directories(benchmarks PRIVATE include)

# Tests
add_executable(parser_tests tests/parser_tests.cpp src/parser/simple_feed_parser.cpp)
target_include_directories(parser_tests PRIVATE include)

add_executable(optimizations_tests tests/optimizations_tests.cpp src/optimizations/simd_parser.cpp)
target_include_directories(optimizations_tests PRIVATE include)

add_executable(datastructures_tests tests/datastructures_tests.cpp)
target_include_directories(datastructures_tests PRIVATE include)

add_executable(io_tests tests/io_tests.cpp)
target_include_directories(io_tests PRIVATE include)