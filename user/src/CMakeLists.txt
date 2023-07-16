cmake_minimum_required(VERSION 3.16)

add_library(users SHARED user.cpp graph.cpp)

target_link_libraries(users PRIVATE  utils)
target_link_libraries(users PRIVATE  postgressql)