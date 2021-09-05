#include <filesystem>
#include <iostream>
#include <permissions.hpp>
#include <ptype.hpp>
#include <style.hpp>

namespace fs = std::filesystem;

template <class T>
inline T validate_dir_path(T dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }

  return dir;
}

template <class T>
void handle_indivisual_entry(T entry) {
  PType ptype{entry};
  auto path = entry.path();
  std::cout << ptype.get_color() << ptype.get_leter()
            << get_permission_color_str(fs::status(path.c_str()).permissions())
            << " " << ptype.get_color() << path.filename().c_str() << std::endl;
}

template <class T>
void handle_multiple_entries(T p) {
  for (const fs::directory_entry& entry : fs::directory_iterator(p)) {
    handle_indivisual_entry(entry);
  }
}

int main(const int argc, char* argv[]) {
  if (argc <= 1) {
    handle_multiple_entries(".");
    return 0;
  }

  for (int i = 1; i < argc; ++i) {
    validate_dir_path(argv[i]);
    if (fs::is_directory(argv[i])) {
      handle_multiple_entries(argv[i]);
      return 0;
    }

    handle_indivisual_entry(fs::directory_entry{argv[i]});
  }

  return 0;
}
