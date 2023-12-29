cmake_minimum_required(VERSION 3.25)

# Set Configuration Properties/Values
set(CMAKE_DEBUG_POSTFIX d)


project(CarbonEngine)

set(ENGINE_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Includes)
set(SDL2_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Libs/SDL2/include)
set(SDL_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/SDL2/include)

add_subdirectory(Engine)
add_subdirectory(TestGame)


# TESTING # 
enable_testing()
add_subdirectory(Tests)
include(CTest)