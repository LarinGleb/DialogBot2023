#ifndef __TIME_H__
#define __TIME_H__

#include <iostream>

#define DEFAULT_LOG_FORMAT_TIME "%d-%m-%Y %H:%M:%OS"
#define DEAFULT_PSQL_FORMAT_DATE "%m.%d.%Y"

std::string CurrentDataTime(const char* format);

#endif