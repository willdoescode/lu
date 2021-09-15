#pragma once

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <filesystem>
#include <sstream>
#include <string>

#include "style.hpp"

namespace fs = std::filesystem;

struct PType {
 private:
  std::string modified_time;
  char letter;
  std::string color;
  std::string filename;
  std::string filepath;
  struct stat fileinfo;
  std::string pw;
  std::string gr;
  bool is_dir;

 public:
  inline bool operator<(const PType& f2) {
    if (this->get_dir() && !f2.get_dir())
      return true;
    else if (!this->get_dir() && f2.get_dir())
      return false;
    else {
      return this->get_filepath() < f2.get_filepath();
    }
  }

  inline bool get_dir() const noexcept { return this->is_dir; }

  inline const std::string& get_color() const noexcept { return this->color; }

  inline char get_leter() const noexcept { return this->letter; }

  inline const std::string& get_filepath() const noexcept {
    return this->filepath;
  }

  inline const std::string& get_filename() const noexcept {
    return this->filename;
  }

  inline const struct stat get_fileinfo() const noexcept {
    return this->fileinfo;
  }

  inline const std::string& get_filepw() const noexcept { return this->pw; }

  inline const std::string& get_filegr() const noexcept { return this->gr; }

  inline const std::string& get_modified_time() const noexcept {
    return this->modified_time;
  }

  PType(const fs::directory_entry& entry)
      : filename(entry.path().filename()), filepath(entry.path()) {
    stat(this->filepath.c_str(), &this->fileinfo);
    this->pw = std::string{getpwuid(this->fileinfo.st_uid)->pw_name};
    this->gr = std::string{getgrgid(this->fileinfo.st_gid)->gr_name};

    try {
      std::time_t tt = decltype(entry.last_write_time())::clock::to_time_t(
          entry.last_write_time());
      std::tm* gmt = std::gmtime(&tt);
      std::stringstream buffer;
      buffer << std::put_time(gmt, "%d %b %H:%M %y");
      this->modified_time = buffer.str();
    } catch (fs::filesystem_error& e) {
      this->modified_time = "";
    }

    switch (entry.status().type()) {
      case fs::file_type::regular:
        this->color = std::string{style::end};
        this->letter = '.';
        this->is_dir = false;
        break;
      case fs::file_type::directory:
        this->color = std::string{style::fg::light_blue};
        this->letter = 'd';
        this->is_dir = true;
        break;
      case fs::file_type::symlink:
        this->color = std::string{style::fg::light_magenta};
        this->letter = 'l';
        this->is_dir = false;
        break;
      case fs::file_type::block:
        this->color = std::string{style::fg::light_green};
        this->letter = 'b';
        this->is_dir = false;
        break;
      case fs::file_type::character:
        this->color = std::string{style::fg::light_yellow};
        this->letter = 'c';
        this->is_dir = false;
        break;
      case fs::file_type::fifo:
        this->color = std::string{style::fg::light_yellow};
        this->letter = '|';
        this->is_dir = false;
        break;
      case fs::file_type::socket:
        this->color = std::string{style::fg::light_red};
        this->letter = 's';
        this->is_dir = false;
        break;
      case fs::file_type::unknown:
        this->color = std::string{style::end};
        this->letter = '.';
        this->is_dir = false;
        break;
      default:
        this->color = std::string{style::end};
        this->letter = '.';
        this->is_dir = false;
        break;
    }
  };
};
