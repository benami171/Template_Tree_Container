// will be a generic class of a tree. 
// it will have a constructor that gets int k = number of children each node can have at most. 
// if k isnt stated when the constructor was called , set k = 2 by default.
// the tree will contain nodes that contains templates of type T.
// we will want to implement a container that represent the tree thats mentioned above.



#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include "Node.hpp"



template<typename T>
class Tree{
    private:
    Node<T>* root;
    int k;

    void delete_tree(Node<T>* node);

    public:

    explicit Tree(int k = 2);
    ~Tree();

    void add_root
};