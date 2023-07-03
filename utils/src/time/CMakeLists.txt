cmake_minimum_required(VERSION 3.16)

file(GLOB TIME_LIB_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(time_lib SHARED ${TIME_LIB_SRC})