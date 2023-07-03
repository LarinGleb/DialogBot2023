#include <iostream>
#include <vector>
#include <string>

#include "time_treatment.h"
#include "log.h"

void Log(const std::string log) {
    std::cout << "[" << CurrentTime(DEFAULT_LOG_FORMAT_TIME) << "]: " << log << std::endl; 
}

void Log(const std::vector<std::string>& log, const std::string separator) {
    std::cout << "[" << CurrentTime(DEFAULT_LOG_FORMAT_TIME) << "]: ";

    for (const std::string& part_log : log) {
        std::cout << part_log << separator;
    }
    std::cout << std::endl;
}