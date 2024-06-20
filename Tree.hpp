#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "Node.hpp"

template <typename T, int K = 2>
class Tree {
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
    explicit Tree() : root(nullptr) {}

    ~Tree() {
        delete_tree(root);
    }

    void add_root(Node<T>& node) {
        root = &node;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < K) {
            parent.children.push_back(&child);
        } else {
            std::cout << "Parent has reached its maximum number of children" << std::endl;
        }
    }

    class pre_order_iter {
       private:
        std::stack<Node<T>*> nodes_stack;

       public:
        pre_order_iter(Node<T>* root) {
            if (root != nullptr) {
                nodes_stack.push(root);
            }
        }

        Node<T>* operator*() {
            return nodes_stack.top();
        }

        pre_order_iter& operator++() {
            Node<T>* current = nodes_stack.top();
            nodes_stack.pop();
            if (K == 2 && current->children.size() == 2) {
                // For binary trees, push the right child first, then the left child
                nodes_stack.push(current->children[1]);
                nodes_stack.push(current->children[0]);
            } else {
                // For non-binary trees, push all children in reverse order
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    nodes_stack.push(*it);
                }
            }
            return *this;
        }

        bool operator!=(const pre_order_iter& other) {
            return nodes_stack.size() != other.nodes_stack.size();
        }
    };

    

    pre_order_iter begin_pre_order() {
        return pre_order_iter(root);
    }

    pre_order_iter end_pre_order() {
        return pre_order_iter(nullptr);
    }
};