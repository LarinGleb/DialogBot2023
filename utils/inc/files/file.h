#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <vector>

#define ADMINS_FILE_NAME "admins.txt"
#define TOKEN_FILE_NAME "token.txt"
#define PID_FILE_NAME "PID.txt"

// basic function only for my own use
int __save_to_file(const std::string filename, const std::string content);
std::vector<std::string> __read_from_file(const std::string name);

// function need to bot directly 

std::vector<int> get_admin_list();
std::string get_token();


#endif