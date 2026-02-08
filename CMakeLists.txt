cmake_minimum_required(VERSION 3.14)
file(READ "VERSION" PROJECT_VERSION)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)  
project(tango-moench LANGUAGES CXX VERSION ${PROJECT_VERSION})
message(STATUS "Project Version: ${PROJECT_VERSION}")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

option(TESTS_ENABLED "Enable tests" OFF)
option(COVERAGE_ENABLED "Enable coverage" OFF)
option(BUILD_DOCS "Build documentation" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TESTS_ENABLED ON)
    set(COVERAGE_ENABLED ON)
endif()

if (TESTS_ENABLED)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    # for code coverage
    if (COVERAGE_ENABLED)
        # coverage requires C compiler somehow
        enable_language(C)
        include(CodeCoverage)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-default-inline")
        setup_target_for_coverage_lcov(
            NAME coverage
            EXECUTABLE ctest --output-on-failure
            EXCLUDE "/usr/*"
            "build/*"
            "tango-moenchzmq/test"
            "tango-moenchzmq/src/tangods"
            "tango-moenchcontrol/src/tangods"
            "tango-moenchcontrol/test"
            )
    endif()
endif()
add_subdirectory(tango-moenchzmq)
add_subdirectory(tango-moenchcontrol)

if (BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    find_package(Sphinx REQUIRED breathe sphinxcontrib.mermaid)

    set(DOXYGEN_FILE_PATTERNS "*.hpp;*.cpp;*.h")
    set(DOXYGEN_RECUVISE YES)
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_XML YES)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doxygen)
    set(DOXYGEN_SHOW_INCLUDE_FILES NO)
    set(DOXYGEN_SHOW_FILES NO)
    set(DOXYGEN_SHOW_DIRECTORIES NO)
    set(DOXYGEN_MACRO_EXPANSION YES)
    set(DOXYGEN_EXCLUDE_PATTERNS "**/ClassFactory.cpp;**/main.cpp;**/*Class.cpp;**/*Class.h;**/*StateMachine.cpp")

    set(DOXYGEN_XML_OUTPUT ${CMAKE_BINARY_DIR}/doxygen/zmq)
    
    doxygen_add_docs(
        doxygen_moenchzmq
        ${CMAKE_SOURCE_DIR}/tango-moenchzmq/src
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tango-moenchzmq/src
        COMMENT "Generating ZMQ API documentation with Doxygen"
    )
    
    set(DOXYGEN_XML_OUTPUT ${CMAKE_BINARY_DIR}/doxygen/control)
    
    doxygen_add_docs(
        doxygen_moenchcontrol
        ${CMAKE_SOURCE_DIR}/tango-moenchcontrol/src
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tango-moenchcontrol/src
        COMMENT "Generating Control API documentation with Doxygen"
    )

    # Configure Sphinx
    set(SPHINX_BUILD "${CMAKE_BINARY_DIR}/docs/sphinx")
    set(SPHINX_INDEX_FILE "${SPHINX_BUILD}/index.html")

    sphinx_add_docs(
        sphinx_docs
        BREATHE_PROJECTS tango-moenchzmq tango-moenchcontrol
        SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        BUILDER html
        DEPENDS doxygen_moenchzmq doxygen_moenchcontrol
    )

    add_dependencies(sphinx_docs doxygen_moenchzmq doxygen_moenchcontrol)

endif()
