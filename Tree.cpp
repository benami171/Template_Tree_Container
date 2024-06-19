#include "Tree.hpp"

template <typename T>
void delete_tree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    for (auto child : node->children) {
        delete_tree(child);
    }
    delete node;
};