#ifndef COMMIT_H
#define COMMIT_H

#include <vector>
#include <string>

struct TreeEntry {
    std::string mode;
    std::string type;
    std::string sha1;
    std::string name;
};

std::vector<TreeEntry> read_index();
std::string create_tree_object();
std::string construct_commit_obj(const std::string &tree_hash, const std::string &parent_commit_hash, const std::string &commit_message);

#endif