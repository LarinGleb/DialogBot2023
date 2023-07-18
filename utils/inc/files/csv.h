#ifndef __CSV_GENERATION_H__
#define __CSV_GENERATION_H__

#define test 1 

#include <iostream>
#include <pqxx/pqxx>

void create_csv(const std::string namefile);
void generate_csv(const std::string namefile, std::vector<std::string> reviews);
void delete_csv(const std::string namefile);

#endif