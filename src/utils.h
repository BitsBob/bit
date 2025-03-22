#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

void create_dir(const std::string& path);
void write_file(const std::string& path, const std::string& content);
void store_blob(const std::string& content, const std::string& hash);
void update_index(const std::string& file_path, const std::string& file_hash);
std::vector<std::string> list_files(const std::string& dir);
std::string compute_hash(const std::string& file_path);
std::string sha1(const std::string data);
std::string get_last_commit();

#endif
