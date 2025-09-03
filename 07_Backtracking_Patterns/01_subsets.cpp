/**
 * Pattern: Backtracking - Subsets (Include/Exclude)
 * 
 * Description:
 * This pattern is used to generate all possible subsets of a given set by making
 * binary decisions (include/exclude) for each element. It's a fundamental backtracking
 * pattern that serves as a building block for many other problems.
 * 
 * Time Complexity: 
 * - O(2^n) where n is the number of elements in the input
 * - This is because there are 2^n possible subsets for a set of size n
 * 
 * Space Complexity: O(n) for the recursion stack
 * 
 * When to use:
 * - Finding all possible subsets/combinations of a set
 * - Letter combinations problems
 * - Problems requiring enumeration of all possible states
 * 
 * LeetCode Problems:
 * - 78. Subsets
 * - 90. Subsets II (with duplicates)
 * - 17. Letter Combinations of a Phone Number
 * - 77. Combinations
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Example 1: Generate all subsets of a given array
// LeetCode 78: https://leetcode.com/problems/subsets/
class Subsets {
public:
    // Approach 1: Recursive (Backtracking)
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> currentSubset;
        
        // Start the backtracking process
        backtrack(result, currentSubset, nums, 0);
        
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& currentSubset, 
                   vector<int>& nums, int start) {
        // Add the current subset to the result
        result.push_back(currentSubset);
        
        // Explore all possible next elements
        for (int i = start; i < nums.size(); i++) {
            // Include the current element
            currentSubset.push_back(nums[i]);
            
            // Recursively generate subsets with this element included
            backtrack(result, currentSubset, nums, i + 1);
            
            // Exclude the current element (backtrack)
            currentSubset.pop_back();
        }
    }
    
    // Approach 2: Iterative (Bit Manipulation)
    vector<vector<int>> subsetsIterative(vector<int>& nums) {
        int n = nums.size();
        int numSubsets = 1 << n; // 2^n subsets
        vector<vector<int>> result;
        
        for (int i = 0; i < numSubsets; i++) {
            vector<int> currentSubset;
            
            for (int j = 0; j < n; j++) {
                // Check if jth bit is set in i
                if ((i & (1 << j)) != 0) {
                    currentSubset.push_back(nums[j]);
                }
            }
            
            result.push_back(currentSubset);
        }
        
        return result;
    }
};

// Example 2: Subsets II (with duplicates)
// LeetCode 90: https://leetcode.com/problems/subsets-ii/
class SubsetsII {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // Sort to handle duplicates
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> result;
        vector<int> currentSubset;
        
        backtrack(result, currentSubset, nums, 0);
        
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& currentSubset, 
                   vector<int>& nums, int start) {
        // Add the current subset to the result
        result.push_back(currentSubset);
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates
            if (i > start && nums[i] == nums[i-1]) {
                continue;
            }
            
            // Include the current element
            currentSubset.push_back(nums[i]);
            
            // Recursively generate subsets with this element included
            backtrack(result, currentSubset, nums, i + 1);
            
            // Exclude the current element (backtrack)
            currentSubset.pop_back();
        }
    }
};

// Example 3: Letter Combinations of a Phone Number
// LeetCode 17: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class LetterCombinations {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }
        
        // Map digits to letters
        unordered_map<char, string> digitToLetters = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        
        vector<string> result;
        string currentCombination;
        
        backtrack(result, currentCombination, digits, 0, digitToLetters);
        
        return result;
    }
    
private:
    void backtrack(vector<string>& result, string& currentCombination, 
                   string& digits, int index, unordered_map<char, string>& digitToLetters) {
        // If we've processed all digits, add the combination to the result
        if (index == digits.size()) {
            result.push_back(currentCombination);
            return;
        }
        
        // Get the letters corresponding to the current digit
        string letters = digitToLetters[digits[index]];
        
        // Try each letter
        for (char letter : letters) {
            // Include the current letter
            currentCombination.push_back(letter);
            
            // Recursively generate combinations with this letter included
            backtrack(result, currentCombination, digits, index + 1, digitToLetters);
            
            // Exclude the current letter (backtrack)
            currentCombination.pop_back();
        }
    }
};

// Example 4: Combinations
// LeetCode 77: https://leetcode.com/problems/combinations/
class Combinations {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> currentCombination;
        
        backtrack(result, currentCombination, 1, n, k);
        
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& currentCombination, 
                   int start, int n, int k) {
        // If we've selected k elements, add the combination to the result
        if (currentCombination.size() == k) {
            result.push_back(currentCombination);
            return;
        }
        
        // Try each possible next element
        for (int i = start; i <= n; i++) {
            // Include the current element
            currentCombination.push_back(i);
            
            // Recursively generate combinations with this element included
            backtrack(result, currentCombination, i + 1, n, k);
            
            // Exclude the current element (backtrack)
            currentCombination.pop_back();
        }
    }
    
    // Optimization: Pruning the search space
    void backtrackOptimized(vector<vector<int>>& result, vector<int>& currentCombination, 
                           int start, int n, int k) {
        // If we've selected k elements, add the combination to the result
        if (currentCombination.size() == k) {
            result.push_back(currentCombination);
            return;
        }
        
        // Pruning: if we can't form a combination of size k with the remaining elements, return
        // We need (k - currentCombination.size()) more elements, and we have (n - i + 1) elements left
        for (int i = start; i <= n - (k - currentCombination.size()) + 1; i++) {
            currentCombination.push_back(i);
            backtrackOptimized(result, currentCombination, i + 1, n, k);
            currentCombination.pop_back();
        }
    }
};

// Example 5: Find all subsets with a given sum
class SubsetSum {
public:
    vector<vector<int>> findSubsetsWithSum(vector<int>& nums, int targetSum) {
        vector<vector<int>> result;
        vector<int> currentSubset;
        int currentSum = 0;
        
        backtrack(result, currentSubset, nums, 0, currentSum, targetSum);
        
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& currentSubset, 
                   vector<int>& nums, int start, int currentSum, int targetSum) {
        // If the current sum equals the target sum, add the subset to the result
        if (currentSum == targetSum) {
            result.push_back(currentSubset);
            // We don't return here as there might be zeros in the array
        }
        
        // If we've gone beyond the target sum or the end of the array, return
        if (currentSum > targetSum || start >= nums.size()) {
            return;
        }
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates (if the array is sorted)
            if (i > start && nums[i] == nums[i-1]) {
                continue;
            }
            
            // Include the current element
            currentSubset.push_back(nums[i]);
            currentSum += nums[i];
            
            // Recursively generate subsets with this element included
            backtrack(result, currentSubset, nums, i + 1, currentSum, targetSum);
            
            // Exclude the current element (backtrack)
            currentSum -= nums[i];
            currentSubset.pop_back();
        }
    }
};

// Example 6: Binary Watch
// LeetCode 401: https://leetcode.com/problems/binary-watch/
class BinaryWatch {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        
        // Try all possible hours and minutes
        for (int hour = 0; hour < 12; hour++) {
            for (int minute = 0; minute < 60; minute++) {
                // Count the number of bits in hour and minute
                int hourBits = countBits(hour);
                int minuteBits = countBits(minute);
                
                // If the total number of bits equals turnedOn, add the time to the result
                if (hourBits + minuteBits == turnedOn) {
                    // Format the time as "h:mm"
                    string time = to_string(hour) + ":" + 
                                 (minute < 10 ? "0" : "") + to_string(minute);
                    result.push_back(time);
                }
            }
        }
        
        return result;
    }
    
    // Alternative approach using backtracking
    vector<string> readBinaryWatchBacktracking(int turnedOn) {
        vector<string> result;
        backtrack(result, 0, 0, 0, 0, turnedOn);
        return result;
    }
    
private:
    // Count the number of bits set to 1 in n
    int countBits(int n) {
        int count = 0;
        while (n > 0) {
            count += (n & 1);
            n >>= 1;
        }
        return count;
    }
    
    // Backtracking approach
    void backtrack(vector<string>& result, int position, int hour, int minute, int count, int turnedOn) {
        // If we have used the required number of LEDs, add the time to the result
        if (count == turnedOn) {
            string time = to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
            result.push_back(time);
            return;
        }
        
        // If we have considered all positions or hour/minute is invalid, return
        if (position == 10 || hour >= 12 || minute >= 60) {
            return;
        }
        
        // There are 10 positions total: 4 for hours (0-3) and 6 for minutes (4-9)
        
        // Try setting the current position to 1
        if (position < 4) { // Hour positions
            backtrack(result, position + 1, hour + (1 << position), minute, count + 1, turnedOn);
        } else { // Minute positions
            int minutePos = position - 4;
            backtrack(result, position + 1, hour, minute + (1 << minutePos), count + 1, turnedOn);
        }
        
        // Try not setting the current position
        backtrack(result, position + 1, hour, minute, count, turnedOn);
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

// Main function to demonstrate Subset pattern
int main() {
    // Example 1: Subsets
    cout << "Example 1: Subsets" << endl;
    vector<int> nums1 = {1, 2, 3};
    cout << "Input: ";
    printVector(nums1);
    cout << endl;
    
    Subsets subsets;
    vector<vector<int>> subsetsResult = subsets.subsets(nums1);
    
    cout << "All subsets: ";
    print2DVector(subsetsResult);
    
    // Example 2: Subsets II (with duplicates)
    cout << "\nExample 2: Subsets II (with duplicates)" << endl;
    vector<int> nums2 = {1, 2, 2};
    cout << "Input: ";
    printVector(nums2);
    cout << endl;
    
    SubsetsII subsetsII;
    vector<vector<int>> subsetsIIResult = subsetsII.subsetsWithDup(nums2);
    
    cout << "All subsets without duplicates: ";
    print2DVector(subsetsIIResult);
    
    // Example 3: Letter Combinations of a Phone Number
    cout << "\nExample 3: Letter Combinations of a Phone Number" << endl;
    string digits = "23";
    cout << "Input: " << digits << endl;
    
    LetterCombinations letterCombinations;
    vector<string> letterCombinationsResult = letterCombinations.letterCombinations(digits);
    
    cout << "All letter combinations: [";
    for (int i = 0; i < letterCombinationsResult.size(); i++) {
        cout << "\"" << letterCombinationsResult[i] << "\"";
        if (i < letterCombinationsResult.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 4: Combinations
    cout << "\nExample 4: Combinations" << endl;
    int n = 4, k = 2;
    cout << "n = " << n << ", k = " << k << endl;
    
    Combinations combinations;
    vector<vector<int>> combinationsResult = combinations.combine(n, k);
    
    cout << "All combinations of " << k << " elements from 1 to " << n << ": ";
    print2DVector(combinationsResult);
    
    // Example 5: Find all subsets with a given sum
    cout << "\nExample 5: Find all subsets with a given sum" << endl;
    vector<int> nums5 = {1, 2, 3, 4, 5};
    int targetSum = 5;
    cout << "Input: ";
    printVector(nums5);
    cout << ", Target Sum: " << targetSum << endl;
    
    SubsetSum subsetSum;
    vector<vector<int>> subsetSumResult = subsetSum.findSubsetsWithSum(nums5, targetSum);
    
    cout << "All subsets with sum " << targetSum << ": ";
    print2DVector(subsetSumResult);
    
    // Example 6: Binary Watch
    cout << "\nExample 6: Binary Watch" << endl;
    int turnedOn = 1;
    cout << "turnedOn = " << turnedOn << endl;
    
    BinaryWatch binaryWatch;
    vector<string> binaryWatchResult = binaryWatch.readBinaryWatch(turnedOn);
    
    cout << "All possible times with " << turnedOn << " LEDs turned on: [";
    for (int i = 0; i < binaryWatchResult.size(); i++) {
        cout << "\"" << binaryWatchResult[i] << "\"";
        if (i < binaryWatchResult.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
