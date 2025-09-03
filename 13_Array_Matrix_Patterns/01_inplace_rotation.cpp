/**
 * Pattern: Array/Matrix - In-place Rotation
 * 
 * Description:
 * This pattern focuses on rotating arrays or matrices in-place without using extra space.
 * The key insight is using coordinate transformations and swap operations to rearrange elements.
 * 
 * Time Complexity: O(n) or O(n^2) depending on the problem (array or matrix)
 * Space Complexity: O(1) for truly in-place operations
 * 
 * When to use:
 * - When you need to rotate an array or matrix by a certain amount
 * - When you need to perform circular shifts on data
 * - When memory constraints require in-place operations
 * 
 * LeetCode Problems:
 * - 48. Rotate Image
 * - 189. Rotate Array
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Example 1: Rotate Image (Matrix) - Rotate a n×n matrix 90 degrees clockwise
// LeetCode 48: https://leetcode.com/problems/rotate-image/
class RotateImage {
public:
    // Approach 1: Transpose then reverse each row
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Step 1: Transpose the matrix (swap rows with columns)
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
    
    // Approach 2: Rotate four elements at a time (layer by layer)
    void rotateLayerByLayer(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Iterate through each layer of the matrix
        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;
            
            // Iterate through each element in the current layer
            for (int i = first; i < last; i++) {
                int offset = i - first;
                
                // Save the top element
                int top = matrix[first][i];
                
                // Move left to top
                matrix[first][i] = matrix[last - offset][first];
                
                // Move bottom to left
                matrix[last - offset][first] = matrix[last][last - offset];
                
                // Move right to bottom
                matrix[last][last - offset] = matrix[i][last];
                
                // Move top to right
                matrix[i][last] = top;
            }
        }
    }
};

// Example 2: Rotate Array - Rotate an array to the right by k steps
// LeetCode 189: https://leetcode.com/problems/rotate-array/
class RotateArray {
public:
    // Approach 1: Using reverse
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Handle the case where k > n
        k = k % n;
        
        if (k == 0) return; // No rotation needed
        
        // Reverse the entire array
        reverse(nums.begin(), nums.end());
        
        // Reverse the first k elements
        reverse(nums.begin(), nums.begin() + k);
        
        // Reverse the remaining n-k elements
        reverse(nums.begin() + k, nums.end());
    }
    
    // Approach 2: Using cyclic replacements
    void rotateCyclic(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Handle the case where k > n
        k = k % n;
        
        if (k == 0 || n <= 1) return; // No rotation needed
        
        int count = 0; // Keep track of how many elements have been moved
        
        for (int start = 0; count < n; start++) {
            int current = start;
            int prev = nums[start];
            
            do {
                // Calculate the next position
                int next = (current + k) % n;
                
                // Save the value at the next position
                int temp = nums[next];
                
                // Place the previous value at the next position
                nums[next] = prev;
                
                // Update previous value and current position
                prev = temp;
                current = next;
                
                count++;
            } while (start != current); // Continue until we return to the starting position
        }
    }
    
    // Approach 3: Using extra space (not in-place)
    void rotateExtraSpace(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Handle the case where k > n
        k = k % n;
        
        if (k == 0) return; // No rotation needed
        
        vector<int> temp(n);
        
        // Copy elements to their rotated positions
        for (int i = 0; i < n; i++) {
            temp[(i + k) % n] = nums[i];
        }
        
        // Copy back to the original array
        nums = temp;
    }
};

// Example 3: Rotate elements in a ring (Extension of Rotate Image)
class RotateRing {
public:
    // Rotate the outer ring of a matrix clockwise by k steps
    void rotateRingByK(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        
        // Extract the outer ring into a 1D array
        vector<int> ring;
        
        // Top row (left to right)
        for (int j = 0; j < n; j++) {
            ring.push_back(matrix[0][j]);
        }
        
        // Right column (top to bottom, excluding the top-right corner)
        for (int i = 1; i < n; i++) {
            ring.push_back(matrix[i][n - 1]);
        }
        
        // Bottom row (right to left, excluding the bottom-right corner)
        for (int j = n - 2; j >= 0; j--) {
            ring.push_back(matrix[n - 1][j]);
        }
        
        // Left column (bottom to top, excluding the bottom-left and top-left corners)
        for (int i = n - 2; i > 0; i--) {
            ring.push_back(matrix[i][0]);
        }
        
        // Rotate the ring by k steps
        int ringSize = ring.size();
        k = k % ringSize; // Handle the case where k > ringSize
        
        RotateArray rotator;
        rotator.rotate(ring, k);
        
        // Put the rotated ring back into the matrix
        int idx = 0;
        
        // Top row (left to right)
        for (int j = 0; j < n; j++) {
            matrix[0][j] = ring[idx++];
        }
        
        // Right column (top to bottom, excluding the top-right corner)
        for (int i = 1; i < n; i++) {
            matrix[i][n - 1] = ring[idx++];
        }
        
        // Bottom row (right to left, excluding the bottom-right corner)
        for (int j = n - 2; j >= 0; j--) {
            matrix[n - 1][j] = ring[idx++];
        }
        
        // Left column (bottom to top, excluding the bottom-left and top-left corners)
        for (int i = n - 2; i > 0; i--) {
            matrix[i][0] = ring[idx++];
        }
    }
};

// Example 4: Left Rotation of an Array
class LeftRotateArray {
public:
    // Rotate array to the left by d positions
    void leftRotate(vector<int>& arr, int d) {
        int n = arr.size();
        
        // Handle the case where d > n
        d = d % n;
        
        if (d == 0) return; // No rotation needed
        
        // Method 1: Using reverse (three reverse operations)
        // 1. Reverse the first d elements
        reverse(arr.begin(), arr.begin() + d);
        
        // 2. Reverse the remaining n-d elements
        reverse(arr.begin() + d, arr.end());
        
        // 3. Reverse the entire array
        reverse(arr.begin(), arr.end());
        
        // Note: We could also use the right rotation algorithm with (n-d) rotations
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

// Helper function to print a vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate the In-place Rotation pattern
int main() {
    // Example 1: Rotate Image (Matrix)
    cout << "Example 1: Rotate Image (Matrix)" << endl;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(matrix);
    
    RotateImage rotator;
    rotator.rotate(matrix);
    
    cout << "After 90-degree clockwise rotation (transpose + reverse):" << endl;
    printMatrix(matrix);
    
    // Reset matrix
    matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    rotator.rotateLayerByLayer(matrix);
    
    cout << "After 90-degree clockwise rotation (layer by layer):" << endl;
    printMatrix(matrix);
    
    // Example 2: Rotate Array
    cout << "Example 2: Rotate Array" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    
    cout << "Original array: ";
    printVector(nums);
    
    RotateArray arrayRotator;
    arrayRotator.rotate(nums, 3);
    
    cout << "After rotating 3 steps to the right (using reverse): ";
    printVector(nums);
    
    // Reset array
    nums = {1, 2, 3, 4, 5, 6, 7};
    
    arrayRotator.rotateCyclic(nums, 3);
    
    cout << "After rotating 3 steps to the right (using cyclic replacements): ";
    printVector(nums);
    
    // Reset array
    nums = {1, 2, 3, 4, 5, 6, 7};
    
    arrayRotator.rotateExtraSpace(nums, 3);
    
    cout << "After rotating 3 steps to the right (using extra space): ";
    printVector(nums);
    
    // Example 3: Rotate Ring
    cout << "Example 3: Rotate Ring" << endl;
    vector<vector<int>> ringMatrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    cout << "Original matrix:" << endl;
    printMatrix(ringMatrix);
    
    RotateRing ringRotator;
    ringRotator.rotateRingByK(ringMatrix, 2);
    
    cout << "After rotating the outer ring by 2 steps clockwise:" << endl;
    printMatrix(ringMatrix);
    
    // Example 4: Left Rotation of an Array
    cout << "Example 4: Left Rotation of an Array" << endl;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    
    cout << "Original array: ";
    printVector(arr);
    
    LeftRotateArray leftRotator;
    leftRotator.leftRotate(arr, 2);
    
    cout << "After rotating 2 steps to the left: ";
    printVector(arr);
    
    return 0;
}
