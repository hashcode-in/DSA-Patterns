# Linked List Manipulation Patterns

This directory contains implementations of common linked list patterns used in data structure and algorithm problems.

## Patterns Overview

### In-place Reversal Pattern
- Reverse a linked list or parts of it in-place without using extra space
- Useful for problems requiring reversing linked list segments
- Examples: Reverse Linked List, Reverse Nodes in k-Group

### Merging/Sorting Linked Lists Pattern
- Techniques for merging or sorting linked lists
- Often used in problems that require combining multiple lists
- Examples: Merge Two Sorted Lists, Sort List

### Addition/Manipulation of Numbers Pattern
- Represent and manipulate numbers using linked lists
- Each node typically represents a digit
- Examples: Add Two Numbers, Plus One Linked List

### Intersection/Cycle Detection Pattern
- Find intersections between lists or detect cycles
- Often involves using slow and fast pointers (Floyd's Cycle Finding Algorithm)
- Examples: Intersection of Two Linked Lists, Linked List Cycle

### Reordering/Partitioning Pattern
- Reorder or partition linked lists based on specific criteria
- Examples: Reorder List, Partition List, Odd Even Linked List

## Common Techniques

1. **Two Pointer Technique**: Using multiple pointers to traverse the list at different speeds or positions
2. **Dummy Head**: Using a dummy/sentinel node to simplify edge cases
3. **In-place Manipulation**: Modifying the links between nodes rather than creating new nodes
4. **Slow and Fast Pointers**: For cycle detection and finding middle elements
5. **Recursion**: Especially useful for reversal problems

## LeetCode Problems by Pattern

### Pattern 70: Linked List - In-place Reversal
- 206. Reverse Linked List
- 92. Reverse Linked List II
- 25. Reverse Nodes in k-Group
- 234. Palindrome Linked List
- 83. Remove Duplicates from Sorted List
- 82. Remove Duplicates from Sorted List II

### Pattern 71: Linked List - Merging Two Sorted Lists
- 21. Merge Two Sorted Lists
- 23. Merge k Sorted Lists (combines with Heap pattern)

### Pattern 72: Linked List - Addition of Numbers
- 2. Add Two Numbers
- 369. Plus One Linked List
- 445. Add Two Numbers II

### Pattern 73: Linked List - Intersection Detection
- 160. Intersection of Two Linked Lists
- 141. Linked List Cycle
- 142. Linked List Cycle II

### Pattern 74: Linked List - Reordering / Partitioning
- 24. Swap Nodes in Pairs
- 61. Rotate List
- 86. Partition List
- 143. Reorder List
- 328. Odd Even Linked List
