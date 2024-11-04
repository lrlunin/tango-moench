#pragma once
#include <boost/lockfree/queue.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <filesystem>
#include <shared_mutex>
#include <thread>
#include <vector>

#include "FileWriter.hpp"
#include "Frames.hpp"

class CPUComputationBackend {
public:
  typedef boost::singleton_pool<FullFrame, sizeof(FullFrame)> memory_pool;
  boost::lockfree::queue<FullFrame *> frame_ptr_queue;
  FileWriter *fileWriter;
  const float PEDESTAL_BUFFER_LENGTH;
  const unsigned int THREAD_AMOUNT;
  std::atomic_bool threads_sleep = true;
  std::atomic_bool destroy_threads = false;
  std::vector<std::thread> threads;
  std::string save_root_path, file_path, file_name;
  int max_frame_index = 0;
  std::atomic<float> counting_sigma = 4;
  std::atomic<long> file_index;
  size_t individual_frame_buffer_capacity = 300;

  std::shared_mutex pedestal_share;
  std::mutex frames_sums;
  std::atomic<long> processed_frames_amount{ 0 };

  CPUComputationBackend(FileWriter *fileWriter, float PEDESTAL_BUFFER_LENGTH,
                        unsigned int THREAD_AMOUNT);
  CPUComputationBackend(FileWriter *fileWriter);
  ~CPUComputationBackend();
  void initThreads();
  void destroyThreads();
  void pause();
  void resume();
  void allocateIndividualStorage();
  void resetAccumulators();
  void resetPedestalAndRMS();
  void dumpAccumulators();
  void loadPedestalAndRMS(OrderedFrame<float, consts::LENGTH> &pedestal,
                          OrderedFrame<float, consts::LENGTH> &pedestal_rms);
  OrderedFrame<char, consts::LENGTH>
  classifyFrame(OrderedFrame<float, consts::LENGTH> &input,
                OrderedFrame<float, consts::LENGTH> &pedestal_rms);
  void updatePedestalMovingAverage(
      OrderedFrame<unsigned short, consts::LENGTH> &raw_frame,
      OrderedFrame<char, consts::LENGTH> &frame_classes, bool isPedestal);
  void threadTask();
  void processFrame(FullFrame *ptr);

  OrderedFrame<float, consts::LENGTH> pedestal_counter_counting;
  OrderedFrame<float, consts::LENGTH> pedestal_sum_counting;
  OrderedFrame<float, consts::LENGTH> pedestal_squared_sum_counting;

  OrderedFrame<float, consts::LENGTH> pedestal_counter;
  OrderedFrame<float, consts::LENGTH> pedestal_sum;
  OrderedFrame<float, consts::LENGTH> pedestal_squared_sum;

  OrderedFrame<float, consts::LENGTH> analog_sum;
  OrderedFrame<float, consts::LENGTH> analog_sum_pumped;
  OrderedFrame<float, consts::LENGTH> thresholded_sum;
  OrderedFrame<float, consts::LENGTH> thresholded_sum_pumped;
  OrderedFrame<float, consts::LENGTH> counting_sum;
  OrderedFrame<int, consts::LENGTH> counting_sum_pumped;
  std::atomic_bool isSplitPumped = false;
  std::atomic_bool isPedestal = true;
  long updatePedestalPeriod = 1;
  std::atomic_bool saveIndividualFrames = true;
  int *frameindex_storage_ptr = nullptr;
  float *individual_analog_storage_ptr = nullptr;
#ifdef SINGLE_FRAMES_DEBUG
  float *pedestal_storage_ptr = nullptr;
  float *pedestal_rms_storage_ptr = nullptr;
  char *frame_classes_storage_ptr = nullptr;
#endif
};
