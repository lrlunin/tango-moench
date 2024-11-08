#[=======================================================================[.rst:
Findcppzmq
---------

Find the C++ ZeroMQ library

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

    ``cppzmq::cppzmq``
    The C++ ZeroMQ library
    ``cppzmq::cppzmq-static``
    The C++ ZeroMQ library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

    ``cppzmq_FOUND``
    True if the system has the C++ ZeroMQ library.
    ``cppzmq_static_FOUND``
    True if the system has the static C++ ZeroMQ library.
    ``cppzmq_IS_STTAIC``
    True if ``cppzmq::cppzmq-static`` is the same as ``cppzmq::cppzmq``.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

    ``cppzmq_INCLUDE_FILE``
    The path to ``zmq.hpp`` file.
    ``cppzmq_INCLUDE_DIR``
    The directory containing ``zmq.hpp``.

#]=======================================================================]

if (NOT DEFINED PKG_CONFIG_FOUND)
    find_package(PkgConfig QUIET)
endif()

set(_cppzmq_PKG_INCLUDE_DIRS "")  # initialise variable

# Collect hints from pkg-config
if (PKG_CONFIG_FOUND)
    pkg_search_module(_cppzmq_PKG cppzmq QUIET)
endif()

find_path(cppzmq_INCLUDE_DIR
    NAMES zmq.hpp
    PATHS "${_cppzmq_PKG_INCLUDE_DIRS}"
)

# Find the include file just so we can report it in
# find_package_handle_standard_args
find_file(cppzmq_INCLUDE_FILE
    NAMES zmq.hpp
    PATHS "" ${_cppzmq_PKG_INCLUDE_DIRS}
)

set(_cppzmq_quiet "") # initialise variable
if (cppzmq_FIND_QUIETLY)
    set(_cppzmq_quiet QUIET)
endif()

find_package(ZeroMQ ${_cppzmq_quiet})
unset(_cppzmq_required)
unset(_cppzmq_quiet)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cppzmq
    REQUIRED_VARS
        cppzmq_INCLUDE_FILE
        cppzmq_INCLUDE_DIR
        ZeroMQ_FOUND
)

if(ZeroMQ_static_FOUND AND cppzmq_FOUND)
    set(cppzmq_static_FOUND TRUE)
    set(cppzmq_IS_STATIC ${ZeroMQ_IS_STATIC})
endif()

if (cppzmq_FOUND)
    mark_as_advanced(cppzmq_INCLUDE_FILE)
    mark_as_advanced(cppzmq_INCLUDE_DIR)
endif()

if (cppzmq_FOUND AND NOT TARGET cppzmq::cppzmq)
    add_library(cppzmq::cppzmq INTERFACE IMPORTED)
    set_target_properties(cppzmq::cppzmq PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${cppzmq_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES  ZeroMQ::ZeroMQ
    )
endif()

if(cppzmq_static_FOUND AND NOT TARGET cppzmq::cppzmq-static)
    set(cppzmq_static_FOUND TRUE)
    add_library(cppzmq::cppzmq-static INTERFACE IMPORTED)
    set_target_properties(cppzmq::cppzmq-static PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${cppzmq_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES  ZeroMQ::ZeroMQ-static
    )
endif()
