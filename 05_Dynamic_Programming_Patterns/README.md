# Dynamic Programming (DP) Patterns

Dynamic Programming is a powerful technique for solving complex problems by breaking them down into overlapping subproblems and solving each subproblem only once. It's particularly effective when a problem has optimal substructure (the optimal solution to the problem contains optimal solutions to the subproblems) and overlapping subproblems (the same subproblems are solved multiple times).

## Core Principles of Dynamic Programming

1. **Identify Subproblems**: Break down the original problem into smaller, overlapping subproblems.
2. **Define State**: Determine the state variables that represent the subproblems.
3. **Establish Recurrence Relation**: Define how the solution to a subproblem relates to solutions of smaller subproblems.
4. **Memoization/Tabulation**: Store solutions to subproblems to avoid redundant calculations.
5. **Build Final Solution**: Combine subproblem solutions to solve the original problem.

## Common Approaches

1. **Top-down (Memoization)**: Start with the original problem and recursively break it down, caching results.
2. **Bottom-up (Tabulation)**: Start from the smallest subproblems and iteratively build up to the original problem.

## Patterns in this Category

### Pattern 27: DP - 1D Array (Fibonacci Style)
- **Description**: Problems where each state depends on one or two previous states in a linear manner.
- **When to use**: Sequential decision-making, where future states depend only on a limited number of previous states.
- **Files**: [01_fibonacci_style.cpp](./01_fibonacci_style.cpp)
- **LeetCode Problems**: Climbing Stairs, Fibonacci Number, House Robber

### Pattern 28: DP - 1D Array (Kadane's Algorithm for Max/Min Subarray)
- **Description**: Finding the contiguous subarray with the maximum/minimum sum.
- **When to use**: Problems involving finding subarrays with optimal sums or products.
- **Files**: [02_kadanes_algorithm.cpp](./02_kadanes_algorithm.cpp)
- **LeetCode Problems**: Maximum Subarray, Maximum Product Subarray

### Pattern 29: DP - 1D Array (Coin Change / Unbounded Knapsack Style)
- **Description**: Problems where items can be used multiple times to achieve a target.
- **When to use**: Optimization problems with unlimited supplies of items or actions.
- **Files**: [03_coin_change_unbounded_knapsack.cpp](./03_coin_change_unbounded_knapsack.cpp)
- **LeetCode Problems**: Coin Change, Combination Sum IV, Coin Change II

### Pattern 30: DP - 1D Array (0/1 Knapsack Subset Sum Style)
- **Description**: Problems where each item can be used at most once to achieve a target.
- **When to use**: Resource allocation with limited availability of items.
- **Files**: [04_01_knapsack_subset_sum.cpp](./04_01_knapsack_subset_sum.cpp)
- **LeetCode Problems**: Partition Equal Subset Sum, Target Sum

### Pattern 31: DP - 1D Array (Word Break Style)
- **Description**: Determining if a string can be segmented into words from a dictionary.
- **When to use**: String segmentation and decomposition problems.
- **Files**: [05_word_break.cpp](./05_word_break.cpp)
- **LeetCode Problems**: Word Break, Word Break II

### Pattern 32: DP - 2D Array (Longest Common Subsequence - LCS)
- **Description**: Finding the longest subsequence common to two sequences.
- **When to use**: String comparison, sequence alignment, or similarity measurement.
- **Files**: [06_longest_common_subsequence.cpp](./06_longest_common_subsequence.cpp)
- **LeetCode Problems**: Longest Common Subsequence, Delete Operation for Two Strings

### Pattern 33: DP - 2D Array (Edit Distance / Levenshtein Distance)
- **Description**: Computing the minimum number of operations to transform one string into another.
- **When to use**: String transformation, spell checking, or DNA sequence alignment.
- **Files**: [07_edit_distance.cpp](./07_edit_distance.cpp)
- **LeetCode Problems**: Edit Distance

### Pattern 34: DP - 2D Array (Unique Paths on Grid)
- **Description**: Counting or finding paths in a grid with obstacles or weights.
- **When to use**: Path-finding, robot movement, or grid traversal problems.
- **Files**: [08_unique_paths_grid.cpp](./08_unique_paths_grid.cpp)
- **LeetCode Problems**: Unique Paths, Unique Paths II, Minimum Path Sum

### Pattern 35: DP - Interval DP
- **Description**: Problems involving operations on subarrays or substrings.
- **When to use**: When the solution depends on combining results from different intervals.
- **Files**: [09_interval_dp.cpp](./09_interval_dp.cpp)
- **LeetCode Problems**: Burst Balloons, Remove Boxes

### Pattern 36: DP - Catalan Numbers
- **Description**: Problems whose solutions form Catalan numbers sequence.
- **When to use**: Counting problems involving balanced expressions or binary trees.
- **Files**: [10_catalan_numbers.cpp](./10_catalan_numbers.cpp)
- **LeetCode Problems**: Unique Binary Search Trees, Different Ways to Add Parentheses

### Pattern 37: DP - Longest Increasing Subsequence (LIS)
- **Description**: Finding the longest subsequence where elements are in strictly increasing order.
- **When to use**: Sequence optimization with ordering constraints.
- **Files**: [11_longest_increasing_subsequence.cpp](./11_longest_increasing_subsequence.cpp)
- **LeetCode Problems**: Longest Increasing Subsequence, Russian Doll Envelopes

## Time and Space Complexity

- **Time Complexity**: Typically O(n²) for problems with two state variables, or O(n) for problems with one state variable, where n is the input size.
- **Space Complexity**: Typically O(n²) or O(n) depending on the dimensionality of the state.

## Common Optimization Techniques

1. **Space Optimization**: Reducing space complexity by using only the necessary previous states.
2. **State Compression**: Using bit manipulation to represent states more efficiently.
3. **Reusing Arrays**: Overwriting values in the same array to save space.
4. **Preprocessing**: Computing certain values in advance to speed up DP calculation.

## Common Mistakes and Pitfalls

1. **Incorrect State Definition**: Not capturing all aspects of the problem in the state.
2. **Missing Base Cases**: Not properly initializing the DP table for the smallest subproblems.
3. **Wrong Recurrence Relation**: Establishing an incorrect relationship between subproblems.
4. **Overlooking Constraints**: Not considering the constraints or boundary conditions.
5. **Redundant Computation**: Not effectively memoizing or tabulating to avoid repeated work.

## Tips for Identifying DP Problems

1. **Optimization Problem**: The problem asks for maximum/minimum value, or counting possibilities.
2. **Overlapping Subproblems**: The same calculations would be done multiple times in a naive approach.
3. **Optimal Substructure**: Solutions to subproblems can be used to solve larger problems.
4. **Sequential Decisions**: The problem involves making a series of interconnected choices.
