#ifndef __USER_CLASS_H__
#define __USER_CLASS_H__

#include <iostream>
#include <vector>

#include "crypt_id.h"
#include "graph.h"
#include "pqxx_conn.h"

#define CHOOSE_NODE_ID "ChooseEvent"
#define CHOOSE_REVIEWS_NODE_ID "ChooseEventReview"

#define START_NODE_ID "Start"

#define ADD_NAME_EVENT_NODE_ID "EventName"
#define ADD_DESC_EVENT_NODE_ID "EventDesc"
#define ADD_DATE_EVENT_NODE_ID "EventDate"


#define NAMES_NODE_REVIEW                        \
    (std::string[4])                             \
    {                                            \
        "_mark", "_change", "_good", "_nextyear" \
    }

class User {
public:
    User() = default;
    User(const int64_t cr_telegram_id, const db_api::PsqlConnector conn, const bool admin)
    {
        m_id = cr_telegram_id;
        m_tree_states = Graph();
        GenerateTreeStates(conn, admin);
    }

    void NextState(const std::string state = "");
    bool ValidState(const std::string possible_state);

    void DeleteEventNode(const std::string nameEvent);
    void GenerateTreeStates(db_api::PsqlConnector conn, const bool admin);

    void DeleteUser()
    {
        m_input.clear();
        m_events.clear();
    }

    ~User() = default;

    void AddReview(db_api::PsqlConnector conn);
    void AddEvent(db_api::PsqlConnector conn);

    // Geters

    std::string GetState()
    {
        return m_id_state;
    }

    std::string GetEvent()
    {
        return m_name_chose_event;
    }

    std::vector<std::string> GetPossibleEvents()
    {
        return m_events;
    }

    // sETERS

    void SetCurrentWorkingEvent(std::string event)
    {
        m_name_chose_event = event;
    }

    void AddInput(std::string input)
    {
        m_input.push_back(input);
    }

    void SetPossibleEvents(db_api::PsqlConnector conn)
    {
        m_events.clear();
        for (std::string event : conn.NameEvents(m_id)) {
            m_events.push_back(event);
        }
    }

private:
    int64_t m_id = -1;

    std::vector<std::string> m_input;
    std::vector<std::string> m_events;

    std::string m_name_chose_event = std::string("");

    Graph m_tree_states;
    std::string m_id_state = std::string("");
};

/* There are six nodes for basic user

1. NameEvent + _mark
2. NameEvent + _change
3. NameEvent + _good
4. NameEvent + _nextyear

5. CreateReview
6. ChooseEvent
*/

#endif