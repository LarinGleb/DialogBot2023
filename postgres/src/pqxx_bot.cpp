#include <iostream>
#include <string>
#include <vector>

#include <pqxx/pqxx>

#include "log.h"
#include "pqxx_conn.h"


namespace db_api {

std::vector<std::string> PsqlConnector::NameEvents(const int64_t id_in_db)
{
    std::string request = std::string(
                              "SELECT name FROM events WHERE id IN (SELECT id FROM events WHERE "
                              "id NOT IN (SELECT event_id FROM reviews WHERE user_id =")
        + std::to_string(id_in_db) + std::string(") AND AGE(CURRENT_DATE, events.date::DATE) <= INTERVAL '1 "
                                                 "days' AND CURRENT_DATE >= events.date)");

    pqxx::result possibleEvents = ExecuteRequest(request.c_str());

    std::vector<std::string> names;
    for (pqxx::result::const_iterator row = possibleEvents.begin();
         row != possibleEvents.end(); ++row) {
        names.push_back(row[0].as<std::string>());
    }
    return names;
}
void PsqlConnector::AddEvent(const std::string name,
    const std::string desc,
    const std::string date)
{
    std::string request = std::string("INSERT INTO events(name, description, date) VALUES(") + name + "," + desc + "," + date + std::string(");");
    Log("Добавлено мероприятие " + name, "Admin");
    ExecuteRequest(request.c_str());
}

void PsqlConnector::AddReview(const std::string event_id,
    const int64_t user_id,
    const std::string date,
    const std::string mark,
    const std::string change,
    const std::string good_things,
    const std::string next_year)
{
    Log("Пользователь " + std::to_string(user_id) + " добавил отзыв", "User");
    std::string request = std::string(
                              "INSERT INTO reviews(event_id, user_id, date, mark_event, "
                              "change, good, next_year) VALUES(")
        + event_id + "," + std::to_string(user_id) + "," + date + "," + mark + "," + change + "," + good_things + "," + next_year + ");";
    ExecuteRequest(request.c_str());
}

int PsqlConnector::IdByName(const std::string name)
{
    std::string request = std::string("SELECT id FROM events WHERE name = " + name);

    pqxx::result id = ExecuteRequest(request.c_str());

    return std::get<0>(id[0].as<int>());
}
} // namespace db_api
/*

SELECT name FROM events where id IN // where id in list of possible ids
(SELECT id
FROM events
WHERE id NOT IN ( // where no reviews by current id
 SELECT event_id
 FROM reviews
 WHERE user_id = 123
)
AND AGE(CURRENT_DATE, events.date::DATE) <= INTERVAL '1 days' AND // and
current   date is valid   CURRENT_DATE >= events.date)



*/