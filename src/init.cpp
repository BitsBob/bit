#include <iostream>
#include "utils.h"

void init(const std::string& path) {
    std::string bit_dir = path + "/.bit";

    create_dir(bit_dir);
    create_dir(bit_dir + "/objects");
    create_dir(bit_dir + "/index");
    create_dir(bit_dir + "/refs/heads");
    create_dir(bit_dir + "/refs/tags");
    write_file(bit_dir + "/HEAD", "ref: refs/heads/master\n");

   std::string config_content =
       "[core]\n"
       "  repositoryformatversion = 0\n"
       "  filemode = true\n"
       "  bare = false\n";
   write_file(bit_dir + "/config", config_content);

   std::cout << "Initialized empty repository in " << bit_dir << "\n";
}