/**
 * Pattern: DP - 1D Array (Kadane's Algorithm for Max/Min Subarray)
 * 
 * Description:
 * Kadane's algorithm is a dynamic programming approach to find the maximum (or minimum)
 * sum subarray in a one-dimensional array. It's an elegant solution that runs in linear time
 * by considering at each position whether to start a new subarray or extend the current one.
 * 
 * Time Complexity: O(n) where n is the length of the array
 * Space Complexity: O(1) as we only need a few variables to track state
 * 
 * When to use:
 * - Finding the maximum (or minimum) sum contiguous subarray
 * - Problems involving optimization over contiguous segments
 * - When you need to identify the "best" subsection of an array
 * - When local decisions can lead to a global optimum
 * 
 * LeetCode Problems:
 * - 53. Maximum Subarray
 * - 152. Maximum Product Subarray
 * - 918. Maximum Sum Circular Subarray
 * - 1186. Maximum Subarray Sum with One Deletion
 * - 1191. K-Concatenation Maximum Sum
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

// Example 1: Maximum Subarray (Classic Kadane's Algorithm)
// LeetCode 53: https://leetcode.com/problems/maximum-subarray/
class MaximumSubarray {
public:
    // Approach 1: Basic Kadane's Algorithm
    int maxSubArray(vector<int>& nums) {
        int currentSum = 0;
        int maxSum = INT_MIN;
        
        for (int num : nums) {
            // Decision: start a new subarray or extend current one
            currentSum = max(num, currentSum + num);
            
            // Update global maximum
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
    
    // Approach 2: Kadane's with subarray tracking
    pair<int, pair<int, int>> maxSubArrayWithIndices(vector<int>& nums) {
        int currentSum = 0;
        int maxSum = INT_MIN;
        int start = 0;
        int tempStart = 0;
        int end = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            // If current_sum becomes negative, reset it and update start position
            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i;
            }
            
            currentSum += nums[i];
            
            // Update maxSum and indices if we found a better subarray
            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }
        }
        
        return {maxSum, {start, end}};
    }
    
    // Approach 3: Divide and Conquer (alternative to Kadane's)
    int maxSubArrayDivideConquer(vector<int>& nums) {
        return maxSubArrayDivideConquerHelper(nums, 0, nums.size() - 1);
    }
    
    int maxSubArrayDivideConquerHelper(vector<int>& nums, int left, int right) {
        // Base case: single element
        if (left == right) return nums[left];
        
        int mid = left + (right - left) / 2;
        
        // Find maximum subarray sum in left half
        int leftMax = maxSubArrayDivideConquerHelper(nums, left, mid);
        
        // Find maximum subarray sum in right half
        int rightMax = maxSubArrayDivideConquerHelper(nums, mid + 1, right);
        
        // Find maximum subarray sum that crosses the midpoint
        int crossMax = maxCrossingSum(nums, left, mid, right);
        
        // Return the maximum of the three
        return max({leftMax, rightMax, crossMax});
    }
    
    int maxCrossingSum(vector<int>& nums, int left, int mid, int right) {
        // Calculate sum of elements on left of mid
        int leftSum = 0;
        int maxLeftSum = INT_MIN;
        for (int i = mid; i >= left; i--) {
            leftSum += nums[i];
            maxLeftSum = max(maxLeftSum, leftSum);
        }
        
        // Calculate sum of elements on right of mid
        int rightSum = 0;
        int maxRightSum = INT_MIN;
        for (int i = mid + 1; i <= right; i++) {
            rightSum += nums[i];
            maxRightSum = max(maxRightSum, rightSum);
        }
        
        // Return the sum of the two
        return maxLeftSum + maxRightSum;
    }
};

// Example 2: Maximum Product Subarray
// LeetCode 152: https://leetcode.com/problems/maximum-product-subarray/
class MaximumProductSubarray {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // Initialize variables to track current max and min products
        // (we need min for handling negative numbers)
        int maxSoFar = nums[0];
        int minSoFar = nums[0];
        int result = maxSoFar;
        
        for (int i = 1; i < n; i++) {
            // Store current values before updating
            int curr = nums[i];
            int tempMax = max({curr, maxSoFar * curr, minSoFar * curr});
            minSoFar = min({curr, maxSoFar * curr, minSoFar * curr});
            
            // Update maxSoFar
            maxSoFar = tempMax;
            
            // Update global maximum
            result = max(result, maxSoFar);
        }
        
        return result;
    }
};

// Example 3: Maximum Sum Circular Subarray
// LeetCode 918: https://leetcode.com/problems/maximum-sum-circular-subarray/
class MaximumSumCircularSubarray {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        
        // Case 1: Maximum subarray sum without wrapping (standard Kadane's)
        int maxStraightSum = kadane(nums, true);
        
        // If all numbers are negative, return the maximum (least negative)
        if (maxStraightSum < 0) return maxStraightSum;
        
        // Case 2: Maximum subarray sum with wrapping
        // This is equivalent to: total_sum - minimum_subarray_sum
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        
        // Find minimum subarray sum using Kadane's
        int minStraightSum = kadane(nums, false);
        
        // Return the maximum of the two cases
        return max(maxStraightSum, totalSum - minStraightSum);
    }
    
    // Helper function for Kadane's algorithm (can find both max and min)
    int kadane(vector<int>& nums, bool findMax) {
        int currentSum = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            if (findMax) {
                currentSum = max(nums[i], currentSum + nums[i]);
                result = max(result, currentSum);
            } else {
                currentSum = min(nums[i], currentSum + nums[i]);
                result = min(result, currentSum);
            }
        }
        
        return result;
    }
};

// Example 4: Maximum Subarray Sum with One Deletion
// LeetCode 1186: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/
class MaximumSubarrayWithOneDeletion {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];
        
        // Initialize variables
        int maxWithNoDeletion = arr[0];   // Max sum without deletion
        int maxWithOneDeletion = 0;       // Max sum with one deletion
        int result = arr[0];              // Global max
        
        for (int i = 1; i < n; i++) {
            // Update max with one deletion:
            // Either delete current element (maxWithNoDeletion) or extend without deletion
            maxWithOneDeletion = max(maxWithNoDeletion, maxWithOneDeletion + arr[i]);
            
            // Update max without deletion (standard Kadane's)
            maxWithNoDeletion = max(arr[i], maxWithNoDeletion + arr[i]);
            
            // Update result
            result = max({result, maxWithNoDeletion, maxWithOneDeletion});
        }
        
        return result;
    }
};

// Example 5: K-Concatenation Maximum Sum
// LeetCode 1191: https://leetcode.com/problems/k-concatenation-maximum-sum/
class KConcatenationMaximumSum {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        const int MOD = 1e9 + 7;
        long long totalSum = 0;
        for (int num : arr) totalSum += num;
        
        // Case 1: k = 1 (just the array itself)
        if (k == 1) return kadane(arr) % MOD;
        
        // Case 2: If total sum is non-positive, then best we can do is find
        // the maximum subarray in the first two copies of the array
        if (totalSum <= 0) {
            // Concatenate array with itself and find max subarray
            vector<int> doubleArr(arr);
            doubleArr.insert(doubleArr.end(), arr.begin(), arr.end());
            return kadane(doubleArr) % MOD;
        }
        
        // Case 3: If total sum is positive, we want all k copies, possibly
        // trimming some elements from the beginning and end
        // This is: max_prefix_sum + (k-2) * total_sum + max_suffix_sum
        long long maxPrefixSum = kadanePrefix(arr);
        long long maxSuffixSum = kadaneSuffix(arr);
        
        long long result = (maxPrefixSum + (k - 2) * totalSum + maxSuffixSum) % MOD;
        
        // Handle special case where normal kadane on 2 copies is better
        vector<int> doubleArr(arr);
        doubleArr.insert(doubleArr.end(), arr.begin(), arr.end());
        result = max(result, (long long)kadane(doubleArr)) % MOD;
        
        return (int)result;
    }
    
    // Standard Kadane's algorithm
    long long kadane(vector<int>& arr) {
        long long currentSum = 0;
        long long maxSum = 0;  // At minimum, we can always have an empty subarray with sum 0
        
        for (int num : arr) {
            currentSum = max(0LL, currentSum + num);
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
    
    // Maximum sum of any prefix of the array
    long long kadanePrefix(vector<int>& arr) {
        long long currentSum = 0;
        long long maxSum = 0;
        
        for (int num : arr) {
            currentSum += num;
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
    
    // Maximum sum of any suffix of the array
    long long kadaneSuffix(vector<int>& arr) {
        long long currentSum = 0;
        long long maxSum = 0;
        
        for (int i = arr.size() - 1; i >= 0; i--) {
            currentSum += arr[i];
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
};

// Example 6: Minimum Size Subarray Sum (Variant: finding minimum length subarray with sum >= target)
// LeetCode 209: https://leetcode.com/problems/minimum-size-subarray-sum/
class MinimumSizeSubarraySum {
public:
    // This is more of a sliding window approach than Kadane's, but included for comparison
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int minLength = INT_MAX;
        
        for (int right = 0; right < n; right++) {
            sum += nums[right];
            
            // Shrink window from left while sum >= target
            while (sum >= target) {
                minLength = min(minLength, right - left + 1);
                sum -= nums[left++];
            }
        }
        
        return minLength == INT_MAX ? 0 : minLength;
    }
};

// Utility function to print a subarray
void printSubarray(const vector<int>& nums, int start, int end) {
    cout << "Subarray [" << start << "..." << end << "]: [";
    for (int i = start; i <= end; i++) {
        cout << nums[i];
        if (i < end) cout << ", ";
    }
    cout << "]" << endl;
}

// Main function to demonstrate Kadane's Algorithm pattern
int main() {
    // Example 1: Maximum Subarray
    cout << "Example 1: Maximum Subarray" << endl;
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    MaximumSubarray solution1;
    
    cout << "Array: [";
    for (int i = 0; i < nums1.size(); i++) {
        cout << nums1[i];
        if (i < nums1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    int maxSum = solution1.maxSubArray(nums1);
    cout << "Maximum subarray sum: " << maxSum << endl;
    
    auto [sum, indices] = solution1.maxSubArrayWithIndices(nums1);
    cout << "Maximum subarray sum with indices: " << sum << endl;
    printSubarray(nums1, indices.first, indices.second);
    
    // Example 2: Maximum Product Subarray
    cout << "\nExample 2: Maximum Product Subarray" << endl;
    vector<int> nums2 = {2, 3, -2, 4};
    MaximumProductSubarray solution2;
    
    cout << "Array: [";
    for (int i = 0; i < nums2.size(); i++) {
        cout << nums2[i];
        if (i < nums2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    int maxProduct = solution2.maxProduct(nums2);
    cout << "Maximum product subarray: " << maxProduct << endl;
    
    // Example 3: Maximum Sum Circular Subarray
    cout << "\nExample 3: Maximum Sum Circular Subarray" << endl;
    vector<int> nums3 = {1, -2, 3, -2};
    MaximumSumCircularSubarray solution3;
    
    cout << "Array: [";
    for (int i = 0; i < nums3.size(); i++) {
        cout << nums3[i];
        if (i < nums3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    int maxCircularSum = solution3.maxSubarraySumCircular(nums3);
    cout << "Maximum sum circular subarray: " << maxCircularSum << endl;
    
    // Example 4: Maximum Subarray Sum with One Deletion
    cout << "\nExample 4: Maximum Subarray Sum with One Deletion" << endl;
    vector<int> nums4 = {1, -2, 0, 3};
    MaximumSubarrayWithOneDeletion solution4;
    
    cout << "Array: [";
    for (int i = 0; i < nums4.size(); i++) {
        cout << nums4[i];
        if (i < nums4.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    int maxSumWithDeletion = solution4.maximumSum(nums4);
    cout << "Maximum sum with one deletion: " << maxSumWithDeletion << endl;
    
    // Example 5: K-Concatenation Maximum Sum
    cout << "\nExample 5: K-Concatenation Maximum Sum" << endl;
    vector<int> nums5 = {1, 2};
    int k = 3;
    KConcatenationMaximumSum solution5;
    
    cout << "Array: [";
    for (int i = 0; i < nums5.size(); i++) {
        cout << nums5[i];
        if (i < nums5.size() - 1) cout << ", ";
    }
    cout << "] with k=" << k << endl;
    
    int kConcatMaxSum = solution5.kConcatenationMaxSum(nums5, k);
    cout << "Maximum sum of k-concatenated array: " << kConcatMaxSum << endl;
    
    // Example 6: Minimum Size Subarray Sum
    cout << "\nExample 6: Minimum Size Subarray Sum" << endl;
    vector<int> nums6 = {2, 3, 1, 2, 4, 3};
    int target = 7;
    MinimumSizeSubarraySum solution6;
    
    cout << "Array: [";
    for (int i = 0; i < nums6.size(); i++) {
        cout << nums6[i];
        if (i < nums6.size() - 1) cout << ", ";
    }
    cout << "] with target=" << target << endl;
    
    int minLength = solution6.minSubArrayLen(target, nums6);
    cout << "Minimum length subarray with sum >= " << target << ": " << minLength << endl;
    
    return 0;
}
