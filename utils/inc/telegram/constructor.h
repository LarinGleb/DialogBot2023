#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include <iostream>
#include <map>
#include <vector>

#include <tgbot/tgbot.h>

TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton,
    const std::string callBackData);

std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(
    const std::map<std::string, std::string> button);

std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(
    const std::vector<TgBot::InlineKeyboardButton::Ptr> button);

#endif