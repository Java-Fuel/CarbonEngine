# Platform Library

cmake_minimum_required(VERSION 3.25)

set(target CarbonPlatform)
set(target_version 0.0.1)
set(target_so_version 1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

# Add Testing Project
enable_testing()
add_subdirectory(tests)

# Add include directories
include_directories(includes)

# Find all source files
file(GLOB src src/*.cpp)

# Build library
add_library(${target} ${src})
# Set target properties
set(TARGET ${target} PROPERTY VERSION ${target_version})
set(TARGET ${target} PROPERTY SOVERSION ${target_so_version})