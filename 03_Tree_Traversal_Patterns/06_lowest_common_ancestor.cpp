/**
 * Pattern: Tree - Lowest Common Ancestor (LCA) Finding
 * 
 * Description:
 * The Lowest Common Ancestor (LCA) of two nodes in a tree is the deepest node that has both nodes
 * as descendants. This pattern is widely used for solving relationship queries between nodes in trees.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(h) where h is the height of the tree
 * 
 * When to use:
 * - Finding the common ancestor of two nodes in a tree
 * - Calculating the distance between two nodes in a tree
 * - Identifying relationships between nodes
 * - Solving path-related problems in trees
 * 
 * LeetCode Problems:
 * - 235. Lowest Common Ancestor of a Binary Search Tree
 * - 236. Lowest Common Ancestor of a Binary Tree
 * - 1123. Lowest Common Ancestor of Deepest Leaves
 * - 1644. Lowest Common Ancestor of a Binary Tree II
 * - 1650. Lowest Common Ancestor of a Binary Tree III
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

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

// Example 1: LCA in a Binary Tree
// LeetCode 236: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base case: if root is null or root is one of the nodes we're looking for
    if (!root || root == p || root == q) return root;
    
    // Look for p and q in left and right subtrees
    TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
    TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);
    
    // If both left and right are non-null, root is the LCA
    if (leftLCA && rightLCA) return root;
    
    // Otherwise, return the non-null subtree result
    return leftLCA ? leftLCA : rightLCA;
}

// Example 2: LCA in a Binary Search Tree
// LeetCode 235: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Ensure p's value is smaller than q's for simplicity
    if (p->val > q->val) {
        swap(p, q);
    }
    
    while (root) {
        // If both p and q are smaller than root, LCA must be in the left subtree
        if (q->val < root->val) {
            root = root->left;
        } 
        // If both p and q are larger than root, LCA must be in the right subtree
        else if (p->val > root->val) {
            root = root->right;
        } 
        // Root is between p and q, so root is the LCA
        else {
            break;
        }
    }
    
    return root;
}

// Example 3: LCA of Deepest Leaves
// Similar to LeetCode 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
TreeNode* lcaDeepestLeaves(TreeNode* root) {
    // Function to calculate the height of a node and find LCA of deepest leaves
    function<pair<int, TreeNode*>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int, TreeNode*> {
        if (!node) return {0, nullptr};
        
        // Calculate height and LCA for left and right subtrees
        auto [leftHeight, leftLCA] = dfs(node->left);
        auto [rightHeight, rightLCA] = dfs(node->right);
        
        // If heights are equal, this node is the LCA of deepest leaves in its subtree
        if (leftHeight == rightHeight) {
            return {leftHeight + 1, node};
        }
        
        // Return the subtree with greater height, as it contains the deepest leaves
        if (leftHeight > rightHeight) {
            return {leftHeight + 1, leftLCA};
        } else {
            return {rightHeight + 1, rightLCA};
        }
    };
    
    return dfs(root).second;
}

// Example 4: LCA with Parent Pointers
// Similar to LeetCode 1650: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/
// Node definition with parent pointer
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* parent;
    Node(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node* lowestCommonAncestorWithParent(Node* p, Node* q) {
    // Create a set to store ancestors of p
    unordered_set<Node*> ancestors;
    
    // Traverse from p to root, adding each node to the set
    while (p) {
        ancestors.insert(p);
        p = p->parent;
    }
    
    // Traverse from q to root, checking if any node is in p's ancestors
    while (q) {
        if (ancestors.count(q)) {
            return q; // This is the LCA
        }
        q = q->parent;
    }
    
    return nullptr; // Should not reach here if p and q are in the same tree
}

// Example 5: LCA when nodes may not exist in the tree
// Similar to LeetCode 1644: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/
TreeNode* lowestCommonAncestorII(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Flag to track if p and q are found
    bool pFound = false;
    bool qFound = false;
    
    // Helper function to find LCA
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        
        // Search in left and right subtrees
        TreeNode* leftResult = dfs(node->left);
        TreeNode* rightResult = dfs(node->right);
        
        // Check if current node is p or q
        if (node == p) {
            pFound = true;
            return node;
        }
        if (node == q) {
            qFound = true;
            return node;
        }
        
        // If both left and right have results, this node is the LCA
        if (leftResult && rightResult) return node;
        
        // Return the non-null result from subtrees
        return leftResult ? leftResult : rightResult;
    };
    
    TreeNode* result = dfs(root);
    
    // Return LCA only if both p and q are found
    return (pFound && qFound) ? result : nullptr;
}

// Example 6: Distance Between Two Nodes in a Binary Tree
int findDistance(TreeNode* root, TreeNode* p, TreeNode* q) {
    // First, find the LCA of p and q
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    
    // Function to find the distance from LCA to a node
    function<int(TreeNode*, TreeNode*, int)> getDistance = [&](TreeNode* node, TreeNode* target, int distance) -> int {
        if (!node) return -1;
        if (node == target) return distance;
        
        int leftDist = getDistance(node->left, target, distance + 1);
        if (leftDist != -1) return leftDist;
        
        return getDistance(node->right, target, distance + 1);
    };
    
    // Calculate distances from LCA to p and q
    int distanceToP = getDistance(lca, p, 0);
    int distanceToQ = getDistance(lca, q, 0);
    
    // Total distance is the sum of distances from LCA to p and q
    return distanceToP + distanceToQ;
}

// Example 7: LCA of Multiple Nodes
TreeNode* findLCAOfMultipleNodes(TreeNode* root, vector<TreeNode*>& nodes) {
    // Base case
    if (!root || nodes.empty()) return nullptr;
    
    // If only one node, return it as the LCA
    if (nodes.size() == 1) return nodes[0];
    
    // Function to check if a node is in the given list
    auto isInList = [&](TreeNode* node) -> bool {
        for (TreeNode* n : nodes) {
            if (n == node) return true;
        }
        return false;
    };
    
    // Helper function to find LCA
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        
        // If current node is in the list, it could be the LCA
        if (isInList(node)) return node;
        
        // Search in left and right subtrees
        TreeNode* leftResult = dfs(node->left);
        TreeNode* rightResult = dfs(node->right);
        
        // If results from both subtrees, this node is the LCA
        if (leftResult && rightResult) return node;
        
        // Return the non-null result
        return leftResult ? leftResult : rightResult;
    };
    
    return dfs(root);
}

// Utility function to build a sample binary tree for testing
TreeNode* buildSampleTree() {
    /* Builds this tree:
            3
           / \
          5   1
         / \ / \
        6  2 0  8
          / \
         7   4
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    
    return root;
}

// Utility function to build a sample binary search tree for testing
TreeNode* buildSampleBST() {
    /* Builds this BST:
            6
           / \
          2   8
         / \ / \
        0  4 7  9
          / \
         3   5
    */
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    
    return root;
}

