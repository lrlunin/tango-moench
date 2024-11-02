enable_testing()

add_executable(moenchzmq_test moenchzmq_test.cpp)
add_executable(hdfwriter_test hdfwriter_test.cpp)
target_link_libraries(hdfwriter_test GTest::gtest_main moenchZmqStatic)
target_link_libraries(moenchzmq_test GTest::gtest_main moenchZmqStatic)

include(GoogleTest)
gtest_discover_tests(moenchzmq_test)
gtest_discover_tests(hdfwriter_test)
