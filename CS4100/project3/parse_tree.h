#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include "tree_node.h"
#include <map>
#include <string>
#include <iostream>

class ParseTree {
public:
    std::map<std::string, TreeNode*> trees;

    void assign(const std::string& id, TreeNode* node) {
        trees[id] = node;
    }

    void print(const std::string& id) {
        if (trees.count(id)) {
            trees[id]->print();
        } else {
            std::cout << "Undefined tree: " << id << std::endl;
        }
    }
};

#endif