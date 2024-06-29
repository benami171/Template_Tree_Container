// Created by: Gal Ben Ami
// email: benami171@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"


using namespace std;

TEST_CASE("Binary character tree iterators"){
    Node<char> root('a');
    Node<char> b('b');
    Node<char> c('c');
    Node<char> d('d');
    Node<char> e('e');
    Node<char> f('f');
    Node<char> g('g');

    Tree<char> tree;
    tree.add_root(&root);
    tree.add_sub_node(&root, &b);
    tree.add_sub_node(&root, &c);
    tree.add_sub_node(&b, &d);
    tree.add_sub_node(&b, &e);
    tree.add_sub_node(&c, &f);
    tree.add_sub_node(&c, &g);

    // The tree should look like:
    /**
     *      root =  
     *             a
     *          /     \
     *         b       c
     *        /  \     /
     *       d    e   f
     *                \
     *                 g
     */
    SUBCASE("DFS"){
        string expected = "a b d e c f g ";
        string result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result += node->get_value();
            result += " ";
        }
        CHECK(expected == result);
    }


}