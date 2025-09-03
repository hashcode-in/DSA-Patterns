/**
 * Pattern: DP - 2D Array (Longest Common Subsequence - LCS)
 * 
 * Description:
 * The Longest Common Subsequence (LCS) problem is a classic dynamic programming problem
 * that finds the longest subsequence common to two sequences. A subsequence is a sequence
 * that can be derived from another sequence by deleting some elements without changing
 * the order of the remaining elements.
 * 
 * Time Complexity: O(m*n) where m and n are the lengths of the two sequences
 * Space Complexity: O(m*n) for the 2D DP table, can be optimized to O(min(m,n)) in some cases
 * 
 * When to use:
 * - String comparison problems
 * - When you need to find similarities between sequences
 * - Sequence alignment problems (DNA/RNA alignment in bioinformatics)
 * - Basis for string edit distance or diff algorithms
 * 
 * LeetCode Problems:
 * - 1143. Longest Common Subsequence
 * - 583. Delete Operation for Two Strings
 * - 712. Minimum ASCII Delete Sum for Two Strings
 * - 1035. Uncrossed Lines
 * - 1092. Shortest Common Supersequence
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Basic Longest Common Subsequence
// LeetCode 1143: https://leetcode.com/problems/longest-common-subsequence/
class LongestCommonSubsequence {
public:
    // Approach 1: Bottom-up DP with 2D array
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // dp[i][j] = length of LCS of text1[0...i-1] and text2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    // If current characters match, extend the LCS
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // If current characters don't match, take the maximum of two options
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Approach 2: Space-optimized version with 1D array
    int longestCommonSubsequenceOptimized(string text1, string text2) {
        // Make text1 the shorter string to optimize space
        if (text1.length() > text2.length()) {
            swap(text1, text2);
        }
        
        int m = text1.length();
        int n = text2.length();
        
        // Use only two rows: current row and previous row
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            // Update previous row with current row
            prev = curr;
        }
        
        return prev[n];
    }
    
    // Approach 3: Print the LCS
    string getLCS(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // dp[i][j] = length of LCS of text1[0...i-1] and text2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Fill the dp table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Backtrack to find the LCS
        string lcs = "";
        int i = m, j = n;
        
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                // If characters match, include in LCS
                lcs = text1[i - 1] + lcs;
                i--; j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                // Move in the direction of larger value
                i--;
            } else {
                j--;
            }
        }
        
        return lcs;
    }
};

// Example 2: Delete Operation for Two Strings
// LeetCode 583: https://leetcode.com/problems/delete-operation-for-two-strings/
class DeleteOperationForTwoStrings {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // Find LCS length
        int lcsLength = longestCommonSubsequence(word1, word2);
        
        // Minimum deletions = (m - lcsLength) + (n - lcsLength)
        // m - lcsLength = chars to delete from word1
        // n - lcsLength = chars to delete from word2
        return m + n - 2 * lcsLength;
    }
    
    // Helper function to find LCS length
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Alternative approach: Direct DP for minimum deletions
    int minDistanceDirect(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[i][j] = min operations to make word1[0...i-1] and word2[0...j-1] equal
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;  // Delete all chars from word1
        }
        
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;  // Delete all chars from word2
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // If current characters match, no deletion needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Min of: Delete from word1, or Delete from word2
                    dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 3: Minimum ASCII Delete Sum for Two Strings
// LeetCode 712: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
class MinimumDeleteSum {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.length();
        int n = s2.length();
        
        // dp[i][j] = minimum ASCII sum of deleted characters to make s1[0...i-1] and s2[0...j-1] equal
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases
        // To make s1[0...i-1] equal to empty string, delete all characters in s1[0...i-1]
        for (int i = 1; i <= m; i++) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        
        // To make empty string equal to s2[0...j-1], delete all characters in s2[0...j-1]
        for (int j = 1; j <= n; j++) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    // If current characters match, no deletion needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Min of: Delete from s1, or Delete from s2
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1],  // Delete from s1
                                  dp[i][j - 1] + s2[j - 1]);  // Delete from s2
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 4: Uncrossed Lines
// LeetCode 1035: https://leetcode.com/problems/uncrossed-lines/
class UncrossedLines {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        // This problem is equivalent to finding the LCS of the two arrays
        // dp[i][j] = max number of uncrossed lines between nums1[0...i-1] and nums2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    // If current numbers match, connect with a line
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // If current numbers don't match, take the maximum from previous states
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 5: Shortest Common Supersequence
// LeetCode 1092: https://leetcode.com/problems/shortest-common-supersequence/
class ShortestCommonSupersequence {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();
        
        // First, find the LCS of str1 and str2
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Backtrack to construct the shortest common supersequence
        string result = "";
        int i = m, j = n;
        
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                // If characters match, include only once in the supersequence
                result = str1[i - 1] + result;
                i--; j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                // Include character from str1
                result = str1[i - 1] + result;
                i--;
            } else {
                // Include character from str2
                result = str2[j - 1] + result;
                j--;
            }
        }
        
        // Include remaining characters from str1
        while (i > 0) {
            result = str1[i - 1] + result;
            i--;
        }
        
        // Include remaining characters from str2
        while (j > 0) {
            result = str2[j - 1] + result;
            j--;
        }
        
        return result;
    }
};

// Example 6: Distinct Subsequences
// LeetCode 115: https://leetcode.com/problems/distinct-subsequences/
class DistinctSubsequences {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[i][j] = number of distinct subsequences of s[0...i-1] equal to t[0...j-1]
        // Use long to prevent integer overflow
        vector<vector<long>> dp(m + 1, vector<long>(n + 1, 0));
        
        // Empty string "" is a subsequence of any string with one occurrence
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    // If current characters match, we have two options:
                    // 1. Include current character: dp[i-1][j-1]
                    // 2. Exclude current character: dp[i-1][j]
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    // If current characters don't match, we can only exclude current character
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Space-optimized version
    int numDistinctOptimized(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // Use only one row
        vector<long> dp(n + 1, 0);
        dp[0] = 1;  // Empty string is a subsequence with one occurrence
        
        for (int i = 1; i <= m; i++) {
            // Process from right to left to avoid overwriting needed values
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] = dp[j - 1] + dp[j];
                }
                // If characters don't match, dp[j] remains unchanged
            }
        }
        
        return dp[n];
    }
};

// Example 7: Longest Common Substring
class LongestCommonSubstring {
public:
    int longestCommonSubstring(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // dp[i][j] = length of longest common substring ending at text1[i-1] and text2[j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        int maxLength = 0;
        int endIndex = 0;  // End index of LCS in text1
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endIndex = i - 1;
                    }
                }
                // If characters don't match, substring length is 0 (dp[i][j] remains 0)
            }
        }
        
        // Extract the longest common substring
        string lcs = text1.substr(endIndex - maxLength + 1, maxLength);
        
        return maxLength;
    }
    
    // Return the substring itself
    string getLongestCommonSubstring(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        int maxLength = 0;
        int endIndex = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endIndex = i - 1;
                    }
                }
            }
        }
        
        return text1.substr(endIndex - maxLength + 1, maxLength);
    }
};

// Main function to demonstrate Longest Common Subsequence pattern
int main() {
    // Example 1: Basic LCS
    cout << "Example 1: Longest Common Subsequence" << endl;
    string text1 = "abcde";
    string text2 = "ace";
    LongestCommonSubsequence solution1;
    
    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;
    
    int lcsLength = solution1.longestCommonSubsequence(text1, text2);
    cout << "Length of LCS: " << lcsLength << endl;
    
    string lcs = solution1.getLCS(text1, text2);
    cout << "LCS: " << lcs << endl;
    
    // Example 2: Delete Operation for Two Strings
    cout << "\nExample 2: Delete Operation for Two Strings" << endl;
    string word1 = "sea";
    string word2 = "eat";
    DeleteOperationForTwoStrings solution2;
    
    cout << "Word 1: " << word1 << endl;
    cout << "Word 2: " << word2 << endl;
    
    int minDeletions = solution2.minDistance(word1, word2);
    cout << "Minimum number of deletions: " << minDeletions << endl;
    
    // Example 3: Minimum ASCII Delete Sum
    cout << "\nExample 3: Minimum ASCII Delete Sum" << endl;
    string s1 = "delete";
    string s2 = "leet";
    MinimumDeleteSum solution3;
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    int minAsciiSum = solution3.minimumDeleteSum(s1, s2);
    cout << "Minimum ASCII sum of deleted characters: " << minAsciiSum << endl;
    
    // Example 4: Uncrossed Lines
    cout << "\nExample 4: Uncrossed Lines" << endl;
    vector<int> nums1 = {1, 4, 2};
    vector<int> nums2 = {1, 2, 4};
    UncrossedLines solution4;
    
    cout << "Array 1: [";
    for (int i = 0; i < nums1.size(); i++) {
        cout << nums1[i];
        if (i < nums1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Array 2: [";
    for (int i = 0; i < nums2.size(); i++) {
        cout << nums2[i];
        if (i < nums2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    int maxLines = solution4.maxUncrossedLines(nums1, nums2);
    cout << "Maximum number of uncrossed lines: " << maxLines << endl;
    
    // Example 5: Shortest Common Supersequence
    cout << "\nExample 5: Shortest Common Supersequence" << endl;
    string str1 = "abac";
    string str2 = "cab";
    ShortestCommonSupersequence solution5;
    
    cout << "String 1: " << str1 << endl;
    cout << "String 2: " << str2 << endl;
    
    string scs = solution5.shortestCommonSupersequence(str1, str2);
    cout << "Shortest Common Supersequence: " << scs << endl;
    
    // Example 6: Distinct Subsequences
    cout << "\nExample 6: Distinct Subsequences" << endl;
    string s = "rabbbit";
    string t = "rabbit";
    DistinctSubsequences solution6;
    
    cout << "String s: " << s << endl;
    cout << "String t: " << t << endl;
    
    int distinctCount = solution6.numDistinct(s, t);
    cout << "Number of distinct subsequences: " << distinctCount << endl;
    
    // Example 7: Longest Common Substring
    cout << "\nExample 7: Longest Common Substring" << endl;
    string text1_7 = "ABCDEF";
    string text2_7 = "XYZABCDE";
    LongestCommonSubstring solution7;
    
    cout << "Text 1: " << text1_7 << endl;
    cout << "Text 2: " << text2_7 << endl;
    
    int lcSubstringLength = solution7.longestCommonSubstring(text1_7, text2_7);
    string lcSubstring = solution7.getLongestCommonSubstring(text1_7, text2_7);
    
    cout << "Length of Longest Common Substring: " << lcSubstringLength << endl;
    cout << "Longest Common Substring: " << lcSubstring << endl;
    
    return 0;
}
