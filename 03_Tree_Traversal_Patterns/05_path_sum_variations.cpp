/**
 * Pattern: Tree DFS - Path Sum Variations
 * 
 * Description:
 * This pattern focuses on various problems related to paths in a binary tree where we 
 * need to find or verify paths with specific sum requirements. A path can be defined 
 * as a sequence of nodes along edges of the tree. These problems typically use DFS to 
 * traverse the tree while tracking sums along the way.
 * 
 * Time Complexity: O(n) to O(n²) depending on the specific variation
 * Space Complexity: O(h) where h is the height of the tree
 * 
 * When to use:
 * - Finding if a root-to-leaf path with a specific sum exists
 * - Collecting all root-to-leaf paths with a specific sum
 * - Counting paths (not necessarily starting at the root) with a given sum
 * - Finding the maximum/minimum path sum
 * - Collecting all paths in a tree (root-to-leaf, any-to-any, etc.)
 * 
 * LeetCode Problems:
 * - 112. Path Sum
 * - 113. Path Sum II
 * - 437. Path Sum III
 * - 257. Binary Tree Paths
 * - 129. Sum Root to Leaf Numbers
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
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

// Example 1: Path Sum - Check if root-to-leaf path with given sum exists
// LeetCode 112: https://leetcode.com/problems/path-sum/
bool hasPathSum(TreeNode* root, int targetSum) {
    // Base case: empty tree
    if (!root) return false;
    
    // Subtract the current node's value from targetSum
    targetSum -= root->val;
    
    // If this is a leaf node, check if targetSum is 0
    if (!root->left && !root->right) {
        return targetSum == 0;
    }
    
    // Recursively check left and right subtrees
    return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}

// Example 2: Path Sum II - Find all root-to-leaf paths with given sum
// LeetCode 113: https://leetcode.com/problems/path-sum-ii/
void pathSumHelper(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& paths) {
    if (!root) return;
    
    // Add current node to path
    path.push_back(root->val);
    
    // Subtract current node's value from targetSum
    targetSum -= root->val;
    
    // If this is a leaf node and targetSum is 0, we found a valid path
    if (!root->left && !root->right && targetSum == 0) {
        paths.push_back(path);
    }
    
    // Recursively check left and right subtrees
    pathSumHelper(root->left, targetSum, path, paths);
    pathSumHelper(root->right, targetSum, path, paths);
    
    // Backtrack: remove current node from path
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> paths;
    vector<int> path;
    pathSumHelper(root, targetSum, path, paths);
    return paths;
}

// Example 3: Path Sum III - Count paths with given sum (not necessarily starting at root)
// LeetCode 437: https://leetcode.com/problems/path-sum-iii/
int pathSumIII(TreeNode* root, int targetSum) {
    // Use a prefix sum map to store the count of each cumulative sum
    unordered_map<long, int> prefixSum; // {sum, count}
    prefixSum[0] = 1; // Empty path has sum 0
    
    // Helper function to count paths with targetSum
    function<int(TreeNode*, long)> dfs = [&](TreeNode* node, long currentSum) {
        if (!node) return 0;
        
        // Add current node value to the running sum
        currentSum += node->val;
        
        // Count the number of paths that end at current node with targetSum
        // This is equivalent to counting previous paths with sum = currentSum - targetSum
        int count = prefixSum[currentSum - targetSum];
        
        // Update the prefix sum map
        prefixSum[currentSum]++;
        
        // Recursively count paths in left and right subtrees
        count += dfs(node->left, currentSum);
        count += dfs(node->right, currentSum);
        
        // Backtrack: remove current sum from the map to not affect other paths
        prefixSum[currentSum]--;
        
        return count;
    };
    
    return dfs(root, 0);
}

// Example 4: Binary Tree Paths - Find all root-to-leaf paths
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

// Example 5: Sum Root to Leaf Numbers
// LeetCode 129: https://leetcode.com/problems/sum-root-to-leaf-numbers/
int sumNumbers(TreeNode* root) {
    // Helper function to calculate the sum of all paths
    function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int currentSum) {
        if (!node) return 0;
        
        // Update current sum: multiply by 10 and add current node's value
        currentSum = currentSum * 10 + node->val;
        
        // If this is a leaf node, return the current sum
        if (!node->left && !node->right) {
            return currentSum;
        }
        
        // Recursively calculate the sum from left and right subtrees
        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    };
    
    return dfs(root, 0);
}

// Example 6: Maximum Path Sum from Root to Leaf
int maxPathSumRootToLeaf(TreeNode* root) {
    if (!root) return 0;
    
    // Helper function to find maximum path sum
    function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int currentSum) {
        if (!node) return INT_MIN; // Return a very small value for non-existent paths
        
        // Update current sum
        currentSum += node->val;
        
        // If this is a leaf node, return the current sum
        if (!node->left && !node->right) {
            return currentSum;
        }
        
        // Return the maximum sum path through left or right subtree
        return max(dfs(node->left, currentSum), dfs(node->right, currentSum));
    };
    
    return dfs(root, 0);
}

// Example 7: Sum of all paths where each path is represented as a number
int sumOfAllPathNumbers(TreeNode* root) {
    // Helper function to calculate the sum of all path numbers
    function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int currentNumber) {
        if (!node) return 0;
        
        // Form the current number
        currentNumber = currentNumber * 10 + node->val;
        
        // If this is a leaf node, return the current number
        if (!node->left && !node->right) {
            return currentNumber;
        }
        
        // Return the sum of path numbers from left and right subtrees
        return dfs(node->left, currentNumber) + dfs(node->right, currentNumber);
    };
    
    return dfs(root, 0);
}

// Example 8: Path with Required Product
// Find a root-to-leaf path with product equal to target
bool hasPathProduct(TreeNode* root, int targetProduct) {
    if (!root) return false;
    
    // Helper function to check if a path with the target product exists
    function<bool(TreeNode*, long)> dfs = [&](TreeNode* node, long currentProduct) {
        if (!node) return false;
        
        // Update current product
        currentProduct *= node->val;
        
        // If product becomes 0 and targetProduct is 0, return true
        if (currentProduct == 0 && targetProduct == 0) return true;
        
        // If product is 0 but targetProduct is not, this path won't work
        if (currentProduct == 0) return false;
        
        // If this is a leaf node, check if currentProduct equals targetProduct
        if (!node->left && !node->right) {
            return currentProduct == targetProduct;
        }
        
        // Check left and right subtrees
        return dfs(node->left, currentProduct) || dfs(node->right, currentProduct);
    };
    
    return dfs(root, 1); // Start with product 1 (multiplicative identity)
}

// Utility function to build a sample tree for testing
TreeNode* buildSampleTree() {
    /* Builds this tree:
            5
           / \
          4   8
         /   / \
        11  13  4
       /  \    / \
      7    2  5   1
    */
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);
    
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

