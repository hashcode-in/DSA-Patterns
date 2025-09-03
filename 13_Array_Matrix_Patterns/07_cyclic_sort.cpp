/**
 * Pattern: Array - Cyclic Sort
 * 
 * Description:
 * This pattern deals with problems involving arrays containing numbers in a given range.
 * The key insight is that we can use the array indices to efficiently sort the array in O(n)
 * time by placing each number in its correct position. This is particularly useful when
 * the array contains values between 1 and n (or 0 and n-1).
 * 
 * Time Complexity: O(n) where n is the size of the input array
 * Space Complexity: O(1) as it sorts in-place
 * 
 * When to use:
 * - When dealing with arrays containing numbers in range [1...n] or [0...n-1]
 * - When you need to find missing numbers, duplicate numbers, or smallest missing positive
 * - When you need to sort the array in O(n) time with O(1) space
 * 
 * LeetCode Problems:
 * - 41. First Missing Positive
 * - 268. Missing Number
 * - 287. Find the Duplicate Number
 * - 442. Find All Duplicates in an Array
 * - 448. Find All Numbers Disappeared in an Array
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Example 1: Cyclic Sort - Sort an array containing numbers from 1 to n
class CyclicSort {
public:
    // Sort array containing numbers from 1 to n
    vector<int> cyclicSort(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        
        // Place each number at its correct position
        while (i < n) {
            // Correct position for nums[i] is nums[i] - 1 (for 1-based indexing)
            int correctPos = nums[i] - 1;
            
            // If the number is not at its correct position, swap
            if (nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else {
                i++;
            }
        }
        
        return nums;
    }
    
    // Sort array containing numbers from 0 to n-1
    vector<int> cyclicSortZeroIndexed(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        
        // Place each number at its correct position
        while (i < n) {
            // Correct position for nums[i] is nums[i] (for 0-based indexing)
            int correctPos = nums[i];
            
            // If the number is at valid index and not at its correct position, swap
            if (nums[i] < n && nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else {
                i++;
            }
        }
        
        return nums;
    }
};

// Example 2: Missing Number - Find the missing number in an array containing n distinct numbers in range [0, n]
// LeetCode 268: https://leetcode.com/problems/missing-number/
class MissingNumber {
public:
    // Approach 1: Using Cyclic Sort
    int findMissingNumber(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        
        // Place each number at its correct position
        while (i < n) {
            // Correct position for nums[i] is nums[i]
            int correctPos = nums[i];
            
            // If the number is within range and not at its correct position, swap
            if (nums[i] < n && nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else {
                i++;
            }
        }
        
        // Find the first index where the value is not equal to its index
        for (i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        
        // If no missing number found in the array, the missing number is n
        return n;
    }
    
    // Approach 2: Using XOR
    int findMissingNumberXOR(vector<int>& nums) {
        int n = nums.size();
        int result = n; // XOR with n first
        
        for (int i = 0; i < n; i++) {
            // XOR with index and value
            result ^= i ^ nums[i];
        }
        
        return result;
    }
    
    // Approach 3: Using Sum Formula
    int findMissingNumberSum(vector<int>& nums) {
        int n = nums.size();
        // Sum of first n natural numbers
        int expectedSum = n * (n + 1) / 2;
        
        // Actual sum of array elements
        int actualSum = 0;
        for (int num : nums) {
            actualSum += num;
        }
        
        // Missing number = expected sum - actual sum
        return expectedSum - actualSum;
    }
};

// Example 3: Find All Duplicates in an Array
// LeetCode 442: https://leetcode.com/problems/find-all-duplicates-in-an-array/
class FindDuplicates {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> duplicates;
        int n = nums.size();
        
        // Place each number at its correct position
        int i = 0;
        while (i < n) {
            // Correct position for nums[i] is nums[i] - 1 (for 1-indexed values)
            int correctPos = nums[i] - 1;
            
            // If the number is not at its correct position, swap
            if (nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else {
                i++;
            }
        }
        
        // Check for duplicates
        for (i = 0; i < n; i++) {
            // If the number at index i is not i+1, then it's a duplicate
            if (nums[i] != i + 1) {
                duplicates.push_back(nums[i]);
            }
        }
        
        return duplicates;
    }
};

// Example 4: Find the Duplicate Number
// LeetCode 287: https://leetcode.com/problems/find-the-duplicate-number/
class FindDuplicateNumber {
public:
    // Approach 1: Using Cyclic Sort
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        
        // Place each number at its correct position
        while (i < n) {
            // Correct position for nums[i] is nums[i] - 1
            int correctPos = nums[i] - 1;
            
            // If the number is not at its correct position, swap
            if (nums[i] != i + 1 && nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else if (nums[i] != i + 1) {
                // If we found the duplicate
                return nums[i];
            } else {
                i++;
            }
        }
        
        return -1; // No duplicate found (should not reach here based on problem constraints)
    }
    
    // Approach 2: Using Floyd's Tortoise and Hare (Cycle Detection)
    int findDuplicateFloyd(vector<int>& nums) {
        // Start slow and fast pointers at the first element
        int slow = nums[0];
        int fast = nums[0];
        
        // Find the meeting point inside the cycle
        do {
            slow = nums[slow]; // Move slow pointer one step
            fast = nums[nums[fast]]; // Move fast pointer two steps
        } while (slow != fast);
        
        // Find the entrance to the cycle (duplicate number)
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};

// Example 5: First Missing Positive
// LeetCode 41: https://leetcode.com/problems/first-missing-positive/
class FirstMissingPositive {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        
        // Place each positive number at its correct position
        while (i < n) {
            // Correct position for positive number nums[i] is nums[i] - 1
            int correctPos = nums[i] - 1;
            
            // Only place if it's a positive number and within range [1, n]
            // and it's not already at the correct position
            if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[correctPos]) {
                swap(nums[i], nums[correctPos]);
            } else {
                i++;
            }
        }
        
        // Find the first position where the number doesn't match its position
        for (i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        // If all numbers from 1 to n are present, return n+1
        return n + 1;
    }
};

// Main function with examples of each application
int main() {
    cout << "\n=== Cyclic Sort Pattern Examples ===\n\n";

    // Example 1: Cyclic Sort
    CyclicSort cs;
    vector<int> arr1 = {3, 1, 5, 4, 2};
    cout << "Original array: ";
    for (int num : arr1) cout << num << " ";
    
    vector<int> sorted = cs.cyclicSort(arr1);
    cout << "\nAfter cyclic sort: ";
    for (int num : sorted) cout << num << " ";
    cout << endl << endl;
    
    // Example 2: Find Missing Number
    MissingNumber mn;
    vector<int> arr2 = {3, 0, 1};
    cout << "Array for missing number: ";
    for (int num : arr2) cout << num << " ";
    
    cout << "\nMissing number (Cyclic Sort): " << mn.findMissingNumber(arr2);
    cout << "\nMissing number (XOR): " << mn.findMissingNumberXOR({3, 0, 1});
    cout << "\nMissing number (Sum): " << mn.findMissingNumberSum({3, 0, 1});
    cout << endl << endl;
    
    // Example 3: Find Duplicates
    FindDuplicates fd;
    vector<int> arr3 = {4, 3, 2, 7, 8, 2, 3, 1};
    cout << "Array for finding duplicates: ";
    for (int num : arr3) cout << num << " ";
    
    vector<int> duplicates = fd.findDuplicates(arr3);
    cout << "\nDuplicate numbers: ";
    for (int num : duplicates) cout << num << " ";
    cout << endl << endl;
    
    // Example 4: Find Duplicate Number
    FindDuplicateNumber fdn;
    vector<int> arr4 = {1, 3, 4, 2, 2};
    cout << "Array for finding duplicate number: ";
    for (int num : arr4) cout << num << " ";
    
    cout << "\nDuplicate number (Cyclic Sort): " << fdn.findDuplicate(arr4);
    cout << "\nDuplicate number (Floyd's Cycle Detection): " << fdn.findDuplicateFloyd({1, 3, 4, 2, 2});
    cout << endl << endl;
    
    // Example 5: Find First Missing Positive
    FirstMissingPositive fmp;
    vector<int> arr5 = {3, 4, -1, 1};
    cout << "Array for finding first missing positive: ";
    for (int num : arr5) cout << num << " ";
    
    cout << "\nFirst missing positive: " << fmp.firstMissingPositive(arr5);
    cout << endl << endl;
    
    return 0;
}
