# Backtracking Patterns

## Overview

Backtracking is an algorithmic technique for solving problems recursively by trying to build a solution incrementally, one step at a time, removing solutions that fail to satisfy the constraints of the problem at any point.

Backtracking can be thought of as a systematic way of trying all possible solutions to a problem using a brute force approach but with the ability to abandon a path once it's determined that the path cannot lead to a valid solution.

## Key Concepts

1. **Decision Space**: The set of all possible choices at each step.
2. **Constraints**: Rules that limit valid solutions.
3. **Goal State**: The condition that indicates a solution has been found.
4. **Exploration Strategy**: Depth-first search is typically used in backtracking.

## Common Backtracking Framework

```
function backtrack(current_state, remaining_choices):
    if current_state is a valid solution:
        add current_state to solutions
        return
    
    for choice in remaining_choices:
        if choice is valid:
            apply choice to current_state
            backtrack(new_state, new_remaining_choices)
            undo choice (backtrack)
```

## Pattern Categories

### 1. Subsets (Include/Exclude)

This pattern involves generating all possible subsets of a given set by making binary decisions (include/exclude) for each element.

#### Common Applications:
- Finding all possible subsets of a set
- Letter combinations of a phone number
- Combinations of k elements from n elements

#### Example Problems:
- Subsets
- Letter Combinations of a Phone Number
- Combinations

### 2. Permutations

This pattern generates all possible arrangements of elements where the order matters.

#### Common Applications:
- Generating all permutations of an array
- Next permutation in lexicographical order
- Permutation with specific constraints

#### Example Problems:
- Permutations
- Permutations II (with duplicates)
- Next Permutation

### 3. Combination Sum

This pattern finds all combinations of elements that sum to a target, with various constraints on reuse.

#### Common Applications:
- Finding combinations that sum to a target
- Subset sum problems
- Coin change variations

#### Example Problems:
- Combination Sum
- Combination Sum II (no duplicates)
- Combination Sum III (with size constraints)

### 4. Parentheses Generation

This pattern generates valid combinations of parentheses, typically balanced ones.

#### Common Applications:
- Generate all valid parentheses combinations
- Remove invalid parentheses
- Longest valid parentheses

#### Example Problems:
- Generate Parentheses
- Remove Invalid Parentheses

### 5. Word Search / Path Finding in Grid

This pattern involves finding paths in a grid with specific constraints.

#### Common Applications:
- Word search in a grid of characters
- Path finding in mazes
- Island counting with specific constraints

#### Example Problems:
- Word Search
- Word Search II (using Trie)
- Path with Maximum Gold

### 6. N-Queens / Constraint Satisfaction

This pattern deals with placing elements on a grid with specific constraints.

#### Common Applications:
- N-Queens problem
- Sudoku solver
- Constraint satisfaction problems

#### Example Problems:
- N-Queens
- Sudoku Solver

### 7. Palindrome Partitioning

This pattern partitions a string into palindromic substrings.

#### Common Applications:
- Palindrome partitioning
- String segmentation problems
- Minimizing cuts for palindrome partitioning

#### Example Problems:
- Palindrome Partitioning
- Palindrome Partitioning II (dynamic programming + backtracking)

## When to Use Backtracking

- When you need to find all solutions that satisfy certain constraints
- When a problem requires exploring multiple paths to find the optimal solution
- When the solution can be built incrementally with valid/invalid states at each step
- When you can identify a point at which a partial solution cannot be extended to a valid complete solution

## Optimization Techniques

- **Pruning**: Early termination of exploration paths that cannot lead to valid solutions
- **State Representation**: Efficient data structures to represent and update state
- **Order Optimization**: Trying more likely choices first to find solutions faster
- **Memoization**: Caching results of overlapping subproblems (combining with dynamic programming)
- **Bit manipulation**: For compact representation in subset and state problems
