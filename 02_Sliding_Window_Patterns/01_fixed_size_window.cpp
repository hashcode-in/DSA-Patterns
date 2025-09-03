/**
 * Pattern: Sliding Window - Fixed Size (Subarray Calculation)
 * 
 * Description:
 * This pattern maintains a fixed-size window that slides through an array or string,
 * calculating some value (sum, average, etc.) for each window position. It's efficient
 * because we don't recalculate the entire window - we simply remove the element that's
 * no longer in the window and add the new element.
 * 
 * Time Complexity: O(n) - where n is the length of the array
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * When to use:
 * - Finding maximum/minimum sum of a subarray of fixed size k
 * - Calculating average of all subarrays of size k
 * - Finding the subarray with the highest/lowest sum of size k
 * - Any problem requiring calculations on all possible subarrays of a fixed size
 * 
 * LeetCode Problems:
 * - 643. Maximum Average Subarray I
 * - 346. Moving Average from Data Stream
 * - 2985. Calculate Compressed Mean
 * - 3254. Find the Power of K-Size Subarrays I
 */

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Maximum Average Subarray I
// LeetCode 643: https://leetcode.com/problems/maximum-average-subarray-i/
double findMaxAverage(vector<int>& nums, int k) {
    int n = nums.size();
    
    // Calculate the sum of first k elements
    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    
    double maxSum = sum;
    
    // Slide the window and keep track of the maximum sum
    for (int i = k; i < n; i++) {
        // Add the current element and remove the element k positions back
        sum += nums[i] - nums[i - k];
        maxSum = max(maxSum, sum);
    }
    
    // Return the maximum average
    return maxSum / k;
}

// Example 2: Moving Average from Data Stream
// LeetCode 346: https://leetcode.com/problems/moving-average-from-data-stream/
class MovingAverage {
private:
    queue<int> window;
    int maxSize;
    double sum;
    
public:
    MovingAverage(int size) {
        maxSize = size;
        sum = 0;
    }
    
    double next(int val) {
        // Add the new value
        window.push(val);
        sum += val;
        
        // If window exceeds the max size, remove the oldest element
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop();
        }
        
        // Return the average
        return sum / window.size();
    }
};

// Example 3: Find Subarrays with Given Sum
vector<vector<int>> findSubarrays(vector<int>& nums, int k, int targetSum) {
    vector<vector<int>> result;
    int n = nums.size();
    
    if (n < k) return result;
    
    // Calculate the sum of first k elements
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    
    // Check if the first window has the target sum
    if (sum == targetSum) {
        result.push_back(vector<int>(nums.begin(), nums.begin() + k));
    }
    
    // Slide the window and check each subarray
    for (int i = k; i < n; i++) {
        // Add the current element and remove the element k positions back
        sum += nums[i] - nums[i - k];
        
        // If current window has the target sum, add it to the result
        if (sum == targetSum) {
            result.push_back(vector<int>(nums.begin() + (i - k + 1), nums.begin() + i + 1));
        }
    }
    
    return result;
}

// Example 4: Count Subarrays with Average Greater than Threshold
int countSubarraysWithAverageGreaterThanThreshold(vector<int>& nums, int k, double threshold) {
    int n = nums.size();
    int count = 0;
    
    if (n < k) return 0;
    
    // Calculate the sum of first k elements
    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    
    // Check if the first window's average exceeds the threshold
    if (sum / k > threshold) {
        count++;
    }
    
    // Slide the window and check each subarray
    for (int i = k; i < n; i++) {
        // Add the current element and remove the element k positions back
        sum += nums[i] - nums[i - k];
        
        // If current window's average exceeds the threshold, increment count
        if (sum / k > threshold) {
            count++;
        }
    }
    
    return count;
}

// Example 5: Maximum Sum Subarray of Size K
int maxSumSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    
    if (n < k) {
        // Not enough elements
        return -1;
    }
    
    // Calculate sum of first k elements
    int maxSum = 0;
    for (int i = 0; i < k; i++) {
        maxSum += nums[i];
    }
    
    int windowSum = maxSum;
    
    // Slide the window and update the maximum sum
    for (int i = k; i < n; i++) {
        windowSum += nums[i] - nums[i - k];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}

// Example 6: Maximum of All Subarrays of Size K (Using Deque)
// Similar to LeetCode 239: Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; // Will store indices of elements in decreasing order of values
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements as they're not useful for maximum
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        // Add current element's index to the deque
        dq.push_back(i);
        
        // Add the maximum element of the current window to the result
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Example 7: Calculate Compressed Mean (Average of Window)
// Simplified version of LeetCode 2985
double calculateCompressedMean(vector<int>& nums, int k) {
    int n = nums.size();
    if (n < k) return 0;
    
    long long totalSum = 0;
    int validWindows = 0;
    
    // Calculate the sum of first k elements
    long long windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    totalSum += windowSum;
    validWindows++;
    
    // Slide the window and accumulate window sums
    for (int i = k; i < n; i++) {
        // Update window sum by adding new element and removing oldest
        windowSum += nums[i] - nums[i - k];
        
        // Add this window's sum to the total
        totalSum += windowSum;
        validWindows++;
    }
    
    // Return the average of all window sums
    return (double)totalSum / (validWindows * k);
}

