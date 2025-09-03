/**
 * Pattern: Bitwise XOR - Finding Single/Missing Number
 * 
 * Description:
 * This pattern uses XOR operations to find a single number or missing number in a collection.
 * The key insight is the special properties of the XOR operation:
 *  - a XOR a = 0 (XOR with same number results in 0)
 *  - a XOR 0 = a (XOR with 0 doesn't change the number)
 *  - XOR is commutative and associative: a XOR b XOR a = b
 * 
 * Time Complexity: O(n) where n is the number of elements
 * Space Complexity: O(1) as we only use a single variable
 * 
 * When to use:
 * - When finding a single non-duplicated element in an array where all others appear twice
 * - When finding a missing number in a sequence
 * - When finding two unique numbers in an array where all others appear twice
 * 
 * LeetCode Problems:
 * - 136. Single Number
 * - 137. Single Number II 
 * - 260. Single Number III
 * - 268. Missing Number
 * - 389. Find the Difference
 */

#include <iostream>
#include <vector>
#include <numeric> // For accumulate

using namespace std;

// Example 1: Find Single Number
// LeetCode 136: https://leetcode.com/problems/single-number/
class SingleNumber {
public:
    int findSingleNumber(vector<int>& nums) {
        int result = 0;
        
        // XOR all numbers together
        for (int num : nums) {
            result ^= num;
        }
        
        // The result is the single number that appears only once
        return result;
    }
};

// Example 2: Find Missing Number
// LeetCode 268: https://leetcode.com/problems/missing-number/
class MissingNumber {
public:
    // Approach 1: Using XOR
    int findMissingNumber(vector<int>& nums) {
        int n = nums.size();
        int result = n; // Initialize with n (the largest number expected)
        
        // XOR result with each index and value
        for (int i = 0; i < n; i++) {
            result ^= i ^ nums[i];
        }
        
        return result;
    }
    
    // Approach 2: Using Sum
    int findMissingNumberSum(vector<int>& nums) {
        int n = nums.size();
        int expectedSum = n * (n + 1) / 2; // Sum of 0 to n
        int actualSum = 0;
        
        for (int num : nums) {
            actualSum += num;
        }
        
        return expectedSum - actualSum;
    }
};

// Example 3: Find the Difference
// LeetCode 389: https://leetcode.com/problems/find-the-difference/
class FindDifference {
public:
    char findTheDifference(string s, string t) {
        char result = 0;
        
        // XOR all characters in both strings
        for (char c : s) {
            result ^= c;
        }
        
        for (char c : t) {
            result ^= c;
        }
        
        // The result is the added character
        return result;
    }
};

// Example 4: Single Number II
// LeetCode 137: https://leetcode.com/problems/single-number-ii/
class SingleNumberII {
public:
    // Bit manipulation solution for elements appearing three times
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        
        for (int num : nums) {
            // Update first and second counters
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        
        return ones;
    }
};

// Example 5: Single Number III
// LeetCode 260: https://leetcode.com/problems/single-number-iii/
class SingleNumberIII {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        // First XOR all numbers together
        int bitmask = 0;
        for (int num : nums) {
            bitmask ^= num;
        }
        
        // Find the rightmost set bit (a bit that is 1)
        // This bit is different between our two unique numbers
        int diff = bitmask & (-bitmask);
        
        // Divide the numbers into two groups based on this bit
        // XOR elements in each group separately
        int x = 0;
        for (int num : nums) {
            // Check if the bit is set
            if (num & diff) {
                x ^= num;
            }
        }
        
        // The two single numbers are x and bitmask^x
        return {x, bitmask ^ x};
    }
};

// Main function to demonstrate the Bitwise XOR pattern
int main() {
    // Example 1: Find Single Number
    cout << "Example 1: Find Single Number" << endl;
    
    SingleNumber sn;
    vector<int> nums1 = {4, 1, 2, 1, 2};
    
    cout << "Array: [";
    for (size_t i = 0; i < nums1.size(); i++) {
        cout << nums1[i];
        if (i < nums1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "The single number is: " << sn.findSingleNumber(nums1) << " (expected: 4)" << endl;
    cout << endl;
    
    // Example 2: Find Missing Number
    cout << "Example 2: Find Missing Number" << endl;
    
    MissingNumber mn;
    vector<int> nums2 = {3, 0, 1};
    
    cout << "Array: [";
    for (size_t i = 0; i < nums2.size(); i++) {
        cout << nums2[i];
        if (i < nums2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "The missing number using XOR: " << mn.findMissingNumber(nums2) << " (expected: 2)" << endl;
    cout << "The missing number using Sum: " << mn.findMissingNumberSum(nums2) << " (expected: 2)" << endl;
    cout << endl;
    
    // Example 3: Find the Difference
    cout << "Example 3: Find the Difference" << endl;
    
    FindDifference fd;
    string s = "abcd";
    string t = "abcde";
    
    cout << "String s: \"" << s << "\"" << endl;
    cout << "String t: \"" << t << "\"" << endl;
    
    cout << "The difference is: '" << fd.findTheDifference(s, t) << "' (expected: 'e')" << endl;
    cout << endl;
    
    // Example 4: Single Number II
    cout << "Example 4: Single Number II" << endl;
    
    SingleNumberII sn2;
    vector<int> nums3 = {2, 2, 3, 2};
    
    cout << "Array: [";
    for (size_t i = 0; i < nums3.size(); i++) {
        cout << nums3[i];
        if (i < nums3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "The single number appearing once (others three times): " << sn2.singleNumber(nums3) << " (expected: 3)" << endl;
    cout << endl;
    
    // Example 5: Single Number III
    cout << "Example 5: Single Number III" << endl;
    
    SingleNumberIII sn3;
    vector<int> nums4 = {1, 2, 1, 3, 2, 5};
    
    cout << "Array: [";
    for (size_t i = 0; i < nums4.size(); i++) {
        cout << nums4[i];
        if (i < nums4.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    vector<int> result = sn3.singleNumbers(nums4);
    cout << "The two single numbers are: [" << result[0] << ", " << result[1] << "] (expected: [3, 5] or [5, 3])" << endl;
    
    return 0;
}
