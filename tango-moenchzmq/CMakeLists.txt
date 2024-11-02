cmake_minimum_required(VERSION 3.14)
project(TangoMoenchZMQ LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Tango)
find_package(ZeroMQ REQUIRED)
find_package(Boost REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS CXX)
include_directories(${HDF5_INCLUDE_DIRS})

if (CUDA_ENABLED)
    enable_language(CUDA)
    find_package(CUDAToolkit)
    add_definitions(-DCUDA_ENABLED=1)
endif()
if (SINGLE_FRAMES_DEBUG)
    message(STATUS "Single Frames Debug enabled")
    add_definitions(-DSINGLE_FRAMES_DEBUG=1)
endif()
if (OPENMP_ENABLED)
    find_package(OpenMP)
    if (OpenMP_CXX_FOUND)
        message(STATUS "OpenMP CXX found")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
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

add_subdirectory(src)
