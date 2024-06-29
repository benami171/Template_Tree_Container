// Created by: Gal Ben Ami
// email: benami171@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "complex.hpp"
#include "doctest.h"
#include "node.hpp"
#include "tree.hpp"

using namespace std;

TEST_CASE("Binary character tree iterators") {
    Node<char> root('a');
    Node<char> b('b');
    Node<char> c('c');
    Node<char> d('d');
    Node<char> e('e');
    Node<char> f('f');
    Node<char> g('g');
    Node<char> h('h');
    Node<char> i('i');

    Tree<char> tree;
    tree.add_root(&root);
    tree.add_sub_node(&root, &b);
    tree.add_sub_node(&root, &c);
    tree.add_sub_node(&b, &d);
    tree.add_sub_node(&b, &e);
    tree.add_sub_node(&c, &f);
    tree.add_sub_node(&c, &g);
    tree.add_sub_node(&f, &h);
    tree.add_sub_node(&f, &i);

    // The tree should look like:
    /**
     *      root =
     *             a
     *          /     \
     *         b        c
     *        /  \     / \
     *       d    e   f   g
     *              /  \
     *             h    i
     */
    SUBCASE("DFS traversal using char tree") {
        string expected = "a b d e c f h i g ";
        string result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result += node->get_value();
            result += " ";
        }
        CHECK(expected == result);
    }

    SUBCASE("Pre order traversal using char tree") {
        string expected = "a b d e c f h i g ";
        string result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            result += node->get_value();
            result += " ";
        }
        CHECK(expected == result);
    }

    SUBCASE("In order traversal using char tree") {
        string expected = "d b e a h f i c g ";
        string result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            result += node->get_value();
            result += " ";
        }
        CHECK(expected == result);
    }

    SUBCASE("Post order traversal using char tree") {
        string expected = "d e b h i f g c a ";
        string result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            result += node->get_value();
            result += " ";
        }
        CHECK(expected == result);
    }
};

TEST_CASE("Empty tree traversal") {
    Tree<char> empty_tree;
    string result;
    for (auto node = empty_tree.begin_dfs_scan(); node != empty_tree.end_dfs_scan(); ++node) {
        result += node->get_value();
        result += " ";
    }
    CHECK(result.empty());
};

TEST_CASE("Single node tree traversal") {
    Node<char> single('x');
    Tree<char> single_node_tree;
    single_node_tree.add_root(&single);
    string expected = "x ";
    string result;
    for (auto node = single_node_tree.begin_dfs_scan(); node != single_node_tree.end_dfs_scan(); ++node) {
        result += node->get_value();
        result += " ";
    }
    CHECK(expected == result);
};

TEST_CASE("Tree with only left children traversal") {
    Node<char> left_root('l');
    Node<char> l1('m');
    Node<char> l2('n');
    Tree<char> left_tree;
    left_tree.add_root(&left_root);
    left_tree.add_sub_node(&left_root, &l1);
    left_tree.add_sub_node(&l1, &l2);
    string expected = "l m n ";
    string result;
    for (auto node = left_tree.begin_dfs_scan(); node != left_tree.end_dfs_scan(); ++node) {
        result += node->get_value();
        result += " ";
    }
    CHECK(expected == result);
};

TEST_CASE("Tree with only right children traversal") {
    Node<char> right_root('r');
    Node<char> r1('s');
    Node<char> r2('t');
    Tree<char> right_tree;
    right_tree.add_root(&right_root);
    right_tree.add_sub_node(&right_root, &r1);
    right_tree.add_sub_node(&r1, &r2);
    string expected = "r s t ";
    string result;
    for (auto node = right_tree.begin_dfs_scan(); node != right_tree.end_dfs_scan(); ++node) {
        result += node->get_value();
        result += " ";
    }
    CHECK(expected == result);
};

TEST_CASE("3-Ary tree") {
    SUBCASE("Pre order uses a dfs traversal for NON Binary tree") {
        Node<int> root(1);
        Node<int> n1(2);
        Node<int> n2(3);
        Node<int> n3(4);
        Node<int> n4(5);
        Node<int> n5(6);
        Node<int> n6(7);
        Node<int> n7(8);
        Tree<int, 3> tree;
        tree.add_root(&root);
        tree.add_sub_node(&root, &n1);
        tree.add_sub_node(&root, &n2);
        tree.add_sub_node(&root, &n3);
        tree.add_sub_node(&n1, &n4);
        tree.add_sub_node(&n1, &n5);
        tree.add_sub_node(&n2, &n6);
        tree.add_sub_node(&n2, &n7);
        string dfs;
        string pre_order_iterator;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            dfs += to_string(node->get_value());
            dfs += " ";
        }
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            pre_order_iterator += to_string(node->get_value());
            pre_order_iterator += " ";
        }
        CHECK(dfs == pre_order_iterator);
    }

    SUBCASE("In order uses a dfs traversal for NON Binary tree") {
        Node<int> root(1);
        Node<int> n1(2);
        Node<int> n2(3);
        Node<int> n3(4);
        Node<int> n4(5);
        Node<int> n5(6);
        Node<int> n6(7);
        Node<int> n7(8);
        Tree<int, 3> tree;
        tree.add_root(&root);
        tree.add_sub_node(&root, &n1);
        tree.add_sub_node(&root, &n2);
        tree.add_sub_node(&root, &n3);
        tree.add_sub_node(&n1, &n4);
        tree.add_sub_node(&n1, &n5);
        tree.add_sub_node(&n2, &n6);
        tree.add_sub_node(&n2, &n7);
        string dfs;
        string in_order_iterator;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            dfs += to_string(node->get_value());
            dfs += " ";
        }
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            in_order_iterator += to_string(node->get_value());
            in_order_iterator += " ";
        }
        CHECK(dfs == in_order_iterator);
    }
}
