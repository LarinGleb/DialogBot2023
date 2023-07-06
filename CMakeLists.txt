cmake_minimum_required(VERSION 3.16)
project(dialog-bot-2023 VERSION 0.1 DESCRIPTION "A dialog bot for 2023 year")

# ---------- SETS ----------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# ---------- FOR TG LIB ----------
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include_directories(utils/inc/files)
include_directories(utils/inc/time)
include_directories(utils/inc/telegram)
include_directories(utils/inc)
include_directories(bot/inc)
include_directories(postgres/inc)
include_directories(user/inc)


add_subdirectory(utils/src)
add_subdirectory(postgres/src)
add_subdirectory(user/src)

add_executable(dialog_bot_2023 bot/src/bot.cpp)

add_dependencies(dialog_bot_2023 utils)
add_dependencies(dialog_bot_2023 postgressql)
add_dependencies(dialog_bot_2023 users)

target_link_libraries(dialog_bot_2023 utils)
target_link_libraries(dialog_bot_2023 postgressql)
target_link_libraries(dialog_bot_2023 users)

target_link_libraries(dialog_bot_2023 /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
target_link_libraries(dialog_bot_2023 -lpqxx -lpq)