cmake_minimum_required(VERSION 3.16)

add_subdirectory(files)
add_subdirectory(time)

add_library(utils SHARED log.cpp)

target_link_libraries(utils time_lib)
target_link_libraries(utils files_lib)