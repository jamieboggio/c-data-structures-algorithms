# BUILDING

1. Ensure `CMake, clang, and cmocka` are installed.
1. Download the codebase into a directory of your choosing. (e.g., `~/Projects/dsa-c`)
1. In the root directory, run `cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_C_COMPILER=clang`.
1. Then run `cd build && make && cd ..`.
1. Then executables will be in the `${PROJECT_ROOT}/build` directory.

--- 

1. Dynamic Array (vec_t)
    - [x] init_empty_vec(): Create an empty vector
    - [x] init_vec(): Initialize with a requested capacity
    - [x] free_vec(): Release allocated storage
    - [x] push_back_vec(): Append an element
    - [x] pop_back_vec(): Remove the last element
    - [ ] insert_vec(): Insert at an index, shifting elements right
    - [ ] erase_vec(): Remove at an index, shifting elements left
    - [ ] get_vec(): Read an element by index
    - [ ] set_vec(): Replace an existing element
    - [ ] reserve_vec(): Ensure minimum capacity
    - [ ] resize_vec(): Change size, zero-initializing new elements

1. Singly Linked List (slist_t)
    - [ ] init_slist(): Create an empty list
    - [ ] free_slist(): Free all nodes
    - [ ] push_front_slist(): Prepend a node
    - [ ] push_back_slist(): Append a node
    - [ ] pop_front_slist(): Remove the first node
    - [ ] pop_back_slist(): Remove the last node
    - [ ] insert_slist(): Insert at a given index
    - [ ] erase_slist(): Remove at a given index
    - [ ] find_slist(): Find the first matching element
    - [ ] reverse_slist(): Reverse links in place

1. Doubly Linked List (dlist_t)
    - [ ] init_dlist(): Create an empty list
    - [ ] free_dlist(): Free all nodes
    - [ ] push_front_dlist(): Prepend a node
    - [ ] push_back_dlist(): Append a node
    - [ ] pop_front_dlist(): Remove the first node
    - [ ] pop_back_dlist(): Remove the last node
    - [ ] find_dlist(): Return a matching node handle
    - [ ] insert_before_dlist(): Insert before a specified node
    - [ ] insert_after_dlist(): Insert after a specified node
    - [ ] erase_node_dlist(): Remove a specified node

1. Circular Buffer / Deque (deque_t)
    - [ ] init_deque(): Create with an initial capacity
    - [ ] free_deque(): Release storage
    - [ ] push_front_deque(): Insert at the front
    - [ ] push_back_deque(): Insert at the back
    - [ ] pop_front_deque(): Remove from the front
    - [ ] pop_back_deque(): Remove from the back
    - [ ] peek_front_deque(): Read the first element
    - [ ] peek_back_deque(): Read the last element
    - [ ] reserve_deque(): Increase storage capacity
    - [ ] clear_deque(): Remove all logical elements

1. Binary Min-Heap (heap_t)
    - [ ] init_heap(): Create an empty heap
    - [ ] free_heap(): Release storage
    - [ ] push_heap(): Insert while preserving heap order
    - [ ] pop_min_heap(): Remove the minimum element
    - [ ] peek_min_heap(): Read the minimum element
    - [ ] build_heap(): Build a heap from an existing array

1. Hash Table (hmap_t)
    - [ ] init_hmap(): Initialize the table
    - [ ] free_hmap(): Release table storage
    - [ ] put_hmap(): Insert or overwrite a key/value pair
    - [ ] get_hmap(): Find the value for a key
    - [ ] contains_hmap(): Check whether a key exists
    - [ ] remove_hmap(): Delete a key/value pair
    - [ ] reserve_hmap(): Grow and rehash the table
    - [ ] clear_hmap(): Remove all entries

1. Binary Search Tree (bst_t)
    - [ ] init_bst(): Create an empty tree
    - [ ] free_bst(): Free all nodes
    - [ ] insert_bst(): Insert a unique value
    - [ ] contains_bst(): Search for a value
    - [ ] remove_bst(): Delete a node while preserving order
    - [ ] min_bst(): Find the smallest value
    - [ ] max_bst(): Find the largest value
    - [ ] traverse_inorder_bst(): Visit elements in sorted order

1. AVL Tree (avl_t)
    - [ ] init_avl(): Create an empty tree
    - [ ] free_avl(): Free all nodes
    - [ ] insert_avl(): Insert and rebalance
    - [ ] contains_avl(): Search for a value
    - [ ] remove_avl(): Delete and rebalance
    - [ ] min_avl(): Find the smallest value
    - [ ] max_avl(): Find the largest value
    - [ ] traverse_inorder_avl(): Visit elements in sorted order

1. Trie (trie_t)
    - [ ] init_trie(): Create an empty trie
    - [ ] free_trie(): Release all nodes
    - [ ] insert_trie(): Insert a word
    - [ ] contains_trie(): Check for an exact word
    - [ ] starts_with_trie(): Check whether a prefix exists
    - [ ] remove_trie(): Remove a word and prune unused nodes
    - [ ] count_prefix_trie(): Count words with a given prefix

1. Disjoint-Set Union (dsu_t)
    - [ ] init_dsu(): Create n singleton sets
    - [ ] free_dsu(): Release arrays
    - [ ] find_dsu(): Find a representative with path compression
    - [ ] union_dsu(): Merge sets by size
    - [ ] connected_dsu(): Check whether two elements share a set
    - [ ] component_size_dsu(): Count elements in a set
    - [ ] component_count_dsu(): Count distinct sets
