#include <iostream>
#include <map>
#include <vector> // for concat

#include <tgbot/tgbot.h>

#include "constructor.h"

TgBot::InlineKeyboardButton::Ptr CreateButtonTG(
    const std::string textButton,
    const std::string callBackData)
{
    TgBot::InlineKeyboardButton::Ptr Button(new TgBot::InlineKeyboardButton);
    Button->text = textButton;
    Button->callbackData = callBackData;
    return Button;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(
    std::map<std::string, std::string> buttons)
{
    std::vector<TgBot::InlineKeyboardButton::Ptr> linebuttons;
    for (const std::pair<std::string, std::string> pair : buttons) {
        linebuttons.push_back(CreateButtonTG(pair.first, pair.second));
    }
    return linebuttons;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(
    const std::vector<TgBot::InlineKeyboardButton::Ptr> buttons)
{

    std::vector<TgBot::InlineKeyboardButton::Ptr> linebuttons;
    for (const TgBot::InlineKeyboardButton::Ptr button : buttons) {
        linebuttons.push_back(button);
    }
    return linebuttons;
}
