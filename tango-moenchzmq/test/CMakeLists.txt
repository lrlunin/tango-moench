enable_testing()

add_executable(moenchzmq_test moenchzmq_test.cpp)
target_link_libraries(moenchzmq_test GTest::gtest_main moenchZmqStatic)

include(GoogleTest)
gtest_discover_tests(moenchzmq_test)