#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/FileWriter.hpp"
#include "../src/backend/Frames.hpp"
#include "../src/backend/ZMQListener.hpp"
#include <chrono>
#include <fmt/core.h>
#include <zmq.hpp>

/*
class ZMQPublisher {
protected:
    const std::string json_header = std::string("{\"data\":{data:d},
\"bitmode\":{bitmode:d}, \"frameIndex\":{frameIndex:d}}"); public:
  zmq::context_t context;
  zmq::socket_t socket;
  ZMQPublisher(std::string socket_addr, unsigned long long socket_port) {
    if (!socket_addr.starts_with("tcp://")) {
      socket_addr = "tcp://" + socket_addr;
    }
    std::string full_address = socket_addr + ":" + std::to_string(socket_port);
    context = zmq::context_t(1);
    socket = zmq::socket_t(context, ZMQ_PUB);
    socket.bind(full_address.c_str());
  }
  ~ZMQPublisher() {
    socket.close();
  }

  void send_frame_with_header(unsigned long long frame_index, bool data) {
    send_header(frame_index, data);
    if (data) send_frame();
  }

  void send_frame() {
    OrderedFrame<unsigned short, consts::LENGTH> frame;
    frame.fill(0);
    zmq::message_t message(sizeof(frame));
    std::memcpy(message.data(), frame.arr, sizeof(frame));
    socket.send(message);
  }

  void send_header(unsigned long long frame_index, bool data) {
    std::string ready_json = fmt::format(fmt::runtime(json_header),
                                fmt::arg("data", (unsigned int)data),
                                fmt::arg("bitmode", 16),
                                fmt::arg("frameIndex", frame_index));
    zmq::message_t message(ready_json.size());
    std::memcpy(message.data(), ready_json.c_str(), ready_json.size());
    socket.send(message);
  }
};

class MockFileWriter : public FileWriter {
public:
    MOCK_METHOD(std::filesystem::path, buildFullFilePath, (), (override));
    MOCK_METHOD(std::filesystem::path, buildFullDirectoryPath, (), (override));
    MOCK_METHOD(void, openFile, (), (override));
    MOCK_METHOD(void, closeFile, (), (override));
    MOCK_METHOD(void, writeFrame, (const std::string group_name, const
std::string frame_name, (OrderedFrame<float, consts::LENGTH> &frame)),
(override)); MOCK_METHOD(void, writeFrameStack, (const std::string group_name,
const std::string frame_stack_name, float *frame_stack_ptr, size_t
frame_stack_length), (override)); MOCK_METHOD(void, writeFrameStack, (const
std::string group_name, const std::string frame_stack_name, char
*frame_stack_ptr, size_t frame_stack_length), (override)); MOCK_METHOD(void,
writeFrameStack, (const std::string group_name, const std::string
frame_stack_name, unsigned short *frame_stack_ptr, size_t frame_stack_length),
(override)); MOCK_METHOD(void, write1DArray, (const std::string group_name,
const std::string array_name, long *array, size_t array_length), (override));
};

class MockCPUComputationBackend : public CPUComputationBackend {
public:
  MOCK_METHOD(void, pause, ());
  MOCK_METHOD(void, resume, ());
  MOCK_METHOD(void, dumpAccumulators, ());
  MOCK_METHOD(void, allocateIndividualStorage, ());
};

class ZMQListenerTest : public testing::Test {
protected:
  ZMQListener *zmq_listener_ptr;
  ZMQPublisher *zmq_publisher_ptr;
  MockFileWriter filewriter;
  MockCPUComputationBackend fi;

  void SetUp() override {
    zmq_publisher_ptr = new ZMQPublisher("127.0.0.1", 5555);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    zmq_listener_ptr = new ZMQListener("127.0.0.1", 5555);
    zmq_listener_ptr->comp_backend_ptr = &fi;
  }

  void TearDown() override {
    delete zmq_listener_ptr;
    delete zmq_publisher_ptr;
  }
};
*/
TEST(ZMQListener, NoTCPPrefixConstructor) {
  ZMQListener *zmq_listener_ptr = new ZMQListener("127.0.0.1", 5555);
  delete zmq_listener_ptr;
}

TEST(ZMQListener, TCPPrefixConstructor) {
  ZMQListener *zmq_listener_ptr = new ZMQListener("tcp://127.0.0.1", 5555);
  delete zmq_listener_ptr;
}

/*
TEST_F(ZMQListenerTest, StartReceive) {
  zmq_listener_ptr->start_receive();
}

TEST_F(ZMQListenerTest, StopReceive) {
  zmq_listener_ptr->stop_receive();
}

TEST_F(ZMQListenerTest, AbortReceive) {
  zmq_listener_ptr->abort_receive();
}
*/
