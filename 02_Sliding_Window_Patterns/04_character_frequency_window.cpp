/**
 * Pattern: Sliding Window - Character Frequency Matching
 * 
 * Description:
 * This pattern involves tracking character frequencies within a sliding window to match
 * specific patterns or conditions. It's particularly useful for string manipulation problems
 * that require finding substrings with specific character frequency properties, such as
 * anagrams, permutations, or substrings with constraints on character occurrences.
 * 
 * Time Complexity: O(n) - where n is the length of the string
 * Space Complexity: O(k) - where k is the size of the character set (often constant)
 * 
 * When to use:
 * - Finding anagrams or permutations in a string
 * - Matching substrings with specific character frequency requirements
 * - Problems involving character replacement, substitution, or rearrangement
 * - Any problem requiring frequency analysis of characters in a sliding window
 * 
 * LeetCode Problems:
 * - 438. Find All Anagrams in a String
 * - 567. Permutation in String
 * - 76. Minimum Window Substring (variation with character constraints)
 * - 3. Longest Substring Without Repeating Characters (variation)
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <climits>

using namespace std;

// Example 1: Find All Anagrams in a String
// LeetCode 438: https://leetcode.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.length() < p.length()) return result;
    
    // Character frequency maps
    array<int, 26> pCount = {0};
    array<int, 26> sCount = {0};
    
    // Count frequencies in pattern
    for (char c : p) {
        pCount[c - 'a']++;
    }
    
    // Sliding window
    for (int i = 0; i < s.length(); i++) {
        // Add current character to window
        sCount[s[i] - 'a']++;
        
        // Remove character that's no longer in the window
        if (i >= p.length()) {
            sCount[s[i - p.length()] - 'a']--;
        }
        
        // Check if current window matches pattern
        if (i >= p.length() - 1 && pCount == sCount) {
            result.push_back(i - (p.length() - 1));
        }
    }
    
    return result;
}

// Example 2: Permutation in String
// LeetCode 567: https://leetcode.com/problems/permutation-in-string/
bool checkInclusion(string s1, string s2) {
    if (s1.length() > s2.length()) return false;
    
    // Character frequency maps
    array<int, 26> s1Count = {0};
    array<int, 26> s2Count = {0};
    
    // Count frequencies in pattern
    for (char c : s1) {
        s1Count[c - 'a']++;
    }
    
    // Sliding window
    for (int i = 0; i < s2.length(); i++) {
        // Add current character to window
        s2Count[s2[i] - 'a']++;
        
        // Remove character that's no longer in the window
        if (i >= s1.length()) {
            s2Count[s2[i - s1.length()] - 'a']--;
        }
        
        // Check if current window matches pattern
        if (i >= s1.length() - 1 && s1Count == s2Count) {
            return true;
        }
    }
    
    return false;
}

// Example 3: Minimum Window Substring
// LeetCode 76: https://leetcode.com/problems/minimum-window-substring/
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    
    // Character frequency map for pattern
    unordered_map<char, int> requiredChars;
    for (char c : t) {
        requiredChars[c]++;
    }
    
    int left = 0;
    int minStart = 0;
    int minLength = INT_MAX;
    int requiredCount = t.length(); // Number of characters needed to be matched
    
    for (int right = 0; right < s.length(); right++) {
        // If this character is in our target string, decrement the required count
        if (requiredChars.count(s[right]) > 0) {
            if (requiredChars[s[right]] > 0) {
                requiredCount--;
            }
            requiredChars[s[right]]--;
        }
        
        // When we have all required characters, try to minimize the window
        while (requiredCount == 0) {
            // Update the minimum window if smaller
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minStart = left;
            }
            
            // Try to remove the leftmost character and update counts
            if (requiredChars.count(s[left]) > 0) {
                requiredChars[s[left]]++;
                if (requiredChars[s[left]] > 0) {
                    requiredCount++; // We removed a necessary character
                }
            }
            
            left++; // Shrink from the left
        }
    }
    
    return (minLength != INT_MAX) ? s.substr(minStart, minLength) : "";
}

// Example 4: Count Occurrences of Anagrams
int countAnagrams(string text, string pattern) {
    int n = text.length();
    int k = pattern.length();
    if (n < k) return 0;
    
    // Character frequency maps
    array<int, 26> patternCount = {0};
    array<int, 26> windowCount = {0};
    
    // Count frequencies in pattern
    for (char c : pattern) {
        patternCount[c - 'a']++;
    }
    
    int count = 0;
    
    // Process first window
    for (int i = 0; i < k; i++) {
        windowCount[text[i] - 'a']++;
    }
    
    // Check first window
    if (patternCount == windowCount) {
        count++;
    }
    
    // Slide the window
    for (int i = k; i < n; i++) {
        // Add new character
        windowCount[text[i] - 'a']++;
        
        // Remove oldest character
        windowCount[text[i - k] - 'a']--;
        
        // Check current window
        if (patternCount == windowCount) {
            count++;
        }
    }
    
    return count;
}

// Example 5: Custom Anagram Finder with Multiple Constraints
// Find substrings where:
// 1. All chars from pattern are present (may have different frequencies)
// 2. At most k characters can have frequency less than required
// 3. No character from outside the pattern is allowed
vector<int> findCustomAnagrams(string s, string pattern, int k) {
    vector<int> result;
    int n = s.length();
    int m = pattern.length();
    
    // Create pattern frequency map
    unordered_map<char, int> patternFreq;
    for (char c : pattern) {
        patternFreq[c]++;
    }
    
    // Create set of pattern characters for quick lookups
    unordered_map<char, bool> patternChars;
    for (char c : pattern) {
        patternChars[c] = true;
    }
    
    for (int i = 0; i <= n - m; i++) {
        // Check if current substring is a valid custom anagram
        unordered_map<char, int> windowFreq;
        int invalidChars = 0; // Count of chars with wrong frequency
        bool containsOutsideChar = false;
        
        for (int j = 0; j < m; j++) {
            char currentChar = s[i + j];
            
            // Check if char is outside pattern
            if (patternChars.find(currentChar) == patternChars.end()) {
                containsOutsideChar = true;
                break;
            }
            
            // Count frequency
            windowFreq[currentChar]++;
        }
        
        // Skip if contains outside character
        if (containsOutsideChar) {
            continue;
        }
        
        // Count characters with wrong frequency
        for (auto& pair : patternFreq) {
            char c = pair.first;
            int requiredFreq = pair.second;
            int actualFreq = windowFreq[c];
            
            if (actualFreq < requiredFreq) {
                invalidChars++;
            }
        }
        
        // Add to result if constraints are met
        if (invalidChars <= k) {
            result.push_back(i);
        }
    }
    
    return result;
}

// Example 6: Longest Substring with At Most K Distinct Characters
// Find the length of the longest substring with at most k distinct characters
int lengthOfLongestSubstringKDistinct(string s, int k) {
    int n = s.length();
    if (n == 0 || k == 0) return 0;
    
    unordered_map<char, int> charCount;
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < n; right++) {
        // Add current character to window
        charCount[s[right]]++;
        
        // Shrink window while we have more than k distinct characters
        while (charCount.size() > k) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0) {
                charCount.erase(s[left]);
            }
            left++;
        }
        
        // Update maximum length
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// Example 7: Longest Substring with Exactly K Distinct Characters
// Find the length of the longest substring with exactly k distinct characters
int lengthOfLongestSubstringExactlyKDistinct(string s, int k) {
    int n = s.length();
    if (n == 0 || k == 0 || k > n) return 0;
    
    // Helper function to find longest substring with at most k distinct chars
    auto atMostK = [&](int limit) {
        unordered_map<char, int> charCount;
        int left = 0;
        int result = 0;
        
        for (int right = 0; right < n; right++) {
            charCount[s[right]]++;
            
            while (charCount.size() > limit) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            result += right - left + 1;
        }
        
        return result;
    };
    
    // Exactly K = At Most K - At Most (K-1)
    // This is a mathematical trick to count windows with exactly k distinct chars
    return atMostK(k) - atMostK(k - 1);
}

// Example 8: String Matching with Character Substitution
// Check if we can make string s match pattern p with at most k character substitutions
bool canMatch(string s, string p, int k) {
    int n = s.length();
    int m = p.length();
    
    if (n != m) return false;
    
    int mismatchCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (s[i] != p[i]) {
            mismatchCount++;
        }
    }
    
    return mismatchCount <= k;
}

// Example 9: Find All Anagrams with Character Mapping
// Find anagrams where characters can be mapped to different ones
vector<int> findAnagramsWithMapping(string s, string p) {
    vector<int> result;
    int n = s.length();
    int m = p.length();
    
    if (n < m) return result;
    
    for (int i = 0; i <= n - m; i++) {
        string window = s.substr(i, m);
        
        // Check if window is an anagram of pattern with character mapping
        bool isAnagram = true;
        unordered_map<char, char> charMap;
        unordered_map<char, bool> usedChars;
        
        for (int j = 0; j < m; j++) {
            char c1 = window[j];
            char c2 = p[j];
            
            // If mapping exists, check consistency
            if (charMap.find(c1) != charMap.end()) {
                if (charMap[c1] != c2) {
                    isAnagram = false;
                    break;
                }
            } 
            // If no mapping exists, create one if target char not already used
            else {
                if (usedChars[c2]) {
                    isAnagram = false;
                    break;
                }
                charMap[c1] = c2;
                usedChars[c2] = true;
            }
        }
        
        if (isAnagram) {
            result.push_back(i);
        }
    }
    
    return result;
}

// Utility function to print a vector
template<typename T>
void printVector(const vector<T>& vec) {
    for (const T& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate the Character Frequency Matching pattern
void demonstrateCharacterFrequencyMatching() {
    cout << "Example 1: Find All Anagrams in a String" << endl;
    string s1 = "cbaebabacd";
    string p1 = "abc";
    cout << "String: " << s1 << endl;
    cout << "Pattern: " << p1 << endl;
    vector<int> anagramIndices = findAnagrams(s1, p1);
    cout << "Start indices of anagrams: ";
    printVector(anagramIndices);
    
    cout << "\nExample 2: Permutation in String" << endl;
    string s2 = "eidbaooo";
    string p2 = "ab";
    cout << "String: " << s2 << endl;
    cout << "Pattern: " << p2 << endl;
    cout << "Contains permutation: " << (checkInclusion(p2, s2) ? "Yes" : "No") << endl;
    
    cout << "\nExample 3: Minimum Window Substring" << endl;
    string s3 = "ADOBECODEBANC";
    string t3 = "ABC";
    cout << "String: " << s3 << endl;
    cout << "Target: " << t3 << endl;
    cout << "Minimum window substring: " << minWindow(s3, t3) << endl;
    
    cout << "\nExample 4: Count Occurrences of Anagrams" << endl;
    string text = "forxxorfxdofr";
    string pattern = "for";
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "Count of anagrams: " << countAnagrams(text, pattern) << endl;
    
    cout << "\nExample 5: Custom Anagram Finder" << endl;
    string s5 = "aabcdeaabc";
    string p5 = "abcde";
    int k5 = 1; // Allow at most 1 character to have incorrect frequency
    cout << "String: " << s5 << endl;
    cout << "Pattern: " << p5 << endl;
    cout << "Max allowed incorrect chars: " << k5 << endl;
    vector<int> customAnagrams = findCustomAnagrams(s5, p5, k5);
    cout << "Start indices of custom anagrams: ";
    printVector(customAnagrams);
    
    cout << "\nExample 6: Longest Substring with At Most K Distinct Characters" << endl;
    string s6 = "eceba";
    int k6 = 2;
    cout << "String: " << s6 << endl;
    cout << "k (max distinct chars): " << k6 << endl;
    cout << "Length of longest substring: " << lengthOfLongestSubstringKDistinct(s6, k6) << endl;
    
    cout << "\nExample 7: Longest Substring with Exactly K Distinct Characters" << endl;
    string s7 = "pqpqs";
    int k7 = 2;
    cout << "String: " << s7 << endl;
    cout << "k (exact distinct chars): " << k7 << endl;
    cout << "Length of longest substring: " << lengthOfLongestSubstringExactlyKDistinct(s7, k7) << endl;
    
    cout << "\nExample 8: String Matching with Character Substitution" << endl;
    string s8 = "abcde";
    string p8 = "abfde";
    int k8 = 1;
    cout << "String: " << s8 << endl;
    cout << "Pattern: " << p8 << endl;
    cout << "Max allowed substitutions: " << k8 << endl;
    cout << "Can match: " << (canMatch(s8, p8, k8) ? "Yes" : "No") << endl;
    
    cout << "\nExample 9: Find Anagrams with Character Mapping" << endl;
    string s9 = "badc";
    string p9 = "abcd";
    cout << "String: " << s9 << endl;
    cout << "Pattern: " << p9 << endl;
    vector<int> mappedAnagrams = findAnagramsWithMapping(s9, p9);
    cout << "Start indices of mapped anagrams: ";
    printVector(mappedAnagrams);
}

int main() {
    // Demonstrate the Character Frequency Matching pattern
    demonstrateCharacterFrequencyMatching();
    
    return 0;
}
