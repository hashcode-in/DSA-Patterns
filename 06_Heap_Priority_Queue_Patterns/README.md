# Heap (Priority Queue) Patterns

## Overview

Heaps are specialized tree-based data structures that satisfy the heap property. A heap is a complete binary tree where:
- In a max heap: for any given node C, if P is a parent node of C, then the value of P is greater than or equal to the value of C
- In a min heap: for any given node C, if P is a parent node of C, then the value of P is less than or equal to the value of C

Heaps are commonly used to implement priority queues, which are essential for many algorithms including:
- Finding the k largest/smallest elements
- Finding the median in a stream of numbers
- Merging sorted lists
- Scheduling tasks based on priority

## Key Operations

- **Insert**: O(log n) - Add an element to the heap
- **Extract Min/Max**: O(log n) - Remove and return the minimum (or maximum) element
- **Peek**: O(1) - View the minimum (or maximum) element without removing it
- **Heapify**: O(n) - Create a heap from an array
- **Decrease/Increase Key**: O(log n) - Change the priority of an element

## Pattern Categories

### 1. Top K Elements (Selection/Frequency)

This pattern is used to find the k largest or smallest elements in a collection or handle elements based on their frequency. It leverages the heap's ability to maintain a fixed-size subset of elements ordered by priority.

#### Common Applications:
- Finding k largest/smallest elements in an array
- Finding most frequent elements
- Finding elements with highest/lowest priority

#### Example Problems:
- Kth Largest Element in an Array
- Top K Frequent Elements
- Sort Characters By Frequency
- K Closest Points to Origin

### 2. Two Heaps for Median Finding

This pattern uses two heaps (one min heap, one max heap) to efficiently find the median of a stream of numbers. The max heap stores the smaller half of elements, and the min heap stores the larger half.

#### Common Applications:
- Finding the median from a stream of data
- Balancing two groups of elements with specific constraints
- Solving sliding window median problems

#### Example Problems:
- Find Median from Data Stream
- Sliding Window Median
- Finding MK Average

### 3. K-way Merge

This pattern is used to merge k sorted lists into a single sorted list. It leverages a min heap to always select the smallest element from among the current heads of the k lists.

#### Common Applications:
- Merging multiple sorted arrays/lists
- Finding the kth smallest element across multiple sorted collections
- Handling streams of sorted data

#### Example Problems:
- Merge k Sorted Lists
- Find K Pairs with Smallest Sums
- Kth Smallest Element in a Sorted Matrix

### 4. Scheduling / Minimum Cost (Greedy with Priority Queue)

This pattern combines greedy algorithms with priority queues to make optimal scheduling decisions or allocate resources efficiently.

#### Common Applications:
- Task scheduling to minimize wait time or maximize throughput
- Resource allocation problems
- Interval scheduling
- Meeting room allocation

#### Example Problems:
- Meeting Rooms II
- Minimum Cost to Hire K Workers
- Task Scheduler
- The Skyline Problem
- Single-Threaded CPU

## Implementation Considerations

- **Choosing the right heap type**: Min-heap vs Max-heap depends on whether you want to prioritize smaller or larger elements.
- **Efficient heap operations**: Use built-in priority queue implementations for best performance.
- **Custom comparators**: For complex priorities, define custom comparison functions.
- **Space-time tradeoffs**: Heaps typically require O(n) space but can significantly improve time complexity for certain operations.
- **Lazy deletion**: Sometimes it's more efficient to mark elements as deleted rather than removing them immediately.

## When to Use Heap Patterns

- When you need to repeatedly find the minimum or maximum element
- When you need to efficiently maintain a collection in a partially sorted state
- When you need to merge multiple sorted collections
- When elements have priorities that can change during processing
- When you need to efficiently find the k largest/smallest elements in a collection
