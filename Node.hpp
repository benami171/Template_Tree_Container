#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Node{
    public:
    T value;
    std::vector<Node<T>*> children;

    Node(T value) : value(value) {}

    T get_value() const
    {
        return value;
    }

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