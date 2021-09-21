#include <concepts>
#include <filesystem>
#include <iostream>
#include <optional>
#include <permissions.hpp>
#include <ptype.hpp>
#include <sstream>
#include <string>
#include <style.hpp>
#include <type_traits>
#include <vector>

namespace fs = std::filesystem;

template <typename T>
concept IntoPath = std::is_convertible<T, fs::path>::value;

template <typename Path>
requires IntoPath<Path>
inline void validate_dir_path(const Path& dir) {
  if (!fs::exists(dir)) {
    std::cout << "Error: \"" << dir << "\" does not exist." << std::endl;
    exit(EXIT_FAILURE);
  }
}

inline void handle_indivisual_entry(std::ostream& o, PType ptype,
                                    int longest_size, int longest_group,
                                    int longest_owner, int longest_date) {
  o << ptype.get_color() << ptype.get_leter()
    << get_permission_color_str(fs::status(ptype.get_filepath()).permissions())
    << (ptype.get_size() != "-" ? style::fg::light_green
                                : style::fg::light_black)
    << " " << ptype.get_size()
    << std::string((longest_size - ptype.get_size().length()), ' ') << " "
    << style::fg::dark_yellow << ptype.get_filegr()
    << std::string((longest_group - ptype.get_filegr().length()), ' ') << " "
    << ptype.get_filepw()
    << std::string((longest_owner - ptype.get_filepw().length()), ' ')
    << style::fg::light_blue << " " << ptype.get_modified_time()
    << std::string((longest_date - ptype.get_modified_time().length()), ' ')
    << ptype.get_color() << " " << ptype.get_filename() << std::endl;
}

template <typename Path>
requires IntoPath<Path>
inline void handle_multiple_entries(std::ostream& buffer, const Path& p) {
  int longest_date = 0, longest_modified_str = 0, longest_group = 0,
      longest_owner = 0, longest_size = 0;

  std::vector<PType> entry_ptypes{};

  for (const fs::directory_entry& entry : fs::directory_iterator(p)) {
    PType path(entry);

    if (path.get_filepw().length() > longest_owner)
      longest_owner = path.get_filepw().length() + 1;
    if (path.get_filegr().length() > longest_group)
      longest_group = path.get_filegr().length();
    if (path.get_modified_time().length() > longest_date)
      longest_date = path.get_modified_time().length();
    if (path.get_size().length() > longest_size)
      longest_size = path.get_size().length();

    entry_ptypes.push_back(path);
  }

  std::sort(entry_ptypes.begin(), entry_ptypes.end(),
            [](auto f1, auto f2) { return f1 < f2; });

  for (const PType& p : entry_ptypes) {
    handle_indivisual_entry(buffer, p, longest_size, longest_group,
                            longest_owner, longest_date);
  }
}

int main(const int argc, char* argv[]) {
  std::ostringstream buffer;

  if (argc <= 1) {
    handle_multiple_entries(buffer, ".");
    goto PRINT_BUFFER;
  }

  for (size_t i = 1; i < argc; ++i) {
    validate_dir_path(argv[i]);
    if (fs::is_directory(argv[i])) {
      handle_multiple_entries(buffer, argv[i]);
      continue;
    }

    PType single_entry{fs::directory_entry{argv[i]}};

    handle_indivisual_entry(
        buffer, single_entry, single_entry.get_size().length(),
        single_entry.get_filegr().length(), single_entry.get_filepw().length(),
        single_entry.get_modified_time().length());
  }

PRINT_BUFFER:
  std::cout << buffer.str();
  return EXIT_SUCCESS;
}
