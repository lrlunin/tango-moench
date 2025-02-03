#include "ZMQListener.hpp"
// #include <chrono>
#include <iostream>
#include <numeric>
#include <thread>

using namespace std;

ZMQListener::ZMQListener(std::string socket_addr,
                         unsigned long long socket_port) {
  if (!socket_addr.starts_with("tcp://")) {
    socket_addr = "tcp://" + socket_addr;
  }
  std::string full_address = socket_addr + ":" + std::to_string(socket_port);
  context = zmq::context_t(1);
  socket = zmq::socket_t(context, ZMQ_SUB);
  socket.connect(full_address.c_str());
  socket.set(zmq::sockopt::subscribe, "");
  receive_data = false;
  abort_wait = false;
  abort_listen = false;
  zmq_listener_thread = std::thread(&ZMQListener::listen_socket, this);
}

ZMQListener::~ZMQListener() {
  stop_receive();
  abort_receive();
  abort_listen = true;
  if (zmq_listener_thread.joinable())
    zmq_listener_thread.join();
  socket.close();
  context.close();
}

void ZMQListener::listen_socket() {
  bool next_json = true;
  zmq::message_t zmq_message;
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> rj;
  while (!abort_listen) {
    if (socket.recv(zmq_message, zmq::recv_flags::dontwait)) {
      if (next_json) {
        if (rj.Parse(static_cast<char *>(zmq_message.data()),
                     zmq_message.size())
                .HasParseError())
          continue;
        if (rj["data"].GetUint() == 1)
          next_json = false;
      } else {
        next_json = true;
        if (receive_data && zmq_message.size() == FRAME_SIZE) {
          FullFrame *ff_ptr = static_cast<FullFrame *>(
              CPUComputationBackend::memory_pool::malloc());
          ff_ptr->m.frameIndex = rj["frameIndex"].GetUint64();
          ff_ptr->m.bitmode = rj["bitmode"].GetUint();
          std::memcpy(ff_ptr->f.arr, zmq_message.data(), FRAME_SIZE);
          comp_backend_ptr->frame_ptr_queue.push(ff_ptr);
          received_frames_amount++;
        }
      }
    } else
      this_thread::sleep_for(5ms);
  }
}

void ZMQListener::start_receive() {
  if (!receive_data) {
    received_frames_amount = 0;
    comp_backend_ptr->processed_frames_amount = 0;
    comp_backend_ptr->resetAccumulators();
    comp_backend_ptr->resume();
    receive_data = true;
  }
}

void ZMQListener::stop_receive() {
  if (receive_data) {
    receive_data = false;
    while (comp_backend_ptr->processed_frames_amount < received_frames_amount
           && !abort_wait) {
      this_thread::sleep_for(10ms);
    }
    abort_wait = false;
    comp_backend_ptr->pause();
    // save data etc
    comp_backend_ptr->dumpAccumulators();
    comp_backend_ptr->file_writer_ptr->file_index++;
  }
}

void ZMQListener::abort_receive() { abort_wait = true; }
