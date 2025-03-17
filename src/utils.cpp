#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

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
        std::cerr << "Error: Could not create file " << path << "\n";
    }
}