#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "graph.h"
#include "nodes.h"

void Graph::AddNode(const struct __node_s* node, const std::string node_before_id) {
    for(__node_s g_node: nodes) {
        if (g_node.id == node_before_id) {
            g_node.node_after.push_back(*node);
            nodes.push_back(*node);
            return;
        }
    }
    std::cerr << "Cannot find node with this id!" << std::endl;

}

void Graph::DeleteNode(const std::string id) {
    for (auto it = nodes.begin(); it != nodes.end(); ) {
        if (it->id == id) {
            it = nodes.erase(it);
        } else {
            DeleteNodeFromNodeAfter(*it, id); 
            ++it; 
        }
    }
}

void Graph::DeleteNodeFromNodeAfter(__node_s& node, const std::string id) {
    for (auto it = node.node_after.begin(); it != node.node_after.end(); ) {
        if (it->id == id) {
            it = node.node_after.erase(it);
        } else {
            DeleteNodeFromNodeAfter(*it, id); 
            ++it;
        }
    }
}

__node_s Graph::FindNode(const std::string id) {
    for (__node_s g_node: nodes) {
        if(g_node.id == id) {
            return g_node;
        }
    }
    return __node_s();
}