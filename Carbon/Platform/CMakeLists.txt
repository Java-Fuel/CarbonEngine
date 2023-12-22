# Platform Library

cmake_minimum_required(VERSION 3.25)

set(target CarbonPlatform)
set(target_version 0.0.1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

# Add include directories
include_directories(includes)

# Find all source files
file(GLOB src src/*.cpp)

# Build library
add_library(${target} ${src})