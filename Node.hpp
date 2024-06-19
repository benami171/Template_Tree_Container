#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Node{
    public:
    T value;
    std::vector<Node<T>*> children;

    explicit Node(T value): value(value){}

    T getValue() const{
        return value;
    }

};