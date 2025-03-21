#include <iostream>
#include "utils.h"

void init(const std::string& path) {
    std::string bit_dir = path + "/.git";

    create_dir(bit_dir);
    create_dir(bit_dir + "/objects");
    create_dir(bit_dir + "/index");

   std::string config_content =
       "[core]\n"
       "  repositoryformatversion = 0\n"
       "  filemode = true\n"
       "  bare = false\n";
   write_file(bit_dir + "/config", config_content);

   std::cout << "Initialized empty repository in " << bit_dir << "\n";
}