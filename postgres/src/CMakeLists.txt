cmake_minimum_required(VERSION 3.16)

add_library(postgressql pqxx_conn.cpp pqxx_bot.cpp)

target_link_libraries(postgressql utils)