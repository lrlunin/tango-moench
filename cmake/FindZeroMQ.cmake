#[=======================================================================[.rst:
FindZeroMQ
---------

Find the ZeroMQ library

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

    ``ZeroMQ::ZeroMQ``
    The ZeroMQ library.  On Windows this will always be a shared library, on other platforms this will be whatever is found.
    ``ZeroMQ::ZeroMQ-static``
    The ZeroMQ static library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

    ``ZeroMQ_FOUND``
    True if the required components have been found.
    ``ZeroMQ_static_FOUND``
    True if the system has the C++ ZeroMQ static library.
    ``ZeroMQ_IS_STATIC``
    True if ``ZeroMQ::ZeroMQ`` and ``ZeroMQ::ZeroMQ-static`` are the same.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

    ``ZeroMQ_INCLUDE_DIR``
    The directory containing ``zmq.hpp``.
    ``ZeroMQ_shared_LIBRARY_RELEASE``
    The path to the release ZeroMQ library.
    ``ZeroMQ_shared_LIBRARY_DEBUG``
    The path to the debug ZeroMQ library.
    ``ZeroMQ_shared_LIBRARY``
    The path to the release ZeroMQ library, or the debug library
    if the release library is not found
    ``ZeroMQ_static_LIBRARY_RELEASE``
    The path to the release ZeroMQ library.
    ``ZeroMQ_static_LIBRARY_DEBUG``
    The path to the debug ZeroMQ library.
    ``ZeroMQ_static_LIBRARY``
    The path to the release ZeroMQ library, or the debug library
    if the release library is not found
    ``ZeroMQ_RUNTIME_RELEASE``
	The path to the release ZeroMQ dll, windows only.
    ``ZeroMQ_RUNTIME_DEBUG``
	The path to the debug ZeroMQ dll, windows only.

#]=======================================================================]

if (NOT DEFINED PKG_CONFIG_FOUND)
    find_package(PkgConfig QUIET)
endif()

# initialise variables
set(_ZeroMQ_PKG_INCLUDE_DIRS "")
set(_ZeroMQ_PKG_LIBRARY_DIRS "")
set(_ZeroMQ_PKG_CFLAGS_OTHER "")
set(_ZeroMQ_PKG_PREFIX "")

# Collect hints from pkg-config
if (PKG_CONFIG_FOUND)
    pkg_search_module(_ZeroMQ_PKG libzmq QUIET)
    if(NOT _ZeroMQ_PKG_LIBRARY_DIRS AND _ZeroMQ_PKG_LIBDIR)
        set(_ZeroMQ_PKG_LIBRARY_DIRS ${_ZeroMQ_PKG_LIBDIR})
    endif()
endif()

find_path(ZeroMQ_INCLUDE_DIR
    NAMES "zmq.h"
    PATHS ${_ZeroMQ_PKG_INCLUDE_DIRS}
)

if(WIN32)
    set(_zmq_versions "4_0_5" "4_3_4" "4_3_5")
    set(_zmq_vc_versions "" "-v141" "-v142")

    foreach(ver IN LISTS _zmq_versions)
        foreach(vc_ver IN LISTS _zmq_vc_versions)
            list(APPEND _zmq_lib_release_names "libzmq${vc_ver}-mt-${ver}.lib")
            list(APPEND _zmq_lib_debug_names "libzmq${vc_ver}-mt-gd-${ver}.lib")
            list(APPEND _zmq_lib_static_release_names "libzmq${vc_ver}-mt-s-${ver}.lib")
            list(APPEND _zmq_lib_static_debug_names "libzmq${vc_ver}-mt-sgd-${ver}.lib")
            list(APPEND _zmq_runtime_release_names "libzmq${vc_ver}-mt-${ver}.dll")
            list(APPEND _zmq_runtime_debug_names "libzmq${vc_ver}-mt-gd-${ver}.dll")
        endforeach(vc_ver IN LISTS VC_VERSIONS)
    endforeach(ver IN ZMQ_VERSIONS)

    unset(_zmq_versions)
    unset(_zmq_vc_versions)
