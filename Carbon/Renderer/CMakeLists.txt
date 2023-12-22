# Render Libarary 

cmake_minimum_required(VERSION 3.25)

set(target CarbonRenderer)
set(target_version 0.0.1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

# Add includes directories
include_directories(includes)

# Find all source files
file(GLOB src src/*.cpp)

# Build CarbonRenderer Lib
add_library(${target} STATIC ${src})