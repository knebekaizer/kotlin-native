cmake_minimum_required(VERSION 3.15)
project(eh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(SNIPPETS_DIR "$ENV{HOME}/snippets")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${SNIPPETS_DIR}/include)

message(STATUS "SNIPPETS_DIR: ${SNIPPETS_DIR}")

add_library(eh main.cpp)
add_executable(eh_test main.cpp)

target_compile_definitions(eh_test PUBLIC "-DMAIN")
