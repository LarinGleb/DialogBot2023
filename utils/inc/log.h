#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <vector>

void Log(const std::string log, const std::string source_log);
void Log(const std::vector<std::string>& log,
    const std::string source_log,
    const std::string separator);

#endif