#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Node{
    public:
    T value;
    std::vector<Node<T>*> children;

    Node(T value) : value(value) {}

    const T &get_value() const {return value;}
    const std::vector<Node<T>*> &get_children() const {return children;}
    
    bool operator<(const Node<T>& other) const
    {
        return value < other.value;
    }

    bool operator>(const Node<T>& other) const
    {
        return value > other.value;
    }

    bool operator==(const Node<T>& other) const
    {
        return (!(value < other.value)) && (!(value > other.value));
    }

    bool operator!=(const Node<T>& other) const
    {
        return !(*this == other);
    }


};