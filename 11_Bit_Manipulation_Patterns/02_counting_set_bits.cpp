/**
 * Pattern: Bitwise AND - Counting Set Bits (Hamming Weight)
 * 
 * Description:
 * This pattern focuses on counting the number of set bits (1s) in the binary representation
 * of an integer, also known as the Hamming Weight. There are several efficient algorithms
 * to perform this operation without iterating through all bits.
 * 
 * Time Complexity: 
 * - O(log n) for naive bit-by-bit method where n is the number
 * - O(set bits) for Brian Kernighan's algorithm
 * - O(1) for lookup table approach
 * 
 * Space Complexity: 
 * - O(1) for most methods
 * - O(n) if using a lookup table
 * 
 * When to use:
 * - When you need to count the number of 1 bits in an integer
 * - When calculating Hamming distance (number of positions at which bits differ)
 * - As a subroutine in more complex bit manipulation algorithms
 * - In hardware emulation or low-level programming
 * 
 * LeetCode Problems:
 * - 191. Number of 1 Bits
 * - 461. Hamming Distance
 * - 477. Total Hamming Distance
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <array>

using namespace std;

// Example 1: Count Set Bits - Naive Approach (Bit-by-bit)
// LeetCode 191: https://leetcode.com/problems/number-of-1-bits/
class CountBitsNaive {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        
        // Loop through each bit in the 32-bit integer
        for (int i = 0; i < 32; i++) {
            // If the current bit is 1, increment the count
            if ((n & (1 << i)) != 0) {
                count++;
            }
        }
        
        return count;
    }
    
    // Alternative approach with right shift
    int hammingWeightRightShift(uint32_t n) {
        int count = 0;
        
        // Loop until n becomes 0
        while (n > 0) {
            // If the least significant bit is 1, increment count
            if (n & 1) {
                count++;
            }
            // Right shift n by 1 bit
            n >>= 1;
        }
        
        return count;
    }
};

// Example 2: Brian Kernighan's Algorithm
// The key insight: n & (n-1) removes the rightmost set bit
class CountBitsBrianKernighan {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        
        while (n > 0) {
            // Remove the rightmost set bit
            n &= (n - 1);
            count++;
        }
        
        return count;
    }
};

// Example 3: Lookup Table Approach
class CountBitsLookupTable {
private:
    // Precomputed table for number of set bits in each 8-bit number
    array<int, 256> lookupTable;
    
    // Initialize the lookup table
    void initLookupTable() {
        lookupTable[0] = 0;
        for (int i = 1; i < 256; i++) {
            // Number of set bits in i = number of set bits in (i/2) + (i % 2)
            lookupTable[i] = lookupTable[i/2] + (i & 1);
        }
    }
    
public:
    CountBitsLookupTable() {
        initLookupTable();
    }
    
    int hammingWeight(uint32_t n) {
        // Process 8 bits at a time using lookup table
        return lookupTable[n & 0xFF] + 
               lookupTable[(n >> 8) & 0xFF] + 
               lookupTable[(n >> 16) & 0xFF] + 
               lookupTable[(n >> 24) & 0xFF];
    }
};

// Example 4: Using Built-in Functions (for comparison)
class CountBitsBuiltIn {
public:
    int hammingWeight(uint32_t n) {
        // Different languages have different built-in functions
        // C++: __builtin_popcount (GCC)
        return __builtin_popcount(n);
        
        // C++: std::bitset (standard library)
        // return bitset<32>(n).count();
    }
};

// Example 5: Hamming Distance (number of positions at which bits differ)
// LeetCode 461: https://leetcode.com/problems/hamming-distance/
class HammingDistance {
public:
    int hammingDistance(int x, int y) {
        // XOR the two numbers - resulting 1 bits show where they differ
        int xorResult = x ^ y;
        
        // Count set bits in the XOR result
        return __builtin_popcount(xorResult);
        
        // Alternatively, use Brian Kernighan's algorithm
        /*
        int count = 0;
        while (xorResult) {
            xorResult &= (xorResult - 1);
            count++;
        }
        return count;
        */
    }
};

