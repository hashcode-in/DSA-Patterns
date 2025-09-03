/**
 * Pattern: DP - Longest Increasing Subsequence (LIS)
 * 
 * Description:
 * The Longest Increasing Subsequence (LIS) problem is to find the length of the longest
 * subsequence in an array such that all elements of the subsequence are in strictly increasing
 * order. A subsequence is a sequence that can be derived from another sequence by deleting
 * some elements without changing the order of the remaining elements.
 * 
 * Time Complexity: 
 * - O(n²) for the standard dynamic programming approach
 * - O(n log n) for the binary search optimization
 * 
 * Space Complexity: O(n)
 * 
 * When to use:
 * - Finding the longest sequence with specific ordering properties
 * - Problems involving arranging items in a specific order
 * - Finding patterns in sequences or arrays
 * - Optimization problems with ordering constraints
 * 
 * LeetCode Problems:
 * - 300. Longest Increasing Subsequence
 * - 354. Russian Doll Envelopes
 * - 646. Maximum Length of Pair Chain
 * - 673. Number of Longest Increasing Subsequence
 * - 1048. Longest String Chain
 * - 1218. Longest Arithmetic Subsequence of Given Difference
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

using namespace std;

// Example 1: Basic Longest Increasing Subsequence
// LeetCode 300: https://leetcode.com/problems/longest-increasing-subsequence/
class LongestIncreasingSubsequence {
public:
    // Approach 1: Dynamic Programming (O(n²))
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1); // Base case: each element is a LIS of length 1
        
        int maxLength = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLength = max(maxLength, dp[i]);
        }
        
        return maxLength;
    }
    
    // Approach 2: Binary Search Optimization (O(n log n))
    int lengthOfLISOptimized(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<int> tails; // tails[i] = smallest tail of all increasing subsequences of length i+1
        
        for (int num : nums) {
            // Binary search to find the position to insert or update
            auto it = lower_bound(tails.begin(), tails.end(), num);
            
            if (it == tails.end()) {
                // If num is greater than all tails, extend the LIS
                tails.push_back(num);
            } else {
                // Otherwise, update the tail
                *it = num;
            }
        }
        
        return tails.size();
    }
    
    // Approach 3: Finding the actual LIS (not just its length)
    vector<int> findLIS(vector<int>& nums) {
        if (nums.empty()) return {};
        
        int n = nums.size();
        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);
        // prev[i] = previous index in the LIS ending at index i
        vector<int> prev(n, -1);
        
        int maxLength = 1;
        int endIndex = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
            
            if (dp[i] > maxLength) {
                maxLength = dp[i];
                endIndex = i;
            }
        }
        
        // Reconstruct the LIS
        vector<int> lis;
        while (endIndex != -1) {
            lis.push_back(nums[endIndex]);
            endIndex = prev[endIndex];
        }
        
        reverse(lis.begin(), lis.end());
        return lis;
    }
};

// Example 2: Russian Doll Envelopes
// LeetCode 354: https://leetcode.com/problems/russian-doll-envelopes/
class RussianDollEnvelopes {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty()) return 0;
        
        // Sort by width (ascending) and height (descending)
        sort(envelopes.begin(), envelopes.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
             });
        
        // Extract heights and find LIS
        vector<int> heights;
        for (const auto& env : envelopes) {
            heights.push_back(env[1]);
        }
        
        // Apply binary search LIS to heights
        return lengthOfLISOptimized(heights);
    }
    
private:
    // Binary search optimization for LIS
    int lengthOfLISOptimized(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<int> tails;
        
        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }
        
        return tails.size();
    }
};

// Example 3: Maximum Length of Pair Chain
// LeetCode 646: https://leetcode.com/problems/maximum-length-of-pair-chain/
class MaximumLengthOfPairChain {
public:
    // Approach 1: Dynamic Programming
    int findLongestChain(vector<vector<int>>& pairs) {
        if (pairs.empty()) return 0;
        
        // Sort pairs by their first element
        sort(pairs.begin(), pairs.end());
        
        int n = pairs.size();
        // dp[i] = length of longest chain ending at pairs[i]
        vector<int> dp(n, 1);
        
        int maxLength = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLength = max(maxLength, dp[i]);
        }
        
        return maxLength;
    }
    
    // Approach 2: Greedy Algorithm (more efficient)
    int findLongestChainGreedy(vector<vector<int>>& pairs) {
        if (pairs.empty()) return 0;
        
        // Sort pairs by their second element (end of interval)
        sort(pairs.begin(), pairs.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });
        
        int count = 1;
        int currentEnd = pairs[0][1];
        
        for (int i = 1; i < pairs.size(); i++) {
            if (pairs[i][0] > currentEnd) {
                count++;
                currentEnd = pairs[i][1];
            }
        }
        
        return count;
    }
};

// Example 4: Number of Longest Increasing Subsequence
// LeetCode 673: https://leetcode.com/problems/number-of-longest-increasing-subsequence/
class NumberOfLIS {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);
        // count[i] = number of LIS ending at index i
        vector<int> count(n, 1);
        
        int maxLength = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    } else if (dp[j] + 1 == dp[i]) {
                        count[i] += count[j];
                    }
                }
            }
            maxLength = max(maxLength, dp[i]);
        }
        
        // Count all LIS with maxLength
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] == maxLength) {
                result += count[i];
            }
        }
        
        return result;
    }
};

// Example 5: Longest String Chain
// LeetCode 1048: https://leetcode.com/problems/longest-string-chain/
class LongestStringChain {
public:
    int longestStrChain(vector<string>& words) {
        // Sort words by length
        sort(words.begin(), words.end(), 
             [](const string& a, const string& b) {
                 return a.length() < b.length();
             });
        
        // dp[word] = length of longest chain ending with word
        unordered_map<string, int> dp;
        int maxLength = 1;
        
        for (const string& word : words) {
            dp[word] = 1; // Base case
            
            // Try removing each character to find predecessor
            for (int i = 0; i < word.length(); i++) {
                string predecessor = word.substr(0, i) + word.substr(i + 1);
                
                if (dp.find(predecessor) != dp.end()) {
                    dp[word] = max(dp[word], dp[predecessor] + 1);
                }
            }
            
            maxLength = max(maxLength, dp[word]);
        }
        
        return maxLength;
    }
};

// Example 6: Longest Arithmetic Subsequence of Given Difference
// LeetCode 1218: https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/
class LongestArithmeticSubsequence {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> dp; // dp[val] = length of arithmetic subsequence ending with val
        int maxLength = 1;
        
        for (int num : arr) {
            int prev = num - difference;
            
            if (dp.find(prev) != dp.end()) {
                dp[num] = dp[prev] + 1;
            } else {
                dp[num] = 1; // Start a new subsequence
            }
            
            maxLength = max(maxLength, dp[num]);
        }
        
        return maxLength;
    }
};

// Example 7: Longest Bitonic Subsequence
class LongestBitonicSubsequence {
public:
    int longestBitonicSubsequence(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        
        // lis[i] = length of longest increasing subsequence ending at index i
        vector<int> lis(n, 1);
        
        // lds[i] = length of longest decreasing subsequence starting at index i
        vector<int> lds(n, 1);
        
        // Compute LIS for each element
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
        }
        
        // Compute LDS for each element (from right to left)
        for (int i = n - 2; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[i] > nums[j]) {
                    lds[i] = max(lds[i], lds[j] + 1);
                }
            }
        }
        
        // Maximum bitonic subsequence length = max(lis[i] + lds[i] - 1)
        int maxLength = 1;
        for (int i = 0; i < n; i++) {
            maxLength = max(maxLength, lis[i] + lds[i] - 1);
        }
        
        return maxLength;
    }
};

// Example 8: Maximum Sum Increasing Subsequence
class MaximumSumIncreasingSubsequence {
public:
    int maxSumIncreasingSubsequence(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        // dp[i] = maximum sum of increasing subsequence ending at index i
        vector<int> dp = nums; // Initialize with the numbers themselves
        
        int maxSum = dp[0];
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + nums[i]);
                }
            }
            maxSum = max(maxSum, dp[i]);
        }
        
        return maxSum;
    }
    
    // Additionally, find the actual subsequence with maximum sum
    vector<int> findMaxSumIncreasingSubsequence(vector<int>& nums) {
        if (nums.empty()) return {};
        
        int n = nums.size();
        // dp[i] = maximum sum of increasing subsequence ending at index i
        vector<int> dp = nums;
        // prev[i] = previous index in the maximum sum increasing subsequence ending at index i
        vector<int> prev(n, -1);
        
        int maxSum = dp[0];
        int endIndex = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j] && dp[j] + nums[i] > dp[i]) {
                    dp[i] = dp[j] + nums[i];
                    prev[i] = j;
                }
            }
            
            if (dp[i] > maxSum) {
                maxSum = dp[i];
                endIndex = i;
            }
        }
        
        // Reconstruct the subsequence
        vector<int> msis;
        while (endIndex != -1) {
            msis.push_back(nums[endIndex]);
            endIndex = prev[endIndex];
        }
        
        reverse(msis.begin(), msis.end());
        return msis;
    }
};

// Utility function to print a vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate Longest Increasing Subsequence pattern
int main() {
    // Example 1: Basic Longest Increasing Subsequence
    cout << "Example 1: Longest Increasing Subsequence" << endl;
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    LongestIncreasingSubsequence solution1;
    
    cout << "Array: ";
    printVector(nums1);
    
    int lisLength = solution1.lengthOfLIS(nums1);
    cout << "Length of LIS: " << lisLength << endl;
    
    int lisLengthOpt = solution1.lengthOfLISOptimized(nums1);
    cout << "Length of LIS (optimized): " << lisLengthOpt << endl;
    
    vector<int> actualLIS = solution1.findLIS(nums1);
    cout << "Actual LIS: ";
    printVector(actualLIS);
    
    // Example 2: Russian Doll Envelopes
    cout << "\nExample 2: Russian Doll Envelopes" << endl;
    vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    RussianDollEnvelopes solution2;
    
    cout << "Envelopes: ";
    for (const auto& env : envelopes) {
        cout << "(" << env[0] << "," << env[1] << ") ";
    }
    cout << endl;
    
    int maxEnvelopes = solution2.maxEnvelopes(envelopes);
    cout << "Maximum number of nested envelopes: " << maxEnvelopes << endl;
    
    // Example 3: Maximum Length of Pair Chain
    cout << "\nExample 3: Maximum Length of Pair Chain" << endl;
    vector<vector<int>> pairs = {{1, 2}, {2, 3}, {3, 4}};
    MaximumLengthOfPairChain solution3;
    
    cout << "Pairs: ";
    for (const auto& pair : pairs) {
        cout << "(" << pair[0] << "," << pair[1] << ") ";
    }
    cout << endl;
    
    int chainLength = solution3.findLongestChain(pairs);
    cout << "Maximum length of chain (DP): " << chainLength << endl;
    
    int chainLengthGreedy = solution3.findLongestChainGreedy(pairs);
    cout << "Maximum length of chain (Greedy): " << chainLengthGreedy << endl;
    
    // Example 4: Number of Longest Increasing Subsequence
    cout << "\nExample 4: Number of Longest Increasing Subsequence" << endl;
    vector<int> nums4 = {1, 3, 5, 4, 7};
    NumberOfLIS solution4;
    
    cout << "Array: ";
    printVector(nums4);
    
    int numLIS = solution4.findNumberOfLIS(nums4);
    cout << "Number of LIS: " << numLIS << endl;
    
    // Example 5: Longest String Chain
    cout << "\nExample 5: Longest String Chain" << endl;
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};
    LongestStringChain solution5;
    
    cout << "Words: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;
    
    int chainLen = solution5.longestStrChain(words);
    cout << "Longest string chain length: " << chainLen << endl;
    
    // Example 6: Longest Arithmetic Subsequence of Given Difference
    cout << "\nExample 6: Longest Arithmetic Subsequence of Given Difference" << endl;
    vector<int> nums6 = {1, 2, 3, 4};
    int difference = 1;
    LongestArithmeticSubsequence solution6;
    
    cout << "Array: ";
    printVector(nums6);
    cout << "Difference: " << difference << endl;
    
    int lasLength = solution6.longestSubsequence(nums6, difference);
    cout << "Length of longest arithmetic subsequence: " << lasLength << endl;
    
    // Example 7: Longest Bitonic Subsequence
    cout << "\nExample 7: Longest Bitonic Subsequence" << endl;
    vector<int> nums7 = {1, 11, 2, 10, 4, 5, 2, 1};
    LongestBitonicSubsequence solution7;
    
    cout << "Array: ";
    printVector(nums7);
    
    int lbsLength = solution7.longestBitonicSubsequence(nums7);
    cout << "Length of longest bitonic subsequence: " << lbsLength << endl;
    
    // Example 8: Maximum Sum Increasing Subsequence
    cout << "\nExample 8: Maximum Sum Increasing Subsequence" << endl;
    vector<int> nums8 = {1, 101, 2, 3, 100, 4, 5};
    MaximumSumIncreasingSubsequence solution8;
    
    cout << "Array: ";
    printVector(nums8);
    
    int msisSum = solution8.maxSumIncreasingSubsequence(nums8);
    cout << "Maximum sum of increasing subsequence: " << msisSum << endl;
    
    vector<int> msisElements = solution8.findMaxSumIncreasingSubsequence(nums8);
    cout << "Elements of MSIS: ";
    printVector(msisElements);
    
    return 0;
}
