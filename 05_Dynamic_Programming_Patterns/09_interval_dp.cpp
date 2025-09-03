/**
 * Pattern: DP - Interval DP
 * 
 * Description:
 * Interval DP involves problems where we consider intervals or segments of elements.
 * We typically process intervals of increasing lengths, combining smaller intervals to
 * form larger ones and computing optimal values for these intervals.
 * 
 * Time Complexity: Usually O(n³) where n is the length of the sequence
 * Space Complexity: O(n²) for the 2D DP table
 * 
 * When to use:
 * - Problems involving finding optimal ways to partition a sequence
 * - Problems requiring merging or splitting intervals optimally
 * - Matrix chain multiplication and similar problems
 * - Problems involving optimal splitting of strings/arrays
 * 
 * LeetCode Problems:
 * - 312. Burst Balloons
 * - 1039. Minimum Score Triangulation of Polygon
 * - 546. Remove Boxes
 * - 1000. Minimum Cost to Merge Stones
 * - 1547. Minimum Cost to Cut a Stick
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

// Example 1: Matrix Chain Multiplication
// A classic interval DP problem
class MatrixChainMultiplication {
public:
    // Returns the minimum number of scalar multiplications needed to multiply
    // a chain of matrices with dimensions specified by dims
    int matrixChainOrder(vector<int>& dims) {
        int n = dims.size() - 1; // Number of matrices
        
        // dp[i][j] = minimum cost of multiplying matrices from i to j
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Compute costs for chains of increasing length
        for (int len = 2; len <= n; len++) { // Chain length
            for (int i = 0; i <= n - len; i++) { // Starting matrix
                int j = i + len - 1; // Ending matrix
                dp[i][j] = INT_MAX;
                
                // Try each possible split point
                for (int k = i; k < j; k++) {
                    // Cost = Cost of left subchain + Cost of right subchain + Cost of multiplying the results
                    int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        
        return dp[0][n - 1];
    }
    
    // Function to return the optimal parenthesization
    string getOptimalParenthesization(vector<int>& dims) {
        int n = dims.size() - 1;
        
        // dp[i][j] = minimum cost of multiplying matrices from i to j
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // split[i][j] = optimal split point k for matrices i to j
        vector<vector<int>> split(n, vector<int>(n, 0));
        
        // Compute costs for chains of increasing length
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        split[i][j] = k;
                    }
                }
            }
        }
        
        // Reconstruct the optimal parenthesization
        return printOptimalParens(split, 0, n - 1);
    }
    
    string printOptimalParens(const vector<vector<int>>& split, int i, int j) {
        if (i == j) {
            return "A" + to_string(i + 1);  // Matrix names start from A1
        } else {
            return "(" + printOptimalParens(split, i, split[i][j]) +
                   printOptimalParens(split, split[i][j] + 1, j) + ")";
        }
    }
};

// Example 2: Burst Balloons
// LeetCode 312: https://leetcode.com/problems/burst-balloons/
class BurstBalloons {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        
        // Add 1 at the beginning and end to handle edge cases
        vector<int> balloons(n + 2, 1);
        for (int i = 0; i < n; i++) {
            balloons[i + 1] = nums[i];
        }
        
        // dp[i][j] = maximum coins obtained by bursting all balloons between i and j (exclusive)
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        // Compute maximum coins for increasing intervals
        for (int len = 1; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                
                // Try each balloon as the last one to burst
                for (int k = i; k <= j; k++) {
                    // Coins = Left boundary value * Last burst balloon value * Right boundary value
                    //       + Maximum coins from left subinterval + Maximum coins from right subinterval
                    dp[i][j] = max(dp[i][j], 
                                  dp[i][k-1] + 
                                  balloons[i-1] * balloons[k] * balloons[j+1] + 
                                  dp[k+1][j]);
                }
            }
        }
        
        return dp[1][n];
    }
};

// Example 3: Minimum Score Triangulation of Polygon
// LeetCode 1039: https://leetcode.com/problems/minimum-score-triangulation-of-polygon/
class MinScoreTriangulation {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        
        // dp[i][j] = minimum score of triangulation for the subpolygon from vertex i to j
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Process intervals of increasing lengths
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                // Try each vertex k between i and j as the third point of the triangle
                for (int k = i + 1; k < j; k++) {
                    // Score = Score of triangle (i,k,j) + Optimal scores of subpolygons
                    dp[i][j] = min(dp[i][j], 
                                 dp[i][k] + values[i] * values[k] * values[j] + dp[k][j]);
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

// Example 4: Remove Boxes
// LeetCode 546: https://leetcode.com/problems/remove-boxes/
class RemoveBoxes {
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        
        // dp[i][j][k] = maximum points from removing boxes[i...j]
        // where k is the number of adjacent boxes with the same color as boxes[i] to the left
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        
        return calculatePoints(boxes, dp, 0, n - 1, 0);
    }
    
private:
    int calculatePoints(vector<int>& boxes, vector<vector<vector<int>>>& dp, int i, int j, int k) {
        // Base case: empty interval
        if (i > j) return 0;
        
        // Return memoized result if available
        if (dp[i][j][k] > 0) return dp[i][j][k];
        
        // Initial solution: remove boxes[i] together with k same-colored boxes to the left
        int originalI = i;
        int originalK = k;
        
        // Extend the interval by including consecutive boxes of the same color
        while (i + 1 <= j && boxes[i] == boxes[i + 1]) {
            i++;
            k++;
        }
        
        // Option 1: Remove the current group of same-colored boxes
        int result = (k + 1) * (k + 1) + calculatePoints(boxes, dp, i + 1, j, 0);
        
        // Option 2: Try all ways to extend the current group by first removing other boxes
        for (int m = i + 1; m <= j; m++) {
            if (boxes[m] == boxes[i]) {
                // Remove boxes between i and m, then combine boxes[i] with boxes[m]
                result = max(result, 
                           calculatePoints(boxes, dp, i + 1, m - 1, 0) +
                           calculatePoints(boxes, dp, m, j, k + 1));
            }
        }
        
        // Memoize and return the result
        return dp[originalI][j][originalK] = result;
    }
};

// Example 5: Minimum Cost to Merge Stones
// LeetCode 1000: https://leetcode.com/problems/minimum-cost-to-merge-stones/
class MinCostMergeStones {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        
        // Check if merging to one pile is possible
        if ((n - 1) % (K - 1) != 0) return -1;
        
        // Calculate prefix sums for quick range sum computation
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }
        
        // dp[i][j][k] = minimum cost to merge stones[i...j] into k piles
        vector<vector<vector<int>>> dp(n, 
                                     vector<vector<int>>(n, 
                                                      vector<int>(K + 1, INT_MAX)));
        
        // Base case: each stone is already a pile
        for (int i = 0; i < n; i++) {
            dp[i][i][1] = 0;
        }
        
        // Process intervals of increasing lengths
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                
                // Try merging into different number of piles
                for (int k = 2; k <= K; k++) {
                    // If we want more piles than stones, not possible
                    if (k > len) continue;
                    
                    // Try different split points
                    for (int m = i; m < j; m += K - 1) {
                        if (dp[i][m][1] != INT_MAX && dp[m + 1][j][k - 1] != INT_MAX) {
                            dp[i][j][k] = min(dp[i][j][k], dp[i][m][1] + dp[m + 1][j][k - 1]);
                        }
                    }
                }
                
                // Merge k piles into 1 pile if possible
                if (dp[i][j][K] != INT_MAX) {
                    dp[i][j][1] = dp[i][j][K] + prefixSum[j + 1] - prefixSum[i];
                }
            }
        }
        
        return dp[0][n - 1][1];
    }
    
    // Simplified version with 2D DP
    int mergeStonesSimplified(vector<int>& stones, int K) {
        int n = stones.size();
        
        // Check if merging to one pile is possible
        if ((n - 1) % (K - 1) != 0) return -1;
        
        // Calculate prefix sums
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }
        
        // dp[i][j] = minimum cost to merge stones[i...j] optimally
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Process intervals of increasing lengths
        for (int len = K; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                // Try different split points
                for (int m = i; m < j; m += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }
                
                // If we can merge all stones in the interval into one pile, add the cost
                if ((j - i) % (K - 1) == 0) {
                    dp[i][j] += prefixSum[j + 1] - prefixSum[i];
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

// Example 6: Minimum Cost to Cut a Stick
// LeetCode 1547: https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
class MinCostCutStick {
public:
    int minCost(int n, vector<int>& cuts) {
        // Add endpoints to the cuts array
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        
        int m = cuts.size();
        
        // dp[i][j] = minimum cost to cut the stick from position cuts[i] to cuts[j]
        vector<vector<int>> dp(m, vector<int>(m, 0));
        
        // Process intervals of increasing lengths
        for (int len = 2; len < m; len++) {
            for (int i = 0; i + len < m; i++) {
                int j = i + len;
                dp[i][j] = INT_MAX;
                
                // Try each cut point between i and j
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
                }
            }
        }
        
        return dp[0][m - 1];
    }
};

// Example 7: Palindrome Partitioning II
// LeetCode 132: https://leetcode.com/problems/palindrome-partitioning-ii/
class PalindromePartitioning {
public:
    int minCut(string s) {
        int n = s.length();
        
        // isPalindrome[i][j] = true if s[i...j] is a palindrome
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        
        // Pre-compute palindrome information
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;  // Single characters are palindromes
        }
        
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);  // Check adjacent characters
        }
        
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i + 1][j - 1]);
            }
        }
        
        // dp[i] = minimum number of cuts needed for s[0...i]
        vector<int> dp(n, INT_MAX);
        
        for (int i = 0; i < n; i++) {
            // If s[0...i] is already a palindrome, no cuts needed
            if (isPalindrome[0][i]) {
                dp[i] = 0;
                continue;
            }
            
            // Try all possible last cuts
            for (int j = 0; j < i; j++) {
                if (isPalindrome[j + 1][i]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        
        return dp[n - 1];
    }
};

// Utility function to print a 2D vector
void print2DVector(const vector<vector<int>>& vec) {
    for (const auto& row : vec) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate Interval DP pattern
int main() {
    // Example 1: Matrix Chain Multiplication
    cout << "Example 1: Matrix Chain Multiplication" << endl;
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    MatrixChainMultiplication solution1;
    
    cout << "Matrix dimensions: ";
    for (int i = 0; i < dimensions.size() - 1; i++) {
        cout << "(" << dimensions[i] << "x" << dimensions[i + 1] << ") ";
    }
    cout << endl;
    
    int minMult = solution1.matrixChainOrder(dimensions);
    cout << "Minimum number of scalar multiplications: " << minMult << endl;
    
    string parenthesization = solution1.getOptimalParenthesization(dimensions);
    cout << "Optimal parenthesization: " << parenthesization << endl;
    
    // Example 2: Burst Balloons
    cout << "\nExample 2: Burst Balloons" << endl;
    vector<int> balloons = {3, 1, 5, 8};
    BurstBalloons solution2;
    
    cout << "Balloon values: ";
    for (int val : balloons) {
        cout << val << " ";
    }
    cout << endl;
    
    int maxCoins = solution2.maxCoins(balloons);
    cout << "Maximum coins: " << maxCoins << endl;
    
    // Example 3: Minimum Score Triangulation
    cout << "\nExample 3: Minimum Score Triangulation" << endl;
    vector<int> values = {1, 2, 3};
    MinScoreTriangulation solution3;
    
    cout << "Polygon values: ";
    for (int val : values) {
        cout << val << " ";
    }
    cout << endl;
    
    int minScore = solution3.minScoreTriangulation(values);
    cout << "Minimum score: " << minScore << endl;
    
    // Example 4: Remove Boxes
    cout << "\nExample 4: Remove Boxes" << endl;
    vector<int> boxes = {1, 3, 2, 2, 2, 3, 4, 3, 1};
    RemoveBoxes solution4;
    
    cout << "Box values: ";
    for (int val : boxes) {
        cout << val << " ";
    }
    cout << endl;
    
    int maxPoints = solution4.removeBoxes(boxes);
    cout << "Maximum points: " << maxPoints << endl;
    
    // Example 5: Minimum Cost to Merge Stones
    cout << "\nExample 5: Minimum Cost to Merge Stones" << endl;
    vector<int> stones = {3, 2, 4, 1};
    int K = 2;
    MinCostMergeStones solution5;
    
    cout << "Stone values: ";
    for (int val : stones) {
        cout << val << " ";
    }
    cout << endl;
    cout << "K = " << K << endl;
    
    int minCost = solution5.mergeStones(stones, K);
    cout << "Minimum cost: " << minCost << endl;
    
    // Example 6: Minimum Cost to Cut a Stick
    cout << "\nExample 6: Minimum Cost to Cut a Stick" << endl;
    int stickLength = 7;
    vector<int> cuts = {1, 3, 4, 5};
    MinCostCutStick solution6;
    
    cout << "Stick length: " << stickLength << endl;
    cout << "Cut positions: ";
    for (int val : cuts) {
        cout << val << " ";
    }
    cout << endl;
    
    int minCutCost = solution6.minCost(stickLength, cuts);
    cout << "Minimum cost to cut: " << minCutCost << endl;
    
    // Example 7: Palindrome Partitioning II
    cout << "\nExample 7: Palindrome Partitioning II" << endl;
    string s = "aab";
    PalindromePartitioning solution7;
    
    cout << "String: " << s << endl;
    
    int minCuts = solution7.minCut(s);
    cout << "Minimum cuts needed: " << minCuts << endl;
    
    return 0;
}
