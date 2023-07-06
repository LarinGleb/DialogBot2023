#include <iostream>
#include <vector>
#include <string>

#include "time_treatment.h"
#include "log.h"

void Log(const std::string log, const std::string source_log) {
    std::cout << "[" << CurrentDataTime(DEFAULT_LOG_FORMAT_TIME) << "] [" << source_log << "]: " << log << std::endl; 
}

void Log(const std::vector<std::string>& log, const std::string source_log, const std::string separator) {
    std::cout << "[" << CurrentDataTime(DEFAULT_LOG_FORMAT_TIME) << "] [" << source_log << "]: ";

    for (const std::string& part_log : log) {
        std::cout << part_log << separator;
    }
    std::cout << std::endl;
}