/**
 * Pattern: Stack - Valid Parentheses Matching
 * 
 * Description:
 * This pattern uses a stack to validate and manipulate strings containing parentheses
 * or brackets. It's particularly useful for checking if the opening and closing brackets
 * are correctly matched and nested in the right order. The stack helps to keep track of
 * the most recent opening bracket, which should be matched with the next closing bracket.
 * 
 * Time Complexity: O(n) where n is the length of the input string
 * Space Complexity: O(n) in the worst case when all characters are opening brackets
 * 
 * When to use:
 * - When validating strings with brackets/parentheses
 * - When checking if a sequence of brackets is balanced
 * - When finding the longest valid substring with properly matched brackets
 * - When determining the minimum operations to make a string valid
 * 
 * LeetCode Problems:
 * - 20. Valid Parentheses
 * - 32. Longest Valid Parentheses
 * - 921. Minimum Add to Make Parentheses Valid
 * - 1249. Minimum Remove to Make Valid Parentheses
 * - 1963. Minimum Number of Swaps to Make the String Balanced
 */

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Example 1: Valid Parentheses
// LeetCode 20: https://leetcode.com/problems/valid-parentheses/
class ValidParentheses {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                // Push opening brackets onto the stack
                st.push(c);
            } else {
                // Check if stack is empty (no matching opening bracket)
                if (st.empty()) {
                    return false;
                }
                
                // Check if the current closing bracket matches the top of the stack
                char top = st.top();
                if ((c == ')' && top == '(') || 
                    (c == '}' && top == '{') || 
                    (c == ']' && top == '[')) {
                    st.pop();  // Matching pair found, remove the opening bracket
                } else {
                    return false;  // Mismatched brackets
                }
            }
        }
        
        // If stack is empty, all brackets were matched
        return st.empty();
    }
};

// Example 2: Longest Valid Parentheses
// LeetCode 32: https://leetcode.com/problems/longest-valid-parentheses/
class LongestValidParentheses {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);  // Base index for length calculation
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                // Push the index of the opening parenthesis
                st.push(i);
            } else {
                // Pop the top element (should be an opening parenthesis)
                st.pop();
                
                if (st.empty()) {
                    // If stack is empty, push current index as new base
                    st.push(i);
                } else {
                    // Calculate length of valid substring
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }
        
        return maxLen;
    }
    
    // Alternative approach using DP
    int longestValidParenthesesDP(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        vector<int> dp(n, 0);  // dp[i] = length of longest valid substring ending at i
        int maxLen = 0;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    // Case: "...()"
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                } else if (i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                    // Case: "...))" where "..." contains a valid substring
                    dp[i] = dp[i-1] + 2 + (i - dp[i-1] >= 2 ? dp[i - dp[i-1] - 2] : 0);
                }
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
};

// Example 3: Minimum Add to Make Parentheses Valid
// LeetCode 921: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
class MinAddToMakeValid {
public:
    int minAddToMakeValid(string s) {
        int openCount = 0;    // Count of unmatched opening brackets
        int closeCount = 0;   // Count of unmatched closing brackets
        
        for (char c : s) {
            if (c == '(') {
                // Increment count of opening brackets
                openCount++;
            } else {
                if (openCount > 0) {
                    // Match a closing bracket with an opening bracket
                    openCount--;
                } else {
                    // No matching opening bracket, need to add one
                    closeCount++;
                }
            }
        }
        
        // Sum of unmatched opening and closing brackets gives minimum additions needed
        return openCount + closeCount;
    }
    
    // Alternative approach using a stack
    int minAddToMakeValidWithStack(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                if (!st.empty() && st.top() == '(') {
                    st.pop();  // Matched pair, remove from stack
                } else {
                    st.push(c);  // Unmatched closing bracket
                }
            }
        }
        
        // Size of the stack represents the number of unmatched brackets
        return st.size();
    }
};

// Example 4: Minimum Remove to Make Valid Parentheses
// LeetCode 1249: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
class MinRemoveToMakeValid {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> st;
        unordered_set<int> indicesToRemove;
        
