#include <iostream>
#include <pqxx/pqxx>

#include "pqxx_conn.h"

#include "time_treatment.h"
#include "log.h"

namespace db_api { 
    void PsqlConnector::SetupConnection() {
        Log("Create a connection");
        conn = new pqxx::connection(
            " user=" + m_user +
            " password=" + m_password +
            " hostaddr=" + m_host +
            " dbname=" + m_database +
            " port=" + m_port
        );
    }

    void PsqlConnector::StopConnection() {
        Log("Соединение с базой данных закрыто");
        delete conn;
    }

    pqxx::result PsqlConnector::ExecuteRequest(const char* request) {
        pqxx::work txn(*conn); // transaction

        pqxx::result result = txn.exec(request);
        txn.commit();

        return result;
    }
}
