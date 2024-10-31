cmake_minimum_required(VERSION 3.14)
project(TangoMoenchControl LANGUAGES CXX)

find_package(Tango)
find_package(ZeroMQ REQUIRED)
find_package(Boost REQUIRED)
find_package(slsDetectorPackage 8.0 REQUIRED)

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# for code coverage
# include(CodeCoverage)
# APPEND_COVERAGE_COMPILER_FLAGS()
# setup_target_for_coverage_lcov(
#     NAME coverage
#     EXECUTABLE ctest -j
#     EXCLUDE "/usr/*"
#     DEPENDENCIES
#         moenchcontrol_test)

enable_testing()
add_subdirectory(test)