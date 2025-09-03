/**
 * Pattern: Two Pointers - Converging (Sorted Array Target Sum)
 * 
 * Description:
 * The converging pointers pattern involves starting with two pointers at the opposite ends 
 * of a sorted array (or other data structure) and moving them towards each other until they 
 * meet or a specific condition is satisfied.
 * 
 * Time Complexity: O(n) - where n is the size of the array
 * Space Complexity: O(1) - only requires a constant amount of extra space
 * 
 * When to use:
 * - Finding pairs that sum up to a target value
 * - Container with most water problem
 * - 3Sum, 4Sum problems (with additional nested loops)
 * - Finding closest pair to a target sum
 * 
 * LeetCode Problems:
 * - 1. Two Sum (variant with sorted array: Two Sum II)
 * - 11. Container With Most Water
 * - 15. 3Sum
 * - 16. 3Sum Closest
 * - 18. 4Sum
 * - 167. Two Sum II - Input Array Is Sorted
 * - 259. 3Sum Smaller (Premium)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Example 1: Two Sum II - Find indices of two numbers that add up to target
// LeetCode 167: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;
    
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        
        if (sum == target) {
            // LeetCode problem is 1-indexed, so add 1 to both indices
            return {left + 1, right + 1};
        } else if (sum < target) {
            left++; // Need a larger sum, so move left pointer right
        } else {
            right--; // Need a smaller sum, so move right pointer left
        }
    }
    
    return {}; // No solution found (should not happen given the problem constraints)
}

// Example 2: Container With Most Water
// LeetCode 11: https://leetcode.com/problems/container-with-most-water/
int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        // Calculate water area: width × minimum height
        int width = right - left;
        int h = min(height[left], height[right]);
        int water = width * h;
        
        // Update maximum water area
        maxWater = max(maxWater, water);
        
        // Move the pointer with the smaller height
        // (Moving the taller one can only decrease or maintain the area)
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

// Example 3: 3Sum - Find all unique triplets that sum to zero
// LeetCode 15: https://leetcode.com/problems/3sum/
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> results;
    
    // Sort array to use two pointers and handle duplicates
    sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate first elements
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        // Use two pointers on the remaining array
        int left = i + 1;
        int right = n - 1;
        int target = -nums[i]; // Looking for pairs that sum to -nums[i]
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum == target) {
                // Found a triplet
                results.push_back({nums[i], nums[left], nums[right]});
                
                // Skip duplicates
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                // Move both pointers
                left++;
                right--;
            } else if (sum < target) {
                left++; // Need a larger sum
            } else {
                right--; // Need a smaller sum
            }
        }
    }
    
    return results;
}

// Example 4: 3Sum Closest - Find triplet with sum closest to target
// LeetCode 16: https://leetcode.com/problems/3sum-closest/
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int closestSum = nums[0] + nums[1] + nums[2]; // Initial closest sum
    
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            // Update closest sum if current sum is closer to target
            if (abs(sum - target) < abs(closestSum - target)) {
                closestSum = sum;
            }
            
            if (sum == target) {
                return target; // Exact match, can't get closer
            } else if (sum < target) {
                left++; // Need a larger sum
            } else {
                right--; // Need a smaller sum
            }
        }
    }
    
    return closestSum;
}

// Utility function to demonstrate the pattern
void demonstrateConvergingPointers() {
    // Example 1: Two Sum II
    vector<int> numbers = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(numbers, target);
    cout << "Two Sum Result: [" << result[0] << ", " << result[1] << "]" << endl;
    
    // Example 2: Container With Most Water
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Maximum Water Container: " << maxArea(height) << endl;
    
    // Example 3: 3Sum
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> triplets = threeSum(nums);
    cout << "3Sum Results: " << endl;
    for (const auto& triplet : triplets) {
        cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]" << endl;
    }
    
    // Example 4: 3Sum Closest
    vector<int> nums2 = {-1, 2, 1, -4};
    int target2 = 1;
    cout << "3Sum Closest: " << threeSumClosest(nums2, target2) << endl;
}

int main() {
    // Run demonstration
    demonstrateConvergingPointers();
    
    return 0;
}
