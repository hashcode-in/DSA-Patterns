/**
 * Pattern: DP - 1D Array (Coin Change / Unbounded Knapsack Style)
 * 
 * Description:
 * This pattern involves problems where you can use items multiple times to achieve a target.
 * Unlike the 0/1 Knapsack where each item can be used at most once, here an item can be used
 * repeatedly (unbounded). The classic example is the Coin Change problem, where you determine
 * the number of ways to make a target amount using a set of coins, with each coin being available
 * in unlimited quantity.
 * 
 * Time Complexity: O(N*T) where N is the number of items/coins and T is the target
 * Space Complexity: O(T) as we typically only need a 1D array to store results for each value up to target
 * 
 * When to use:
 * - When items can be used multiple times
 * - When trying to optimize some value (maximize, minimize) or count possibilities
 * - Problems involving making change or creating combinations with unlimited supplies
 * 
 * LeetCode Problems:
 * - 322. Coin Change
 * - 377. Combination Sum IV
 * - 518. Coin Change II
 * - 279. Perfect Squares
 * - 983. Minimum Cost For Tickets
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>

using namespace std;

// Example 1: Coin Change (Minimum Coins)
// LeetCode 322: https://leetcode.com/problems/coin-change/
class CoinChange {
public:
    // Approach 1: Top-down with memoization
    int coinChangeMemo(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, -1);
        return coinChangeDFS(coins, amount, memo);
    }
    
    int coinChangeDFS(vector<int>& coins, int amount, vector<int>& memo) {
        // Base case
        if (amount == 0) return 0;
        if (amount < 0) return -1;
        
        // Check if we've already solved this subproblem
        if (memo[amount] != -1) return memo[amount];
        
        int minCoins = INT_MAX;
        
        // Try using each coin
        for (int coin : coins) {
            int result = coinChangeDFS(coins, amount - coin, memo);
            
            // If it's possible to make change using this coin
            if (result >= 0) {
                minCoins = min(minCoins, result + 1);
            }
        }
        
        // Store result in memo table
        memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins;
        return memo[amount];
    }
    
    // Approach 2: Bottom-up with tabulation
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = minimum number of coins needed to make amount i
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
    
    // Variant: Print the coins used (not just the count)
    vector<int> coinChangeWithCoins(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        vector<int> coinUsed(amount + 1, -1);  // Store which coin was used for each amount
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                int coin = coins[j];
                if (coin <= i && dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    coinUsed[i] = coin;
                }
            }
        }
        
        if (dp[amount] > amount) return {};  // No solution
        
        // Reconstruct the solution
        vector<int> result;
        int currentAmount = amount;
        
        while (currentAmount > 0) {
            result.push_back(coinUsed[currentAmount]);
            currentAmount -= coinUsed[currentAmount];
        }
        
        return result;
    }
};

// Example 2: Coin Change II (Number of Ways)
// LeetCode 518: https://leetcode.com/problems/coin-change-ii/
class CoinChange2 {
public:
    // Bottom-up approach
    int change(int amount, vector<int>& coins) {
        // dp[i] = number of ways to make amount i
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;  // There is 1 way to make amount 0 (use no coins)
        
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        
        return dp[amount];
    }
    
    // Note: The order of loops matters!
    // Outer loop over coins ensures each coin can be used multiple times
    // but prevents duplicates (e.g., [1,2] and [2,1] are counted as one way)
    
    // Another way to think about it:
    // - When we iterate coins first, we're counting combinations (order doesn't matter)
    // - When we iterate amount first, we're counting permutations (order matters)
    
    // Alternative approach: Permutations (when order matters)
    int changePermutations(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i >= coin) {
                    dp[i] += dp[i - coin];
                }
            }
        }
        
        return dp[amount];
    }
};

// Example 3: Combination Sum IV (Permutations)
// LeetCode 377: https://leetcode.com/problems/combination-sum-iv/
class CombinationSum4 {
public:
    // Top-down with memoization
    int combinationSum4Memo(vector<int>& nums, int target) {
        unordered_map<int, int> memo;
        return combinationSumDFS(nums, target, memo);
    }
    
    int combinationSumDFS(vector<int>& nums, int target, unordered_map<int, int>& memo) {
        // Base case
        if (target == 0) return 1;
        if (target < 0) return 0;
        
        // Check memo
        if (memo.find(target) != memo.end()) return memo[target];
        
        int count = 0;
        for (int num : nums) {
            count += combinationSumDFS(nums, target - num, memo);
        }
        
        memo[target] = count;
        return count;
    }
    
    // Bottom-up approach (note: this counts permutations, not combinations)
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);  // Using unsigned to handle potential overflow
        dp[0] = 1;
        
        for (int i = 1; i <= target; i++) {
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        
        return dp[target];
    }
};

// Example 4: Perfect Squares
// LeetCode 279: https://leetcode.com/problems/perfect-squares/
class PerfectSquares {
public:
    int numSquares(int n) {
        // dp[i] = least number of perfect square numbers that sum to i
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        // Precompute all perfect squares <= n
        vector<int> perfectSquares;
        for (int i = 1; i * i <= n; i++) {
            perfectSquares.push_back(i * i);
        }
        
        for (int i = 1; i <= n; i++) {
            for (int square : perfectSquares) {
                if (i >= square) {
                    dp[i] = min(dp[i], dp[i - square] + 1);
                }
            }
        }
        
        return dp[n];
    }
};

// Example 5: Minimum Cost For Tickets
// LeetCode 983: https://leetcode.com/problems/minimum-cost-for-tickets/
class MinCostTickets {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // Last day in the travel plan
        int lastDay = days.back();
        
        // dp[i] = minimum cost to cover all travels up to day i
        vector<int> dp(lastDay + 1, 0);
        
        // Mark travel days
        vector<bool> isTravelDay(lastDay + 1, false);
        for (int day : days) {
            isTravelDay[day] = true;
        }
        
        for (int i = 1; i <= lastDay; i++) {
            // If not a travel day, cost remains the same as previous day
            if (!isTravelDay[i]) {
                dp[i] = dp[i - 1];
                continue;
            }
            
            // Consider 1-day pass
            int option1 = dp[i - 1] + costs[0];
            
            // Consider 7-day pass
            int option2 = dp[max(0, i - 7)] + costs[1];
            
            // Consider 30-day pass
            int option3 = dp[max(0, i - 30)] + costs[2];
            
            // Choose the minimum cost option
            dp[i] = min({option1, option2, option3});
        }
        
        return dp[lastDay];
    }
};

// Example 6: Rod Cutting (Maximize Profit)
class RodCutting {
public:
    int rodCutting(vector<int>& prices, int n) {
        // prices[i] = price of rod of length i+1
        // n = rod length
        
        // dp[i] = maximum profit for rod of length i
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            int maxProfit = INT_MIN;
            for (int j = 0; j < i; j++) {
                // Cut rod at length j+1, compare with best so far
                maxProfit = max(maxProfit, prices[j] + dp[i - (j + 1)]);
            }
            dp[i] = maxProfit;
        }
        
        return dp[n];
    }
};

// Example 7: Unbounded Knapsack
class UnboundedKnapsack {
public:
    int unboundedKnapsack(vector<int>& values, vector<int>& weights, int capacity) {
        // values[i], weights[i] = value and weight of item i
        // capacity = maximum weight the knapsack can hold
        
        // dp[w] = maximum value with capacity w
        vector<int> dp(capacity + 1, 0);
        
        for (int w = 1; w <= capacity; w++) {
            for (int i = 0; i < values.size(); i++) {
                if (weights[i] <= w) {
                    dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
                }
            }
        }
        
        return dp[capacity];
    }
};

// Utility function to print a vector
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Main function to demonstrate Coin Change / Unbounded Knapsack pattern
int main() {
    // Example 1: Coin Change (Minimum Coins)
    cout << "Example 1: Coin Change (Minimum Coins)" << endl;
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    CoinChange solution1;
    
    cout << "Coins: ";
    printVector(coins1);
    cout << "Amount: " << amount1 << endl;
    
    int minCoins = solution1.coinChange(coins1, amount1);
    cout << "Minimum coins needed: " << minCoins << endl;
    
    vector<int> coinsUsed = solution1.coinChangeWithCoins(coins1, amount1);
    cout << "Coins used: ";
    printVector(coinsUsed);
    
    // Example 2: Coin Change II (Number of Ways)
    cout << "\nExample 2: Coin Change II (Number of Ways)" << endl;
    vector<int> coins2 = {1, 2, 5};
    int amount2 = 5;
    CoinChange2 solution2;
    
    cout << "Coins: ";
    printVector(coins2);
    cout << "Amount: " << amount2 << endl;
    
    int ways = solution2.change(amount2, coins2);
    cout << "Number of ways to make change: " << ways << endl;
    
    // Example 3: Combination Sum IV (Permutations)
    cout << "\nExample 3: Combination Sum IV (Permutations)" << endl;
    vector<int> nums = {1, 2, 3};
    int target = 4;
    CombinationSum4 solution3;
    
    cout << "Numbers: ";
    printVector(nums);
    cout << "Target: " << target << endl;
    
    int permutations = solution3.combinationSum4(nums, target);
    cout << "Number of permutations: " << permutations << endl;
    
    // Example 4: Perfect Squares
    cout << "\nExample 4: Perfect Squares" << endl;
    int n = 12;
    PerfectSquares solution4;
    
    cout << "Number: " << n << endl;
    int minSquares = solution4.numSquares(n);
    cout << "Minimum number of perfect squares: " << minSquares << endl;
    
    // Example 5: Minimum Cost For Tickets
    cout << "\nExample 5: Minimum Cost For Tickets" << endl;
    vector<int> days = {1, 4, 6, 7, 8, 20};
    vector<int> costs = {2, 7, 15};  // 1-day, 7-day, 30-day pass costs
    MinCostTickets solution5;
    
    cout << "Travel days: ";
    printVector(days);
    cout << "Ticket costs (1-day, 7-day, 30-day): ";
    printVector(costs);
    
    int minCost = solution5.mincostTickets(days, costs);
    cout << "Minimum cost for tickets: " << minCost << endl;
    
    // Example 6: Rod Cutting
    cout << "\nExample 6: Rod Cutting" << endl;
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int rodLength = 8;
    RodCutting solution6;
    
    cout << "Prices for lengths 1 to " << prices.size() << ": ";
    printVector(prices);
    cout << "Rod length: " << rodLength << endl;
    
    int maxProfit = solution6.rodCutting(prices, rodLength);
    cout << "Maximum profit: " << maxProfit << endl;
    
    // Example 7: Unbounded Knapsack
    cout << "\nExample 7: Unbounded Knapsack" << endl;
    vector<int> values = {10, 40, 50, 70};
    vector<int> weights = {1, 3, 4, 5};
    int capacity = 8;
    UnboundedKnapsack solution7;
    
    cout << "Values: ";
    printVector(values);
    cout << "Weights: ";
    printVector(weights);
    cout << "Knapsack capacity: " << capacity << endl;
    
    int maxValue = solution7.unboundedKnapsack(values, weights, capacity);
    cout << "Maximum value: " << maxValue << endl;
    
    return 0;
}
