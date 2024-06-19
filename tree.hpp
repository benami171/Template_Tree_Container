// will be a generic class of a tree. 
// it will have a constructor that gets int k = number of children each node can have at most. 
// if k isnt stated when the constructor was called , set k = 2 by default.
// the tree will contain nodes that contains templates of type T.
// we will want to implement a container that represent the tree thats mentioned above.



#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "node.hpp"

template<typename T>
class Tree{
    private:
    Node<T>* root;
    int k;

    void delete_tree(Node<T>* node){
        if(node == nullptr){
            return;
        }
        for(auto child: node->children){
            delete_tree(child);
        }
        delete node;
    }

    public:

    explicit Tree(int k = 2): root(nullptr), k(k){}
    ~Tree(){
        delete_tree(root);
    }

    void add_root
};