#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "utils.h"
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

bool switch_branch(const std::string& branch_name) {
    std::string branch_path = ".bit/refs/heads/" + branch_name;
    if (!std::filesystem::exists(branch_path)) {
        std::cerr << "E: Branch does not exist.\n";
        return false;
    }
    
    std::ofstream head_file(".bit/HEAD");
    if (!head_file) {
        std::cerr << "E: Failed to update HEAD.\n";
        return false;
    }
    
    head_file << "ref: refs/heads/" << branch_name << "\n";
    head_file.close();
    std::cout << "Switched to branch '" << branch_name << "'\n";
    return true;
}

bool update_head_to_commit(const std::string& commit_hash) {
    // Open the .git/HEAD file for writing
    std::ofstream head_file(".git/HEAD");
    if (!head_file) {
        std::cerr << "Error: Cannot open .git/HEAD.\n";
        return false;
    }

    // Write the commit hash directly to HEAD (detached state)
    head_file << commit_hash << "\n";
    head_file.close();

    std::cout << "Updated HEAD to commit hash: " << commit_hash << "\n";
    return true;
}

bool update_head_to_branch(const std::string& branch_name) {
    std::string branch_ref = "ref: refs/heads/" + branch_name;

    std::ofstream head_file(".bit/HEAD");
    if (!head_file) {
        std::cerr << "E: Cannot open .git/HEAD.\n";
        return false;
    }

    head_file << branch_ref << "\n";
    head_file.close();

    std::cout << "Updated HEAD to branch: " << branch_name << "\n";
    return true;
}