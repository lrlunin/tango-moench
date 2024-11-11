#include "../src/tangods/MoenchControl.h"
#include "../src/tangods/MoenchControlClass.h"
#include <gtest/gtest.h>
#include <iostream>
#include <tango/tango.h>

class MoenchControlTest : public testing::Test {
protected:
  Tango::DeviceProxy *dp;

  void SetUp() {
    dp = new Tango::DeviceProxy("127.0.0.1:50009/a/b/c#dbase=no");
  };

  void TearDown() { delete dp; };
};

TEST_F(MoenchControlTest, basisTest) {
  std::cout << "TEST" << std::endl;
  Tango::DevFloat exptime;
  dp->read_attribute("exposure") >> exptime;
  std::cout << "Exptime: " << exptime << std::endl;
  SUCCEED();
}
