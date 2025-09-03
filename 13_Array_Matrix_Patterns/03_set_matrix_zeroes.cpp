/**
 * Pattern: Array/Matrix - Set Matrix Zeroes (In-place Marking)
 * 
 * Description:
 * This pattern focuses on efficiently marking rows and columns in a matrix that need to be
 * zeroed out based on the presence of zero elements. The key insight is using the first row
 * and first column as markers to avoid using extra space.
 * 
 * Time Complexity: O(m*n) where m and n are the dimensions of the matrix
 * Space Complexity: O(1) for the in-place solution
 * 
 * When to use:
 * - When you need to modify a matrix based on the presence of certain values
 * - When memory constraints require in-place operations
 * - When you need to propagate changes across rows and columns
 * 
 * LeetCode Problems:
 * - 73. Set Matrix Zeroes
 */

#include <iostream>
#include <vector>

using namespace std;

// Example 1: Set Matrix Zeroes - If an element is 0, set its entire row and column to 0
// LeetCode 73: https://leetcode.com/problems/set-matrix-zeroes/
class SetMatrixZeroes {
public:
    // Approach 1: Using O(m + n) extra space
    void setZeroesExtraSpace(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        
        // Track which rows and columns need to be zeroed
        vector<bool> zeroRows(m, false);
        vector<bool> zeroCols(n, false);
        
        // Mark rows and columns that contain zeros
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    zeroRows[i] = true;
                    zeroCols[j] = true;
                }
            }
        }
        
        // Set entire rows to zero
        for (int i = 0; i < m; i++) {
            if (zeroRows[i]) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Set entire columns to zero
        for (int j = 0; j < n; j++) {
            if (zeroCols[j]) {
                for (int i = 0; i < m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    // Approach 2: Using O(1) space (in-place)
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        
        // Flag to track if the first row needs to be zeroed
        bool firstRowZero = false;
        // Flag to track if the first column needs to be zeroed
        bool firstColZero = false;
        
        // Check if the first row has any zeros
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }
        
        // Check if the first column has any zeros
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }
        
        // Use the first row and first column as markers
        // If matrix[i][j] is zero, set matrix[i][0] and matrix[0][j] to zero
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        
        // Zero out rows based on the markers in the first column
        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Zero out columns based on the markers in the first row
        for (int j = 1; j < n; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Zero out the first row if needed
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        
        // Zero out the first column if needed
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
    
    // Approach 3: Alternative in-place solution using a single variable
    void setZeroesAlternative(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        
        // Use first cell (0,0) as a marker for first column
        // and track first row separately
        bool firstRowHasZero = false;
        
        // Check if the first row has any zeros
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }
        
        // Use first row and first column as markers for other cells
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // Mark the row
                    matrix[0][j] = 0; // Mark the column
                }
            }
        }
        
        // Zero out marked rows (skip first row)
        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Zero out marked columns (includes first column)
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < m; i++) { // Skip first row for now
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Zero out the first row if needed
        if (firstRowHasZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};

// Example 2: Variation - Set borders to zero when interior element is zero
class SetBordersToZero {
public:
    void setBorderZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m <= 2) return; // Nothing to do for small matrices
        int n = matrix[0].size();
        if (n <= 2) return;
        
        // Create a copy of the matrix to avoid modifying while checking
        vector<vector<int>> result = matrix;
        
        // Check interior elements (excluding the border)
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (matrix[i][j] == 0) {
                    // Zero out the corresponding border elements
                    // Top border
                    result[0][j] = 0;
                    // Bottom border
                    result[m-1][j] = 0;
                    // Left border
                    result[i][0] = 0;
                    // Right border
                    result[i][n-1] = 0;
                }
            }
        }
        
        matrix = result;
    }
};

// Example 3: Variation - Set connected region to zero when finding a zero
class SetRegionToZero {
public:
    void setConnectedZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        
        // Create a copy to avoid modifying while processing
        vector<vector<int>> result = matrix;
        
        // Direction vectors for 4-way connectivity (up, right, down, left)
        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0, -1};
        
        // Process the matrix
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    // DFS to set connected non-zero elements to zero
                    dfs(result, i, j, dx, dy, m, n);
                }
            }
        }
        
        matrix = result;
    }
    
private:
    // DFS to set connected elements to zero
    void dfs(vector<vector<int>>& matrix, int i, int j, 
             const vector<int>& dx, const vector<int>& dy, int m, int n) {
        
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            
            // Check if the neighboring cell is within bounds and not already zero
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] != 0) {
                matrix[ni][nj] = 0;
                // Continue DFS from the newly zeroed cell
                dfs(matrix, ni, nj, dx, dy, m, n);
            }
        }
    }
};

// Helper function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Main function to demonstrate the Set Matrix Zeroes pattern
int main() {
    // Example 1: Set Matrix Zeroes
    cout << "Example 1: Set Matrix Zeroes" << endl;
    vector<vector<int>> matrix1 = {
        {1, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix1);
    
    SetMatrixZeroes solver1;
    solver1.setZeroes(matrix1);
    
    cout << "After setting zeroes (in-place):" << endl;
    printMatrix(matrix1);
    
    // Example with extra space solution
    vector<vector<int>> matrix2 = {
        {1, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    };
    
    solver1.setZeroesExtraSpace(matrix2);
    
    cout << "After setting zeroes (using extra space):" << endl;
    printMatrix(matrix2);
    
    // Example 2: Set Borders to Zero
    cout << "Example 2: Set Borders to Zero" << endl;
    vector<vector<int>> matrix3 = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix3);
    
    SetBordersToZero solver2;
    solver2.setBorderZeroes(matrix3);
    
    cout << "After setting border zeroes:" << endl;
    printMatrix(matrix3);
    
    // Example 3: Set Connected Region to Zero
    cout << "Example 3: Set Connected Region to Zero" << endl;
    vector<vector<int>> matrix4 = {
        {1, 1, 1, 1, 1},
        {1, 2, 2, 0, 1},
        {1, 2, 2, 2, 1},
        {1, 2, 2, 2, 1},
        {1, 1, 1, 1, 1}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix4);
    
    SetRegionToZero solver3;
    solver3.setConnectedZeroes(matrix4);
    
    cout << "After setting connected zeroes:" << endl;
    printMatrix(matrix4);
    
    return 0;
}
