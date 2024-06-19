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
#include <algorithm>
#include "Node.hpp"



template<typename T, int K = 2>
class Tree{
    private:
    Node<T>* root;


    void delete_tree(Node<T>* node);

    public:
    explicit Tree();
    ~Tree();

    void add_root(Node<T>& node);
    void add_sub_node(Node<T>& parent, Node<T>& child);


};