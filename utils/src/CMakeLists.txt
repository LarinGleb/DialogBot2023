cmake_minimum_required(VERSION 3.16)

file(GLOB UTILS_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(utils SHARED ${UTILS_SRC})
