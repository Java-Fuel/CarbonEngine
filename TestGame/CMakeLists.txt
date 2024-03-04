cmake_minimum_required(VERSION 3.25)


set(target TestGame)
set(target_version 0.0.1)
set(platform WIN32)

project(TestGame)

# Get Source Files 
file(GLOB src_files src/*.cpp)
message(src_files = "${src_files}")

IF (WIN32)
    set(platform WIN32)
ENDIF()

add_executable(${target} ${platform} ${src_files})


# Include proper directories
target_include_directories(${target} PRIVATE ${ENGINE_INCLUDES_DIR})


# Link CarbonMath library
target_link_libraries(${target} Engine)

# Set target properties
set(TARGET ${target} PROPERTIES
    VERSION ${target_version}
)




