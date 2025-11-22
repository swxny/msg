#pragma once
#include <string>

void init_db();
void insert_message(const std::string& user, const std::string& msg);
std::string get_all_messages();
