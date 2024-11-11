#pragma once
#include <H5Cpp.h>
#include <fmt/core.h>

#include <filesystem>
#include <regex>
#include <string>

#include "FileWriter.hpp"
#include "Frames.hpp"

class HDFWriter : public FileWriter {
private:
  /// File extension (e.g. h5)
  static constexpr char file_extension[] = "h5";
  /// HDF5 file object
  H5::H5File current_file;
  /**
   * @brief format string like {file_name}_{file_index:06d}.h5 with file_name
   * and file_index as arguments as constexpr
   *
   */
  const std::string file_format
      = std::string("{file_name}_{file_index:06d}.") + file_extension;
  /// regex to match file names like 20230825_run_122.h5
  const std::regex file_match
      = std::regex(std::string("^\\w+_(\\d+)\\.") + file_extension);

protected:
  /**
   * @brief Build the full file path (e.g.
   * /home/user/20230825_run/20230825_run_122.h5)
   *
   * @return std::filesystem::path
   */
  std::filesystem::path buildFullFilePath() override;
  /**
   * @brief Build the full directory path (e.g. /home/user/20230825_run)
   *
   * @return std::filesystem::path
   */
  std::filesystem::path buildFullDirectoryPath() override;

public:
  HDFWriter(std::filesystem::path root_path);
  HDFWriter(std::filesystem::path root_path, int file_index);
  ~HDFWriter();
  void openFile() override;
  void closeFile() override;
  void writeFrame(const std::string group_name, const std::string frame_name,
                  OrderedFrame<float, consts::LENGTH> &frame) override;
  void writeFrameStack(const std::string group_name,
                       const std::string frame_stack_name,
                       float *frame_stack_ptr,
                       size_t frame_stack_length) override;
  void writeFrameStack(const std::string group_name,
                       const std::string frame_stack_name,
                       char *frame_stack_ptr,
                       size_t frame_stack_length) override;
  void writeFrameStack(const std::string group_name,
                       const std::string frame_stack_name,
                       unsigned short *frame_stack_ptr,
                       size_t frame_stack_length) override;
  void write1DArray(const std::string group_name, const std::string array_name,
                    int *array_ptr, size_t array_length) override;
};
