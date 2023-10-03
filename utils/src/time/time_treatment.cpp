#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

#include "time_treatment.h"

std::string CurrentDataTime(const char* format)
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format, localTime);
    return buffer;
}

std::vector<std::string> CurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::vector<std::string> time;

    time.push_back(std::to_string(localTime->tm_hour));
    time.push_back(std::to_string(localTime->tm_min));

    return time;
}
