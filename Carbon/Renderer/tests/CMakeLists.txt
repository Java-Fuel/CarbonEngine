cmake_minimum_required(VERSION 3.25)

enable_testing()

set(target carbonrenderer_tests)

include(FetchContent)
FetchContent_Declare(
  googletest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

# Windows Only Setting: Prevent overriding the parent projects compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Get Source Files
file(GLOB src *.cpp)

include_directories(../includes)

add_executable(${target} ${src})

target_link_libraries(
  ${target}
  GTest::gtest_main
  CarbonRenderer
)

include(GoogleTest)
gtest_discover_tests(${target})