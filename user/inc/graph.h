#ifndef __BASIC_GRAPH_H__
#define __BASIC_GRAPH_H__

#include <iostream>
#include <vector>

#include "nodes.h"

class Graph {
public:
    Graph() = default;
    void DeleteNode(const std::string id);
    void DeleteNodeFromNodeAfter(__node_s& node, const std::string id);
    void AddNode(struct __node_s* node);
    void PrintIdsRecursive(const std::vector<__node_s*> nodes, std::string indent);

    std::vector<__node_s*>* NodesPrt()
    {
        return &m_nodes;
    }
    __node_s* FindNode(const std::string id);

    ~Graph()
    {
        m_nodes.clear();
    }

private:
    std::vector<__node_s*> m_nodes;

    __node_s m_root_node;
};

#endif