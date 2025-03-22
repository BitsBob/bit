#include <filesystem>
#include <iostream>
#include <cstring>
#include <string>
#include "init.h"
#include "add.h"
#include "commit.h"
#include "utils.h"
#include "head.h"

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
        } else if (strcmp(argv[1], "commit") == 0) {
            if (argc < 4) {
                std::cerr << "E: Commit message not provided.\n";
                return 1;
            }

            std::string path = (argc > 2) ? argv[2] : ".";
            read_index();
            std::string tree_hash = create_tree_object();

            std::string commit_message = "";
            if (strcmp(argv[2], "-m") == 0 || strcmp(argv[2], "-message") == 0) {
                commit_message = argv[3];
            } else {
                std::cerr << "E: Unknown commit message flag '" << argv[2] << "'\n";
                return 1;
            }

            std::string parent_commit_hash = get_last_commit();

            std::string obj = construct_commit_obj(tree_hash, parent_commit_hash, commit_message);
            std::cout << "Commit created with object: " << obj << std::endl;
        } else if  (std::string(argv[1]) != "branch") {
            list_branches();

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
