/**
 * Pattern: Tree DFS - Recursive Postorder Traversal
 * 
 * Description:
 * Postorder traversal is a depth-first traversal method that visits the left subtree first,
 * then the right subtree, and finally the root node. The traversal order is: Left → Right → Root.
 * This pattern is useful for operations that need to process children before their parents.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(h) where h is the height of the tree (worst case O(n) for skewed trees)
 * 
 * When to use:
 * - Deleting a tree (need to delete children before parent)
 * - Computing height or depth of a tree
 * - Calculating the diameter of a tree
 * - Finding the lowest common ancestor
 * - Evaluating expressions represented by a syntax tree
 * 
 * LeetCode Problems:
 * - 145. Binary Tree Postorder Traversal
 * - 104. Maximum Depth of Binary Tree
 * - 124. Binary Tree Maximum Path Sum
 * - 543. Diameter of Binary Tree
 * - 236. Lowest Common Ancestor of a Binary Tree
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

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

// Example 1: Recursive Postorder Traversal
// LeetCode 145: https://leetcode.com/problems/binary-tree-postorder-traversal/
void postorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    
    // Traverse left subtree
    postorderHelper(root->left, result);
    
    // Traverse right subtree
    postorderHelper(root->right, result);
    
    // Visit root
    result.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    postorderHelper(root, result);
    return result;
}

// Example 2: Iterative Postorder Traversal (using two stacks)
vector<int> postorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> s1, s2;
    s1.push(root);
    
    // First stack to get nodes in root->right->left order
    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);
        
        // Push left then right to get right then left in s2
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    
    // Second stack has nodes in left->right->root order
    while (!s2.empty()) {
        result.push_back(s2.top()->val);
        s2.pop();
    }
    
    return result;
}

// Example 3: Calculate Height/Depth of Binary Tree
// LeetCode 104: https://leetcode.com/problems/maximum-depth-of-binary-tree/
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    
    // Calculate height of left and right subtrees
    int leftHeight = maxDepth(root->left);
    int rightHeight = maxDepth(root->right);
    
    // Return the maximum height plus 1 for the current node
    return max(leftHeight, rightHeight) + 1;
}

// Example 4: Calculate Diameter of Binary Tree
// LeetCode 543: https://leetcode.com/problems/diameter-of-binary-tree/
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    
    // Helper function to calculate height while updating diameter
    function<int(TreeNode*)> height = [&](TreeNode* node) {
        if (!node) return 0;
        
        // Calculate height of left and right subtrees
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        // Update diameter if path through this node is longer
        diameter = max(diameter, leftHeight + rightHeight);
        
        // Return height of this subtree
        return max(leftHeight, rightHeight) + 1;
    };
    
    height(root);
    return diameter;
}

// Example 5: Binary Tree Maximum Path Sum
// LeetCode 124: https://leetcode.com/problems/binary-tree-maximum-path-sum/
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    
    // Helper function to calculate max path sum
    function<int(TreeNode*)> maxPathSumHelper = [&](TreeNode* node) {
        if (!node) return 0;
        
        // Calculate max path sum from left and right subtrees
        // Negative sums are not considered (max with 0)
        int leftSum = max(0, maxPathSumHelper(node->left));
        int rightSum = max(0, maxPathSumHelper(node->right));
        
        // Update maxSum if path through this node is larger
        maxSum = max(maxSum, leftSum + rightSum + node->val);
        
        // Return the max sum of a path starting from this node
        return max(leftSum, rightSum) + node->val;
    };
    
    maxPathSumHelper(root);
    return maxSum;
}

// Example 6: Lowest Common Ancestor of a Binary Tree
// LeetCode 236: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    
    // Look for p and q in left and right subtrees
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    // If both p and q are found in different subtrees, root is LCA
    if (left && right) return root;
    
    // Otherwise, return the non-null result
    return left ? left : right;
}

// Example 7: Check if a Binary Tree is Balanced
// LeetCode 110: https://leetcode.com/problems/balanced-binary-tree/
bool isBalanced(TreeNode* root) {
    // Helper function that returns height if balanced, -1 if unbalanced
    function<int(TreeNode*)> checkBalance = [&](TreeNode* node) {
        if (!node) return 0;
        
        // Check left subtree
        int leftHeight = checkBalance(node->left);
        if (leftHeight == -1) return -1;
        
        // Check right subtree
        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1) return -1;
        
        // Check if current node is balanced
        if (abs(leftHeight - rightHeight) > 1) return -1;
        
        // Return height of current subtree
        return max(leftHeight, rightHeight) + 1;
    };
    
    return checkBalance(root) != -1;
}

// Example 8: Find Leaves of Binary Tree
// Similar to LeetCode 366: Find Leaves of Binary Tree
vector<vector<int>> findLeaves(TreeNode* root) {
    vector<vector<int>> result;
    
    // Helper function to compute the height and collect nodes
    function<int(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return -1;
        
        // Compute height from bottom (leaves are height 0)
        int height = max(dfs(node->left), dfs(node->right)) + 1;
        
        // Ensure result has enough levels
        if (result.size() <= height) {
            result.resize(height + 1);
        }
        
        // Add current node to its level
        result[height].push_back(node->val);
        
        return height;
    };
    
    dfs(root);
    return result;
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

// Utility function to print a 2D vector
template<typename T>
void print2DVector(const vector<vector<T>>& vec) {
    cout << "[" << endl;
    for (const auto& row : vec) {
        cout << "  ";
        printVector(row);
        cout << endl;
    }
    cout << "]" << endl;
}

// Free memory of the tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function to demonstrate the Postorder Traversal pattern
void demonstratePostorderTraversal() {
    TreeNode* root = buildSampleTree();
    
    cout << "Example 1: Recursive Postorder Traversal" << endl;
    vector<int> postorderResult = postorderTraversal(root);
    cout << "Postorder traversal: ";
    printVector(postorderResult);
    cout << endl;
    
    cout << "\nExample 2: Iterative Postorder Traversal" << endl;
    vector<int> iterativeResult = postorderTraversalIterative(root);
    cout << "Postorder traversal (iterative): ";
    printVector(iterativeResult);
    cout << endl;
    
    cout << "\nExample 3: Calculate Height/Depth of Binary Tree" << endl;
    cout << "Maximum depth of the tree: " << maxDepth(root) << endl;
    
    cout << "\nExample 4: Calculate Diameter of Binary Tree" << endl;
    cout << "Diameter of the tree: " << diameterOfBinaryTree(root) << endl;
    
    cout << "\nExample 5: Binary Tree Maximum Path Sum" << endl;
    cout << "Maximum path sum: " << maxPathSum(root) << endl;
    
    cout << "\nExample 7: Check if a Binary Tree is Balanced" << endl;
    cout << "Is the tree balanced? " << (isBalanced(root) ? "Yes" : "No") << endl;
    
    cout << "\nExample 8: Find Leaves of Binary Tree" << endl;
    vector<vector<int>> leaves = findLeaves(root);
    cout << "Leaves by level: " << endl;
    print2DVector(leaves);
    
    // Clean up memory
    deleteTree(root);
}

int main() {
    // Demonstrate the Postorder Traversal pattern
    demonstratePostorderTraversal();
    
    return 0;
}
