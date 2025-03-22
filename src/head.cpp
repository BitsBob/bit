#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "src/utils.h"
#include "utils.h"

namespace fs = std::filesystem;

bool create_branch(const std::string& branch_name) {
    std::string commit_hash = get_last_commit();
    if (commit_hash.empty()) {
        std::cerr << "E: No commits found. Cannot create branch.\n";
        return false;
    }
    
    std::string branch_path = ".bit/refs/heads/" + branch_name;
    std::ofstream branch_file(branch_path);
    if (!branch_file) {
        std::cerr << "E: Failed to create branch.\n";
        return false;
    }
    
    branch_file << commit_hash << "\n";
    branch_file.close();
    std::cout << "Branch '" << branch_name << "' created at " << commit_hash << "\n";
    return true;
}

void list_branches() {
    std::string refs_path = ".bit/refs/heads";
    for (const auto& entry : fs::directory_iterator(refs_path)) {
        std::cout << entry.path().filename().string() << "\n";
    }
}