/**
 * Pattern: Binary Search - Find First/Last Occurrence
 * 
 * Description:
 * This pattern uses binary search to find the first or last occurrence of a target element
 * in a sorted array. It's particularly useful when the array contains duplicate elements,
 * and we need to know the boundaries of where a specific element appears.
 * 
 * Time Complexity: O(log n) where n is the length of the input array
 * Space Complexity: O(1) as we only need a few pointers
 * 
 * When to use:
 * - When dealing with a sorted array that may contain duplicates
 * - When you need to find the first or last occurrence of a specific element
 * - When you need to find the range (start and end positions) of a specific element
 * 
 * LeetCode Problems:
 * - 34. Find First and Last Position of Element in Sorted Array
 * - 658. Find K Closest Elements
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // For INT_MAX

using namespace std;

// Example 1: Find First and Last Position of Element in Sorted Array
// LeetCode 34: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
class FindFirstLastPositions {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result = {-1, -1};
        
        if (nums.empty()) {
            return result;
        }
        
        // Find the first occurrence
        result[0] = findFirstOccurrence(nums, target);
        
        // If target doesn't exist in the array, return {-1, -1}
        if (result[0] == -1) {
            return result;
        }
        
        // Find the last occurrence
        result[1] = findLastOccurrence(nums, target);
        
        return result;
    }
    
private:
    // Helper function to find the first occurrence of target
    int findFirstOccurrence(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                result = mid;  // Update result and continue searching in the left half
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return result;
    }
    
    // Helper function to find the last occurrence of target
    int findLastOccurrence(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                result = mid;  // Update result and continue searching in the right half
                left = mid + 1;
            } else if (nums[mid] < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return result;
    }
};

// Example 2: Find K Closest Elements
// LeetCode 658: https://leetcode.com/problems/find-k-closest-elements/
class FindKClosestElements {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // If x is less than or equal to the smallest element,
        // return the first k elements
        if (x <= arr[0]) {
            return vector<int>(arr.begin(), arr.begin() + k);
        }
        
        // If x is greater than or equal to the largest element,
        // return the last k elements
        if (x >= arr[arr.size() - 1]) {
            return vector<int>(arr.end() - k, arr.end());
        }
        
        // Find the position where x would be inserted
        int left = 0;
        int right = arr.size() - k;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Compare the distance between x and arr[mid] with the distance between x and arr[mid+k]
            if (x - arr[mid] > arr[mid + k] - x) {
                // The k elements starting from mid+1 are closer to x
                left = mid + 1;
            } else {
                // The k elements starting from mid are closer to x
                right = mid;
            }
        }
        
        // Return the k elements starting from the left index
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
    
    // Alternative approach with binary search to find the closest element and expanding outward
    vector<int> findClosestElementsAlt(vector<int>& arr, int k, int x) {
        // Find the index of the closest element to x
        int closestIdx = findClosestElement(arr, x);
        
        // Use two pointers to expand from closestIdx
        int left = closestIdx;
        int right = closestIdx + 1;
        int count = 0;
        
        // Expand from the closest element by comparing elements on both sides
        while (count < k) {
            if (left < 0) {
                right++;  // No more elements on the left, move right
            } else if (right >= arr.size()) {
                left--;   // No more elements on the right, move left
            } else {
                // Compare distances and choose the closer element
                if (x - arr[left] <= arr[right] - x) {
                    left--;  // Left element is closer or equidistant, include it
                } else {
                    right++;  // Right element is closer, include it
                }
            }
            count++;
        }
        
        // Return the k elements within the range [left+1, right-1]
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
    
private:
    // Helper function to find the index of the element closest to x
    int findClosestElement(vector<int>& arr, int x) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == x) {
                return mid;  // Found exact match
            } else if (arr[mid] < x) {
                left = mid;  // Target is in the right half
            } else {
                right = mid;  // Target is in the left half
            }
        }
        
        // Choose the closer of left and right
        return abs(arr[left] - x) <= abs(arr[right] - x) ? left : right;
    }
};

// Example 3: An extension - Find the lower bound (first element >= target)
class LowerBound {
public:
    int findLowerBound(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid;     // Target is in the left half (including mid)
            }
        }
        
        // left points to the first element >= target,
        // or nums.size() if no such element exists
        return left < nums.size() ? left : -1;
    }
};

// Example 4: An extension - Find the upper bound (first element > target)
class UpperBound {
public:
    int findUpperBound(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] <= target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid;     // Target is in the left half (including mid)
            }
        }
        
        // left points to the first element > target,
        // or nums.size() if no such element exists
        return left < nums.size() ? left : -1;
    }
};

// Main function to demonstrate Binary Search Find First/Last Occurrence pattern
int main() {
    // Example 1: Find First and Last Position of Element in Sorted Array
    cout << "Example 1: Find First and Last Position of Element in Sorted Array" << endl;
    vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    int target1 = 8;
    
    FindFirstLastPositions fflp;
    cout << "Array: [5, 7, 7, 8, 8, 10], Target: 8" << endl;
    vector<int> range1 = fflp.searchRange(nums1, target1);
    cout << "First and last positions: [" << range1[0] << ", " << range1[1] << "]" << endl;
    
    // Try with a target that doesn't exist in the array
    target1 = 6;
    cout << "Array: [5, 7, 7, 8, 8, 10], Target: 6" << endl;
    range1 = fflp.searchRange(nums1, target1);
    cout << "First and last positions: [" << range1[0] << ", " << range1[1] << "]" << endl;
    
    // Example 2: Find K Closest Elements
    cout << "\nExample 2: Find K Closest Elements" << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 4;
    int x = 3;
    
    FindKClosestElements fkce;
    cout << "Array: [1, 2, 3, 4, 5], k = 4, x = 3" << endl;
    vector<int> closest = fkce.findClosestElements(arr, k, x);
    cout << "K closest elements: [";
    for (int i = 0; i < closest.size(); i++) {
        cout << closest[i];
        if (i < closest.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    
    // Try with a different array and parameters
    arr = {1, 2, 3, 4, 5};
    k = 4;
    x = -1;
    
    cout << "Array: [1, 2, 3, 4, 5], k = 4, x = -1" << endl;
    closest = fkce.findClosestElements(arr, k, x);
    cout << "K closest elements: [";
    for (int i = 0; i < closest.size(); i++) {
        cout << closest[i];
        if (i < closest.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    
    // Example 3: Find Lower Bound
    cout << "\nExample 3: Find Lower Bound (first element >= target)" << endl;
    vector<int> nums3 = {1, 3, 5, 6};
    int target3 = 5;
    
    LowerBound lb;
    cout << "Array: [1, 3, 5, 6], Target: 5" << endl;
    int lbIndex = lb.findLowerBound(nums3, target3);
    cout << "Lower bound index: " << lbIndex << ", Value: " << nums3[lbIndex] << endl;
    
    // Example 4: Find Upper Bound
    cout << "\nExample 4: Find Upper Bound (first element > target)" << endl;
    vector<int> nums4 = {1, 3, 5, 5, 6};
    int target4 = 5;
    
    UpperBound ub;
    cout << "Array: [1, 3, 5, 5, 6], Target: 5" << endl;
    int ubIndex = ub.findUpperBound(nums4, target4);
    cout << "Upper bound index: " << ubIndex << ", Value: " << nums4[ubIndex] << endl;
    
    return 0;
}
