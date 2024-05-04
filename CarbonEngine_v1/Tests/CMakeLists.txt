cmake_minimum_required(VERSION 3.25)

set(target CarbonEngineTests)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${target})

include(FetchContent)
FetchContent_Declare(
  googletest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Find all CPP test files
file(GLOB src *.cpp)

include_directories(${ENGINE_INCLUDES_DIR})
add_executable(${target} ${src})

target_link_libraries(
  ${target}
  GTest::gtest_main
  Engine
)

include(GoogleTest)
gtest_discover_tests(${target})