else()
    set(_zmq_lib_release_names "zmq")
    set(_zmq_lib_debug_names "zmq")
    set(_zmq_lib_static_release_names "libzmq.a")
    set(_zmq_lib_static_debug_names "libzmq.a")
endif(WIN32)

find_library(ZeroMQ_LIBRARY_RELEASE
    NAMES ${_zmq_lib_release_names}
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Release
)

find_library(ZeroMQ_LIBRARY_RELEASE
    NAMES ${_zmq_lib_static_release_names}
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Release
)

find_library(ZeroMQ_LIBRARY_DEBUG
    NAMES ${_zmq_lib_debug_names}
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Debug
)

find_library(ZeroMQ_LIBRARY_DEBUG
    NAMES ${_zmq_lib_static_debug_names}
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Debug
)

find_library(ZeroMQ_static_LIBRARY_RELEASE
    NAMES ${_zmq_lib_static_release_names}
    NAMES_PER_DIR
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Release
)

find_library(ZeroMQ_static_LIBRARY_DEBUG
    NAMES ${_zmq_lib_static_debug_names}
    NAMES_PER_DIR
    PATHS "" ${_ZeroMQ_PKG_LIBRARY_DIRS}
    PATH_SUFFIXES Debug
)

unset(_zmq_lib_release_names)
unset(_zmq_lib_debug_names)
unset(_zmq_lib_static_release_names)
unset(_zmq_lib_static_debug_names)

if(WIN32)
    find_file(ZeroMQ_RUNTIME_DEBUG
        NAMES ${_zmq_runtime_debug_names}
        PATHS "${_ZeroMQ_PKG_PREFIX}"
        PATH_SUFFIXES "bin/Debug" "bin"
    )
    find_file(ZeroMQ_RUNTIME_RELEASE
        NAMES ${_zmq_runtime_release_names}
        PATHS "${_ZeroMQ_PKG_PREFIX}"
        PATH_SUFFIXES "bin/Release" "bin"
    )
    unset(_zmq_runtime_release_names)
    unset(_zmq_runtime_debug_names)
endif()

include(SelectLibraryConfigurations)
select_library_configurations(ZeroMQ)
select_library_configurations(ZeroMQ_static)

if (ZeroMQ_static_LIBRARY)
    set(ZeroMQ_static_FOUND TRUE)
endif()

if (ZeroMQ_LIBRARY STREQUAL ZeroMQ_static_LIBRARY)
    set(ZeroMQ_IS_STATIC TRUE)
else()
    set(ZeroMQ_IS_STATIC FALSE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZeroMQ
    REQUIRED_VARS
        ZeroMQ_LIBRARY
        ZeroMQ_INCLUDE_DIR
)

if (ZeroMQ_FOUND)
    mark_as_advanced(ZeroMQ_INCLUDE_DIR)
    mark_as_advanced(ZeroMQ_LIBRARY)
    mark_as_advanced(ZeroMQ_LIBRARY_RELEASE)
    mark_as_advanced(ZeroMQ_LIBRARY_DEBUG)
endif()

if (ZeroMQ_static_FOUND)
    mark_as_advanced(ZeroMQ_static_LIBRARY)
    mark_as_advanced(ZeroMQ_static_LIBRARY_RELEASE)
    mark_as_advanced(ZeroMQ_static_LIBRARY_DEBUG)
endif()

