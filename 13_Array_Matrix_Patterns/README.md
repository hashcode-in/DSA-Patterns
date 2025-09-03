# Array/Matrix Manipulation Patterns

This directory contains implementations of common array and matrix manipulation patterns used in data structure and algorithm problems.

## Patterns Overview

### In-place Rotation Pattern
- Rotate arrays or matrices in place without using extra space
- Useful for problems involving circular shifting or matrix rotations
- Examples: Rotate Image, Rotate Array

### Spiral Traversal Pattern
- Traverse a matrix in a spiral order from outer to inner elements
- Useful for generating patterns or processing matrices in a specific order
- Examples: Spiral Matrix, Spiral Matrix II, Spiral Matrix III

### Set Matrix Zeroes Pattern
- Efficiently mark rows and columns in a matrix based on zero elements
- Uses in-place marking techniques to avoid extra space
- Examples: Set Matrix Zeroes

### Product Except Self Pattern
- Calculate products of array elements with specific exclusions
- Uses prefix and suffix product techniques
- Examples: Product of Array Except Self

### Plus One (Handling Carry) Pattern
- Increment a number represented as an array of digits
- Handle carry propagation efficiently
- Examples: Plus One, Add Binary

### Merge Sorted Arrays Pattern
- Combine sorted arrays efficiently, often in place
- Usually involves working from the end of the arrays
- Examples: Merge Sorted Array

### Cyclic Sort Pattern
- Sort arrays with values in a specific range in O(n) time
- Particularly useful when array values have a relationship with their indices
- Examples: Find Missing Number, Find All Duplicates in an Array

### Maximum Product Subarray Pattern
- Variation of Kadane's algorithm for product instead of sum
- Handles positive and negative numbers efficiently
- Examples: Maximum Product Subarray

## Common Techniques

1. **In-place Manipulation**: Modify the array or matrix without using additional data structures
2. **Two-pointer Technique**: Use multiple pointers to navigate the array efficiently
3. **Prefix/Suffix Computations**: Pre-compute values from left and right for efficient operations
4. **Boundary-based Traversal**: Process arrays or matrices by moving along the boundaries
5. **Index Mapping**: Exploit the relationship between array values and their indices

## LeetCode Problems by Pattern

### Pattern 75: Array/Matrix - In-place Rotation
- 48. Rotate Image
- 189. Rotate Array

### Pattern 76: Array/Matrix - Spiral Traversal
- 54. Spiral Matrix
- 59. Spiral Matrix II
- 885. Spiral Matrix III
- 2326. Spiral Matrix IV

### Pattern 77: Array/Matrix - Set Matrix Zeroes
- 73. Set Matrix Zeroes

### Pattern 78: Array - Product Except Self
- 238. Product of Array Except Self

### Pattern 79: Array - Plus One
- 66. Plus One
- 67. Add Binary (similar concept)
- 989. Add to Array-Form of Integer

### Pattern 80: Array - Merge Sorted Array
- 88. Merge Sorted Array
- 21. Merge Two Sorted Lists (linked list version)

### Pattern 81: Array - Cyclic Sort
- 41. First Missing Positive
- 268. Missing Number
- 287. Find the Duplicate Number
- 442. Find All Duplicates in an Array
- 448. Find All Numbers Disappeared in an Array
- 645. Set Mismatch

### Pattern 82: Array - Kadane's Variant for Maximum Product
- 152. Maximum Product Subarray
- 1567. Maximum Length of Subarray With Positive Product
