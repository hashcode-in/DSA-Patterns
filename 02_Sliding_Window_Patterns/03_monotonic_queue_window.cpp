/**
 * Pattern: Sliding Window - Monotonic Queue for Max/Min
 * 
 * Description:
 * This pattern uses a monotonic queue (deque) to efficiently track maximum or minimum 
 * elements within a sliding window. The queue maintains elements in increasing or decreasing 
 * order, allowing O(1) access to the maximum/minimum value while efficiently removing 
 * elements that are no longer in the window or cannot be maximum/minimum in future windows.
 * 
 * Time Complexity: O(n) - each element is processed at most twice (once when added, once when removed)
 * Space Complexity: O(k) - where k is the window size (maximum size of the deque)
 * 
 * When to use:
 * - Finding maximum or minimum element in each window of size k
 * - Computing subarrays that satisfy certain criteria related to max/min values
 * - Problems requiring efficient tracking of maximum/minimum values within sliding windows
 * 
 * LeetCode Problems:
 * - 239. Sliding Window Maximum
 * - 862. Shortest Subarray with Sum at Least K
 * - 1696. Jump Game VI
 */

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

// Example 1: Sliding Window Maximum
// LeetCode 239: https://leetcode.com/problems/sliding-window-maximum/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; // Store indices of elements in decreasing order of values
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements that are out of the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from the back as they won't be the maximum in current or future windows
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        // Add current element index to the deque
        dq.push_back(i);
        
        // Add maximum element to result once we have a full window
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Example 2: Sliding Window Minimum
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; // Store indices of elements in increasing order of values
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements that are out of the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove larger elements from the back as they won't be the minimum in current or future windows
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }
        
        // Add current element index to the deque
        dq.push_back(i);
        
        // Add minimum element to result once we have a full window
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Example 3: Shortest Subarray with Sum at Least K
// LeetCode 862: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    // Compute prefix sums
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    deque<int> dq; // Store indices of prefix sums in increasing order
    int minLen = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // Find subarrays that satisfy the sum criteria
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            minLen = min(minLen, i - dq.front());
            dq.pop_front();
        }
        
        // Maintain a monotonic increasing queue
        // Remove larger prefix sums from the back that can't lead to shorter valid subarrays
        while (!dq.empty() && prefix[dq.back()] >= prefix[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}

// Example 4: Jump Game VI
// LeetCode 1696: https://leetcode.com/problems/jump-game-vi/
int maxResult(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n); // dp[i] = maximum score ending at index i
    dp[0] = nums[0];
    
    deque<int> dq; // Store indices where dp[i] is monotonically decreasing
    dq.push_back(0);
    
    for (int i = 1; i < n; i++) {
        // Remove indices outside the window of size k
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // Get the maximum score from previous positions
        dp[i] = dp[dq.front()] + nums[i];
        
        // Remove smaller values from the back of the deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        // Add current index to the deque
        dq.push_back(i);
    }
    
    return dp[n - 1];
}

// Example 5: Maximum of Minimums of All Subarrays
// Find the maximum of minimums for all window sizes from 1 to n
vector<int> maxOfMinOfAllSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    
    for (int k = 1; k <= n; k++) {
        // Find minimum for each window of size k
        deque<int> dq;
        int maxOfMin = INT_MIN;
        
        for (int i = 0; i < n; i++) {
            // Remove elements outside the window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove larger elements from the back
            while (!dq.empty() && nums[dq.back()] >= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Update max of mins if we have a full window
            if (i >= k - 1) {
                maxOfMin = max(maxOfMin, nums[dq.front()]);
            }
        }
        
        result[k - 1] = maxOfMin;
    }
    
    return result;
}

// Example 6: Sum of Minimum and Maximum Elements in Subarrays
// Find the sum of (max + min) for all subarrays of size k
int sumOfMaxMinSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    if (n < k) return 0;
    
    deque<int> maxDq; // For tracking maximum
    deque<int> minDq; // For tracking minimum
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        // Remove elements outside the window from both deques
        while (!maxDq.empty() && maxDq.front() <= i - k) {
            maxDq.pop_front();
        }
        while (!minDq.empty() && minDq.front() <= i - k) {
            minDq.pop_front();
        }
        
        // Update maximum deque (decreasing order)
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[i]) {
            maxDq.pop_back();
        }
        maxDq.push_back(i);
        
        // Update minimum deque (increasing order)
        while (!minDq.empty() && nums[minDq.back()] >= nums[i]) {
            minDq.pop_back();
        }
        minDq.push_back(i);
        
        // Add max + min to sum once we have a full window
        if (i >= k - 1) {
            sum += nums[maxDq.front()] + nums[minDq.front()];
        }
    }
    
    return sum;
}

