cmake_minimum_required(VERSION 3.14)
project(RocketAndAsteriods VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# SDL
find_package(SDL2 REQUIRED)

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
  src/world/world.cpp
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
src/world/world.cpp)

target_link_libraries(raa ${SDL2_LIBRARIES})

target_include_directories(raa PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)