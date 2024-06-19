#include "Tree.hpp"
#include <iostream>
#include <vector>


template<typename T,int K>
Tree<T,K>::Tree() : root (nullptr) {}

template<typename T,int K>
Tree<T,K>::~Tree() {
    delete_tree(root);
}

template<typename T,int K>
void Tree<T,K>::delete_tree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    for (auto child : node->children) {
        delete_tree(child);
    }
    delete node;
}

template<typename T,int K>
void Tree<T,K>::add_root(Node<T>& node) {
    root = &node;
}

template<typename T,int K>
void Tree<T,K>::add_sub_node(Node<T>& parent, Node<T>& child) {
    if(parent.children.size() < K) {
        parent.children.push_back(&child);
    }
    else {
        std::cout << "Parent has reached its maximum number of children" << std::endl;
    }
}

// Explicit instantiation
// we separated the implementation from the declaration, and for that reason
// we need to explicitly instantiate the classes we want to use because
// the compiler needs to know about all the possible types that could be used 
// with the template when it compiles the .cpp file. 

// template Tree<int,k>::Tree(int k);
// template Tree<int,k>::~Tree();
// template class Tree<int,k>;

// template Tree<char,k>::Tree(int k);
// template Tree<char,k>::~Tree();
// template class Tree<char,k>;

// template Tree<double,k>::Tree(int k);
// template Tree<double,k>::~Tree();
// template class Tree<double,k>;

// template Tree<float,k>::Tree(int k);
// template Tree<float,k>::~Tree();
// template class Tree<float,k>;

// template Tree<std::string,k>::Tree(int k);
// template Tree<std::string,k>::~Tree();
// template class Tree<std::string,k>;








