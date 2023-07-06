#ifndef __PQXX_CONN_H__
#define __PQXX_CONN_H__

#include <iostream>
#include <pqxx/pqxx>

typedef long long ll;

namespace db_api { 
    
class PsqlConnector {

    

    public:
        PsqlConnector() = delete;
        PsqlConnector(const char* dbname, const char* user, const char* password) {
            m_user = user;
            m_database = dbname;
            m_password = password;
            SetupConnection();
        }
        PsqlConnector(const char* dbname, const char* user, const char* password, const char* host, const char* port) {
            m_user = user;
            m_database = dbname;
            m_password = password;
            m_port = port;
            m_host = host;
            SetupConnection();
        }

        ~PsqlConnector() {
            StopConnection();
        }
        
        void SetupConnection();
        void StopConnection();

        pqxx::result ExecuteRequest(const char* request);

        std::vector<std::string> NameEvents(const ll id_in_db);

        int IdByName(const std::string name);
        
        void AddEvent(const std::string name, const std::string desc, const std::string date);
        void AddReview(const std::string event_id, const ll user_id, const std::string date, const int mark, const std::string change, const std::string good_things, const bool next_year);

        pqxx::connection* conn;
    private:
        std::string m_database = "dialog2023";
        std::string m_user = "gleb";
        std::string m_host = "127.0.0.1"; 
        std::string m_port = "5432" ;
        std::string m_password = "1957";

        std::string m_eventTableName = "eventsdemo";


};

}
#endif