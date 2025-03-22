#ifndef HEAD_H
#define HEAD_H

#include <string>

bool create_branch(const std::string& branch_name);
void list_branches();
bool switch_branch(const std::string& branch_name);

#endif