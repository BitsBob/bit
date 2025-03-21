#include <iostream>
#include <filesystem>
#include <openssl/sha.h>
#include <vector>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

std::string sha1(const std::string data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    std::stringstream ss;

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string compute_hash(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return sha1(buffer.str());
}

void store_blob(const std::string& content, const std::string& hash) {
    std::string object_dir = ".git/objects/" + hash.substr(0, 2);
    std::string object_file = object_dir + "/" + hash.substr(2);

    std::filesystem::create_directories(object_dir);

    std::ofstream out(object_file, std::ios::binary);
    out.write(content.c_str(), content.size());
}

void create_dir(const std::string& path) {
     if (!fs::exists(path)) {
          fs::create_directories(path);
     }
}

void write_file(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (file) {
        file << content;
    } else {
        std::cerr << "E: Could not create file " << path << "\n";
    }
}

void update_index(const std::string& file_path, const std::string& file_hash) {
    std::ofstream index_file(".git/index", std::ios::app);
    if (!index_file) {
        std::cerr << "E: Could not open .git/index for writing\n";
        return;
    }

    index_file << file_path << " " << file_hash << "\n";
}


std::vector<std::string> list_files(const std::string& dir) {
    std::vector<std::string> files;
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().string().find(".git/") == std::string::npos) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

std::string get_parent_commit_hash(const std::string &commit_hash) {
    std::string commit_file_path = ".bit/objects/" + commit_hash.substr(0, 2) + "/" + commit_hash.substr(2);
    
    std::ifstream commit_file(commit_file_path);
    if (!commit_file.is_open()) {
        std::cerr << "E: Commit file not found!" << std::endl;
        return "";
    }

    std::string line;
    std::string parent_commit_hash;

    while (std::getline(commit_file, line)) {
        if (line.find("parent") != std::string::npos) {
            parent_commit_hash = line.substr(7);
            break;
        }
    }

    return parent_commit_hash;
}

bool is_first_commit() {
    // Check if .git/objects is empty
    fs::path objects_dir(".git/objects");
    if (fs::exists(objects_dir) && fs::is_directory(objects_dir)) {
        for (const auto &entry : fs::directory_iterator(objects_dir)) {
            // If there is at least one object file, it's not the first commit
            return false;
        }
    }

    // If no objects exist, it's the first commit
    return true;
}
