/**
 * Pattern: Binary Search - Median of Two Sorted Arrays
 * 
 * Description:
 * This pattern involves finding the median of two sorted arrays without merging them.
 * It's one of the most challenging binary search problems and requires a deep understanding
 * of partitioning and the properties of medians. The key insight is to partition both arrays
 * such that the left half of the combined arrays contains exactly (n1 + n2) / 2 elements.
 * 
 * Time Complexity: O(log(min(n1, n2))) where n1 and n2 are the lengths of the input arrays
 * Space Complexity: O(1) as we only need a few variables
 * 
 * When to use:
 * - When you need to find the median or k-th element of two sorted arrays
 * - When you need to solve problems involving partitioning of sorted arrays
 * - When a problem requires efficient merging of sorted arrays without actually merging them
 * 
 * LeetCode Problems:
 * - 4. Median of Two Sorted Arrays
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // For INT_MAX and INT_MIN

using namespace std;

// Example 1: Median of Two Sorted Arrays
// LeetCode 4: https://leetcode.com/problems/median-of-two-sorted-arrays/
class MedianOfTwoSortedArrays {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array for efficiency
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0;
        int high = n1;
        
        while (low <= high) {
            // Partition nums1 and nums2
            int partitionX = (low + high) / 2;
            int partitionY = (n1 + n2 + 1) / 2 - partitionX;
            
            // Get the four boundary elements
            int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minX = (partitionX == n1) ? INT_MAX : nums1[partitionX];
            
            int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minY = (partitionY == n2) ? INT_MAX : nums2[partitionY];
            
            // Check if the partitions are correct
            if (maxX <= minY && maxY <= minX) {
                // Found the correct partitions
                
                // If total number of elements is odd
                if ((n1 + n2) % 2 != 0) {
                    return max(maxX, maxY);
                }
                
                // If total number of elements is even
                return (max(maxX, maxY) + min(minX, minY)) / 2.0;
            } else if (maxX > minY) {
                // Move partition of nums1 to the left
                high = partitionX - 1;
            } else {
                // Move partition of nums1 to the right
                low = partitionX + 1;
            }
        }
        
        // Should never reach here if the input arrays are sorted
        return 0.0;
    }
};

// Example 2: Alternative Approach - Kth Element of Two Sorted Arrays
// This is a more general approach that can be used to find the k-th element of two sorted arrays
class KthElementOfTwoSortedArrays {
public:
    double findKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        
        // Ensure nums1 is the smaller array for efficiency
        if (n1 > n2) {
            return findKthElement(nums2, nums1, k);
        }
        
        // Edge cases: if one array is empty
        if (n1 == 0) {
            return nums2[k - 1];
        }
        
        // Base case: k = 1, return the minimum of the first elements
        if (k == 1) {
            return min(nums1[0], nums2[0]);
        }
        
        // Divide k into two parts
        int i = min(n1, k / 2);
        int j = min(n2, k / 2);
        
        // If nums1[i-1] > nums2[j-1], then nums2[0...j-1] must be in the first k elements
        if (nums1[i - 1] > nums2[j - 1]) {
            // Discard nums2[0...j-1]
            vector<int> newNums2(nums2.begin() + j, nums2.end());
            return findKthElement(nums1, newNums2, k - j);
        } else {
            // Discard nums1[0...i-1]
            vector<int> newNums1(nums1.begin() + i, nums1.end());
            return findKthElement(newNums1, nums2, k - i);
        }
    }
    
    // Find the median using the k-th element approach
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        
        if (totalLength % 2 == 1) {
            // Odd number of elements, return the middle one
            return findKthElement(nums1, nums2, (totalLength + 1) / 2);
        } else {
            // Even number of elements, return the average of the two middle ones
            return (findKthElement(nums1, nums2, totalLength / 2) +
                    findKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};

// Example 3: Optimized approach for finding the k-th element without creating new vectors
class OptimizedKthElement {
public:
    int findKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        
        int i = 0;  // Index for nums1
        int j = 0;  // Index for nums2
        
        // Skip k-1 elements
        while (i < n1 && j < n2 && k > 1) {
            int halfK = k / 2;
            int newI = min(i + halfK, n1) - 1;
            int newJ = min(j + halfK, n2) - 1;
            
            if (nums1[newI] <= nums2[newJ]) {
                k -= (newI - i + 1);
                i = newI + 1;
            } else {
                k -= (newJ - j + 1);
                j = newJ + 1;
            }
        }
        
        // If one array is exhausted, return the k-th element from the other array
        if (i >= n1) {
            return nums2[j + k - 1];
        }
        
        if (j >= n2) {
            return nums1[i + k - 1];
        }
        
        // If k = 1, return the smaller of the current elements
        return min(nums1[i], nums2[j]);
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        
        if (totalLength % 2 == 1) {
            // Odd number of elements, return the middle one
            return findKthElement(nums1, nums2, (totalLength + 1) / 2);
        } else {
            // Even number of elements, return the average of the two middle ones
            return (findKthElement(nums1, nums2, totalLength / 2) +
                    findKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};

// Main function to demonstrate Binary Search Median of Two Sorted Arrays pattern
int main() {
    // Example 1: Median of Two Sorted Arrays
    cout << "Example 1: Median of Two Sorted Arrays" << endl;
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    
    MedianOfTwoSortedArrays motsa;
    cout << "Array 1: [1, 3], Array 2: [2]" << endl;
    double median1 = motsa.findMedianSortedArrays(nums1, nums2);
    cout << "Median: " << median1 << endl;
    
    // Try with arrays of even combined length
    nums1 = {1, 2};
    nums2 = {3, 4};
    
    cout << "\nArray 1: [1, 2], Array 2: [3, 4]" << endl;
    double median2 = motsa.findMedianSortedArrays(nums1, nums2);
    cout << "Median: " << median2 << endl;
    
    // Example 2: Using the Kth Element approach
    cout << "\nExample 2: Using the Kth Element Approach" << endl;
    nums1 = {1, 3, 8, 9, 15};
    nums2 = {7, 11, 18, 19, 21, 25};
    
    KthElementOfTwoSortedArrays keotsa;
    cout << "Array 1: [1, 3, 8, 9, 15], Array 2: [7, 11, 18, 19, 21, 25]" << endl;
    double median3 = keotsa.findMedianSortedArrays(nums1, nums2);
    cout << "Median: " << median3 << endl;
    
    // Example 3: Using the Optimized Kth Element approach
    cout << "\nExample 3: Using the Optimized Kth Element Approach" << endl;
    nums1 = {23, 26, 31, 35};
    nums2 = {3, 5, 7, 9, 11, 16};
    
    OptimizedKthElement oke;
    cout << "Array 1: [23, 26, 31, 35], Array 2: [3, 5, 7, 9, 11, 16]" << endl;
    double median4 = oke.findMedianSortedArrays(nums1, nums2);
    cout << "Median: " << median4 << endl;
    
    return 0;
}
