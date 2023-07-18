#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "graph.h"
#include "nodes.h"
#include "pqxx_conn.h"
#include "time_treatment.h"
#include "user.h"

// Bad. We need to check our state, because we have end states;
void User::NextState(const std::string state)
{
    __node_s* current_node = m_tree_states.FindNode(m_id_state);

    Log("Текущее состояние пользователя: " + current_node->id, "User");
    if (state == "") {
        if (m_id_state == CHOOSE_NODE_ID) {
            m_id_state = m_name_chose_event + NAMES_NODE_REVIEW[0];
        } else {

            m_id_state = current_node->node_after[0]->id;
        }
    } else {
        if (ValidState(state)) {
            m_id_state = state;
        }
    }
}

bool User::ValidState(const std::string possible_state)
{
    __node_s current_node = *m_tree_states.FindNode(m_id_state);
    for (__node_s* after_node : current_node.node_after) {
        if (after_node->id == possible_state) {
            return true;
        }
    }
    return false;
}

void User::DeleteEventNode(const std::string nameEvent)
{
    // m_tree_states.DeleteNode(nameEvent + NAMES_NODE_REVIEW[0]);
}

// In russian this is call govnocode. I will change to for
void User::GenerateTreeStates(db_api::PsqlConnector conn, const bool admin)
{

    __node_s* choose_node = new __node_s(CHOOSE_NODE_ID);

    SetPossibleEvents(conn);

    for (std::string event : GetPossibleEvents()) {
        __node_s* node1 = new __node_s(event + NAMES_NODE_REVIEW[0]);
        __node_s* node2 = new __node_s(event + NAMES_NODE_REVIEW[1]);
        __node_s* node3 = new __node_s(event + NAMES_NODE_REVIEW[2]);
        __node_s* node4 = new __node_s(event + NAMES_NODE_REVIEW[3]);

        node1->node_after.push_back(node2);
        node2->node_after.push_back(node3);
        node3->node_after.push_back(node4);
        choose_node->node_after.push_back(node1);

        m_tree_states.NodesPrt()->push_back(node1);
        m_tree_states.AddNode(node2);
        m_tree_states.AddNode(node3);
        m_tree_states.AddNode(node4);
    }
    __node_s* start_node;
    if (admin) {
        __node_s* add_date = new __node_s(ADD_DATE_EVENT_NODE_ID, {});
        __node_s* add_desc = new __node_s(ADD_DESC_EVENT_NODE_ID, { add_date });
        __node_s* add_event = new __node_s(ADD_NAME_EVENT_NODE_ID, { add_desc });
        m_tree_states.AddNode(add_date);
        m_tree_states.AddNode(add_desc);
        m_tree_states.AddNode(add_event);

        __node_s* read_review = new __node_s(CHOOSE_REVIEWS_NODE_ID, {});
        m_tree_states.AddNode(read_review);

        start_node = new __node_s(START_NODE_ID, { choose_node, add_event, read_review });
    } else {
        start_node = new __node_s(START_NODE_ID, { choose_node });
    }

    m_tree_states.AddNode(start_node);
    m_tree_states.AddNode(choose_node);
    m_id_state = start_node->id;

    // m_tree_states.PrintIdsRecursive(start_node->node_after, "");
}

void User::AddReview(db_api::PsqlConnector conn)
{
    conn.AddReview(std::to_string(conn.IdByName(m_name_chose_event)), m_id,
        "\'" + CurrentDataTime(DEAFULT_PSQL_FORMAT_DATE) + "\'", "\'" + m_input[0] + "\'", "\'" + m_input[1] + "\'",
        "\'" + m_input[2] + "\'", "\'" + m_input[3] + "\'");
}

void User::AddEvent(db_api::PsqlConnector conn)
{
    conn.AddEvent("\'" + m_input[0] + "\'", "\'" + m_input[1] + "\'", "\'" + m_input[2] + "\'");
}