#include <fstream>
#include <iostream>

#include <pqxx/pqxx>

#include "bot.h"

void create_csv(const std::string namefile) {
    std::fstream csv;
    csv.open(MAIN_PATH + CREATION_CSV_PATH + namefile,
        std::ios::out | std::ios::app);
    csv << "ID;event_id;user_id;date;mark_event;change;good;next_year \n";
    csv.close();
}

void generate_csv(const std::string namefile,
    std::vector<std::string> reviews)
{
    std::fstream csv;
    csv.open(MAIN_PATH + CREATION_CSV_PATH + namefile,
        std::ios::out | std::ios::app);
    for (std::string review: reviews) {
        csv << review;
        csv << "\n";
    }
    csv.close();
}

void delete_csv(const std::string namefile)
{
    std::string path = MAIN_PATH + CREATION_CSV_PATH + namefile;
    std::remove(path.c_str());
}