// Example 6: Total Hamming Distance (sum of Hamming distances for all pairs)
// LeetCode 477: https://leetcode.com/problems/total-hamming-distance/
class TotalHammingDistance {
public:
    int totalHammingDistance(vector<int>& nums) {
        int totalDistance = 0;
        int n = nums.size();
        
        // For each bit position (0 to 31), count how many numbers have a 1
        for (int i = 0; i < 32; i++) {
            int countOnes = 0;
            
            // Count how many numbers have a 1 at the current bit position
            for (int num : nums) {
                if ((num & (1 << i)) != 0) {
                    countOnes++;
                }
            }
            
            // The total Hamming distance contribution at this bit position
            // is countOnes * (n - countOnes)
            totalDistance += countOnes * (n - countOnes);
        }
        
        return totalDistance;
    }
};

// Main function to demonstrate the Counting Set Bits pattern
int main() {
    // Example 1: Count Set Bits - Naive Approach
    cout << "Example 1: Count Set Bits - Naive Approach" << endl;
    
    CountBitsNaive naive;
    uint32_t num1 = 0b1011; // Binary 1011 (decimal 11)
    
    cout << "Number: " << num1 << " (Binary: " << bitset<32>(num1) << ")" << endl;
    cout << "Number of set bits (bit-by-bit): " << naive.hammingWeight(num1) << " (expected: 3)" << endl;
    cout << "Number of set bits (right shift): " << naive.hammingWeightRightShift(num1) << " (expected: 3)" << endl;
    cout << endl;
    
    // Example 2: Brian Kernighan's Algorithm
    cout << "Example 2: Brian Kernighan's Algorithm" << endl;
    
    CountBitsBrianKernighan kernighan;
    uint32_t num2 = 0b10101010; // Binary 10101010 (decimal 170)
    
    cout << "Number: " << num2 << " (Binary: " << bitset<32>(num2) << ")" << endl;
    cout << "Number of set bits: " << kernighan.hammingWeight(num2) << " (expected: 4)" << endl;
    cout << endl;
    
    // Example 3: Lookup Table Approach
    cout << "Example 3: Lookup Table Approach" << endl;
    
    CountBitsLookupTable lookupTable;
    uint32_t num3 = 0b11110000; // Binary 11110000 (decimal 240)
    
    cout << "Number: " << num3 << " (Binary: " << bitset<32>(num3) << ")" << endl;
    cout << "Number of set bits: " << lookupTable.hammingWeight(num3) << " (expected: 4)" << endl;
    cout << endl;
    
    // Example 4: Using Built-in Functions
    cout << "Example 4: Using Built-in Functions" << endl;
    
    CountBitsBuiltIn builtIn;
    uint32_t num4 = 0b11111111; // Binary 11111111 (decimal 255)
    
    cout << "Number: " << num4 << " (Binary: " << bitset<32>(num4) << ")" << endl;
    cout << "Number of set bits: " << builtIn.hammingWeight(num4) << " (expected: 8)" << endl;
    cout << endl;
    
    // Example 5: Hamming Distance
    cout << "Example 5: Hamming Distance" << endl;
    
    HammingDistance hd;
    int x = 0b1011; // Binary 1011 (decimal 11)
    int y = 0b0111; // Binary 0111 (decimal 7)
    
    cout << "Number X: " << x << " (Binary: " << bitset<32>(x) << ")" << endl;
    cout << "Number Y: " << y << " (Binary: " << bitset<32>(y) << ")" << endl;
    cout << "Hamming Distance: " << hd.hammingDistance(x, y) << " (expected: 2)" << endl;
    cout << endl;
    
    // Example 6: Total Hamming Distance
    cout << "Example 6: Total Hamming Distance" << endl;
    
    TotalHammingDistance thd;
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
    
    cout << "Total Hamming Distance: " << thd.totalHammingDistance(nums) << " (expected: 6)" << endl;
    
    return 0;
}