// Example 7: Count of Subarrays Where Max - Min <= Limit
// Count subarrays where the difference between max and min is at most 'limit'
int countSubarraysWithinLimit(vector<int>& nums, int limit) {
    int n = nums.size();
    int left = 0;
    int count = 0;
    deque<int> maxDq; // For tracking maximum
    deque<int> minDq; // For tracking minimum
    
    for (int right = 0; right < n; right++) {
        // Update maximum deque (decreasing order)
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right]) {
            maxDq.pop_back();
        }
        maxDq.push_back(right);
        
        // Update minimum deque (increasing order)
        while (!minDq.empty() && nums[minDq.back()] >= nums[right]) {
            minDq.pop_back();
        }
        minDq.push_back(right);
        
        // Shrink window from left if max - min > limit
        while (!maxDq.empty() && !minDq.empty() && 
               nums[maxDq.front()] - nums[minDq.front()] > limit) {
            // Move left pointer forward
            left++;
            
            // Remove indices outside the new window
            while (!maxDq.empty() && maxDq.front() < left) {
                maxDq.pop_front();
            }
            while (!minDq.empty() && minDq.front() < left) {
                minDq.pop_front();
            }
        }
        
        // Add count of valid subarrays ending at right
        count += (right - left + 1);
    }
    
    return count;
}

// Example 8: First Negative Number in Every Window of Size K
vector<int> firstNegativeInWindow(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> result;
    deque<int> negIndices; // Store indices of negative numbers
    
    for (int i = 0; i < n; i++) {
        // Add current element's index if it's negative
        if (nums[i] < 0) {
            negIndices.push_back(i);
        }
        
        // Remove elements outside the window
        while (!negIndices.empty() && negIndices.front() <= i - k) {
            negIndices.pop_front();
        }
        
        // Add first negative or 0 if none exists
        if (i >= k - 1) {
            if (!negIndices.empty()) {
                result.push_back(nums[negIndices.front()]);
            } else {
                result.push_back(0); // No negative number in this window
            }
        }
    }
    
    return result;
}

// Utility function to print a vector
template<typename T>
void printVector(const vector<T>& vec) {
    for (const T& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Monotonic Queue Sliding Window pattern
void demonstrateMonotonicQueueSlidingWindow() {
    cout << "Example 1: Sliding Window Maximum" << endl;
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    cout << "Array: ";
    printVector(nums1);
    cout << "Window size: " << k1 << endl;
    vector<int> maxValues = maxSlidingWindow(nums1, k1);
    cout << "Maximum values in each window: ";
    printVector(maxValues);
    
    cout << "\nExample 2: Sliding Window Minimum" << endl;
    vector<int> nums2 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k2 = 3;
    cout << "Array: ";
    printVector(nums2);
    cout << "Window size: " << k2 << endl;
    vector<int> minValues = minSlidingWindow(nums2, k2);
    cout << "Minimum values in each window: ";
    printVector(minValues);
    
    cout << "\nExample 3: Shortest Subarray with Sum at Least K" << endl;
    vector<int> nums3 = {2, -1, 2, 1, -2, 3};
    int k3 = 3;
    cout << "Array: ";
    printVector(nums3);
    cout << "Target sum (k): " << k3 << endl;
    cout << "Length of shortest subarray: " << shortestSubarray(nums3, k3) << endl;
    
    cout << "\nExample 4: Jump Game VI" << endl;
    vector<int> nums4 = {1, -1, -2, 4, -7, 3};
    int k4 = 2;
    cout << "Array: ";
    printVector(nums4);
    cout << "Maximum jump distance (k): " << k4 << endl;
    cout << "Maximum score: " << maxResult(nums4, k4) << endl;
    
    cout << "\nExample 5: Maximum of Minimums of All Subarrays" << endl;
    vector<int> nums5 = {3, 1, 2, 4, 2};
    cout << "Array: ";
    printVector(nums5);
    vector<int> maxOfMins = maxOfMinOfAllSubarrays(nums5);
    cout << "Max of mins for window sizes 1 to n: ";
    printVector(maxOfMins);
    
    cout << "\nExample 6: Sum of Minimum and Maximum Elements in Subarrays" << endl;
    vector<int> nums6 = {2, 5, 1, 3, 7, 4};
    int k6 = 3;
    cout << "Array: ";
    printVector(nums6);
    cout << "Window size: " << k6 << endl;
    cout << "Sum of (max + min) for all subarrays: " << sumOfMaxMinSubarrays(nums6, k6) << endl;
    
    cout << "\nExample 7: Count of Subarrays Where Max - Min <= Limit" << endl;
    vector<int> nums7 = {1, 3, 5, 7, 9};
    int limit = 4;
    cout << "Array: ";
    printVector(nums7);
    cout << "Limit: " << limit << endl;
    cout << "Count of valid subarrays: " << countSubarraysWithinLimit(nums7, limit) << endl;
    
    cout << "\nExample 8: First Negative Number in Every Window of Size K" << endl;
    vector<int> nums8 = {12, -1, -7, 8, -15, 30, 16, 28};
    int k8 = 3;
    cout << "Array: ";
    printVector(nums8);
    cout << "Window size: " << k8 << endl;
    vector<int> firstNegatives = firstNegativeInWindow(nums8, k8);
    cout << "First negative number in each window: ";
    printVector(firstNegatives);
}

int main() {
    // Demonstrate the Monotonic Queue Sliding Window pattern
    demonstrateMonotonicQueueSlidingWindow();
    
    return 0;
}
