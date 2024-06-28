# Iterators and Templates on trees.
- run main program: in order to compile and run the program, type `qmake myProg.pro -config Prog` and than `make tree`.
- run tests: in order to compile and run the tests, type `qmake myProg.pro -config Test` and than `make test`.

## Tree class
- A template class that represents a K-ary tree (Binary by default), holds an access to the root node and its `K` value that represents the highest degree that a node can have in the tree.
- during runtime the program will detect which type of tree the iterator got and if the iterators `in_order_iterator`, `pre_order_iterator` or `post_order_iterator` was called with a K!=2-Tree, it will direct the type of iterator to be `dfs_iterator` in runtime.

- How it does it:
- in the Tree class, we have used `type_traits` in this way:
```cpp
    using iterator_type = typename std::conditional<K == BINARY, pre_order_iterator, dfs_iterator>::type;
    using iterator_type2 = typename std::conditional<K == BINARY, post_order_iterator, dfs_iterator>::type;
    using iterator_type3 = typename std::conditional<K == BINARY, in_order_iterator, dfs_iterator>::type;
    using iterator_type4 = typename std::conditional<K == BINARY, min_heap_iterator, dfs_iterator>::type;
```

So for example when we call `in_order_iterator` function in tree.hpp :




has the Following Iterators:
- `in_order_iterator`
- `pre_order_iterator`
- `post_order_iterator`
- `dfs_iterator`
- `bfs_iterator` 

- For binary trees all the iterators work as expected, but for K-ary trees we will be directed to the dfs_iterator by all the different iterators in runtime.

