#include "Tree.hpp"
#include <iostream>
#include <vector>


template <typename T>
Tree<T>::Tree(int k = 2) : root (nullptr), k(k) {}

template <typename T>
Tree<T>::~Tree() {
    delete_tree(root);
}

template <typename T>
void Tree<T>::delete_tree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    for (auto child : node->children) {
        delete_tree(child);
    }
    delete node;
}

// Explicit instantiation
// we separated the implementation from the declaration, and for that reason
// we need to explicitly instantiate the classes we want to use because
// the compiler needs to know about all the possible types that could be used 
// with the template when it compiles the .cpp file. 

template Tree<int>::Tree(int k);
template Tree<int>::~Tree();
template class Tree<int>;

template Tree<char>::Tree(int k);
template Tree<char>::~Tree();
template class Tree<char>;

template Tree<double>::Tree(int k);
template Tree<double>::~Tree();
template class Tree<double>;

template Tree<float>::Tree(int k);
template Tree<float>::~Tree();
template class Tree<float>;

template Tree<std::string>::Tree(int k);
template Tree<std::string>::~Tree();
template class Tree<std::string>;








