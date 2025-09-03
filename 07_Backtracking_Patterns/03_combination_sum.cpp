/**
 * Pattern: Backtracking - Combination Sum
 * 
 * Description:
 * This pattern finds all combinations of elements that sum to a target value, with various
 * constraints on element reuse. It's a common backtracking pattern that's used in many
 * problems involving constructing combinations with specific properties.
 * 
 * Time Complexity: 
 * - Worst case: O(N^target) where N is the number of candidates
 * - More precisely, it depends on the number of valid combinations and their lengths
 * 
 * Space Complexity: O(target) for the recursion stack depth
 * 
 * When to use:
 * - Finding combinations that sum to a target value
 * - Subset sum problems with specific constraints
 * - Coin change variations requiring all possible combinations
 * 
 * LeetCode Problems:
 * - 39. Combination Sum (elements can be reused)
 * - 40. Combination Sum II (no duplicates, each element used at most once)
 * - 216. Combination Sum III (use numbers 1-9, exactly k numbers)
 * - 377. Combination Sum IV (order matters, treated as permutation problem)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>   // For sqrt() function

using namespace std;

// Example 1: Combination Sum (elements can be reused)
// LeetCode 39: https://leetcode.com/problems/combination-sum/
class CombinationSum {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        
        // Sort the candidates for optimization (not necessary for correctness)
        sort(candidates.begin(), candidates.end());
        
        backtrack(candidates, target, 0, current, result);
        
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int remaining, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (remaining < 0) {
            return;  // Invalid combination
        }
        
        if (remaining == 0) {
            result.push_back(current);  // Valid combination found
            return;
        }
        
        // Try each candidate starting from the current position
        for (int i = start; i < candidates.size(); i++) {
            // Optimization: if the current candidate is larger than remaining, no need to proceed
            if (candidates[i] > remaining) {
                break;
            }
            
            // Include the current candidate
            current.push_back(candidates[i]);
            
            // Note: we pass i, not i+1, because we can reuse the same element
            backtrack(candidates, remaining - candidates[i], i, current, result);
            
            // Backtrack (remove the last element)
            current.pop_back();
        }
    }
};

// Example 2: Combination Sum II (no duplicates, each element used at most once)
// LeetCode 40: https://leetcode.com/problems/combination-sum-ii/
class CombinationSumII {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        
        // Sort candidates to handle duplicates
        sort(candidates.begin(), candidates.end());
        
        backtrack(candidates, target, 0, current, result);
        
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int remaining, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (remaining < 0) {
            return;  // Invalid combination
        }
        
        if (remaining == 0) {
            result.push_back(current);  // Valid combination found
            return;
        }
        
        // Try each candidate starting from the current position
        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates
            if (i > start && candidates[i] == candidates[i-1]) {
                continue;
            }
            
            // Optimization: if the current candidate is larger than remaining, no need to proceed
            if (candidates[i] > remaining) {
                break;
            }
            
            // Include the current candidate
            current.push_back(candidates[i]);
            
            // Note: we pass i+1, not i, because each element can be used only once
            backtrack(candidates, remaining - candidates[i], i + 1, current, result);
            
            // Backtrack
            current.pop_back();
        }
    }
};

// Example 3: Combination Sum III (use numbers 1-9, exactly k numbers)
// LeetCode 216: https://leetcode.com/problems/combination-sum-iii/
class CombinationSumIII {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> current;
        
        backtrack(k, n, 1, current, result);
        
        return result;
    }
    
private:
    void backtrack(int k, int remaining, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (current.size() == k && remaining == 0) {
            result.push_back(current);  // Valid combination found
            return;
        }
        
        if (current.size() >= k || remaining <= 0) {
            return;  // Invalid combination
        }
        
        // Try each number from start to 9
        for (int i = start; i <= 9; i++) {
            // Optimization: if the current number is larger than remaining, no need to proceed
            if (i > remaining) {
                break;
            }
            
            // Include the current number
            current.push_back(i);
            
            // Continue with the next number
            backtrack(k, remaining - i, i + 1, current, result);
            
            // Backtrack
            current.pop_back();
        }
    }
};

// Example 4: Combination Sum IV (order matters, treated as permutation problem)
// LeetCode 377: https://leetcode.com/problems/combination-sum-iv/
class CombinationSumIV {
public:
    // Dynamic Programming approach (since this is actually a permutation problem)
    int combinationSum4(vector<int>& nums, int target) {
        // dp[i] = number of ways to make sum i
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;  // Empty combination
        
        // For each target sum
        for (int i = 1; i <= target; i++) {
            // Try each number
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        
        return dp[target];
    }
    
    // Backtracking approach (less efficient, may time out for large inputs)
    int combinationSum4Backtrack(vector<int>& nums, int target) {
        // Memoization to avoid redundant calculations
        vector<int> memo(target + 1, -1);
        return backtrack(nums, target, memo);
    }
    
private:
    int backtrack(vector<int>& nums, int remaining, vector<int>& memo) {
        // Base cases
        if (remaining < 0) {
            return 0;
        }
        
        if (remaining == 0) {
            return 1;
        }
        
        // Check if we've already computed this
        if (memo[remaining] != -1) {
            return memo[remaining];
        }
        
        int count = 0;
        
        // Try each number
        for (int num : nums) {
            count += backtrack(nums, remaining - num, memo);
        }
        
        // Memoize the result
        memo[remaining] = count;
        
        return count;
    }
};

// Example 5: Coin Change Problem (finding combinations)
class CoinCombinations {
public:
    // Find all combinations of coins that sum to a target amount
    vector<vector<int>> coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> result;
        vector<int> current;
        
        // Sort coins for optimization
        sort(coins.begin(), coins.end());
        
        backtrack(coins, amount, 0, current, result);
        
        return result;
    }
    
private:
    void backtrack(vector<int>& coins, int remaining, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (remaining < 0) {
            return;
        }
        
        if (remaining == 0) {
            result.push_back(current);
            return;
        }
        
        // Try each coin starting from the current position
        for (int i = start; i < coins.size(); i++) {
            // Skip duplicates
            if (i > start && coins[i] == coins[i-1]) {
                continue;
            }
            
            // If the current coin is too large, skip
            if (coins[i] > remaining) {
                continue;
            }
            
            // Include the current coin
            current.push_back(coins[i]);
            
            // Since we can reuse the same coin, we pass i, not i+1
            backtrack(coins, remaining - coins[i], i, current, result);
            
            // Backtrack
            current.pop_back();
        }
    }
    
    // Variation: Each coin can be used only once
    void backtrackUniqueCoins(vector<int>& coins, int remaining, int start, 
                              vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (remaining < 0) {
            return;
        }
        
        if (remaining == 0) {
            result.push_back(current);
            return;
        }
        
        // Try each coin starting from the current position
        for (int i = start; i < coins.size(); i++) {
            // Skip duplicates
            if (i > start && coins[i] == coins[i-1]) {
                continue;
            }
            
            // If the current coin is too large, skip
            if (coins[i] > remaining) {
                continue;
            }
            
            // Include the current coin
            current.push_back(coins[i]);
            
            // Since each coin can be used only once, we pass i+1
            backtrackUniqueCoins(coins, remaining - coins[i], i + 1, current, result);
            
            // Backtrack
            current.pop_back();
        }
    }
};

// Example 6: Factor Combinations
// Find all possible combinations of factors that multiply to n
// LeetCode 254: https://leetcode.com/problems/factor-combinations/
class FactorCombinations {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> result;
        vector<int> current;
        
        backtrack(n, 2, current, result);
        
        return result;
    }
    
private:
    void backtrack(int remaining, int start, vector<int>& current, vector<vector<int>>& result) {
        // If we've used at least one factor and reached 1
        if (current.size() > 0 && remaining == 1) {
            result.push_back(current);
            return;
        }
        
        // Try each potential factor from start up to sqrt(remaining)
        for (int i = start; i <= sqrt(remaining); i++) {
            // If i is a factor of remaining
            if (remaining % i == 0) {
                // Include i as a factor
                current.push_back(i);
                
                // Continue with the same factor (i can be used multiple times)
                backtrack(remaining / i, i, current, result);
                
                // Backtrack
                current.pop_back();
            }
        }
        
        // Include the remaining itself as a factor (if it's greater than 1 and we have at least one other factor)
        if (remaining > 1 && current.size() > 0) {
            current.push_back(remaining);
            result.push_back(current);
            current.pop_back();
        }
    }
};

// Utility function to print a vector of integers
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Utility function to print a vector of vectors
void print2DVector(const vector<vector<int>>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        printVector(vec[i]);
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Main function to demonstrate Combination Sum pattern
int main() {
    // Example 1: Combination Sum
    cout << "Example 1: Combination Sum (elements can be reused)" << endl;
    vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;
    cout << "Candidates: ";
    printVector(candidates1);
    cout << ", Target: " << target1 << endl;
    
    CombinationSum cs1;
    vector<vector<int>> result1 = cs1.combinationSum(candidates1, target1);
    
    cout << "All combinations: ";
    print2DVector(result1);
    
    // Example 2: Combination Sum II
    cout << "\nExample 2: Combination Sum II (no duplicates, each element used at most once)" << endl;
    vector<int> candidates2 = {10, 1, 2, 7, 6, 1, 5};
    int target2 = 8;
    cout << "Candidates: ";
    printVector(candidates2);
    cout << ", Target: " << target2 << endl;
    
    CombinationSumII cs2;
    vector<vector<int>> result2 = cs2.combinationSum2(candidates2, target2);
    
    cout << "All unique combinations: ";
    print2DVector(result2);
    
    // Example 3: Combination Sum III
    cout << "\nExample 3: Combination Sum III (use numbers 1-9, exactly k numbers)" << endl;
    int k = 3;
    int target3 = 7;
    cout << "k = " << k << ", Target: " << target3 << endl;
    
    CombinationSumIII cs3;
    vector<vector<int>> result3 = cs3.combinationSum3(k, target3);
    
    cout << "All combinations of " << k << " numbers that sum to " << target3 << ": ";
    print2DVector(result3);
    
    // Example 4: Combination Sum IV
    cout << "\nExample 4: Combination Sum IV (order matters, treated as permutation problem)" << endl;
    vector<int> candidates4 = {1, 2, 3};
    int target4 = 4;
    cout << "Candidates: ";
    printVector(candidates4);
    cout << ", Target: " << target4 << endl;
    
    CombinationSumIV cs4;
    int result4 = cs4.combinationSum4(candidates4, target4);
    
    cout << "Number of possible combinations: " << result4 << endl;
    
    // Example 5: Coin Change Problem
    cout << "\nExample 5: Coin Change Problem (finding combinations)" << endl;
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    cout << "Coins: ";
    printVector(coins);
    cout << ", Amount: " << amount << endl;
    
    CoinCombinations cc;
    vector<vector<int>> result5 = cc.coinChange(coins, amount);
    
    cout << "All combinations of coins: ";
    print2DVector(result5);
    
    // Example 6: Factor Combinations
    cout << "\nExample 6: Factor Combinations" << endl;
    int n = 12;
    cout << "n = " << n << endl;
    
    FactorCombinations fc;
    vector<vector<int>> result6 = fc.getFactors(n);
    
    cout << "All factor combinations: ";
    print2DVector(result6);
    
    return 0;
}
