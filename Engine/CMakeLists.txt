cmake_minimum_required(VERSION 3.25)

set(target Engine)
set(target_version 0.0.1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Get Source Files
file(GLOB_RECURSE src *.cpp)
file(GLOB headers Includes/*.hpp)

# Ensure files are found (debugging)
message(SRC = ${src})
message(HEADERS ${headers})

include_directories(Includes)

add_library(${target} SHARED ${src})

# Set target properties
set_target_properties(${target} PROPERTIES
    VERSION ${target_version}
    PUBLIC_HEADER "${headers}"
)

# Install DLL
install(TARGETS ${target}
 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
 PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
