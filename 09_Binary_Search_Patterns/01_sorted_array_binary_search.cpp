/**
 * Pattern: Binary Search - On Sorted Array/List
 * 
 * Description:
 * Binary search is an efficient algorithm for finding a target value within a sorted array.
 * It works by repeatedly dividing the search interval in half, making it O(log n) time complexity.
 * The basic idea is to compare the target value with the middle element of the array,
 * then narrow down the search to the left or right half accordingly.
 * 
 * Time Complexity: O(log n) where n is the length of the input array
 * Space Complexity: O(1) for iterative approach, O(log n) for recursive approach
 * 
 * When to use:
 * - When the data is sorted
 * - When you need to efficiently search for an element
 * - When you need to find insertion position
 * - When you want to check if an element exists in the collection
 * 
 * LeetCode Problems:
 * - 35. Search Insert Position
 * - 69. Sqrt(x)
 * - 74. Search a 2D Matrix
 * - 278. First Bad Version
 * - 374. Guess Number Higher or Lower
 * - 540. Single Element in a Sorted Array
 * - 704. Binary Search
 * - 1539. Kth Missing Positive Number
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Example 1: Standard Binary Search
// LeetCode 704: https://leetcode.com/problems/binary-search/
class StandardBinarySearch {
public:
    // Iterative approach
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;  // Avoid potential integer overflow
            
            if (nums[mid] == target) {
                return mid;  // Target found
            } else if (nums[mid] < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return -1;  // Target not found
    }
    
    // Recursive approach
    int searchRecursive(vector<int>& nums, int target) {
        return binarySearchHelper(nums, target, 0, nums.size() - 1);
    }
    
private:
    int binarySearchHelper(vector<int>& nums, int target, int left, int right) {
        if (left > right) {
            return -1;  // Base case: target not found
        }
        
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;  // Target found
        } else if (nums[mid] < target) {
            return binarySearchHelper(nums, target, mid + 1, right);  // Search right half
        } else {
            return binarySearchHelper(nums, target, left, mid - 1);  // Search left half
        }
    }
};

// Example 2: Search Insert Position
// LeetCode 35: https://leetcode.com/problems/search-insert-position/
class SearchInsertPosition {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;  // Target found
            } else if (nums[mid] < target) {
                left = mid + 1;  // Target should be inserted to the right
            } else {
                right = mid - 1;  // Target should be inserted to the left
            }
        }
        
        return left;  // Return the insertion position
    }
    
    // Alternative approach using lower_bound
    int searchInsertSTL(vector<int>& nums, int target) {
        auto it = lower_bound(nums.begin(), nums.end(), target);
        return distance(nums.begin(), it);
    }
};

// Example 3: Sqrt(x)
// LeetCode 69: https://leetcode.com/problems/sqrtx/
class Sqrt {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        
        int left = 1;
        int right = x;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Be careful of integer overflow when calculating mid * mid
            if (mid <= x / mid) {
                // mid * mid <= x, valid candidate for sqrt
                result = mid;
                left = mid + 1;  // Try to find a larger valid value
            } else {
                right = mid - 1;  // mid is too large
            }
        }
        
        return result;
    }
    
    // Alternative approach using Newton's method
    int mySqrtNewton(int x) {
        if (x == 0) {
            return 0;
        }
        
        double guess = x;
        double epsilon = 1e-9;  // Desired precision
        
        while (abs(guess * guess - x) > epsilon) {
            guess = (guess + x / guess) / 2.0;
        }
        
        return static_cast<int>(guess);
    }
};

// Example 4: Search in a 2D Matrix
// LeetCode 74: https://leetcode.com/problems/search-a-2d-matrix/
class Search2DMatrix {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        // Treat the 2D matrix as a 1D sorted array
        int left = 0;
        int right = m * n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Convert the 1D index back to 2D coordinates
            int row = mid / n;
            int col = mid % n;
            
            if (matrix[row][col] == target) {
                return true;  // Target found
            } else if (matrix[row][col] < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return false;  // Target not found
    }
    
    // Alternative approach: First find the row, then search within the row
    bool searchMatrixTwoStage(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        // First find the potential row
        int top = 0;
        int bottom = m - 1;
        int row = -1;
        
        while (top <= bottom) {
            int mid = top + (bottom - top) / 2;
            
            if (matrix[mid][0] <= target && target <= matrix[mid][n - 1]) {
                row = mid;
                break;
            } else if (matrix[mid][0] > target) {
                bottom = mid - 1;
            } else {
                top = mid + 1;
            }
        }
        
        if (row == -1) {
            return false;  // Target is not in any row
        }
        
        // Then search within the row
        int left = 0;
        int right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (matrix[row][mid] == target) {
                return true;  // Target found
            } else if (matrix[row][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;  // Target not found in the row
    }
};

// Example 5: First Bad Version
// LeetCode 278: https://leetcode.com/problems/first-bad-version/
// API provided by LeetCode:
bool isBadVersion(int version); // Placeholder function

class FirstBadVersion {
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (isBadVersion(mid)) {
                right = mid;  // The first bad version is either mid or before
            } else {
                left = mid + 1;  // The first bad version is after mid
            }
        }
        
        return left;  // left == right is the first bad version
    }
    
    // Implementation for local testing
    bool isBadVersionForTesting(int version, int badVersion) {
        return version >= badVersion;
    }
    
    int firstBadVersionForTesting(int n, int badVersion) {
        int left = 1;
        int right = n;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (isBadVersionForTesting(mid, badVersion)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};

// Example 6: Guess Number Higher or Lower
// LeetCode 374: https://leetcode.com/problems/guess-number-higher-or-lower/
// API provided by LeetCode:
int guess(int num); // Placeholder function

class GuessGame {
public:
    int guessNumber(int n) {
        int left = 1;
        int right = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int result = guess(mid);
            
            if (result == 0) {
                return mid;  // Correct guess
            } else if (result == -1) {
                right = mid - 1;  // Target is lower
            } else {
                left = mid + 1;  // Target is higher
            }
        }
        
        return -1;  // This should never happen according to the problem
    }
    
    // Implementation for local testing
    int guessForTesting(int num, int target) {
        if (num == target) {
            return 0;  // Correct
        } else if (num > target) {
            return -1;  // Too high
        } else {
            return 1;  // Too low
        }
    }
    
    int guessNumberForTesting(int n, int target) {
        int left = 1;
        int right = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int result = guessForTesting(mid, target);
            
            if (result == 0) {
                return mid;
            } else if (result == -1) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return -1;
    }
};

// Example 7: Single Element in a Sorted Array
// LeetCode 540: https://leetcode.com/problems/single-element-in-a-sorted-array/
class SingleElementInSortedArray {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Make sure mid is even by adjusting it if necessary
            if (mid % 2 == 1) {
                mid--;
            }
            
            // Check if the pair at mid, mid+1 is intact
            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2;  // The single element is on the right side
            } else {
                right = mid;  // The single element is on the left side or is mid itself
            }
        }
        
        return nums[left];  // left == right is the single element
    }
    
    // Alternative approach using XOR properties
    int singleNonDuplicateXOR(vector<int>& nums) {
        int result = 0;
        
        for (int num : nums) {
            result ^= num;  // XOR cancels out pairs, leaving only the single element
        }
        
        return result;
    }
};

// Example 8: Kth Missing Positive Number
// LeetCode 1539: https://leetcode.com/problems/kth-missing-positive-number/
class KthMissingPositiveNumber {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Calculate how many numbers are missing before arr[mid]
            int missing = arr[mid] - (mid + 1);
            
            if (missing < k) {
                left = mid + 1;  // Need to find more missing numbers
            } else {
                right = mid - 1;  // Too many missing numbers, go left
            }
        }
        
        // At this point, right is the index before the kth missing number
        // The kth missing number is (right + 1) + (k - missing before arr[right])
        // Simplifies to: right + 1 + k - (arr[right] - (right + 1)) = k + 2*right + 2 - arr[right]
        
        // Since we need to handle the case where right = -1 (all numbers are missing more than k)
        // We use the formula: k + left (left = right + 1)
        return k + left;
    }
    
    // Alternative approach: Linear search
    int findKthPositiveLinear(vector<int>& arr, int k) {
        int expected = 1;
        int i = 0;
        int missing = 0;
        
        while (missing < k) {
            if (i < arr.size() && arr[i] == expected) {
                i++;  // Current number exists in the array
            } else {
                missing++;  // Current number is missing
                if (missing == k) {
                    return expected;
                }
            }
            expected++;
        }
        
        return -1;  // This should never happen according to the problem
    }
};

// Main function to demonstrate Binary Search on Sorted Array pattern
int main() {
    // Example 1: Standard Binary Search
    cout << "Example 1: Standard Binary Search" << endl;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    
    StandardBinarySearch sbs;
    cout << "Array: [-1, 0, 3, 5, 9, 12], Target: 9" << endl;
    int index = sbs.search(nums, target);
    cout << "Index of target (iterative): " << index << endl;
    
    index = sbs.searchRecursive(nums, target);
    cout << "Index of target (recursive): " << index << endl;
    
    // Example 2: Search Insert Position
    cout << "\nExample 2: Search Insert Position" << endl;
    vector<int> nums2 = {1, 3, 5, 6};
    target = 5;
    
    SearchInsertPosition sip;
    cout << "Array: [1, 3, 5, 6], Target: 5" << endl;
    int insertPos = sip.searchInsert(nums2, target);
    cout << "Insert position: " << insertPos << endl;
    
    target = 2;
    cout << "Array: [1, 3, 5, 6], Target: 2" << endl;
    insertPos = sip.searchInsert(nums2, target);
    cout << "Insert position: " << insertPos << endl;
    
    // Example 3: Sqrt(x)
    cout << "\nExample 3: Sqrt(x)" << endl;
    int x = 8;
    
    Sqrt sqrt;
    cout << "x = 8" << endl;
    int sqrtResult = sqrt.mySqrt(x);
    cout << "Square root: " << sqrtResult << endl;
    
    // Example 4: Search in a 2D Matrix
    cout << "\nExample 4: Search in a 2D Matrix" << endl;
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    target = 3;
    
    Search2DMatrix s2d;
    cout << "Matrix: [1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60], Target: 3" << endl;
    bool found = s2d.searchMatrix(matrix, target);
    cout << "Target found: " << (found ? "true" : "false") << endl;
    
    // Example 5: First Bad Version
    cout << "\nExample 5: First Bad Version" << endl;
    int n = 10;
    int badVersion = 4;
    
    FirstBadVersion fbv;
    cout << "n = 10, First bad version is 4" << endl;
    int firstBad = fbv.firstBadVersionForTesting(n, badVersion);
    cout << "First bad version found: " << firstBad << endl;
    
    // Example 6: Guess Number Higher or Lower
    cout << "\nExample 6: Guess Number Higher or Lower" << endl;
    n = 10;
    int pick = 6;
    
    GuessGame gg;
    cout << "n = 10, pick = 6" << endl;
    int guessResult = gg.guessNumberForTesting(n, pick);
    cout << "Guess result: " << guessResult << endl;
    
    // Example 7: Single Element in a Sorted Array
    cout << "\nExample 7: Single Element in a Sorted Array" << endl;
    vector<int> nums3 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    
    SingleElementInSortedArray seisa;
    cout << "Array: [1, 1, 2, 3, 3, 4, 4, 8, 8]" << endl;
    int singleElement = seisa.singleNonDuplicate(nums3);
    cout << "Single element: " << singleElement << endl;
    
    // Example 8: Kth Missing Positive Number
    cout << "\nExample 8: Kth Missing Positive Number" << endl;
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;
    
    KthMissingPositiveNumber kmpn;
    cout << "Array: [2, 3, 4, 7, 11], k = 5" << endl;
    int kthMissing = kmpn.findKthPositive(arr, k);
    cout << "Kth missing positive number: " << kthMissing << endl;
    
    return 0;
}
