#include <iostream>
#include <sstream>
#include <fstream>
#include <openssl/sha.h>
#include "utils.h"

void add(const std::string& path) {
    std::vector<std::string> files = list_files(path);

    for (const std::string& file : files) {
        std::string hash = compute_hash(file);
        std::ifstream f(".git/index");
        std::string line, existing_hash;
        bool already_staged = false;

        while (std::getline(f, line)) {
            if (line.find(file) != std::string::npos) {
                existing_hash = line.substr(file.length() + 1);
                already_staged = (existing_hash == hash);
                break;
            }
        }

        if (!already_staged) {
            std::ifstream file_stream(file, std::ios::binary);
            std::stringstream buffer;
            buffer << file_stream.rdbuf();

            store_blob(buffer.str(), hash);
            update_index(file, hash);
            std::cout << "Staged: " << file << "\n";
        }
    }
}
