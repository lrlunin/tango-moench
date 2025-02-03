#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/FileWriter.hpp"
#include "../src/backend/Frames.hpp"
#include "../src/backend/ZMQListener.hpp"
#include <fmt/core.h>
#include <numeric>
#include <zmq.hpp>

using namespace std;

class ZMQPublisher {
protected:
  const std::string json_header = "{{\"data\":{data:d},\"bitmode\":{bitmode:d}"
                                  ", \"frameIndex\":{frameIndex:d}}}";
  zmq::context_t context;
  zmq::socket_t socket;

public:
  int port;

  ZMQPublisher(std::string socket_addr) {
    context = zmq::context_t(1);
    socket = zmq::socket_t(context, ZMQ_PUB);
    for (int p = 10000; p < 65535; p++) {
      std::string full_address = socket_addr + ":" + std::to_string(p);
      try {
        socket.bind(full_address.c_str());
        port = p;
        break;
      } catch (zmq::error_t &e) {
        continue;
      }
    }
  }

  ~ZMQPublisher() {
    socket.close();
    context.close();
  }

  void send_frame_with_header(unsigned long long frame_index,
                              unsigned int data) {
    send_header(frame_index, data);
    if (data)
      send_frame();
  }

  void send_frame() {
    zmq::message_t message(sizeof(FullFrame::f.arr));
    std::memset(message.data(), 1, sizeof(FullFrame::f.arr));
    socket.send(message, zmq::send_flags::none);
  }

  void send_header(unsigned long long frame_index, unsigned int data) {
    std::string ready_json = fmt::format(
        fmt::runtime(json_header), fmt::arg("data", data),
        fmt::arg("bitmode", 16), fmt::arg("frameIndex", frame_index));
    zmq::message_t message(ready_json.size());
    std::memcpy(message.data(), ready_json.c_str(), ready_json.size());
    socket.send(message, zmq::send_flags::none);
  }
};

class MockFileWriter : public FileWriter {
public:
  MOCK_METHOD(std::filesystem::path, buildFullFilePath, (), (override));
  MOCK_METHOD(std::filesystem::path, buildFullDirectoryPath, (), (override));
  MOCK_METHOD(void, openFile, (), (override));
  MOCK_METHOD(void, closeFile, (), (override));
  MOCK_METHOD(void, writeFrame,
              (const std::string group_name, const std::string frame_name,
               (OrderedFrame<float, consts::LENGTH> & frame)),
              (override));
  MOCK_METHOD(void, writeFrameStack,
              (const std::string group_name,
               const std::string frame_stack_name, float *frame_stack_ptr,
               size_t frame_stack_length),
              (override));
  MOCK_METHOD(void, writeFrameStack,
              (const std::string group_name,
               const std::string frame_stack_name, char *frame_stack_ptr,
               size_t frame_stack_length),
              (override));
  MOCK_METHOD(void, writeFrameStack,
              (const std::string group_name,
               const std::string frame_stack_name,
               unsigned short *frame_stack_ptr, size_t frame_stack_length),
              (override));
  MOCK_METHOD(void, write1DArray,
              (const std::string group_name, const std::string array_name,
               long *array, size_t array_length),
              (override));
};

class ZMQListenerTest : public testing::Test {
protected:
  ZMQListener *zmq_listener_ptr;
  ZMQPublisher *zmq_publisher_ptr;
  CPUComputationBackend *comp_backend_ptr;
  MockFileWriter mock_file_writer;

  void SetUp() {
    zmq_publisher_ptr = new ZMQPublisher("tcp://127.0.0.1");
    std::this_thread::sleep_for(150ms);
    comp_backend_ptr = new CPUComputationBackend(&mock_file_writer, 100, 1);
    zmq_listener_ptr = new ZMQListener("127.0.0.1", zmq_publisher_ptr->port);
    zmq_listener_ptr->comp_backend_ptr = comp_backend_ptr;
    std::this_thread::sleep_for(150ms);
  }

  void TearDown() {
    delete zmq_publisher_ptr;
    delete zmq_listener_ptr;
    delete comp_backend_ptr;
  }
};

TEST(ZMQListener, NoTCPPrefixConstructor) {
  ZMQPublisher *zmq_publisher_ptr = new ZMQPublisher("tcp://127.0.0.1");
  ZMQListener *zmq_listener_ptr
      = new ZMQListener("127.0.0.1", zmq_publisher_ptr->port);
  delete zmq_listener_ptr;
  delete zmq_publisher_ptr;
}

TEST(ZMQListener, TCPPrefixConstructor) {
  ZMQPublisher *zmq_publisher_ptr = new ZMQPublisher("tcp://127.0.0.1");
  ZMQListener *zmq_listener_ptr
      = new ZMQListener("tcp://127.0.0.1", zmq_publisher_ptr->port);
  delete zmq_listener_ptr;
  delete zmq_publisher_ptr;
}

TEST_F(ZMQListenerTest, ReceiveOneFrame) {
  zmq_listener_ptr->start_receive();
  zmq_publisher_ptr->send_frame_with_header(0, true);
  std::this_thread::sleep_for(300ms);
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, 1);
}

TEST_F(ZMQListenerTest, ReceiveNFrames) {
  const int N = 10;
  zmq_listener_ptr->start_receive();
  for (int i = 0; i < N; i++) {
    zmq_publisher_ptr->send_frame_with_header(i, true);
  }
  std::this_thread::sleep_for(300ms);
  zmq_listener_ptr->stop_receive();
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, N);
}

TEST_F(ZMQListenerTest, ReceiveNWithDummyFrames) {
  const int N = 20;
  zmq_listener_ptr->start_receive();
  for (int i = 0; i < N; i++) {
    zmq_publisher_ptr->send_frame_with_header(i, i % 2 == 0);
  }
  std::this_thread::sleep_for(300ms);
  zmq_listener_ptr->stop_receive();
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, N / 2);
}

TEST_F(ZMQListenerTest, ReceiveOneFrameNoData) {
  zmq_listener_ptr->start_receive();
  zmq_publisher_ptr->send_frame_with_header(0, false);
  std::this_thread::sleep_for(300ms);
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, 0);
}

TEST_F(ZMQListenerTest, ReceiveOneFrameStop) {
  zmq_listener_ptr->start_receive();
  zmq_publisher_ptr->send_frame_with_header(0, true);
  std::this_thread::sleep_for(300ms);
  zmq_listener_ptr->stop_receive();
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, 1);
  zmq_publisher_ptr->send_frame_with_header(1, true);
  std::this_thread::sleep_for(300ms);
  EXPECT_EQ(zmq_listener_ptr->received_frames_amount, 1);
}
