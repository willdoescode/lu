#include <filesystem>
#include <iostream>
#include <permissions.hpp>
#include <ptype.hpp>
#include <style.hpp>

namespace fs = std::filesystem;

template <class T>
inline void validate_dir_path(T dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }
}

template <class T>
inline void handle_indivisual_entry(T entry) {
  PType ptype{entry};
  auto path = entry.path();
  std::cout << ptype.get_color() << ptype.get_leter()
            << get_permission_color_str(fs::status(path.c_str()).permissions())
            << " " << ptype.get_filegr()->gr_name << " "
            << ptype.get_filepw()->pw_name << " " << ptype.get_color()
            << path.filename().c_str() << std::endl;
}

template <class T>
inline void handle_multiple_entries(T p) {
  for (const fs::directory_entry& entry : fs::directory_iterator(p)) {
    handle_indivisual_entry(entry);
  }
}

int main(const int argc, char* argv[]) {
  if (argc <= 1) {
    handle_multiple_entries(".");
    return EXIT_SUCCESS;
  }

  for (size_t i = 1; i < argc; ++i) {
    auto p = argv[i];
    validate_dir_path(p);
    if (fs::is_directory(p)) {
      handle_multiple_entries(p);
      continue;
    }

    handle_indivisual_entry(fs::directory_entry{p});
  }

  return EXIT_SUCCESS;
}
