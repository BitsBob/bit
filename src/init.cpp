#include <iostream>
#include "utils.cpp"

void init(const std::string& path) {
     std::string bit_dir = path + "/.git";

     create_dir(bit_dir);
     create_dir(bit_dir + "/objects");

    std::string config_content =
        "[core]\n"
        "  repositoryformatversion = 0\n"
        "  filemode = true\n"
        "  bare = false\n";
    write_file(bit_dir + "/config", config_content);
}