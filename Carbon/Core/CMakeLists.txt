cmake_minimum_required(VERSION 3.25)


set(target CarbonEngine_Core)
set(target_version 0.0.1)

project(${target} VERSION ${target_version})

# Get Source Files 
file(GLOB src_files src/*.cpp)
message(src_files = "${src_files}")

# Add includes directory 
include_directories(includes)
include_directories(../Math/includes)
include_directories(../Platform/includes)
include_directories(../Renderer/includes)
include_directories(../Utils/includes)

add_executable(${target} ${src_files})

# Link CarbonMath library
target_link_libraries(${target} PUBLIC CarbonMath CarbonPlatform CarbonRenderer CarbonUtils)

# Set target properties
set(TARGET ${target} PROPERTY VERSION ${target_version})

# Install target
install(TARGETS ${target} RUNTIME DESTINATION bin)

# Package for release
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${${target}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${target}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_OUTPUT_FILE_PREFIX packages)
include(CPack)