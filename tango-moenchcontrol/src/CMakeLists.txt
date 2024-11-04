add_subdirectory(tangods)

add_library(moenchControlStatic STATIC ${MOENCHCONTROL_TANGODS_SRC_FILES})
target_link_libraries(moenchControlStatic slsDetectorShared slsReceiverStatic Tango::Tango)

# check why not working when added as a static library
add_executable(MoenchControl tangods/main.cpp ${MOENCHCONTROL_TANGODS_SRC_FILES})
target_link_libraries(MoenchControl moenchControlStatic)

install(TARGETS MoenchControl DESTINATION bin)
