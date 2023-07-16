#ifndef __BASIC_NODES_H__
#define __BASIC_NODES_H__

#include <iostream>
#include <vector>


struct __node_s {
    std::vector<struct __node_s*> node_after;
    std::string id;
    bool operator==(const __node_s& other) const
    {
        return id == other.id && node_after == other.node_after;
    }

    __node_s(std::string n_id) {
        node_after = std::vector<struct __node_s*>(); 
        id = n_id;
    }

    __node_s(std::string n_id, std::vector<struct __node_s*> after) {
        id = n_id;
        node_after = after;
    }

    __node_s() {
        id = "";
    }
    /*~__node_s() {

        for (__node_s* node : node_after) {
            if (node == nullptr) {
                continue;
            }
            
            delete node;
        }
    }*/

};

#endif