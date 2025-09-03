/**
 * Pattern: Tree BFS - Level Order Traversal
 * 
 * Description:
 * This pattern involves traversing a tree level by level from top to bottom, using a queue
 * to keep track of the nodes at each level. It's a Breadth-First Search (BFS) approach
 * where we visit all nodes at the current level before moving to the next level.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(w) where w is the maximum width of the tree (worst case O(n/2) ≈ O(n) for a complete tree)
 * 
 * When to use:
 * - Finding the minimum depth of a tree
 * - Level-specific operations (like finding the average of each level)
 * - Zigzag traversal or spiral traversal
 * - Finding the rightmost node at each level
 * - Problems requiring level-by-level processing
 * 
 * LeetCode Problems:
 * - 102. Binary Tree Level Order Traversal
 * - 103. Binary Tree Zigzag Level Order Traversal
 * - 199. Binary Tree Right Side View
 * - 515. Find Largest Value in Each Tree Row
 * - 116. Populating Next Right Pointers in Each Node
 */

#include <iostream>
#include <vector>
#include <queue>
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

// Example 1: Standard Level Order Traversal
// LeetCode 102: https://leetcode.com/problems/binary-tree-level-order-traversal/
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at current level
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Add the current node's value to current level
            currentLevel.push_back(node->val);
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}

// Example 2: Zigzag Level Order Traversal
// LeetCode 103: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel(levelSize);
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Position to fill current node's value based on direction
            int index = leftToRight ? i : levelSize - 1 - i;
            currentLevel[index] = node->val;
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
        leftToRight = !leftToRight; // Flip direction for next level
    }
    
    return result;
}

// Example 3: Binary Tree Right Side View
// LeetCode 199: https://leetcode.com/problems/binary-tree-right-side-view/
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // If this is the last node at this level, add it to the result
            if (i == levelSize - 1) {
                result.push_back(node->val);
            }
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return result;
}

// Example 4: Find Largest Value in Each Tree Row
// LeetCode 515: https://leetcode.com/problems/find-largest-value-in-each-tree-row/
vector<int> largestValues(TreeNode* root) {
    vector<int> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        int maxVal = INT_MIN;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Update max value for current level
            maxVal = max(maxVal, node->val);
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(maxVal);
    }
    
    return result;
}

// Example 5: Average of Levels in Binary Tree
// LeetCode 637: https://leetcode.com/problems/average-of-levels-in-binary-tree/
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        double levelSum = 0;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Add current node's value to level sum
            levelSum += node->val;
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        // Calculate average for current level
        result.push_back(levelSum / levelSize);
    }
    
    return result;
}

// Example 6: Populating Next Right Pointers in Each Node
// LeetCode 116: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
// Definition for a Node with next pointer
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

Node* connect(Node* root) {
    if (!root) return nullptr;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        Node* prev = nullptr;
        
        for (int i = 0; i < levelSize; i++) {
            Node* node = q.front();
            q.pop();
            
            // Connect current node to previous node at same level
            if (prev) {
                prev->next = node;
            }
            prev = node;
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        // Last node at each level points to nullptr (already set by default)
    }
    
    return root;
}

// Example 7: Binary Tree Level Order Traversal II (Bottom-Up Level Order Traversal)
// LeetCode 107: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result;
    
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Add the current node's value to current level
            currentLevel.push_back(node->val);
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    // Reverse the result to get bottom-up order
    reverse(result.begin(), result.end());
    
    return result;
}

// Example 8: Minimum Depth of Binary Tree (using BFS)
// LeetCode 111: https://leetcode.com/problems/minimum-depth-of-binary-tree/
int minDepth(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int depth = 1;
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // If this is a leaf node, return current depth
            if (!node->left && !node->right) {
                return depth;
            }
            
            // Add child nodes to the queue for next level processing
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        depth++; // Increase depth for next level
    }
    
    return depth; // This line should not be reached if the tree has at least one leaf
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

// Main function to demonstrate the Level Order Traversal pattern
void demonstrateLevelOrderTraversal() {
    TreeNode* root = buildSampleTree();
    
    cout << "Example 1: Standard Level Order Traversal" << endl;
    vector<vector<int>> levelOrderResult = levelOrder(root);
    cout << "Level order traversal: " << endl;
    print2DVector(levelOrderResult);
    
    cout << "\nExample 2: Zigzag Level Order Traversal" << endl;
    vector<vector<int>> zigzagResult = zigzagLevelOrder(root);
    cout << "Zigzag level order traversal: " << endl;
    print2DVector(zigzagResult);
    
    cout << "\nExample 3: Binary Tree Right Side View" << endl;
    vector<int> rightViewResult = rightSideView(root);
    cout << "Right side view: ";
    printVector(rightViewResult);
    cout << endl;
    
    cout << "\nExample 4: Largest Value in Each Tree Row" << endl;
    vector<int> largestValuesResult = largestValues(root);
    cout << "Largest values in each row: ";
    printVector(largestValuesResult);
    cout << endl;
    
    cout << "\nExample 5: Average of Levels in Binary Tree" << endl;
    vector<double> averagesResult = averageOfLevels(root);
    cout << "Average of levels: ";
    printVector(averagesResult);
    cout << endl;
    
    cout << "\nExample 7: Bottom-Up Level Order Traversal" << endl;
    vector<vector<int>> bottomUpResult = levelOrderBottom(root);
    cout << "Bottom-up level order traversal: " << endl;
    print2DVector(bottomUpResult);
    
    cout << "\nExample 8: Minimum Depth of Binary Tree" << endl;
    int minDepthResult = minDepth(root);
    cout << "Minimum depth of the tree: " << minDepthResult << endl;
    
    // Clean up memory
    deleteTree(root);
}

int main() {
    // Demonstrate the Level Order Traversal pattern
    demonstrateLevelOrderTraversal();
    
    return 0;
}
