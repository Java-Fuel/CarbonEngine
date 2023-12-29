cmake_minimum_required(VERSION 3.25)


set(target TestGame)
set(target_version 0.0.1)

# Get Source Files 
file(GLOB src_files src/*.cpp)
message(src_files = "${src_files}")

add_executable(${target} ${src_files})


# Include proper directories
target_include_directories(${target} PRIVATE ${ENGINE_INCLUDES_DIR})


# Link CarbonMath library
target_link_libraries(${target} Engine)


# Set target properties
set(TARGET ${target} PROPERTIES
    VERSION ${target_version}
)

# Install target
install(TARGETS ${target} RUNTIME)

# Package for release
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${${target}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${target}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_OUTPUT_FILE_PREFIX "Game")
include(CPack)


