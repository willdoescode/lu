#pragma once

#include <filesystem>
#include <string>

#include "style.hpp"

namespace fs = std::filesystem;

inline const std::string get_permission_color_str(const fs::perms p) {
  using namespace std::string_literals;
  std::string bar{style::fg::light_black + "-"s};

  return style::fg::light_green +
         ((p & fs::perms::owner_read) != fs::perms::none ? "r"s : bar) +
         style::fg::light_yellow +
         ((p & fs::perms::owner_write) != fs::perms::none ? "w"s : bar) +
         style::fg::light_red +
         ((p & fs::perms::owner_exec) != fs::perms::none ? "x"s : bar) +
         style::fg::light_green +
         ((p & fs::perms::group_read) != fs::perms::none ? "r"s : bar) +
         style::fg::light_yellow +
         ((p & fs::perms::group_write) != fs::perms::none ? "w"s : bar) +
         style::fg::light_red +
         ((p & fs::perms::group_exec) != fs::perms::none ? "x"s : bar) +
         style::fg::light_green +
         ((p & fs::perms::others_read) != fs::perms::none ? "r"s : bar) +
         style::fg::light_yellow +
         ((p & fs::perms::others_write) != fs::perms::none ? "w"s : bar) +
         style::fg::light_red +
         ((p & fs::perms::others_exec) != fs::perms::none ? "x"s : bar) +
         style::end;
}
