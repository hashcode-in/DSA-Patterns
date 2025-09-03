/**
 * Pattern: DP - 2D Array (Unique Paths on Grid)
 * 
 * Description:
 * This pattern involves problems where we need to find paths in a 2D grid, typically counting
 * the number of unique paths from a starting position to an ending position, or finding the
 * optimal (minimum cost or maximum value) path. We use a 2D DP table to represent the grid
 * and build our solution by combining results from adjacent cells.
 * 
 * Time Complexity: O(m*n) where m and n are the dimensions of the grid
 * Space Complexity: O(m*n) for the 2D DP table, can be optimized to O(min(m,n)) in some cases
 * 
 * When to use:
 * - Problems involving a 2D grid or matrix
 * - Finding the number of ways to reach a destination
 * - Finding the minimum/maximum cost path
 * - Robot/agent movement problems on a grid
 * 
 * LeetCode Problems:
 * - 62. Unique Paths
 * - 63. Unique Paths II
 * - 64. Minimum Path Sum
 * - 120. Triangle
 * - 931. Minimum Falling Path Sum
 * - 1289. Minimum Falling Path Sum II
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// Example 1: Unique Paths
// LeetCode 62: https://leetcode.com/problems/unique-paths/
class UniquePaths {
public:
    // Approach 1: Bottom-up DP with 2D array
    int uniquePaths(int m, int n) {
        // dp[i][j] = number of unique paths to reach position (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        // Base cases: There is only one way to reach any cell in the first row or first column
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        
        // Fill the DP table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // The number of ways to reach (i, j) is the sum of ways to reach
                // the cell above (i-1, j) and the cell to the left (i, j-1)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        
        return dp[m - 1][n - 1];
    }
    
    // Approach 2: Space-optimized version with 1D array
    int uniquePathsOptimized(int m, int n) {
        vector<int> dp(n, 1);  // Initialize all cells to 1 (base case)
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // Update dp[j] based on the cell above (dp[j]) and to the left (dp[j-1])
                dp[j] += dp[j - 1];
            }
        }
        
        return dp[n - 1];
    }
    
    // Approach 3: Mathematical solution using combinations
    int uniquePathsMath(int m, int n) {
        // To reach from (0,0) to (m-1,n-1), we need to make m-1 down moves and n-1 right moves
        // So we need to choose m-1 positions from a total of (m-1)+(n-1) positions for down moves
        // This is the combination C(m+n-2, m-1) or C(m+n-2, n-1)
        
        int totalMoves = m + n - 2;  // Total number of moves (down + right)
        int downMoves = m - 1;       // Number of down moves
        
        // Calculate C(totalMoves, downMoves) = totalMoves! / (downMoves! * (totalMoves - downMoves)!)
        long long result = 1;
        
        // To avoid overflow, calculate combination carefully
        // C(n, k) = C(n, n-k), so choose the smaller of k and n-k
        if (downMoves > totalMoves - downMoves) {
            downMoves = totalMoves - downMoves;
        }
        
        // Calculate C(totalMoves, downMoves)
        for (int i = 1; i <= downMoves; i++) {
            result *= (totalMoves - i + 1);
            result /= i;
        }
        
        return static_cast<int>(result);
    }
};

// Example 2: Unique Paths II (with obstacles)
// LeetCode 63: https://leetcode.com/problems/unique-paths-ii/
class UniquePathsII {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0) return 0;
        
        int n = obstacleGrid[0].size();
        if (n == 0) return 0;
        
        // If start or end position has an obstacle, there is no path
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }
        
        // dp[i][j] = number of unique paths to reach position (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        // Base case: There is one way to reach the start position
        dp[0][0] = 1;
        
        // Fill the first column: if there's no obstacle and the previous cell is reachable
        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0] == 0 && dp[i - 1][0] == 1) {
                dp[i][0] = 1;
            } else {
                dp[i][0] = 0;  // Once we hit an obstacle, all cells below are unreachable from the first column
            }
        }
        
        // Fill the first row: if there's no obstacle and the previous cell is reachable
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j] == 0 && dp[0][j - 1] == 1) {
                dp[0][j] = 1;
            } else {
                dp[0][j] = 0;  // Once we hit an obstacle, all cells to the right are unreachable from the first row
            }
        }
        
        // Fill the DP table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;  // If there's an obstacle, no path can go through this cell
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];  // Sum of paths from above and from left
                }
            }
        }
        
        return dp[m - 1][n - 1];
    }
    
    // Space-optimized version
    int uniquePathsWithObstaclesOptimized(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0) return 0;
        
        int n = obstacleGrid[0].size();
        if (n == 0) return 0;
        
        // If start or end position has an obstacle, there is no path
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }
        
        // 1D DP array to store the number of ways to reach each position in the current row
        vector<int> dp(n, 0);
        
        // Initialize the starting position
        dp[0] = (obstacleGrid[0][0] == 0) ? 1 : 0;
        
        // Process each row
        for (int i = 0; i < m; i++) {
            // If there's an obstacle at the beginning of the row, no path can go through this cell
            if (obstacleGrid[i][0] == 1) {
                dp[0] = 0;
            }
            
            // Process each column (starting from the second column)
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;  // If there's an obstacle, no path can go through this cell
                } else {
                    dp[j] += dp[j - 1];  // Add the number of ways to reach from the left
                }
            }
        }
        
        return dp[n - 1];
    }
};

// Example 3: Minimum Path Sum
// LeetCode 64: https://leetcode.com/problems/minimum-path-sum/
class MinimumPathSum {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        
        int n = grid[0].size();
        if (n == 0) return 0;
        
        // dp[i][j] = minimum path sum to reach position (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        // Initialize the starting position
        dp[0][0] = grid[0][0];
        
        // Fill the first column: can only come from the cell above
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        
        // Fill the first row: can only come from the cell to the left
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        
        // Fill the DP table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // Choose the minimum path from above or from left
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        
        return dp[m - 1][n - 1];
    }
    
    // Space-optimized version
    int minPathSumOptimized(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        
        int n = grid[0].size();
        if (n == 0) return 0;
        
        // 1D DP array to store the minimum path sum to reach each position in the current row
        vector<int> dp(n, INT_MAX);
        
        // Initialize the starting position
        dp[0] = grid[0][0];
        
        // Fill the first row
        for (int j = 1; j < n; j++) {
            dp[j] = dp[j - 1] + grid[0][j];
        }
        
        // Process each row
        for (int i = 1; i < m; i++) {
            // Update the first column: can only come from the cell above
            dp[0] += grid[i][0];
            
            // Process each column (starting from the second column)
            for (int j = 1; j < n; j++) {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
        
        return dp[n - 1];
    }
    
    // Return the actual minimum path (not just the sum)
    vector<pair<int, int>> getMinPath(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return {};
        
        int n = grid[0].size();
        if (n == 0) return {};
        
        // dp[i][j] = minimum path sum to reach position (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        // Initialize the starting position
        dp[0][0] = grid[0][0];
        
        // Fill the first column
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        
        // Fill the first row
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        
        // Fill the DP table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        
        // Backtrack to find the path
        vector<pair<int, int>> path;
        int i = m - 1, j = n - 1;
        
        // Start from the end position and work backwards
        path.push_back({i, j});
        
        while (i > 0 || j > 0) {
            // If we're in the first row, move left
            if (i == 0) {
                j--;
            }
            // If we're in the first column, move up
            else if (j == 0) {
                i--;
            }
            // Otherwise, choose the direction with the smaller path sum
            else if (dp[i - 1][j] <= dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
            
            path.push_back({i, j});
        }
        
        // Reverse the path to get it from start to end
        reverse(path.begin(), path.end());
        return path;
    }
};

// Example 4: Triangle (Minimum Path Sum)
// LeetCode 120: https://leetcode.com/problems/triangle/
class Triangle {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 0) return 0;
        
        // dp[i][j] = minimum path sum to reach position (i, j) in the triangle
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Initialize the top of the triangle
        dp[0][0] = triangle[0][0];
        
        // Fill the DP table
        for (int i = 1; i < n; i++) {
            // Leftmost element in the row can only come from the leftmost element in the row above
            dp[i][0] = dp[i - 1][0] + triangle[i][0];
            
            // Middle elements can come from one of two elements in the row above
            for (int j = 1; j < i; j++) {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
            
            // Rightmost element in the row can only come from the rightmost element in the row above
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        }
        
        // Find the minimum value in the bottom row
        int minPathSum = dp[n - 1][0];
        for (int j = 1; j < n; j++) {
            minPathSum = min(minPathSum, dp[n - 1][j]);
        }
        
        return minPathSum;
    }
    
    // Space-optimized version
    int minimumTotalOptimized(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 0) return 0;
        
        // Use the bottom row as the initial DP array
        vector<int> dp = triangle[n - 1];
        
        // Work backwards from the second-to-last row up to the top
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                // The minimum path sum to reach position (i, j) is the value at (i, j)
                // plus the minimum of the two adjacent positions in the row below
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        
        // The minimum path sum is now in the first element of the DP array
        return dp[0];
    }
};

// Example 5: Minimum Falling Path Sum
// LeetCode 931: https://leetcode.com/problems/minimum-falling-path-sum/
class MinimumFallingPathSum {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        
        // dp[i][j] = minimum path sum to reach position (i, j)
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Initialize the first row with the values from the matrix
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j];
        }
        
        // Fill the DP table
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Initialize with the value directly above
                dp[i][j] = dp[i - 1][j];
                
                // Check top-left (if not in the leftmost column)
                if (j > 0) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
                
                // Check top-right (if not in the rightmost column)
                if (j < n - 1) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j + 1]);
                }
                
                // Add the current cell's value
                dp[i][j] += matrix[i][j];
            }
        }
        
        // Find the minimum value in the bottom row
        int minPathSum = dp[n - 1][0];
        for (int j = 1; j < n; j++) {
            minPathSum = min(minPathSum, dp[n - 1][j]);
        }
        
        return minPathSum;
    }
    
    // Space-optimized version
    int minFallingPathSumOptimized(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        
        // Use two 1D arrays to store the current and previous rows
        vector<int> prev = matrix[0];  // Initialize with the first row
        vector<int> curr(n);
        
        // Process each row
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Initialize with the value directly above
                curr[j] = prev[j];
                
                // Check top-left (if not in the leftmost column)
                if (j > 0) {
                    curr[j] = min(curr[j], prev[j - 1]);
                }
                
                // Check top-right (if not in the rightmost column)
                if (j < n - 1) {
                    curr[j] = min(curr[j], prev[j + 1]);
                }
                
                // Add the current cell's value
                curr[j] += matrix[i][j];
            }
            
            // Update previous row for the next iteration
            prev = curr;
        }
        
        // Find the minimum value in the last row
        int minPathSum = prev[0];
        for (int j = 1; j < n; j++) {
            minPathSum = min(minPathSum, prev[j]);
        }
        
        return minPathSum;
    }
};

// Example 6: Minimum Falling Path Sum II (non-adjacent columns)
// LeetCode 1289: https://leetcode.com/problems/minimum-falling-path-sum-ii/
class MinimumFallingPathSumII {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        
        // dp[i][j] = minimum path sum to reach position (i, j)
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Initialize the first row with the values from the grid
        for (int j = 0; j < n; j++) {
            dp[0][j] = grid[0][j];
        }
        
        // Fill the DP table
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Find the minimum value in the previous row, excluding the same column
                int minPrev = INT_MAX;
                for (int k = 0; k < n; k++) {
                    if (k != j) {
                        minPrev = min(minPrev, dp[i - 1][k]);
                    }
                }
                
                // Update the current cell
                dp[i][j] = minPrev + grid[i][j];
            }
        }
        
        // Find the minimum value in the bottom row
        int minPathSum = dp[n - 1][0];
        for (int j = 1; j < n; j++) {
            minPathSum = min(minPathSum, dp[n - 1][j]);
        }
        
        return minPathSum;
    }
    
    // Optimized approach: For each row, find the two smallest values in the previous row
    int minFallingPathSumOptimized(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        if (n == 1) return grid[0][0];
        
        // Use two 1D arrays to store the current and previous rows
        vector<int> prev = grid[0];  // Initialize with the first row
        vector<int> curr(n);
        
        // Process each row
        for (int i = 1; i < n; i++) {
            // Find the two smallest values in the previous row
            int firstMin = INT_MAX, secondMin = INT_MAX;
            int firstMinIdx = -1;
            
            for (int j = 0; j < n; j++) {
                if (prev[j] < firstMin) {
                    secondMin = firstMin;
                    firstMin = prev[j];
                    firstMinIdx = j;
                } else if (prev[j] < secondMin) {
                    secondMin = prev[j];
                }
            }
            
            // For each cell in the current row, use the smallest value from the previous row
            // unless that's in the same column, in which case use the second smallest
            for (int j = 0; j < n; j++) {
                if (j != firstMinIdx) {
                    curr[j] = firstMin + grid[i][j];
                } else {
                    curr[j] = secondMin + grid[i][j];
                }
            }
            
            // Update previous row for the next iteration
            prev = curr;
        }
        
        // Find the minimum value in the last row
        int minPathSum = prev[0];
        for (int j = 1; j < n; j++) {
            minPathSum = min(minPathSum, prev[j]);
        }
        
        return minPathSum;
    }
};

// Example 7: Dungeon Game (Path with Minimum Initial Health)
// LeetCode 174: https://leetcode.com/problems/dungeon-game/
class DungeonGame {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        if (m == 0) return 0;
        
        int n = dungeon[0].size();
        if (n == 0) return 0;
        
        // dp[i][j] = minimum health needed to reach the princess from position (i, j)
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        
        // Base case: minimum health needed at the princess's position
        dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);
        
        // Fill the DP table, starting from the bottom-right
        // and working backwards to the top-left
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                // Skip the bottom-right cell (already processed)
                if (i == m - 1 && j == n - 1) continue;
                
                // Calculate minimum health needed to go down (if possible)
                int healthDown = (i + 1 < m) ? dp[i + 1][j] : INT_MAX;
                
                // Calculate minimum health needed to go right (if possible)
                int healthRight = (j + 1 < n) ? dp[i][j + 1] : INT_MAX;
                
                // Choose the direction requiring the minimum health
                int minHealthNeeded = min(healthDown, healthRight) - dungeon[i][j];
                
                // The health should at least be 1
                dp[i][j] = max(1, minHealthNeeded);
            }
        }
        
        return dp[0][0];
    }
};

// Utility function to print a 2D vector
void print2DVector(const vector<vector<int>>& vec) {
    for (const auto& row : vec) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Utility function to print a path
void printPath(const vector<pair<int, int>>& path) {
    cout << "Path: ";
    for (const auto& [i, j] : path) {
        cout << "(" << i << ", " << j << ") ";
    }
    cout << endl;
}

// Main function to demonstrate Unique Paths Grid pattern
int main() {
    // Example 1: Unique Paths
    cout << "Example 1: Unique Paths" << endl;
    int m = 3, n = 7;
    UniquePaths solution1;
    
    cout << "Grid size: " << m << " x " << n << endl;
    
    int paths = solution1.uniquePaths(m, n);
    cout << "Number of unique paths: " << paths << endl;
    
    int pathsOpt = solution1.uniquePathsOptimized(m, n);
    cout << "Number of unique paths (optimized): " << pathsOpt << endl;
    
    int pathsMath = solution1.uniquePathsMath(m, n);
    cout << "Number of unique paths (math): " << pathsMath << endl;
    
    // Example 2: Unique Paths II (with obstacles)
    cout << "\nExample 2: Unique Paths II (with obstacles)" << endl;
    vector<vector<int>> obstacleGrid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    UniquePathsII solution2;
    
    cout << "Obstacle Grid:" << endl;
    print2DVector(obstacleGrid);
    
    int pathsWithObstacles = solution2.uniquePathsWithObstacles(obstacleGrid);
    cout << "Number of unique paths with obstacles: " << pathsWithObstacles << endl;
    
    // Example 3: Minimum Path Sum
    cout << "\nExample 3: Minimum Path Sum" << endl;
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    MinimumPathSum solution3;
    
    cout << "Grid:" << endl;
    print2DVector(grid);
    
    int minSum = solution3.minPathSum(grid);
    cout << "Minimum path sum: " << minSum << endl;
    
    vector<pair<int, int>> minPath = solution3.getMinPath(grid);
    printPath(minPath);
    
    // Example 4: Triangle
    cout << "\nExample 4: Triangle" << endl;
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    Triangle solution4;
    
    cout << "Triangle:" << endl;
    for (const auto& row : triangle) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    int minTriangle = solution4.minimumTotal(triangle);
    cout << "Minimum path sum in triangle: " << minTriangle << endl;
    
    // Example 5: Minimum Falling Path Sum
    cout << "\nExample 5: Minimum Falling Path Sum" << endl;
    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };
    MinimumFallingPathSum solution5;
    
    cout << "Matrix:" << endl;
    print2DVector(matrix);
    
    int minFalling = solution5.minFallingPathSum(matrix);
    cout << "Minimum falling path sum: " << minFalling << endl;
    
    // Example 6: Minimum Falling Path Sum II
    cout << "\nExample 6: Minimum Falling Path Sum II" << endl;
    vector<vector<int>> grid2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    MinimumFallingPathSumII solution6;
    
    cout << "Grid:" << endl;
    print2DVector(grid2);
    
    int minFalling2 = solution6.minFallingPathSum(grid2);
    cout << "Minimum falling path sum (non-adjacent): " << minFalling2 << endl;
    
    // Example 7: Dungeon Game
    cout << "\nExample 7: Dungeon Game" << endl;
    vector<vector<int>> dungeon = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };
    DungeonGame solution7;
    
    cout << "Dungeon:" << endl;
    print2DVector(dungeon);
    
    int minInitialHealth = solution7.calculateMinimumHP(dungeon);
    cout << "Minimum initial health needed: " << minInitialHealth << endl;
    
    return 0;
}
