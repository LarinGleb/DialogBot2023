#include <fstream>
#include <iostream>
#include <vector>

#include "file.h"

int __save_to_file(const std::string filename, const std::string content)
{
    std::ofstream __file;

    __file.open(filename.c_str());

    if (__file.is_open()) {
        __file << content;
        __file.close();
    } else
        return -1;
    return 0;
}

std::vector<std::string> __read_from_file(const std::string name)
{
    std::string __line;
    std::vector<std::string> __content;
    std::ifstream __file;

    __file.open(name);

    if (__file.is_open()) {
        while (std::getline(__file, __line)) {
            __content.push_back(__line);
        }
        __file.close();
    }

    else
        return { "" };

    return __content;
}