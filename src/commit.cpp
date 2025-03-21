#include "commit.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "utils.h"

namespace fs = std::filesystem;

std::vector<TreeEntry> read_index() {
    std::vector<TreeEntry> entries;
    std::ifstream index_file(".git/index");

    if (!index_file.is_open()) {
        std::cerr << "E: .git/index not found!" << std::endl;
        return entries;
    }

    std::string line;

    while (std::getline(index_file, line)) {
        std::istringstream iss(line);
        std::string mode, type, sha1, name;
        iss >> mode >> type >> sha1 >> name;
        
        if (!iss.fail()) {
            entries.push_back({mode, type, sha1, name});
        }
    }
}

std::string create_tree_object() {
    std::vector<TreeEntry> entries = read_index();
    if (entries.empty()) return "";

    std::ostringstream tree_data;
    for (const auto entry : entries) {
        tree_data << entry.mode << " " << entry.type << " " << entry.sha1 << " " << entry.name << "\n";
    }

    std::string tree_content = tree_data.str();
    std::string tree_hash = sha1("tree " + std::to_string(tree_content.size()) + "\0" + tree_content);

    // Store the tree object in .git/objects/
    std::string object_dir = ".git/objects/" + tree_hash.substr(0, 2);
    std::string object_file = object_dir + "/" + tree_hash.substr(2);

    fs::create_directories(object_dir);
    std::ofstream out_file(object_file, std::ios::binary);
    if (out_file.is_open()) {
        out_file << tree_content;
        out_file.close();
    }

    return tree_hash;
}