cmake_minimum_required(VERSION 3.16)

project(VMEM_Manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(vmem_core
    src/memory/BackingStore.cpp
    src/memory/PhysicalMemory.cpp
    src/paging/Types.cpp
)

target_include_directories(vmem_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(vmem_core PRIVATE -Wall -Wextra -Wpedantic)

add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data
)
