/**
 * Pattern: Array - Product Except Self (Prefix/Suffix Products)
 * 
 * Description:
 * This pattern focuses on calculating the product of all array elements except the current element.
 * The key insight is using prefix and suffix products to avoid division operation and achieve O(n) time
 * complexity with O(1) extra space (apart from the output array).
 * 
 * Time Complexity: O(n) where n is the size of the input array
 * Space Complexity: O(1) excluding the output array
 * 
 * When to use:
 * - When you need to compute products of all elements except self
 * - When division operation is not allowed or may cause precision issues
 * - When you need to handle arrays that may contain zeros
 * 
 * LeetCode Problems:
 * - 238. Product of Array Except Self
 */

#include <iostream>
#include <vector>
#include <algorithm> // For sort function
#include <climits>   // For INT_MIN, INT_MAX constants

using namespace std;

// Example 1: Product of Array Except Self
// LeetCode 238: https://leetcode.com/problems/product-of-array-except-self/
class ProductExceptSelf {
public:
    // Approach 1: Using O(n) extra space for prefix and suffix arrays
    vector<int> productExceptSelfExtraSpace(vector<int>& nums) {
        int n = nums.size();
        
        // Edge case: empty array
        if (n == 0) return {};
        
        // Initialize prefix and suffix product arrays
        vector<int> prefix(n);
        vector<int> suffix(n);
        vector<int> result(n);
        
        // Calculate prefix products
        prefix[0] = 1; // prefix product before first element is 1
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i-1] * nums[i-1];
        }
        
        // Calculate suffix products
        suffix[n-1] = 1; // suffix product after last element is 1
        for (int i = n-2; i >= 0; i--) {
            suffix[i] = suffix[i+1] * nums[i+1];
        }
        
        // Combine prefix and suffix to get the result
        for (int i = 0; i < n; i++) {
            result[i] = prefix[i] * suffix[i];
        }
        
        return result;
    }
    
    // Approach 2: Using O(1) extra space (excluding the output array)
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        
        // Edge case: empty array
        if (n == 0) return {};
        
        vector<int> result(n);
        
        // First pass: Calculate prefix products and store in result
        result[0] = 1; // prefix product before first element is 1
        for (int i = 1; i < n; i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        
        // Second pass: Multiply by suffix products
        int suffixProduct = 1; // Initialize suffix product
        for (int i = n-1; i >= 0; i--) {
            result[i] *= suffixProduct; // Multiply with suffix product
            suffixProduct *= nums[i]; // Update suffix product for next iteration
        }
        
        return result;
    }
};

// Example 2: Variation - Product of All Numbers Except Self and Handle Zeros
class ProductExceptSelfWithZeros {
public:
    // Handle the case when array may contain zeros
    vector<int> productExceptSelfWithZero(vector<int>& nums) {
        int n = nums.size();
        
        // Edge case: empty array
        if (n == 0) return {};
        
        vector<int> result(n, 0); // Initialize all to 0
        
        // Count zeros and calculate product of non-zero elements
        int zeroCount = 0;
        int productNonZero = 1;
        
        for (int num : nums) {
            if (num == 0) {
                zeroCount++;
            } else {
                productNonZero *= num;
            }
        }
        
        // Case 1: More than one zero
        if (zeroCount > 1) {
            // All products will be 0
            return result;
        }
        
        // Case 2: Exactly one zero
        if (zeroCount == 1) {
            for (int i = 0; i < n; i++) {
                if (nums[i] == 0) {
                    // Only this position will have non-zero product
                    result[i] = productNonZero;
                }
            }
            return result;
        }
        
        // Case 3: No zeros
        for (int i = 0; i < n; i++) {
            result[i] = productNonZero / nums[i];
        }
        
        return result;
    }
};

// Example 3: Variation - Maximum Product of Three Numbers
class MaximumProductOfThree {
public:
    // Find the maximum product of three numbers in the array
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        
        // Sort the array
        sort(nums.begin(), nums.end());
        
        // Two possible cases:
        // 1. Three largest numbers (all positive or all negative)
        // 2. Two smallest numbers (negative) and the largest number (positive)
        
        int option1 = nums[n-1] * nums[n-2] * nums[n-3];
        int option2 = nums[0] * nums[1] * nums[n-1];
        
