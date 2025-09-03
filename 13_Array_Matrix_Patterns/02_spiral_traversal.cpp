/**
 * Pattern: Array/Matrix - Spiral Traversal
 * 
 * Description:
 * This pattern focuses on traversing a matrix in a spiral order, moving from the outermost
 * elements to the inner ones in a clockwise or counter-clockwise direction. The key insight
 * is to define clear boundaries and update them after traversing each layer.
 * 
 * Time Complexity: O(m*n) where m and n are the dimensions of the matrix
 * Space Complexity: O(1) excluding output space
 * 
 * When to use:
 * - When you need to process all elements in a matrix in a spiral order
 * - When generating or filling matrices in a spiral pattern
 * - When extracting data from layered structures in a systematic way
 * 
 * LeetCode Problems:
 * - 54. Spiral Matrix
 * - 59. Spiral Matrix II
 * - 885. Spiral Matrix III
 */

#include <iostream>
#include <vector>

using namespace std;

// Example 1: Spiral Matrix - Return all elements of the matrix in spiral order
// LeetCode 54: https://leetcode.com/problems/spiral-matrix/
class SpiralMatrix {
public:
    // Traverse matrix in spiral order and return the elements
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // Define boundaries for the spiral traversal
        int top = 0;
        int bottom = rows - 1;
        int left = 0;
        int right = cols - 1;
        
        while (top <= bottom && left <= right) {
            // Traverse right: move across the top row from left to right
            for (int j = left; j <= right; j++) {
                result.push_back(matrix[top][j]);
            }
            top++; // Move the top boundary down
            
            // Traverse down: move down the rightmost column
            for (int i = top; i <= bottom; i++) {
                result.push_back(matrix[i][right]);
            }
            right--; // Move the right boundary left
            
            // Check if there are more rows to traverse
            if (top <= bottom) {
                // Traverse left: move across the bottom row from right to left
                for (int j = right; j >= left; j--) {
                    result.push_back(matrix[bottom][j]);
                }
                bottom--; // Move the bottom boundary up
            }
            
            // Check if there are more columns to traverse
            if (left <= right) {
                // Traverse up: move up the leftmost column
                for (int i = bottom; i >= top; i--) {
                    result.push_back(matrix[i][left]);
                }
                left++; // Move the left boundary right
            }
        }
        
        return result;
    }
    
    // Approach 2: Using direction array
    vector<int> spiralOrderDirections(vector<vector<int>>& matrix) {
        vector<int> result;
        
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        int total = rows * cols;
        
        // Direction vectors for right, down, left, up
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int dir = 0; // Start with moving right
        
        // Starting position
        int row = 0, col = 0;
        
        // Track visited cells
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        for (int i = 0; i < total; i++) {
            // Add current element to result
            result.push_back(matrix[row][col]);
            visited[row][col] = true;
            
            // Calculate next position
            int nextRow = row + directions[dir].first;
            int nextCol = col + directions[dir].second;
            
            // Check if we need to change direction
            if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols || visited[nextRow][nextCol]) {
                // Change direction (0 -> 1 -> 2 -> 3 -> 0)
                dir = (dir + 1) % 4;
                
                // Calculate new position after changing direction
                nextRow = row + directions[dir].first;
                nextCol = col + directions[dir].second;
            }
            
            // Move to next position
            row = nextRow;
            col = nextCol;
        }
        
        return result;
    }
};

// Example 2: Spiral Matrix II - Generate an n×n matrix filled with elements from 1 to n^2 in spiral order
// LeetCode 59: https://leetcode.com/problems/spiral-matrix-ii/
class SpiralMatrixII {
public:
    vector<vector<int>> generateMatrix(int n) {
        // Initialize matrix with zeros
        vector<vector<int>> result(n, vector<int>(n, 0));
        
        // Define boundaries for the spiral traversal
        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        
        int num = 1; // Start with 1
        
        while (top <= bottom && left <= right) {
            // Fill top row from left to right
            for (int j = left; j <= right; j++) {
                result[top][j] = num++;
            }
            top++;
            
            // Fill right column from top to bottom
            for (int i = top; i <= bottom; i++) {
                result[i][right] = num++;
            }
            right--;
            
            // Check if there are more rows to traverse
            if (top <= bottom) {
                // Fill bottom row from right to left
                for (int j = right; j >= left; j--) {
                    result[bottom][j] = num++;
                }
                bottom--;
            }
            
            // Check if there are more columns to traverse
            if (left <= right) {
                // Fill left column from bottom to top
                for (int i = bottom; i >= top; i--) {
                    result[i][left] = num++;
                }
                left++;
            }
        }
        
        return result;
    }
};

// Example 3: Spiral Matrix III - Visit all points in a 2D grid starting from (r0, c0) following a spiral pattern
// LeetCode 885: https://leetcode.com/problems/spiral-matrix-iii/
class SpiralMatrixIII {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> result;
        
