#include <iostream>
#include <ctime>
#include <iomanip>

#include "time_treatment.h"

std::string CurrentDataTime(const char* format) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format, localTime);
    return buffer;
}