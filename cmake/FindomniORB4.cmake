#[=======================================================================[.rst:
FindomniORB4
------------

Find the omniORB4 libraries

Components
^^^^^^^^^^

    ``COS4``
    Provides the ``omniORB4::COS4`` and ``omniORB4::COS4-static`` (if found) targets
    ``Dynamic4``
    Provides the ``omniORB4::Dynamic4`` and ``omniORB4::Dynamic4-static`` (if found) targets

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

    ``omniORB4::omniORB4``
    The omniORB4 library
    ``omniORB4::omniORB4-static``
    The omniORB4 static library
    ``omniORB4::thread``
    The omnithread library, linked to omniORB4::omniORB4
    ``omniORB4::thread-static``
    The omnithread static library, linked to omniORB4::omniORB4-static
    ``omniORB4::COS4``
    The COS library
    ``omniORB4::COS4-static``
    The COS static library
    ``omniORB4::Dynamic4``
    The Dynamic library
    ``omniORB4::Dynamic4-static``
    The Dynamic static library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

    ``omniORB4_thread_FOUND``
    True if the system has the COS4 library.
    ``omniORB4_COS4_FOUND``
    True if the system has the COS4 library.
    ``omniORB4_Dynamic4_FOUND``
    True if the system has the omniDynamic4 library.
    ``omniORB4_FOUND``
    True if that system has all the required components and
    the main omniORB4 library
    ``omniORB4_thread_IS_STATIC``
    True if ``omniORB4::thread`` is the same as ``omniORB4::thread-static``
    ``omniORB4_COS4_IS_STATIC``
    True if ``omniORB4::COS4`` is the same as ``omniORB4::COS4-static``
    ``omniORB4_Dynamic4_IS_STATIC``
    True if ``omniORB4::Dynamic4`` is the same as ``omniORB4::Dynamic4-static``
    ``omniORB4_IS_STATIC``
    True if ``omniORB4::omniORB4`` is the same as ``omniORB4::omniORB4-static``

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

    ``omniORB4_INCLUDE_DIR``
    The directory containing omniORB4/omniORB.h.
    ``omniORB4_LIBRARY_RELEASE``
    The path to the omniORB release library.
    ``omniORB4_LIBRARY_DEBUG``
    The path to the omniORB debug library.
    ``omniORB4_LIBRARY``
    The path to the omniORB library.
    ``omniORB4_static_LIBRARY_RELEASE``
    The path to the omniORB release static library.
    ``omniORB4_static_LIBRARY_DEBUG``
    The path to the omniORB debug static library.
    ``omniORB4_static_LIBRARY``
    The path to the omniORB static library.
    ``omniORB4_COS4_LIBRARY_RELEASE``
    The path to the omniORB release library.
    ``omniORB4_COS4_LIBRARY_DEBUG``
    The path to the omniORB debug library.
    ``omniORB4_COS4_LIBRARY``
    The path to the omniORB library.
    ``omniORB4_COS4_static_LIBRARY_RELEASE``
    The path to the omniORB release static library.
    ``omniORB4_COS4_static_LIBRARY_DEBUG``
    The path to the omniORB debug static library.
    ``omniORB4_COS4_static_LIBRARY``
    The path to the omniORB static library.
    ``omniORB4_Dynamic4_LIBRARY_RELEASE``
    The path to the omniORB release library.
    ``omniORB4_Dynamic4_LIBRARY_DEBUG``
    The path to the omniORB debug library.
    ``omniORB4_Dynamic4_LIBRARY``
    The path to the omniORB library.
    ``omniORB4_Dynamic4_static_LIBRARY_RELEASE``
    The path to the omniORB release static library.
    ``omniORB4_Dynamic4_static_LIBRARY_DEBUG``
    The path to the omniORB debug static library.
    ``omniORB4_Dynamic4_static_LIBRARY``
    The path to the omniORB static library.
    ``omniORB4_thread_LIBRARY_RELEASE``
    The path to the omniORB release library.
    ``omniORB4_thread_LIBRARY_DEBUG``
    The path to the omniORB debug library.
    ``omniORB4_thread_LIBRARY``
    The path to the omniORB library.
    ``omniORB4_thread_static_LIBRARY_RELEASE``
    The path to the omniORB release static library.
    ``omniORB4_thread_static_LIBRARY_DEBUG``
    The path to the omniORB debug static library.
    ``omniORB4_thread_static_LIBRARY``
    The path to the omniORB static library.
    ``OMNIIDL``
    The path to the omniIDL executable.

#]=======================================================================]

if (NOT DEFINED PKG_CONFIG_FOUND)
    find_package(PkgConfig QUIET)
endif()

# initialise variables
set(_omniORB4_PKG_INCLUDE_DIRS "")
set(_omniORB4_PKG_LIBRARY_DIRS "")
set(_omniORB4_PKG_PREFIX "")

