#include <filesystem>
#include <iostream>
#include <cstring>
#include <string>
#include "init.h"
#include "add.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "E: No command provided.\n";
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        std::string repo_path = (argc > 2) ? argv[2] : ".";
        init(repo_path);
    } else if (std::filesystem::exists(".git") && std::filesystem::is_directory(".git")) {
        if (strcmp(argv[1], "add") == 0) {
            std::string path = (argc > 2) ? argv[2] : ".";
            add(path);
        } else {
            std::cerr << "E: Unknown command '" << argv[1] << "'\n";
            return 1;
        }
    } else {
        std::cerr << "E: Not a repository (or any parent directory)\n";
        return 1;
    }

    return 0;
}
