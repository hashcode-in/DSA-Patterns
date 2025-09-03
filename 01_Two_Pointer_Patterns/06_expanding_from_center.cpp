/**
 * Pattern: Two Pointers - Expanding From Center (Palindromes)
 * 
 * Description:
 * This pattern uses two pointers that start at the same position (or adjacent positions)
 * and expand outward in opposite directions. This approach is particularly useful for 
 * finding palindromic structures in strings or arrays, where we need to check elements
 * that are equidistant from a center point.
 * 
 * Time Complexity: O(n²) - where n is the length of the string/array
 * Space Complexity: O(1) - only requires a constant amount of extra space
 * 
 * When to use:
 * - Finding palindromic substrings or subsequences
 * - Determining the longest palindrome in a string
 * - Checking if a string can be made into a palindrome
 * - Problems involving symmetric structures around a center point
 * 
 * LeetCode Problems:
 * - 5. Longest Palindromic Substring
 * - 647. Palindromic Substrings
 * - 680. Valid Palindrome II (variation)
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// Example 1: Longest Palindromic Substring
// LeetCode 5: https://leetcode.com/problems/longest-palindromic-substring/
string longestPalindromicSubstring(string s) {
    if (s.empty() || s.length() == 1) {
        return s;
    }
    
    int start = 0; // Start index of the longest palindromic substring
    int maxLength = 1; // Length of the longest palindromic substring
    
    // Helper function to expand around center
    auto expandAroundCenter = [&s](int left, int right) -> pair<int, int> {
        // Expand as long as we're within bounds and characters match
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        
        // Return the start index and length of palindrome
        return {left + 1, right - left - 1};
    };
    
    // Check each potential center position
    for (int i = 0; i < s.length(); i++) {
        // For odd length palindromes (single character center)
        auto [oddStart, oddLength] = expandAroundCenter(i, i);
        
        // For even length palindromes (between two characters)
        auto [evenStart, evenLength] = expandAroundCenter(i, i + 1);
        
        // Update if we found a longer palindrome
        if (oddLength > maxLength) {
            start = oddStart;
            maxLength = oddLength;
        }
        
        if (evenLength > maxLength) {
            start = evenStart;
            maxLength = evenLength;
        }
    }
    
    return s.substr(start, maxLength);
}

// Example 2: Count Palindromic Substrings
// LeetCode 647: https://leetcode.com/problems/palindromic-substrings/
int countPalindromicSubstrings(string s) {
    int n = s.length();
    int count = 0;
    
    // Helper function to expand around center and count palindromes
    auto expandAroundCenter = [&s, &count](int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++; // Found a palindrome
            left--;
            right++;
        }
    };
    
    for (int i = 0; i < n; i++) {
        // Odd length palindromes (single character center)
        expandAroundCenter(i, i);
        
        // Even length palindromes (between two characters)
        expandAroundCenter(i, i + 1);
    }
    
    return count;
}

// Example 3: Check if a string is a palindrome
bool isPalindrome(const string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

// Example 4: Valid Palindrome II (can remove at most one character)
// LeetCode 680: https://leetcode.com/problems/valid-palindrome-ii/
bool validPalindromeII(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    // Helper function to check if substring is a palindrome
    auto isPalindromeRange = [&s](int start, int end) -> bool {
        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    };
    
    // Main two-pointer traversal
    while (left < right) {
        if (s[left] != s[right]) {
            // Try both possibilities: skip left char or skip right char
            return isPalindromeRange(left + 1, right) || 
                   isPalindromeRange(left, right - 1);
        }
        left++;
        right--;
    }
    
    return true; // Already a palindrome
}

// Example 5: Longest Palindromic Subsequence
// LeetCode 516: https://leetcode.com/problems/longest-palindromic-subsequence/
// Note: This is usually solved with DP, but here's a simplified brute force approach using the pattern
int longestPalindromeSubseq(string s) {
    // This is a naive recursive implementation using the expanding from center concept
    // For a real solution, you'd use dynamic programming which is much more efficient
    
    function<int(int, int)> expandAndFind = [&](int left, int right) -> int {
        // Base case: single character
        if (left == right) return 1;
        
        // Base case: empty substring
        if (left > right) return 0;
        
        // If characters at both ends match, include them and look inside
        if (s[left] == s[right]) {
            // If there's only two characters that match
            if (left + 1 == right) return 2;
            
            // Otherwise include both and expand inward
            return 2 + expandAndFind(left + 1, right - 1);
        }
        
        // Characters don't match, try both possibilities and take the best
        return max(expandAndFind(left + 1, right), expandAndFind(left, right - 1));
    };
    
    return expandAndFind(0, s.length() - 1);
}

// Example 6: Find All Palindromic Substrings
vector<string> findAllPalindromicSubstrings(string s) {
    vector<string> result;
    int n = s.length();
    
    // Helper function to expand around center and collect palindromes
    auto expandAroundCenter = [&s, &result](int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            result.push_back(s.substr(left, right - left + 1));
            left--;
            right++;
        }
    };
    
    for (int i = 0; i < n; i++) {
        // Odd length palindromes (single character center)
        expandAroundCenter(i, i);
        
        // Even length palindromes (between two characters)
        expandAroundCenter(i, i + 1);
    }
    
    return result;
}

// Example 7: Manacher's Algorithm for Linear Time Palindrome Finding
// This is an advanced application of the expanding from center pattern
string manachersAlgorithm(string s) {
    if (s.empty()) return "";
    
    // Preprocess the string to handle even length palindromes
    string processedString = "#";
    for (char c : s) {
        processedString += c;
        processedString += "#";
    }
    
    int n = processedString.length();
    vector<int> palindromeLengths(n, 0); // Store radius of palindrome centered at each position
    
    int center = 0;      // Current center of palindrome
    int rightBoundary = 0; // Right boundary of current palindrome
    
    int maxCenter = 0;   // Center of the longest palindrome found
    int maxLength = 0;   // Length of the longest palindrome found
    
    for (int i = 0; i < n; i++) {
        // If within right boundary, use symmetry property
        if (i < rightBoundary) {
            int mirror = 2 * center - i; // Mirror position
            palindromeLengths[i] = min(rightBoundary - i, palindromeLengths[mirror]);
        }
        
        // Expand around current position
        int left = i - (palindromeLengths[i] + 1);
        int right = i + (palindromeLengths[i] + 1);
        
        // Continue expansion as far as possible
        while (left >= 0 && right < n && processedString[left] == processedString[right]) {
            palindromeLengths[i]++;
            left--;
            right++;
        }
        
        // Update center and right boundary if this palindrome extends further
        if (i + palindromeLengths[i] > rightBoundary) {
            center = i;
            rightBoundary = i + palindromeLengths[i];
        }
        
        // Track the longest palindrome
        if (palindromeLengths[i] > maxLength) {
            maxLength = palindromeLengths[i];
            maxCenter = i;
        }
    }
    
    // Extract the longest palindromic substring from the original string
    int start = (maxCenter - maxLength) / 2; // Convert back to original string index
    return s.substr(start, maxLength);
}

// Main function to demonstrate the Expanding From Center pattern
void demonstrateExpandingFromCenter() {
    cout << "Example 1: Longest Palindromic Substring" << endl;
    string s1 = "babad";
    cout << "Input string: " << s1 << endl;
    cout << "Longest palindromic substring: " << longestPalindromicSubstring(s1) << endl;
    
    cout << "\nExample 2: Count Palindromic Substrings" << endl;
    string s2 = "aaa";
    cout << "Input string: " << s2 << endl;
    cout << "Number of palindromic substrings: " << countPalindromicSubstrings(s2) << endl;
    
    cout << "\nExample 3: Check if a string is a palindrome" << endl;
    string s3 = "racecar";
    cout << "Input string: " << s3 << endl;
    cout << "Is palindrome: " << (isPalindrome(s3) ? "true" : "false") << endl;
    
    cout << "\nExample 4: Valid Palindrome II" << endl;
    string s4 = "abca";
    cout << "Input string: " << s4 << endl;
    cout << "Can be a palindrome by removing at most one character: " << (validPalindromeII(s4) ? "true" : "false") << endl;
    
    cout << "\nExample 5: Longest Palindromic Subsequence" << endl;
    string s5 = "bbbab";
    cout << "Input string: " << s5 << endl;
    cout << "Length of longest palindromic subsequence: " << longestPalindromeSubseq(s5) << endl;
    
    cout << "\nExample 6: Find All Palindromic Substrings" << endl;
    string s6 = "abc";
    cout << "Input string: " << s6 << endl;
    vector<string> palindromes = findAllPalindromicSubstrings(s6);
    cout << "All palindromic substrings: ";
    for (const string& p : palindromes) {
        cout << p << " ";
    }
    cout << endl;
    
    cout << "\nExample 7: Manacher's Algorithm" << endl;
    string s7 = "babcbabcbaccba";
    cout << "Input string: " << s7 << endl;
    cout << "Longest palindromic substring (Manacher's): " << manachersAlgorithm(s7) << endl;
}

int main() {
    // Demonstrate the Expanding From Center pattern
    demonstrateExpandingFromCenter();
    
    return 0;
}
