cmake_minimum_required(VERSION 3.16)

add_library(users SHARED user.cpp graph.cpp nodes.cpp)

target_link_libraries(users utils)
