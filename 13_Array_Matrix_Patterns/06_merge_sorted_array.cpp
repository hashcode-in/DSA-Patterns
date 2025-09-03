/**
 * Pattern: Array - Merge Sorted Array (In-place from End)
 * 
 * Description:
 * This pattern focuses on merging two sorted arrays into one, with in-place
 * manipulation by starting from the end of the array to avoid overwriting
 * values that are still needed. The key insight is using a three-pointer
 * approach and working backward from the end of the arrays.
 * 
 * Time Complexity: O(m+n) where m and n are the sizes of the input arrays
 * Space Complexity: O(1) for the in-place solution
 * 
 * When to use:
 * - When merging sorted arrays or parts of arrays
 * - When you need to perform in-place array manipulations
 * - When you have constraints on extra space usage
 * 
 * LeetCode Problems:
 * - 88. Merge Sorted Array
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Example 1: Merge Sorted Array - Merge nums1 and nums2 into nums1 in sorted order
// LeetCode 88: https://leetcode.com/problems/merge-sorted-array/
class MergeSortedArray {
public:
    // Approach 1: Merge from the end (in-place)
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Initialize three pointers:
        // p1 points to the last element in nums1
        // p2 points to the last element in nums2
        // p points to the last position in the merged array
        int p1 = m - 1;
        int p2 = n - 1;
        int p = m + n - 1;
        
        // While there are elements in both arrays
        while (p1 >= 0 && p2 >= 0) {
            // Compare elements and place the larger one at the current position
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }
        
        // If there are remaining elements in nums2, copy them to nums1
        // (No need to check for remaining elements in nums1, as they're already in place)
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }
    
    // Approach 2: Using STL (not in-place, but simple)
    void mergeUsingSTL(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Copy elements from nums2 to the end of nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        
        // Sort the entire array
        sort(nums1.begin(), nums1.end());
    }
};

// Example 2: Merge Multiple Sorted Arrays
class MergeMultipleSortedArrays {
public:
    // Merge k sorted arrays into a single sorted array
    vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
        vector<int> result;
        
        // Concatenate all arrays
        for (const auto& arr : arrays) {
            result.insert(result.end(), arr.begin(), arr.end());
        }
        
        // Sort the combined array
        sort(result.begin(), result.end());
        
        return result;
    }
    
    // Alternative approach using min heap (more efficient)
    vector<int> mergeKSortedArraysHeap(const vector<vector<int>>& arrays) {
        vector<int> result;
        
        // Calculate total number of elements
        int totalSize = 0;
        for (const auto& arr : arrays) {
            totalSize += arr.size();
        }
        result.reserve(totalSize);
        
        // Create vectors of iterators for each array
        vector<pair<vector<int>::const_iterator, vector<int>::const_iterator>> iters;
        for (const auto& arr : arrays) {
            if (!arr.empty()) {
                iters.push_back({arr.begin(), arr.end()});
            }
        }
        
        // Merge arrays using a custom comparator
        auto comp = [](const pair<vector<int>::const_iterator, vector<int>::const_iterator>& a, 
                        const pair<vector<int>::const_iterator, vector<int>::const_iterator>& b) {
            return *a.first > *b.first; // Min heap
        };
        
        // Build min heap
        make_heap(iters.begin(), iters.end(), comp);
        
        // Extract minimum elements one by one
        while (!iters.empty()) {
            pop_heap(iters.begin(), iters.end(), comp);
            auto current = iters.back();
            iters.pop_back();
            
            // Add current minimum to result
            result.push_back(*current.first);
            
            // Move to next element in this array
            ++current.first;
            
            // If more elements in this array, push back to heap
            if (current.first != current.second) {
                iters.push_back(current);
                push_heap(iters.begin(), iters.end(), comp);
            }
        }
        
        return result;
    }
};

// Example 3: Merge Sorted Subarrays In-Place
class MergeSortedSubarrays {
public:
    // Merge two sorted subarrays within the same array
    void mergeSortedSubarrays(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1; // Size of left subarray
        int n2 = right - mid;    // Size of right subarray
        
        // Create temporary arrays
        vector<int> leftArr(n1);
        vector<int> rightArr(n2);
        
        // Copy data to temporary arrays
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            rightArr[i] = arr[mid + 1 + i];
        
        // Merge the temp arrays back into arr[left..right]
        int i = 0;      // Index for left subarray
        int j = 0;      // Index for right subarray
        int k = left;   // Index for merged array
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements of leftArr[]
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        // Copy remaining elements of rightArr[]
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    // Implement merge sort using the above function
    void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            // Same as (left + right) / 2, but avoids overflow
            int mid = left + (right - left) / 2;
            
            // Sort first and second halves
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            
            // Merge the sorted halves
            mergeSortedSubarrays(arr, left, mid, right);
        }
    }
};

// Example 4: Merge Two Sorted Lists into a New List (without modifying input)
class MergeToNewList {
public:
    // Merge two sorted arrays into a new array
    vector<int> mergeTwoSorted(const vector<int>& nums1, const vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        vector<int> result(m + n);
        
        int i = 0, j = 0, k = 0;
        
        // Compare elements from both arrays and add the smaller one to result
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                result[k++] = nums1[i++];
            } else {
                result[k++] = nums2[j++];
            }
        }
        
        // Copy remaining elements from nums1, if any
        while (i < m) {
            result[k++] = nums1[i++];
        }
        
        // Copy remaining elements from nums2, if any
        while (j < n) {
            result[k++] = nums2[j++];
        }
        
        return result;
    }
};

// Helper function to print a vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Merge Sorted Array pattern
int main() {
    // Example 1: Merge Sorted Array
    cout << "Example 1: Merge Sorted Array" << endl;
    
    vector<int> nums1 = {1, 2, 3, 0, 0, 0}; // First 3 elements are actual values, last 3 are placeholders
    vector<int> nums2 = {2, 5, 6};
    int m = 3; // Number of actual elements in nums1
    int n = 3; // Number of elements in nums2
    
    cout << "Original nums1: ";
    for (int i = 0; i < m; i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;
    
    cout << "Original nums2: ";
    printVector(nums2);
    
    MergeSortedArray solver1;
    solver1.merge(nums1, m, nums2, n);
    
    cout << "After merging: ";
    printVector(nums1);
    cout << endl;
    
    // Example 2: Merge Multiple Sorted Arrays
    cout << "Example 2: Merge Multiple Sorted Arrays" << endl;
    
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    
    cout << "Original arrays:" << endl;
    for (const auto& arr : arrays) {
        printVector(arr);
    }
    
    MergeMultipleSortedArrays solver2;
    vector<int> resultMultiple = solver2.mergeKSortedArrays(arrays);
    
    cout << "After merging multiple arrays: ";
    printVector(resultMultiple);
    cout << endl;
    
    // Example 3: Merge Sorted Subarrays In-Place
    cout << "Example 3: Merge Sorted Subarrays In-Place (Merge Sort)" << endl;
    
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Original array: ";
    printVector(arr);
    
    MergeSortedSubarrays solver3;
    solver3.mergeSort(arr, 0, arr.size() - 1);
    
    cout << "Sorted array: ";
    printVector(arr);
    cout << endl;
    
    // Example 4: Merge Two Sorted Lists into a New List
    cout << "Example 4: Merge Two Sorted Lists into a New List" << endl;
    
    vector<int> vec1 = {1, 3, 5, 7, 9};
    vector<int> vec2 = {2, 4, 6, 8, 10};
    
    cout << "First sorted list: ";
    printVector(vec1);
    
    cout << "Second sorted list: ";
    printVector(vec2);
    
    MergeToNewList solver4;
    vector<int> mergedNew = solver4.mergeTwoSorted(vec1, vec2);
    
    cout << "Merged into new list: ";
    printVector(mergedNew);
    
    return 0;
}
