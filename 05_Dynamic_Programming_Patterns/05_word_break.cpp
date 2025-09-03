/**
 * Pattern: DP - 1D Array (Word Break Style)
 * 
 * Description:
 * The Word Break pattern involves determining if a string can be segmented into a sequence of
 * dictionary words. It's characterized by using dynamic programming to build up the solution
 * from smaller subproblems, where each subproblem asks whether a substring can be segmented.
 * 
 * Time Complexity: O(n²) where n is the length of the input string
 * Space Complexity: O(n) for the DP array + additional space for the dictionary
 * 
 * When to use:
 * - String segmentation problems (can a string be broken into valid parts)
 * - Word-related problems with dictionary lookups
 * - Problems involving constructing sequences from a given set of building blocks
 * 
 * LeetCode Problems:
 * - 139. Word Break
 * - 140. Word Break II
 * - 472. Concatenated Words
 * - 79. Word Search (variation using backtracking)
 * - 212. Word Search II (Trie + backtracking variation)
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

// Example 1: Word Break
// LeetCode 139: https://leetcode.com/problems/word-break/
class WordBreak {
public:
    // Approach 1: Dynamic Programming (Bottom-up)
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // dp[i] = true if the substring s[0...i-1] can be segmented into dictionary words
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // Empty string can always be segmented
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // If the substring s[0...j-1] can be segmented and s[j...i-1] is in dictionary
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
    
    // Approach 2: Dynamic Programming with length optimization
    bool wordBreakOptimized(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // Find maximum word length in dictionary
        int maxWordLen = 0;
        for (const string& word : wordDict) {
            maxWordLen = max(maxWordLen, (int)word.length());
        }
        
        // dp[i] = true if the substring s[0...i-1] can be segmented into dictionary words
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // Empty string can always be segmented
        
        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= 0 && j >= i - maxWordLen; j--) {
                // If the substring s[0...j-1] can be segmented and s[j...i-1] is in dictionary
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
    
    // Approach 3: Memoization (Top-down)
    bool wordBreakMemo(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, bool> memo;
        return dfs(s, dict, 0, memo);
    }
    
    bool dfs(const string& s, const unordered_set<string>& dict, int start, unordered_map<int, bool>& memo) {
        if (start == s.length()) {
            return true;
        }
        
        if (memo.count(start)) {
            return memo[start];
        }
        
        for (int end = start + 1; end <= s.length(); end++) {
            if (dict.count(s.substr(start, end - start)) && dfs(s, dict, end, memo)) {
                memo[start] = true;
                return true;
            }
        }
        
        memo[start] = false;
        return false;
    }
    
    // Approach 4: BFS
    bool wordBreakBFS(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // queue to keep track of all valid starting points
        queue<int> q;
        q.push(0);
        
        // visited array to avoid revisiting same positions
        vector<bool> visited(n, false);
        
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            
            if (start == n) {
                return true;
            }
            
            if (visited[start]) {
                continue;
            }
            
            visited[start] = true;
            
            for (int end = start + 1; end <= n; end++) {
                if (dict.count(s.substr(start, end - start))) {
                    q.push(end);
                }
            }
        }
        
        return false;
    }
};

// Example 2: Word Break II
// LeetCode 140: https://leetcode.com/problems/word-break-ii/
class WordBreakII {
public:
    // Helper function for memoization
    vector<string> wordBreakDFS(const string& s, const unordered_set<string>& wordDict, 
                               unordered_map<string, vector<string>>& memo) {
        // Check if we've already solved this subproblem
        if (memo.count(s)) {
            return memo[s];
        }
        
        vector<string> result;
        
        // Base case: empty string
        if (s.empty()) {
            result.push_back("");
            return result;
        }
        
        // Try all possible prefixes
        for (int i = 1; i <= s.length(); i++) {
            string prefix = s.substr(0, i);
            
            // If prefix is in dictionary, recursively solve for suffix
            if (wordDict.count(prefix)) {
                string suffix = s.substr(i);
                vector<string> subResult = wordBreakDFS(suffix, wordDict, memo);
                
                // Combine prefix with each result from suffix
                for (const string& sub : subResult) {
                    result.push_back(prefix + (sub.empty() ? "" : " " + sub));
                }
            }
        }
        
        // Memoize and return
        memo[s] = result;
        return result;
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<string, vector<string>> memo;
        
        return wordBreakDFS(s, dict, memo);
    }
    
    // Approach 2: DP + Backtracking
    vector<string> wordBreakDPBacktracking(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // dp[i] = true if the substring s[0...i-1] can be segmented into dictionary words
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // Empty string can always be segmented
        
        // First check if string can be segmented at all
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        // If string cannot be segmented, return empty result
        if (!dp[n]) {
            return {};
        }
        
        // Backtracking to find all valid segmentations
        vector<string> result;
        vector<string> current;
        backtrack(s, dict, 0, current, result);
        
        return result;
    }
    
    void backtrack(const string& s, const unordered_set<string>& dict, int start, 
                  vector<string>& current, vector<string>& result) {
        if (start == s.length()) {
            // Join words with spaces
            string sentence;
            for (int i = 0; i < current.size(); i++) {
                sentence += current[i];
                if (i < current.size() - 1) {
                    sentence += " ";
                }
            }
            result.push_back(sentence);
            return;
        }
        
        for (int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            if (dict.count(word)) {
                current.push_back(word);
                backtrack(s, dict, end, current, result);
                current.pop_back();  // Backtrack
            }
        }
    }
};

// Example 3: Concatenated Words
// LeetCode 472: https://leetcode.com/problems/concatenated-words/
class ConcatenatedWords {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        // Sort words by length (this is important for the correctness of the algorithm)
        sort(words.begin(), words.end(), 
            [](const string& a, const string& b) { return a.length() < b.length(); });
        
        vector<string> result;
        unordered_set<string> wordSet; // Dictionary of known words
        
        for (const string& word : words) {
            // Skip empty words
            if (word.empty()) {
                continue;
            }
            
            // Check if current word can be formed by concatenating other words
            if (canFormWord(word, wordSet)) {
                result.push_back(word);
            }
            
            // Add current word to the dictionary
            wordSet.insert(word);
        }
        
        return result;
    }
    
    bool canFormWord(const string& word, const unordered_set<string>& wordSet) {
        if (wordSet.empty()) {
            return false;
        }
        
        int n = word.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // Empty string can be formed
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // Check if substring s[j...i-1] is in wordSet and s[0...j-1] can be formed
                if (dp[j] && wordSet.count(word.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};

// Example 4: Palindrome Partitioning (similar to Word Break but with palindrome check)
// LeetCode 131: https://leetcode.com/problems/palindrome-partitioning/
class PalindromePartitioning {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        
        // Pre-compute palindrome information: isPalindrome[i][j] = true if s[i...j] is a palindrome
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        
        // All substrings of length 1 are palindromes
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        
        // Check for palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                isPalindrome[i][i + 1] = true;
            }
        }
        
        // Check for palindromes of length > 2
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && isPalindrome[i + 1][j - 1]) {
                    isPalindrome[i][j] = true;
                }
            }
        }
        
        // Use backtracking to find all partitions
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, isPalindrome, current, result);
        
        return result;
    }
    
    void backtrack(const string& s, int start, const vector<vector<bool>>& isPalindrome, 
                  vector<string>& current, vector<vector<string>>& result) {
        if (start == s.length()) {
            result.push_back(current);
            return;
        }
        
        for (int end = start; end < s.length(); end++) {
            if (isPalindrome[start][end]) {
                current.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, isPalindrome, current, result);
                current.pop_back();  // Backtrack
            }
        }
    }
};

// Example 5: Word Pattern II (similar to Word Break but with pattern matching)
class WordPatternII {
public:
    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> charToStr;
        unordered_set<string> usedStrs;
        
        return backtrack(pattern, 0, s, 0, charToStr, usedStrs);
    }
    
    bool backtrack(const string& pattern, int pIdx, const string& s, int sIdx,
                  unordered_map<char, string>& charToStr,
                  unordered_set<string>& usedStrs) {
        // Base case: both pattern and string are consumed
        if (pIdx == pattern.length() && sIdx == s.length()) {
            return true;
        }
        
        // If one is consumed but the other is not, they don't match
        if (pIdx == pattern.length() || sIdx == s.length()) {
            return false;
        }
        
        char currentChar = pattern[pIdx];
        
        // If the current character already has a mapping
        if (charToStr.count(currentChar)) {
            string mappedStr = charToStr[currentChar];
            int len = mappedStr.length();
            
            // Check if the mapped string matches the current position in s
            if (sIdx + len > s.length() || s.substr(sIdx, len) != mappedStr) {
                return false;
            }
            
            // Continue with the next character in pattern
            return backtrack(pattern, pIdx + 1, s, sIdx + len, charToStr, usedStrs);
        }
        
        // Try all possible substrings
        for (int len = 1; sIdx + len <= s.length(); len++) {
            string substr = s.substr(sIdx, len);
            
            // Skip if the string is already mapped to a different character
            if (usedStrs.count(substr)) {
                continue;
            }
            
            // Create a mapping and mark the string as used
            charToStr[currentChar] = substr;
            usedStrs.insert(substr);
            
            // Continue with the next character in pattern
            if (backtrack(pattern, pIdx + 1, s, sIdx + len, charToStr, usedStrs)) {
                return true;
            }
            
            // Backtrack
            usedStrs.erase(substr);
            charToStr.erase(currentChar);
        }
        
        return false;
    }
};

// Example 6: Regular Expression Matching (similar concept with pattern matching)
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

// Example 7: Restore IP Addresses
// LeetCode 93: https://leetcode.com/problems/restore-ip-addresses/
class RestoreIPAddresses {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> current;
        
        backtrack(s, 0, 0, current, result);
        
        return result;
    }
    
    void backtrack(const string& s, int start, int segmentCount, 
                  vector<string>& current, vector<string>& result) {
        // If we've formed 4 segments and used all characters
        if (segmentCount == 4 && start == s.length()) {
            result.push_back(current[0] + "." + current[1] + "." + 
                            current[2] + "." + current[3]);
            return;
        }
        
        // If we've formed 4 segments but haven't used all characters,
        // or we've used all characters but haven't formed 4 segments
        if (segmentCount == 4 || start == s.length()) {
            return;
        }
        
        // Try segments of different lengths
        for (int len = 1; len <= 3 && start + len <= s.length(); len++) {
            string segment = s.substr(start, len);
            
            // Skip segments with leading zeros (except "0" itself)
            if (len > 1 && segment[0] == '0') {
                continue;
            }
            
            // Skip segments that are out of range (0-255)
            if (len == 3 && stoi(segment) > 255) {
                continue;
            }
            
            current.push_back(segment);
            backtrack(s, start + len, segmentCount + 1, current, result);
            current.pop_back();  // Backtrack
        }
    }
};

// Main function to demonstrate Word Break pattern
int main() {
    // Example 1: Word Break
    cout << "Example 1: Word Break" << endl;
    string s1 = "leetcode";
    vector<string> wordDict1 = {"leet", "code"};
    WordBreak solution1;
    
    cout << "String: " << s1 << endl;
    cout << "Dictionary: [";
    for (int i = 0; i < wordDict1.size(); i++) {
        cout << "\"" << wordDict1[i] << "\"";
        if (i < wordDict1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    bool canBreak = solution1.wordBreak(s1, wordDict1);
    cout << "Can break? " << (canBreak ? "Yes" : "No") << endl;
    
    // Example 2: Word Break II
    cout << "\nExample 2: Word Break II" << endl;
    string s2 = "catsanddog";
    vector<string> wordDict2 = {"cat", "cats", "and", "sand", "dog"};
    WordBreakII solution2;
    
    cout << "String: " << s2 << endl;
    cout << "Dictionary: [";
    for (int i = 0; i < wordDict2.size(); i++) {
        cout << "\"" << wordDict2[i] << "\"";
        if (i < wordDict2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    vector<string> sentences = solution2.wordBreak(s2, wordDict2);
    cout << "All possible sentences:" << endl;
    for (const string& sentence : sentences) {
        cout << "  " << sentence << endl;
    }
    
    // Example 3: Concatenated Words
    cout << "\nExample 3: Concatenated Words" << endl;
    vector<string> words = {"cat", "cats", "catsdogcats", "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat"};
    ConcatenatedWords solution3;
    
    cout << "Words: [";
    for (int i = 0; i < words.size(); i++) {
        cout << "\"" << words[i] << "\"";
        if (i < words.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    vector<string> concatenatedWords = solution3.findAllConcatenatedWordsInADict(words);
    cout << "Concatenated words:" << endl;
    for (const string& word : concatenatedWords) {
        cout << "  " << word << endl;
    }
    
    // Example 4: Palindrome Partitioning
    cout << "\nExample 4: Palindrome Partitioning" << endl;
    string s4 = "aab";
    PalindromePartitioning solution4;
    
    cout << "String: " << s4 << endl;
    
    vector<vector<string>> partitions = solution4.partition(s4);
    cout << "All possible partitions:" << endl;
    for (const auto& partition : partitions) {
        cout << "  [";
        for (int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if (i < partition.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    // Example 5: Word Pattern II
    cout << "\nExample 5: Word Pattern II" << endl;
    string pattern = "abab";
    string s5 = "redblueredblue";
    WordPatternII solution5;
    
    cout << "Pattern: " << pattern << endl;
    cout << "String: " << s5 << endl;
    
    bool matches = solution5.wordPatternMatch(pattern, s5);
    cout << "Pattern matches? " << (matches ? "Yes" : "No") << endl;
    
    // Example 6: Regular Expression Matching
    cout << "\nExample 6: Regular Expression Matching" << endl;
    string s6 = "aa";
    string p6 = "a*";
    RegexMatching solution6;
    
    cout << "String: " << s6 << endl;
    cout << "Pattern: " << p6 << endl;
    
    bool regexMatches = solution6.isMatch(s6, p6);
    cout << "Regex matches? " << (regexMatches ? "Yes" : "No") << endl;
    
    // Example 7: Restore IP Addresses
    cout << "\nExample 7: Restore IP Addresses" << endl;
    string s7 = "25525511135";
    RestoreIPAddresses solution7;
    
    cout << "String: " << s7 << endl;
    
    vector<string> ipAddresses = solution7.restoreIpAddresses(s7);
    cout << "Valid IP addresses:" << endl;
    for (const string& ip : ipAddresses) {
        cout << "  " << ip << endl;
    }
    
    return 0;
}
