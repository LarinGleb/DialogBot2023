#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "file.h"
#include "pid.h"

std::vector<int64_t> get_admin_list()
{
    std::vector<std::string> list_from_file = __read_from_file(ADMINS_FILE_NAME);
    std::string line;

    if (list_from_file.size() == 0) {
        std::cout << "You didnt add any admin!" << std::endl;
        return {};
    }

    std::vector<int64_t> admin_list;

    for (size_t i = 0; i < list_from_file.size(); i++) {
        admin_list.push_back(std::stoi(list_from_file.at(i)));
    }
    return admin_list;
}

std::string get_token()
{
    return __read_from_file(TOKEN_FILE_NAME)[0];
}
