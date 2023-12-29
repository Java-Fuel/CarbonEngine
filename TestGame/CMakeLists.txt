cmake_minimum_required(VERSION 3.25)


set(target TestGame)
set(target_version 0.0.1)

# Get Source Files 
file(GLOB src_files src/*.cpp)
message(src_files = "${src_files}")

add_executable(${target} ${src_files})


# Include proper directories
target_include_directories(${target} PRIVATE ${ENGINE_INCLUDES_DIR} ${SDL_INCLUDES_DIR})

# Find SDL2 
find_package(SDL2 REQUIRED)

# Link CarbonMath library
target_link_libraries(${target} Engine SDL2::SDL2)

add_custom_command(TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${target}> $<TARGET_FILE_DIR:${target}>
  COMMAND_EXPAND_LISTS
)

# Set target properties
set(TARGET ${target} PROPERTIES
    VERSION ${target_version}
)

# Install target
install(IMPORTED_RUNTIME_ARTIFACTS SDL2::SDL2)
install(TARGETS ${target} RUNTIME)

# Package for release
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${${target}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${target}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_OUTPUT_FILE_PREFIX "Game")
include(CPack)


