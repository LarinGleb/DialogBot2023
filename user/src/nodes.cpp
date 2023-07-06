#include <iostream>
#include <vector>

#include "nodes.h"

__node_s __create_node(const std::string name_node) {
    __node_s node;

    node.id = name_node;

    return node;
}

__node_s __create_node(const std::string name_node, std::vector<struct __node_s> node_after) {
    __node_s node;

    node.id = name_node;
    node.node_after = node_after;

    return node;
}
