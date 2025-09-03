/**
 * Pattern: Binary Search - Find Min/Max in Rotated Sorted Array
 * 
 * Description:
 * This pattern uses binary search to find the minimum or maximum element in a rotated sorted array.
 * A rotated sorted array is a sorted array that has been rotated at some pivot unknown to you beforehand.
 * For example, [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2] after rotation. The challenge is to
 * find specific elements or properties like the minimum value or a target element in such arrays.
 * 
 * Time Complexity: O(log n) where n is the length of the input array
 * Space Complexity: O(1) as we only need a few pointers
 * 
 * When to use:
 * - When dealing with a sorted array that has been rotated at some pivot
 * - When you need to find the minimum or maximum element in the rotated array
 * - When searching for a specific element in the rotated array
 * 
 * LeetCode Problems:
 * - 33. Search in Rotated Sorted Array
 * - 81. Search in Rotated Sorted Array II
 * - 153. Find Minimum in Rotated Sorted Array
 * - 154. Find Minimum in Rotated Sorted Array II
 * - 162. Find Peak Element
 * - 852. Peak Index in a Mountain Array
 * - 1095. Find in Mountain Array
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Example 1: Find Minimum in Rotated Sorted Array
// LeetCode 153: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
class FindMinimumInRotatedSortedArray {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        // If the array is not rotated
        if (nums[left] < nums[right]) {
            return nums[left];
        }
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than the rightmost element,
            // the minimum is in the right half
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // If mid element is less than or equal to the rightmost element,
            // the minimum is in the left half (including mid)
            else {
                right = mid;
            }
        }
        
        // At this point, left == right and points to the minimum element
        return nums[left];
    }
};

// Example 2: Find Minimum in Rotated Sorted Array II (with duplicates)
// LeetCode 154: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
class FindMinimumInRotatedSortedArrayII {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than the rightmost element,
            // the minimum is in the right half
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // If mid element is less than the rightmost element,
            // the minimum is in the left half (including mid)
            else if (nums[mid] < nums[right]) {
                right = mid;
            } 
            // If mid element is equal to the rightmost element,
            // we cannot determine which half to search, so we decrement right
            else {
                right--;
            }
        }
        
        // At this point, left == right and points to the minimum element
        return nums[left];
    }
};

// Example 3: Search in Rotated Sorted Array
// LeetCode 33: https://leetcode.com/problems/search-in-rotated-sorted-array/
class SearchInRotatedSortedArray {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;  // Target found
            }
            
            // Check if the left half is sorted
            if (nums[left] <= nums[mid]) {
                // Check if target is in the left half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;  // Search the left half
                } else {
                    left = mid + 1;  // Search the right half
                }
            } 
            // If the right half is sorted
            else {
                // Check if target is in the right half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // Search the right half
                } else {
                    right = mid - 1;  // Search the left half
                }
            }
        }
        
        return -1;  // Target not found
    }
};

// Example 4: Search in Rotated Sorted Array II (with duplicates)
// LeetCode 81: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
class SearchInRotatedSortedArrayII {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return true;  // Target found
            }
            
            // Handle duplicates at left and mid
            if (nums[left] == nums[mid]) {
                left++;  // Skip the duplicate and continue
                continue;
            }
            
            // Check if the left half is sorted
            if (nums[left] < nums[mid]) {
                // Check if target is in the left half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;  // Search the left half
                } else {
                    left = mid + 1;  // Search the right half
                }
            } 
            // If the right half is sorted
            else {
                // Check if target is in the right half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // Search the right half
                } else {
                    right = mid - 1;  // Search the left half
                }
            }
        }
        
        return false;  // Target not found
    }
};

// Example 5: Find Peak Element
// LeetCode 162: https://leetcode.com/problems/find-peak-element/
class FindPeakElement {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than the next element,
            // then mid might be a peak or a peak is in the left half
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } 
            // If mid element is less than the next element,
            // then a peak must be in the right half
            else {
                left = mid + 1;
            }
        }
        
        // At this point, left == right and points to a peak element
        return left;
    }
};

// Example 6: Peak Index in a Mountain Array
// LeetCode 852: https://leetcode.com/problems/peak-index-in-a-mountain-array/
class PeakIndexInMountainArray {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than the next element,
            // then mid might be the peak or the peak is in the left half
            if (arr[mid] > arr[mid + 1]) {
                right = mid;
            } 
            // If mid element is less than the next element,
            // then the peak is in the right half
            else {
                left = mid + 1;
            }
        }
        
        // At this point, left == right and points to the peak index
        return left;
    }
};

// Example 7: Find in Mountain Array
// LeetCode 1095: https://leetcode.com/problems/find-in-mountain-array/
// Interface provided by LeetCode:
class MountainArray {
public:
    int get(int index) const { return -1; }  // Placeholder method
    int length() const { return 0; }         // Placeholder method
};

class FindInMountainArray {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        
        // First, find the peak index
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;  // Peak is in the right half
            } else {
                right = mid;     // Peak is in the left half (including mid)
            }
        }
        
        int peakIndex = left;
        
        // Search in the increasing part of the array (left of the peak)
        int result = binarySearchIncreasing(mountainArr, target, 0, peakIndex);
        
        if (result != -1) {
            return result;  // Target found in the increasing part
        }
        
        // If not found in the increasing part, search in the decreasing part (right of the peak)
        return binarySearchDecreasing(mountainArr, target, peakIndex, n - 1);
    }

private:
    int binarySearchIncreasing(MountainArray &mountainArr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            
            if (midVal == target) {
                return mid;  // Target found
            } else if (midVal < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return -1;  // Target not found
    }
    
    int binarySearchDecreasing(MountainArray &mountainArr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            
            if (midVal == target) {
                return mid;  // Target found
            } else if (midVal > target) {
                left = mid + 1;  // Target is in the right half (since array is decreasing)
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return -1;  // Target not found
    }
};

// Example implementation for local testing
class MountainArrayImpl {
private:
    vector<int> arr;

public:
    MountainArrayImpl(vector<int> data) : arr(data) {}
    
    int get(int index) const {
        if (index < 0 || index >= arr.size()) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }
    
    int length() const {
        return arr.size();
    }
};

class FindInMountainArrayTesting {
public:
    int findInMountainArray(int target, const MountainArrayImpl &mountainArr) {
        int n = mountainArr.length();
        
        // First, find the peak index
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;  // Peak is in the right half
            } else {
                right = mid;     // Peak is in the left half (including mid)
            }
        }
        
        int peakIndex = left;
        
        // Search in the increasing part of the array (left of the peak)
        int result = binarySearchIncreasing(mountainArr, target, 0, peakIndex);
        
        if (result != -1) {
            return result;  // Target found in the increasing part
        }
        
        // If not found in the increasing part, search in the decreasing part (right of the peak)
        return binarySearchDecreasing(mountainArr, target, peakIndex, n - 1);
    }

private:
    int binarySearchIncreasing(const MountainArrayImpl &mountainArr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            
            if (midVal == target) {
                return mid;  // Target found
            } else if (midVal < target) {
                left = mid + 1;  // Target is in the right half
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return -1;  // Target not found
    }
    
    int binarySearchDecreasing(const MountainArrayImpl &mountainArr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midVal = mountainArr.get(mid);
            
            if (midVal == target) {
                return mid;  // Target found
            } else if (midVal > target) {
                left = mid + 1;  // Target is in the right half (since array is decreasing)
            } else {
                right = mid - 1;  // Target is in the left half
            }
        }
        
        return -1;  // Target not found
    }
};

// Main function to demonstrate Binary Search in Rotated Sorted Array pattern
int main() {
    // Example 1: Find Minimum in Rotated Sorted Array
    cout << "Example 1: Find Minimum in Rotated Sorted Array" << endl;
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    
    FindMinimumInRotatedSortedArray fmrsa;
    cout << "Array: [4, 5, 6, 7, 0, 1, 2]" << endl;
    int minValue = fmrsa.findMin(nums1);
    cout << "Minimum value: " << minValue << endl;
    
    // Example 2: Find Minimum in Rotated Sorted Array II (with duplicates)
    cout << "\nExample 2: Find Minimum in Rotated Sorted Array II (with duplicates)" << endl;
    vector<int> nums2 = {2, 2, 2, 0, 1};
    
    FindMinimumInRotatedSortedArrayII fmrsa2;
    cout << "Array: [2, 2, 2, 0, 1]" << endl;
    minValue = fmrsa2.findMin(nums2);
    cout << "Minimum value: " << minValue << endl;
    
    // Example 3: Search in Rotated Sorted Array
    cout << "\nExample 3: Search in Rotated Sorted Array" << endl;
    vector<int> nums3 = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    
    SearchInRotatedSortedArray srsa;
    cout << "Array: [4, 5, 6, 7, 0, 1, 2], Target: 0" << endl;
    int index = srsa.search(nums3, target);
    cout << "Index of target: " << index << endl;
    
    // Example 4: Search in Rotated Sorted Array II (with duplicates)
    cout << "\nExample 4: Search in Rotated Sorted Array II (with duplicates)" << endl;
    vector<int> nums4 = {2, 5, 6, 0, 0, 1, 2};
    target = 0;
    
    SearchInRotatedSortedArrayII srsa2;
    cout << "Array: [2, 5, 6, 0, 0, 1, 2], Target: 0" << endl;
    bool found = srsa2.search(nums4, target);
    cout << "Target found: " << (found ? "true" : "false") << endl;
    
    // Example 5: Find Peak Element
    cout << "\nExample 5: Find Peak Element" << endl;
    vector<int> nums5 = {1, 2, 3, 1};
    
    FindPeakElement fpe;
    cout << "Array: [1, 2, 3, 1]" << endl;
    int peakIndex = fpe.findPeakElement(nums5);
    cout << "Peak index: " << peakIndex << ", Peak value: " << nums5[peakIndex] << endl;
    
    // Example 6: Peak Index in a Mountain Array
    cout << "\nExample 6: Peak Index in a Mountain Array" << endl;
    vector<int> nums6 = {0, 1, 0};
    
    PeakIndexInMountainArray pima;
    cout << "Array: [0, 1, 0]" << endl;
    peakIndex = pima.peakIndexInMountainArray(nums6);
    cout << "Peak index: " << peakIndex << ", Peak value: " << nums6[peakIndex] << endl;
    
    // Example 7: Find in Mountain Array
    cout << "\nExample 7: Find in Mountain Array" << endl;
    vector<int> nums7 = {1, 2, 3, 4, 5, 3, 1};
    target = 3;
    
    MountainArrayImpl mountainArr(nums7);
    FindInMountainArrayTesting fima;
    
    cout << "Array: [1, 2, 3, 4, 5, 3, 1], Target: 3" << endl;
    int targetIndex = fima.findInMountainArray(target, mountainArr);
    cout << "Target found at index: " << targetIndex << endl;
    
    return 0;
}
