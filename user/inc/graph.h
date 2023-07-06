#ifndef __BASIC_GRAPH_H__
#define __BASIC_GRAPH_H__

#include <iostream>
#include <vector>

#include "nodes.h"

class Graph {

    public:
        void DeleteNode(const std::string id);
        void DeleteNodeFromNodeAfter(__node_s& node, const std::string id);
        void AddNode(const struct __node_s* node, const std::string node_before_id);
        
        __node_s FindNode(const std::string id);
        ~Graph() {
            if (!nodes.empty()) {
                DeleteNode(nodes.front().id);
            }
            nodes.clear();
        }
    private:
        std::vector<__node_s> nodes = std::vector<__node_s>();
};

#endif