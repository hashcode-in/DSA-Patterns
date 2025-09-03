/**
 * Pattern: Two Pointers - In-place Array Modification
 * 
 * Description:
 * This pattern uses two pointers to perform in-place modifications on arrays or strings,
 * allowing us to achieve O(n) time complexity with O(1) space complexity. This is especially
 * useful when we need to avoid using extra space for storing modified elements.
 * 
 * Time Complexity: O(n) - where n is the size of the array
 * Space Complexity: O(1) - performs operations in-place without requiring extra space
 * 
 * When to use:
 * - Removing elements from an array without using extra space
 * - Partitioning arrays based on specific criteria
 * - Moving particular elements to specific positions (e.g., moving zeroes to end)
 * - Removing duplicates from sorted arrays
 * 
 * LeetCode Problems:
 * - 26. Remove Duplicates from Sorted Array
 * - 27. Remove Element
 * - 75. Sort Colors (Dutch National Flag Problem)
 * - 80. Remove Duplicates from Sorted Array II
 * - 283. Move Zeroes
 * - 443. String Compression
 * - 905. Sort Array By Parity
 * - 2337. Move Pieces to Obtain a String
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Example 1: Remove Duplicates from Sorted Array
// LeetCode 26: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Initialize slow pointer at position 0
    int slow = 0;
    
    // Fast pointer iterates through the array
    for (int fast = 1; fast < nums.size(); fast++) {
        // If current element is different from the element at slow pointer
        if (nums[fast] != nums[slow]) {
            // Move slow pointer forward
            slow++;
            // Place the new unique element at the slow pointer position
            nums[slow] = nums[fast];
        }
        // If element is the same, fast pointer moves on while slow stays
    }
    
    // The length of the array with duplicates removed is (slow + 1)
    return slow + 1;
}

// Example 2: Remove Element
// LeetCode 27: https://leetcode.com/problems/remove-element/
int removeElement(vector<int>& nums, int val) {
    int slow = 0; // Position to place the next non-target element
    
    for (int fast = 0; fast < nums.size(); fast++) {
        // If current element is not the target value
        if (nums[fast] != val) {
            // Place it at the slow pointer position and advance slow
            nums[slow] = nums[fast];
            slow++;
        }
        // If it is the target value, skip it (fast moves on, slow stays)
    }
    
    // The length of the array with all val removed is slow
    return slow;
}

// Example 3: Sort Colors (Dutch National Flag Problem)
// LeetCode 75: https://leetcode.com/problems/sort-colors/
void sortColors(vector<int>& nums) {
    // Three pointers: low, mid, and high
    int low = 0;         // All elements before low are 0
    int mid = 0;         // All elements between low and mid are 1
    int high = nums.size() - 1;  // All elements after high are 2
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            // Found a 0, swap with the low pointer and advance both
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            // Found a 1, just advance the mid pointer
            mid++;
        } else { // nums[mid] == 2
            // Found a 2, swap with the high pointer and decrease high
            // Don't advance mid as the swapped element needs to be checked
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

// Example 4: Remove Duplicates from Sorted Array II (allow up to 2 duplicates)
// LeetCode 80: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
int removeDuplicatesII(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    
    // Slow pointer starts at position 2 (after allowing the first two elements)
    int slow = 2;
    
    // Fast pointer iterates through the array starting from position 2
    for (int fast = 2; fast < nums.size(); fast++) {
        // If current element is different from the element two positions back at slow
        // This ensures we allow at most 2 duplicates
        if (nums[fast] != nums[slow - 2]) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    return slow;
}

// Example 5: Move Zeroes
// LeetCode 283: https://leetcode.com/problems/move-zeroes/
void moveZeroes(vector<int>& nums) {
    // Position to place the next non-zero element
    int nonZeroPos = 0;
    
    // First pass: Move all non-zero elements to the front
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[nonZeroPos] = nums[i];
            nonZeroPos++;
        }
    }
    
    // Second pass: Fill the rest of the array with zeroes
    for (int i = nonZeroPos; i < nums.size(); i++) {
        nums[i] = 0;
    }
}

// Example 6: String Compression
// LeetCode 443: https://leetcode.com/problems/string-compression/
int compress(vector<char>& chars) {
    if (chars.empty()) return 0;
    
    int writePos = 0; // Position to write compressed characters
    int count = 1;    // Count of current character
    
    for (int readPos = 1; readPos <= chars.size(); readPos++) {
        // If we're at the end of the array or encounter a different character
        if (readPos == chars.size() || chars[readPos] != chars[readPos - 1]) {
            // Write the current character
            chars[writePos++] = chars[readPos - 1];
            
            // If count > 1, write the count as one or more digits
            if (count > 1) {
                // Convert count to string and write each digit
                string countStr = to_string(count);
                for (char digit : countStr) {
                    chars[writePos++] = digit;
                }
            }
            
            // Reset count for the next character
            count = 1;
        } else {
            // Same character, increment count
            count++;
        }
    }
    
    // Return the length of the compressed array
    return writePos;
}

// Example 7: Sort Array By Parity (even numbers first, then odd)
// LeetCode 905: https://leetcode.com/problems/sort-array-by-parity/
vector<int> sortArrayByParity(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        // If left is odd and right is even, swap them
        if (nums[left] % 2 == 1 && nums[right] % 2 == 0) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        } else {
            // If left is already even, move left pointer forward
            if (nums[left] % 2 == 0) {
                left++;
            }
            
            // If right is already odd, move right pointer backward
            if (nums[right] % 2 == 1) {
                right--;
            }
        }
    }
    
    return nums;
}

// Example 8: Move Pieces to Obtain a String (moves Ls left and Rs right)
// LeetCode 2337: https://leetcode.com/problems/move-pieces-to-obtain-a-string/
bool canChange(string start, string target) {
    int n = start.length();
    int i = 0, j = 0;
    
    while (i < n || j < n) {
        // Skip spaces in start
        while (i < n && start[i] == '_') i++;
        
        // Skip spaces in target
        while (j < n && target[j] == '_') j++;
        
        // If both pointers reach the end, we're done
        if (i == n && j == n) return true;
        
        // If only one pointer reaches the end, we can't match
        if (i == n || j == n) return false;
        
        // If characters don't match, we can't transform
        if (start[i] != target[j]) return false;
        
        // Check movement constraints: 
        // 'L' can only move left, so i should be >= j
        // 'R' can only move right, so i should be <= j
        if ((start[i] == 'L' && i < j) || (start[i] == 'R' && i > j)) return false;
        
        // Move to next characters
        i++;
        j++;
    }
    
    return true;
}

// Example 9: Separate Black and White Balls
// LeetCode 2938: https://leetcode.com/problems/separate-black-and-white-balls/
long long minimumSteps(string s) {
    int n = s.length();
    long long steps = 0;
    int zeros = 0; // Count of '0's encountered
    
    // Iterate from left to right
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            // For each '0', it needs to move past all '1's to its left
            // Which is the number of '1's we've seen so far
            steps += (i - zeros);
            zeros++; // Increment the count of '0's
        }
    }
    
    return steps;
}

// Utility function to print array
void printArray(const vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

// Utility function to print character array
void printCharArray(const vector<char>& chars) {
    for (char c : chars) {
        cout << c;
    }
    cout << endl;
}

// Main function to demonstrate the In-place Array Modification pattern
void demonstrateInplaceArrayModification() {
    cout << "Example 1: Remove Duplicates from Sorted Array" << endl;
    vector<int> nums1 = {1, 1, 2, 2, 3, 4, 4, 5};
    cout << "Original array: ";
    printArray(nums1);
    
    int newLength1 = removeDuplicates(nums1);
    cout << "After removing duplicates: ";
    for (int i = 0; i < newLength1; i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;
    cout << "New length: " << newLength1 << endl;
    
    cout << "\nExample 2: Remove Element" << endl;
    vector<int> nums2 = {3, 2, 2, 3, 4, 5, 3};
    int val = 3;
    cout << "Original array: ";
    printArray(nums2);
    
    int newLength2 = removeElement(nums2, val);
    cout << "After removing " << val << ": ";
    for (int i = 0; i < newLength2; i++) {
        cout << nums2[i] << " ";
    }
    cout << endl;
    cout << "New length: " << newLength2 << endl;
    
    cout << "\nExample 3: Sort Colors" << endl;
    vector<int> nums3 = {2, 0, 2, 1, 1, 0};
    cout << "Original array: ";
    printArray(nums3);
    
    sortColors(nums3);
    cout << "After sorting colors: ";
    printArray(nums3);
    
    cout << "\nExample 4: Remove Duplicates from Sorted Array II" << endl;
    vector<int> nums4 = {1, 1, 1, 2, 2, 3};
    cout << "Original array: ";
    printArray(nums4);
    
    int newLength4 = removeDuplicatesII(nums4);
    cout << "After removing extra duplicates: ";
    for (int i = 0; i < newLength4; i++) {
        cout << nums4[i] << " ";
    }
    cout << endl;
    cout << "New length: " << newLength4 << endl;
    
    cout << "\nExample 5: Move Zeroes" << endl;
    vector<int> nums5 = {0, 1, 0, 3, 12};
    cout << "Original array: ";
    printArray(nums5);
    
    moveZeroes(nums5);
    cout << "After moving zeroes: ";
    printArray(nums5);
    
    cout << "\nExample 6: String Compression" << endl;
    vector<char> chars = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
    cout << "Original character array: ";
    printCharArray(chars);
    
    int compressedLength = compress(chars);
    cout << "After compression: ";
    for (int i = 0; i < compressedLength; i++) {
        cout << chars[i];
    }
    cout << endl;
    cout << "Compressed length: " << compressedLength << endl;
    
    cout << "\nExample 7: Sort Array By Parity" << endl;
    vector<int> nums7 = {3, 1, 2, 4, 5, 6};
    cout << "Original array: ";
    printArray(nums7);
    
    sortArrayByParity(nums7);
    cout << "After sorting by parity: ";
    printArray(nums7);
    
    cout << "\nExample 8: Move Pieces to Obtain a String" << endl;
    string start = "_L__R__R_";
    string target = "L______RR";
    cout << "Start: " << start << endl;
    cout << "Target: " << target << endl;
    cout << "Can transform: " << (canChange(start, target) ? "Yes" : "No") << endl;
    
    cout << "\nExample 9: Separate Black and White Balls" << endl;
    string s = "10101";
    cout << "Original string: " << s << endl;
    cout << "Minimum steps to separate: " << minimumSteps(s) << endl;
}

int main() {
    // Demonstrate the In-place Array Modification pattern
    demonstrateInplaceArrayModification();
    
    return 0;
}
