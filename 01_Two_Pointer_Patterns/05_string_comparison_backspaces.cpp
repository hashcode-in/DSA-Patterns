/**
 * Pattern: Two Pointers - String Comparison with Backspaces
 * 
 * Description:
 * This pattern addresses the specific problem of comparing strings that contain backspace
 * characters ('#'). The challenge is to determine if two strings are equal after applying
 * all backspaces. We use two pointers to process the strings from right to left, skipping
 * characters that would be deleted by backspaces.
 * 
 * Time Complexity: O(n) - where n is the length of the input strings
 * Space Complexity: O(1) - if we process strings in-place without additional data structures
 * 
 * When to use:
 * - When comparing strings with backspace characters
 * - When simulating text editor behavior with deletion operations
 * - When processing strings with special modification operators
 * 
 * LeetCode Problems:
 * - 844. Backspace String Compare
 */

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

// Example 1: Backspace String Compare (Using Stack)
// LeetCode 844: https://leetcode.com/problems/backspace-string-compare/
// Approach 1: Using additional data structure (stack)
bool backspaceCompareUsingStack(string s, string t) {
    stack<char> sStack, tStack;
    
    // Process first string
    for (char c : s) {
        if (c == '#') {
            // Backspace, remove the top character if stack is not empty
            if (!sStack.empty()) {
                sStack.pop();
            }
        } else {
            // Normal character, push to stack
            sStack.push(c);
        }
    }
    
    // Process second string
    for (char c : t) {
        if (c == '#') {
            // Backspace, remove the top character if stack is not empty
            if (!tStack.empty()) {
                tStack.pop();
            }
        } else {
            // Normal character, push to stack
            tStack.push(c);
        }
    }
    
    // Check if the resulting stacks are identical
    if (sStack.size() != tStack.size()) {
        return false;
    }
    
    while (!sStack.empty()) {
        if (sStack.top() != tStack.top()) {
            return false;
        }
        sStack.pop();
        tStack.pop();
    }
    
    return true;
}

// Example 2: Backspace String Compare (Two Pointers)
// LeetCode 844: https://leetcode.com/problems/backspace-string-compare/
// Approach 2: Using two pointers (no extra space)
bool backspaceCompare(string s, string t) {
    int sPointer = s.length() - 1;
    int tPointer = t.length() - 1;
    int sSkip = 0; // Count of characters to skip in s
    int tSkip = 0; // Count of characters to skip in t
    
    // Process both strings from right to left
    while (sPointer >= 0 || tPointer >= 0) {
        // Find the next valid character in s
        while (sPointer >= 0) {
            if (s[sPointer] == '#') {
                // Increment skip count for each backspace
                sSkip++;
                sPointer--;
            } else if (sSkip > 0) {
                // Skip character due to backspace
                sSkip--;
                sPointer--;
            } else {
                // Found a valid character
                break;
            }
        }
        
        // Find the next valid character in t
        while (tPointer >= 0) {
            if (t[tPointer] == '#') {
                // Increment skip count for each backspace
                tSkip++;
                tPointer--;
            } else if (tSkip > 0) {
                // Skip character due to backspace
                tSkip--;
                tPointer--;
            } else {
                // Found a valid character
                break;
            }
        }
        
        // If one string is exhausted but the other isn't, they're not equal
        if ((sPointer >= 0) != (tPointer >= 0)) {
            return false;
        }
        
        // If both strings have characters, compare them
        if (sPointer >= 0 && tPointer >= 0) {
            if (s[sPointer] != t[tPointer]) {
                return false;
            }
        }
        
        // Move to the next characters
        sPointer--;
        tPointer--;
    }
    
    // If we've processed both strings completely, they're equal
    return true;
}

// Example 3: Build String After Backspaces
// Helper function to demonstrate how to build a final string after applying backspaces
string buildFinalString(const string& str) {
    string result;
    
    for (char c : str) {
        if (c == '#') {
            // Backspace, remove the last character if result is not empty
            if (!result.empty()) {
                result.pop_back();
            }
        } else {
            // Normal character, append to result
            result.push_back(c);
        }
    }
    
    return result;
}

