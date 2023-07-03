#ifndef __TIME_H__
#define __TIME_H__

#include <iostream>

#define DEFAULT_LOG_FORMAT_TIME "%d-%m-%Y %H:%M:%OS"

std::string CurrentTime(const char* format);

#endif