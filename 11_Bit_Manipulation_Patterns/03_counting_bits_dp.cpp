/**
 * Pattern: Bitwise DP - Counting Bits Optimization
 * 
 * Description:
 * This pattern combines bit manipulation with dynamic programming to efficiently
 * compute the number of set bits (1s) in the binary representation of numbers
 * in a range. The key insight is reusing previously calculated results by recognizing
 * patterns in how bit counts change across numbers.
 * 
 * Time Complexity: O(n) where n is the number of integers to process
 * Space Complexity: O(n) for storing the results
 * 
 * When to use:
 * - When counting bits for a range of numbers
 * - When needing to process bit counts in an efficient way
 * - In problems where binary representation patterns need to be exploited
 * 
 * LeetCode Problems:
 * - 338. Counting Bits
 * - 191. Number of 1 Bits (as a subroutine)
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>

using namespace std;

// Example 1: Counting Bits using DP
// LeetCode 338: https://leetcode.com/problems/counting-bits/
class CountingBitsDP {
public:
    // Approach 1: Using Least Significant Bit (LSB)
    vector<int> countBits(int n) {
        vector<int> result(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            // The number of bits in i is equal to the number of bits in i / 2
            // plus 1 if i is odd (LSB is 1)
            result[i] = result[i >> 1] + (i & 1);
        }
        
        return result;
    }
    
    // Approach 2: Using Last Set Bit (Brian Kernighan's algorithm insight)
    vector<int> countBitsLastSetBit(int n) {
        vector<int> result(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            // i & (i-1) removes the last set bit of i
            // So result[i] = result[i & (i-1)] + 1
            result[i] = result[i & (i - 1)] + 1;
        }
        
        return result;
    }
    
    // Approach 3: Using Offset - DP with pattern recognition
    vector<int> countBitsOffset(int n) {
        vector<int> result(n + 1, 0);
        
        int offset = 1;  // Power of 2 boundary
        
        for (int i = 1; i <= n; i++) {
            // When i equals a power of 2, update offset
            if (offset * 2 == i) {
                offset = i;
            }
            
            // result[i] = 1 + result[i - offset]
            // For example, result[9] = 1 + result[9-8] = 1 + result[1] = 1 + 1 = 2
            result[i] = 1 + result[i - offset];
        }
        
        return result;
    }
};

// Example 2: Hamming Distance Sum DP
// Extension of Counting Bits pattern to sum of Hamming distances
class HammingDistanceSum {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int totalDistance = 0;
        
        // For each bit position 0 to 31 (for 32-bit integers)
        for (int i = 0; i < 32; i++) {
            int countOnes = 0;
            
            // Count how many numbers have a 1 at position i
            for (int num : nums) {
                countOnes += (num >> i) & 1;
            }
            
            // For each bit position, the total Hamming distance contribution is:
            // (count of numbers with a 1) * (count of numbers with a 0)
            totalDistance += countOnes * (n - countOnes);
        }
        
        return totalDistance;
    }
};

// Example 3: Bit Counting with Memoization
class BitCountingMemoization {
private:
    unordered_map<int, int> memo;
    
    // Recursive helper with memoization
    int countBitsHelper(int n) {
        if (n == 0) return 0;
        
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        
        // n & (n-1) removes the rightmost set bit
        int result = 1 + countBitsHelper(n & (n - 1));
        memo[n] = result;
        
        return result;
    }
    
public:
    // Count bits in a single number using memoization
    int countBits(int n) {
        memo.clear();
        return countBitsHelper(n);
    }
    
    // Count bits for a range of numbers using memoization
    vector<int> countBitsRange(int n) {
        vector<int> result(n + 1);
        memo.clear();
        
        for (int i = 0; i <= n; i++) {
            result[i] = countBitsHelper(i);
        }
        
        return result;
    }
};

// Example 4: Counting Bits in Binary Strings
class BinaryStringBitCounting {
public:
    // Count bits in a binary string
    int countBits(const string& binaryStr) {
        int count = 0;
        for (char bit : binaryStr) {
            if (bit == '1') {
                count++;
            }
        }
        return count;
    }
    
    // Generate and count all binary strings of length n
    vector<int> countAllBinaryStrings(int n) {
        int totalStrings = 1 << n;  // 2^n
        vector<int> result(totalStrings);
        
        for (int i = 0; i < totalStrings; i++) {
            // Convert i to a binary string and count its bits
            result[i] = __builtin_popcount(i);
        }
        
        return result;
    }
    
    // Count the number of binary strings of length n with k bits set
    int countBinaryStringsWithKBits(int n, int k) {
        // This is the binomial coefficient C(n,k)
        if (k > n) return 0;
        
        int result = 1;
        
        // Calculate C(n,k) = n! / (k! * (n-k)!)
        // Optimized for overflow considerations
        for (int i = 1; i <= k; i++) {
            result = result * (n - k + i) / i;
        }
        
        return result;
    }
};

// Main function to demonstrate the Counting Bits Optimization pattern
int main() {
    // Example 1: Counting Bits using DP
    cout << "Example 1: Counting Bits using DP" << endl;
    
    CountingBitsDP dp;
    int n = 16;
    
    vector<int> resultLSB = dp.countBits(n);
    cout << "Number of set bits for 0 to " << n << " using LSB approach:" << endl;
    for (int i = 0; i <= n; i++) {
        cout << i << " (" << bitset<5>(i) << "): " << resultLSB[i] << endl;
    }
    cout << endl;
    
    vector<int> resultLastBit = dp.countBitsLastSetBit(n);
    cout << "Number of set bits for 0 to " << n << " using Last Set Bit approach:" << endl;
    for (int i = 0; i <= min(n, 5); i++) {
        cout << i << " (" << bitset<5>(i) << "): " << resultLastBit[i] << endl;
    }
    cout << "..." << endl;
    for (int i = n - 3; i <= n; i++) {
        cout << i << " (" << bitset<5>(i) << "): " << resultLastBit[i] << endl;
    }
    cout << endl;
    
    // Example 2: Hamming Distance Sum DP
    cout << "Example 2: Hamming Distance Sum DP" << endl;
    
    HammingDistanceSum hds;
    vector<int> nums = {4, 14, 2};
    
    cout << "Array: [";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Binary representations:" << endl;
    for (int num : nums) {
        cout << "  " << num << " = " << bitset<4>(num) << endl;
    }
    
    cout << "Total Hamming Distance: " << hds.totalHammingDistance(nums) << endl;
    cout << endl;
    
    // Example 3: Bit Counting with Memoization
    cout << "Example 3: Bit Counting with Memoization" << endl;
    
    BitCountingMemoization memo;
    int number = 42;
    
    cout << "Number: " << number << " (" << bitset<8>(number) << ")" << endl;
    cout << "Number of set bits: " << memo.countBits(number) << endl;
    
    vector<int> memoCounts = memo.countBitsRange(7);
    cout << "Memoized bit counts for numbers 0-7:" << endl;
    for (int i = 0; i <= 7; i++) {
        cout << i << " (" << bitset<3>(i) << "): " << memoCounts[i] << endl;
    }
    cout << endl;
    
    // Example 4: Counting Bits in Binary Strings
    cout << "Example 4: Counting Bits in Binary Strings" << endl;
    
    BinaryStringBitCounting bsbc;
    string binaryStr = "10110";
    
    cout << "Binary String: " << binaryStr << endl;
    cout << "Number of set bits: " << bsbc.countBits(binaryStr) << endl;
    
    int stringLength = 3;
    cout << "Bit counts for all binary strings of length " << stringLength << ":" << endl;
    vector<int> stringCounts = bsbc.countAllBinaryStrings(stringLength);
    for (int i = 0; i < (1 << stringLength); i++) {
        cout << bitset<3>(i) << ": " << stringCounts[i] << endl;
    }
    
    int k = 2;
    cout << "Number of binary strings of length " << stringLength << " with " << k << " bits set: " 
         << bsbc.countBinaryStringsWithKBits(stringLength, k) << endl;
    
    return 0;
}