if (PKG_CONFIG_FOUND)
    pkg_search_module(_omniORB4_PKG omniORB4 QUIET)
    pkg_get_variable(_OMNIIDL omniORB4 omniidl)
endif()

set(OMNIIDL_DIR "")
if (_OMNIIDL)
    get_filename_component(OMNIIDL_DIR ${_OMNIIDL} DIRECTORY)
    unset(_OMNIIDL)
endif()

find_program(OMNIIDL NAMES omniidl
    DOC "omniidl executable location"
    PATHS "${OMNIIDL_DIR}"
    PATH_SUFFIXES x86_win32)

unset(OMNIIDL_DIR)
mark_as_advanced(OMNIIDL)

find_path(omniORB4_INCLUDE_DIR
    NAMES omniORB4/omniORB.h
    PATHS "${_omniORB4_PKG_INCLUDE_DIRS}"
)

include(SelectLibraryConfigurations)
function(_omniORB4_find_release_and_debug prefix release_names debug_names release_static_names debug_static_names)
    find_library(${prefix}_LIBRARY_RELEASE
        NAMES ${release_names}
        PATHS "${_omniORB4_PKG_LIBRARY_DIRS}"
        PATH_SUFFIXES x86_win32
    )

    find_library(${prefix}_LIBRARY_DEBUG
        NAMES ${debug_names}
        PATHS "${_omniORB4_PKG_LIBRARY_DIRS}"
        PATH_SUFFIXES x86_win32
    )

    find_library(${prefix}_static_LIBRARY_RELEASE
        NAMES ${release_static_names}
        PATHS "${_omniORB4_PKG_LIBRARY_DIRS}"
        PATH_SUFFIXES x86_win32
    )

    find_library(${prefix}_static_LIBRARY_DEBUG
        NAMES ${debug_static_names}
        PATHS "${_omniORB4_PKG_LIBRARY_DIRS}"
        PATH_SUFFIXES x86_win32
    )

    select_library_configurations(${prefix})
    select_library_configurations(${prefix}_static)

    if ("${${prefix}_LIBRARY}" STREQUAL "${${prefix}_static_LIBRARY}")
        set(${prefix}_IS_STATIC TRUE PARENT_SCOPE)
    endif()

    set(${prefix}_LIBRARY_RELEASE ${${prefix}_LIBRARY_RELEASE} PARENT_SCOPE)
    set(${prefix}_LIBRARY_DEBUG ${${prefix}_LIBRARY_DEBUG} PARENT_SCOPE)
    set(${prefix}_LIBRARY ${${prefix}_LIBRARY} PARENT_SCOPE)

    set(${prefix}_static_LIBRARY_RELEASE ${${prefix}_static_LIBRARY_RELEASE} PARENT_SCOPE)
    set(${prefix}_static_LIBRARY_DEBUG ${${prefix}_static_LIBRARY_DEBUG} PARENT_SCOPE)
    set(${prefix}_static_LIBRARY ${${prefix}_static_LIBRARY} PARENT_SCOPE)
endfunction()

function(_omniORB4_find_runtime_release_and_debug prefix runtime_release_names runtime_debug_names)
    set(release_dlls "")
    foreach(name IN LISTS runtime_release_names)
        list(APPEND release_dlls ${name}.dll)
    endforeach()
    find_file(${prefix}_RUNTIME_RELEASE
            NAMES ${release_dlls}
            PATHS "${_omniORB4_PKG_PREFIX}"
            PATH_SUFFIXES "bin/x86_win32"
        )

    set(debug_dlls "")
    foreach(name IN LISTS runtime_debug_names)
        list(APPEND debug_dlls ${name}.dll)
    endforeach()
    find_file(${prefix}_RUNTIME_DEBUG
            NAMES ${debug_dlls}
            PATHS "${_omniORB4_PKG_PREFIX}"
            PATH_SUFFIXES "bin/x86_win32"
            )
endfunction()

