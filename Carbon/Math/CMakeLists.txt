# Math Library 
cmake_minimum_required(VERSION 3.25)

set(target CarbonMath)
set(target_version 0.0.1)

project(${target} LANGUAGES C CXX VERSION ${target_version})

file(GLOB src src/*.cpp)
message(sources = "${src}")

include_directories(includes)
add_library(${target} STATIC ${src})
