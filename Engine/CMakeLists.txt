cmake_minimum_required(VERSION 3.25)

set(target Engine)
set(target_version 0.0.1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Get Source Files
file(GLOB_RECURSE src *.cpp)
file(GLOB headers Includes/*.hpp)

# Add SDL2
find_package(SDL2 REQUIRED)

include_directories(Includes ${SDL_INCLUDES_DIR})

# Create Engine
add_library(${target} SHARED ${src})
target_link_libraries(${target} SDL2::SDL2)

# Copy SDL2 DLL to proper folder after build
add_custom_command(TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${target}> $<TARGET_FILE_DIR:${target}>
  COMMAND_EXPAND_LISTS
)

# # Set target properties
# set_target_properties(${target} PROPERTIES
#     VERSION ${target_version}
#     PUBLIC_HEADER "${headers}"
# )

# # Install DLL
# install(TARGETS ${target}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
