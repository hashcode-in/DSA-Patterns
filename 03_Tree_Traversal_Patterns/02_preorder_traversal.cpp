/**
 * Pattern: Tree DFS - Recursive Preorder Traversal
 * 
 * Description:
 * Preorder traversal is a depth-first traversal method that visits the root node first,
 * then recursively traverses the left subtree, and finally the right subtree.
 * The traversal order is: Root → Left → Right.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(h) where h is the height of the tree (worst case O(n) for skewed trees)
 * 
 * When to use:
 * - Creating a copy or clone of a tree
 * - Serializing/deserializing a tree
 * - Finding paths from root to leaves
 * - Checking if a tree is a subtree of another
 * - Tree structure validation (e.g., checking if two trees are identical)
 * 
 * LeetCode Problems:
 * - 100. Same Tree
 * - 101. Symmetric Tree
 * - 226. Invert Binary Tree
 * - 617. Merge Two Binary Trees
 * - 105. Construct Binary Tree from Preorder and Inorder Traversal
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Example 1: Recursive Preorder Traversal
// LeetCode 144: https://leetcode.com/problems/binary-tree-preorder-traversal/
void preorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    
    // Visit root
    result.push_back(root->val);
    
    // Traverse left subtree
    preorderHelper(root->left, result);
    
    // Traverse right subtree
    preorderHelper(root->right, result);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    preorderHelper(root, result);
    return result;
}

// Example 2: Iterative Preorder Traversal (using stack)
vector<int> preorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> s;
    s.push(root);
    
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        
        // Visit the node
        result.push_back(node->val);
        
        // Push right child first (so that left child is processed first)
        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
    
    return result;
}

// Example 3: Check if two trees are the same (using preorder traversal)
// LeetCode 100: https://leetcode.com/problems/same-tree/
bool isSameTree(TreeNode* p, TreeNode* q) {
    // If both are null, they are the same
    if (!p && !q) return true;
    
    // If one is null and the other is not, they are different
    if (!p || !q) return false;
    
    // Check if current nodes have the same value
    if (p->val != q->val) return false;
    
    // Recursively check left and right subtrees
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// Example 4: Check if a tree is symmetric (mirror of itself)
// LeetCode 101: https://leetcode.com/problems/symmetric-tree/
bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
    // If both are null, they are symmetric
    if (!left && !right) return true;
    
    // If one is null and the other is not, they are not symmetric
    if (!left || !right) return false;
    
    // Check if values are the same and subtrees are symmetric
    return (left->val == right->val) &&
           isSymmetricHelper(left->left, right->right) &&
           isSymmetricHelper(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isSymmetricHelper(root->left, root->right);
}

// Example 5: Invert a binary tree (mirror the tree)
// LeetCode 226: https://leetcode.com/problems/invert-binary-tree/
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    // Swap left and right children
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively invert left and right subtrees
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}

// Example 6: Merge two binary trees (add values where nodes overlap)
// LeetCode 617: https://leetcode.com/problems/merge-two-binary-trees/
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    // If one tree is empty, return the other
    if (!root1) return root2;
    if (!root2) return root1;
    
    // Merge the values of the current nodes
    root1->val += root2->val;
    
    // Recursively merge left and right subtrees
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    
    return root1;
}

// Example 7: Check if a tree is a subtree of another
// LeetCode 572: https://leetcode.com/problems/subtree-of-another-tree/
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    
    // Check if the trees are identical from this node
    if (isSameTree(root, subRoot)) return true;
    
    // If not, check if subRoot is a subtree of root's left or right subtree
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// Example 8: Flatten Binary Tree to Linked List (in-place)
// LeetCode 114: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
void flatten(TreeNode* root) {
    if (!root) return;
    
    // Store the original right and left subtrees
    TreeNode* rightSubtree = root->right;
    TreeNode* leftSubtree = root->left;
    
    // Clear the left subtree
    root->left = nullptr;
    
    // Flatten the left subtree
    flatten(leftSubtree);
    
    // Attach the flattened left subtree to the right
    root->right = leftSubtree;
    
    // Find the end of the new right subtree
    TreeNode* current = root;
    while (current->right) {
        current = current->right;
    }
    
    // Flatten the original right subtree and attach it
    flatten(rightSubtree);
    current->right = rightSubtree;
}

// Example 9: Construct Binary Tree from Preorder and Inorder Traversal
// LeetCode 105: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd,
                         vector<int>& inorder, int inStart, int inEnd,
                         unordered_map<int, int>& inMap) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;
    
    // The first element in preorder is the root
    TreeNode* root = new TreeNode(preorder[preStart]);
    
    // Find the position of root in inorder
    int inRoot = inMap[root->val];
    // Number of elements in left subtree
    int numsLeft = inRoot - inStart;
    
    // Recursively build left and right subtrees
    root->left = buildTreeHelper(preorder, preStart + 1, preStart + numsLeft,
                                inorder, inStart, inRoot - 1, inMap);
    root->right = buildTreeHelper(preorder, preStart + numsLeft + 1, preEnd,
                                 inorder, inRoot + 1, inEnd, inMap);
    
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    // Create a map to store value -> index for inorder traversal
    unordered_map<int, int> inMap;
    for (int i = 0; i < inorder.size(); i++) {
        inMap[inorder[i]] = i;
    }
    
    return buildTreeHelper(preorder, 0, preorder.size() - 1,
                          inorder, 0, inorder.size() - 1, inMap);
}

// Example 10: Binary Tree Paths - Find all root-to-leaf paths
// LeetCode 257: https://leetcode.com/problems/binary-tree-paths/
void binaryTreePathsHelper(TreeNode* root, string path, vector<string>& paths) {
    if (!root) return;
    
    // Add current node to path
    if (!path.empty()) path += "->";
    path += to_string(root->val);
    
    // If this is a leaf node, add the path to the result
    if (!root->left && !root->right) {
        paths.push_back(path);
        return;
    }
    
    // Recursively find paths in left and right subtrees
    binaryTreePathsHelper(root->left, path, paths);
    binaryTreePathsHelper(root->right, path, paths);
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> paths;
    binaryTreePathsHelper(root, "", paths);
    return paths;
}

// Utility function to build a sample tree for testing
TreeNode* buildSampleTree() {
    /* Builds this tree:
            1
           / \
          2   3
         / \   \
        4   5   6
           /
          7
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->right->left = new TreeNode(7);
    
    return root;
}

// Utility function to build a sample symmetric tree for testing
TreeNode* buildSymmetricTree() {
    /* Builds this tree:
            1
           / \
          2   2
         / \ / \
        3  4 4  3
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    
    return root;
}

// Utility function to print a vector
template<typename T>
void printVector(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Free memory of the tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function to demonstrate the Preorder Traversal pattern
void demonstratePreorderTraversal() {
    TreeNode* root = buildSampleTree();
    
    cout << "Example 1: Recursive Preorder Traversal" << endl;
    vector<int> preorderResult = preorderTraversal(root);
    cout << "Preorder traversal: ";
    printVector(preorderResult);
    cout << endl;
    
    cout << "\nExample 2: Iterative Preorder Traversal" << endl;
    vector<int> iterativeResult = preorderTraversalIterative(root);
    cout << "Preorder traversal (iterative): ";
    printVector(iterativeResult);
    cout << endl;
    
    TreeNode* root2 = buildSampleTree();
    cout << "\nExample 3: Check if Two Trees are the Same" << endl;
    cout << "Are the trees the same? " << (isSameTree(root, root2) ? "Yes" : "No") << endl;
    
    TreeNode* symmetricRoot = buildSymmetricTree();
    cout << "\nExample 4: Check if a Tree is Symmetric" << endl;
    cout << "Is the tree symmetric? " << (isSymmetric(symmetricRoot) ? "Yes" : "No") << endl;
    cout << "Is the regular tree symmetric? " << (isSymmetric(root) ? "Yes" : "No") << endl;
    
    cout << "\nExample 5: Invert Binary Tree" << endl;
    TreeNode* rootToInvert = buildSampleTree();
    cout << "Original preorder traversal: ";
    printVector(preorderTraversal(rootToInvert));
    cout << endl;
    
    invertTree(rootToInvert);
    cout << "Inverted preorder traversal: ";
    printVector(preorderTraversal(rootToInvert));
    cout << endl;
    
    cout << "\nExample 6: Merge Two Binary Trees" << endl;
    TreeNode* root3 = buildSampleTree();
    TreeNode* root4 = buildSampleTree();
    TreeNode* mergedRoot = mergeTrees(root3, root4);
    cout << "Merged tree preorder traversal: ";
    printVector(preorderTraversal(mergedRoot));
    cout << endl;
    
    cout << "\nExample 10: Binary Tree Paths" << endl;
    vector<string> paths = binaryTreePaths(root);
    cout << "Root-to-leaf paths: ";
    printVector(paths);
    cout << endl;
    
    // Clean up memory
    deleteTree(root);
    deleteTree(symmetricRoot);
    deleteTree(rootToInvert);
    deleteTree(mergedRoot); // This also deletes root3 and root4 since they were merged
}

int main() {
    // Demonstrate the Preorder Traversal pattern
    demonstratePreorderTraversal();
    
    return 0;
}
