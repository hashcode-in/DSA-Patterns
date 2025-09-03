/**
 * Pattern: Backtracking - Palindrome Partitioning
 * 
 * Description:
 * This pattern involves partitioning a string into substrings such that each substring is a palindrome.
 * It's a backtracking problem that explores all possible ways to cut a string while maintaining
 * the palindrome property for each segment.
 * 
 * Time Complexity: 
 * - O(N * 2^N) where N is the length of the string
 * - We need to check all possible substrings (O(2^N)) and each check takes O(N) time
 * 
 * Space Complexity: O(N) for the recursion stack depth
 * 
 * When to use:
 * - String partitioning problems where each partition must have certain properties
 * - Problems requiring all possible ways to split a string
 * - Minimizing the number of cuts in a string
 * 
 * LeetCode Problems:
 * - 131. Palindrome Partitioning
 * - 132. Palindrome Partitioning II (minimizing cuts)
 * - 1745. Palindrome Partitioning IV
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Example 1: Palindrome Partitioning
// LeetCode 131: https://leetcode.com/problems/palindrome-partitioning/
class PalindromePartitioning {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> currentPartition;
        
        // Pre-compute palindrome status
        int n = s.length();
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome);
        
        backtrack(s, 0, currentPartition, result, isPalindrome);
        
        return result;
    }
    
private:
    // Pre-compute all palindrome substrings to avoid repeated checks
    void precomputePalindromes(const string& s, vector<vector<bool>>& isPalindrome) {
        int n = s.length();
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        
        // Check for palindromes of length 3 or more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i + 1][j - 1];
            }
        }
    }
    
    void backtrack(const string& s, int start, vector<string>& currentPartition, 
                   vector<vector<string>>& result, const vector<vector<bool>>& isPalindrome) {
        // If we've reached the end of the string, add the current partition to the result
        if (start >= s.length()) {
            result.push_back(currentPartition);
            return;
        }
        
        // Try all possible substrings starting at the current position
        for (int end = start; end < s.length(); end++) {
            // If the substring s[start...end] is a palindrome
            if (isPalindrome[start][end]) {
                // Add this substring to the current partition
                currentPartition.push_back(s.substr(start, end - start + 1));
                
                // Recursively partition the rest of the string
                backtrack(s, end + 1, currentPartition, result, isPalindrome);
                
                // Backtrack
                currentPartition.pop_back();
            }
        }
    }
};

// Example 2: Palindrome Partitioning II (Minimum Cuts)
// LeetCode 132: https://leetcode.com/problems/palindrome-partitioning-ii/
class PalindromePartitioningII {
public:
    // Dynamic Programming approach (not backtracking, but related problem)
    int minCut(string s) {
        int n = s.length();
        
        // Pre-compute palindrome status
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome);
        
        // dp[i] = minimum number of cuts needed for s[0...i]
        vector<int> dp(n, n);  // Initialize with maximum possible cuts
        
        for (int i = 0; i < n; i++) {
            // If s[0...i] is a palindrome, no cuts needed
            if (isPalindrome[0][i]) {
                dp[i] = 0;
                continue;
            }
            
            for (int j = 0; j < i; j++) {
                // If s[j+1...i] is a palindrome, then add 1 to dp[j]
                if (isPalindrome[j + 1][i]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        
        return dp[n - 1];
    }
    
    // Recursive approach with memoization
    int minCutRecursive(string s) {
        int n = s.length();
        
        // Pre-compute palindrome status
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome);
        
        // Memoization to avoid redundant calculations
        vector<int> memo(n, -1);
        
        return minCutHelper(s, 0, isPalindrome, memo);
    }
    
private:
    void precomputePalindromes(const string& s, vector<vector<bool>>& isPalindrome) {
        int n = s.length();
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        
        // Check for palindromes of length 3 or more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i + 1][j - 1];
            }
        }
    }
    
    int minCutHelper(const string& s, int start, const vector<vector<bool>>& isPalindrome, vector<int>& memo) {
        int n = s.length();
        
        // Base case: if we've reached the end of the string or s[start...n-1] is a palindrome
        if (start >= n || isPalindrome[start][n - 1]) {
            return 0;
        }
        
        // If we've already computed this result
        if (memo[start] != -1) {
            return memo[start];
        }
        
        int minCuts = INT_MAX;
        
        // Try all possible cuts at the current position
        for (int i = start; i < n; i++) {
            if (isPalindrome[start][i]) {
                minCuts = min(minCuts, 1 + minCutHelper(s, i + 1, isPalindrome, memo));
            }
        }
        
        // Memoize the result
        memo[start] = minCuts;
        
        return minCuts;
    }
};

// Example 3: Palindrome Partitioning IV
// LeetCode 1745: https://leetcode.com/problems/palindrome-partitioning-iv/
class PalindromePartitioningIV {
public:
    bool checkPartitioning(string s) {
        int n = s.length();
        
        // Pre-compute palindrome status
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome);
        
        // Check if s can be partitioned into exactly 3 palindromes
        for (int i = 0; i < n - 2; i++) {
            if (!isPalindrome[0][i]) continue;
            
            for (int j = i + 1; j < n - 1; j++) {
                if (!isPalindrome[i + 1][j]) continue;
                
                if (isPalindrome[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    void precomputePalindromes(const string& s, vector<vector<bool>>& isPalindrome) {
        int n = s.length();
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        
        // Check for palindromes of length 3 or more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i + 1][j - 1];
            }
        }
    }
};

// Example 4: Longest Palindromic Substring
// LeetCode 5: https://leetcode.com/problems/longest-palindromic-substring/
class LongestPalindromicSubstring {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) return s;
        
        // Pre-compute palindrome status
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome);
        
        int maxLen = 1;  // Length of the longest palindrome found
        int start = 0;   // Starting index of the longest palindrome
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome[i][j] && (j - i + 1 > maxLen)) {
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
    
private:
    void precomputePalindromes(const string& s, vector<vector<bool>>& isPalindrome) {
        int n = s.length();
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        
        // Check for palindromes of length 3 or more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i + 1][j - 1];
            }
        }
    }
    
    // Alternative approach: expand around center
    string longestPalindromeExpand(string s) {
        int n = s.length();
        if (n <= 1) return s;
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < n; i++) {
            // Expand around center for odd-length palindromes
            int len1 = expandAroundCenter(s, i, i);
            
            // Expand around center for even-length palindromes
            int len2 = expandAroundCenter(s, i, i + 1);
            
            int len = max(len1, len2);
            
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        
        return right - left - 1;  // Length of the palindrome
    }
};

// Example 5: Palindromic Substrings
// LeetCode 647: https://leetcode.com/problems/palindromic-substrings/
class PalindromicSubstrings {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        
        // Pre-compute palindrome status
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        precomputePalindromes(s, isPalindrome, count);
        
        return count;
    }
    
    // Alternative approach: expand around center
    int countSubstringsExpand(string s) {
        int n = s.length();
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            // Expand around center for odd-length palindromes
            count += expandAroundCenter(s, i, i);
            
            // Expand around center for even-length palindromes
            count += expandAroundCenter(s, i, i + 1);
        }
        
        return count;
    }
    
private:
    void precomputePalindromes(const string& s, vector<vector<bool>>& isPalindrome, int& count) {
        int n = s.length();
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
            count++;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
            if (isPalindrome[i][i + 1]) {
                count++;
            }
        }
        
        // Check for palindromes of length 3 or more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i + 1][j - 1];
                if (isPalindrome[i][j]) {
                    count++;
                }
            }
        }
    }
    
    int expandAroundCenter(const string& s, int left, int right) {
        int count = 0;
        
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        
        return count;
    }
};

// Example 6: Palindrome Permutation
// LeetCode 266: https://leetcode.com/problems/palindrome-permutation/
class PalindromePermutation {
public:
    bool canPermutePalindrome(string s) {
        // Count the frequency of each character
        unordered_map<char, int> charCount;
        
        for (char c : s) {
            charCount[c]++;
        }
        
        // Count characters with odd frequency
        int oddCount = 0;
        
        for (const auto& pair : charCount) {
            if (pair.second % 2 == 1) {
                oddCount++;
            }
        }
        
        // For a string to be a palindrome, at most one character can have an odd frequency
        return oddCount <= 1;
    }
    
    // Generate all palindrome permutations (bonus)
    vector<string> generatePalindromePermutations(string s) {
        unordered_map<char, int> charCount;
        
        for (char c : s) {
            charCount[c]++;
        }
        
        char oddChar = '\0';
        string halfString = "";
        
        for (const auto& pair : charCount) {
            if (pair.second % 2 == 1) {
                oddChar = pair.first;
            }
            
            // Add half of the occurrences to halfString
            for (int i = 0; i < pair.second / 2; i++) {
                halfString += pair.first;
            }
        }
        
        vector<string> result;
        vector<bool> used(halfString.length(), false);
        string current;
        
        backtrack(halfString, used, current, result, oddChar);
        
        return result;
    }
    
private:
    void backtrack(const string& halfString, vector<bool>& used, string& current, 
                   vector<string>& result, char oddChar) {
        if (current.length() == halfString.length()) {
            // Create the other half (reverse of current)
            string otherHalf = current;
            std::reverse(otherHalf.begin(), otherHalf.end());
            
            // Build the palindrome
            string palindrome = current;
            if (oddChar != '\0') {
                palindrome += oddChar;
            }
            palindrome += otherHalf;
            
            result.push_back(palindrome);
            return;
        }
        
        for (int i = 0; i < halfString.length(); i++) {
            // Skip if the character is used or is a duplicate
            if (used[i] || (i > 0 && halfString[i] == halfString[i-1] && !used[i-1])) {
                continue;
            }
            
            used[i] = true;
            current.push_back(halfString[i]);
            
            backtrack(halfString, used, current, result, oddChar);
            
            current.pop_back();
            used[i] = false;
        }
    }
};

// Utility function to check if a string is a palindrome
bool isPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start++] != s[end--]) {
            return false;
        }
    }
    return true;
}

// Utility function to print a vector of strings
void printStringVector(const vector<string>& vec) {
    for (const string& str : vec) {
        cout << str << " ";
    }
    cout << endl;
}

// Utility function to print a vector of vector of strings
void print2DStringVector(const vector<vector<string>>& vec) {
    for (const auto& partition : vec) {
        cout << "[ ";
        for (const string& str : partition) {
            cout << str << " ";
        }
        cout << "]" << endl;
    }
}

// Main function to demonstrate Palindrome Partitioning pattern
int main() {
    // Example 1: Palindrome Partitioning
    cout << "Example 1: Palindrome Partitioning" << endl;
    string s1 = "aab";
    cout << "String: " << s1 << endl;
    
    PalindromePartitioning pp;
    vector<vector<string>> partitions = pp.partition(s1);
    
    cout << "All possible palindrome partitioning:" << endl;
    print2DStringVector(partitions);
    
    // Example 2: Palindrome Partitioning II (Minimum Cuts)
    cout << "\nExample 2: Palindrome Partitioning II (Minimum Cuts)" << endl;
    string s2 = "aab";
    cout << "String: " << s2 << endl;
    
    PalindromePartitioningII pp2;
    int minCuts = pp2.minCut(s2);
    
    cout << "Minimum cuts needed: " << minCuts << endl;
    
    // Example 3: Palindrome Partitioning IV
    cout << "\nExample 3: Palindrome Partitioning IV" << endl;
    string s3 = "abcbdd";
    cout << "String: " << s3 << endl;
    
    PalindromePartitioningIV pp4;
    bool canPartition = pp4.checkPartitioning(s3);
    
    cout << "Can be partitioned into exactly 3 palindromes: " << (canPartition ? "true" : "false") << endl;
    
    // Example 4: Longest Palindromic Substring
    cout << "\nExample 4: Longest Palindromic Substring" << endl;
    string s4 = "babad";
    cout << "String: " << s4 << endl;
    
    LongestPalindromicSubstring lps;
    string longest = lps.longestPalindrome(s4);
    
    cout << "Longest palindromic substring: " << longest << endl;
    
    // Example 5: Palindromic Substrings
    cout << "\nExample 5: Palindromic Substrings" << endl;
    string s5 = "abc";
    cout << "String: " << s5 << endl;
    
    PalindromicSubstrings ps;
    int count = ps.countSubstrings(s5);
    
    cout << "Number of palindromic substrings: " << count << endl;
    
    // Example 6: Palindrome Permutation
    cout << "\nExample 6: Palindrome Permutation" << endl;
    string s6 = "aab";
    cout << "String: " << s6 << endl;
    
    PalindromePermutation ppm;
    bool canPermute = ppm.canPermutePalindrome(s6);
    
    cout << "Can permute to form a palindrome: " << (canPermute ? "true" : "false") << endl;
    
    if (canPermute) {
        vector<string> permutations = ppm.generatePalindromePermutations(s6);
        cout << "Palindrome permutations:" << endl;
        printStringVector(permutations);
    }
    
    return 0;
}
