#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include <iostream>
#include <vector>
#include <map>

#include <tgbot/tgbot.h>

typedef std::map<std::string, std::string> buttonQuery;

TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData);
std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(const buttonQuery button);

#endif