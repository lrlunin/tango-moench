enable_testing()

add_executable(moenchzmq_test moenchzmq_test.cpp ${MOENCHZMQ_BACKEND_SRC_FILES})
target_link_libraries(moenchzmq_test GTest::gtest_main zmq fmt Boost::boost ${HDF5_LIBRARIES} Tango::Tango)

include(GoogleTest)
gtest_discover_tests(moenchzmq_test)