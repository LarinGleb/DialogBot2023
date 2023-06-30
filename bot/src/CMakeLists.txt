cmake_minimum_required(VERSION 3.16)

add_executable(dialog_bot_2023 bot.cpp)

add_dependencies(dialog_bot_2023 utils)
target_link_libraries(dialog_bot_2023 utils)
