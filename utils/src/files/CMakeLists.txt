cmake_minimum_required(VERSION 3.16)

file(GLOB FILES_LIB_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(files_lib SHARED ${FILES_LIB_SRC})
