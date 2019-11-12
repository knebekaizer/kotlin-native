cmake_minimum_required(VERSION 3.15)
project(simd_wrapper)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v ")

add_library(simd_wrapper simd_lib.cpp simd_lib.h)

add_executable(ctest simd_lib.cpp simd_lib.h)
target_compile_definitions(ctest PUBLIC "-DMAIN")
