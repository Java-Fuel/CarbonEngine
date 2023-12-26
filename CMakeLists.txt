cmake_minimum_required(VERSION 3.25)

# Set Configuration Properties/Values
set(CMAKE_DEBUG_POSTFIX d)


project(CarbonEngine)

add_subdirectory(Carbon/Utils)
add_subdirectory(Carbon/Math)
add_subdirectory(Carbon/Platform)
add_subdirectory(Carbon/Renderer)
add_subdirectory(Carbon/Core)


include(CTest)