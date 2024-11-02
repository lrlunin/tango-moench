cmake_minimum_required(VERSION 3.14)
project(TangoMoench LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
        # for code coverage
    include(CodeCoverage)
    setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE ctest --output-on-failure
        EXCLUDE "/usr/*" "build/_deps/*" "*/test/*" "*/tangods/*"
        DEPENDENCIES
            hdfwriter_test
            moenchzmq_test)
endif()
add_subdirectory(tango-moenchzmq)
add_subdirectory(tango-moenchcontrol)
