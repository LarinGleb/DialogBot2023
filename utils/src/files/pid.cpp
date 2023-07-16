#include <fstream>
#include <iostream>

#include "file.h"
#include "pid.h"

#include <sys/types.h>
#include <unistd.h>

int __save_pid()
{
    pid_t pid = getpid();
    return __save_to_file(PID_FILE_NAME, std::to_string(pid));
}

pid_t __get_pid()
{
    std::string pid_str = __read_from_file(PID_FILE_NAME)[0];
    return (pid_t)std::stoi(pid_str);
}