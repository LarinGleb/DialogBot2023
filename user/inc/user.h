#ifndef __USER_CLASS_H__
#define __USER_CLASS_H__

#include <iostream>

#include "graph.h"
#include "crypt_id.h"
#include "pqxx_conn.h"

#define START_NODE_ID "CreateReview"
#define CHOOSE_NODE_ID "ChooseEvent"

#define NAMES_NODE_REVIEW (std::string[4]){"_mark", "_change", "_good", "_nextyear"}

typedef long long ll;

class User {
    public:
        User() = delete;
        User(const ll telegram_id) {
            m_id = crypt_id(telegram_id);
        }
        void NextState();
        bool ValidState(const std::string possible_state);

        void DeleteEventNode(const std::string nameEvent);
        void GenerateTreeStates(db_api::PsqlConnector conn, bool admin);
        ~User() = default;
        
        void DropUser();

        void AddReview(db_api::PsqlConnector conn);

    private:
        ll m_id = -1;
        
        int m_mark = -1;
        std::string m_good = std::string("");
        std::string m_change = std::string("");
        bool m_next_year = false;

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