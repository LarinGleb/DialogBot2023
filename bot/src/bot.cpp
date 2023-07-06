#include <string>
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <vector>

#include <tgbot/tgbot.h>

#include "bot.h"
#include "pqxx_conn.h"
#include "pid.h"
#include "file.h"
#include "log.h"
#include "crypt_id.h"

using namespace std;
using namespace TgBot;

int main() {
    std::filesystem::current_path(MAIN_PATH + TXT_PATH);
    std::string token = get_token();
    __save_pid();
    db_api::PsqlConnector conn("dialog2023", "gleb", "1957");

    std::vector<int> admin_list = get_admin_list();

    Log({std::string{"Token for bot - "}, token}, "Start", "");
    Bot bot(token);
    
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }

    return 0;
}