/**
 * Pattern: Sliding Window - Variable Size (Condition-Based)
 * 
 * Description:
 * This pattern involves dynamically adjusting the window size based on specific conditions
 * while sliding through an array or string. Unlike the fixed-size window, the variable-size
 * window expands or contracts to find an optimal solution that satisfies given constraints.
 * 
 * Time Complexity: O(n) - where n is the length of the array/string
 * Space Complexity: O(k) - where k is the size of unique elements in the window (often O(1) for integer problems)
 * 
 * When to use:
 * - Finding the longest/shortest subarray that satisfies a specific condition
 * - Problems involving constraints like "at most k distinct elements"
 * - Finding minimum window containing a pattern
 * - Any problem requiring dynamic adjustment of window boundaries based on conditions
 * 
 * LeetCode Problems:
 * - 3. Longest Substring Without Repeating Characters
 * - 76. Minimum Window Substring
 * - 209. Minimum Size Subarray Sum
 * - 424. Longest Repeating Character Replacement
 * - 713. Subarray Product Less Than K
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Example 1: Longest Substring Without Repeating Characters
// LeetCode 3: https://leetcode.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if (n == 0) return 0;
    
    unordered_map<char, int> charIndex; // Map to store the last index of each character
    int left = 0; // Left pointer of the window
    int maxLength = 0;
    
    for (int right = 0; right < n; right++) {
        // If the character is already in the current window, shrink the window
        if (charIndex.find(s[right]) != charIndex.end() && charIndex[s[right]] >= left) {
            left = charIndex[s[right]] + 1; // Move left pointer to the right of the repeated character
        }
        
        // Update the last seen position of the current character
        charIndex[s[right]] = right;
        
        // Update the maximum length
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// Example 2: Minimum Size Subarray Sum
// LeetCode 209: https://leetcode.com/problems/minimum-size-subarray-sum/
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int sum = 0;
    int minLength = INT_MAX;
    
    for (int right = 0; right < n; right++) {
        sum += nums[right]; // Add the current element to the window
        
        // Shrink the window as small as possible while maintaining the sum >= target
        while (sum >= target) {
            minLength = min(minLength, right - left + 1);
            sum -= nums[left]; // Remove the leftmost element from the window
            left++; // Shrink the window from the left
        }
    }
    
    return (minLength != INT_MAX) ? minLength : 0;
}

// Example 3: Minimum Window Substring
// LeetCode 76: https://leetcode.com/problems/minimum-window-substring/
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    
    // Store character frequency of pattern t
    unordered_map<char, int> requiredChars;
    for (char c : t) {
        requiredChars[c]++;
    }
    
    int left = 0;
    int minLength = INT_MAX;
    int minStart = 0;
    int requiredCount = t.length(); // Number of characters needed to be matched
    
    for (int right = 0; right < s.length(); right++) {
        // If this character is in our target string, decrement the required count
        if (requiredChars.find(s[right]) != requiredChars.end()) {
            if (requiredChars[s[right]] > 0) {
                requiredCount--;
            }
            requiredChars[s[right]]--; // Decrement regardless (could go negative for extra chars)
        }
        
        // When we have all required characters, try to minimize the window
        while (requiredCount == 0) {
            // Update the minimum window if smaller
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minStart = left;
            }
            
            // Try to remove the leftmost character and update counts
            if (requiredChars.find(s[left]) != requiredChars.end()) {
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

// Example 4: Longest Repeating Character Replacement
// LeetCode 424: https://leetcode.com/problems/longest-repeating-character-replacement/
int characterReplacement(string s, int k) {
    int n = s.length();
    if (n == 0) return 0;
    
    unordered_map<char, int> charCount;
    int maxLength = 0;
    int maxCount = 0; // Count of the most frequent character in the current window
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        charCount[s[right]]++;
        maxCount = max(maxCount, charCount[s[right]]);
        
        // If the number of replacements needed exceeds k, shrink the window
        // (window size - count of most frequent char > k)
        if (right - left + 1 - maxCount > k) {
            charCount[s[left]]--;
            left++;
        }
        
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// Example 5: Subarray Product Less Than K
// LeetCode 713: https://leetcode.com/problems/subarray-product-less-than-k/
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0; // Since the array contains only positive integers
    
    int n = nums.size();
    int left = 0;
    int product = 1;
    int count = 0;
    
    for (int right = 0; right < n; right++) {
        product *= nums[right];
        
        // Shrink the window from the left while the product is >= k
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        
        // The number of valid subarrays ending at the current position is (right - left + 1)
        // This counts all subarrays ending at 'right'
        count += right - left + 1;
    }
    
    return count;
}

// Example 6: Fruits Into Baskets (Max 2 Distinct Elements)
// LeetCode 904: https://leetcode.com/problems/fruit-into-baskets/
int totalFruit(vector<int>& fruits) {
    int n = fruits.size();
    unordered_map<int, int> fruitCount;
    int left = 0;
    int maxFruits = 0;
    
    for (int right = 0; right < n; right++) {
        fruitCount[fruits[right]]++;
        
        // If we have more than 2 types of fruits, shrink the window
        while (fruitCount.size() > 2) {
            fruitCount[fruits[left]]--;
            if (fruitCount[fruits[left]] == 0) {
                fruitCount.erase(fruits[left]);
            }
            left++;
        }
        
        maxFruits = max(maxFruits, right - left + 1);
    }
    
    return maxFruits;
}

// Example 7: Longest Subarray of 1's After Deleting One Element
// LeetCode 1493: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
int longestSubarray(vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int zeroCount = 0;
    int maxLength = 0;
    
    for (int right = 0; right < n; right++) {
        if (nums[right] == 0) {
            zeroCount++;
        }
        
        // If we have more than 1 zero, shrink the window
        while (zeroCount > 1) {
            if (nums[left] == 0) {
                zeroCount--;
            }
            left++;
        }
        
        // Current length minus 1 (because we must delete one element)
        maxLength = max(maxLength, right - left);
    }
    
    return maxLength;
}

// Example 8: Max Consecutive Ones III
// LeetCode 1004: https://leetcode.com/problems/max-consecutive-ones-iii/
int longestOnes(vector<int>& nums, int k) {
    int n = nums.size();
    int left = 0;
    int zeroCount = 0;
    int maxLength = 0;
    
    for (int right = 0; right < n; right++) {
        if (nums[right] == 0) {
            zeroCount++;
        }
        
        // If we have more than k zeros, shrink the window
        while (zeroCount > k) {
            if (nums[left] == 0) {
                zeroCount--;
            }
            left++;
        }
        
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// Example 9: Find All Anagrams in a String (Fixed-Size Window but Variable Validation)
// LeetCode 438: https://leetcode.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.empty() || p.empty() || s.length() < p.length()) return result;
    
    unordered_map<char, int> pCount, sCount;
    int pLen = p.length();
    
    // Initialize pattern count
    for (char c : p) {
        pCount[c]++;
    }
    
    // Initial window
    for (int i = 0; i < pLen; i++) {
        sCount[s[i]]++;
    }
    
    // Check if the initial window is an anagram
    if (pCount == sCount) {
        result.push_back(0);
    }
    
    // Slide the window
    for (int i = pLen; i < s.length(); i++) {
        // Add new character
        sCount[s[i]]++;
        
        // Remove oldest character
        sCount[s[i - pLen]]--;
        if (sCount[s[i - pLen]] == 0) {
            sCount.erase(s[i - pLen]);
        }
        
        // Check if current window is an anagram
        if (pCount == sCount) {
            result.push_back(i - pLen + 1);
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

// Main function to demonstrate the Variable Size Sliding Window pattern
void demonstrateVariableSizeSlidingWindow() {
    cout << "Example 1: Longest Substring Without Repeating Characters" << endl;
    string s1 = "abcabcbb";
    cout << "String: " << s1 << endl;
    cout << "Length of longest substring: " << lengthOfLongestSubstring(s1) << endl;
    
    cout << "\nExample 2: Minimum Size Subarray Sum" << endl;
    vector<int> nums2 = {2, 3, 1, 2, 4, 3};
    int target2 = 7;
    cout << "Array: ";
    printVector(nums2);
    cout << "Target sum: " << target2 << endl;
    cout << "Minimum length subarray: " << minSubArrayLen(target2, nums2) << endl;
    
    cout << "\nExample 3: Minimum Window Substring" << endl;
    string s3 = "ADOBECODEBANC";
    string t3 = "ABC";
    cout << "String: " << s3 << endl;
    cout << "Target: " << t3 << endl;
    cout << "Minimum window substring: " << minWindow(s3, t3) << endl;
    
    cout << "\nExample 4: Longest Repeating Character Replacement" << endl;
    string s4 = "AABABBA";
    int k4 = 1;
    cout << "String: " << s4 << endl;
    cout << "k (max replacements): " << k4 << endl;
    cout << "Length of longest substring: " << characterReplacement(s4, k4) << endl;
    
    cout << "\nExample 5: Subarray Product Less Than K" << endl;
    vector<int> nums5 = {10, 5, 2, 6};
    int k5 = 100;
    cout << "Array: ";
    printVector(nums5);
    cout << "k (max product): " << k5 << endl;
    cout << "Number of valid subarrays: " << numSubarrayProductLessThanK(nums5, k5) << endl;
    
    cout << "\nExample 6: Fruits Into Baskets" << endl;
    vector<int> fruits = {1, 2, 1, 3, 2, 2};
    cout << "Fruits: ";
    printVector(fruits);
    cout << "Maximum fruits that can be collected: " << totalFruit(fruits) << endl;
    
    cout << "\nExample 7: Longest Subarray of 1's After Deleting One Element" << endl;
    vector<int> nums7 = {1, 1, 0, 1, 1, 1, 0, 1, 1};
    cout << "Array: ";
    printVector(nums7);
    cout << "Length of longest subarray: " << longestSubarray(nums7) << endl;
    
    cout << "\nExample 8: Max Consecutive Ones III" << endl;
    vector<int> nums8 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k8 = 2;
    cout << "Array: ";
    printVector(nums8);
    cout << "k (max flips): " << k8 << endl;
    cout << "Length of longest subarray: " << longestOnes(nums8, k8) << endl;
    
    cout << "\nExample 9: Find All Anagrams in a String" << endl;
    string s9 = "cbaebabacd";
    string p9 = "abc";
    cout << "String: " << s9 << endl;
    cout << "Pattern: " << p9 << endl;
    vector<int> anagramIndices = findAnagrams(s9, p9);
    cout << "Start indices of anagrams: ";
    printVector(anagramIndices);
}

int main() {
    // Demonstrate the Variable Size Sliding Window pattern
    demonstrateVariableSizeSlidingWindow();
    
    return 0;
}
