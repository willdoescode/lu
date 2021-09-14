#include <concepts>
#include <filesystem>
#include <iostream>
#include <optional>
#include <permissions.hpp>
#include <ptype.hpp>
#include <string>
#include <style.hpp>
#include <vector>

namespace fs = std::filesystem;

template <typename T>
concept IntoPath = std::is_convertible<T, fs::path>::value;

template <typename T>
requires IntoPath<T>
inline void
validate_dir_path(const T& dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }
}

inline void
handle_indivisual_entry(
		PType ptype,
		int longest_group,
		int longest_owner,
		int longest_date) 
{
  std::cout << ptype.get_color() << ptype.get_leter()
            << get_permission_color_str(
                   fs::status(ptype.get_filepath()).permissions())
            << " " << style::fg::dark_yellow << ptype.get_filegr()
            << std::string((longest_group - ptype.get_filegr().length()), ' ')
            << " " << ptype.get_filepw()
            << std::string((longest_owner - ptype.get_filepw().length()), ' ')
            << style::fg::light_blue << " " << ptype.get_modified_time()
            << std::string((longest_date - ptype.get_modified_time().length()),
                           ' ')
            << ptype.get_color() << " " << ptype.get_filename() << std::endl;
}

template <typename T>
requires IntoPath<T>
inline void
handle_multiple_entries(const T& p) {
  int longest_date = 0, longest_modified_str = 0, longest_group = 0,
      longest_owner = 0;
  std::vector<PType> entry_ptypes{};
  for (const fs::directory_entry& entry : fs::directory_iterator(p)) {
    PType path (entry);

    if (path.get_filepw().length() > longest_owner)
      longest_owner = path.get_filepw().length() + 1;
    if (path.get_filegr().length() > longest_group)
      longest_group = path.get_filegr().length();
    if (path.get_modified_time().length() > longest_date)
      longest_date = path.get_modified_time().length();

    entry_ptypes.push_back(path);
  }

  for (const PType& p : entry_ptypes) {
    handle_indivisual_entry(p, longest_group, longest_owner, longest_date);
  }
}

int
main(const int argc, char* argv[]) {
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

    PType single_entry{fs::directory_entry{argv[i]}};

    handle_indivisual_entry(
				single_entry,
				single_entry.get_filegr().length(),
				single_entry.get_filepw().length(),
				single_entry.get_modified_time().length()
		);
  }

  return EXIT_SUCCESS;
}
