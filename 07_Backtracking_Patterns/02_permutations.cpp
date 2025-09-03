/**
 * Pattern: Backtracking - Permutations
 * 
 * Description:
 * This pattern generates all possible arrangements of elements where the order matters.
 * Unlike subsets, permutations involve reordering the original elements rather than
 * just including/excluding them.
 * 
 * Time Complexity: 
 * - O(n * n!) where n is the number of elements in the input
 * - This is because there are n! permutations and each takes O(n) to construct
 * 
 * Space Complexity: O(n) for the recursion stack
 * 
 * When to use:
 * - Finding all possible arrangements/orderings of elements
 * - Next/previous permutation problems
 * - Permutation with specific constraints
 * 
 * LeetCode Problems:
 * - 46. Permutations
 * - 47. Permutations II (with duplicates)
 * - 31. Next Permutation
 * - 60. Permutation Sequence
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

// Example 1: Generate all permutations of a given array (no duplicates)
// LeetCode 46: https://leetcode.com/problems/permutations/
class Permutations {
public:
    // Approach 1: Backtracking with swapping
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& result) {
        // If we've reached the end of the array, add the current permutation to the result
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        // Try placing each unused number at the current position
        for (int i = start; i < nums.size(); i++) {
            // Swap the current element with the element at position start
            swap(nums[start], nums[i]);
            
            // Recursively generate permutations for the next position
            backtrack(nums, start + 1, result);
            
            // Backtrack (restore the array to its original state)
            swap(nums[start], nums[i]);
        }
    }
    
    // Approach 2: Backtracking with visited set
    vector<vector<int>> permuteVisited(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> currentPerm;
        vector<bool> visited(nums.size(), false);
        
        backtrackVisited(nums, visited, currentPerm, result);
        
        return result;
    }
    
    void backtrackVisited(vector<int>& nums, vector<bool>& visited, vector<int>& currentPerm, vector<vector<int>>& result) {
        // If the current permutation is complete, add it to the result
        if (currentPerm.size() == nums.size()) {
            result.push_back(currentPerm);
            return;
        }
        
        // Try each number that hasn't been used yet
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                // Mark the current number as used
                visited[i] = true;
                currentPerm.push_back(nums[i]);
                
                // Recursively generate permutations with this number included
                backtrackVisited(nums, visited, currentPerm, result);
                
                // Backtrack
                currentPerm.pop_back();
                visited[i] = false;
            }
        }
    }
};

// Example 2: Generate all permutations of a given array (with duplicates)
// LeetCode 47: https://leetcode.com/problems/permutations-ii/
class PermutationsII {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // Sort to handle duplicates
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> result;
        vector<int> currentPerm;
        vector<bool> visited(nums.size(), false);
        
        backtrack(nums, visited, currentPerm, result);
        
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<bool>& visited, vector<int>& currentPerm, vector<vector<int>>& result) {
        // If the current permutation is complete, add it to the result
        if (currentPerm.size() == nums.size()) {
            result.push_back(currentPerm);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            // Skip duplicates: if the current element is the same as the previous one and the previous one is not used
            if (visited[i] || (i > 0 && nums[i] == nums[i-1] && !visited[i-1])) {
                continue;
            }
            
            // Mark the current number as used
            visited[i] = true;
            currentPerm.push_back(nums[i]);
            
            // Recursively generate permutations with this number included
            backtrack(nums, visited, currentPerm, result);
            
            // Backtrack
            currentPerm.pop_back();
            visited[i] = false;
        }
    }
};

// Example 3: Next Permutation
// LeetCode 31: https://leetcode.com/problems/next-permutation/
class NextPermutation {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Find the first decreasing element from the right
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        if (i >= 0) {
            // Step 2: Find the first element larger than nums[i] from the right
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            
            // Step 3: Swap nums[i] and nums[j]
            swap(nums[i], nums[j]);
        }
        
        // Step 4: Reverse the subarray starting at i+1
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// Example 4: Permutation Sequence
// LeetCode 60: https://leetcode.com/problems/permutation-sequence/
class PermutationSequence {
public:
    string getPermutation(int n, int k) {
        // Initialize the numbers from 1 to n
        vector<int> numbers;
        for (int i = 1; i <= n; i++) {
            numbers.push_back(i);
        }
        
        // Compute factorials for quick lookup
        vector<int> factorial(n + 1, 1);
        for (int i = 2; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        
        // Convert to 0-based indexing
        k--;
        
        string result;
        
        // Build the permutation
        for (int i = n - 1; i >= 0; i--) {
            // Find the index of the number to use
            int index = k / factorial[i];
            k %= factorial[i];
            
            // Append the number at the calculated index
            result += to_string(numbers[index]);
            
            // Remove the used number from the list
            numbers.erase(numbers.begin() + index);
        }
        
        return result;
    }
};

// Example 5: String Permutations
class StringPermutations {
public:
    vector<string> permute(string s) {
        vector<string> result;
        sort(s.begin(), s.end()); // Start with the smallest permutation
        
        do {
            result.push_back(s);
        } while (next_permutation(s.begin(), s.end()));
        
        return result;
    }
    
    // Custom implementation of permutation generation
    vector<string> permuteCustom(string s) {
        vector<string> result;
        backtrack(s, 0, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, vector<string>& result) {
        if (start == s.length()) {
            result.push_back(s);
            return;
        }
        
        // Use a set to avoid duplicate permutations if the string contains duplicates
        unordered_set<char> used;
        
        for (int i = start; i < s.length(); i++) {
            // Skip if this character was already used at this position
            if (used.find(s[i]) != used.end()) {
                continue;
            }
            
            used.insert(s[i]);
            
            swap(s[start], s[i]);
            backtrack(s, start + 1, result);
            swap(s[start], s[i]); // Backtrack
        }
    }
};

// Example 6: Circular Permutation in Binary Representation
// LeetCode 1238: https://leetcode.com/problems/circular-permutation-in-binary-representation/
class CircularPermutation {
public:
    vector<int> circularPermutation(int n, int start) {
        // Generate Gray code sequence
        vector<int> grayCode;
        for (int i = 0; i < (1 << n); i++) {
            grayCode.push_back(i ^ (i >> 1));
        }
        
        // Find the index of the starting element
        int startIdx = 0;
        for (int i = 0; i < grayCode.size(); i++) {
            if (grayCode[i] == start) {
                startIdx = i;
                break;
            }
        }
        
        // Rotate the array to start with the specified element
        vector<int> result;
        for (int i = 0; i < grayCode.size(); i++) {
            result.push_back(grayCode[(startIdx + i) % grayCode.size()]);
        }
        
        return result;
    }
};

// Utility function to print a vector of integers
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Utility function to print a vector of vectors
void print2DVector(const vector<vector<int>>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        printVector(vec[i]);
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Main function to demonstrate Permutation pattern
int main() {
    // Example 1: Permutations
    cout << "Example 1: Permutations" << endl;
    vector<int> nums1 = {1, 2, 3};
    cout << "Input: ";
    printVector(nums1);
    cout << endl;
    
    Permutations permutations;
    vector<vector<int>> permutationsResult = permutations.permute(nums1);
    
    cout << "All permutations: ";
    print2DVector(permutationsResult);
    
    // Example 2: Permutations II (with duplicates)
    cout << "\nExample 2: Permutations II (with duplicates)" << endl;
    vector<int> nums2 = {1, 1, 2};
    cout << "Input: ";
    printVector(nums2);
    cout << endl;
    
    PermutationsII permutationsII;
    vector<vector<int>> permutationsIIResult = permutationsII.permuteUnique(nums2);
    
    cout << "All unique permutations: ";
    print2DVector(permutationsIIResult);
    
    // Example 3: Next Permutation
    cout << "\nExample 3: Next Permutation" << endl;
    vector<int> nums3 = {1, 2, 3};
    cout << "Input: ";
    printVector(nums3);
    cout << endl;
    
    NextPermutation nextPermutation;
    nextPermutation.nextPermutation(nums3);
    
    cout << "Next permutation: ";
    printVector(nums3);
    cout << endl;
    
    // Example 4: Permutation Sequence
    cout << "\nExample 4: Permutation Sequence" << endl;
    int n = 3, k = 3;
    cout << "n = " << n << ", k = " << k << endl;
    
    PermutationSequence permutationSequence;
    string permSeq = permutationSequence.getPermutation(n, k);
    
    cout << "The " << k << "th permutation of numbers 1 to " << n << ": " << permSeq << endl;
    
    // Example 5: String Permutations
    cout << "\nExample 5: String Permutations" << endl;
    string s = "abc";
    cout << "Input string: " << s << endl;
    
    StringPermutations stringPermutations;
    vector<string> stringPermsResult = stringPermutations.permute(s);
    
    cout << "All permutations: [";
    for (int i = 0; i < stringPermsResult.size(); i++) {
        cout << "\"" << stringPermsResult[i] << "\"";
        if (i < stringPermsResult.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 6: Circular Permutation in Binary Representation
    cout << "\nExample 6: Circular Permutation in Binary Representation" << endl;
    n = 2;
    int start = 3;
    cout << "n = " << n << ", start = " << start << endl;
    
    CircularPermutation circularPermutation;
    vector<int> circularPermResult = circularPermutation.circularPermutation(n, start);
    
    cout << "Circular permutation: ";
    printVector(circularPermResult);
    cout << endl;
    
    return 0;
}
