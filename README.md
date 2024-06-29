# Iterators and Templates on trees.
In this project i implemented a template container that represents a K-ary tree that can hold Nodes of any type.

## How to run:
- run main program: in order to compile and run the program, type `qmake myProg.pro -config Prog` and than `make tree`.
- run tests: in order to compile and run the tests, type `qmake myProg.pro -config Test` and than `make test`.

## All the different classes and their hierarchy
- `tree.hpp` - a Template K-ary tree container, has a `Node<T>* root`. uses the `iterators.hpp` to travers the tree in different ways (depends what K is the tree).
Also, the `tree` class uses the `type_traits` library to use compile-time type manipulation based on certain conditions (see `Explenation about the tree container usage with iterators` below for additional explenation).
- `node.hpp` - a Template Node class to hold any type.
- `complex.hpp` - represents complex numbers, can be used by `node.hpp` to store complex numbers as data.
- We have 6 different iterator classes inside the file `iterators.hpp`:
- `in_order_iterator` - Traverses Binary tree in in-order way, for any (K!=2)-Tree will travers the tree using dfs.
- `pre_order_iterator` - Traverses Binary tree in pre-order way, for any (K!=2)-Tree will travers the tree using dfs.
- `post_order_iterator` - Traverses Binary tree in post-order way, for any (K!=2)-Tree will travers the tree using dfs.
- `min_heap_iterator` - Turns a Binary tree to a minimum heap and travers it ,for any (K!=2)-Tree will travers the tree using dfs.
- `dfs_iterator` - Works on any K-tree.
- `bfs_iterator` - Works on any K-tree.

### Explenation about the tree container usage with iterators.
- A template class that represents a K-ary tree (Binary by default), holds an access to the root node and its `K` value that represents the highest degree that a node can have in the tree.
- during Compile-time the program will detect which type of tree the iterator gets called on, and if the iterators `in_order_iterator`, `pre_order_iterator` or `post_order_iterator` was called with a K!=2-Tree, it will direct the type of iterator to be `dfs_iterator` in Compile-time.

- How it does it:
- in the Tree class, we have used `type_traits` in this way:
```cpp
    using iterator_pre_order = typename std::conditional<K == BINARY, pre_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_post_order = typename std::conditional<K == BINARY, post_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_in_order = typename std::conditional<K == BINARY, in_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_min_heap = typename std::conditional<K == BINARY, min_heap_iterator<T>, dfs_iterator<T>>::type;
```

- So for example when we call `in_order_iterator` in the main, on 3-Ary array :
```cpp
    Tree<double, 3> three_ary_tree;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order();++node) {
        cout << node->get_value() << " ";
    }
```
It will travers the tree using `bfs_iterator` and not `pre_order_iterator`.

- For further information and usage examples check out `main.cpp` ,`tree.hpp` ,`node.hpp` ,`iterators.hpp` and `complex.hpp`.
- You can see the different tests in the `test.cpp` class.


