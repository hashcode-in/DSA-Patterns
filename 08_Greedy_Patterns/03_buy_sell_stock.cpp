/**
 * Pattern: Greedy - Buy/Sell Stock
 * 
 * Description:
 * This pattern focuses on problems related to buying and selling stocks to maximize profit.
 * The greedy approach makes local optimal decisions at each step regarding when to buy
 * and when to sell stocks.
 * 
 * Time Complexity: O(n) where n is the length of the prices array
 * 
 * Space Complexity: O(1) as we only need a few variables to track states
 * 
 * When to use:
 * - Problems requiring maximizing profit from stock transactions
 * - Scenarios where you need to track minimum or maximum values so far
 * - Problems where making locally optimal decisions leads to a global optimum
 * 
 * LeetCode Problems:
 * - 121. Best Time to Buy and Sell Stock
 * - 122. Best Time to Buy and Sell Stock II
 * - 123. Best Time to Buy and Sell Stock III (DP approach)
 * - 188. Best Time to Buy and Sell Stock IV (DP approach)
 * - 309. Best Time to Buy and Sell Stock with Cooldown (DP approach)
 * - 714. Best Time to Buy and Sell Stock with Transaction Fee (DP approach)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Best Time to Buy and Sell Stock
// LeetCode 121: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class BuyAndSellStock {
public:
    // Approach: Track minimum price so far and maximum profit
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            // Update the minimum price seen so far
            minPrice = min(minPrice, price);
            
            // Update the maximum profit if selling at current price
            maxProfit = max(maxProfit, price - minPrice);
        }
        
        return maxProfit;
    }
    
    // Alternative approach: Calculate differences between consecutive days
    int maxProfitDifference(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int n = prices.size();
        int maxProfit = 0;
        
        for (int i = 1; i < n; i++) {
            // If there's a price increase, consider it as potential profit
            if (prices[i] > prices[i-1]) {
                maxProfit = max(maxProfit, prices[i] - prices[0]);
                
                // Update the minimum price if found
                for (int j = 0; j < i; j++) {
                    if (prices[j] < prices[0]) {
                        maxProfit = max(maxProfit, prices[i] - prices[j]);
                    }
                }
            }
        }
        
        return maxProfit;
    }
};

// Example 2: Best Time to Buy and Sell Stock II
// LeetCode 122: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
class BuyAndSellStockII {
public:
    // Approach: Take every profitable transaction
    int maxProfit(vector<int>& prices) {
        int totalProfit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            // If current price is higher than previous day's price
            // we can make a profit by buying on previous day and selling today
            if (prices[i] > prices[i-1]) {
                totalProfit += prices[i] - prices[i-1];
            }
        }
        
        return totalProfit;
    }
    
    // Alternative approach: Valley-Peak
    int maxProfitValleyPeak(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        int totalProfit = 0;
        int valley = prices[0];  // Buy price
        int peak = prices[0];    // Sell price
        int i = 0;
        
        while (i < n - 1) {
            // Find the next valley (local minimum)
            while (i < n - 1 && prices[i] >= prices[i + 1]) {
                i++;
            }
            valley = prices[i];
            
            // Find the next peak (local maximum)
            while (i < n - 1 && prices[i] <= prices[i + 1]) {
                i++;
            }
            peak = prices[i];
            
            // Add the profit from this valley-peak pair
            totalProfit += peak - valley;
        }
        
        return totalProfit;
    }
};

// Example 3: Best Time to Buy and Sell Stock III (at most two transactions)
// LeetCode 123: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
class BuyAndSellStockIII {
public:
    // Approach: Dynamic Programming
    // Since this requires a more complex state tracking, it's not a pure greedy approach
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        // Represents the max profit after i-th day with at most j transactions
        // where j is 0, 1, or 2 (we can have 0, 1, or 2 transactions)
        vector<vector<int>> dp(n, vector<int>(3, 0));
        
        for (int j = 1; j <= 2; j++) {  // At most 2 transactions
            int maxDiff = -prices[0];   // Initialize with buying on day 0
            
            for (int i = 1; i < n; i++) {
                // Either don't do any transaction on day i, or sell on day i
                dp[i][j] = max(dp[i-1][j], prices[i] + maxDiff);
                
                // Update the maximum difference
                // (maximum profit from previous transactions - cost of buying at day i)
                maxDiff = max(maxDiff, dp[i-1][j-1] - prices[i]);
            }
        }
        
        return dp[n-1][2];  // Maximum profit after considering all days and 2 transactions
    }
    
    // Alternative approach: Two passes
    int maxProfitTwoPasses(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        // First transaction: maximum profit if we make one transaction up to day i
        vector<int> firstTransaction(n, 0);
        int minPrice = prices[0];
        
        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            firstTransaction[i] = max(firstTransaction[i-1], prices[i] - minPrice);
        }
        
        // Second transaction: maximum profit if we make one more transaction after day i
        int maxPrice = prices[n-1];
        int maxProfit = firstTransaction[n-1];  // At least as good as just one transaction
        
        for (int i = n - 2; i >= 0; i--) {
            maxPrice = max(maxPrice, prices[i]);
            // Maximum profit = max profit from first transaction up to day i
            //                  + max profit from second transaction after day i
            maxProfit = max(maxProfit, firstTransaction[i] + (maxPrice - prices[i]));
        }
        
        return maxProfit;
    }
};

// Example 4: Best Time to Buy and Sell Stock with Cooldown
// LeetCode 309: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
class BuyAndSellStockWithCooldown {
public:
    // Approach: State Machine with Dynamic Programming
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        // Three states: 
        // sold[i]: max profit on day i if we just sold stock
        // hold[i]: max profit on day i if we are holding stock
        // rest[i]: max profit on day i if we are in cooldown/reset state
        vector<int> sold(n, 0);
        vector<int> hold(n, 0);
        vector<int> rest(n, 0);
        
        // Initial states
        hold[0] = -prices[0];  // Buy on day 0
        sold[0] = 0;           // Cannot sell on day 0
        rest[0] = 0;           // Start with nothing
        
        for (int i = 1; i < n; i++) {
            // If we're holding, either we were already holding or we just bought
            hold[i] = max(hold[i-1], rest[i-1] - prices[i]);
            
            // If we just sold, we must have been holding
            sold[i] = hold[i-1] + prices[i];
            
            // If we're resting, either we were resting or we just sold
            rest[i] = max(rest[i-1], sold[i-1]);
        }
        
        // Final state is either just sold or resting (both are not holding)
        return max(sold[n-1], rest[n-1]);
    }
    
    // Alternative approach: Simplified DP
    int maxProfitSimplified(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        // buy[i]: Maximum profit ending with a buy or holding state on day i
        // sell[i]: Maximum profit ending with a sell on day i
        // rest[i]: Maximum profit ending with a rest state on day i
        vector<int> buy(n, 0);
        vector<int> sell(n, 0);
        vector<int> rest(n, 0);
        
        buy[0] = -prices[0];
        sell[0] = 0;
        rest[0] = 0;
        
        for (int i = 1; i < n; i++) {
            buy[i] = max(buy[i-1], rest[i-1] - prices[i]);
            sell[i] = max(sell[i-1], buy[i-1] + prices[i]);
            rest[i] = max(rest[i-1], max(buy[i-1], sell[i-1]));
        }
        
        return max(sell[n-1], rest[n-1]);
    }
};

// Example 5: Best Time to Buy and Sell Stock with Transaction Fee
// LeetCode 714: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
class BuyAndSellStockWithFee {
public:
    // Approach: State Machine with Dynamic Programming
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        // Two states: 
        // cash[i]: max profit on day i if we have cash (not holding stock)
        // hold[i]: max profit on day i if we are holding stock
        vector<int> cash(n, 0);
        vector<int> hold(n, 0);
        
        // Initial states
        hold[0] = -prices[0];  // Buy on day 0
        cash[0] = 0;           // Start with cash
        
        for (int i = 1; i < n; i++) {
            // If we have cash, either we had cash previously or we sold stock
            cash[i] = max(cash[i-1], hold[i-1] + prices[i] - fee);
            
            // If we're holding, either we were holding or we just bought
            hold[i] = max(hold[i-1], cash[i-1] - prices[i]);
        }
        
        // Final state should be having cash (not holding stock)
        return cash[n-1];
    }
    
    // Alternative approach: Greedy with Transaction Fee
    int maxProfitGreedy(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        int totalProfit = 0;
        int buyPrice = prices[0];
        
        for (int i = 1; i < n; i++) {
            // If current price is less than buy price, update buy price
            if (prices[i] < buyPrice) {
                buyPrice = prices[i];
            }
            // If selling now minus fee is profitable, sell and update buy price
            else if (prices[i] > buyPrice + fee) {
                totalProfit += prices[i] - buyPrice - fee;
                // Update buy price (accounting for the fee)
                buyPrice = prices[i] - fee;
            }
        }
        
        return totalProfit;
    }
};

// Main function to demonstrate Buy/Sell Stock pattern
int main() {
    // Example 1: Best Time to Buy and Sell Stock
    cout << "Example 1: Best Time to Buy and Sell Stock" << endl;
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    
    BuyAndSellStock bs;
    cout << "Prices: [7, 1, 5, 3, 6, 4]" << endl;
    cout << "Maximum profit: " << bs.maxProfit(prices1) << endl;
    
    // Example 2: Best Time to Buy and Sell Stock II
    cout << "\nExample 2: Best Time to Buy and Sell Stock II" << endl;
    vector<int> prices2 = {7, 1, 5, 3, 6, 4};
    
    BuyAndSellStockII bs2;
    cout << "Prices: [7, 1, 5, 3, 6, 4]" << endl;
    cout << "Maximum profit with multiple transactions: " << bs2.maxProfit(prices2) << endl;
    
    // Example 3: Best Time to Buy and Sell Stock III
    cout << "\nExample 3: Best Time to Buy and Sell Stock III" << endl;
    vector<int> prices3 = {3, 3, 5, 0, 0, 3, 1, 4};
    
    BuyAndSellStockIII bs3;
    cout << "Prices: [3, 3, 5, 0, 0, 3, 1, 4]" << endl;
    cout << "Maximum profit with at most two transactions: " << bs3.maxProfit(prices3) << endl;
    
    // Example 4: Best Time to Buy and Sell Stock with Cooldown
    cout << "\nExample 4: Best Time to Buy and Sell Stock with Cooldown" << endl;
    vector<int> prices4 = {1, 2, 3, 0, 2};
    
    BuyAndSellStockWithCooldown bs4;
    cout << "Prices: [1, 2, 3, 0, 2]" << endl;
    cout << "Maximum profit with cooldown: " << bs4.maxProfit(prices4) << endl;
    
    // Example 5: Best Time to Buy and Sell Stock with Transaction Fee
    cout << "\nExample 5: Best Time to Buy and Sell Stock with Transaction Fee" << endl;
    vector<int> prices5 = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    
    BuyAndSellStockWithFee bs5;
    cout << "Prices: [1, 3, 2, 8, 4, 9], Fee: " << fee << endl;
    cout << "Maximum profit with transaction fee: " << bs5.maxProfit(prices5, fee) << endl;
    
    return 0;
}
