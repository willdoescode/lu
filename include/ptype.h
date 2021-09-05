#pragma once

#include <filesystem>

#include "style.h"

namespace fs = std::filesystem;

struct PType {
 private:
  const char* color;
  char letter;

 public:
  PType(const fs::directory_entry& entry) {
    if (entry.is_regular_file()) {
      this->color = style::fg::light_white;
      this->letter = '.';
      return;
    }
    if (entry.is_directory()) {
      this->color = style::fg::light_blue;
      this->letter = 'd';
      return;
    }

    if (entry.is_symlink()) {
      this->color = style::fg::light_magenta;
      this->letter = 'l';
      return;
    }

    if (entry.is_block_file()) {
      this->color = style::fg::light_green;
      this->letter = 'b';
      return;
    }

    if (entry.is_socket()) {
      this->color = style::fg::light_red;
      this->letter = 's';
      return;
    }

    if (entry.is_character_file()) {
      this->color = style::fg::light_yellow;
      this->letter = 'c';
      return;
    }

    if (entry.is_fifo()) {
      this->color = style::fg::light_yellow;
      this->letter = '|';
      return;
    }

    if (entry.is_other()) {
      this->color = style::fg::light_white;
      this->letter = '.';
    }
  };

  inline const char* get_color() { return this->color; }
  inline char get_leter() { return this->letter; }
};
