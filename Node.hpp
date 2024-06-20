#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Node{
    public:
    T value;
    std::vector<Node<T>*> children;

    Node(T value);

    T getValue() const;

};