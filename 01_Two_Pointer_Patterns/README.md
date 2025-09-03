# Two Pointer Patterns

Two Pointer technique is an efficient approach for solving array-based problems that would otherwise require nested loops (O(n²)). By using two pointers, we can often achieve O(n) time complexity.

## Patterns in this Category

### Pattern 1: Converging Pointers (Sorted Array Target Sum)
- **Description**: Start with two pointers at opposite ends of an array and move them toward each other.
- **When to use**: Finding pairs with a specific sum, container with most water, trapping rain water.
- **Files**: [01_converging_pointers.cpp](./01_converging_pointers.cpp)
- **LeetCode Problems**: Two Sum II, 3Sum, Container With Most Water

### Pattern 2: Fast & Slow Pointers (Cycle Detection)
- **Description**: Use two pointers that move at different speeds through a sequence.
- **When to use**: Detecting cycles in linked lists, finding the middle element, finding duplicates.
- **Files**: [02_fast_slow_pointers.cpp](./02_fast_slow_pointers.cpp)
- **LeetCode Problems**: Linked List Cycle, Find the Duplicate Number, Happy Number

### Pattern 3: Fixed Separation Pointers (Nth Node from End)
- **Description**: Maintain a fixed gap between two pointers as they traverse a sequence.
- **When to use**: Finding kth element from the end of a list, sliding window operations.
- **Files**: [03_fixed_separation_pointers.cpp](./03_fixed_separation_pointers.cpp)
- **LeetCode Problems**: Remove Nth Node From End of List, Middle of the Linked List

### Pattern 4: In-place Array Modification
- **Description**: Use two pointers to modify an array without using extra space.
- **When to use**: Removing duplicates, moving elements, partitioning arrays.
- **Files**: [04_inplace_array_modification.cpp](./04_inplace_array_modification.cpp)
- **LeetCode Problems**: Remove Duplicates, Move Zeroes, Sort Colors

### Pattern 5: String Comparison with Backspaces
- **Description**: Compare strings while handling backspace characters correctly.
- **When to use**: When comparing strings with backspace operations.
- **Files**: [05_string_comparison_backspaces.cpp](./05_string_comparison_backspaces.cpp)
- **LeetCode Problems**: Backspace String Compare

### Pattern 6: Expanding from Center (Palindromes)
- **Description**: Start at a center point and expand outward in both directions.
- **When to use**: Finding palindromes, determining longest palindromic substring.
- **Files**: [06_expanding_from_center.cpp](./06_expanding_from_center.cpp)
- **LeetCode Problems**: Longest Palindromic Substring, Palindromic Substrings

### Pattern 7: String Reversal
- **Description**: Use two pointers to reverse characters or words in a string.
- **When to use**: Reversing strings, words, or specific portions of text.
- **Files**: [07_string_reversal.cpp](./07_string_reversal.cpp)
- **LeetCode Problems**: Reverse String, Reverse Words in a String

## General Implementation Strategy

1. **Identify the pattern**: Determine which of the above patterns fits your problem.
2. **Set up pointers**: Initialize pointers at appropriate positions.
3. **Define movement logic**: Establish clear rules for when and how to move each pointer.
4. **Handle edge cases**: Consider empty arrays, single elements, etc.
5. **Test with examples**: Verify solution with simple examples before coding.

## Time and Space Complexity

- **Time Complexity**: Most two-pointer approaches run in O(n) time.
- **Space Complexity**: Typically O(1) since we only use a constant amount of extra space.

## Code Template

```cpp
// Basic template for the converging pointers pattern
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {}; // No solution found
}
