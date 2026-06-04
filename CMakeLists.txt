cmake_minimum_required(VERSION 3.16)
project(virtual_memory_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VMEM_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

add_library(vmem_core
    src/paging/Types.cpp
)

target_include_directories(vmem_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(vmem_core PRIVATE -Wall -Wextra -Wpedantic)
target_compile_definitions(vmem_core PUBLIC VMEM_DATA_DIR="${VMEM_DATA_DIR}")
