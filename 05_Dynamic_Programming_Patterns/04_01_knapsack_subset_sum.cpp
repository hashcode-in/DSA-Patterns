/**
 * Pattern: DP - 1D Array (0/1 Knapsack Subset Sum Style)
 * 
 * Description:
 * The 0/1 Knapsack pattern involves problems where each item can be used at most once.
 * Unlike unbounded knapsack, here you make a binary choice for each item: either include it (1)
 * or exclude it (0). The classic examples include the 0/1 Knapsack problem (maximize value
 * with weight constraint) and Subset Sum (determine if a subset adds up to a target sum).
 * 
 * Time Complexity: O(N*W) where N is the number of items and W is the constraint (e.g., weight capacity)
 * Space Complexity: O(W) as we can optimize to use just a 1D array for the constraint
 * 
 * When to use:
 * - When each item can be used at most once
 * - When you need to make a binary choice (include/exclude) for each element
 * - Partition problems involving equal subset sums
 * - Problems involving a constraint and optimization
 * 
 * LeetCode Problems:
 * - 416. Partition Equal Subset Sum
 * - 494. Target Sum
 * - 1049. Last Stone Weight II
 * - 474. Ones and Zeroes
 * - 956. Tallest Billboard
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

// Example 1: 0/1 Knapsack Problem
class Knapsack01 {
public:
    // Find maximum value that can be put in a knapsack of capacity W
    // Approach 1: Classic 2D DP solution
    int knapsack(vector<int>& values, vector<int>& weights, int capacity) {
        int n = values.size();
        
        // dp[i][w] = maximum value of items 0...i with weight capacity w
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= capacity; w++) {
                // Skip current item if it's too heavy
                if (weights[i - 1] > w) {
                    dp[i][w] = dp[i - 1][w];
                } else {
                    // Maximum of either including or excluding current item
                    dp[i][w] = max(dp[i - 1][w], 
                                 dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                }
            }
        }
        
        return dp[n][capacity];
    }
    
    // Approach 2: Space-optimized 1D solution
    int knapsackOptimized(vector<int>& values, vector<int>& weights, int capacity) {
        int n = values.size();
        
        // dp[w] = maximum value with weight capacity w
        vector<int> dp(capacity + 1, 0);
        
        for (int i = 0; i < n; i++) {
            // Process in reverse to avoid using items more than once
            for (int w = capacity; w >= weights[i]; w--) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
        
        return dp[capacity];
    }
    
    // Approach 3: Reconstruction - find which items were selected
    pair<int, vector<int>> knapsackWithItems(vector<int>& values, vector<int>& weights, int capacity) {
        int n = values.size();
        
        // dp[i][w] = maximum value with items 0...i and weight capacity w
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= capacity; w++) {
                if (weights[i - 1] > w) {
                    dp[i][w] = dp[i - 1][w];
                } else {
                    dp[i][w] = max(dp[i - 1][w], 
                                 dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                }
            }
        }
        
        // Reconstruct the solution
        vector<int> selectedItems;
        int w = capacity;
        
        for (int i = n; i > 0 && w > 0; i--) {
            // If current item was included
            if (dp[i][w] != dp[i - 1][w]) {
                selectedItems.push_back(i - 1);  // Item index (0-based)
                w -= weights[i - 1];
            }
        }
        
        return {dp[n][capacity], selectedItems};
    }
};

// Example 2: Subset Sum Problem
// Determine if there is a subset of the array that sums up to a target sum
// LeetCode similar: 416. Partition Equal Subset Sum
class SubsetSum {
public:
    // Approach 1: 2D DP solution
    bool subsetSum(vector<int>& nums, int target) {
        int n = nums.size();
        
        // dp[i][j] = true if subset of nums[0...i-1] has sum j
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        // Empty subset has sum 0
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                // Skip current number if it's too large
                if (nums[i - 1] > j) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    // Include or exclude current number
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[n][target];
    }
    
    // Approach 2: Space-optimized 1D solution
    bool subsetSumOptimized(vector<int>& nums, int target) {
        vector<bool> dp(target + 1, false);
        dp[0] = true;  // Empty subset has sum 0
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        return dp[target];
    }
    
    // Approach 3: Find all possible subset sums
    unordered_set<int> findAllSubsetSums(vector<int>& nums) {
        unordered_set<int> sums;
        sums.insert(0);  // Empty subset has sum 0
        
        for (int num : nums) {
            unordered_set<int> newSums = sums;
            for (int sum : sums) {
                newSums.insert(sum + num);
            }
            sums = newSums;
        }
        
        return sums;
    }
};

// Example 3: Partition Equal Subset Sum
// LeetCode 416: https://leetcode.com/problems/partition-equal-subset-sum/
class PartitionEqualSubsetSum {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, we can't divide into two equal subsets
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        
        // Now the problem reduces to finding a subset with sum = target
        // This is the standard Subset Sum problem
        
        vector<bool> dp(target + 1, false);
        dp[0] = true;  // Empty subset has sum 0
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        return dp[target];
    }
};

// Example 4: Target Sum
// LeetCode 494: https://leetcode.com/problems/target-sum/
class TargetSum {
public:
    // Approach 1: DFS with memoization
    int findTargetSumWaysMemo(vector<int>& nums, int target) {
        unordered_map<string, int> memo;
        return dfs(nums, target, 0, 0, memo);
    }
    
    int dfs(vector<int>& nums, int target, int index, int currSum, unordered_map<string, int>& memo) {
        if (index == nums.size()) {
            return currSum == target ? 1 : 0;
        }
        
        string key = to_string(index) + ":" + to_string(currSum);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        // Add current number
        int addWays = dfs(nums, target, index + 1, currSum + nums[index], memo);
        
        // Subtract current number
        int subtractWays = dfs(nums, target, index + 1, currSum - nums[index], memo);
        
        memo[key] = addWays + subtractWays;
        return memo[key];
    }
    
    // Approach 2: DP (reduce to Subset Sum)
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        // If target is too large or sum is odd when target is even (or vice versa)
        if (abs(target) > sum || (sum + target) % 2 != 0) {
            return 0;
        }
        
        // Let's say we assign '+' to subset P and '-' to subset N
        // Then: sum(P) - sum(N) = target
        // And: sum(P) + sum(N) = sum(nums)
        // Solving these two equations:
        // 2 * sum(P) = target + sum(nums)
        // => sum(P) = (target + sum(nums)) / 2
        
        int newTarget = (target + sum) / 2;
        
        // Now we need to find the number of subsets with sum = newTarget
        vector<int> dp(newTarget + 1, 0);
        dp[0] = 1;  // Empty subset has sum 0
        
        for (int num : nums) {
            for (int j = newTarget; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[newTarget];
    }
};

// Example 5: Last Stone Weight II
// LeetCode 1049: https://leetcode.com/problems/last-stone-weight-ii/
class LastStoneWeightII {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // Sum of all stones
        int sum = accumulate(stones.begin(), stones.end(), 0);
        
        // Find a subset with sum closest to sum/2
        // This minimizes the difference between the two piles
        int target = sum / 2;
        
        // dp[j] = whether we can form a subset with sum j
        vector<bool> dp(target + 1, false);
        dp[0] = true;  // Empty subset has sum 0
        
        // Maximum achievable sum <= target
        int maxSum = 0;
        
        for (int stone : stones) {
            for (int j = target; j >= stone; j--) {
                dp[j] = dp[j] || dp[j - stone];
                
                if (dp[j]) {
                    maxSum = max(maxSum, j);
                }
            }
        }
        
        // The result is the difference between the two piles
        // pile1 - pile2, where pile1 + pile2 = sum and pile1 >= pile2
        // So pile1 = sum - pile2
        // Result = pile1 - pile2 = sum - pile2 - pile2 = sum - 2*pile2
        // We want to maximize pile2 (which is maxSum here)
        
        return sum - 2 * maxSum;
    }
};

// Example 6: Ones and Zeroes
// LeetCode 474: https://leetcode.com/problems/ones-and-zeroes/
class OnesAndZeroes {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // dp[i][j] = maximum number of strings with at most i zeros and j ones
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (const string& s : strs) {
            // Count zeros and ones in current string
            int zeros = count(s.begin(), s.end(), '0');
            int ones = s.length() - zeros;
            
            // Update dp array (backward to avoid counting the same string multiple times)
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 7: Tallest Billboard
// LeetCode 956: https://leetcode.com/problems/tallest-billboard/
class TallestBillboard {
public:
    int tallestBillboard(vector<int>& rods) {
        // dp[diff] = maximum height of the taller support when the difference is diff
        unordered_map<int, int> dp;
        dp[0] = 0;  // No rods used, difference is 0, height is 0
        
        for (int rod : rods) {
            // Create a copy of current state
            unordered_map<int, int> currentDP = dp;
            
            for (const auto& [diff, taller] : currentDP) {
                // Option 1: Add to taller support
                dp[diff + rod] = max(dp[diff + rod], taller + rod);
                
                // Option 2: Add to shorter support
                int newDiff = abs(diff - rod);
                int newTaller = diff > rod ? taller : taller + rod - diff;
                dp[newDiff] = max(dp[newDiff], newTaller);
            }
        }
        
        // The answer is the maximum height when difference is 0
        return dp[0];
    }
};

// Utility function to print a vector
template <typename T>
void printVector(const vector<T>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Main function to demonstrate 0/1 Knapsack Subset Sum pattern
int main() {
    // Example 1: 0/1 Knapsack Problem
    cout << "Example 1: 0/1 Knapsack Problem" << endl;
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;
    Knapsack01 solution1;
    
    cout << "Values: ";
    printVector(values);
    cout << "Weights: ";
    printVector(weights);
    cout << "Capacity: " << capacity << endl;
    
    int maxValue = solution1.knapsack(values, weights, capacity);
    cout << "Maximum value (2D DP): " << maxValue << endl;
    
    int maxValueOpt = solution1.knapsackOptimized(values, weights, capacity);
    cout << "Maximum value (1D DP): " << maxValueOpt << endl;
    
    auto [value, items] = solution1.knapsackWithItems(values, weights, capacity);
    cout << "Selected items (0-indexed): ";
    printVector(items);
    
    // Example 2: Subset Sum Problem
    cout << "\nExample 2: Subset Sum Problem" << endl;
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;
    SubsetSum solution2;
    
    cout << "Numbers: ";
    printVector(nums);
    cout << "Target: " << target << endl;
    
    bool canMakeSum = solution2.subsetSum(nums, target);
    cout << "Can make target sum (2D DP): " << (canMakeSum ? "Yes" : "No") << endl;
    
    bool canMakeSumOpt = solution2.subsetSumOptimized(nums, target);
    cout << "Can make target sum (1D DP): " << (canMakeSumOpt ? "Yes" : "No") << endl;
    
    // Example 3: Partition Equal Subset Sum
    cout << "\nExample 3: Partition Equal Subset Sum" << endl;
    vector<int> nums3 = {1, 5, 11, 5};
    PartitionEqualSubsetSum solution3;
    
    cout << "Numbers: ";
    printVector(nums3);
    
    bool canPartition = solution3.canPartition(nums3);
    cout << "Can partition into equal subsets: " << (canPartition ? "Yes" : "No") << endl;
    
    // Example 4: Target Sum
    cout << "\nExample 4: Target Sum" << endl;
    vector<int> nums4 = {1, 1, 1, 1, 1};
    int target4 = 3;
    TargetSum solution4;
    
    cout << "Numbers: ";
    printVector(nums4);
    cout << "Target: " << target4 << endl;
    
    int ways = solution4.findTargetSumWays(nums4, target4);
    cout << "Number of ways to reach target: " << ways << endl;
    
    // Example 5: Last Stone Weight II
    cout << "\nExample 5: Last Stone Weight II" << endl;
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    LastStoneWeightII solution5;
    
    cout << "Stones: ";
    printVector(stones);
    
    int minWeight = solution5.lastStoneWeightII(stones);
    cout << "Minimum possible weight after all smashes: " << minWeight << endl;
    
    // Example 6: Ones and Zeroes
    cout << "\nExample 6: Ones and Zeroes" << endl;
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;  // m zeros, n ones
    OnesAndZeroes solution6;
    
    cout << "Strings: ";
    printVector(strs);
    cout << "Max zeros (m): " << m << ", Max ones (n): " << n << endl;
    
    int maxStrings = solution6.findMaxForm(strs, m, n);
    cout << "Maximum number of strings that can be formed: " << maxStrings << endl;
    
    // Example 7: Tallest Billboard
    cout << "\nExample 7: Tallest Billboard" << endl;
    vector<int> rods = {1, 2, 3, 6};
    TallestBillboard solution7;
    
    cout << "Rods: ";
    printVector(rods);
    
    int maxHeight = solution7.tallestBillboard(rods);
    cout << "Maximum height of the billboard: " << maxHeight << endl;
    
    return 0;
}
