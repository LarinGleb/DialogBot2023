#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <exception>
#include <locale>
#include <algorithm>

#include <tgbot/tgbot.h>

#include "bot.h"

#include "pqxx_conn.h"
#include "user.h"

#include "crypt_id.h"
#include "file.h"
#include "log.h"
#include "pid.h"

#include "constructor.h"

int main()
{
    Log("Некоторое объяснение. \n Start - всё, что на старте. \n Bot - всё взаимодействие пользователей с ботом. \n Info - справочная информация, как такая. \n Stop - всё, что на остановке. \n System - всё, что отвечает за работу бота.", "Info");
    std::filesystem::current_path(MAIN_PATH + TXT_PATH);
    std::string token = get_token();
    __save_pid();
    
    std::locale russian_locale("ru_RU.UTF-8");

    db_api::PsqlConnector conn("dialog2023", "gleb", "1957");

    std::vector<int64_t> admin_list = get_admin_list();

    //Log({ std::string { "Token for bot - " }, token }, "Start", "");
    TgBot::Bot bot(token);

    TgBot::Api api = bot.getApi();
    TgBot::User::Ptr botInfo = api.getMe();
    std::string botUsername = botInfo->username;

    
    Log("Name bot: @" + botUsername, "Start");   

    std::map<int64_t, User> users;

    bot.getEvents().onAnyMessage([&bot, &api, &users, &conn, russian_locale, admin_list](TgBot::Message::Ptr message) {

        int64_t u_id = crypt_id(message->from->id);
        std::string input = message->text;
        if(input.empty()) {
            api.sendMessage(message->chat->id, "Хей! А можно текстом? Хочу текстом!!!!!!!!");
            return;
        }

        bool admin = (std::find(admin_list.begin(), admin_list.end(), decrypt_id(u_id)) != admin_list.end());

        if (users.count(u_id) == 0 ) {
            User new_user(u_id, conn, admin);
            users.insert(std::make_pair(u_id, new_user));

            Log("Новый пользователь: " + std::to_string(u_id), "Bot");
        }

        input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) { 
            return std::ispunct(c); 
        }), input.end());

        Log("Пользователь " + std::to_string(u_id) + " ввёл: " + message->text, "User");

        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        User* current_user = &users[u_id];
        std::string user_state = current_user->GetState();
        
        if (user_state == START_NODE_ID) {
            if (admin) {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({{"Оставить отзыв", ADD_REVIEW_BUTTON_CALLBACK},{"Добавить Мероприятие", ADD_EVENT_BUTTON_CALLBACK}}));
            }
            else {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({{"Оставить отзыв", ADD_REVIEW_BUTTON_CALLBACK}}));
            }
            api.sendMessage(message->chat->id, "Привет! Выбери, что ты хочешь сделать: ", false, 0, keyboard);
        }
        
        else if (user_state.ends_with("mark")) {
            for (char c : input) {
                if (!std::isdigit(c)) {
                    api.sendMessage(message->chat->id, "Ну что-то тут явно не так. Мне целая циферка нужна!");
                    return;
                }
            }
            int mark = std::stoi(input);
            
            if (mark < 1 || mark > 10) {
                
                api.sendMessage(message->chat->id, "Ну что-то тут явно не так. Ты попробуй оценку дать от 1 до 10.");
                return;
            }
            else {
                current_user->AddInput(input);
                current_user->NextState();
                api.sendMessage(message->chat->id, "Спасибо! Чтобы вы хотели изменить в мероприятии?");
            }
        }

        else if (user_state.ends_with("_change")) {
            current_user->AddInput(input);
            api.sendMessage(message->chat->id, "Интересно! Чтобы вы хотели похвалить в мероприятии?");
            current_user->NextState();
        }
        
        else if (user_state.ends_with("_good")) {
            current_user->AddInput(input);
            current_user->NextState();
            api.sendMessage(message->chat->id, "Благодарю! Хотите подобное мероприятие в следующем году?");
        }

        else if (user_state.ends_with("_nextyear")) {
            
            current_user->AddInput(input);
            api.sendMessage(message->chat->id, "Спасибо за отзыв на" + current_user->GetEvent() + "! До новых отзывов");
            current_user->AddReview(conn);
            current_user->DeleteUser();
            users.erase(u_id);

        }

        else if (user_state == ADD_NAME_EVENT_NODE_ID) {
            current_user->AddInput(message->text);
            api.sendMessage(message->chat->id, "Напишите краткое описание мероприятия");
            current_user->NextState();
        }

        else if (user_state == ADD_DESC_EVENT_NODE_ID) {
            current_user->AddInput(message->text);
            api.sendMessage(message->chat->id, "Выберите дату проведения мероприятия.");
            current_user->NextState();
        }

        else if (user_state == ADD_DATE_EVENT_NODE_ID) {
            current_user->AddInput(message->text);
            current_user->AddEvent(conn);
            api.sendMessage(message->chat->id, "Спасибо! Мероприятие добавлено. ");
            current_user->DeleteUser();
            users.erase(u_id);
        }
        
    });

    bot.getEvents().onCallbackQuery([&bot, &api, &conn, &users](TgBot::CallbackQuery::Ptr cb_query) {

        int64_t u_id = crypt_id(cb_query->from->id);
        if (users.count(u_id) == 0 ) {
            api.sendMessage(cb_query->message->chat->id, "Аха, кто-то пытается меня сломать! Ну уж нет! Оставляй отзыв, если ещё этого не сделал. Просто напиши что угодно, чтобы перейти в меню отзывов)");
            return;
        }

        User* current_user = &users[u_id];
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        std::string state_user = current_user->GetState();

        if (state_user == START_NODE_ID && cb_query->data == ADD_REVIEW_BUTTON_CALLBACK) {
            if (current_user->GetPossibleEvents().size() == 0) {
                api.sendMessage(cb_query->message->chat->id, "Для тебя пока нет доступных мероприятий!");
                current_user->DeleteUser();
                return;
            }
            current_user->NextState(CHOOSE_NODE_ID);
            for(std::string event: current_user->GetPossibleEvents()) {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({CreateButtonTG(event, event)}));
            }
            api.sendMessage(cb_query->message->chat->id, "Выбери, на какое мероприятие ты хочешь оставить отзыв: ", false, 0, keyboard);
        }

        if (state_user == START_NODE_ID && cb_query->data == ADD_EVENT_BUTTON_CALLBACK) {
            current_user->NextState(ADD_NAME_EVENT_NODE_ID);
            api.sendMessage(cb_query->message->chat->id, "Введите имя для мероприятия: ", false, 0);
        }
        else if (state_user == CHOOSE_NODE_ID) {
            if (current_user->GetPossibleEvents().size() == 0) {
                api.sendMessage(cb_query->message->chat->id, "Уху. Ну, нет, сорянчик, ты уже оставлял на это отзыв");
                return;
            }
            if (std::find(current_user->GetPossibleEvents().begin(), current_user->GetPossibleEvents().end(), cb_query->data) != current_user->GetPossibleEvents().end()) {
                api.sendMessage(cb_query->message->chat->id, "Ты уже оставлял отзыв на это мероприятие.");
                return;
            }
            current_user->SetCurrentWorkingEvent(cb_query->data);
            api.sendMessage(cb_query->message->chat->id, "Отлично! Поставь оценку этому мероприятию от 0 до 10.");
            current_user->NextState();
        }
        
        

    });
    try {
        api.deleteWebhook();
    
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            Log("Lognpoll запущен.", "System");
            longPoll.start();
        }
    }
    catch (std::exception& e) {
        Log(e.what(), "Error");
    }
    

    return 0;
}