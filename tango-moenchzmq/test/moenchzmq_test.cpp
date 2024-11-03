#include <gtest/gtest.h>

#include "../src/backend/CPUComputationBackend.hpp"
#include "../src/backend/FileWriter.hpp"
#include "../src/backend/Frames.hpp"
#include "../src/backend/HDFWriter.hpp"
#include <random>
#include <thread>

class MoenchZMQTest : public testing::Test {
protected:
  FileWriter *file_writer_ptr;
  CPUComputationBackend *computation_backend_ptr;
  const unsigned int PEDESTAL_BUFFER_LENGTH = 110;

  void SetUp() {
    file_writer_ptr = new HDFWriter("/tmp");
    int hardware_threads = std::thread::hardware_concurrency();
    computation_backend_ptr
        = new CPUComputationBackend(file_writer_ptr, PEDESTAL_BUFFER_LENGTH,
                                    std::min(1, hardware_threads));
  };

  void TearDown() {
    std::filesystem::remove_all("/tmp/" + file_writer_ptr->session_directory);
    delete file_writer_ptr;
    delete computation_backend_ptr;
  };
};

TEST_F(MoenchZMQTest, TestPauseAndResume) {
  const unsigned int frames = 10;
  computation_backend_ptr->pause();
  EXPECT_TRUE(computation_backend_ptr->threads_sleep);
  for (unsigned int i = 0; i < frames; i++) {
    FullFrame *ff_ptr = static_cast<FullFrame *>(
        CPUComputationBackend::memory_pool::malloc());
    ff_ptr->m.frameIndex = static_cast<int>(i);
    ff_ptr->m.bitmode = 16;
    for (unsigned int j = 0; j < consts::LENGTH; j++) {
      ff_ptr->f.arr[j] = 0.0;
    }
    computation_backend_ptr->frame_ptr_queue.push(ff_ptr);
  }
  EXPECT_TRUE(computation_backend_ptr->threads_sleep);
  EXPECT_EQ(computation_backend_ptr->processed_frames_amount, 0);
  computation_backend_ptr->resume();

  while (computation_backend_ptr->processed_frames_amount < frames) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  EXPECT_EQ(computation_backend_ptr->processed_frames_amount, frames);
}

TEST_F(MoenchZMQTest, ConstMovingAverageAndRMS) {
  const unsigned int frames = 30;
  const float pedestal_average = 5400.0;

  computation_backend_ptr->resetPedestalAndRMS();
  computation_backend_ptr->resume();
  for (unsigned int i = 0; i < frames; i++) {
    FullFrame *ff_ptr = static_cast<FullFrame *>(
        CPUComputationBackend::memory_pool::malloc());
    ff_ptr->m.frameIndex = static_cast<int>(i);
    ff_ptr->m.bitmode = 16;
    for (unsigned int j = 0; j < consts::LENGTH; j++) {
      ff_ptr->f.arr[j] = pedestal_average;
    }
    computation_backend_ptr->frame_ptr_queue.push(ff_ptr);
  }
  while (computation_backend_ptr->processed_frames_amount < frames) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  OrderedFrame<float, consts::LENGTH> pedestal;
  OrderedFrame<float, consts::LENGTH> pedestal_rms;
  computation_backend_ptr->loadPedestalAndRMS(pedestal, pedestal_rms);

  EXPECT_FLOAT_EQ(computation_backend_ptr->pedestal_counter_counting.arr[0],
                  frames);
  EXPECT_FLOAT_EQ(pedestal.arr[0], pedestal_average);
  EXPECT_FLOAT_EQ(pedestal_rms.arr[0], 0.0f);
}

