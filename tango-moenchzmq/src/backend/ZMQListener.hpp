#pragma once
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <sls/ZmqSocket.h>

#include <algorithm>
#include <boost/lockfree/queue.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <condition_variable>
#include <queue>
#include <shared_mutex>
#include <string>
#include <syncstream>
#include <thread>
#include <tuple>
#include <vector>
#include <zmq.hpp>

#include "CPUComputationBackend.hpp"

class ZMQListener {
private:
  zmq::context_t context;
  zmq::socket_t socket;
  std::thread zmq_listener_thread;
  std::atomic_bool receive_data;
  std::atomic_bool abort_wait;
  constexpr static size_t FRAME_SIZE = sizeof(FullFrame::f.arr);

public:
  CPUComputationBackend *comp_backend_ptr;
  std::atomic<long> received_frames_amount;
  ZMQListener(std::string socket_addr, unsigned long long socket_port);
  void listen_socket();
  void start_receive();
  void stop_receive();
  void abort_receive();
};
