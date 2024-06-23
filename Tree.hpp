#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

#include "Node.hpp"

#define BINARY 2
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

template <typename T, int K = BINARY>
class Tree {
   private:
    Node<T>* root;
    int max_children = K;

    void delete_tree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        delete node;
    }

    // Helper method to find a node
    Node<T>* find_node(Node<T>* node, const T& value) {
        if (node == nullptr) return nullptr;
        if (node->value == value) return node;
        for (auto child : node->children) {
            Node<T>* found = find_node(child, value);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

   public:
    explicit Tree() : root(nullptr) {}

    ~Tree() {
        delete_tree(root);
    }

    int get_max_children() const { return max_children; }

    void add_root(Node<T>& node) {
        if (root != nullptr) {
            delete_tree(root);
        }
        Node<T>* newRoot = new Node<T>(node);
        root = newRoot;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        Node<T>* parentNode = find_node(root, parent.get_value());
        if (parentNode == nullptr) {
            throw std::runtime_error("Parent node not found in the tree");
        }

        if (parentNode->children.size() < K) {
            Node<T>* newChild = new Node<T>(child);
            parentNode->children.push_back(newChild);
        } else {
            throw std::runtime_error("Parent has reached its maximum number of children");
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

        Node<T>* operator*() const {
            return stk.top();
        }

        Node<T>* operator->() const {
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

    class in_order_iterator {
       private:
        Node<T>* current;
        std::stack<Node<T>*> stk;

        void push_left(Node<T>* node) {
            while (node) {
                stk.push(node);
                if (!node->children.empty()) {
                    node = node->children[LEFT_CHILD];
                } else {
                    node = nullptr;
                }
            }
        }

       public:
        in_order_iterator(Node<T>* root) {
            Node<T>* node = root;
            while (node) {
                stk.push(node);
                if (!node->children.empty()) {
                    node = node->children[LEFT_CHILD];
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

        Node<T>* operator->() const {
            return current;
        }

        in_order_iterator& operator++() {
            if (!current->children.empty() && current->children.size() > 1) {
                Node<T>* node = current->children[RIGHT_CHILD];
                while (node) {
                    stk.push(node);
                    if (!node->children.empty()) {
                        node = node->children[LEFT_CHILD];
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

    // pre order for BINARY tree
    class pre_order_iterator {
       private:
        std::stack<Node<T>*> nodes_stack;

       public:
        pre_order_iterator(Node<T>* root) {
            if (root != nullptr) {
                nodes_stack.push(root);
            }
        }

        Node<T>* operator*() const {
            return nodes_stack.top();
        }

        Node<T>* operator->() const {
            return nodes_stack.top();
        }

        pre_order_iterator& operator++() {
            Node<T>* current = nodes_stack.top();
            nodes_stack.pop();
            if (current->children.size() == BINARY) {
                // For binary trees, push the right child first, then the left child
                nodes_stack.push(current->children[RIGHT_CHILD]);
                nodes_stack.push(current->children[LEFT_CHILD]);
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

    // POST ORDER FOR BINARY TREE
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

        Node<T>* operator->() const {
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

    class bfs_iterator {
       private:
        Node<T>* current;
        std::deque<Node<T>*> queue;

       public:
        bfs_iterator(Node<T>* root) {
            if (root) {
                queue.push_back(root);
            }
            advance();
        }

        void advance() {
            if (queue.empty()) {
                current = nullptr;
                return;
            }
            current = queue.front();
            queue.pop_front();
            for (auto child : current->children) {
                queue.push_back(child);
            }
        }

        Node<T>* operator*() const {
            return current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bfs_iterator& operator++() {
            advance();
            return *this;
        }

        bool operator!=(const bfs_iterator& other) const {
            return current != other.current;
        }
    };

    class min_heap_iterator {
       private:
        Node<T>* current;
        std::queue<Node<T>*> nodesQueue;

       public:
        // Constructor
        min_heap_iterator(Node<T>* root) {
            if (root != nullptr) {
                nodesQueue.push(root);
                current = root;  // Initialize current to root
            }
        }

        // Access the current element
        Node<T>* operator*() {
            return current;
        }

        Node<T>* operator->() {
            return current;
        }

        // Move to the next element
        min_heap_iterator& operator++() {
            if (!nodesQueue.empty()) {
                nodesQueue.pop();  // Pop the current node
                for (auto child : current->children) {
                    if (child != nullptr) nodesQueue.push(child);
                }
                current = !nodesQueue.empty() ? nodesQueue.front() : nullptr;  // Update current to the next node
            }
            return *this;
        }

        // Check for inequality
        bool operator!=(const min_heap_iterator& other) const {
            return current != other.current;
        }
    };

    using iterator_type = typename std::conditional<K == BINARY, pre_order_iterator, dfs_iterator>::type;
    using iterator_type2 = typename std::conditional<K == BINARY, post_order_iterator, dfs_iterator>::type;
    using iterator_type3 = typename std::conditional<K == BINARY, in_order_iterator, dfs_iterator>::type;
    using iterator_type4 = typename std::conditional<K == BINARY, min_heap_iterator, dfs_iterator>::type;

    iterator_type begin_pre_order() {
        return iterator_type(root);
    }

    iterator_type end_pre_order() {
        return iterator_type(nullptr);
    }

    iterator_type2 begin_post_order() {
        return iterator_type2(root);
    }

    iterator_type2 end_post_order() {
        return iterator_type2(nullptr);
    }

    iterator_type3 begin_in_order() {
        return iterator_type3(root);
    }

    iterator_type3 end_in_order() {
        return iterator_type3(nullptr);
    }

    dfs_iterator begin_dfs_scan() {
        return dfs_iterator(root);
    }

    dfs_iterator end_dfs_scan() {
        return dfs_iterator(nullptr);
    }

    bfs_iterator begin_bfs_scan() {
        return bfs_iterator(root);
    }

    bfs_iterator end_bfs_scan() {
        return bfs_iterator(nullptr);
    }

    iterator_type4 begin_min_heap() {
        return iterator_type4(root);
    }

    iterator_type4 end_min_heap() {
        return iterator_type4(nullptr);
    }

    std::pair<iterator_type4, iterator_type4> myHeap() {
        return std::make_pair(begin_min_heap(), end_min_heap());
    }
};
