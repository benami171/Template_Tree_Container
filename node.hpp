#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Node {

   public:
    T value;
    std::vector<Node<T>*> children;
    
    // Constructor
    Node(T value) : value(value) {}
    // Copy Constructor (deep copy)
    
    Node(Node<T>& other) : value(other.value) {
        children.reserve(other.children.size());
        for (auto& child : other.children) {
            children.push_back(new Node<T>(*child));
        }
    }

    // Destructor
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }

    const T& get_value() const { return value; }
    const std::vector<Node<T>*>& get_children() const { return children; }

    Node& operator=(const Node<T>& other) {
        if (this != &other) {  // protect against self-assignment
            value = other.value;
            // Deep copy of children
            for (auto child : children) {
                delete child;
            }
            children.clear();
            children.reserve(other.children.size());
            for (const auto& child : other.children) {
                children.push_back(new Node<T>(*child));
            }
        }
        return *this;
    }

    bool operator<(const Node<T>& other) const { return value < other.value; }
    bool operator>(const Node<T>& other) const { return value > other.value; }
    bool operator==(const Node<T>& other) const { return value == other.value; }
    bool operator!=(const Node<T>& other) const { return !(*this == other); }
};