if (ZeroMQ_static_FOUND)
    if (NOT TARGET ZeroMQ::ZeroMQ-static)
        add_library(ZeroMQ::ZeroMQ-static STATIC IMPORTED)
    endif()
   if (ZeroMQ_static_LIBRARY_RELEASE)
        set_property(TARGET ZeroMQ::ZeroMQ-static APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(ZeroMQ::ZeroMQ-static PROPERTIES
            IMPORTED_LOCATION_RELEASE "${ZeroMQ_static_LIBRARY_RELEASE}")
    endif()
    if (ZeroMQ_static_LIBRARY_DEBUG)
        set_property(TARGET ZeroMQ::ZeroMQ-static APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(ZeroMQ::ZeroMQ-static PROPERTIES
            IMPORTED_LOCATION_DEBUG "${ZeroMQ_static_LIBRARY_DEBUG}")
    endif()
    set_target_properties(ZeroMQ::ZeroMQ-static PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${ZeroMQ_INCLUDE_DIR}"
        INTERFACE_COMPILE_DEFINITIONS "${_ZeroMQ_PKG_CFLAGS_OTHER}"
    )
endif()

if (ZeroMQ_FOUND AND ZeroMQ_IS_STATIC)
    if (NOT TARGET ZeroMQ::ZeroMQ)
        add_library(ZeroMQ::ZeroMQ ALIAS ZeroMQ::ZeroMQ-static)
    endif()
elseif(ZeroMQ_FOUND)
    # If we are going to create the a SHARED IMPORTED target for the
    # release configuration, but we don't have the debug DLL then we should
    # not add a debug configuration.  We ensure that here by "unfinding"
    # any debug library we found.
    if (ZeroMQ_RUNTIME_RELEASE AND ZeroMQ_LIBRARY_RELEASE AND NOT ZeroMQ_RUNTIME_DEBUG)
        set(ZeroMQ_LIBRARY_DEBUG ZeroMQ_LIBRARY_DEBUG-NOTFOUND)
    endif()

    # Similarly, if we are going to create a SHARED UNKNOWN target for the
    # release configuration, and we _have_ a debug DLL, we "unfind" the
    # debug DLL so that we don't use it.
    if (ZeroMQ_LIBRARY_DEBUG AND ZeroMQ_LIBRARY_RELEASE AND NOT ZeroMQ_RUNTIME_RELEASE)
        set(ZeroMQ_RUNTIME_DEBUG ZeroMQ_RUNTIME_DEBUG-NOTFOUND)
    endif()
    
    if (ZeroMQ_LIBRARY_RELEASE AND ZeroMQ_RUNTIME_RELEASE)
        if (NOT TARGET ZeroMQ::ZeroMQ)
            add_library(ZeroMQ::ZeroMQ SHARED IMPORTED)
        endif()
        set_property(TARGET ZeroMQ::ZeroMQ APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_LOCATION_RELEASE "${ZeroMQ_RUNTIME_RELEASE}")
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_IMPLIB_RELEASE "${ZeroMQ_LIBRARY_RELEASE}")
    elseif(ZeroMQ_LIBRARY_RELEASE)
        if (NOT TARGET ZeroMQ::ZeroMQ)
            add_library(ZeroMQ::ZeroMQ UNKNOWN IMPORTED)
        endif()
        set_property(TARGET ZeroMQ::ZeroMQ APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_LOCATION_RELEASE "${ZeroMQ_LIBRARY_RELEASE}")
    endif()

    if (ZeroMQ_LIBRARY_DEBUG AND ZeroMQ_RUNTIME_DEBUG)
        if (NOT TARGET ZeroMQ::ZeroMQ)
            add_library(ZeroMQ::ZeroMQ SHARED IMPORTED)
        endif()
        set_property(TARGET ZeroMQ::ZeroMQ APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_LOCATION_DEBUG "${ZeroMQ_RUNTIME_DEBUG}")
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_IMPLIB_DEBUG "${ZeroMQ_LIBRARY_DEBUG}")
    elseif(ZeroMQ_LIBRARY_DEBUG)
        if (NOT TARGET ZeroMQ::ZeroMQ)
            add_library(ZeroMQ::ZeroMQ UNKNOWN IMPORTED)
        endif()
        set_property(TARGET ZeroMQ::ZeroMQ APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
            IMPORTED_LOCATION_DEBUG "${ZeroMQ_LIBRARY_DEBUG}")
    endif()
    set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${ZeroMQ_INCLUDE_DIR}"
        INTERFACE_DEFINITIONS "${_ZeroMQ_PKG_CFLAGS_OTHER}"
    )
endif()
