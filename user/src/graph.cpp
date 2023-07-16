#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include "graph.h"
#include "nodes.h"

void Graph::AddNode(struct __node_s* node)
{
    m_nodes.push_back(node);
}

void Graph::PrintIdsRecursive(const std::vector<__node_s*> nodes, std::string indent) {
    for (size_t i = 0; i < nodes.size(); ++i) {
        const __node_s* node = nodes[i];
        std::cout << indent;
        if (i == nodes.size() - 1) {
            std::cout << "└─ ";
            indent += std::string("   ");
        } else {
            std::cout << "├─ ";
            indent += std::string("│  ");
        }
        std::cout << node->id << std::endl;
        PrintIdsRecursive(node->node_after, indent);
    }
}

__node_s* Graph::FindNode(const std::string id)
{
    for (__node_s* g_node : m_nodes) {
        
        if (g_node->id == id) {
            return g_node;
        }
    }
}