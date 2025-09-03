/**
 * Pattern: Array - Plus One (Handling Carry)
 * 
 * Description:
 * This pattern focuses on incrementing a number represented as an array of digits,
 * handling the carry propagation efficiently. The key insight is processing the array
 * from right to left (least to most significant digit) and properly managing the carry.
 * 
 * Time Complexity: O(n) where n is the size of the input array
 * Space Complexity: O(1) or O(n) if a new array is needed for the result
 * 
 * When to use:
 * - When working with numbers too large to fit into primitive data types
 * - When manipulating digits of a number individually
 * - When implementing arbitrary-precision arithmetic
 * 
 * LeetCode Problems:
 * - 66. Plus One
 * - 67. Add Binary (similar concept with base 2)
 * - 989. Add to Array-Form of Integer
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // For reverse function

using namespace std;

// Example 1: Plus One - Given an array representing a non-negative integer, add 1 to it
// LeetCode 66: https://leetcode.com/problems/plus-one/
class PlusOne {
public:
    // Increment a number represented as an array of digits
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        
        // Start from the last digit
        for (int i = n - 1; i >= 0; i--) {
            // If the current digit is less than 9, simply increment it and return
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            
            // Otherwise, set the current digit to 0 and continue with carry
            digits[i] = 0;
        }
        
        // If we get here, it means there's a carry beyond the most significant digit
        // Need to insert a 1 at the beginning
        digits.insert(digits.begin(), 1);
        
        return digits;
    }
    
    // Alternative implementation that creates a new result array
    vector<int> plusOneNewArray(vector<int>& digits) {
        int n = digits.size();
        vector<int> result(n, 0);
        
        // Initialize carry to 1 (the "plus one" part)
        int carry = 1;
        
        for (int i = n - 1; i >= 0; i--) {
            // Calculate the sum of current digit and carry
            int sum = digits[i] + carry;
            
            // Update carry for next iteration
            carry = sum / 10;
            
            // Store the current digit
            result[i] = sum % 10;
        }
        
        // If there's a carry after processing all digits, insert it at the beginning
        if (carry > 0) {
            result.insert(result.begin(), carry);
        }
        
        return result;
    }
};

// Example 2: Variation - Add a Specific Number to Array Form
class AddToArrayForm {
public:
    // Add an integer k to a number represented as an array of digits
    // LeetCode 989: https://leetcode.com/problems/add-to-array-form-of-integer/
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> result;
        int n = num.size();
        int i = n - 1;
        int carry = 0;
        
        // Process digits until we've gone through all array digits and k becomes 0
        while (i >= 0 || k > 0 || carry > 0) {
            // Get the current digit from array (or 0 if exhausted)
            int x = (i >= 0) ? num[i] : 0;
            
            // Get the current digit from k (or 0 if exhausted)
            int y = k % 10;
            
            // Calculate sum and update carry
            int sum = x + y + carry;
            carry = sum / 10;
            
            // Add the current digit to result
            result.push_back(sum % 10);
            
            // Move to next digits
            i--;
            k /= 10;
        }
        
        // Reverse the result to get the correct order
        reverse(result.begin(), result.end());
        
        return result;
    }
};

// Example 3: Variation - Add Binary (Base 2 Addition)
// LeetCode 67: https://leetcode.com/problems/add-binary/
class AddBinary {
public:
    // Add two binary strings and return the result
    string addBinary(string a, string b) {
        string result = "";
        int i = a.length() - 1;
        int j = b.length() - 1;
        int carry = 0;
        
        // Process both strings from right to left
        while (i >= 0 || j >= 0 || carry > 0) {
            // Get the current digits (0 if index out of bounds)
            int x = (i >= 0) ? a[i] - '0' : 0;
            int y = (j >= 0) ? b[j] - '0' : 0;
            
            // Calculate sum and update carry
            int sum = x + y + carry;
            carry = sum / 2;  // In binary, carry is sum / 2
            
            // Add the current digit to result
            result = to_string(sum % 2) + result;  // In binary, digit is sum % 2
            
            // Move to next digits
            i--;
            j--;
        }
        
        return result;
    }
};

// Example 4: Variation - Large Integer Addition (Arbitrary Precision)
class LargeIntegerAddition {
public:
    // Add two large integers represented as strings
    string addStrings(string num1, string num2) {
        string result = "";
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;
        
        // Process both strings from right to left
        while (i >= 0 || j >= 0 || carry > 0) {
            // Get the current digits (0 if index out of bounds)
            int x = (i >= 0) ? num1[i] - '0' : 0;
            int y = (j >= 0) ? num2[j] - '0' : 0;
            
            // Calculate sum and update carry
            int sum = x + y + carry;
            carry = sum / 10;
            
            // Add the current digit to result
            result = to_string(sum % 10) + result;
            
            // Move to next digits
            i--;
            j--;
        }
        
        return result;
    }
    
    // Add multiple large integers represented as strings
    string addMultipleStrings(const vector<string>& nums) {
        if (nums.empty()) {
            return "0";
        }
        
        string result = nums[0];
        
        for (size_t i = 1; i < nums.size(); i++) {
            result = addStrings(result, nums[i]);
        }
        
        return result;
    }
};

// Example 5: Variation - Plus K (extend Plus One to add K)
class PlusK {
public:
    // Add k to a number represented as an array of digits
    vector<int> plusK(vector<int>& digits, int k) {
        int n = digits.size();
        int carry = k;
        
        // Start from the last digit
        for (int i = n - 1; i >= 0; i--) {
            int sum = digits[i] + carry;
            digits[i] = sum % 10;  // Update the current digit
            carry = sum / 10;      // Update carry for next iteration
            
            // If no more carry, we can return early
            if (carry == 0) {
                break;
            }
        }
        
        // If there's still a carry, insert digits at the beginning
        while (carry > 0) {
            digits.insert(digits.begin(), carry % 10);
            carry /= 10;
        }
        
        return digits;
    }
};

// Helper function to print a vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val;
    }
    cout << endl;
}

// Main function to demonstrate the Plus One pattern
int main() {
    // Example 1: Plus One
    cout << "Example 1: Plus One" << endl;
    
    // Test Case 1: Regular case with no carry
    vector<int> digits1 = {1, 2, 3};
    cout << "Input: ";
    printVector(digits1);
    
    PlusOne solver1;
    vector<int> result1 = solver1.plusOne(digits1);
    
    cout << "Output (Plus One): ";
    printVector(result1);
    
    // Test Case 2: Case with carries
    vector<int> digits2 = {9, 9, 9};
    cout << "Input: ";
    printVector(digits2);
    
    vector<int> result2 = solver1.plusOne(digits2);
    
    cout << "Output (Plus One): ";
    printVector(result2);
    cout << endl;
    
    // Example 2: Add to Array Form
    cout << "Example 2: Add to Array Form" << endl;
    vector<int> num1 = {1, 2, 0, 0};
    int k1 = 34;
    
    cout << "Input: ";
    printVector(num1);
    cout << "K: " << k1 << endl;
    
    AddToArrayForm solver2;
    vector<int> result3 = solver2.addToArrayForm(num1, k1);
    
    cout << "Output (Add To Array Form): ";
    printVector(result3);
    cout << endl;
    
    // Example 3: Add Binary
    cout << "Example 3: Add Binary" << endl;
    string a = "1010";
    string b = "1011";
    
    cout << "Input: a = " << a << ", b = " << b << endl;
    
    AddBinary solver3;
    string result4 = solver3.addBinary(a, b);
    
    cout << "Output (Add Binary): " << result4 << endl;
    cout << endl;
    
    // Example 4: Large Integer Addition
    cout << "Example 4: Large Integer Addition" << endl;
    string num2 = "12345678901234567890";
    string num3 = "98765432109876543210";
    
    cout << "Input: num1 = " << num2 << ", num2 = " << num3 << endl;
    
    LargeIntegerAddition solver4;
    string result5 = solver4.addStrings(num2, num3);
    
    cout << "Output (Large Integer Addition): " << result5 << endl;
    
    // Multiple large integers
    vector<string> multiNums = {"1111111111", "2222222222", "3333333333"};
    cout << "Input (multiple numbers): ";
    for (const auto& num : multiNums) {
        cout << num << " ";
    }
    cout << endl;
    
    string result6 = solver4.addMultipleStrings(multiNums);
    
    cout << "Output (Multiple Large Integer Addition): " << result6 << endl;
    cout << endl;
    
    // Example 5: Plus K
    cout << "Example 5: Plus K" << endl;
    vector<int> digits3 = {2, 3, 4};
    int k2 = 567;
    
    cout << "Input: ";
    printVector(digits3);
    cout << "K: " << k2 << endl;
    
    PlusK solver5;
    vector<int> result7 = solver5.plusK(digits3, k2);
    
    cout << "Output (Plus K): ";
    printVector(result7);
    
    return 0;
}
