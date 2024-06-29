# Iterators and Templates on trees.
- run main program: in order to compile and run the program, type `qmake myProg.pro -config Prog` and than `make tree`.
- run tests: in order to compile and run the tests, type `qmake myProg.pro -config Test` and than `make test`.

## Tree class
- A template class that represents a K-ary tree (Binary by default), holds an access to the root node and its `K` value that represents the highest degree that a node can have in the tree.
- during runtime the program will detect which type of tree the iterator gets called on, and if the iterators `in_order_iterator`, `pre_order_iterator` or `post_order_iterator` was called with a K!=2-Tree, it will direct the type of iterator to be `dfs_iterator` in runtime.

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

### Tree container private fields:
- `Node<T>* root` a pointer to the root node.
- `int max_children` the highest degree that a node can have in the tree, will be 2 by default.
### Tree container private methods:
- `Node<T>* find_node(Node<T>* node, const T& value)` in order to add the child node to the parent node we want to look for the parent node in the tree.

### Tree container public methods:
- `explicit Tree()` an explicit constructor
- `int get_max_children()` returns the K of the tree container.
- `Tree()` default constructor.
- `~Tree()` destrtuctor, traverses the nodes



has the Following Iterators:
- `in_order_iterator`
- `pre_order_iterator`
- `post_order_iterator`
- `dfs_iterator`
- `bfs_iterator` 

- For binary trees all the iterators work as expected, but for K-ary trees we will be directed to the dfs_iterator by all the different iterators in runtime.

