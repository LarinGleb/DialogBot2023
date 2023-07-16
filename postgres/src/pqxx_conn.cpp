#include <iostream>
#include <pqxx/pqxx>

#include "pqxx_conn.h"

#include "log.h"
#include "time_treatment.h"

namespace db_api {

void PsqlConnector::StopConnection()
{
    Log("Соединение с базой данных закрыто.", "Stop");
    conn->close();
}

pqxx::result PsqlConnector::ExecuteRequest(const char* request)
{
    pqxx::work txn(*conn); // transaction

    pqxx::result result = txn.exec(request);
    txn.commit();

    Log("Get request " + std::string(request), "Database");
    return result;
}
} // namespace db_api
