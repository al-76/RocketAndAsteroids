cmake_minimum_required(VERSION 3.6)
project(RocketAndAsteriods VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

#
# Dependencies
#
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG "release-1.12.1"
)
FetchContent_MakeAvailable(googletest)

#
# Build and link
#
add_executable(raa
src/main.cpp
)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(raa sfml-graphics)

find_program(CLANG_TIDY NAMES clang-tidy)
if (CLANG_TIDY)
  set_target_properties(raa PROPERTIES CXX_CLANG_TIDY clang-tidy)
endif()

target_include_directories(raa PRIVATE
  ${CMAKE_SOURCE_DIR}/src/component
  ${CMAKE_SOURCE_DIR}/src/entity
  ${CMAKE_SOURCE_DIR}/src/system
  ${CMAKE_SOURCE_DIR}/src/world
  ${CMAKE_SOURCE_DIR}/src/implementation
)

#
# Test
#
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
  ${CMAKE_SOURCE_DIR}/src/component
  ${CMAKE_SOURCE_DIR}/src/entity
  ${CMAKE_SOURCE_DIR}/src/system
  ${CMAKE_SOURCE_DIR}/src/world
  ${CMAKE_SOURCE_DIR}/test/implementation
)

include(GoogleTest)
gtest_discover_tests(raa_test)