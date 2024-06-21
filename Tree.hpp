#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
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
    class dfs_iterator {
         private:
          std::stack<Node<T>*> stk;
    
         public:
          dfs_iterator(Node<T>* root) {
                if (root) {
                 stk.push(root);
                }
          }
    
          Node<T>* operator*() {
                return stk.top();
          }
    
          dfs_iterator& operator++() {
                Node<T>* current = stk.top();
                stk.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                 stk.push(*it);
                }
                return *this;
          }
    
          bool operator!=(const dfs_iterator& other) const {
                return !stk.empty();
          }
     };

    class pre_order_iterator {
       private:
        std::stack<Node<T>*> nodes_stack;

       public:
        pre_order_iterator(Node<T>* root) {
            if (root != nullptr) {
                nodes_stack.push(root);
            }
        }

        Node<T>* operator*() {
            return nodes_stack.top();
        }

        pre_order_iterator& operator++() {
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

        bool operator!=(const pre_order_iterator& other) const {
            return !nodes_stack.empty();
        }
    };


    class post_order_iterator {
       private:
        Node<T>* current;
        std::stack<Node<T>*> stk;
        std::unordered_set<Node<T>*> visited;

        void push_children(Node<T>* node) {
            if (node) {
                stk.push(node);
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    if (*it) stk.push(*it);
                }
            }
        }

       public:
        post_order_iterator(Node<T>* root) {
            push_children(root);
            advance();
        }

        void advance() {
            while (!stk.empty()) {
                Node<T>* node = stk.top();
                if (node == nullptr) {
                    stk.pop();
                    if (!stk.empty()) {
                        current = stk.top();
                        stk.pop();
                    }
                    return;
                }
                if (visited.find(node) == visited.end()) {
                    stk.push(nullptr);
                    push_children(node);
                    visited.insert(node);
                } else {
                    stk.pop();
                }
            }
            current = nullptr;
        }

        Node<T>* operator*() const {
            return current;
        }

        post_order_iterator& operator++() {
            advance();
            return *this;
        }

        bool operator!=(const post_order_iterator& other) const {
            return current != other.current;
        }
    };


    class in_order_iterator {
        //     friend class DFS<T>;  // Make DFS a friend class so it can access private members

       private:
        Node<T>* current;
        std::stack<Node<T>*> stk;


       public:
        in_order_iterator(Node<T>* root) {
            Node<T>* node = root;
            while (node) {
                stk.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
            if (!stk.empty()) {
                current = stk.top();
                stk.pop();
            }
        }

        Node<T>* operator*() const {
            return current;
        }

        in_order_iterator& operator++() {
            if (!current->children.empty() && current->children.size() > 1) {
                Node<T>* node = current->children[1];
                while (node) {
                    stk.push(node);
                    if (!node->children.empty()) {
                        node = node->children[0];
                    } else {
                        node = nullptr;
                    }
                }
            }
            if (!stk.empty()) {
                current = stk.top();
                stk.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        bool operator!=(const in_order_iterator& other) const {
            return current != other.current;
        }
    };

    class bfs_iterator{
        private:
        Node<T>* current;
        std::deque<Node<T>*> nodes_queue;

        public:

    };

    post_order_iterator begin_post_order() {
        return post_order_iterator(root);
    }

    post_order_iterator end_post_order() {
        return post_order_iterator(nullptr);
    }

    pre_order_iterator begin_pre_order() {
        return pre_order_iterator(root);
    }

    pre_order_iterator end_pre_order() {
        return pre_order_iterator(nullptr);
    }

    in_order_iterator begin_in_order() {
        return in_order_iterator(root);
    }

    in_order_iterator end_in_order() {
        return in_order_iterator(nullptr);
    }

    dfs_iterator begin_dfs_scan() {
        return dfs_iterator(root);
    }

    dfs_iterator end_dfs_scan() {
        return dfs_iterator(nullptr);
    }

};
