cmake_minimum_required(VERSION 3.16)

project(low_latency_feed_handler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable target (empty for now)
add_executable(feed_handler
    src/main.cpp
)

target_include_directories(feed_handler PRIVATE include)