# Tree Traversal Patterns (DFS & BFS)

Tree traversal patterns involve systematic ways to visit all nodes in a tree data structure. These patterns are fundamental for solving problems that involve hierarchical data. The two main approaches are Depth-First Search (DFS) and Breadth-First Search (BFS).

## Patterns in this Category

### Pattern 12: Tree BFS - Level Order Traversal
- **Description**: Visit all nodes level by level, from left to right, using a queue data structure.
- **When to use**: Finding level-specific information, computing level averages, or when the shortest path in a tree is required.
- **Files**: [01_level_order_traversal.cpp](./01_level_order_traversal.cpp)
- **LeetCode Problems**: Binary Tree Level Order Traversal, Binary Tree Right Side View, Find Largest Value in Each Tree Row

### Pattern 13: Tree DFS - Recursive Preorder Traversal
- **Description**: Visit the root, then left subtree, then right subtree recursively (Root → Left → Right).
- **When to use**: When you need to explore paths from root to leaf, or when creating a copy of the tree.
- **Files**: [02_preorder_traversal.cpp](./02_preorder_traversal.cpp)
- **LeetCode Problems**: Same Tree, Symmetric Tree, Flatten Binary Tree to Linked List

### Pattern 14: Tree DFS - Recursive Inorder Traversal
- **Description**: Visit the left subtree, then root, then right subtree recursively (Left → Root → Right).
- **When to use**: For Binary Search Trees to get elements in sorted order or to validate a BST.
- **Files**: [03_inorder_traversal.cpp](./03_inorder_traversal.cpp)
- **LeetCode Problems**: Binary Tree Inorder Traversal, Validate Binary Search Tree, Kth Smallest Element in a BST

### Pattern 15: Tree DFS - Recursive Postorder Traversal
- **Description**: Visit the left subtree, then right subtree, then root recursively (Left → Right → Root).
- **When to use**: When you need to delete a tree, calculate the height of a tree, or solve problems that need child results first.
- **Files**: [04_postorder_traversal.cpp](./04_postorder_traversal.cpp)
- **LeetCode Problems**: Maximum Depth of Binary Tree, Binary Tree Maximum Path Sum, Diameter of Binary Tree

### Pattern 16: Tree DFS - Path Sum Variations
- **Description**: Use DFS to find paths in a tree that satisfy specific criteria, often involving sums of node values.
- **When to use**: For problems about path sums, path collections, or checking if certain paths exist.
- **Files**: [05_path_sum_variations.cpp](./05_path_sum_variations.cpp)
- **LeetCode Problems**: Path Sum, Path Sum II, Path Sum III, Binary Tree Paths

### Pattern 17: Tree - Lowest Common Ancestor (LCA) Finding
- **Description**: Find the lowest common ancestor of two nodes in a tree - the deepest node that has both nodes as descendants.
- **When to use**: For relationship queries between nodes, like finding the common parent or calculating the distance between nodes.
- **Files**: [06_lowest_common_ancestor.cpp](./06_lowest_common_ancestor.cpp)
- **LeetCode Problems**: Lowest Common Ancestor of a Binary Tree, Lowest Common Ancestor of a Binary Search Tree

### Pattern 18: Tree - Serialization and Deserialization
- **Description**: Convert a tree to a string (serialization) and reconstruct the tree from that string (deserialization).
- **When to use**: When you need to store or transmit a tree, compare tree structures, or clone trees.
- **Files**: [07_serialization_deserialization.cpp](./07_serialization_deserialization.cpp)
- **LeetCode Problems**: Serialize and Deserialize Binary Tree, Subtree of Another Tree, Find Duplicate Subtrees

## Tree Traversal Strategies

### Iterative vs Recursive Traversal
Most tree traversals can be implemented either recursively or iteratively:
- **Recursive**: Simpler to implement but may cause stack overflow for very deep trees.
- **Iterative**: Uses an explicit stack or queue, more efficient for deep trees but more complex code.

### Time and Space Complexity
- **Time Complexity**: O(n) for all traversals, where n is the number of nodes.
- **Space Complexity**: 
  - O(h) for recursive DFS, where h is the height of the tree (worst case O(n) for skewed trees).
  - O(w) for BFS, where w is the maximum width of the tree (worst case O(n/2) ≈ O(n) for complete trees).

## Common Tree Data Structure

```cpp
// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
