# The BST invariant

BSTs are sorted, but not necessarily balanced.

"For any node n, every node in the left subtree of n has a value less than n’s value, and every node in the right subtree of n has a value greater than n’s value."
* find: O(n)

# Balanced BST

Balanced binary search tree data structures include:
* AVL trees (1962)
* 2-3 trees (1970s)
* Red-black trees (1970s)

* find: O(log n)
  
# Ch8.3.2. Red-Black Trees

* **Local Invariant:** There are no two adjacent red nodes along any path.
* **Global Invariant:** Every path from the root to a leaf has the same number of black nodes. This number is called the black height (BH) of the tree.
* insert: O(log n)
* balance: O(1)
* remove: O(log n)

- Red Black Tree Visualization: <https://www.cs.usfca.edu/~galles/visualization/RedBlack.html>