        // First pass: identify invalid parentheses
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                if (!st.empty()) {
                    st.pop();  // Matched pair
                } else {
                    indicesToRemove.insert(i);  // Unmatched closing bracket
                }
            }
        }
        
        // Add remaining unmatched opening brackets to removal set
        while (!st.empty()) {
            indicesToRemove.insert(st.top());
            st.pop();
        }
        
        // Second pass: build the result string by excluding indices in the removal set
        string result;
        for (int i = 0; i < s.length(); i++) {
            if (indicesToRemove.find(i) == indicesToRemove.end()) {
                result.push_back(s[i]);
            }
        }
        
        return result;
    }
};

// Example 5: Minimum Number of Swaps to Make the String Balanced
// LeetCode 1963: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/
class MinSwapsToMakeBalanced {
public:
    int minSwaps(string s) {
        int openCount = 0;    // Count of unmatched opening brackets
        int maxOpen = 0;      // Maximum number of unmatched opening brackets at any point
        
        for (char c : s) {
            if (c == '[') {
                openCount++;
            } else {
                openCount--;
            }
            
            // Keep track of the maximum deficit of opening brackets
            maxOpen = max(maxOpen, -openCount);
        }
        
        // The formula for minimum swaps is ceil(maxOpen / 2)
        return (maxOpen + 1) / 2;  // Ceiling division
    }
    
    // Alternative approach using a stack
    int minSwapsWithStack(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '[') {
                st.push(c);
            } else if (!st.empty() && st.top() == '[') {
                st.pop();  // Matched pair
            } else {
                st.push(c);  // Unmatched closing bracket
            }
        }
        
        // After this, the stack contains only unmatched brackets
        int unmatched = st.size() / 2;  // We need half the number of swaps as unmatched pairs
        
        return (unmatched + 1) / 2;  // Ceiling division
    }
};

// Main function to demonstrate the Stack - Valid Parentheses Matching pattern
int main() {
    // Example 1: Valid Parentheses
    ValidParentheses vp;
    vector<string> testStrings1 = {"()", "()[]{}", "(]", "([)]", "{[]}"};
    
    cout << "Example 1: Valid Parentheses" << endl;
    for (const string& s : testStrings1) {
        bool isValid = vp.isValid(s);
        cout << "String \"" << s << "\" is " << (isValid ? "valid" : "invalid") << endl;
    }
    
    // Example 2: Longest Valid Parentheses
    LongestValidParentheses lvp;
    vector<string> testStrings2 = {"(()", ")()())", "", "()(()"};
    
    cout << "\nExample 2: Longest Valid Parentheses" << endl;
    for (const string& s : testStrings2) {
        int maxLen = lvp.longestValidParentheses(s);
        cout << "Longest valid parentheses in \"" << s << "\" is " << maxLen << endl;
    }
    
    // Example 3: Minimum Add to Make Parentheses Valid
    MinAddToMakeValid matmv;
    vector<string> testStrings3 = {"())", "(((", "()", "()))(("};
    
    cout << "\nExample 3: Minimum Add to Make Parentheses Valid" << endl;
    for (const string& s : testStrings3) {
        int minAdd = matmv.minAddToMakeValid(s);
        cout << "Minimum additions needed for \"" << s << "\" is " << minAdd << endl;
    }
    
    // Example 4: Minimum Remove to Make Valid Parentheses
    MinRemoveToMakeValid mrtmlv;
    vector<string> testStrings4 = {"lee(t(c)o)de)", "a)b(c)d", "))(("};
    
    cout << "\nExample 4: Minimum Remove to Make Valid Parentheses" << endl;
    for (const string& s : testStrings4) {
        string validString = mrtmlv.minRemoveToMakeValid(s);
        cout << "After removing invalid parentheses from \"" << s << "\": \"" << validString << "\"" << endl;
    }
    
    // Example 5: Minimum Number of Swaps to Make the String Balanced
    MinSwapsToMakeBalanced mstmb;
    vector<string> testStrings5 = {"][", "]][[", "[]", "][]["};
    
    cout << "\nExample 5: Minimum Number of Swaps to Make the String Balanced" << endl;
    for (const string& s : testStrings5) {
        int minSwaps = mstmb.minSwaps(s);
        cout << "Minimum swaps needed for \"" << s << "\" is " << minSwaps << endl;
    }
    
    return 0;
}
