// Created by: Gal Ben Ami
// email: benami171@gmail.com
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>
#include "node.hpp"
#define BINARY 2
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

using namespace stSd;
template <typename T>
class dfs_iterator {
   private:
    std::stack<Node<T>*> stk;

   public:
    dfs_iterator(Node<T>* root) {
        if (root) {
            stk.push(root);
        }
    }

    T& operator*() const {
        return stk.top()->get_value();
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

    bool operator==(const dfs_iterator& other) const {
        if (stk.empty() && other.stk.empty()) return true;
        if (stk.empty() || other.stk.empty()) return false;
        return stk.top() == other.stk.top();
    }
    bool operator!=(const dfs_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
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
        push_left(root);
        if (!stk.empty()) {
            current = stk.top();
            stk.pop();
        } else {
            current = nullptr;
        }
    }

    T& operator*() const {
        return current->get_value();
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
    bool operator==(const in_order_iterator& other) const {
        return current == other.current;
    }
    bool operator!=(const in_order_iterator& other) const {
        return current != other.current;
    }
};

template <typename T>
class pre_order_iterator {
   private:
    std::stack<Node<T>*> nodes_stack;

   public:
    pre_order_iterator(Node<T>* root) {
        nodes_stack.emplace(nullptr);  // For the end, because we use top()
        if (root != nullptr) {
            nodes_stack.emplace(root);
        }
    }

    Node<T>* operator*() const {
        return nodes_stack.top()->get_value();
    }

    Node<T>* operator->() const {
        return nodes_stack.top();
    }

    pre_order_iterator& operator++() {
        Node<T>* current = nodes_stack.top();
        nodes_stack.pop();

        // If the current node has a right child, push it onto the stack.
        if (current->children.size() > 1) {
            if (current->children[1] != nullptr) {
                nodes_stack.emplace(current->children[1]);
            }
        }

        // If the current node has a left child, push it onto the stack.
        if (current->children.size() > 0) {
            if (current->children[0] != nullptr) {
                nodes_stack.emplace(current->children[0]);
            }
        }

        return *this; // Return a reference to this iterator to allow chaining.
    }

    bool operator==(const pre_order_iterator& other) const {
        if (nodes_stack.empty() && other.nodes_stack.empty()) {
            return true;
        }
        if (nodes_stack.empty() || other.nodes_stack.empty()) {
            return false;
        }
        return nodes_stack.top() == other.nodes_stack.top();
    }

    bool operator!=(const pre_order_iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
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

    // Helper function to advance the iterator
    void advance() {
        while (!stk.empty()) {
            Node<T>* node = stk.top();  // Get the current node
            if (node == nullptr) {
                stk.pop();  // Remove the null marker indicating a return to a parent node.
                if (!stk.empty()) {
                    current = stk.top();  // Set the current node to the next node in the stack.
                    stk.pop();            // Remove the current node from the stack.
                }
                return;
            }
            if (visited.find(node) == visited.end()) {  // If the node hasn't been visited yet.
                stk.push(nullptr);                      // Push a null marker to indicate a return to this node.
                push_children(node);                    // Push the children of the node onto the stack.
                visited.insert(node);                   // Mark the node as visited.
            } else {
                stk.pop();  // Remove the node from the stack if it has been visited.
            }
        }
        current = nullptr;  // No more nodes to visit.
    }

    T& operator*() const {
        return current->get_value();
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

template <typename T>
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

    T& operator*() const {
        return current->get_value();
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

template <typename T>
class min_heap_iterator {
   private:
    Node<T>* current;
    vector<Node<T>*> nodesVector;
    typename vector<Node<T>*>::iterator iter;

    // Helper function to build the min-heap in vector form
    void build_min_heap(Node<T>* node) {
        if (!node) return;
        nodesVector.push_back(node);
        for (auto child : node->get_children()) {
            build_min_heap(child);
        }
    }

   public:
    // Constructor
    min_heap_iterator(Node<T>* root) : current(nullptr) {
        if (root != nullptr) {
            // Recursively build the min-heap in vector form starting from the root node
            build_min_heap(root);

            // Sort the nodesVector to ensure min-heap order
            sort(nodesVector.begin(), nodesVector.end(), [](Node<T>* a, Node<T>* b) {
                // Compare the values of nodes to determine order
                return a->get_value() < b->get_value();
            });

            // Initialize the iterator to the beginning of the sorted vector
            iter = nodesVector.begin();

            // If the iterator is not at the end, set the current node to the first node in the vector
            if (iter != nodesVector.end()) {
                current = *iter;  // Dereference the iterator to get the node
            }
        }
    }

    T& operator*() {
        return current->get_value();
    }

    Node<T>* operator->() {
        return current;
    }

    // Move to the next element
    min_heap_iterator& operator++() {
        if (iter != nodesVector.end()) {
            ++iter;
            // If we reached the end, set current to nullptr
            current = (iter != nodesVector.end()) ? *iter : nullptr;
        }
        return *this;
    }

    // Check for inequality
    bool operator!=(const min_heap_iterator& other) const {
        return current != other.current;
    }
};
