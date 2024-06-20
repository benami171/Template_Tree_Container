#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <algorithm>
#include "Node.hpp"

template<typename T, int K = 2>
class Tree{
    private:
    Node<T>* root;

    void delete_tree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        for (auto child : node->children) {
            delete_tree(child);
        }
        delete node;
    }

    public:
    explicit Tree() : root (nullptr) {}

    ~Tree() {
        delete_tree(root);
    }

    void add_root(Node<T>& node) {
        root = &node;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if(parent.children.size() < K) {
            parent.children.push_back(&child);
        }
        else {
            std::cout << "Parent has reached its maximum number of children" << std::endl;
        }
    }
};