function(_omniORB4_add_target prefix targetname)
    if (${prefix}_static_FOUND)
        if (NOT TARGET omniORB4::${targetname}-static)
            add_library(omniORB4::${targetname}-static STATIC IMPORTED)
        endif()
        if (${prefix}_static_LIBRARY_RELEASE)
            set_property(TARGET omniORB4::${targetname}-static APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE
            )
            set_target_properties(omniORB4::${targetname}-static PROPERTIES
                IMPORTED_LOCATION_RELEASE "${${prefix}_static_LIBRARY_RELEASE}"
            )
        endif()
        if (${prefix}_static_LIBRARY_DEBUG)
            set_property(TARGET omniORB4::${targetname}-static APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG
            )
            set_target_properties(omniORB4::${targetname}-static PROPERTIES
                IMPORTED_LOCATION_DEBUG "${${prefix}_static_LIBRARY_DEBUG}"
            )
        endif()
        set_target_properties(omniORB4::${targetname}-static PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${omniORB4_INCLUDE_DIR}"
            )
    endif()

    if(${prefix}_FOUND AND ${prefix}_IS_STATIC)
        if (NOT TARGET omniORB4::${targetname})
            add_library(omniORB4::${targetname} ALIAS omniORB4::${targetname}-static)
        endif()
    elseif (${prefix}_FOUND)

        # If we are going to create the a SHARED IMPORTED target for the
        # release configuration, but we don't have the debug DLL then we should
        # not add a debug configuration.  We ensure that here by "unfinding"
        # any debug library we found.
        if (${prefix}_RUNTIME_RELEASE AND ${prefix}_LIBRARY_RELEASE AND NOT ${prefix}_RUNTIME_DEBUG)
            set(${prefix}_LIBRARY_DEBUG ${prefix}_LIBRARY_DEBUG-NOTFOUND)
        endif()

        # Similarly, if we are going to create a SHARED UNKNOWN target for the
        # release configuration, and we _have_ a debug DLL, we "unfind" the
        # debug DLL so that we don't use it.
        if (${prefix}_LIBRARY_DEBUG AND ${prefix}_LIBRARY_RELEASE AND NOT ${prefix}_RUNTIME_RELEASE)
            set(${prefix}_RUNTIME_DEBUG ${prefix}_RUNTIME_DEBUG-NOTFOUND)
        endif()

        if (${prefix}_RUNTIME_RELEASE AND ${prefix}_LIBRARY_RELEASE)
            if (NOT TARGET omniORB4::${targetname})
                add_library(omniORB4::${targetname} SHARED IMPORTED)
            endif()

            set_property(TARGET omniORB4::${targetname} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_LOCATION_RELEASE "${${prefix}_RUNTIME_RELEASE}"
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_IMPLIB_RELEASE "${${prefix}_LIBRARY_RELEASE}"
            )
        elseif (${prefix}_LIBRARY_RELEASE)
            if (NOT TARGET omniORB4::${targetname})
                add_library(omniORB4::${targetname} UNKNOWN IMPORTED)
            endif()

            set_property(TARGET omniORB4::${targetname} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_LOCATION_RELEASE "${${prefix}_LIBRARY_RELEASE}"
            )
        endif()

        if (${prefix}_RUNTIME_DEBUG AND ${prefix}_LIBRARY_DEBUG)
            if (NOT TARGET omniORB4::${targetname})
                add_library(omniORB4::${targetname} SHARED IMPORTED)
            endif()

            set_property(TARGET omniORB4::${targetname} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_LOCATION_DEBUG "${${prefix}_RUNTIME_DEBUG}"
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_IMPLIB_DEBUG "${${prefix}_LIBRARY_DEBUG}"
            )
        elseif (${prefix}_LIBRARY_DEBUG)
            if (NOT TARGET omniORB4::${targetname})
                add_library(omniORB4::${targetname} UNKNOWN IMPORTED)
            endif()

            set_property(TARGET omniORB4::${targetname} APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG
            )
            set_target_properties(omniORB4::${targetname} PROPERTIES
                IMPORTED_LOCATION_DEBUG "${${prefix}_LIBRARY_DEBUG}"
            )
        endif()

        set_target_properties(omniORB4::${targetname} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${omniORB4_INCLUDE_DIR}"
            )
    endif()

endfunction()

if (WIN32)
    _omniORB4_find_release_and_debug(omniORB4 omniORB4_rt omniORB4_rtd omniORB4 omniORB4d)
    _omniORB4_find_release_and_debug(omniORB4_thread omnithread_rt omnithread_rtd omnithread omnithreadd)
    _omniORB4_find_release_and_debug(omniORB4_COS4 COS4_rt COS4_rtd COS4 COS4d)
    _omniORB4_find_release_and_debug(omniORB4_Dynamic4 omniDynamic4_rt omniDynamic4_rtd omniDynamic4 omniDynamic4d)

    _omniORB4_find_runtime_release_and_debug(omniORB4 "omniORB4_rt;omniORB430_vc15_rt" "omniORB4_rtd;omniORB430_vc15_rtd")
    _omniORB4_find_runtime_release_and_debug(omniORB4_thread "omnithread_rt;omnithread43_vc15_rt" "omnithread_rt;omnithread43_vc15_rtd")
    _omniORB4_find_runtime_release_and_debug(omniORB4_COS4 "COS4_rt;COS430_vc15_rt" "COS4_rtd;COS430_vc15_rtd")
    _omniORB4_find_runtime_release_and_debug(omniORB4_Dynamic4 "omniDynamic4_rt;omniDynamic430_vc15_rt" "omniDynamic4_rtd;omniDynamic430_vc15_rtd")
