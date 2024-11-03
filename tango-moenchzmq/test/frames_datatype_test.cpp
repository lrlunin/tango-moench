#include <gtest/gtest.h>

#include "../src/backend/Frames.hpp"

TEST(FramesTest, TestOperatorParenthesis) {
  OrderedFrame<float, consts::LENGTH> of;
  of(0, 0) = 1.0;
  of(0, 1) = 2.0;
  of(1, 0) = 3.0;
  of(1, 1) = 4.0;

  EXPECT_FLOAT_EQ(of(0, 0), 1.0);
  EXPECT_FLOAT_EQ(of(0, 1), 2.0);
  EXPECT_FLOAT_EQ(of(1, 0), 3.0);
  EXPECT_FLOAT_EQ(of(1, 1), 4.0);
}

TEST(FramesTest, TestCopyToBufferNoFlip) {
  OrderedFrame<float, consts::LENGTH> of;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of.arr[i] = static_cast<float>(i);
  }

  float buffer[consts::LENGTH];
  // disable flip
  of.copy_to_buffer(buffer, false);

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(buffer[i], static_cast<float>(i));
  }
}

TEST(FramesTest, TestCopyToBufferFlip) {
  OrderedFrame<float, consts::LENGTH> of;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of.arr[i] = static_cast<float>(i);
  }

  float buffer[consts::LENGTH];
  of.copy_to_buffer(buffer, true);
  for (int y = 0; y < consts::FRAME_HEIGHT; y++) {
    for (int x = 0; x < consts::FRAME_WIDTH; x++) {
      EXPECT_FLOAT_EQ(
          buffer[y * consts::FRAME_WIDTH + x],
          static_cast<float>(
              (consts::FRAME_HEIGHT - 1 - y) * consts::FRAME_WIDTH + x));
    }
  }
}

TEST(FramesTest, TestCopyToBufferDoubleFilpInvariance) {
  OrderedFrame<float, consts::LENGTH> of;
  OrderedFrame<float, consts::LENGTH> of_flipped;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of.arr[i] = static_cast<float>(i);
  }

  float buffer[consts::LENGTH];
  // flip once
  of.copy_to_buffer(of_flipped.arr, true);
  // flip twice
  of_flipped.copy_to_buffer(buffer, true);
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(buffer[i], static_cast<float>(i));
  }
}

TEST(FramesTest, TestOperatorPlusEqual) {
  OrderedFrame<float, consts::LENGTH> of1;
  OrderedFrame<float, consts::LENGTH> of2;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of1.arr[i] = static_cast<float>(i);
    of2.arr[i] = static_cast<float>(i);
  }

  of1 += of2;

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(of1.arr[i], 2 * static_cast<float>(i));
  }
}

TEST(FramesTest, TestOperatorMinus) {
  OrderedFrame<float, consts::LENGTH> of1;
  OrderedFrame<float, consts::LENGTH> of2;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of1.arr[i] = static_cast<float>(i);
    of2.arr[i] = static_cast<float>(i);
  }

  OrderedFrame<float, consts::LENGTH> of3 = of1 - of2;

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(of3.arr[i], 0.0);
  }
}

TEST(FramesTest, TestOperatorMinusEqual) {
  OrderedFrame<float, consts::LENGTH> of1;
  OrderedFrame<float, consts::LENGTH> of2;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of1.arr[i] = static_cast<float>(i);
    of2.arr[i] = static_cast<float>(i);
  }

  of1 -= of2;

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(of1.arr[i], 0.0);
  }
}

TEST(FramesTest, TestAddClass) {
  OrderedFrame<float, consts::LENGTH> of;
  OrderedFrame<char, consts::LENGTH> classes;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of.arr[i] = static_cast<float>(i);
    classes.arr[i] = 1;
  }

  of.addClass(classes, 1);

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(of.arr[i], static_cast<float>(i + 1));
  }
}

TEST(FramesTest, TestAddClassWithDifferentClass) {
  OrderedFrame<float, consts::LENGTH> of;
  OrderedFrame<char, consts::LENGTH> classes;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    of.arr[i] = static_cast<float>(i);
    classes.arr[i] = 1;
  }

  of.addClass(classes, 2);

  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    EXPECT_FLOAT_EQ(of.arr[i], static_cast<float>(i));
  }
}

TEST(FramesTest, TestFill) {
  OrderedFrame<float, consts::LENGTH> of;
  of.fill(3.0);

  bool all_equal = false;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    all_equal = of.arr[i] == 3.0;
  }
  EXPECT_TRUE(all_equal);
}

TEST(FramesTest, TestZeroFill) {
  OrderedFrame<float, consts::LENGTH> of;
  of.fill(3.0);
  of.zero();

  bool all_zero = true;
  for (unsigned int i = 0; i < consts::LENGTH; i++) {
    all_zero = of.arr[i] == 0.0;
  }
  EXPECT_TRUE(all_zero);
}
