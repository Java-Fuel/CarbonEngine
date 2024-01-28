cmake_minimum_required(VERSION 3.25)

set(target Engine)
set(target_version 0.0.1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Get Source Files
file(GLOB_RECURSE src *.cpp)
file(GLOB_RECURSE headers *.h)

include_directories(${ENGINE_INCLUDES_DIR})

# Create Engine
add_library(${target} SHARED ${src} ${headers} ${headers_pp})

set_target_properties(${target} PROPERTIES
  LANGUAGES CXX
  VERSION 0.0.1
  SOVERSION 0.0.1
  PUBLIC_HEADER "${headers_pp}"
)

install(TARGETS ${target}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  COMPONENT Library
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)