cmake_minimum_required(VERSION 3.14)
project(TangoMoench LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

option(TESTS_ENABLED "Enable tests" OFF)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TESTS_ENABLED ON)
endif()

if (TESTS_ENABLED)
    enable_testing()
    # for code coverage
    include(CodeCoverage)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-default-inline")
    setup_target_for_coverage_gcovr_xml(
        NAME coverage
        EXECUTABLE ctest --output-on-failure
        EXCLUDE "/usr/*" "build/_deps/*" "*/test/*" "*/tangods/*"
        )
endif()
add_subdirectory(tango-moenchzmq)
add_subdirectory(tango-moenchcontrol)