else()
    _omniORB4_find_release_and_debug(omniORB4 omniORB4 omniORB4 libomniORB4.a libomniORB4.a)
    _omniORB4_find_release_and_debug(omniORB4_thread omnithread omnithread libomnithread.a libomnithread.a)
    _omniORB4_find_release_and_debug(omniORB4_COS4 COS4 COS4 libCOS4.a libCOS4.a)
    _omniORB4_find_release_and_debug(omniORB4_Dynamic4 omniDynamic4 omniDynamic4 libomniDynamic4.a libomniDynamic4.a)
endif()

if (omniORB4_thread_LIBRARY)
    set(omniORB4_thread_FOUND TRUE)
endif()

if (omniORB4_thread_static_LIBRARY)
    set(omniORB4_thread_static_FOUND TRUE)
endif()

if (omniORB4_COS4_LIBRARY)
    set(omniORB4_COS4_FOUND TRUE)
endif()

if (omniORB4_COS4_static_LIBRARY)
    set(omniORB4_COS4_static_FOUND TRUE)
endif()

if (omniORB4_Dynamic4_LIBRARY)
    set(omniORB4_Dynamic4_FOUND TRUE)
endif()

if (omniORB4_Dynamic4_static_LIBRARY)
    set(omniORB4_Dynamic4_static_FOUND TRUE)
endif()

if(omniORB4_static_LIBRARY AND omniORB4_thread_static_FOUND)
    set(omniORB4_static_FOUND TRUE)
endif()

if(NOT omniORB4_IS_STATIC AND omniORB4_thread_IS_STATIC)
    set(omniORB4_IS_STATIC TRUE)
endif()

# We require the thread component for the main omniORB4 library
list(APPEND omniORB4_FIND_COMPONENTS thread)
if (omniORB4_FIND_REQUIRED)
    set(omniORB4_FIND_REQUIRED_thread TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(omniORB4
    REQUIRED_VARS
        omniORB4_LIBRARY
        omniORB4_INCLUDE_DIR
    HANDLE_COMPONENTS
)

if (omniORB4_FOUND)
    mark_as_advanced(omniORB4_INCLUDE_DIR)
    mark_as_advanced(omniORB4_LIBRARY)
endif()

if (omniORB4_thread_FOUND)
    mark_as_advanced(omniORB4_thread_LIBRARY)
endif()

if (omniORB4_COS4_FOUND)
    mark_as_advanced(omniORB4_COS4_LIBRARY)
endif()

if (omniORB4_Dynamic4_FOUND)
    mark_as_advanced(omniORB4_Dynamic4_LIBRARY)
endif()

_omniORB4_add_target(omniORB4 omniORB4)
_omniORB4_add_target(omniORB4_thread thread)
_omniORB4_add_target(omniORB4_COS4 COS4)
_omniORB4_add_target(omniORB4_Dynamic4 Dynamic4)

if (TARGET omniORB4::omniORB4 AND TARGET omniORB4::thread)
    set_target_properties(omniORB4::omniORB4 PROPERTIES
        INTERFACE_LINK_LIBRARIES omniORB4::thread
        )
endif()

if (TARGET omniORB4::omniORB4-static AND TARGET omniORB4::thread-static)
    set_target_properties(omniORB4::omniORB4-static PROPERTIES
        INTERFACE_LINK_LIBRARIES omniORB4::thread-static
        )
endif()

foreach(tgt omniORB4::thread omniORB4::thread-static)
    if (TARGET ${tgt})
        # For other targets we hope that the appropriate macros are defined in omniconfig.h
        set(_omniORB4_thread_options "") # initialise variable
        set(_omniORB4_thread_libs "") # initialise variable
        if (WIN32)
            # From https://omniorb.sourceforge.io/omni43/omniORB/omniORB001.html
            set(_omniORB4_thread_options
                    -D__x86__
                    -D__NT__
                    -D__WIN32__
                    -D__OSVERSION__=4)
            set(_omniORB4_thread_libs ws2_32.lib mswsock.lib advapi32.lib)
            if (omniORB4_thread_IS_STATIC OR ${tgt} STREQUAL omniORB4::thread-static)
                list(APPEND _omniORB4_thread_options -D_WINSTATIC)
            endif()
        endif()
        set_target_properties(${tgt} PROPERTIES
            INTERFACE_COMPILE_OPTIONS "${_omniORB4_thread_options}"
            INTERFACE_LINK_LIBRARIES "${_omniORB4_thread_libs}"
        )
        unset(_omniORB4_thread_options)
        unset(_omniORB4_thread_libs)
    endif()
endforeach()
