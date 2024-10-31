#include <gtest/gtest.h>

#include "../src/backend/CPUComputationBackend.hpp"
#include "../src/backend/FileWriter.hpp"
#include "../src/backend/HDFWriter.hpp"

TEST(MoenchZMQTest, TypeAssertions) {
  std::unique_ptr<FileWriter> file_writer_ptr = std::make_unique<HDFWriter>("/tmp");
  
  std::unique_ptr<CPUComputationBackend> computation_backend_ptr = std::make_unique<CPUComputationBackend>(file_writer_ptr.get());
  EXPECT_GT(computation_backend_ptr->THREAD_AMOUNT, 0);
}