#pragma once
#include <fmt/core.h>

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

#include "Frames.hpp"

/**
 * @brief Abstract class for writing frames to files.
 *
 */
class FileWriter {
public:
  /// Directory path (e.g. /home/user/)
  std::filesystem::path root_path;

  /// Session directory path (e.g. /home/user/20230825_run)
  std::string session_directory;

  /// Filename like 20230825_run
  std::string file_name;
  /// File index like 122
  int file_index;

  /**
   * @brief Construct a new File Writer object
   *
   */
  FileWriter() = default;
  /**
   * @brief Construct a new File Writer object
   *
   * @param root_path
   * @param file_index
   */
  FileWriter(std::filesystem::path root_path, int file_index)
      : root_path(root_path), file_index(file_index) {};
  virtual std::filesystem::path buildFullFilePath() = 0;
  virtual std::filesystem::path buildFullDirectoryPath() = 0;
  virtual ~FileWriter() = default;
  virtual void openFile() = 0;
  virtual void closeFile() = 0;
  /// @brief Generic method to write a frame to the file
  virtual void writeFrame(const std::string group_name,
                          const std::string frame_name,
                          OrderedFrame<float, consts::LENGTH> &frame)
      = 0;
  /// @brief Generic method to write a frame stack to the file
  virtual void writeFrameStack(const std::string group_name,
                               const std::string frame_stack_name,
                               float *frame_stack_ptr,
                               size_t frame_stack_length)
      = 0;
  virtual void writeFrameStack(const std::string group_name,
                               const std::string frame_stack_name,
                               char *frame_stack_ptr,
                               size_t frame_stack_length)
      = 0;
  virtual void writeFrameStack(const std::string group_name,
                               const std::string frame_stack_name,
                               unsigned short *frame_stack_ptr,
                               size_t frame_stack_length)
      = 0;
  virtual void write1DArray(const std::string group_name,
                            const std::string array_name, long *array,
                            size_t array_length)
      = 0;
};