// Example 4: Get Next Valid Character Position
// This is a utility function that can be used in different backspace-related problems
int getNextValidCharPos(const string& str, int startPos, int& skipCount) {
    int pos = startPos;
    
    while (pos >= 0) {
        if (str[pos] == '#') {
            skipCount++;
            pos--;
        } else if (skipCount > 0) {
            skipCount--;
            pos--;
        } else {
            break;
        }
    }
    
    return pos;
}

// Example 5: Type a String with Backspaces
// Function to simulate typing a string with backspaces on a keyboard
void simulateTyping(const string& input) {
    string displayed;
    
    cout << "Typing: ";
    for (char c : input) {
        if (c == '#') {
            if (!displayed.empty()) {
                displayed.pop_back();
                // Simulate backspace in console output (not perfect but illustrative)
                cout << "\b \b";
            }
        } else {
            displayed.push_back(c);
            cout << c;
        }
        
        // Add a small delay to make the typing simulation more realistic
        // In a real implementation, you might use sleep() or similar
        cout << flush;
    }
    
    cout << "\nFinal text: " << displayed << endl;
}

// Example 6: Advanced Backspace Handling with Multiple Backspace Characters
// Some systems might use multiple '#' characters to represent different backspace operations
bool compareWithAdvancedBackspaces(string s, string t) {
    // Map of special characters and how many characters they delete
    // '#' deletes 1 character, '@' deletes all characters so far, etc.
    unordered_map<char, int> specialChars = {
        {'#', 1},    // Regular backspace
        {'@', -1},   // Clear all (-1 means delete everything)
        {'^', 2}     // Delete two characters
    };
    
    // Build the final strings after applying special characters
    auto buildString = [&specialChars](const string& input) -> string {
        string result;
        
        for (char c : input) {
            if (specialChars.count(c)) {
                int deleteCount = specialChars[c];
                if (deleteCount == -1) {
                    // Clear all
                    result.clear();
                } else {
                    // Delete specified number of characters
                    for (int i = 0; i < deleteCount && !result.empty(); i++) {
                        result.pop_back();
                    }
                }
            } else {
                // Normal character
                result.push_back(c);
            }
        }
        
        return result;
    };
    
    // Build final strings and compare
    return buildString(s) == buildString(t);
}

// Main function to demonstrate the String Comparison with Backspaces pattern
void demonstrateBackspaceComparison() {
    cout << "Example 1: Backspace String Compare (Using Stack)" << endl;
    string s1 = "ab#c";
    string t1 = "ad#c";
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << t1 << endl;
    cout << "Are equal after backspaces: " << (backspaceCompareUsingStack(s1, t1) ? "true" : "false") << endl;
    
    cout << "\nExample 2: Backspace String Compare (Two Pointers)" << endl;
    string s2 = "a##c";
    string t2 = "#a#c";
    cout << "String 1: " << s2 << endl;
    cout << "String 2: " << t2 << endl;
    cout << "Are equal after backspaces: " << (backspaceCompare(s2, t2) ? "true" : "false") << endl;
    
    cout << "\nExample 3: Build String After Backspaces" << endl;
    string input = "abc#d#e";
    cout << "Input: " << input << endl;
    cout << "After applying backspaces: " << buildFinalString(input) << endl;
    
    cout << "\nExample 4: Using Next Valid Character Position" << endl;
    string text = "abc##de#f#ghi#";
    cout << "Input: " << text << endl;
    
    // Process the string manually using getNextValidCharPos
    string processed;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '#') {
            if (!processed.empty()) {
                processed.pop_back();
            }
        } else {
            processed.push_back(text[i]);
        }
    }
    cout << "Processed: " << processed << endl;
    
    cout << "\nExample 5: Typing Simulation" << endl;
    string typingInput = "abc#def##g";
    simulateTyping(typingInput);
    
    cout << "\nExample 6: Advanced Backspace Handling" << endl;
    string advanced1 = "abc#d@ef";  // Should result in "ef" (@ clears all)
    string advanced2 = "ef";        // Already "ef"
    cout << "String 1: " << advanced1 << endl;
    cout << "String 2: " << advanced2 << endl;
    cout << "Are equal with advanced backspaces: " << (compareWithAdvancedBackspaces(advanced1, advanced2) ? "true" : "false") << endl;
}

int main() {
    // Demonstrate the String Comparison with Backspaces pattern
    demonstrateBackspaceComparison();
    
    return 0;
}
