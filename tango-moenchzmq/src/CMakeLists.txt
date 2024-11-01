add_subdirectory(backend)
add_subdirectory(tangods)

if (CUDA_ENABLED)
    add_library(cuda_processing STATIC
    ${CUDA_SRC_FILES}
    )
    set_target_properties(cuda_processing PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_ARCHITECTURES "75;86;89") 
endif()

add_library(moenchZmqStatic STATIC ${MOENCHZMQ_BACKEND_SRC_FILES})
target_link_libraries(moenchZmqStatic zmq fmt ${HDF5_LIBRARIES} Boost::boost)

add_executable(MoenchZMQ tangods/main.cpp ${MOENCHZMQ_TANGODS_SRC_FILES})
add_executable(ComputationTest ${MOENCH_TEST})

target_link_libraries(MoenchZMQ Tango::Tango moenchZmqStatic)

target_link_libraries(ComputationTest moenchZmqStatic)

install(TARGETS MoenchZMQ DESTINATION bin)
