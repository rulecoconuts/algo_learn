cmake_minimum_required(VERSION 3.11.0)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.0
)

FetchContent_MakeAvailable(Catch2)

project(b_tree)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE test_sources "tests/*.cpp")
file(GLOB_RECURSE lib_sources "src/*.cpp")

add_executable(tests ${test_sources})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# allow CMAKE automatically register tests with CTest
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)

add_executable(b_tree ${lib_sources})