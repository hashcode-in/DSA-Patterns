# Sliding Window Patterns

The Sliding Window technique is used to perform operations on a specific window size of an array or string, which could be fixed or variable in size. This approach reduces time complexity from O(n²) to O(n) for many problems involving arrays and strings.

## Patterns in this Category

### Pattern 8: Sliding Window - Fixed Size (Subarray Calculation)
- **Description**: Maintain a fixed-size window that slides through the array, tracking a specific calculation or property.
- **When to use**: Finding maximums, minimums, or averages of all subarrays of a fixed length.
- **Files**: [01_fixed_size_window.cpp](./01_fixed_size_window.cpp)
- **LeetCode Problems**: Maximum Average Subarray I, Moving Average from Data Stream

### Pattern 9: Sliding Window - Variable Size (Condition-Based)
- **Description**: Dynamically adjust the window size based on certain conditions while sliding through the array.
- **When to use**: Finding longest/shortest subarrays that satisfy specific conditions.
- **Files**: [02_variable_size_window.cpp](./02_variable_size_window.cpp)
- **LeetCode Problems**: Longest Substring Without Repeating Characters, Minimum Window Substring

### Pattern 10: Sliding Window - Monotonic Queue for Max/Min
- **Description**: Maintain a monotonic queue (increasing or decreasing) while sliding through the array.
- **When to use**: Finding maximum/minimum elements in every window of size k.
- **Files**: [03_monotonic_queue_window.cpp](./03_monotonic_queue_window.cpp)
- **LeetCode Problems**: Sliding Window Maximum, Shortest Subarray with Sum at Least K

### Pattern 11: Sliding Window - Character Frequency Matching
- **Description**: Track character frequencies within a sliding window to match specific patterns.
- **When to use**: Finding anagrams, permutations, or substrings with specific character frequencies.
- **Files**: [04_character_frequency_window.cpp](./04_character_frequency_window.cpp)
- **LeetCode Problems**: Find All Anagrams in a String, Permutation in String

## General Implementation Strategy

1. **Identify the window type**: Determine if you need a fixed-size or variable-size window.
2. **Initialize variables**: Set up pointers or indices to track the window boundaries.
3. **Process the window**: Add elements to the window and perform the required operations.
4. **Update the result**: Update your answer based on calculations within the current window.
5. **Slide the window**: Move the window forward by adjusting the start and end pointers.

## Time and Space Complexity

- **Time Complexity**: O(n) in most cases, as each element is processed at most twice (once when added to the window, once when removed).
- **Space Complexity**: Usually O(1) for fixed-size windows, or O(k) where k is the size of the distinct elements in the input for variable-size windows.

## Code Template

```cpp
// Basic template for fixed-size sliding window
vector<int> findMaxInSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> window; // Using deque to maintain a monotonic queue
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside the window
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }
        
        // Remove smaller elements as they won't be the maximum
        while (!window.empty() && nums[window.back()] < nums[i]) {
            window.pop_back();
        }
        
        // Add current element
        window.push_back(i);
        
        // Add result once we have a full window
        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }
    
    return result;
}
