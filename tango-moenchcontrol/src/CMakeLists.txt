add_subdirectory(tangods)

add_executable(MoenchControl tangods/main.cpp ${MOENCHCONTROL_TANGODS_SRC_FILES})

target_link_libraries(MoenchControl slsDetectorShared slsReceiverStatic Tango::Tango) 

install(TARGETS MoenchControl DESTINATION bin)