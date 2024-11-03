#include <gtest/gtest.h>

#include "../src/backend/FileWriter.hpp"
#include "../src/backend/Frames.hpp"
#include "../src/backend/HDFWriter.hpp"
#include <chrono>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fstream>

class HDFWriterTest : public testing::Test {
protected:
  FileWriter *file_writer_ptr;
  const std::chrono::time_point<std::chrono::system_clock> now
      = std::chrono::system_clock::now();
  const std::string folder_name = fmt::format("{:%Y%m%d}_run", now);

  void SetUp() { file_writer_ptr = new HDFWriter("/tmp"); };

  void TearDown() {
    std::filesystem::remove_all("/tmp/" + file_writer_ptr->session_directory);
    delete file_writer_ptr;
  };
};

TEST(HDFWriter, PickNewFileName) {
  const std::chrono::time_point<std::chrono::system_clock> now
      = std::chrono::system_clock::now();
  const std::string folder_name = fmt::format("{:%Y%m%d}_run", now);
  std::string session_folder = "/tmp/" + folder_name;
  std::filesystem::create_directory(session_folder);
  int probe_file_index = std::rand();
  auto probe_file_name
      = fmt::format("{:%Y%m%d}_run_{:06d}.h5", now, probe_file_index);

  std::fstream fs;
  fs.open("/tmp/" + folder_name + "/" + probe_file_name, std::ios::out);
  fs.close();

  FileWriter *file_writer_ptr = new HDFWriter("/tmp");
  EXPECT_EQ(file_writer_ptr->file_index, probe_file_index + 1);

  delete file_writer_ptr;
  std::filesystem::remove_all(session_folder);
}

TEST_F(HDFWriterTest, FolderCreation) {
  EXPECT_TRUE(std::filesystem::is_directory("/tmp/" + folder_name));
}

TEST_F(HDFWriterTest, FileCreation) {
  // check if files are created
  const unsigned int files_to_create = 10;
  for (unsigned int x = 0; x < files_to_create; x++) {
    file_writer_ptr->file_index = x;
    file_writer_ptr->openFile();
    file_writer_ptr->closeFile();
    auto file_name = fmt::format("{:%Y%m%d}_run_{:06d}.h5", now, x);
    std::filesystem::path full_file_path
        = "/tmp/" + folder_name + "/" + file_name;
    EXPECT_TRUE(std::filesystem::is_regular_file(full_file_path))
        << "File " << full_file_path << " not found";
  }
}

TEST_F(HDFWriterTest, FileWriteFrame) {
  // preparing frame filled with random value
  OrderedFrame<float, consts::LENGTH> frame;
  const float rand_val = std::rand();
  frame.fill(rand_val);

  // write frame to file
  file_writer_ptr->openFile();
  file_writer_ptr->writeFrame("group", "frame", frame);
  file_writer_ptr->closeFile();

  // read frame from file and compare values
  H5::H5File file("/tmp/" + folder_name + "/"
                      + fmt::format("{:%Y%m%d}_run_{:06d}.h5", now,
                                    file_writer_ptr->file_index),
                  H5F_ACC_RDONLY);
  H5::DataSet dataset = file.openDataSet("group/frame");
  H5::DataSpace dataspace = dataset.getSpace();
  hsize_t dims_out[2];
  dataspace.getSimpleExtentDims(dims_out, NULL);
  EXPECT_EQ(dims_out[0], consts::FRAME_HEIGHT);
  EXPECT_EQ(dims_out[1], consts::FRAME_WIDTH);
  float *data = new float[consts::LENGTH];
  dataset.read(data, H5::PredType::NATIVE_FLOAT);
  for (size_t x = 0; x < consts::LENGTH; x++) {
    EXPECT_FLOAT_EQ(data[x], rand_val);
  }
  delete[] data;
}

TEST_F(HDFWriterTest, FileWriteFloatFrameStack) {
  // allocate memory for frame stack
  const size_t frame_stack_length = 10;
  float *frame_stack = new float[frame_stack_length * consts::LENGTH];
  for (size_t x = 0; x < frame_stack_length * consts::LENGTH; x++) {
    frame_stack[x] = std::rand();
  }

  // write frame to file
  file_writer_ptr->openFile();
  file_writer_ptr->writeFrameStack("group", "frame_stack", frame_stack,
                                   frame_stack_length);
  file_writer_ptr->closeFile();

  // read frame from file and compare values
  H5::H5File file("/tmp/" + folder_name + "/"
                      + fmt::format("{:%Y%m%d}_run_{:06d}.h5", now,
                                    file_writer_ptr->file_index),
                  H5F_ACC_RDONLY);
  H5::DataSet dataset = file.openDataSet("group/frame_stack");
  H5::DataSpace dataspace = dataset.getSpace();
  hsize_t dims_out[3];
  dataspace.getSimpleExtentDims(dims_out, NULL);
  EXPECT_EQ(dims_out[0], frame_stack_length);
  EXPECT_EQ(dims_out[1], consts::FRAME_HEIGHT);
  EXPECT_EQ(dims_out[2], consts::FRAME_WIDTH);
  float *data = new float[frame_stack_length * consts::LENGTH];
  dataset.read(data, H5::PredType::NATIVE_FLOAT);
  for (size_t x = 0; x < frame_stack_length * consts::LENGTH; x++) {
    EXPECT_FLOAT_EQ(data[x], frame_stack[x]);
  }
  delete[] data;
}

TEST_F(HDFWriterTest, FileWriteCharFrameStack) {
  // allocate memory for frame stack
  const size_t frame_stack_length = 10;
  char *frame_stack = new char[frame_stack_length * consts::LENGTH];
  for (size_t x = 0; x < frame_stack_length * consts::LENGTH; x++) {
    frame_stack[x] = static_cast<char>(std::rand() / 256);
  }

  // write frame to file
  file_writer_ptr->openFile();
  file_writer_ptr->writeFrameStack("group", "frame_stack", frame_stack,
                                   frame_stack_length);
  file_writer_ptr->closeFile();

  // read frame from file and compare values
  H5::H5File file("/tmp/" + folder_name + "/"
                      + fmt::format("{:%Y%m%d}_run_{:06d}.h5", now,
                                    file_writer_ptr->file_index),
                  H5F_ACC_RDONLY);
  H5::DataSet dataset = file.openDataSet("group/frame_stack");
  H5::DataSpace dataspace = dataset.getSpace();
  hsize_t dims_out[3];
  dataspace.getSimpleExtentDims(dims_out, NULL);
  EXPECT_EQ(dims_out[0], frame_stack_length);
  EXPECT_EQ(dims_out[1], consts::FRAME_HEIGHT);
  EXPECT_EQ(dims_out[2], consts::FRAME_WIDTH);
  char *data = new char[frame_stack_length * consts::LENGTH];
  dataset.read(data, H5::PredType::NATIVE_CHAR);
  for (size_t x = 0; x < frame_stack_length * consts::LENGTH; x++) {
    EXPECT_EQ(data[x], frame_stack[x]);
  }
  delete[] data;
}
