# Utils Library 
cmake_minimum_required(VERSION 3.25)

set(target CarbonUtils)
set(target_version 0.0.1)
set(target_so_version 1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

# Specify include directories
include_directories(includes)

# Find source files
file(GLOB src src/*.cpp)

# Build library
add_library(${target} STATIC ${src})

# Set target properties
set(TARGET ${target} PROPERTY VERSION ${target_version})
set(TARGET ${target} PROPERTY SOVERSION ${target_so_version})

