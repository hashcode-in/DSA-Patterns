/**
 * Pattern: Stack - Largest Rectangle in Histogram
 * 
 * Description:
 * This pattern uses a stack to efficiently find the largest rectangle area in a histogram.
 * A histogram is represented by an array where each element represents the height of a bar,
 * and the width of each bar is 1. The key insight is to identify for each bar, how far left
 * and right it can extend to form a rectangle with height equal to that bar.
 * 
 * Time Complexity: O(n) where n is the number of bars in the histogram
 * Space Complexity: O(n) for the stack
 * 
 * When to use:
 * - When finding the largest rectangle in a histogram
 * - When solving problems involving contiguous subarrays with certain properties
 * - When dealing with area maximization problems in grid-based data structures
 * 
 * LeetCode Problems:
 * - 84. Largest Rectangle in Histogram
 * - 85. Maximal Rectangle (extension of the histogram pattern to a 2D matrix)
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Example 1: Largest Rectangle in Histogram - Two-Pass Approach
// LeetCode 84: https://leetcode.com/problems/largest-rectangle-in-histogram/
class LargestRectangleHistogram {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (n == 0) {
            return 0;
        }
        
        vector<int> leftLimit(n);  // Leftmost position each bar can extend
        vector<int> rightLimit(n); // Rightmost position each bar can extend
        
        // Initialize limits
        leftLimit[0] = 0;
        rightLimit[n-1] = n-1;
        
        // Find left limits
        for (int i = 1; i < n; i++) {
            int p = i - 1;
            
            // Find the first bar to the left that is shorter
            while (p >= 0 && heights[p] >= heights[i]) {
                p = leftLimit[p] - 1;
            }
            
            leftLimit[i] = p + 1;
        }
        
        // Find right limits
        for (int i = n-2; i >= 0; i--) {
            int p = i + 1;
            
            // Find the first bar to the right that is shorter
            while (p < n && heights[p] >= heights[i]) {
                p = rightLimit[p] + 1;
            }
            
            rightLimit[i] = p - 1;
        }
        
        // Calculate the maximum area
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            // Width is right - left + 1
            int width = rightLimit[i] - leftLimit[i] + 1;
            maxArea = max(maxArea, heights[i] * width);
        }
        
        return maxArea;
    }
};

// Example 2: Largest Rectangle in Histogram - One-Pass Approach
class LargestRectangleHistogramOnePass {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;  // Stack to store indices
        int maxArea = 0;
        int n = heights.size();
        
        // Process all bars
        for (int i = 0; i <= n; i++) {
            // Current height (0 for the final iteration to pop all remaining bars)
            int currentHeight = (i == n) ? 0 : heights[i];
            
            // While the stack is not empty and the current height is less than the height at the top of the stack
            // We've found a right boundary for the bar at the top of the stack
            while (!st.empty() && currentHeight < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();
                
                // Width calculation: i - left_boundary - 1
                // If stack is empty, the left boundary is -1 (can extend all the way left)
                int width = st.empty() ? i : i - st.top() - 1;
                
                // Calculate area and update maximum
                maxArea = max(maxArea, height * width);
            }
            
            // Push current index to the stack
            st.push(i);
        }
        
        return maxArea;
    }
};

// Example 3: Maximal Rectangle in Binary Matrix
// LeetCode 85: https://leetcode.com/problems/maximal-rectangle/
class MaximalRectangle {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // Heights for each column position
        vector<int> heights(cols, 0);
        int maxArea = 0;
        
        // For each row, calculate heights and find largest rectangle
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // Update heights
                if (matrix[i][j] == '1') {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            
            // Find largest rectangle for current row using histogram solution
            maxArea = max(maxArea, largestRectangleInHistogram(heights));
        }
        
        return maxArea;
    }
    
private:
    // Helper function using the one-pass approach
    int largestRectangleInHistogram(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        int n = heights.size();
        
        for (int i = 0; i <= n; i++) {
            int currentHeight = (i == n) ? 0 : heights[i];
            
            while (!st.empty() && currentHeight < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();
                
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            
            st.push(i);
        }
        
        return maxArea;
    }
};

// Example 4: Trapping Rain Water
// LeetCode 42: https://leetcode.com/problems/trapping-rain-water/
class TrappingRainWater {
public:
    // Using stack approach
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) {
            return 0;
        }
        
        int water = 0;
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            // While we find a higher bar, calculate water trapped
            while (!st.empty() && height[i] > height[st.top()]) {
                int top = st.top();
                st.pop();
                
                if (st.empty()) {
                    break;  // No left boundary
                }
                
                // Calculate width between current position and position at top of stack
                int width = i - st.top() - 1;
                // Calculate trapped water height
                int boundedHeight = min(height[i], height[st.top()]) - height[top];
                
                // Add trapped water
                water += width * boundedHeight;
            }
            
            // Push current index
            st.push(i);
        }
        
        return water;
    }
    
    // Alternative approach using two pointers (more optimal for space)
    int trapTwoPointers(vector<int>& height) {
        int n = height.size();
        if (n <= 2) {
            return 0;
        }
        
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                // Water can be trapped based on left max
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                // Water can be trapped based on right max
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }
        
        return water;
    }
};

// Main function to demonstrate the Largest Rectangle in Histogram pattern
int main() {
    // Example 1: Largest Rectangle in Histogram - Two-Pass Approach
    cout << "Example 1: Largest Rectangle in Histogram - Two-Pass Approach" << endl;
    
    LargestRectangleHistogram lrh;
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    
    cout << "Heights: [";
    for (size_t i = 0; i < heights1.size(); i++) {
        cout << heights1[i];
        if (i < heights1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Largest rectangle area: " << lrh.largestRectangleArea(heights1) << " (expected: 10)" << endl;
    cout << endl;
    
    // Example 2: Largest Rectangle in Histogram - One-Pass Approach
    cout << "Example 2: Largest Rectangle in Histogram - One-Pass Approach" << endl;
    
    LargestRectangleHistogramOnePass lrhOne;
    vector<int> heights2 = {2, 4, 5, 3, 1, 2};
    
    cout << "Heights: [";
    for (size_t i = 0; i < heights2.size(); i++) {
        cout << heights2[i];
        if (i < heights2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Largest rectangle area: " << lrhOne.largestRectangleArea(heights2) << " (expected: 9)" << endl;
    cout << endl;
    
    // Example 3: Maximal Rectangle in Binary Matrix
    cout << "Example 3: Maximal Rectangle in Binary Matrix" << endl;
    
    MaximalRectangle mr;
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    
    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
    cout << "Maximal rectangle area: " << mr.maximalRectangle(matrix) << " (expected: 6)" << endl;
    cout << endl;
    
    // Example 4: Trapping Rain Water
    cout << "Example 4: Trapping Rain Water" << endl;
    
    TrappingRainWater trw;
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    
    cout << "Heights: [";
    for (size_t i = 0; i < height.size(); i++) {
        cout << height[i];
        if (i < height.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Trapped water (stack approach): " << trw.trap(height) << " (expected: 6)" << endl;
    cout << "Trapped water (two pointers): " << trw.trapTwoPointers(height) << " (expected: 6)" << endl;
    
    return 0;
}
