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
protected:
  /// File extension (e.g. h5)
  std::string file_extension;

public:
  /// Directory path (e.g. /home/user/)
  std::filesystem::path root_path;

  /// Session directory path (e.g. /home/user/20230825_run)
  std::string session_directory;

  /// Filename like 20230825_run
  std::string file_name;
  /// File index like 122
  int file_index;

  /// Format string like {file_name}_{file_index:06d}.h5 with file_name and
  /// file_index as arguments as constexpr
  const std::string file_format;

  /// RegEx to match file names like 20230825_run_122.h5
  const std::regex file_match;
  /**
   * @brief Construct a new File Writer object
   *
   */
  FileWriter();
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
  /**
   * @brief Write a single frame to the file.
   *
   * @param group_name Group name in the HDF5 file (e.g. /data)
   * @param frame_name Frame name in the HDF5 file (e.g. /data/averaged_frame)
   * @param frame Frame to write into the file
   */
  virtual void writeFrame(const std::string group_name,
                          const std::string frame_name,
                          OrderedFrame<float, consts::LENGTH> &frame)
      = 0;
  /**
   * @brief Write a stack of frames to the file.
   *
   * @param group_name Group name in the HDF5 file (e.g. /data)
   * @param frame_name Frame stack name in the HDF5 file (e.g.
   * /data/individual_frames)
   * @param frame_stack_ptr Pointer to the T[] frame stack of the length
   * frame_stack_length * consts::HEIGHT * consts::WIDTH
   * @param frame_stack_length Length of the frame stack to write. Should be
   * less than or equal to the length of the frame stack array.
   */
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
};
