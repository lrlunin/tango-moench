#pragma once
#include <boost/asio/thread_pool.hpp>
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
  FileWriter *file_writer_ptr;
  float PEDESTAL_BUFFER_LENGTH;
  unsigned int THREAD_AMOUNT;
  std::atomic_bool threads_sleep = true;
  std::atomic_bool destroy_threads = false;
  std::atomic_bool destoy_dispatcher = false;
  std::vector<std::thread> threads;
  std::thread dispatcher_thread;
  boost::asio::thread_pool *thread_pool;
  std::string save_root_path, file_path, file_name;
  int max_frame_index = 0;
  std::atomic<float> counting_sigma = 4;
  std::atomic<long> file_index;
  size_t individual_frame_buffer_capacity = 300;

  std::shared_mutex pedestal_share;
  std::mutex frames_sums;
  std::atomic<long> processed_frames_amount{ 0 };

  CPUComputationBackend(FileWriter *file_writer_ptr,
                        float PEDESTAL_BUFFER_LENGTH,
                        unsigned long long THREAD_AMOUNT);
  CPUComputationBackend(FileWriter *file_writer_ptr);
  CPUComputationBackend() = default;
  ~CPUComputationBackend();
  void pause();
  void resume();
  /// @brief Allocate memory for all of the single frames storage
  void allocateIndividualStorage();
  /// @brief Delete memory for all of the single frames storage
  void deleteIndividualStorage();
  /// @brief Reset all of the accumulators
  void resetAccumulators();
  /// @brief Reset the pedestal and RMS accumulators
  void resetPedestalAndRMS();
  /// @brief Dump the sum frames to the file
  void dumpAccumulators();
  /**
   * @brief  The function calculates the \f$ \hat{p} \f$ pedestal and \f$
   * p_{\sigma} \f$ RMS values with the \f$ p_\Sigma= \f$ #pedestal_sum and \f$
   * p_{\Sigma}^2= \f$ #pedestal_squared_sum
   * @param pedestal the pedestal values
   * @param pedestal_rms the pedestal RMS values
   */
  void loadPedestalAndRMS(OrderedFrame<float, consts::LENGTH> &pedestal,
                          OrderedFrame<float, consts::LENGTH> &pedestal_rms);
  /**
   * @brief Classify the pixels of the frame in types
   *
   * @param input frame to classify
   * @param pedestal_rms the \f$ p_{\sigma} \f$ RMS values (see
   * #loadPedestalAndRMS())
   * @return OrderedFrame<char, consts::LENGTH> the classes of pixel in frame
   */
  OrderedFrame<char, consts::LENGTH>
  classifyFrame(OrderedFrame<float, consts::LENGTH> &input,
                OrderedFrame<float, consts::LENGTH> &pedestal_rms);
  /**
   * @brief Update the pedestal moving average #pedestal_sum and
   * #pedestal_squared_sum
   *
   * @param raw_frame unprocessed frame (no pedestal subtraction etc)
   * @param frame_classes pixel classes (see #classifyFrame())
   * @param isPedestal if the frame is pedestal frame
   */
  void updatePedestalMovingAverage(
      OrderedFrame<unsigned short, consts::LENGTH> &raw_frame,
      OrderedFrame<char, consts::LENGTH> &frame_classes, bool isPedestal);
  /// @brief Dispatch the tasks to the thread pool
  void dispatchTasks();
  /// @brief  Process the #FullFrame
  /// @param ptr pointer to the #FullFrame structure
  void processFrame(FullFrame *ptr);

  OrderedFrame<float, consts::LENGTH> pedestal_counter_counting;
  OrderedFrame<float, consts::LENGTH> pedestal_sum_counting;
  OrderedFrame<float, consts::LENGTH> pedestal_squared_sum_counting;

  OrderedFrame<float, consts::LENGTH> pedestal_counter;
  /// @brief Sum of the pedestal values
  OrderedFrame<float, consts::LENGTH> pedestal_sum;
  /// @brief Sum of the squared pedestal values
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
  std::atomic_bool saveRawFrames = true;
  long *frameindex_storage_ptr = nullptr;
  float *individual_analog_storage_ptr = nullptr;
  unsigned short *individual_raw_storage_ptr = nullptr;
#ifdef SINGLE_FRAMES_DEBUG
  float *pedestal_storage_ptr = nullptr;
  float *pedestal_rms_storage_ptr = nullptr;
  char *frame_classes_storage_ptr = nullptr;
#endif
};
