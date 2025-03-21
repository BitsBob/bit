#include <filesystem>
#include <string.h>
#include <string>
#include <iostream>
#include "init.h"


int main(int argc, char* argv[]) {

    if (strcmp(argv[1], "init")) {
        std::string repo_path = (argc > 1) ? argv[2] : ".";
        init(repo_path);
    } else if (strcmp(argv[1], "commit")) {
        if (std::filesystem::exists(".git") && std::filesystem::is_directory(".git")) {
            
        }
    }

    return 0;
}