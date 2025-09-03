/**
 * Pattern: DP - Catalan Numbers
 * 
 * Description:
 * Catalan numbers form a sequence of positive integers that appear in various counting problems,
 * often involving recursively defined objects. The nth Catalan number, C(n), counts various
 * structures including valid parentheses expressions, binary trees, polygon triangulations, etc.
 * 
 * Formula: C(n) = (1/(n+1)) * (2n choose n) = C(0)*C(n-1) + C(1)*C(n-2) + ... + C(n-1)*C(0)
 * 
 * Time Complexity: O(n²) for computing C(n) using DP
 * Space Complexity: O(n) for storing the Catalan numbers
 * 
 * When to use:
 * - Counting problems with recursive structure
 * - Problems involving binary trees or binary search trees
 * - Problems involving valid parentheses expressions
 * - Problems involving polygon triangulation
 * - Dyck paths or mountain ranges
 * 
 * LeetCode Problems:
 * - 96. Unique Binary Search Trees
 * - 95. Unique Binary Search Trees II
 * - 22. Generate Parentheses
 * - 241. Different Ways to Add Parentheses
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Example 1: Basic Catalan Number calculation
class CatalanNumbers {
public:
    // Calculate nth Catalan number using dynamic programming
    unsigned long long catalanDP(int n) {
        // Array to store Catalan numbers
        vector<unsigned long long> catalan(n + 1, 0);
        
        // Base case
        catalan[0] = 1;
        
        // Fill the array using the recurrence relation
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                catalan[i] += catalan[j] * catalan[i - j - 1];
            }
        }
        
        return catalan[n];
    }
    
    // Calculate nth Catalan number using binomial coefficient
    unsigned long long catalanBinomial(int n) {
        // C(n) = (2n)! / ((n+1)! * n!)
        
        // Calculate (2n choose n)
        unsigned long long c = binomialCoeff(2 * n, n);
        
        // Return C(n) = (2n choose n) / (n+1)
        return c / (n + 1);
    }
    
    // Helper function to calculate binomial coefficient C(n, k)
    unsigned long long binomialCoeff(int n, int k) {
        unsigned long long res = 1;
        
        // C(n, k) = C(n, n-k), take the smaller one
        if (k > n - k) {
            k = n - k;
        }
        
        // Calculate C(n, k) = n! / (k! * (n-k)!)
        for (int i = 0; i < k; i++) {
            res *= (n - i);
            res /= (i + 1);
        }
        
        return res;
    }
    
    // Generate the first n Catalan numbers
    vector<unsigned long long> generateCatalanNumbers(int n) {
        vector<unsigned long long> catalan(n);
        
        for (int i = 0; i < n; i++) {
            catalan[i] = catalanDP(i);
        }
        
        return catalan;
    }
};

// Definition for a binary tree node (forward declaration)
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Example 2: Unique Binary Search Trees
// LeetCode 96: https://leetcode.com/problems/unique-binary-search-trees/
class UniqueBinarySearchTrees {
public:
    // Count the number of unique BSTs with n nodes (values 1 to n)
    int numTrees(int n) {
        // The number of unique BSTs with n nodes is the nth Catalan number
        vector<int> dp(n + 1, 0);
        
        // Base case: empty tree (no nodes) has one structure
        dp[0] = 1;
        
        // Fill the dp array
        for (int i = 1; i <= n; i++) {
            // Calculate the number of unique BSTs with i nodes
            for (int j = 0; j < i; j++) {
                // Number of unique BSTs with root j+1 (nodes 1 to j in left subtree, nodes j+2 to i in right subtree)
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        
        return dp[n];
    }
    
    // Generate all unique BST structures with values 1 to n
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return vector<TreeNode*>();
        return generateTreesHelper(1, n);
    }
    
private:
    
    // Helper function to generate all unique BST structures with values from start to end
    vector<TreeNode*> generateTreesHelper(int start, int end) {
        vector<TreeNode*> result;
        
        // Base case: empty subtree
        if (start > end) {
            result.push_back(nullptr);
            return result;
        }
        
        // Consider each value as the root
        for (int i = start; i <= end; i++) {
            // Generate all possible left subtrees
            vector<TreeNode*> leftSubtrees = generateTreesHelper(start, i - 1);
            
            // Generate all possible right subtrees
            vector<TreeNode*> rightSubtrees = generateTreesHelper(i + 1, end);
            
            // Connect left and right subtrees to the root
            for (TreeNode* left : leftSubtrees) {
                for (TreeNode* right : rightSubtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        
        return result;
    }
};

// Example 3: Generate Parentheses
// LeetCode 22: https://leetcode.com/problems/generate-parentheses/
class GenerateParentheses {
public:
    // Generate all valid combinations of n pairs of parentheses
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
    
    // Using Catalan numbers to count
    int countParenthesis(int n) {
        // The number of valid parentheses expressions with n pairs is the nth Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n);
    }
    
private:
    // Helper function for backtracking
    void backtrack(vector<string>& result, string current, int open, int close, int max) {
        // Base case: if we've used all parentheses
        if (current.length() == max * 2) {
            result.push_back(current);
            return;
        }
        
        // Add an opening parenthesis if we haven't used all of them
        if (open < max) {
            backtrack(result, current + "(", open + 1, close, max);
        }
        
        // Add a closing parenthesis if it makes a valid expression
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, max);
        }
    }
};

// Example 4: Different Ways to Add Parentheses
// LeetCode 241: https://leetcode.com/problems/different-ways-to-add-parentheses/
class DifferentWaysToAddParentheses {
public:
    vector<int> diffWaysToCompute(string expression) {
        // Use memoization to avoid redundant computation
        unordered_map<string, vector<int>> memo;
        return dfs(expression, memo);
    }
    
private:
    vector<int> dfs(string input, unordered_map<string, vector<int>>& memo) {
        // Check if we've already computed the result for this input
        if (memo.count(input)) {
            return memo[input];
        }
        
        vector<int> result;
        
        // Check if the input is a single number
        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        
        // Base case: single number
        if (isNumber) {
            result.push_back(stoi(input));
            return result;
        }
        
        // Split the expression at each operator
        for (int i = 0; i < input.length(); i++) {
            char c = input[i];
            
            // If we find an operator, split and compute recursively
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = dfs(input.substr(0, i), memo);
                vector<int> right = dfs(input.substr(i + 1), memo);
                
                // Combine the results based on the operator
                for (int l : left) {
                    for (int r : right) {
                        if (c == '+') {
                            result.push_back(l + r);
                        } else if (c == '-') {
                            result.push_back(l - r);
                        } else if (c == '*') {
                            result.push_back(l * r);
                        }
                    }
                }
            }
        }
        
        // Cache the result
        memo[input] = result;
        return result;
    }
    
    // Count the number of ways to parenthesize an expression with n operands
    // This is related to the (n-1)th Catalan number
    int countWaysToCatalanDP(int n) {
        // n operands means n-1 operators, which gives n-1 places to split
        // The number of ways is the (n-1)th Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n - 1);
    }
};

// Example 5: Count Valid Parentheses Expressions
class CountValidParentheses {
public:
    // Count valid parentheses expressions of length 2n
    int countValidParentheses(int n) {
        // The count is the nth Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n);
    }
    
    // Validate if a string has valid parentheses
    bool isValid(string s) {
        int count = 0;
        
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                
                // More closing than opening parentheses at any point makes it invalid
                if (count < 0) {
                    return false;
                }
            }
        }
        
        // At the end, count should be 0 for valid parentheses
        return count == 0;
    }
};

// Example 6: Count Binary Trees
class CountBinaryTrees {
public:
    // Count the number of structurally unique binary trees with n nodes
    int countTrees(int n) {
        // The count is the nth Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n);
    }
    
    // Count the number of full binary trees with n internal nodes
    // (internal nodes have 0 or 2 children, and external nodes have 0 children)
    int countFullBinaryTrees(int n) {
        // The number of full binary trees with n internal nodes is the nth Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n);
    }
};

// Example 7: Dyck Paths (Paths that never go below the x-axis)
class DyckPaths {
public:
    // Count Dyck paths from (0,0) to (2n,0) that never go below the x-axis
    int countDyckPaths(int n) {
        // The count is the nth Catalan number
        CatalanNumbers catalanCalculator;
        return catalanCalculator.catalanDP(n);
    }
    
    // Generate all Dyck paths of length 2n
    vector<string> generateDyckPaths(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
    
private:
    // Helper function for backtracking (same as generating parentheses)
    void backtrack(vector<string>& result, string current, int up, int down, int max) {
        if (current.length() == max * 2) {
            result.push_back(current);
            return;
        }
        
        if (up < max) {
            backtrack(result, current + "U", up + 1, down, max);
        }
        
        if (down < up) {
            backtrack(result, current + "D", up, down + 1, max);
        }
    }
};

// Main function to demonstrate Catalan Numbers pattern
int main() {
    // Example 1: Basic Catalan Numbers
    cout << "Example 1: Basic Catalan Numbers" << endl;
    CatalanNumbers catalanCalculator;
    
    cout << "First 10 Catalan numbers:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "C(" << i << ") = " << catalanCalculator.catalanDP(i) << endl;
    }
    
    // Example 2: Unique Binary Search Trees
    cout << "\nExample 2: Unique Binary Search Trees" << endl;
    UniqueBinarySearchTrees solution2;
    
    for (int i = 1; i <= 5; i++) {
        cout << "Number of unique BSTs with " << i << " nodes: " << solution2.numTrees(i) << endl;
    }
    
    // Example 3: Generate Parentheses
    cout << "\nExample 3: Generate Parentheses" << endl;
    GenerateParentheses solution3;
    
    int n = 3;
    cout << "All valid parentheses expressions with " << n << " pairs:" << endl;
    vector<string> parentheses = solution3.generateParenthesis(n);
    
    for (const string& s : parentheses) {
        cout << s << endl;
    }
    
    cout << "Total count: " << solution3.countParenthesis(n) << endl;
    
    // Example 4: Different Ways to Add Parentheses
    cout << "\nExample 4: Different Ways to Add Parentheses" << endl;
    DifferentWaysToAddParentheses solution4;
    
    string expression = "2*3-4*5";
    cout << "Expression: " << expression << endl;
    
    vector<int> results = solution4.diffWaysToCompute(expression);
    cout << "Possible results:" << endl;
    
    for (int result : results) {
        cout << result << " ";
    }
    cout << endl;
    
    // Example 5: Count Valid Parentheses Expressions
    cout << "\nExample 5: Count Valid Parentheses Expressions" << endl;
    CountValidParentheses solution5;
    
    for (int i = 1; i <= 5; i++) {
        cout << "Number of valid parentheses expressions with " << i << " pairs: "
             << solution5.countValidParentheses(i) << endl;
    }
    
    // Example 6: Count Binary Trees
    cout << "\nExample 6: Count Binary Trees" << endl;
    CountBinaryTrees solution6;
    
    for (int i = 1; i <= 5; i++) {
        cout << "Number of structurally unique binary trees with " << i << " nodes: "
             << solution6.countTrees(i) << endl;
    }
    
    // Example 7: Dyck Paths
    cout << "\nExample 7: Dyck Paths" << endl;
    DyckPaths solution7;
    
    n = 3;
    cout << "Number of Dyck paths of length " << 2*n << ": " << solution7.countDyckPaths(n) << endl;
    
    vector<string> paths = solution7.generateDyckPaths(n);
    cout << "All Dyck paths of length " << 2*n << ":" << endl;
    
    for (const string& path : paths) {
        cout << path << endl;
    }
    
    return 0;
}
