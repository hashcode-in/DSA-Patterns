/**
 * Pattern: Backtracking - Parentheses Generation
 * 
 * Description:
 * This pattern focuses on generating valid combinations of parentheses. It's a classic
 * backtracking problem that involves making decisions about when to add opening and closing
 * parentheses while maintaining validity constraints.
 * 
 * Time Complexity: 
 * - O(4^n / sqrt(n)) - This is the nth Catalan number, which is the number of valid parentheses combinations
 * 
 * Space Complexity: O(n) for the recursion stack depth
 * 
 * When to use:
 * - Generating valid parentheses combinations
 * - Removing invalid parentheses to make a string valid
 * - Evaluating expressions with parentheses
 * 
 * LeetCode Problems:
 * - 22. Generate Parentheses
 * - 301. Remove Invalid Parentheses
 * - 32. Longest Valid Parentheses
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <queue>

using namespace std;

// Example 1: Generate Parentheses
// LeetCode 22: https://leetcode.com/problems/generate-parentheses/
class GenerateParentheses {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        
        backtrack(result, current, 0, 0, n);
        
        return result;
    }
    
private:
    void backtrack(vector<string>& result, string& current, int open, int close, int max) {
        // If we've used n opening and n closing parentheses, add the current string to the result
        if (current.length() == max * 2) {
            result.push_back(current);
            return;
        }
        
        // If we haven't used all opening parentheses, add an opening parenthesis
        if (open < max) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, max);
            current.pop_back();  // Backtrack
        }
        
        // If we have more opening than closing parentheses, add a closing parenthesis
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, max);
            current.pop_back();  // Backtrack
        }
    }
};

// Example 2: Remove Invalid Parentheses
// LeetCode 301: https://leetcode.com/problems/remove-invalid-parentheses/
class RemoveInvalidParentheses {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        
        // First, calculate the minimum number of removals needed
        int minRemoval = getMinRemoval(s);
        
        unordered_set<string> visited;  // To avoid duplicates
        
        // Start backtracking
        backtrack(s, 0, 0, 0, minRemoval, result, visited);
        
        return result;
    }
    
private:
    int getMinRemoval(const string& s) {
        int invalidCount = 0;
        int open = 0;
        
        for (char c : s) {
            if (c == '(') {
                open++;
            } else if (c == ')') {
                if (open > 0) {
                    open--;
                } else {
                    invalidCount++;
                }
            }
        }
        
        return invalidCount + open;  // Invalid closing + remaining opening
    }
    
    // Check if a string has valid parentheses
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                if (count < 0) return false;  // More closing than opening
            }
        }
        return count == 0;  // All parentheses are matched
    }
    
    void backtrack(const string& s, int index, int openCount, int closeCount, 
                   int remainingRemoval, vector<string>& result, 
                   unordered_set<string>& visited) {
        // If we've processed the entire string
        if (index == s.length()) {
            if (openCount == closeCount && remainingRemoval == 0) {
                string validString = "";
                for (int i = 0; i < s.length(); i++) {
                    if (s[i] != '#') {  // '#' marks removed characters
                        validString += s[i];
                    }
                }
                
                if (visited.find(validString) == visited.end()) {
                    result.push_back(validString);
                    visited.insert(validString);
                }
            }
            return;
        }
        
        char c = s[index];
        
        if (c == '(' || c == ')') {
            // Option 1: Remove the current parenthesis
            if (remainingRemoval > 0) {
                string newS = s.substr(0, index) + "#" + s.substr(index + 1);
                backtrack(newS, index + 1, openCount, closeCount, remainingRemoval - 1, result, visited);
            }
            
            // Option 2: Keep the current parenthesis
            if (c == '(') {
                backtrack(s, index + 1, openCount + 1, closeCount, remainingRemoval, result, visited);
            } else if (closeCount < openCount) {  // Closing parenthesis must be matched
                backtrack(s, index + 1, openCount, closeCount + 1, remainingRemoval, result, visited);
            }
        } else {
            // For non-parenthesis characters, just include them
            backtrack(s, index + 1, openCount, closeCount, remainingRemoval, result, visited);
        }
    }
    
    // Alternative approach using BFS (more efficient)
    vector<string> removeInvalidParenthesesBFS(string s) {
        vector<string> result;
        unordered_set<string> visited;
        
        // Add the initial string to the queue and visited set
        queue<string> q;
        q.push(s);
        visited.insert(s);
        
        bool found = false;
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            // If current string is valid, add it to the result
            if (isValid(curr)) {
                result.push_back(curr);
                found = true;
            }
            
            // If we've found valid strings at the current level, no need to go deeper
            if (found) continue;
            
            // Try removing each character and see if the resulting string is valid
            for (int i = 0; i < curr.length(); i++) {
                if (curr[i] != '(' && curr[i] != ')') continue;
                
                string next = curr.substr(0, i) + curr.substr(i + 1);
                
                if (visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
        
        return result;
    }
};

// Example 3: Longest Valid Parentheses
// LeetCode 32: https://leetcode.com/problems/longest-valid-parentheses/
class LongestValidParentheses {
public:
    // Stack-based approach (not backtracking, but related to parentheses)
    int longestValidParentheses(string s) {
        int maxLen = 0;
        stack<int> st;
        st.push(-1);  // Base index to calculate length
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {  // Closing parenthesis
                st.pop();
                
                if (st.empty()) {
                    st.push(i);  // New base index
                } else {
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }
        
        return maxLen;
    }
    
    // Dynamic Programming approach
    int longestValidParenthesesDP(string s) {
        int n = s.length();
        if (n <= 1) return 0;
        
        // dp[i] = length of longest valid substring ending at i
        vector<int> dp(n, 0);
        int maxLen = 0;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    // Case: "...()"
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                } else if (i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                    // Case: "...((...))"
                    dp[i] = dp[i-1] + 2 + (i - dp[i-1] >= 2 ? dp[i - dp[i-1] - 2] : 0);
                }
                
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
};

// Example 4: Minimum Removal to Make Valid Parentheses
// LeetCode 1249: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
class MinRemovalToValid {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> st;  // Stack to store indices of unmatched '('
        
        // Mark invalid parentheses with '#'
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                if (!st.empty()) {
                    st.pop();  // Matched with an opening parenthesis
                } else {
                    s[i] = '#';  // Unmatched closing parenthesis, mark for removal
                }
            }
        }
        
        // Mark remaining unmatched opening parentheses
        while (!st.empty()) {
            s[st.top()] = '#';
            st.pop();
        }
        
        // Build result string without the marked characters
        string result;
        for (char c : s) {
            if (c != '#') {
                result += c;
            }
        }
        
        return result;
    }
};

// Example 5: Score of Parentheses
// LeetCode 856: https://leetcode.com/problems/score-of-parentheses/
class ScoreOfParentheses {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);  // Current score
        
        for (char c : s) {
            if (c == '(') {
                st.push(0);  // Start a new level with score 0
            } else {
                int v = st.top();  // Score of the current level
                st.pop();
                
                int w = st.top();  // Score of the outer level
                st.pop();
                
                // Update score of outer level
                st.push(w + max(2 * v, 1));
            }
        }
        
        return st.top();
    }
    
    // Alternative approach using divide and conquer
    int scoreOfParenthesesDC(string s) {
        return score(s, 0, s.length() - 1);
    }
    
private:
    int score(const string& s, int left, int right) {
        // Base case: "()"
        if (right - left == 1) return 1;
        
        // Find the balanced split
        int balance = 0;
        for (int i = left; i < right; i++) {
            if (s[i] == '(') balance++;
            else balance--;
            
            if (balance == 0) {
                // A+B case: score from left to i + score from i+1 to right
                return score(s, left, i) + score(s, i + 1, right);
            }
        }
        
        // (A) case: 2 * score of what's inside
        return 2 * score(s, left + 1, right - 1);
    }
};

// Example 6: Valid Parenthesis String
// LeetCode 678: https://leetcode.com/problems/valid-parenthesis-string/
class ValidParenthesisString {
public:
    bool checkValidString(string s) {
        int minOpen = 0;  // Minimum number of open parentheses
        int maxOpen = 0;  // Maximum number of open parentheses
        
        for (char c : s) {
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } else if (c == ')') {
                minOpen = max(0, minOpen - 1);
                maxOpen--;
                
                if (maxOpen < 0) {
                    return false;  // Too many closing parentheses
                }
            } else {  // Wildcard '*'
                minOpen = max(0, minOpen - 1);  // '*' as ')'
                maxOpen++;  // '*' as '('
            }
        }
        
        return minOpen == 0;  // Valid if we can match all opening parentheses
    }
};

// Main function to demonstrate Parentheses Generation pattern
int main() {
    // Example 1: Generate Parentheses
    cout << "Example 1: Generate Parentheses" << endl;
    int n = 3;
    cout << "n = " << n << endl;
    
    GenerateParentheses gp;
    vector<string> result1 = gp.generateParenthesis(n);
    
    cout << "All valid parentheses combinations: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "\"" << result1[i] << "\"";
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 2: Remove Invalid Parentheses
    cout << "\nExample 2: Remove Invalid Parentheses" << endl;
    string s2 = "()())()";
    cout << "Input: " << s2 << endl;
    
    RemoveInvalidParentheses rip;
    vector<string> result2 = rip.removeInvalidParentheses(s2);
    
    cout << "Valid strings after removing minimum parentheses: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "\"" << result2[i] << "\"";
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 3: Longest Valid Parentheses
    cout << "\nExample 3: Longest Valid Parentheses" << endl;
    string s3 = "(()";
    cout << "Input: " << s3 << endl;
    
    LongestValidParentheses lvp;
    int result3 = lvp.longestValidParentheses(s3);
    
    cout << "Length of longest valid parentheses substring: " << result3 << endl;
    
    // Example 4: Minimum Removal to Make Valid Parentheses
    cout << "\nExample 4: Minimum Removal to Make Valid Parentheses" << endl;
    string s4 = "lee(t(c)o)de)";
    cout << "Input: " << s4 << endl;
    
    MinRemovalToValid mrtv;
    string result4 = mrtv.minRemoveToMakeValid(s4);
    
    cout << "String after minimum removal: " << result4 << endl;
    
    // Example 5: Score of Parentheses
    cout << "\nExample 5: Score of Parentheses" << endl;
    string s5 = "(()(()))";
    cout << "Input: " << s5 << endl;
    
    ScoreOfParentheses sop;
    int result5 = sop.scoreOfParentheses(s5);
    
    cout << "Score of the parentheses: " << result5 << endl;
    
    // Example 6: Valid Parenthesis String
    cout << "\nExample 6: Valid Parenthesis String" << endl;
    string s6 = "(*))";
    cout << "Input: " << s6 << endl;
    
    ValidParenthesisString vps;
    bool result6 = vps.checkValidString(s6);
    
    cout << "Is the string valid: " << (result6 ? "true" : "false") << endl;
    
    return 0;
}
