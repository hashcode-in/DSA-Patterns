/**
 * Pattern: DP - 2D Array (Edit Distance / Levenshtein Distance)
 * 
 * Description:
 * The Edit Distance problem calculates the minimum number of operations required to transform
 * one string into another. The allowed operations are:
 * 1. Insert a character
 * 2. Delete a character
 * 3. Replace/Substitute a character
 * 
 * Time Complexity: O(m*n) where m and n are the lengths of the two strings
 * Space Complexity: O(m*n) for the 2D DP table, can be optimized to O(min(m,n)) in some cases
 * 
 * When to use:
 * - String transformation problems
 * - Spell checking and correction
 * - DNA sequence alignment
 * - Plagiarism detection
 * - Text similarity measurement
 * 
 * LeetCode Problems:
 * - 72. Edit Distance
 * - 161. One Edit Distance
 * - 583. Delete Operation for Two Strings (variation using only deletions)
 * - 1035. Uncrossed Lines (variation of Longest Common Subsequence)
 * - 44. Wildcard Matching (variation with wildcard characters)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Basic Edit Distance (Levenshtein Distance)
// LeetCode 72: https://leetcode.com/problems/edit-distance/
class EditDistance {
public:
    // Approach 1: Bottom-up DP with 2D array
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[i][j] = min operations to convert word1[0...i-1] to word2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases: transforming to empty string (delete all characters)
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        
        // Base cases: transforming from empty string (insert all characters)
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // If current characters match, no operation needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Min of three operations:
                    // 1. Replace: dp[i-1][j-1] + 1
                    // 2. Delete: dp[i-1][j] + 1
                    // 3. Insert: dp[i][j-1] + 1
                    dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Approach 2: Space-optimized version with 1D array
    int minDistanceOptimized(string word1, string word2) {
        // Make word1 the shorter string to optimize space
        if (word1.length() > word2.length()) {
            swap(word1, word2);
        }
        
        int m = word1.length();
        int n = word2.length();
        
        // Use only two rows: current row and previous row
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);
        
        // Initialize the previous row (base case)
        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }
        
        for (int i = 1; i <= m; i++) {
            // First element of current row is always i
            curr[0] = i;
            
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + min({prev[j - 1], prev[j], curr[j - 1]});
                }
            }
            
            // Update previous row with current row
            prev = curr;
        }
        
        return prev[n];
    }
    
    // Approach 3: Backtrace to find the operations
    vector<string> getEditOperations(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[i][j] = min operations to convert word1[0...i-1] to word2[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Initialize base cases
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        // Fill the dp table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                }
            }
        }
        
        // Backtrace to find operations
        vector<string> operations;
        int i = m, j = n;
        
        while (i > 0 || j > 0) {
            // If characters match, no operation needed
            if (i > 0 && j > 0 && word1[i - 1] == word2[j - 1]) {
                i--; j--;
                continue;
            }
            
            // Find which operation was chosen
            if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
                // Replace operation
                operations.push_back("Replace " + string(1, word1[i - 1]) + " with " + string(1, word2[j - 1]));
                i--; j--;
            } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
                // Delete operation
                operations.push_back("Delete " + string(1, word1[i - 1]));
                i--;
            } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
                // Insert operation
                operations.push_back("Insert " + string(1, word2[j - 1]));
                j--;
            }
        }
        
        // Reverse the operations to get them in correct order
        reverse(operations.begin(), operations.end());
        return operations;
    }
};

// Example 2: One Edit Distance
// LeetCode 161: https://leetcode.com/problems/one-edit-distance/
class OneEditDistance {
public:
    // Check if two strings are one edit distance apart
    bool isOneEditDistance(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // If lengths differ by more than 1, they cannot be one edit distance apart
        if (abs(m - n) > 1) {
            return false;
        }
        
        // Make s the shorter string
        if (m > n) {
            swap(s, t);
            swap(m, n);
        }
        
        // If lengths are equal, check for one replacement
        if (m == n) {
            int differences = 0;
            for (int i = 0; i < m; i++) {
                if (s[i] != t[i]) {
                    differences++;
                }
                if (differences > 1) {
                    return false;
                }
            }
            // If no differences, strings are identical (not one edit distance apart)
            return differences == 1;
        } else {
            // If lengths differ by 1, check for one insertion
            int i = 0, j = 0;
            while (i < m && j < n) {
                if (s[i] != t[j]) {
                    if (i != j) {
                        return false;  // More than one difference
                    }
                    j++;  // Skip current character in t
                } else {
                    i++;
                    j++;
                }
            }
            return true;  // One insertion is needed
        }
    }
};

// Example 3: Delete Operation for Two Strings
// LeetCode 583: https://leetcode.com/problems/delete-operation-for-two-strings/
class DeleteOperationForTwoStrings {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // dp[i][j] = min deletions to make word1[0...i-1] and word2[0...j-1] equal
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases: deletions needed to match empty string
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
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
    
    // Alternative approach: Using Longest Common Subsequence
    int minDistanceLCS(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        // Find LCS length
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int lcsLength = dp[m][n];
        
        // Minimum deletions = (m - lcsLength) + (n - lcsLength)
        return m + n - 2 * lcsLength;
    }
};

// Example 4: Wildcard Matching
// LeetCode 44: https://leetcode.com/problems/wildcard-matching/
class WildcardMatching {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        
        // dp[i][j] = true if s[0...i-1] matches p[0...j-1]
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        // Empty pattern matches empty string
        dp[0][0] = true;
        
        // Empty string matches pattern with all '*'
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // '*' can match empty string (dp[i][j-1]) or
                    // match the current character and continue (dp[i-1][j])
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    // '?' matches any single character, or exact character match
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Greedy approach with two pointers
    bool isMatchGreedy(string s, string p) {
        int sIndex = 0, pIndex = 0;
        int sStar = -1, pStar = -1;
        int m = s.length(), n = p.length();
        
        while (sIndex < m) {
            // If pattern matches current character or '?'
            if (pIndex < n && (p[pIndex] == '?' || p[pIndex] == s[sIndex])) {
                sIndex++;
                pIndex++;
            }
            // If '*' found in pattern, mark the position
            else if (pIndex < n && p[pIndex] == '*') {
                sStar = sIndex;  // Mark current string position
                pStar = pIndex;  // Mark '*' position
                pIndex++;  // Move pattern pointer past '*'
            }
            // If mismatch after '*', reset pattern pointer to after '*'
            // and string pointer to next position after last match
            else if (pStar != -1) {
                pIndex = pStar + 1;
                sStar++;
                sIndex = sStar;
            }
            // If no match and no '*', return false
            else {
                return false;
            }
        }
        
        // Skip remaining '*' in pattern
        while (pIndex < n && p[pIndex] == '*') {
            pIndex++;
        }
        
        return pIndex == n;  // Check if we've used the entire pattern
    }
};

// Example 5: Regular Expression Matching
// LeetCode 10: https://leetcode.com/problems/regular-expression-matching/
class RegexMatching {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        
        // dp[i][j] = true if s[0...i-1] matches p[0...j-1]
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        // Empty pattern matches empty string
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, a*b*c*
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];  // Empty string matches X* by ignoring X*
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // Two cases:
                    // 1. Ignore X* (e.g., for "ab" and "abc*", ignore c*)
                    dp[i][j] = dp[i][j - 2];
                    
                    // 2. Match X* multiple times if current character matches X or X is '.'
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    // Match single character
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 6: Edit Distance with Real Words (Spell Checker)
class SpellChecker {
public:
    SpellChecker(const vector<string>& dictionary) : dict(dictionary) {}
    
    // Find closest word in dictionary using edit distance
    string findClosestWord(const string& word) {
        int minDistance = INT_MAX;
        string closestWord = "";
        
        for (const string& dictWord : dict) {
            int distance = editDistance(word, dictWord);
            if (distance < minDistance) {
                minDistance = distance;
                closestWord = dictWord;
            }
        }
        
        return closestWord;
    }
    
    // Get suggestions within a certain edit distance threshold
    vector<string> getSuggestions(const string& word, int threshold = 2) {
        vector<string> suggestions;
        
        for (const string& dictWord : dict) {
            int distance = editDistance(word, dictWord);
            if (distance <= threshold) {
                suggestions.push_back(dictWord);
            }
        }
        
        // Sort suggestions by edit distance (closer words first)
        sort(suggestions.begin(), suggestions.end(), 
            [&](const string& a, const string& b) {
                return editDistance(word, a) < editDistance(word, b);
            });
        
        return suggestions;
    }
    
private:
    vector<string> dict;
    
    // Helper function to calculate edit distance
    int editDistance(const string& s, const string& t) {
        int m = s.length();
        int n = t.length();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                }
            }
        }
        
        return dp[m][n];
    }
};

// Example 7: Damerau-Levenshtein Distance (Edit Distance with Transpositions)
class DamerauLevenshteinDistance {
public:
    // Calculate edit distance allowing transpositions (swapping adjacent characters)
    int distance(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[i][j] = min operations to convert s[0...i-1] to t[0...j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Standard edit operations (insert, delete, replace)
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                    
                    // Check for transposition (if we're at least at position 2 in both strings)
                    if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1]) {
                        dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1);
                    }
                }
            }
        }
        
        return dp[m][n];
    }
};

// Main function to demonstrate Edit Distance pattern
int main() {
    // Example 1: Basic Edit Distance
    cout << "Example 1: Edit Distance" << endl;
    string word1 = "horse";
    string word2 = "ros";
    EditDistance solution1;
    
    cout << "Word 1: " << word1 << endl;
    cout << "Word 2: " << word2 << endl;
    
    int minEdits = solution1.minDistance(word1, word2);
    cout << "Minimum edit distance: " << minEdits << endl;
    
    vector<string> operations = solution1.getEditOperations(word1, word2);
    cout << "Edit operations:" << endl;
    for (const string& op : operations) {
        cout << "  " << op << endl;
    }
    
    // Example 2: One Edit Distance
    cout << "\nExample 2: One Edit Distance" << endl;
    string s1 = "ab";
    string s2 = "acb";
    OneEditDistance solution2;
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    bool isOneEdit = solution2.isOneEditDistance(s1, s2);
    cout << "Is one edit distance apart? " << (isOneEdit ? "Yes" : "No") << endl;
    
    // Example 3: Delete Operation for Two Strings
    cout << "\nExample 3: Delete Operation for Two Strings" << endl;
    string word3 = "sea";
    string word4 = "eat";
    DeleteOperationForTwoStrings solution3;
    
    cout << "Word 1: " << word3 << endl;
    cout << "Word 2: " << word4 << endl;
    
    int minDeletions = solution3.minDistance(word3, word4);
    cout << "Minimum number of deletions: " << minDeletions << endl;
    
    int minDeletionsLCS = solution3.minDistanceLCS(word3, word4);
    cout << "Minimum number of deletions (using LCS): " << minDeletionsLCS << endl;
    
    // Example 4: Wildcard Matching
    cout << "\nExample 4: Wildcard Matching" << endl;
    string s3 = "adceb";
    string p1 = "*a*b";
    WildcardMatching solution4;
    
    cout << "String: " << s3 << endl;
    cout << "Pattern: " << p1 << endl;
    
    bool matchesWildcard = solution4.isMatch(s3, p1);
    cout << "Matches wildcard pattern? " << (matchesWildcard ? "Yes" : "No") << endl;
    
    // Example 5: Regular Expression Matching
    cout << "\nExample 5: Regular Expression Matching" << endl;
    string s4 = "aab";
    string p2 = "c*a*b";
    RegexMatching solution5;
    
    cout << "String: " << s4 << endl;
    cout << "Pattern: " << p2 << endl;
    
    bool matchesRegex = solution5.isMatch(s4, p2);
    cout << "Matches regex pattern? " << (matchesRegex ? "Yes" : "No") << endl;
    
    // Example 6: Spell Checker
    cout << "\nExample 6: Spell Checker" << endl;
    vector<string> dictionary = {"hello", "world", "algorithm", "programming", "computer", "science"};
    string misspelled = "progamming";
    SpellChecker solution6(dictionary);
    
    cout << "Dictionary: [";
    for (int i = 0; i < dictionary.size(); i++) {
        cout << "\"" << dictionary[i] << "\"";
        if (i < dictionary.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Misspelled word: " << misspelled << endl;
    
    string closestWord = solution6.findClosestWord(misspelled);
    cout << "Closest word: " << closestWord << endl;
    
    vector<string> suggestions = solution6.getSuggestions(misspelled, 2);
    cout << "Suggestions (edit distance <= 2): [";
    for (int i = 0; i < suggestions.size(); i++) {
        cout << "\"" << suggestions[i] << "\"";
        if (i < suggestions.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 7: Damerau-Levenshtein Distance
    cout << "\nExample 7: Damerau-Levenshtein Distance" << endl;
    string s5 = "abcd";
    string s6 = "acbd";  // 'b' and 'c' are transposed
    DamerauLevenshteinDistance solution7;
    
    cout << "String 1: " << s5 << endl;
    cout << "String 2: " << s6 << endl;
    
    int damerauDist = solution7.distance(s5, s6);
    cout << "Damerau-Levenshtein distance: " << damerauDist << endl;
    
    return 0;
}
