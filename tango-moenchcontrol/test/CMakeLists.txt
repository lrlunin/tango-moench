enable_testing()

add_executable(moenchcontrol_test moenchcontrol_test.cpp ${MOENCHCONTROL_TANGODS_SRC_FILES})
target_link_libraries(moenchcontrol_test GTest::gtest_main slsDetectorShared slsReceiverStatic Tango::Tango)

include(GoogleTest)
gtest_discover_tests(moenchcontrol_test)