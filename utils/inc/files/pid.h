#ifndef __PID_H__
#define __PID_H__

#include <iostream>

#include <sys/types.h>

// only server part
int __save_pid();
pid_t __get_pid();

#endif