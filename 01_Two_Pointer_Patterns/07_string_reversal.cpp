/**
 * Pattern: Two Pointers - String Reversal
 * 
 * Description:
 * This pattern uses two pointers starting from opposite ends of a string (or array)
 * and moving toward each other to reverse elements or perform operations that involve
 * reversing. It's a simple yet powerful approach for string manipulation problems.
 * 
 * Time Complexity: O(n) - where n is the length of the string/array
 * Space Complexity: O(1) - if done in-place, or O(n) if a new string is created
 * 
 * When to use:
 * - Reversing a string or array
 * - Reversing words in a sentence
 * - Reversing specific elements (like vowels) within a string
 * - Problems involving string rotation or palindrome-related operations
 * 
 * LeetCode Problems:
 * - 151. Reverse Words in a String
 * - 344. Reverse String
 * - 345. Reverse Vowels of a String
 * - 541. Reverse String II
 * - 557. Reverse Words in a String III
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Example 1: Reverse String
// LeetCode 344: https://leetcode.com/problems/reverse-string/
void reverseString(vector<char>& s) {
    int left = 0;
    int right = s.size() - 1;
    
    while (left < right) {
        // Swap characters at left and right pointers
        swap(s[left], s[right]);
        
        // Move pointers toward each other
        left++;
        right--;
    }
}

// Example 2: Reverse Words in a String
// LeetCode 151: https://leetcode.com/problems/reverse-words-in-a-string/
string reverseWords(string s) {
    // Step 1: Remove extra spaces and trim the string
    string cleaned;
    for (char c : s) {
        if (c != ' ' || (!cleaned.empty() && cleaned.back() != ' ')) {
            cleaned.push_back(c);
        }
    }
    // Trim trailing space if any
    if (!cleaned.empty() && cleaned.back() == ' ') {
        cleaned.pop_back();
    }
    
    // Step 2: Reverse the entire string
    reverse(cleaned.begin(), cleaned.end());
    
    // Step 3: Reverse each word individually
    int start = 0;
    for (int i = 0; i <= cleaned.size(); i++) {
        if (i == cleaned.size() || cleaned[i] == ' ') {
            // Found a word boundary, reverse the word
            reverse(cleaned.begin() + start, cleaned.begin() + i);
            start = i + 1;
        }
    }
    
    return cleaned;
}

// Alternative implementation using stringstream
string reverseWordsAlt(string s) {
    // Extract words using stringstream
    stringstream ss(s);
    string word, result;
    
    // Read words and push to the front of result
    while (ss >> word) {
        if (!result.empty()) {
            result = word + " " + result;
        } else {
            result = word;
        }
    }
    
    return result;
}

// Example 3: Reverse Vowels of a String
// LeetCode 345: https://leetcode.com/problems/reverse-vowels-of-a-string/
string reverseVowels(string s) {
    int left = 0;
    int right = s.size() - 1;
    
    // Helper function to check if a character is a vowel
    auto isVowel = [](char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };
    
    while (left < right) {
        // Find vowel from the left
        while (left < right && !isVowel(s[left])) {
            left++;
        }
        
        // Find vowel from the right
        while (left < right && !isVowel(s[right])) {
            right--;
        }
        
        // If both pointers point to vowels, swap them
        if (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
    
    return s;
}

// Example 4: Reverse String II
// LeetCode 541: https://leetcode.com/problems/reverse-string-ii/
// Reverse the first k characters for every 2k characters
string reverseStringII(string s, int k) {
    int n = s.size();
    
    for (int start = 0; start < n; start += 2 * k) {
        // Calculate the end position for reversal (min of start+k or end of string)
        int i = start;
        int j = min(start + k - 1, n - 1);
        
        // Reverse the first k characters
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
    
    return s;
}

// Example 5: Reverse Words in a String III
// LeetCode 557: https://leetcode.com/problems/reverse-words-in-a-string-iii/
// Reverse each word in a string while preserving whitespace and initial word order
string reverseWordsIII(string s) {
    int start = 0;
    int n = s.size();
    
    for (int i = 0; i <= n; i++) {
        // If we reach a space or the end of the string, we've found a word boundary
        if (i == n || s[i] == ' ') {
            // Reverse the current word
            int left = start;
            int right = i - 1;
            
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            
            // Move start to the beginning of the next word
            start = i + 1;
        }
    }
    
    return s;
}

// Example 6: Rotate String
// LeetCode 796: https://leetcode.com/problems/rotate-string/
// Check if a string can be rotated to become another string
bool rotateString(string s, string goal) {
    if (s.size() != goal.size()) {
        return false;
    }
    
    // Approach 1: Check all rotations
    for (int i = 0; i < s.size(); i++) {
        // Rotate the string by 1 position
        char first = s[0];
        for (int j = 0; j < s.size() - 1; j++) {
            s[j] = s[j + 1];
        }
        s[s.size() - 1] = first;
        
        // Check if the rotated string equals the goal
        if (s == goal) {
            return true;
        }
    }
    
    return false;
}

// Approach 2: Using string concatenation
bool rotateStringAlt(string s, string goal) {
    if (s.size() != goal.size()) {
        return false;
    }
    
    // Concatenate s with itself, if goal is a rotation of s,
    // it will be a substring of s+s
    string doubleS = s + s;
    
    return doubleS.find(goal) != string::npos;
}

// Example 7: Palindrome String Implementation
bool isPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

// Utility function to display a character vector as a string
void printCharVector(const vector<char>& chars) {
    for (char c : chars) {
        cout << c;
    }
    cout << endl;
}

// Main function to demonstrate the String Reversal pattern
void demonstrateStringReversal() {
    cout << "Example 1: Reverse String" << endl;
    vector<char> s1 = {'h', 'e', 'l', 'l', 'o'};
    cout << "Original string: ";
    printCharVector(s1);
    
    reverseString(s1);
    cout << "Reversed string: ";
    printCharVector(s1);
    
    cout << "\nExample 2: Reverse Words in a String" << endl;
    string s2 = "  the sky is   blue  ";
    cout << "Original string: \"" << s2 << "\"" << endl;
    cout << "Reversed words: \"" << reverseWords(s2) << "\"" << endl;
    cout << "Reversed words (alternative): \"" << reverseWordsAlt(s2) << "\"" << endl;
    
    cout << "\nExample 3: Reverse Vowels of a String" << endl;
    string s3 = "hello";
    cout << "Original string: \"" << s3 << "\"" << endl;
    cout << "String with reversed vowels: \"" << reverseVowels(s3) << "\"" << endl;
    
    cout << "\nExample 4: Reverse String II" << endl;
    string s4 = "abcdefg";
    int k = 2;
    cout << "Original string: \"" << s4 << "\"" << endl;
    cout << "After reversing every " << k << " chars: \"" << reverseStringII(s4, k) << "\"" << endl;
    
    cout << "\nExample 5: Reverse Words in a String III" << endl;
    string s5 = "Let's take LeetCode contest";
    cout << "Original string: \"" << s5 << "\"" << endl;
    cout << "After reversing each word: \"" << reverseWordsIII(s5) << "\"" << endl;
    
    cout << "\nExample 6: Rotate String" << endl;
    string s6 = "abcde";
    string goal = "cdeab";
    cout << "String 1: \"" << s6 << "\"" << endl;
    cout << "String 2: \"" << goal << "\"" << endl;
    cout << "Can String 1 be rotated to get String 2? " << (rotateString(s6, goal) ? "Yes" : "No") << endl;
    cout << "Using alternative approach: " << (rotateStringAlt("abcde", goal) ? "Yes" : "No") << endl;
    
    cout << "\nExample 7: Palindrome Check" << endl;
    string s7 = "racecar";
    cout << "String: \"" << s7 << "\"" << endl;
    cout << "Is it a palindrome? " << (isPalindrome(s7) ? "Yes" : "No") << endl;
}

int main() {
    // Demonstrate the String Reversal pattern
    demonstrateStringReversal();
    
    return 0;
}