// Free memory of the tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function to demonstrate the Lowest Common Ancestor pattern
void demonstrateLCA() {
    TreeNode* tree = buildSampleTree();
    TreeNode* bst = buildSampleBST();
    
    cout << "Example 1: LCA in a Binary Tree" << endl;
    TreeNode* p1 = tree->left; // Node with value 5
    TreeNode* q1 = tree->left->right->right; // Node with value 4
    TreeNode* lca1 = lowestCommonAncestor(tree, p1, q1);
    cout << "LCA of nodes with values 5 and 4 is: " << lca1->val << endl;
    
    cout << "\nExample 2: LCA in a Binary Search Tree" << endl;
    TreeNode* p2 = bst->left->right; // Node with value 4
    TreeNode* q2 = bst->left->right->right; // Node with value 5
    TreeNode* lca2 = lowestCommonAncestorBST(bst, p2, q2);
    cout << "LCA of nodes with values 4 and 5 in BST is: " << lca2->val << endl;
    
    cout << "\nExample 3: LCA of Deepest Leaves" << endl;
    TreeNode* lcaDeepest = lcaDeepestLeaves(tree);
    cout << "LCA of deepest leaves is: " << lcaDeepest->val << endl;
    
    cout << "\nExample 6: Distance Between Two Nodes" << endl;
    TreeNode* p3 = tree->left->left; // Node with value 6
    TreeNode* q3 = tree->left->right->right; // Node with value 4
    int distance = findDistance(tree, p3, q3);
    cout << "Distance between nodes with values 6 and 4 is: " << distance << endl;
    
    cout << "\nExample 7: LCA of Multiple Nodes" << endl;
    vector<TreeNode*> nodes = {tree->left->left, tree->left->right->left, tree->left->right->right};
    TreeNode* lcaMultiple = findLCAOfMultipleNodes(tree, nodes);
    cout << "LCA of nodes with values 6, 7, and 4 is: " << lcaMultiple->val << endl;
    
    // Clean up memory
    deleteTree(tree);
    deleteTree(bst);
}

int main() {
    // Demonstrate the Lowest Common Ancestor pattern
    demonstrateLCA();
    
    return 0;
}
