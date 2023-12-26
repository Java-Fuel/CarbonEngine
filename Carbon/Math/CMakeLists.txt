# Math Library 
cmake_minimum_required(VERSION 3.25)

set(target CarbonMath)
set(target_version 0.0.1)
set(target_so_version 1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

enable_testing()

add_subdirectory(tests)

file(GLOB src src/*.cpp)
message(sources = "${src}")

include_directories(includes)
add_library(${target} STATIC ${src})

# Set target properties
set(TARGET ${target} PROPERTY VERSION ${target_version})
set(TARGET ${target} PROPERTY SOVERSION ${target_so_version})