// Example 8: Minimum Subarray of Size K
int minSumSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    
    if (n < k) {
        return -1; // Not enough elements
    }
    
    // Calculate sum of first k elements
    int minSum = 0;
    for (int i = 0; i < k; i++) {
        minSum += nums[i];
    }
    
    int windowSum = minSum;
    
    // Slide the window and update the minimum sum
    for (int i = k; i < n; i++) {
        windowSum += nums[i] - nums[i - k];
        minSum = min(minSum, windowSum);
    }
    
    return minSum;
}

// Example 9: Find X-Sum of All K-Long Subarrays I
// Simplified version of LeetCode 3318
int findXSumOfSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    if (n < k) return 0;
    
    // Calculate XOR of first k elements
    int windowXor = 0;
    for (int i = 0; i < k; i++) {
        windowXor ^= nums[i];
    }
    
    int totalXor = windowXor;
    
    // Slide the window and calculate XOR of each window
    for (int i = k; i < n; i++) {
        // For XOR, we can remove the old element by XORing it again (a^a = 0)
        // And add the new element by XORing it
        windowXor ^= nums[i - k]; // Remove the outgoing element
        windowXor ^= nums[i];     // Add the incoming element
        
        // Accumulate the XORs
        totalXor ^= windowXor;
    }
    
    return totalXor;
}

// Utility function to print a vector
void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Fixed Size Sliding Window pattern
void demonstrateFixedSizeSlidingWindow() {
    cout << "Example 1: Maximum Average Subarray I" << endl;
    vector<int> nums1 = {1, 12, -5, -6, 50, 3};
    int k1 = 4;
    cout << "Array: ";
    printVector(nums1);
    cout << "Window size: " << k1 << endl;
    cout << "Maximum average: " << findMaxAverage(nums1, k1) << endl;
    
    cout << "\nExample 2: Moving Average from Data Stream" << endl;
    MovingAverage ma(3);
    cout << "Window size: 3" << endl;
    cout << "Adding 1: " << ma.next(1) << endl;
    cout << "Adding 10: " << ma.next(10) << endl;
    cout << "Adding 3: " << ma.next(3) << endl;
    cout << "Adding 5: " << ma.next(5) << endl;
    
    cout << "\nExample 3: Find Subarrays with Given Sum" << endl;
    vector<int> nums3 = {1, 2, 3, 4, 5, 6, 7, 8};
    int k3 = 3;
    int targetSum = 12;
    cout << "Array: ";
    printVector(nums3);
    cout << "Window size: " << k3 << ", Target sum: " << targetSum << endl;
    vector<vector<int>> subarrays = findSubarrays(nums3, k3, targetSum);
    cout << "Subarrays with sum " << targetSum << ":" << endl;
    for (const auto& subarray : subarrays) {
        cout << "  ";
        for (int num : subarray) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    cout << "\nExample 4: Count Subarrays with Average Greater than Threshold" << endl;
    vector<int> nums4 = {2, 2, 2, 2, 5, 5, 5, 8};
    int k4 = 3;
    double threshold = 4.0;
    cout << "Array: ";
    printVector(nums4);
    cout << "Window size: " << k4 << ", Threshold: " << threshold << endl;
    cout << "Count of subarrays: " << countSubarraysWithAverageGreaterThanThreshold(nums4, k4, threshold) << endl;
    
    cout << "\nExample 5: Maximum Sum Subarray of Size K" << endl;
    vector<int> nums5 = {2, 1, 5, 1, 3, 2};
    int k5 = 3;
    cout << "Array: ";
    printVector(nums5);
    cout << "Window size: " << k5 << endl;
    cout << "Maximum sum: " << maxSumSubarray(nums5, k5) << endl;
    
    cout << "\nExample 6: Maximum of All Subarrays of Size K" << endl;
    vector<int> nums6 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k6 = 3;
    cout << "Array: ";
    printVector(nums6);
    cout << "Window size: " << k6 << endl;
    vector<int> maxValues = maxSlidingWindow(nums6, k6);
    cout << "Maximum values in each window: ";
    printVector(maxValues);
    
    cout << "\nExample 7: Calculate Compressed Mean" << endl;
    vector<int> nums7 = {2, 3, 5, 8, 10, 9};
    int k7 = 2;
    cout << "Array: ";
    printVector(nums7);
    cout << "Window size: " << k7 << endl;
    cout << "Compressed mean: " << calculateCompressedMean(nums7, k7) << endl;
    
    cout << "\nExample 8: Minimum Subarray of Size K" << endl;
    vector<int> nums8 = {2, 1, 5, 1, 3, 2};
    int k8 = 3;
    cout << "Array: ";
    printVector(nums8);
    cout << "Window size: " << k8 << endl;
    cout << "Minimum sum: " << minSumSubarray(nums8, k8) << endl;
    
    cout << "\nExample 9: Find X-Sum of All K-Long Subarrays" << endl;
    vector<int> nums9 = {1, 2, 3, 4};
    int k9 = 2;
    cout << "Array: ";
    printVector(nums9);
    cout << "Window size: " << k9 << endl;
    cout << "X-Sum: " << findXSumOfSubarrays(nums9, k9) << endl;
}

int main() {
    // Demonstrate the Fixed Size Sliding Window pattern
    demonstrateFixedSizeSlidingWindow();
    
    return 0;
}
