/**
 * Pattern: Stack - Monotonic Stack
 * 
 * Description:
 * A monotonic stack is a stack that maintains elements in a monotonically increasing or
 * decreasing order. It's particularly useful for solving problems where we need to find
 * the next greater/smaller element or calculate spans, as it allows us to perform these
 * operations in linear time complexity.
 * 
 * Time Complexity: O(n) where n is the size of the input array (despite the nested loops, each element is pushed and popped at most once)
 * Space Complexity: O(n) for the stack in the worst case
 * 
 * When to use:
 * - When finding the next greater/smaller element for each element in an array
 * - When calculating span problems (days, temperature, etc.)
 * - When solving problems involving range queries
 * - When implementing problems requiring histogram-like calculations
 * 
 * LeetCode Problems:
 * - 402. Remove K Digits
 * - 496. Next Greater Element I
 * - 503. Next Greater Element II
 * - 739. Daily Temperatures
 * - 901. Online Stock Span
 * - 907. Sum of Subarray Minimums
 * - 962. Maximum Width Ramp
 * - 1475. Final Prices With a Special Discount in a Shop
 * - 1673. Find the Most Competitive Subsequence
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Next Greater Element I
// LeetCode 496: https://leetcode.com/problems/next-greater-element-i/
class NextGreaterElementI {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;                  // Monotonic decreasing stack
        unordered_map<int, int> nextGreater;  // Map to store next greater element for each value in nums2
        
        // Calculate next greater element for each element in nums2
        for (int num : nums2) {
            // While stack is not empty and current element is greater than top of the stack
            while (!st.empty() && num > st.top()) {
                nextGreater[st.top()] = num;  // Set next greater element for top of stack
                st.pop();                    // Remove the element from stack
            }
            st.push(num);  // Push current element to stack
        }
        
        // For remaining elements in stack, there's no next greater element
        while (!st.empty()) {
            nextGreater[st.top()] = -1;  // No next greater element
            st.pop();
        }
        
        // Build result array for nums1
        vector<int> result;
        for (int num : nums1) {
            result.push_back(nextGreater[num]);
        }
        
        return result;
    }
};

// Example 2: Next Greater Element II (Circular Array)
// LeetCode 503: https://leetcode.com/problems/next-greater-element-ii/
class NextGreaterElementII {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);  // Initialize with -1 (no next greater element)
        stack<int> st;              // Stack to store indices (not values)
        
        // Process the array twice to simulate circular array
        for (int i = 0; i < n * 2; i++) {
            int num = nums[i % n];  // Get value using circular indexing
            
            // While stack is not empty and current element is greater than element at stack's top index
            while (!st.empty() && num > nums[st.top()]) {
                result[st.top()] = num;  // Set next greater element for the index at top of stack
                st.pop();
            }
            
            // Only push indices from first iteration to avoid duplicates
            if (i < n) {
                st.push(i);
            }
        }
        
        return result;
    }
};

// Example 3: Daily Temperatures
// LeetCode 739: https://leetcode.com/problems/daily-temperatures/
class DailyTemperatures {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);  // Initialize with 0 (no warmer day)
        stack<int> st;             // Stack to store indices
        
        for (int i = 0; i < n; i++) {
            // While stack is not empty and current temperature is higher than temperature at top index
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevDay = st.top();
                st.pop();
                result[prevDay] = i - prevDay;  // Calculate days to wait
            }
            st.push(i);  // Push current day's index
        }
        
        return result;
    }
};

// Example 4: Online Stock Span
// LeetCode 901: https://leetcode.com/problems/online-stock-span/
class StockSpanner {
private:
    stack<pair<int, int>> st;  // Stack of (price, span) pairs
    
public:
    StockSpanner() {
        // No initialization needed
    }
    
    int next(int price) {
        int span = 1;  // At minimum, span is 1 (the day itself)
        
        // While stack is not empty and current price is greater than or equal to top price
        while (!st.empty() && price >= st.top().first) {
            span += st.top().second;  // Add span of the popped price
            st.pop();
        }
        
        st.push({price, span});  // Push current price and its span
        return span;
    }
};

// Example 5: Remove K Digits
// LeetCode 402: https://leetcode.com/problems/remove-k-digits/
class RemoveKDigits {
public:
    string removeKdigits(string num, int k) {
        // Edge case: if we need to remove all digits
        if (k >= num.length()) {
            return "0";
        }
        
        stack<char> st;  // Monotonic increasing stack
        
        for (char digit : num) {
            // While we can remove digits, stack is not empty, and current digit is smaller than top
            while (k > 0 && !st.empty() && digit < st.top()) {
                st.pop();  // Remove larger digit to keep number smaller
                k--;
            }
            
            // Don't push leading zeros
            if (st.empty() && digit == '0') {
                continue;
            }
            
            st.push(digit);
        }
        
        // If we still need to remove digits, remove from the end (largest digits)
        while (k > 0 && !st.empty()) {
            st.pop();
            k--;
        }
        
        // Build the result string
        string result = "";
        while (!st.empty()) {
            result = st.top() + result;  // Add to front of result
            st.pop();
        }
        
        return result.empty() ? "0" : result;
    }
};

// Example 6: Sum of Subarray Minimums
// LeetCode 907: https://leetcode.com/problems/sum-of-subarray-minimums/
class SumSubarrayMins {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        stack<int> st;  // Monotonic increasing stack for indices
        
        // Arrays to store distance to previous and next smaller element
        vector<int> left(n), right(n);
        
        // Calculate distances to previous smaller elements
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            
            left[i] = st.empty() ? i + 1 : i - st.top();
            st.push(i);
        }
        
        // Clear stack for next calculation
        while (!st.empty()) st.pop();
        
        // Calculate distances to next smaller elements
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] > arr[i]) {
                st.pop();
            }
            
            right[i] = st.empty() ? n - i : st.top() - i;
            st.push(i);
        }
        
        // Calculate sum of minimums for all subarrays
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            // For each element, it is the minimum of (left[i] * right[i]) subarrays
            sum = (sum + (long long)arr[i] * left[i] * right[i]) % MOD;
        }
        
        return sum;
    }
};

// Example 7: Find the Most Competitive Subsequence
// LeetCode 1673: https://leetcode.com/problems/find-the-most-competitive-subsequence/
class MostCompetitiveSubsequence {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> st;  // Monotonic increasing stack
        
        for (int i = 0; i < n; i++) {
            // While stack is not empty, current element is smaller than top, and we can afford to remove elements
            while (!st.empty() && nums[i] < nums[st.top()] && st.size() + (n - i - 1) >= k) {
                st.pop();
            }
            
            // Add current element if we have space
            if (st.size() < k) {
                st.push(i);
            }
        }
        
        // Build result from stack
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = nums[st.top()];
            st.pop();
        }
        
        return result;
    }
};

// Example 8: Final Prices With a Special Discount in a Shop
// LeetCode 1475: https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/
class FinalDiscountPrices {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> result = prices;  // Copy the original prices
        stack<int> st;               // Monotonic increasing stack for indices
        
        for (int i = 0; i < n; i++) {
            // While stack is not empty and current price is less than or equal to price at top index
            while (!st.empty() && prices[i] <= prices[st.top()]) {
                result[st.top()] = prices[st.top()] - prices[i];  // Apply discount
                st.pop();
            }
            st.push(i);
        }
        
        return result;
    }
};

// Example 9: Maximum Width Ramp
// LeetCode 962: https://leetcode.com/problems/maximum-width-ramp/
class MaximumWidthRamp {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;  // Monotonic decreasing stack for indices
        
        // Push indices of potential left boundaries (decreasing sequence)
        for (int i = 0; i < n; i++) {
            if (st.empty() || nums[i] < nums[st.top()]) {
                st.push(i);
            }
        }
        
        int maxWidth = 0;
        
        // Scan from right to left to find maximum width
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[i] >= nums[st.top()]) {
                maxWidth = max(maxWidth, i - st.top());
                st.pop();
            }
        }
        
        return maxWidth;
    }
    
    // Alternative approach with two passes
    int maxWidthRampTwoPasses(vector<int>& nums) {
        int n = nums.size();
        vector<int> minLeft(n);
        
        // First pass: build array of minimum values from left
        minLeft[0] = nums[0];
        for (int i = 1; i < n; i++) {
            minLeft[i] = min(minLeft[i-1], nums[i]);
        }
        
        int maxWidth = 0;
        
        // Second pass: find maximum width from right
        for (int j = n - 1; j >= 0; j--) {
            int i = 0;
            while (i < j && minLeft[i] > nums[j]) {
                i++;
            }
            maxWidth = max(maxWidth, j - i);
        }
        
        return maxWidth;
    }
};

// Main function to demonstrate the Monotonic Stack pattern
int main() {
    // Example 1: Next Greater Element I
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    
    cout << "Example 1: Next Greater Element I" << endl;
    cout << "nums1 = [4, 1, 2], nums2 = [1, 3, 4, 2]" << endl;
    
    NextGreaterElementI nge1;
    vector<int> result1 = nge1.nextGreaterElement(nums1, nums2);
    
    cout << "Next greater elements: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 2: Next Greater Element II
    vector<int> nums3 = {1, 2, 1};
    
    cout << "Example 2: Next Greater Element II" << endl;
    cout << "nums = [1, 2, 1] (circular array)" << endl;
    
    NextGreaterElementII nge2;
    vector<int> result2 = nge2.nextGreaterElements(nums3);
    
    cout << "Next greater elements: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 3: Daily Temperatures
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    
    cout << "Example 3: Daily Temperatures" << endl;
    cout << "temperatures = [73, 74, 75, 71, 69, 72, 76, 73]" << endl;
    
    DailyTemperatures dt;
    vector<int> result3 = dt.dailyTemperatures(temperatures);
    
    cout << "Days until warmer: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 4: Online Stock Span
    cout << "Example 4: Online Stock Span" << endl;
    cout << "Prices: [100, 80, 60, 70, 60, 75, 85]" << endl;
    
    StockSpanner stockSpanner;
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> spans;
    
    for (int price : prices) {
        spans.push_back(stockSpanner.next(price));
    }
    
    cout << "Spans: [";
    for (int i = 0; i < spans.size(); i++) {
        cout << spans[i];
        if (i < spans.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 5: Remove K Digits
    cout << "Example 5: Remove K Digits" << endl;
    
    RemoveKDigits rkd;
    string num1 = "1432219";
    int k1 = 3;
    cout << "Input: \"" << num1 << "\", k = " << k1 << endl;
    cout << "Output: \"" << rkd.removeKdigits(num1, k1) << "\"" << endl;
    
    string num2 = "10200";
    int k2 = 1;
    cout << "Input: \"" << num2 << "\", k = " << k2 << endl;
    cout << "Output: \"" << rkd.removeKdigits(num2, k2) << "\"" << endl << endl;
    
    // Example 6: Sum of Subarray Minimums
    vector<int> arr = {3, 1, 2, 4};
    
    cout << "Example 6: Sum of Subarray Minimums" << endl;
    cout << "arr = [3, 1, 2, 4]" << endl;
    
    SumSubarrayMins ssm;
    int result4 = ssm.sumSubarrayMins(arr);
    
    cout << "Sum of subarray minimums: " << result4 << endl << endl;
    
    // Example 7: Find the Most Competitive Subsequence
    vector<int> nums4 = {3, 5, 2, 6};
    int k3 = 2;
    
    cout << "Example 7: Find the Most Competitive Subsequence" << endl;
    cout << "nums = [3, 5, 2, 6], k = " << k3 << endl;
    
    MostCompetitiveSubsequence mcs;
    vector<int> result5 = mcs.mostCompetitive(nums4, k3);
    
    cout << "Most competitive subsequence: [";
    for (int i = 0; i < result5.size(); i++) {
        cout << result5[i];
        if (i < result5.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 8: Final Prices With a Special Discount in a Shop
    vector<int> shop_prices = {8, 4, 6, 2, 3};
    
    cout << "Example 8: Final Prices With a Special Discount in a Shop" << endl;
    cout << "prices = [8, 4, 6, 2, 3]" << endl;
    
    FinalDiscountPrices fdp;
    vector<int> result6 = fdp.finalPrices(shop_prices);
    
    cout << "Final prices after discount: [";
    for (int i = 0; i < result6.size(); i++) {
        cout << result6[i];
        if (i < result6.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Example 9: Maximum Width Ramp
    vector<int> nums5 = {6, 0, 8, 2, 1, 5};
    
    cout << "Example 9: Maximum Width Ramp" << endl;
    cout << "nums = [6, 0, 8, 2, 1, 5]" << endl;
    
    MaximumWidthRamp mwr;
    int result7 = mwr.maxWidthRamp(nums5);
    
    cout << "Maximum width ramp: " << result7 << endl;
    
    return 0;
}