        // Direction vectors for east, south, west, north
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        // Current position
        int row = rStart, col = cStart;
        
        // Add the starting position
        result.push_back({row, col});
        
        // If the matrix is 1x1, we're already done
        if (rows * cols == 1) {
            return result;
        }
        
        // The spiral grows in steps of 1, 1, 2, 2, 3, 3, ...
        for (int step = 1; result.size() < rows * cols; step++) {
            for (int i = 0; i < 4; i++) { // For each direction
                int steps = (i % 2 == 0) ? step : step; // Take 'step' steps in each direction
                
                for (int j = 0; j < steps; j++) {
                    // Move in the current direction
                    row += directions[i].first;
                    col += directions[i].second;
                    
                    // If we're still in the grid, add this position
                    if (row >= 0 && row < rows && col >= 0 && col < cols) {
                        result.push_back({row, col});
                    }
                }
            }
            
            // Increment step after completing a full spiral
            // Note: step is incremented by 1 each time we go through two directions (east-south or west-north)
        }
        
        return result;
    }
    
    // Approach 2: Simplified version with clearer step handling
    vector<vector<int>> spiralMatrixIIISimplified(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> result = {{rStart, cStart}}; // Start with the initial cell
        
        // Direction vectors: east, south, west, north
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        int len = 0; // Current step length
        int d = 0;   // Current direction index
        
        while (result.size() < rows * cols) {
            if (d == 0 || d == 2) len++; // Increase step length after moving east or west
            
            for (int i = 0; i < len; i++) {
                rStart += dirs[d][0];
                cStart += dirs[d][1];
                
                // If within bounds, add to result
                if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
                    result.push_back({rStart, cStart});
                }
            }
            
            d = (d + 1) % 4; // Change direction
        }
        
        return result;
    }
};

// Example 4: Custom Spiral - Filling a matrix in a counter-clockwise spiral
class CounterClockwiseSpiral {
public:
    vector<vector<int>> generateCounterClockwise(int n) {
        // Initialize matrix with zeros
        vector<vector<int>> result(n, vector<int>(n, 0));
        
        // Define boundaries
        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        
        int num = 1;
        
        while (top <= bottom && left <= right) {
            // Fill left column from top to bottom
            for (int i = top; i <= bottom; i++) {
                result[i][left] = num++;
            }
            left++;
            
            // Fill bottom row from left to right
            for (int j = left; j <= right; j++) {
                result[bottom][j] = num++;
            }
            bottom--;
            
            // Check if there are more columns to traverse
            if (left <= right) {
                // Fill right column from bottom to top
                for (int i = bottom; i >= top; i--) {
                    result[i][right] = num++;
                }
                right--;
            }
            
            // Check if there are more rows to traverse
            if (top <= bottom) {
                // Fill top row from right to left
                for (int j = right; j >= left; j--) {
                    result[top][j] = num++;
                }
                top++;
            }
        }
        
        return result;
    }
};

// Helper function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Helper function to print a vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Spiral Traversal pattern
int main() {
    // Example 1: Spiral Matrix
    cout << "Example 1: Spiral Matrix" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix);
    
    SpiralMatrix spiralTraverser;
    vector<int> spiralOrder = spiralTraverser.spiralOrder(matrix);
    
    cout << "Spiral order: ";
    printVector(spiralOrder);
    
    vector<int> spiralOrderDir = spiralTraverser.spiralOrderDirections(matrix);
    cout << "Spiral order (using directions): ";
    printVector(spiralOrderDir);
    cout << endl;
    
    // Example 2: Spiral Matrix II
    cout << "Example 2: Spiral Matrix II" << endl;
    int n = 4;
    
    SpiralMatrixII generator;
    vector<vector<int>> spiralMatrixII = generator.generateMatrix(n);
    
    cout << "Generated " << n << "x" << n << " matrix in spiral order:" << endl;
    printMatrix(spiralMatrixII);
    
    // Example 3: Spiral Matrix III
    cout << "Example 3: Spiral Matrix III" << endl;
    int rows = 3, cols = 3, rStart = 0, cStart = 0;
    
    SpiralMatrixIII spiralIII;
    vector<vector<int>> spiralIIIResult = spiralIII.spiralMatrixIII(rows, cols, rStart, cStart);
    
    cout << "Spiral Matrix III visited positions from (" << rStart << ", " << cStart << "):" << endl;
    for (const auto& pos : spiralIIIResult) {
        cout << "(" << pos[0] << ", " << pos[1] << ") ";
    }
    cout << endl << endl;
    
    // Example 4: Counter-clockwise Spiral
    cout << "Example 4: Counter-clockwise Spiral" << endl;
    int m = 4;
    
    CounterClockwiseSpiral ccwGenerator;
    vector<vector<int>> ccwMatrix = ccwGenerator.generateCounterClockwise(m);
    
    cout << "Generated " << m << "x" << m << " matrix in counter-clockwise spiral order:" << endl;
    printMatrix(ccwMatrix);
    
    return 0;
}
