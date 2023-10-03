#ifndef __PQXX_CONN_H__
#define __PQXX_CONN_H__

#include <iostream>
#include <pqxx/pqxx>

#include "log.h"

namespace db_api {

class PsqlConnector {
public:
    PsqlConnector() = delete;
    PsqlConnector(const char* dbname, const char* user, const char* password)
    {
        m_user = user;
        m_database = dbname;
        m_password = password;
        Log("Create a connection", "Start");
        conn = new pqxx::connection(std::move(" user=" + m_user + " password=" + m_password + " hostaddr=" + m_host + " dbname=" + m_database + " port=" + m_port));
    }
    PsqlConnector(const char* dbname,
        const char* user,
        const char* password,
        const char* host,
        const char* port)
    {
        m_user = user;
        m_database = dbname;
        m_password = password;
        m_port = port;
        m_host = host;
        Log("Create a connection", "Start");
        conn = new pqxx::connection(std::move(" user=" + m_user + " password=" + m_password + " hostaddr=" + m_host + " dbname=" + m_database + " port=" + m_port));
    }

    ~PsqlConnector() = default;

    void StopConnection();

    pqxx::result ExecuteRequest(const char* request);

    std::vector<std::string> NameEvents(const int64_t id_in_db);

    int IdByName(const std::string name);

    void AddEvent(const std::string name,
        const std::string desc,
        const std::string date);
    void AddReview(const std::string event_id,
        const int64_t user_id,
        const std::string date,
        const std::string mark,
        const std::string change,
        const std::string good_things,
        const std::string next_year);
    
    std::vector<int64_t> GetAllUsers();

    std::vector<std::string> ReadReviews(const int event_id);

    std::vector<std::string> GetAllEvents();
    
    pqxx::connection* conn;

private:
    std::string m_database = "dialog2023";
    std::string m_user = "gleb";
    std::string m_host = "127.0.0.1";
    std::string m_port = "5432";
    std::string m_password = "1957";

    std::string m_eventTableName = "eventsdemo";
};

} // namespace db_api
#endif
