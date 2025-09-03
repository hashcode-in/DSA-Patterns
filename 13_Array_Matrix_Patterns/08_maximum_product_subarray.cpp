/**
 * Pattern: Array - Kadane's Variant for Maximum Product
 * 
 * Description:
 * This pattern extends Kadane's algorithm (used for maximum sum subarray) to find the
 * maximum product subarray. The key difference is that we need to track both maximum and
 * minimum products because a negative number can turn a minimum product into a maximum product
 * when multiplied by another negative number.
 * 
 * Time Complexity: O(n) where n is the size of the input array
 * Space Complexity: O(1) as we only use constant extra space
 * 
 * When to use:
 * - When you need to find a contiguous subarray with the largest product
 * - When the array contains both positive and negative numbers
 * - When you need to consider how negative numbers affect products
 * 
 * LeetCode Problem:
 * - 152. Maximum Product Subarray
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MaximumProductSubarray {
public:
    // Find the contiguous subarray with the largest product
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        int maxSoFar = nums[0];  // Maximum product so far
        int minSoFar = nums[0];  // Minimum product so far
        int result = nums[0];    // Final result (maximum product)
        
        for (int i = 1; i < n; i++) {
            // If current element is negative, swap max and min
            // This is because when we multiply a negative number with a negative,
            // a very negative number can become a large positive number
            if (nums[i] < 0) {
                swap(maxSoFar, minSoFar);
            }
            
            // Update max and min at current position
            maxSoFar = max(nums[i], maxSoFar * nums[i]);
            minSoFar = min(nums[i], minSoFar * nums[i]);
            
            // Update result if we found a larger product
            result = max(result, maxSoFar);
        }
        
        return result;
    }
    
    // Alternative approach (more explicit about keeping track of both max and min)
    int maxProductAlternative(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        int maxEndingHere = nums[0];
        int minEndingHere = nums[0];
        int maxSoFar = nums[0];
        
        for (int i = 1; i < n; i++) {
            // Store previous max and min because we need both for new calculations
            int prevMax = maxEndingHere;
            int prevMin = minEndingHere;
            
            // Update max product ending at current position
            // It can be either the current number itself, or the product with
            // the previous max or min (if the current number is negative)
            maxEndingHere = max({nums[i], prevMax * nums[i], prevMin * nums[i]});
            
            // Update min product ending at current position
            minEndingHere = min({nums[i], prevMax * nums[i], prevMin * nums[i]});
            
            // Update global max
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        
        return maxSoFar;
    }
    
    // Variation: Find the maximum product subarray and return the subarray itself
    vector<int> maxProductSubarray(vector<int>& nums) {
        if (nums.empty()) return {};
        
        int n = nums.size();
        int maxEndingHere = nums[0];
        int minEndingHere = nums[0];
        int maxSoFar = nums[0];
        
        // Track the start and end of the maximum product subarray
        int start = 0, end = 0;
        int tempStart = 0; // Temporary start for current potential max subarray
        
        for (int i = 1; i < n; i++) {
            int prevMax = maxEndingHere;
            int prevMin = minEndingHere;
            
            // Determine if we're starting a new subarray
            bool startNewSubarray = nums[i] > prevMax * nums[i] && nums[i] > prevMin * nums[i];
            if (startNewSubarray) {
                tempStart = i;
            }
            
            // Update max and min product ending here
            maxEndingHere = max({nums[i], prevMax * nums[i], prevMin * nums[i]});
            minEndingHere = min({nums[i], prevMax * nums[i], prevMin * nums[i]});
            
            // If we found a new maximum product, update the result subarray
            if (maxEndingHere > maxSoFar) {
                maxSoFar = maxEndingHere;
                start = tempStart;
                end = i;
            }
        }
        
        // Extract the maximum product subarray
        vector<int> result;
        for (int i = start; i <= end; i++) {
            result.push_back(nums[i]);
        }
        
        return result;
    }
    
    // Variation: Maximum product of a fixed size subarray
    int maxProductFixedSize(vector<int>& nums, int k) {
        if (nums.size() < k) return 0;
        
        int n = nums.size();
        int product = 1;
        int maxProduct = INT_MIN;
        
        // Calculate product of first k elements
        for (int i = 0; i < k; i++) {
            product *= nums[i];
        }
        maxProduct = product;
        
        // Use sliding window to find maximum product
        for (int i = k; i < n; i++) {
            // Remove the leftmost element from the window
            if (nums[i - k] != 0) {
                product /= nums[i - k];
            } else {
                // If we divided by zero, recalculate the entire product
                product = 1;
                for (int j = i - k + 1; j <= i; j++) {
                    product *= nums[j];
                }
            }
            
            // Add the new rightmost element to the window
            product *= nums[i];
            
            // Update maximum product if needed
            maxProduct = max(maxProduct, product);
        }
        
        return maxProduct;
    }
};

// Main function to demonstrate the maximum product subarray algorithm
int main() {
    MaximumProductSubarray solution;
    
    cout << "\n=== Maximum Product Subarray Examples ===\n\n";
    
    // Example 1: Basic example
    vector<int> nums1 = {2, 3, -2, 4};
    cout << "Array 1: ";
    for (int num : nums1) cout << num << " ";
    cout << "\nMaximum Product: " << solution.maxProduct(nums1);
    cout << "\nExpected Output: 6 (subarray [2, 3])\n\n";
    
    // Example 2: Array with negative numbers
    vector<int> nums2 = {-2, 0, -1};
    cout << "Array 2: ";
    for (int num : nums2) cout << num << " ";
    cout << "\nMaximum Product: " << solution.maxProduct(nums2);
    cout << "\nExpected Output: 0 (subarray [0])\n\n";
    
    // Example 3: Array with multiple negative numbers
    vector<int> nums3 = {-2, 3, -4};
    cout << "Array 3: ";
    for (int num : nums3) cout << num << " ";
    cout << "\nMaximum Product: " << solution.maxProduct(nums3);
    cout << "\nExpected Output: 24 (subarray [-2, 3, -4])\n\n";
    
    // Example 4: Finding the actual subarray
    vector<int> nums4 = {2, 3, -2, 4, -1, -3};
    cout << "Array 4: ";
    for (int num : nums4) cout << num << " ";
    
    vector<int> maxSubarray = solution.maxProductSubarray(nums4);
    cout << "\nMaximum Product Subarray: ";
    for (int num : maxSubarray) cout << num << " ";
    cout << "\n\n";
    
    // Example 5: Fixed size subarray
    vector<int> nums5 = {1, 2, 3, 4, 5};
    int k = 3;
    cout << "Array 5: ";
    for (int num : nums5) cout << num << " ";
    cout << "\nMaximum Product of " << k << "-sized Subarray: " << solution.maxProductFixedSize(nums5, k);
    cout << "\nExpected Output: 60 (subarray [3, 4, 5])\n\n";
    
    return 0;
}
