cmake_minimum_required(VERSION 3.14)
project(TangoMoenchControl LANGUAGES CXX)

find_package(Tango)
find_package(ZeroMQ REQUIRED)
find_package(Boost REQUIRED)
find_package(slsDetectorPackage REQUIRED)

if (slsDetectorPackage_VERSION_MAJOR LESS 8)
        message(FATAL_ERROR "slsDetectorPacakge version needs to be 8 or greater")
else()
    message(STATUS "Found slsDetectorPackage version ${slsDetectorPackage_VERSION_MAJOR}")
    add_definitions(-DSLS_MAJOR_VERSION=${slsDetectorPackage_VERSION_MAJOR})
endif()

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (TESTS_ENABLED)
    message(STATUS "Tests for tango-moenchcontrol enabled")
    add_subdirectory(test)
    # google test requires C language due to the CTest inside, I guess.
    enable_language(C)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()
