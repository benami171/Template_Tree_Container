#pragma once

#include <iostream>
#include <vector>
#include <type_traits>
#include "complex.hpp"

using namespace std;

template <typename T>
class Node {
   public:
    T value;
     vector<Node<T>*> children;

    // Constructor
    Node(T value) : value(value) {}
    
    // Constructor for complex numbers, enabled only if T is Complex
    template <typename U = T>
    Node(double real, double imag, typename enable_if<is_same<U, Complex>::value>::type* = 0)
        : value(real, imag) {}

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
    string to_string() const { 
        if(typeid(T) == typeid(Complex)){
            return value.to_string();
        } else {
            return std::to_string(value);
        }
    }

    const  vector<Node<T>*>& get_children() const { return children; }

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