TEST_F(MoenchZMQTest, GaussianMovingAverageAndRMSLessThenBufferLength) {
  const unsigned int frames = PEDESTAL_BUFFER_LENGTH - 10;
  const float pedestal_average_target = 5400.0;
  const float pedestal_rms_target = 17.0;

  std::random_device rd{};
  std::mt19937 gen{ rd() };
  std::normal_distribution<float> d{ pedestal_average_target,
                                     pedestal_rms_target };

  auto get_normal = [&d, &gen] { return d(gen); };

  computation_backend_ptr->resetPedestalAndRMS();
  computation_backend_ptr->resume();
  for (unsigned int i = 0; i < frames; i++) {
    FullFrame *ff_ptr = static_cast<FullFrame *>(
        CPUComputationBackend::memory_pool::malloc());
    ff_ptr->m.frameIndex = static_cast<int>(i);
    ff_ptr->m.bitmode = 16;
    for (unsigned int j = 0; j < consts::LENGTH; j++) {
      ff_ptr->f.arr[j] = get_normal();
    }
    computation_backend_ptr->frame_ptr_queue.push(ff_ptr);
  }
  while (computation_backend_ptr->processed_frames_amount < frames) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  OrderedFrame<float, consts::LENGTH> pedestal;
  OrderedFrame<float, consts::LENGTH> pedestal_rms;
  computation_backend_ptr->loadPedestalAndRMS(pedestal, pedestal_rms);
  EXPECT_FLOAT_EQ(computation_backend_ptr->pedestal_counter_counting.arr[0],
                  std::min(PEDESTAL_BUFFER_LENGTH, frames));

  // needs to be checked with the samping variance formula
  float sigma_sampling = 1. / std::sqrt(frames);

  float resulted_rms = pedestal_rms.arr[0];
  ASSERT_NEAR(resulted_rms, pedestal_rms_target,
              3 * sigma_sampling * pedestal_rms_target);
  EXPECT_NEAR(pedestal.arr[0], pedestal_average_target, 3 * resulted_rms);
}

TEST_F(MoenchZMQTest, GaussianMovingAverageAndRMSGreaterThenBufferLength) {
  const unsigned int frames = PEDESTAL_BUFFER_LENGTH + 10;
  const float pedestal_average_target = 5400.0;
  const float pedestal_rms_target = 17.0;

  std::random_device rd{};
  std::mt19937 gen{ rd() };
  std::normal_distribution<float> d{ pedestal_average_target,
                                     pedestal_rms_target };

  auto get_normal = [&d, &gen] { return d(gen); };

  computation_backend_ptr->resetPedestalAndRMS();
  computation_backend_ptr->resume();
  for (unsigned int i = 0; i < frames; i++) {
    FullFrame *ff_ptr = static_cast<FullFrame *>(
        CPUComputationBackend::memory_pool::malloc());
    ff_ptr->m.frameIndex = static_cast<int>(i);
    ff_ptr->m.bitmode = 16;
    for (unsigned int j = 0; j < consts::LENGTH; j++) {
      ff_ptr->f.arr[j] = get_normal();
    }
    computation_backend_ptr->frame_ptr_queue.push(ff_ptr);
  }
  while (computation_backend_ptr->processed_frames_amount < frames) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  OrderedFrame<float, consts::LENGTH> pedestal;
  OrderedFrame<float, consts::LENGTH> pedestal_rms;
  computation_backend_ptr->loadPedestalAndRMS(pedestal, pedestal_rms);
  EXPECT_FLOAT_EQ(computation_backend_ptr->pedestal_counter_counting.arr[0],
                  std::min(PEDESTAL_BUFFER_LENGTH, frames));

  // needs to be checked with the samping variance formula
  float sigma_sampling = 1. / std::sqrt(frames);

  float resulted_rms = pedestal_rms.arr[0];
  ASSERT_NEAR(resulted_rms, pedestal_rms_target,
              3 * sigma_sampling * pedestal_rms_target);
  EXPECT_NEAR(pedestal.arr[0], pedestal_average_target, 3 * resulted_rms);
}

TEST_F(MoenchZMQTest, DefaultContructor) {
  EXPECT_GT(computation_backend_ptr->THREAD_AMOUNT, 0);
}
