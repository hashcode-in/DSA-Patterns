/**
 * Pattern: Bitwise Operations - Power of Two/Four Check
 * 
 * Description:
 * This pattern focuses on efficient ways to check if a number is a power of two,
 * power of four, or more generally, a power of any specific base. These checks
 * leverage bit manipulation properties to achieve constant-time operations.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 * 
 * When to use:
 * - When you need to check if a number is a power of a certain base
 * - When optimizing performance for binary representation checks
 * - In scenarios involving powers of 2, which are common in computer science
 * 
 * LeetCode Problems:
 * - 231. Power of Two
 * - 342. Power of Four
 * - Similar: 326. Power of Three (can't use bit manipulation directly)
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

// Example 1: Check if number is a power of two
// LeetCode 231: https://leetcode.com/problems/power-of-two/
class PowerOfTwo {
public:
    // Approach 1: Using bit count
    // A power of 2 has exactly one bit set to 1 in its binary representation
    bool isPowerOfTwo(int n) {
        if (n <= 0) {
            return false;
        }
        
        // Count the number of set bits
        int bitCount = 0;
        while (n > 0) {
            if (n & 1) {
                bitCount++;
            }
            n >>= 1;
        }
        
        // If exactly one bit is set, it's a power of 2
        return bitCount == 1;
    }
    
    // Approach 2: Using the property that n & (n-1) removes the rightmost set bit
    // For powers of 2, removing the only set bit results in 0
    bool isPowerOfTwoBitTrick(int n) {
        if (n <= 0) {
            return false;
        }
        
        return (n & (n - 1)) == 0;
    }
    
    // Approach 3: Using the property that for powers of 2, n & (-n) equals n
    // This is because -n is the two's complement of n
    bool isPowerOfTwoBitTrick2(int n) {
        if (n <= 0) {
            return false;
        }
        
        return (n & (-n)) == n;
    }
};

// Example 2: Check if number is a power of four
// LeetCode 342: https://leetcode.com/problems/power-of-four/
class PowerOfFour {
public:
    // Approach 1: Using logarithm
    bool isPowerOfFourMath(int n) {
        if (n <= 0) {
            return false;
        }
        
        // Check if n is a power of 2
        if ((n & (n - 1)) != 0) {
            return false;
        }
        
        // For a power of 4, the only set bit must be at an even position (0, 2, 4, ...)
        // This is equivalent to checking if n is congruent to 1 modulo 3
        return n % 3 == 1;
    }
    
    // Approach 2: Using bit mask
    // 0x55555555 = 01010101010101010101010101010101
    // This mask has 1s at even positions only (0-indexed)
    bool isPowerOfFourBitMask(int n) {
        if (n <= 0) {
            return false;
        }
        
        // Check if n is a power of 2
        if ((n & (n - 1)) != 0) {
            return false;
        }
        
        // Check if the set bit is at an even position
        return (n & 0x55555555) != 0;
    }
    
    // Approach 3: Using bit position check
    bool isPowerOfFourBitPosition(int n) {
        if (n <= 0) {
            return false;
        }
        
        // Check if n is a power of 2
        if ((n & (n - 1)) != 0) {
            return false;
        }
        
        // Find the position of the set bit (0-indexed)
        int position = 0;
        while ((n & 1) == 0) {
            n >>= 1;
            position++;
        }
        
        // For powers of 4, the position should be even (0, 2, 4, ...)
        return position % 2 == 0;
    }
};

// Example 3: Check if number is a power of a specific base
class PowerOfBase {
public:
    // Generic function to check if n is a power of base
    // Note: This uses logarithm, not bit manipulation
    bool isPowerOf(int n, int base) {
        if (n <= 0 || base <= 0) {
            return false;
        }
        
        // Special case for base = 1
        if (base == 1) {
            return n == 1;
        }
        
        // Check if log_base(n) is an integer
        double logResult = log(n) / log(base);
        return abs(logResult - round(logResult)) < 1e-10;
    }
    
    // Specialized function for powers of 3
    // LeetCode 326: https://leetcode.com/problems/power-of-three/
    bool isPowerOfThree(int n) {
        if (n <= 0) {
            return false;
        }
        
        // Check if n is a divisor of the largest power of 3 that fits in 32-bit int
        // 3^19 = 1162261467 is the largest power of 3 less than INT_MAX
        return 1162261467 % n == 0;
    }
};

// Example 4: Count trailing zeros in a binary number
class TrailingZeros {
public:
    // Using the property that n & (-n) isolates the rightmost set bit
    int countTrailingZeros(int n) {
        if (n == 0) {
            return 32;  // All 32 bits are zero
        }
        
        // Isolate the rightmost set bit
        int rightmostBit = n & (-n);
        
        // Count the position of this bit
        int count = 0;
        while (rightmostBit > 1) {
            rightmostBit >>= 1;
            count++;
        }
        
        return count;
    }
    
    // Alternative approach using GCC built-in function
    int countTrailingZerosBuiltin(int n) {
        if (n == 0) {
            return 32;  // All 32 bits are zero
        }
        
        // __builtin_ctz counts trailing zeros
        return __builtin_ctz(n);
    }
};

// Example 5: Find next power of 2
class NextPowerOfTwo {
public:
    // Find the smallest power of 2 greater than or equal to n
    int nextPowerOf2(int n) {
        if (n <= 0) {
            return 1;
        }
        
        // If n is already a power of 2, return n
        if ((n & (n - 1)) == 0) {
            return n;
        }
        
        // Find the most significant bit position
        int position = 0;
        int temp = n;
        while (temp > 0) {
            temp >>= 1;
            position++;
        }
        
        // Next power of 2 is 2^position
        return 1 << position;
    }
    
    // Alternative approach using bit manipulation
    int nextPowerOf2Alt(int n) {
        if (n <= 0) {
            return 1;
        }
        
        n--;
        
        // Set all bits to the right of the most significant bit
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        
        return n + 1;
    }
};

// Main function to demonstrate the Power of Two/Four Check pattern
int main() {
    // Example 1: Check if number is a power of two
    cout << "Example 1: Check if number is a power of two" << endl;
    
    PowerOfTwo pot;
    std::vector<int> nums1 = {1, 2, 3, 4, 8, 10, 16, 32};
    
    cout << "Using bit count approach:" << endl;
    for (int num : nums1) {
        cout << num << " is " << (pot.isPowerOfTwo(num) ? "" : "not ") << "a power of 2" << endl;
    }
    cout << endl;
    
    cout << "Using n & (n-1) approach:" << endl;
    for (int num : nums1) {
        cout << num << " is " << (pot.isPowerOfTwoBitTrick(num) ? "" : "not ") << "a power of 2" << endl;
    }
    cout << endl;
    
    // Example 2: Check if number is a power of four
    cout << "Example 2: Check if number is a power of four" << endl;
    
    PowerOfFour pof;
    std::vector<int> nums2 = {1, 2, 4, 8, 16, 32, 64};
    
    cout << "Using bit mask approach:" << endl;
    for (int num : nums2) {
        cout << num << " is " << (pof.isPowerOfFourBitMask(num) ? "" : "not ") << "a power of 4" << endl;
    }
    cout << endl;
    
    cout << "Using bit position approach:" << endl;
    for (int num : nums2) {
        cout << num << " is " << (pof.isPowerOfFourBitPosition(num) ? "" : "not ") << "a power of 4" << endl;
    }
    cout << endl;
    
    // Example 3: Check if number is a power of a specific base
    cout << "Example 3: Check if number is a power of a specific base" << endl;
    
    PowerOfBase pob;
    std::vector<int> bases = {2, 3, 4, 5};
    int testNum = 81;
    
    cout << testNum << " is " << (pob.isPowerOfThree(testNum) ? "" : "not ") << "a power of 3" << endl;
    
    for (int base : bases) {
        cout << testNum << " is " << (pob.isPowerOf(testNum, base) ? "" : "not ") << "a power of " << base << endl;
    }
    cout << endl;
    
    // Example 4: Count trailing zeros in a binary number
    cout << "Example 4: Count trailing zeros in a binary number" << endl;
    
    TrailingZeros tz;
    std::vector<int> nums3 = {1, 2, 4, 8, 16, 32, 64, 128};
    
    for (int num : nums3) {
        cout << "Number: " << num << " (" << bitset<8>(num) << ")" << endl;
        cout << "Trailing zeros: " << tz.countTrailingZeros(num) << endl;
    }
    cout << endl;
    
    // Example 5: Find next power of 2
    cout << "Example 5: Find next power of 2" << endl;
    
    NextPowerOfTwo npot;
    std::vector<int> nums4 = {1, 2, 3, 5, 7, 10, 15, 16, 17, 31, 32};
    
    for (int num : nums4) {
        int next = npot.nextPowerOf2(num);
        cout << "Next power of 2 for " << num << ": " << next << " (" << bitset<8>(next) << ")" << endl;
    }
    
    return 0;
}
