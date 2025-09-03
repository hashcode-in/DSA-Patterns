/**
 * Pattern: Greedy - Jump Game Reachability/Minimization
 * 
 * Description:
 * This pattern deals with problems where we need to determine if it's possible 
 * to reach a target by making jumps of various lengths, or to find the minimum
 * number of jumps needed to reach a target. The greedy approach makes optimal
 * local decisions at each step to achieve the global optimum.
 * 
 * Time Complexity: 
 * - Typically O(n) where n is the length of the array
 * 
 * Space Complexity: O(1) for most implementations
 * 
 * When to use:
 * - Problems involving reachability in an array where each element represents a maximum jump distance
 * - Finding the minimum jumps required to reach the end of an array
 * - Problems where you need to maximize/minimize a value while moving forward
 * 
 * LeetCode Problems:
 * - 55. Jump Game
 * - 45. Jump Game II
 * - 1306. Jump Game III
 * - 1345. Jump Game IV
 * - 1340. Jump Game V
 * - 1871. Jump Game VII
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Jump Game (Can you reach the end?)
// LeetCode 55: https://leetcode.com/problems/jump-game/
class JumpGame {
public:
    // Approach 1: Greedy (working backwards)
    bool canJump(vector<int>& nums) {
        int lastPos = nums.size() - 1;
        
        // Start from the second last position and work backwards
        for (int i = nums.size() - 2; i >= 0; i--) {
            // If we can reach the last position from current position
            if (i + nums[i] >= lastPos) {
                // Update the last position to current position
                lastPos = i;
            }
        }
        
        // If we can reach the first position, return true
        return lastPos == 0;
    }
    
    // Approach 2: Greedy (working forwards)
    bool canJumpForward(vector<int>& nums) {
        int maxReach = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            // If we can't reach the current position, return false
            if (i > maxReach) {
                return false;
            }
            
            // Update the maximum reachable position
            maxReach = max(maxReach, i + nums[i]);
            
            // If we can already reach the last position, return true
            if (maxReach >= nums.size() - 1) {
                return true;
            }
        }
        
        return true;
    }
    
    // Approach 3: Dynamic Programming (for understanding)
    bool canJumpDP(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n, false);
        dp[0] = true;  // Start position is always reachable
        
        for (int i = 0; i < n; i++) {
            if (!dp[i]) {
                continue;  // If we can't reach position i, skip it
            }
            
            // Mark all positions reachable from position i
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = true;
            }
            
            if (dp[n - 1]) {
                return true;
            }
        }
        
        return dp[n - 1];
    }
};

// Example 2: Jump Game II (Minimum jumps to reach end)
// LeetCode 45: https://leetcode.com/problems/jump-game-ii/
class JumpGameII {
public:
    // Approach 1: Greedy (BFS-like)
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        // Edge case: if array has only one element, no jumps needed
        if (n <= 1) {
            return 0;
        }
        
        int jumps = 0;     // Number of jumps
        int curMax = 0;    // Maximum position that can be reached in the current jump
        int nextMax = 0;   // Maximum position that can be reached in the next jump
        
        for (int i = 0; i < n - 1; i++) {
            // Update the farthest position that can be reached
            nextMax = max(nextMax, i + nums[i]);
            
            // If we've reached the boundary of current jump
            if (i == curMax) {
                jumps++;           // Take a jump
                curMax = nextMax;  // Update the boundary for the next jump
                
                // If we can already reach the end, break
                if (curMax >= n - 1) {
                    break;
                }
            }
        }
        
        return jumps;
    }
    
    // Approach 2: Greedy (more intuitive)
    int jumpAlternative(vector<int>& nums) {
        int n = nums.size();
        
        // If there's only one element, no jumps needed
        if (n == 1) {
            return 0;
        }
        
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;
        
        for (int i = 0; i < n - 1; i++) {
            // Update the farthest position we can reach
            farthest = max(farthest, i + nums[i]);
            
            // If we've come to the end of the current jump
            if (i == currentEnd) {
                jumps++;           // Take another jump
                currentEnd = farthest;  // Update the end for the next jump
            }
        }
        
        return jumps;
    }
    
    // Approach 3: Dynamic Programming (for understanding)
    int jumpDP(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;  // Start position needs 0 jumps
        
        for (int i = 0; i < n; i++) {
            // If position i is not reachable, skip
            if (dp[i] == INT_MAX) {
                continue;
            }
            
            // Try all possible jumps from position i
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = min(dp[i + j], dp[i] + 1);
            }
        }
        
        return dp[n - 1];
    }
};

// Example 3: Jump Game III (Can reach zero from given index)
// LeetCode 1306: https://leetcode.com/problems/jump-game-iii/
class JumpGameIII {
public:
    // Approach 1: BFS
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            // If we've found a zero, return true
            if (arr[current] == 0) {
                return true;
            }
            
            // Try jumping forward
            int forward = current + arr[current];
            if (forward < n && !visited[forward]) {
                q.push(forward);
                visited[forward] = true;
            }
            
            // Try jumping backward
            int backward = current - arr[current];
            if (backward >= 0 && !visited[backward]) {
                q.push(backward);
                visited[backward] = true;
            }
        }
        
        return false;
    }
    
    // Approach 2: DFS
    bool canReachDFS(vector<int>& arr, int start) {
        // If we're out of bounds or already visited, return false
        if (start < 0 || start >= arr.size() || arr[start] < 0) {
            return false;
        }
        
        // If we've found a zero, return true
        if (arr[start] == 0) {
            return true;
        }
        
        // Mark as visited (by negating the value)
        arr[start] = -arr[start];
        
        // Try both directions
        return canReachDFS(arr, start + arr[start]) || canReachDFS(arr, start - arr[start]);
    }
};

// Example 4: Jump Game IV (Min jumps with additional constraints)
// LeetCode 1345: https://leetcode.com/problems/jump-game-iv/
class JumpGameIV {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        
        // Edge case: if array has only one element, no jumps needed
        if (n == 1) {
            return 0;
        }
        
        // Create a map of values to all their indices
        unordered_map<int, vector<int>> indices;
        for (int i = 0; i < n; i++) {
            indices[arr[i]].push_back(i);
        }
        
        vector<bool> visited(n, false);
        visited[0] = true;
        
        queue<int> q;
        q.push(0);
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                int current = q.front();
                q.pop();
                
                // If we've reached the end, return the steps
                if (current == n - 1) {
                    return steps;
                }
                
                // Option 1: Check the value one step forward
                if (current + 1 < n && !visited[current + 1]) {
                    visited[current + 1] = true;
                    q.push(current + 1);
                }
                
                // Option 2: Check the value one step backward
                if (current - 1 >= 0 && !visited[current - 1]) {
                    visited[current - 1] = true;
                    q.push(current - 1);
                }
                
                // Option 3: Check all indices with the same value
                for (int next : indices[arr[current]]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
                
                // Clear the list to avoid revisiting indices
                indices[arr[current]].clear();
            }
            
            steps++;
        }
        
        return -1;  // Should not reach here if the array is valid
    }
};

// Example 5: Jump Game V (Max jumps with height constraints)
// LeetCode 1340: https://leetcode.com/problems/jump-game-v/
class JumpGameV {
public:
    // Approach: DP + Memoization
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> memo(n, -1);
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            result = max(result, dfs(arr, d, i, memo));
        }
        
        return result;
    }
    
private:
    int dfs(vector<int>& arr, int d, int index, vector<int>& memo) {
        // If we've already computed this result, return it
        if (memo[index] != -1) {
            return memo[index];
        }
        
        int n = arr.size();
        int result = 1;  // At minimum, we can visit the current index
        
        // Try jumping to the right
        for (int j = index + 1; j <= min(index + d, n - 1) && arr[j] < arr[index]; j++) {
            result = max(result, 1 + dfs(arr, d, j, memo));
        }
        
        // Try jumping to the left
        for (int j = index - 1; j >= max(index - d, 0) && arr[j] < arr[index]; j--) {
            result = max(result, 1 + dfs(arr, d, j, memo));
        }
        
        // Memoize the result
        memo[index] = result;
        
        return result;
    }
};

// Example 6: Jump Game VII (Can reach end with s and minJump/maxJump)
// LeetCode 1871: https://leetcode.com/problems/jump-game-vii/
class JumpGameVII {
public:
    // Approach: Sliding Window
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        
        // Can't start if first or last position is blocked
        if (s[0] == '1' || s[n - 1] == '1') {
            return false;
        }
        
        vector<bool> dp(n, false);
        dp[0] = true;  // Starting position is always reachable
        
        // Keep track of how many positions are reachable within the sliding window
        int reachable = 0;
        
        for (int i = 1; i < n; i++) {
            // Start of the window
            if (i >= minJump) {
                reachable += dp[i - minJump];
            }
            
            // End of the window (remove positions outside the window)
            if (i > maxJump) {
                reachable -= dp[i - maxJump - 1];
            }
            
            // Position is reachable if it's not blocked and there's at least one reachable position in the window
            dp[i] = s[i] == '0' && reachable > 0;
        }
        
        return dp[n - 1];
    }
    
    // Approach 2: BFS (easier to understand)
    bool canReachBFS(string s, int minJump, int maxJump) {
        int n = s.length();
        
        if (s[n - 1] == '1') {
            return false;
        }
        
        vector<bool> visited(n, false);
        visited[0] = true;
        
        queue<int> q;
        q.push(0);
        
        int farthest = 0;  // Keep track of the farthest position processed
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            // Try all possible jumps
            int start = max(farthest + 1, curr + minJump);
            int end = min(n - 1, curr + maxJump);
            
            for (int i = start; i <= end; i++) {
                if (s[i] == '0' && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                    
                    if (i == n - 1) {
                        return true;
                    }
                }
            }
            
            farthest = curr + maxJump;
        }
        
        return false;
    }
};

// Main function to demonstrate Jump Game Reachability/Minimization patterns
int main() {
    // Example 1: Jump Game
    cout << "Example 1: Jump Game (Can Reach End)" << endl;
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {3, 2, 1, 0, 4};
    
    JumpGame jg;
    cout << "Input: [2, 3, 1, 1, 4]" << endl;
    cout << "Can reach end: " << (jg.canJump(nums1) ? "true" : "false") << endl;
    cout << "Input: [3, 2, 1, 0, 4]" << endl;
    cout << "Can reach end: " << (jg.canJump(nums2) ? "true" : "false") << endl;
    
    // Example 2: Jump Game II (Minimum Jumps)
    cout << "\nExample 2: Jump Game II (Minimum Jumps)" << endl;
    vector<int> nums3 = {2, 3, 1, 1, 4};
    
    JumpGameII jg2;
    cout << "Input: [2, 3, 1, 1, 4]" << endl;
    cout << "Minimum jumps to reach end: " << jg2.jump(nums3) << endl;
    
    // Example 3: Jump Game III (Can Reach Zero)
    cout << "\nExample 3: Jump Game III (Can Reach Zero)" << endl;
    vector<int> nums4 = {4, 2, 3, 0, 3, 1, 2};
    int start = 5;
    
    JumpGameIII jg3;
    cout << "Input: [4, 2, 3, 0, 3, 1, 2], start = 5" << endl;
    cout << "Can reach a zero: " << (jg3.canReach(nums4, start) ? "true" : "false") << endl;
    
    // Example 4: Jump Game IV (Min Jumps with Equal Value)
    cout << "\nExample 4: Jump Game IV (Min Jumps with Equal Value)" << endl;
    vector<int> nums5 = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
    
    JumpGameIV jg4;
    cout << "Input: [100, -23, -23, 404, 100, 23, 23, 23, 3, 404]" << endl;
    cout << "Minimum jumps to reach end: " << jg4.minJumps(nums5) << endl;
    
    // Example 5: Jump Game V (Max Jumps with Height Constraints)
    cout << "\nExample 5: Jump Game V (Max Jumps with Height Constraints)" << endl;
    vector<int> nums6 = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    int d = 2;
    
    JumpGameV jg5;
    cout << "Input: [6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12], d = 2" << endl;
    cout << "Maximum number of indices visited: " << jg5.maxJumps(nums6, d) << endl;
    
    // Example 6: Jump Game VII (Can Reach End with Constraints)
    cout << "\nExample 6: Jump Game VII (Can Reach End with Constraints)" << endl;
    string s = "01101110";
    int minJump = 2, maxJump = 3;
    
    JumpGameVII jg7;
    cout << "Input: s = \"01101110\", minJump = 2, maxJump = 3" << endl;
    cout << "Can reach end: " << (jg7.canReach(s, minJump, maxJump) ? "true" : "false") << endl;
    
    return 0;
}
