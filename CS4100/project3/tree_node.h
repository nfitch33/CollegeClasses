#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
#include <vector>
#include <iostream>

class TreeNode {
public:
    std::string name;
    int weight;
    std::vector<TreeNode*> children;

    TreeNode(const std::string& n, int w)
        : name(n), weight(w) {}

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    void print(int depth = 0) const {
        std::cout << name;

        if (!children.empty()) {
            std::cout << " [ ";

            for (size_t i = 0; i < children.size(); i++) {
                children[i]->print(depth + 1);
                if (i != children.size() - 1)
                    std::cout << ", ";
            }

            std::cout << " ]";
        }
    }

    ~TreeNode() {
        for (auto c : children)
            delete c;
    }
};

#endif