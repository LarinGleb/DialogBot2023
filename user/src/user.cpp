#include <iostream>
#include <cstring>
#include <vector> 

#include "user.h"
#include "graph.h"
#include "nodes.h"
#include "pqxx_conn.h"
#include "time_treatment.h"

void User::NextState() {
    __node_s current_node = m_tree_states.FindNode(m_id_state);
    if (m_id_state == CHOOSE_NODE_ID) {
        m_id_state = m_name_chose_event + NAMES_NODE_REVIEW[0];
    }
    else if (current_node.node_after.size() != 0) {
        m_id_state = current_node.node_after[0].id;
    }
    else {
        return;
    }
}

bool User::ValidState(const std::string possible_state) {
    __node_s current_node = m_tree_states.FindNode(m_id_state);
    for (__node_s after_node: current_node.node_after) {
        if (after_node.id == possible_state) {
            return true;
        }
    }
    return false;
}


void User::DeleteEventNode(const std::string nameEvent) {
    m_tree_states.DeleteNode(nameEvent + NAMES_NODE_REVIEW[0]);
}

void User::GenerateTreeStates(db_api::PsqlConnector conn, bool admin) {
    m_tree_states = Graph();

    __node_s start_node = __create_node(START_NODE_ID);
    __node_s choose_node = __create_node(CHOOSE_NODE_ID, (std::vector<__node_s>){start_node});
    
    start_node.node_after.push_back(choose_node);

    std::vector<std::string> events = conn.NameEvents(m_id);

    for(std::string event : events) {
        __node_s current_node = __create_node(NAMES_NODE_REVIEW[0]);
        choose_node.node_after.push_back(current_node);
        for (int i = 1; i < 3; i ++) {
            __node_s new_node = __create_node(NAMES_NODE_REVIEW[i]);
            current_node.node_after.push_back(new_node);
            current_node = new_node;
        }
        current_node.node_after.push_back(__create_node(NAMES_NODE_REVIEW[3]));
    }


}

void User::DropUser() {
    m_tree_states = Graph();

    m_change = std::string("");
    m_good = std::string("");
    m_id_state = std::string("");
    m_mark = -1;
    m_name_chose_event = std::string("");
    m_next_year = false;
    
}

void User::AddReview(db_api::PsqlConnector conn) {
    conn.AddReview(std::to_string(conn.IdByName(m_name_chose_event)), m_id, CurrentDataTime(DEAFULT_PSQL_FORMAT_DATE), m_mark, m_change, m_good, m_next_year);
}