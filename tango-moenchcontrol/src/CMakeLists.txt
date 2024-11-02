add_subdirectory(tangods)

add_library(moenchControlStatic STATIC ${MOENCHCONTROL_TANGODS_SRC_FILES})
target_link_libraries(moenchControlStatic slsDetectorShared slsReceiverStatic Tango::Tango)

add_executable(MoenchControl tangods/main.cpp)
target_link_libraries(MoenchControl moenchControlStatic)

install(TARGETS MoenchControl DESTINATION bin)
