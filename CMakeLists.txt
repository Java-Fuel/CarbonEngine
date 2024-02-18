cmake_minimum_required(VERSION 3.25)

# Set Configuration Properties/Values
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}/../bin
  CACHE PATH
  "Single Directory for all Libraries"
)

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}/../bin
  CACHE PATH
  "Single Directory for all Executables."
)


project(CarbonEngine)

set(ENGINE_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

add_subdirectory(Engine)
add_subdirectory(TestGame)


# TESTING # 
enable_testing()
add_subdirectory(Tests)
include(CTest)