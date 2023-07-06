#ifndef __BASIC_NODES_H__
#define __BASIC_NODES_H__

#include <iostream>

//this is bad, because we have to storage ptr to next node. In our case we need only copy;
struct __node_s
{
    std::vector<struct __node_s> node_after;
    std::string id;  
    bool operator==(const __node_s& other) const {
        return id == other.id && node_after == other.node_after;
    }
};

__node_s __create_node(const std::string name_node);

__node_s __create_node(const std::string name_node, std::vector<struct __node_s> node_after);

#endif