// Main function to demonstrate the Path Sum Variations pattern
void demonstratePathSumVariations() {
    TreeNode* root = buildSampleTree();
    
    cout << "Example 1: Path Sum - Check if root-to-leaf path with given sum exists" << endl;
    int targetSum1 = 22;
    cout << "Has path with sum " << targetSum1 << "? " << (hasPathSum(root, targetSum1) ? "Yes" : "No") << endl;
    
    cout << "\nExample 2: Path Sum II - Find all root-to-leaf paths with given sum" << endl;
    int targetSum2 = 22;
    vector<vector<int>> paths = pathSum(root, targetSum2);
    cout << "Paths with sum " << targetSum2 << ": " << endl;
    print2DVector(paths);
    
    cout << "\nExample 3: Path Sum III - Count paths with given sum (not necessarily starting at root)" << endl;
    int targetSum3 = 22;
    cout << "Number of paths with sum " << targetSum3 << ": " << pathSumIII(root, targetSum3) << endl;
    
    cout << "\nExample 4: Binary Tree Paths - Find all root-to-leaf paths" << endl;
    vector<string> allPaths = binaryTreePaths(root);
    cout << "All root-to-leaf paths: ";
    printVector(allPaths);
    cout << endl;
    
    cout << "\nExample 5: Sum Root to Leaf Numbers" << endl;
    cout << "Sum of all root-to-leaf numbers: " << sumNumbers(root) << endl;
    
    cout << "\nExample 6: Maximum Path Sum from Root to Leaf" << endl;
    cout << "Maximum path sum from root to leaf: " << maxPathSumRootToLeaf(root) << endl;
    
    cout << "\nExample 7: Sum of all paths where each path is represented as a number" << endl;
    cout << "Sum of all path numbers: " << sumOfAllPathNumbers(root) << endl;
    
    // Clean up memory
    deleteTree(root);
}

int main() {
    // Demonstrate the Path Sum Variations pattern
    demonstratePathSumVariations();
    
    return 0;
}
