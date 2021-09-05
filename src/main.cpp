#include <permissions.h>
#include <ptype.h>
#include <stdio.h>
#include <style.h>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

template <class T>
inline T validate_dir_path(T dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!fs::is_directory(dir)) {
    std::cout << "Error: \"" << dir << "\" is not a directory." << std::endl;
    exit(EXIT_FAILURE);
  }

  return dir;
}

int main(const int argc, char* argv[]) {
  const char* dir = (argc <= 1 ? (char*)"." : argv[1]);
  dir = validate_dir_path(dir);

  std::cout << dir << std::endl;

  for (const fs::directory_entry& entry : fs::directory_iterator(dir)) {
    PType ptype{entry};
    auto path = entry.path();
    std::cout << ptype.get_color() << ptype.get_leter()
              << get_permission_color_str(
                     fs::status(path.c_str()).permissions())
              << " " << ptype.get_color() << path.filename().c_str()
              << std::endl;
  }

  return 0;
}
