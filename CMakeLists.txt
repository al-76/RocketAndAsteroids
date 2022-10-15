cmake_minimum_required(VERSION 3.6)
project(RocketAndAsteriods VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

# Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Test
enable_testing()

add_executable(
  raa_test
  test/system/collision_system_test.cpp
  test/system/game_logic_system_test.cpp
  test/system/graphics_system_test.cpp
  test/system/input_system_test.cpp
  test/entity_test.cpp
  test/world_test.cpp
)

target_link_libraries(
  raa_test
  GTest::gtest_main
  GTest::gmock
)

target_include_directories(raa_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(raa_test)

# Build and link
add_executable(raa
src/main.cpp
)

find_program(CLANG_TIDY NAMES clang-tidy)
if (CLANG_TIDY)
  set_target_properties(raa PROPERTIES CXX_CLANG_TIDY clang-tidy)
endif()

target_include_directories(raa PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)
