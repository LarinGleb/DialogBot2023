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
    std::string request = std::string("INSERT INTO events(name, description, date) VALUES(") + name + "," + desc + "," + +"TO_DATE(" + date + std::string(",\'DD.MM.YYYY\'));");
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
    std::string request = std::string("SELECT id FROM events WHERE name = ") + "\'" + name  + "\'" + ';';

    pqxx::result id = ExecuteRequest(request.c_str());

    return std::get<0>(id[0].as<int>());
}

std::vector<std::string> PsqlConnector::ReadReviews(const int event_id) {
    std::string request = std::string("SELECT * from reviews WHERE event_id = ") + std::to_string(event_id) + ';';

    pqxx::result db_reviews = ExecuteRequest(request.c_str());

    std::vector<std::string> reviews_str;
    std::string review;

    for (pqxx::result::const_iterator row = db_reviews.begin(); row != db_reviews.end(); ++row) {
        for (auto field = row.begin(); field != row.end(); ++field) {
            review += field->c_str();
            if (std::next(field) != row.end()) {
                review += ";";
            }
        }
        reviews_str.push_back(review);
        review = "";
    }
    return reviews_str;
}

std::vector<std::string> PsqlConnector::GetAllEvents() {
    std::string request = std::string("SELECT name from events;");
    
    pqxx::result db_events = ExecuteRequest(request.c_str());

    std::vector<std::string> events;
    for (pqxx::result::const_iterator row = db_events.begin(); row != db_events.end(); ++row) {
        events.push_back(row[0].as<std::string>());
    }

    return events;

}

std::vector<int64_t> PsqlConnector::GetAllUsers() {
    std::string request = std::string("SELECT DISTINCT user_id from reviews;");
    pqxx::result db_ids = ExecuteRequest(request.c_str());

    std::vector<int64_t> ids;
    for (pqxx::result::const_iterator row = db_ids.begin(); row != db_ids.end(); ++row) {
        ids.push_back(row[0].as<int64_t>());
    }
   return ids;


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
