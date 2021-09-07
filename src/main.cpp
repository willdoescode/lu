#include <filesystem>
#include <iostream>
#include <optional>
#include <permissions.hpp>
#include <ptype.hpp>
#include <string>
#include <style.hpp>
#include <vector>

namespace fs = std::filesystem;

template <class T>
inline void validate_dir_path(T dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }
}

template <class T>
inline void handle_indivisual_entry(T ptype, int longest_group,
                                    int longest_owner, int longest_date) {
  std::cout
      << ptype.get_color() << ptype.get_leter()
      << get_permission_color_str(
             fs::status(ptype.get_filepath()).permissions())
      << " " << style::fg::dark_yellow << ptype.get_filegr()->gr_name
      << std::string((longest_group - strlen(ptype.get_filegr()->gr_name)), ' ')
      << " " << ptype.get_filepw()->pw_name
      << std::string((longest_owner - strlen(ptype.get_filepw()->pw_name)), ' ')
      << style::fg::light_blue << " " << ptype.get_modified_time()
      << std::string((longest_date - ptype.get_modified_time().length()), ' ')
      << ptype.get_color() << " " << ptype.get_filename() << std::endl;
}

template <class T>
inline void handle_multiple_entries(T p) {
  int longest_date, longest_modified_str, longest_group, longest_owner = 0;
  std::vector<PType> entry_ptypes;
  for (const fs::directory_entry& entry : fs::directory_iterator(p)) {
    PType ptype{entry};
    if (strlen(ptype.get_filepw()->pw_name) > longest_owner)
      longest_owner = strlen(ptype.get_filepw()->pw_name);
    if (strlen(ptype.get_filegr()->gr_name) > longest_group)
      longest_group = strlen(ptype.get_filegr()->gr_name);
    if (ptype.get_modified_time().length() > longest_date)
      longest_date = ptype.get_modified_time().length();

    entry_ptypes.push_back(ptype);
  }

  for (auto p : entry_ptypes) {
    handle_indivisual_entry(p, longest_group, longest_owner, longest_date);
  }
}

int main(const int argc, char* argv[]) {
  if (argc <= 1) {
    handle_multiple_entries(".");
    return EXIT_SUCCESS;
  }

  for (size_t i = 1; i < argc; ++i) {
    validate_dir_path(argv[i]);
    if (fs::is_directory(argv[i])) {
      handle_multiple_entries(argv[i]);
      continue;
    }

    handle_indivisual_entry(PType{fs::directory_entry{argv[i]}}, 0, 0, 0);
  }

  return EXIT_SUCCESS;
}
