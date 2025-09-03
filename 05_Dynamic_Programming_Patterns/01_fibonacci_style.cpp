/**
 * Pattern: DP - 1D Array (Fibonacci Style)
 * 
 * Description:
 * This pattern involves problems where each state depends on one or two previous states
 * in a linear manner. The classic example is the Fibonacci sequence, where each number
 * is the sum of the two preceding ones. This pattern is characterized by:
 * 1. Linear dependency on previous states
 * 2. 1D array or a few variables to track state
 * 3. Iterative or recursive solutions with memoization
 * 
 * Time Complexity: O(n) where n is the input size
 * Space Complexity: O(n) for memoization array, can be optimized to O(1) for some problems
 * 
 * When to use:
 * - When a problem can be solved by considering only a limited number of previous states
 * - When there's a clear recurrence relation between current and previous states
 * - When solving optimization problems with sequential decision-making
 * 
 * LeetCode Problems:
 * - 70. Climbing Stairs
 * - 198. House Robber
 * - 213. House Robber II
 * - 509. Fibonacci Number
 * - 746. Min Cost Climbing Stairs
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Example 1: Fibonacci Number
// LeetCode 509: https://leetcode.com/problems/fibonacci-number/
class FibonacciNumber {
public:
    // Approach 1: Top-down with memoization (recursive)
    int fibMemo(int n) {
        vector<int> memo(n + 1, -1);
        return fibHelper(n, memo);
    }
    
    int fibHelper(int n, vector<int>& memo) {
        // Base cases
        if (n <= 1) return n;
        
        // Check if already computed
        if (memo[n] != -1) return memo[n];
        
        // Compute and store result
        memo[n] = fibHelper(n - 1, memo) + fibHelper(n - 2, memo);
        return memo[n];
    }
    
    // Approach 2: Bottom-up with tabulation (iterative)
    int fibTab(int n) {
        if (n <= 1) return n;
        
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
    
    // Approach 3: Space-optimized (iterative)
    int fib(int n) {
        if (n <= 1) return n;
        
        int prev2 = 0;  // F(0)
        int prev1 = 1;  // F(1)
        int curr = 0;
        
        for (int i = 2; i <= n; i++) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Example 2: Climbing Stairs
// LeetCode 70: https://leetcode.com/problems/climbing-stairs/
class ClimbingStairs {
public:
    // Approach 1: Top-down with memoization
    int climbStairsMemo(int n) {
        unordered_map<int, int> memo;
        return climbStairsHelper(n, memo);
    }
    
    int climbStairsHelper(int n, unordered_map<int, int>& memo) {
        // Base cases
        if (n <= 2) return n;
        
        // Check if already computed
        if (memo.find(n) != memo.end()) return memo[n];
        
        // Compute and store result
        memo[n] = climbStairsHelper(n - 1, memo) + climbStairsHelper(n - 2, memo);
        return memo[n];
    }
    
    // Approach 2: Bottom-up with tabulation
    int climbStairsTab(int n) {
        if (n <= 2) return n;
        
        vector<int> dp(n + 1);
        dp[1] = 1;  // 1 way to climb 1 stair
        dp[2] = 2;  // 2 ways to climb 2 stairs: 1+1 or 2
        
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
    
    // Approach 3: Space-optimized
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1;  // Ways to climb 1 stair
        int prev1 = 2;  // Ways to climb 2 stairs
        int curr = 0;
        
        for (int i = 3; i <= n; i++) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Example 3: House Robber
// LeetCode 198: https://leetcode.com/problems/house-robber/
class HouseRobber {
public:
    // Approach 1: Top-down with memoization
    int robMemo(vector<int>& nums) {
        vector<int> memo(nums.size(), -1);
        return robHelper(nums, nums.size() - 1, memo);
    }
    
    int robHelper(vector<int>& nums, int i, vector<int>& memo) {
        // Base cases
        if (i < 0) return 0;
        
        // Check if already computed
        if (memo[i] != -1) return memo[i];
        
        // Decision: rob current house or skip it
        memo[i] = max(robHelper(nums, i - 2, memo) + nums[i], robHelper(nums, i - 1, memo));
        return memo[i];
    }
    
    // Approach 2: Bottom-up with tabulation
    int robTab(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        
        return dp[n - 1];
    }
    
    // Approach 3: Space-optimized
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];          // Max money after robbing house 0
        int prev1 = max(nums[0], nums[1]); // Max money after considering houses 0 and 1
        
        for (int i = 2; i < n; i++) {
            int curr = max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Example 4: House Robber II (circular arrangement)
// LeetCode 213: https://leetcode.com/problems/house-robber-ii/
class HouseRobberII {
public:
    // Helper function for linear house robbery
    int robLinear(vector<int>& nums, int start, int end) {
        int prev2 = 0;
        int prev1 = 0;
        
        for (int i = start; i <= end; i++) {
            int curr = max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Case 1: Rob first house, skip last house
        int rob1 = robLinear(nums, 0, n - 2);
        
        // Case 2: Skip first house, rob last house
        int rob2 = robLinear(nums, 1, n - 1);
        
        return max(rob1, rob2);
    }
};

// Example 5: Min Cost Climbing Stairs
// LeetCode 746: https://leetcode.com/problems/min-cost-climbing-stairs/
class MinCostClimbingStairs {
public:
    // Approach 1: Top-down with memoization
    int minCostClimbingStairsMemo(vector<int>& cost) {
        vector<int> memo(cost.size(), -1);
        return min(minCostHelper(cost, 0, memo), minCostHelper(cost, 1, memo));
    }
    
    int minCostHelper(vector<int>& cost, int i, vector<int>& memo) {
        // Base case: reached beyond the top
        if (i >= cost.size()) return 0;
        
        // Check if already computed
        if (memo[i] != -1) return memo[i];
        
        // Compute and store result
        memo[i] = cost[i] + min(minCostHelper(cost, i + 1, memo), minCostHelper(cost, i + 2, memo));
        return memo[i];
    }
    
    // Approach 2: Bottom-up with tabulation
    int minCostClimbingStairsTab(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1);
        
        // Base cases: can start from step 0 or step 1
        dp[0] = 0;
        dp[1] = 0;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        
        return dp[n];
    }
    
    // Approach 3: Space-optimized
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev2 = 0;  // Min cost to reach step 0
        int prev1 = 0;  // Min cost to reach step 1
        
        for (int i = 2; i <= n; i++) {
            int curr = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Example 6: Maximum Sum of Non-Adjacent Elements
class MaxSumNonAdjacent {
public:
    // Find the maximum sum of non-adjacent elements in an array
    int maxSumNonAdjacent(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int include = nums[0];  // Max sum including the current element
        int exclude = 0;        // Max sum excluding the current element
        
        for (int i = 1; i < n; i++) {
            // Current include is previous exclude + current element
            int new_include = exclude + nums[i];
            
            // Current exclude is max of previous include and exclude
            exclude = max(include, exclude);
            
            // Update include
            include = new_include;
        }
        
        return max(include, exclude);
    }
};

// Example 7: Decode Ways
// LeetCode 91: https://leetcode.com/problems/decode-ways/
class DecodeWays {
public:
    // Bottom-up approach
    int numDecodings(string s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;
        
        vector<int> dp(n + 1, 0);
        dp[0] = 1; // Empty string has one way to decode
        dp[1] = 1; // First character has one way if it's not '0'
        
        for (int i = 2; i <= n; i++) {
            // Check if current digit is valid (not '0')
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }
            
            // Check if last two digits form a valid letter (10-26)
            int twoDigit = stoi(s.substr(i - 2, 2));
            if (twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }
        
        return dp[n];
    }
    
    // Space-optimized approach
    int numDecodingsOptimized(string s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;
        
        int prev2 = 1; // dp[0]
        int prev1 = 1; // dp[1]
        
        for (int i = 2; i <= n; i++) {
            int curr = 0;
            
            // Check if current digit is valid (not '0')
            if (s[i - 1] != '0') {
                curr += prev1;
            }
            
            // Check if last two digits form a valid letter (10-26)
            int twoDigit = stoi(s.substr(i - 2, 2));
            if (twoDigit >= 10 && twoDigit <= 26) {
                curr += prev2;
            }
            
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

// Utility function to print vector
void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Fibonacci-style DP pattern
int main() {
    // Example 1: Fibonacci Number
    cout << "Example 1: Fibonacci Number" << endl;
    FibonacciNumber fib;
    int n = 10;
    cout << "Fibonacci of " << n << " (Memoization): " << fib.fibMemo(n) << endl;
    cout << "Fibonacci of " << n << " (Tabulation): " << fib.fibTab(n) << endl;
    cout << "Fibonacci of " << n << " (Optimized): " << fib.fib(n) << endl;
    
    // Example 2: Climbing Stairs
    cout << "\nExample 2: Climbing Stairs" << endl;
    ClimbingStairs stairs;
    int steps = 5;
    cout << "Ways to climb " << steps << " stairs (Memoization): " << stairs.climbStairsMemo(steps) << endl;
    cout << "Ways to climb " << steps << " stairs (Tabulation): " << stairs.climbStairsTab(steps) << endl;
    cout << "Ways to climb " << steps << " stairs (Optimized): " << stairs.climbStairs(steps) << endl;
    
    // Example 3: House Robber
    cout << "\nExample 3: House Robber" << endl;
    vector<int> houses = {1, 2, 3, 1};
    HouseRobber robber;
    cout << "Houses: ";
    printVector(houses);
    cout << "Maximum loot (Memoization): " << robber.robMemo(houses) << endl;
    cout << "Maximum loot (Tabulation): " << robber.robTab(houses) << endl;
    cout << "Maximum loot (Optimized): " << robber.rob(houses) << endl;
    
    // Example 4: House Robber II (circular)
    cout << "\nExample 4: House Robber II (circular)" << endl;
    vector<int> houses2 = {2, 3, 2};
    HouseRobberII robber2;
    cout << "Houses (circular): ";
    printVector(houses2);
    cout << "Maximum loot (circular): " << robber2.rob(houses2) << endl;
    
    // Example 5: Min Cost Climbing Stairs
    cout << "\nExample 5: Min Cost Climbing Stairs" << endl;
    vector<int> cost = {10, 15, 20};
    MinCostClimbingStairs minCost;
    cout << "Costs: ";
    printVector(cost);
    cout << "Minimum cost (Memoization): " << minCost.minCostClimbingStairsMemo(cost) << endl;
    cout << "Minimum cost (Tabulation): " << minCost.minCostClimbingStairsTab(cost) << endl;
    cout << "Minimum cost (Optimized): " << minCost.minCostClimbingStairs(cost) << endl;
    
    // Example 6: Maximum Sum of Non-Adjacent Elements
    cout << "\nExample 6: Maximum Sum of Non-Adjacent Elements" << endl;
    vector<int> nums = {3, 2, 7, 10};
    MaxSumNonAdjacent maxSum;
    cout << "Array: ";
    printVector(nums);
    cout << "Maximum sum of non-adjacent elements: " << maxSum.maxSumNonAdjacent(nums) << endl;
    
    // Example 7: Decode Ways
    cout << "\nExample 7: Decode Ways" << endl;
    string s = "226";
    DecodeWays decode;
    cout << "String: " << s << endl;
    cout << "Number of ways to decode (Tabulation): " << decode.numDecodings(s) << endl;
    cout << "Number of ways to decode (Optimized): " << decode.numDecodingsOptimized(s) << endl;
    
    return 0;
}
