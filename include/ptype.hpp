#pragma once

#include <filesystem>

#include "style.hpp"

namespace fs = std::filesystem;

struct PType {
 private:
  const char* color;
  char letter;
  const char* filename;
  const char* filepath;

 public:
  PType(const fs::directory_entry& entry) {
    switch (entry.status().type()) {
      case fs::file_type::regular:
        this->color = style::fg::light_white;
        this->letter = '.';
        break;
      case fs::file_type::directory:
        this->color = style::fg::light_blue;
        this->letter = 'd';
        break;
      case fs::file_type::symlink:
        this->color = style::fg::light_magenta;
        this->letter = 'l';
        break;
      case fs::file_type::block:
        this->color = style::fg::light_green;
        this->letter = 'b';
        break;
      case fs::file_type::character:
        this->color = style::fg::light_yellow;
        this->letter = 'c';
        break;
      case fs::file_type::fifo:
        this->color = style::fg::light_yellow;
        this->letter = '|';
        break;
      case fs::file_type::socket:
        this->color = style::fg::light_red;
        this->letter = 's';
        break;
      case fs::file_type::unknown:
        this->color = style::fg::light_white;
        this->letter = '.';
        break;
      default:
        this->color = style::fg::light_white;
        this->letter = '.';
        break;
    }
  };

  bool operator<(const PType& ptype) {
    return this->filepath < ptype.get_filepath();
  }

  inline const char* get_color() const noexcept { return this->color; }
  inline char get_leter() const noexcept { return this->letter; }
  inline const char* get_filepath() const noexcept { return this->filepath; }
};
