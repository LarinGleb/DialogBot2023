#include <algorithm>
#include <cctype>
#include <exception>
#include <filesystem>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

#include "bot.h"

#include "pqxx_conn.h"
#include "user.h"

#include "crypt_id.h"
#include "file.h"
#include "log.h"
#include "pid.h"
#include "csv.h"
#include "time_treatment.h"

#include "constructor.h"

int main()
{
    Log("Некоторое объяснение. \n Start - всё, что на старте. \n Bot - всё взаимодействие пользователей с ботом. \n Info - справочная информация, как такая. \n Stop - всё, что на остановке. \n System - всё, что отвечает за работу бота.", "Info");
    std::filesystem::current_path(MAIN_PATH + TXT_PATH);
    std::string token = get_token();
    __save_pid();
    bool tech_work = false;

    db_api::PsqlConnector conn("dialog2023", "gleb", "19572006gG");

    std::vector<int64_t> admin_list = get_admin_list();
    std::vector<std::string> command_list = {"/help", "/help_readr", "/help_addr"};
    // Log({ std::string { "Token for bot - " }, token }, "Start", "");
    TgBot::Bot bot(token);

    TgBot::Api api = bot.getApi();
    TgBot::User::Ptr botInfo = api.getMe();
    std::string botUsername = botInfo->username;

    Log("Name bot: @" + botUsername, "Start");

    std::map<int64_t, User> users;
    
    
    bot.getEvents().onCommand("help", [&bot, &api, &users, admin_list](TgBot::Message::Ptr message) {
        int64_t u_id = crypt_id(message->from->id);
        bool admin = (std::find(admin_list.begin(), admin_list.end(), decrypt_id(u_id)) != admin_list.end());
        if (admin) {
            api.sendMessage(message->chat->id, "Привет! Я бот, созданный @PanteleevLenka для анонимной оценки мероприятий. Вот мой функционал в помощи: \n /help_readr - помочь прочитать отзывы на своё мероприятие. \n /help_addr - помочь добавить отзыв на мероприятие. \n /help - выводит это сообщениею. \n Надеюсь, я был полезен! До новых отзывов! ");
        }
        else {
            api.sendMessage(message->chat->id, "Привет! Я бот, созданный @PanteleevLenka для анонимной оценки мероприятий. Вот мой функционал в помощи: \n /help_addr - помочь добавить отзыв на мероприятие. \n /help - выводит это сообщение. \n Надеюсь, я был полезен! До новых отзывов! ");
        }
    });

    bot.getEvents().onCommand("help_readr", [&bot, &api, &users, admin_list](TgBot::Message::Ptr message) {
        int64_t u_id = crypt_id(message->from->id);
        bool admin = (std::find(admin_list.begin(), admin_list.end(), decrypt_id(u_id)) != admin_list.end());
        if (admin) {
            api.sendMessage(message->chat->id, "Сейчас я вам отправлю инструкцию, как прочитать отзывы на своё мероприятие.");
            const std::string type =  "image/png";

            std::vector<std::string> help = {"Напишите мне что-нибудь и выберите \"прочитать отзывы\":", \
                                            "Выберите мероприятие, на которое хотели бы прочитать отзывы. Учтите, что кнопка \"На всё\" даст возможность прочитать отзывы на все мероприятия:", \
                                            "Я отправлю вам файл. Скачайте его:", \
                                            "__Если вы умеете работать с csv файлами, то можете пропустить этап дальше. __ \n Создайте аккаунт в google sheets и перейдите по этой ссылке: https://docs.google.com/spreadsheets/u/0/. \n Нажмите на кнопку создания пустого файла:", \
                                            "В левом верхнем углу нажмите на файл->импротировать: ", \
                                            "Выберите добавление файлов и загрузите свой csv файл:", \
                                            "Заполните поля, как на примере, то есть поставьте разделители и уберите галочку. Нажмите на импротирование данных:", \
                                            "После у вас появится синия кнопка \"открыть сейчас\". Нажмите на неё:", \
                                            "У вас будут отзывы. Небольшое пояснение: \n"
                                            "id - id отзыва в бд \n"
                                            "event_id - id мероприятия, на которое был отправлены отзывы \n"
                                            "user_id - зашифрованный id юзера, который оставил на мероприятие отзыв \n"
                                            "date - дата создания отзыва \n"
                                            "mark_event - общая оценка мероприятия от 1 до 10 \n"
                                            "change - то, что хотели бы поменять в мероприятии \n" 
                                            "good - то, что уже хорошо в мероприятии \n" 
                                            "next_year - хотят ли видеть данное мероприятие в следующем году. \n"
                                            "Надеюсь, я был вам полезен!"};

            for (size_t i = 0; i < help.size(); i ++) {
                const std::string name_file = MAIN_PATH + std::string(TXT_PATH) + std::string("help_png/help_readr/") + std::to_string(i+1) + std::string(".png");
                TgBot::Message::Ptr reply = api.sendMessage(message->chat->id, help[i]); 
                api.sendDocument(message->chat->id, TgBot::InputFile::fromFile(name_file, type), "", "", reply->messageId); 
                
            }

        }
        else {
            api.sendMessage(message->chat->id, "Ты не админ, тебе нельзя!");
        }
    });

    bot.getEvents().onCommand("drop_me", [&bot, &api, &users](TgBot::Message::Ptr message) {
	int64_t u_id = crypt_id(message->from->id);
	if (users.count(u_id) == 0) {
		api.sendMessage(message->chat->id, "Ты и так в начальном состоянии!");

	}
	else {
		User* current_user = &users[u_id];
		current_user->DeleteUser();
		users.erase(u_id);
	}
    });
    bot.getEvents().onAnyMessage([&bot, &api, &users, &conn,admin_list, tech_work, command_list](TgBot::Message::Ptr message) {
        int64_t u_id = crypt_id(message->from->id);
        std::string input = message->text;
        if(tech_work) {
	    api.sendMessage(message->chat->id, "Я на тех работах!");
	    return;
	}
	if (std::find(command_list.begin(), command_list.end(), input) != command_list.end()) {
            return;
        }
        if (input.empty()) {
            api.sendMessage(message->chat->id, "Хей! А можно текстом? Хочу текстом!!!!!!!!");
            return;
        }
        
	bool admin = (std::find(admin_list.begin(), admin_list.end(), decrypt_id(u_id)) != admin_list.end());
        if (users.count(u_id) == 0) {
            User new_user(u_id, conn, admin);
            users.insert(std::make_pair(u_id, new_user));

            Log("Новый пользователь: " + std::to_string(u_id), "Bot");
        }

        input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
            return c == '\"' || c == ';' || c == '\n';
        }),
            input.end());

        Log("Пользователь " + std::to_string(u_id) + " ввёл: " + message->text, "User");
	Log("После обработки его сообщение: " + input, "User");

        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        User* current_user = &users[u_id];
        std::string user_state = current_user->GetState();

        if (user_state == START_NODE_ID) {
            if (admin) {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({{"Добавить Мероприятие", ADD_EVENT_BUTTON_CALLBACK}})) ;
                keyboard->inlineKeyboard.push_back(CreateLineButtons({{"Оставить отзыв", ADD_REVIEW_BUTTON_CALLBACK }, {"Читать отзывы", READ_RIVEW_BUTTON_CALLBACK}}));
            } else {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({ { "Оставить отзыв", ADD_REVIEW_BUTTON_CALLBACK } }));
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
            } else {
                current_user->AddInput(input);
                current_user->NextState();
                api.sendMessage(message->chat->id, "Спасибо! Что бы вы хотели изменить в мероприятии?");
            }
        }

        else if (user_state.ends_with("_change")) {
            current_user->AddInput(input);
            api.sendMessage(message->chat->id, "Интересно! Что бы вы хотели похвалить в мероприятии?");
            current_user->NextState();
        }

        else if (user_state.ends_with("_good")) {
            current_user->AddInput(input);
            current_user->NextState();
            api.sendMessage(message->chat->id, "Благодарю! Хотите подобное мероприятие в следующем году?");
        }

        else if (user_state.ends_with("_nextyear")) {

            current_user->AddInput(input);
            api.sendMessage(message->chat->id, "Спасибо за отзыв на " + current_user->GetEvent() + "! До новых отзывов");
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

    bot.getEvents().onCallbackQuery([&bot, &api, &conn,tech_work, &users](TgBot::CallbackQuery::Ptr cb_query) {
        int64_t u_id = crypt_id(cb_query->from->id);
        if (users.count(u_id) == 0) {
            api.sendMessage(cb_query->message->chat->id, "Аха, кто-то пытается меня сломать! Ну уж нет! Оставляй отзыв, если ещё этого не сделал. Просто напиши что угодно, чтобы перейти в меню отзывов)");
            return;
        }
	if (tech_work) {
	   api.sendMessage(cb_query->message->chat->id, "Я на технических работах!");
	   return;
	}

        User* current_user = &users[u_id];
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        std::string state_user = current_user->GetState();

        if (state_user == START_NODE_ID && cb_query->data == ADD_REVIEW_BUTTON_CALLBACK) {
            if (current_user->GetPossibleEvents().size() == 0) {
                api.sendMessage(cb_query->message->chat->id, "Для тебя пока нет доступных мероприятий!");
                current_user->DeleteUser();
                users.erase(u_id);
                return;
            }
            current_user->NextState(CHOOSE_NODE_ID);
            for (std::string event : current_user->GetPossibleEvents()) {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({ CreateButtonTG(event, event) }));
            }
            api.sendMessage(cb_query->message->chat->id, "Выбери мероприятие на которое оставишь отзыв: ", false, 0, keyboard);
        }

        else if (state_user == START_NODE_ID && cb_query->data == READ_RIVEW_BUTTON_CALLBACK) {
            current_user->NextState(CHOOSE_REVIEWS_NODE_ID);

            for (std::string event: conn.GetAllEvents()) {
                keyboard->inlineKeyboard.push_back(CreateLineButtons({ CreateButtonTG(event, event) }));
            }
            keyboard->inlineKeyboard.push_back(CreateLineButtons({ CreateButtonTG("На всё", ALL_EVENT_CHOOSE) }));
            api.sendMessage(cb_query->message->chat->id, "Выбери мероприятие, на которое прочтёшь отзывы: ", false, 0, keyboard);
        }

        else if (state_user == START_NODE_ID && cb_query->data == ADD_EVENT_BUTTON_CALLBACK) {
            current_user->NextState(ADD_NAME_EVENT_NODE_ID);
            api.sendMessage(cb_query->message->chat->id, "Введите имя для мероприятия: ", false, 0);
        }

        else if (state_user == CHOOSE_REVIEWS_NODE_ID) {
            std::vector<std::string> all_events = conn.GetAllEvents();
            Log("Запрошены отзывы от " + std::to_string(u_id), "User");
            if (std::find(all_events.begin(), all_events.end(), cb_query->data) != all_events.end()) {
                
                int id = conn.IdByName(cb_query->data);
                std::vector<std::string> reviews = conn.ReadReviews(id);
                std::string name_file = cb_query->data + "_" + CurrentDataTime("%d_%m_%Y") + ".csv";
                create_csv(name_file);
                generate_csv(name_file, reviews);
                current_user->DeleteUser();
                users.erase(u_id);
                bot.getApi().sendDocument(cb_query->message->chat->id, TgBot::InputFile::fromFile(MAIN_PATH + CREATION_CSV_PATH + name_file, "text/csv"));
                delete_csv(name_file);

            }
            else if (cb_query->data == ALL_EVENT_CHOOSE) {
                std::string name_file = "reviews_" + CurrentDataTime("%d_%m_%Y") + ".csv";
                create_csv(name_file);
                for (std::string event: all_events) {
                    int id = conn.IdByName(event);
                    std::vector<std::string> reviews = conn.ReadReviews(id);
                    generate_csv(name_file, reviews);
                }
                current_user->DeleteUser();
                users.erase(u_id);
                bot.getApi().sendDocument(cb_query->message->chat->id, TgBot::InputFile::fromFile(MAIN_PATH + CREATION_CSV_PATH + name_file, "text/csv"));
                delete_csv(name_file);
            }
        }
        else if (state_user == CHOOSE_NODE_ID) {
            if (current_user->GetPossibleEvents().size() == 0) {
                api.sendMessage(cb_query->message->chat->id, "Уху. Ну, нет, сорянчик, ты уже оставлял на это отзыв");
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
	    bool need_sended = true;
        bool need_to_send = false;
        while (true) {
//Log("Lognpoll запущен.", "System");
            longPoll.start();
	    std::vector<std::string> time = CurrentTime();
	    std::string time_string = time[0] + ":" + time[1];
	    Log("Cureent time: " + time_string, "test");
	    if ((time_string == "19:15" || time_string == "22:1") && need_sended && need_to_send) {
		    std::vector<int64_t> ids = conn.GetAllUsers();
		    for (int64_t id: ids) {
			api.sendMessage(decrypt_id(id), "Привет! Не забывай обо мне и оставляй отзывы!");
		    }
		    need_sended = false;
	    }
	    if (time_string == "19:16" || time_string == "22:2") {
		    need_sended = true;
	        }
        }
    } catch (std::exception& e) {
        Log(e.what(), "Error");
    }

    return 0;
}
