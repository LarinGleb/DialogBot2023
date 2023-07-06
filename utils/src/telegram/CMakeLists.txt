cmake_minimum_required(VERSION 3.16)

file(GLOB TELEGRAM_LIB_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(telegram_utils_lib SHARED ${TELEGRAM_LIB_SRC})