        return max(option1, option2);
    }
    
    // Alternative approach without sorting (O(n) time)
    int maximumProductLinear(vector<int>& nums) {
        // Find the three largest and two smallest numbers
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        int min1 = INT_MAX, min2 = INT_MAX;
        
        for (int num : nums) {
            // Update the three largest numbers
            if (num > max1) {
                max3 = max2;
                max2 = max1;
                max1 = num;
            } else if (num > max2) {
                max3 = max2;
                max2 = num;
            } else if (num > max3) {
                max3 = num;
            }
            
            // Update the two smallest numbers
            if (num < min1) {
                min2 = min1;
                min1 = num;
            } else if (num < min2) {
                min2 = num;
            }
        }
        
        return max(max1 * max2 * max3, min1 * min2 * max1);
    }
};

// Example 4: Variation - Continuous Product Subarray
class ContinuousProductSubarray {
public:
    // Find the maximum product subarray
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // Initialize variables to track max and min product so far
        int maxSoFar = nums[0];
        int minSoFar = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < n; i++) {
            // Store previous values before updating
            int prevMax = maxSoFar;
            int prevMin = minSoFar;
            
            // Update max product considering current number
            // We need to consider min product too because two negatives make positive
            maxSoFar = max(nums[i], max(prevMax * nums[i], prevMin * nums[i]));
            
            // Update min product
            minSoFar = min(nums[i], min(prevMax * nums[i], prevMin * nums[i]));
            
            // Update result
            result = max(result, maxSoFar);
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

// Main function to demonstrate the Product Except Self pattern
int main() {
    // Example 1: Product of Array Except Self
    cout << "Example 1: Product of Array Except Self" << endl;
    vector<int> nums1 = {1, 2, 3, 4};
    
    cout << "Input array: ";
    printVector(nums1);
    
    ProductExceptSelf solver1;
    vector<int> result1 = solver1.productExceptSelf(nums1);
    
    cout << "Product except self (O(1) extra space): ";
    printVector(result1);
    
    vector<int> result2 = solver1.productExceptSelfExtraSpace(nums1);
    
    cout << "Product except self (using extra space): ";
    printVector(result2);
    cout << endl;
    
    // Example 2: Product Except Self with Zeros
    cout << "Example 2: Product Except Self with Zeros" << endl;
    vector<int> nums2 = {1, 2, 0, 4};
    vector<int> nums3 = {0, 0, 2, 3};
    
    cout << "Input array with one zero: ";
    printVector(nums2);
    
    ProductExceptSelfWithZeros solver2;
    vector<int> result3 = solver2.productExceptSelfWithZero(nums2);
    
    cout << "Product except self with zero: ";
    printVector(result3);
    
    cout << "Input array with two zeros: ";
    printVector(nums3);
    
    vector<int> result4 = solver2.productExceptSelfWithZero(nums3);
    
    cout << "Product except self with multiple zeros: ";
    printVector(result4);
    cout << endl;
    
    // Example 3: Maximum Product of Three Numbers
    cout << "Example 3: Maximum Product of Three Numbers" << endl;
    vector<int> nums4 = {1, 2, 3, 4, 5};
    vector<int> nums5 = {-5, -4, -3, -2, -1};
    vector<int> nums6 = {-5, -4, 1, 2, 3};
    
    cout << "Input array (all positive): ";
    printVector(nums4);
    
    MaximumProductOfThree solver3;
    int result5 = solver3.maximumProduct(nums4);
    int result6 = solver3.maximumProductLinear(nums4);
    
    cout << "Maximum product of three numbers (sorting): " << result5 << endl;
    cout << "Maximum product of three numbers (linear): " << result6 << endl;
    
    cout << "Input array (all negative): ";
    printVector(nums5);
    
    int result7 = solver3.maximumProductLinear(nums5);
    cout << "Maximum product of three numbers: " << result7 << endl;
    
    cout << "Input array (mixed): ";
    printVector(nums6);
    
    int result8 = solver3.maximumProductLinear(nums6);
    cout << "Maximum product of three numbers: " << result8 << endl;
    cout << endl;
    
    // Example 4: Continuous Product Subarray
    cout << "Example 4: Continuous Product Subarray" << endl;
    vector<int> nums7 = {2, 3, -2, 4};
    vector<int> nums8 = {-2, 0, -1};
    
    cout << "Input array 1: ";
    printVector(nums7);
    
    ContinuousProductSubarray solver4;
    int result9 = solver4.maxProduct(nums7);
    
    cout << "Maximum product subarray: " << result9 << endl;
    
    cout << "Input array 2: ";
    printVector(nums8);
    
    int result10 = solver4.maxProduct(nums8);
    
    cout << "Maximum product subarray: " << result10 << endl;
    
    return 0;
}
