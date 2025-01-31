#include "ZMQListener.hpp"
#include <chrono>
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
  zmq_listener_thread = std::thread(&ZMQListener::listen_socket, this);
}

ZMQListener::~ZMQListener() {
  stop_receive();
  abort_receive();
  abort_listen = true;
  if (zmq_listener_thread.joinable()) {
    zmq_listener_thread.join();
  }
  socket.close();
}

void ZMQListener::listen_socket() {
  zmq::message_t json_zmq_msg, data_zmq_msg;
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> d;
  while (!abort_listen) {
    if (socket.recv(json_zmq_msg)) {
      if (d.Parse(static_cast<char *>(json_zmq_msg.data()),
                  json_zmq_msg.size())
              .HasParseError()) {
        continue;
      };
      std::cout << "Received json, frameindex: " << d["frameIndex"].GetUint64()
                << " nextData " << (d["data"].GetUint() == 1) << std::endl;
    }
    if (d["data"].GetUint() == 1) {
      std::cout << "Received data" << std::endl;
      if (socket.recv(data_zmq_msg) && receive_data) {
        // if data is not a full frame, skip it
        if (data_zmq_msg.size() < FRAME_SIZE) {
          continue;
        }
        FullFrame *ff_ptr = static_cast<FullFrame *>(
            CPUComputationBackend::memory_pool::malloc());
        ff_ptr->m.frameIndex = d["frameIndex"].GetUint64();
        ff_ptr->m.bitmode = d["bitmode"].GetUint();
        std::memcpy(ff_ptr->f.arr, data_zmq_msg.data(), FRAME_SIZE);
        comp_backend_ptr->frame_ptr_queue.push(ff_ptr);
        received_frames_amount++;
      }
    };
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
      this_thread::sleep_for(0.25s);
    }
    abort_wait = false;
    comp_backend_ptr->pause();
    // save data etc
    comp_backend_ptr->dumpAccumulators();
    comp_backend_ptr->fileWriter->file_index++;
  }
}

void ZMQListener::abort_receive() { abort_wait = true; }
