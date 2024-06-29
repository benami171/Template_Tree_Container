// Created by: Gal Ben Ami
// email: benami171@gmail.com
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "complex.hpp"

template <typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    explicit Node(T value) : value(value) {}

    void add_child(Node<T>* child) {
        if (child) {
            children.push_back(child);
        }
    }

    void delete_children() {
        children.clear();
    }

    T& get_value() {
        return value;
    }

    const std::vector<Node<T>*>& get_children() const {
        return children;
    }

    std::string to_string() const {
        return value_to_string(value);
    }

private:
    template <typename U>
    std::string value_to_string(const U& val) const {
        std::ostringstream oss;
        oss << val;  // Relying on the stream operator for non-Complex types
        return oss.str();
    }

    std::string value_to_string(const Complex& val) const {
        return val.to_string();
    }
};
