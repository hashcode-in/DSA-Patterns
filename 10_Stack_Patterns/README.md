# Stack Patterns

Stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle. It's a fundamental data structure used in many algorithms and problem-solving techniques.

## Key Properties

- Elements are added and removed from the same end (the "top" of the stack)
- Only the top element is accessible at any given time
- Operations: push (add), pop (remove), peek/top (view top without removing)
- Time complexity for all operations is O(1)

## Common Stack Patterns

1. **Valid Parentheses Matching**
   - Used for validating the correct opening and closing of brackets
   - Ensures proper nesting of different types of brackets
   - Examples: `{}[]()` is valid, `{[}]` is invalid

2. **Monotonic Stack**
   - Maintains a monotonically increasing or decreasing order of elements
   - Used for finding next greater/smaller element or span problems
   - Helps solve range queries efficiently

3. **Expression Evaluation (RPN/Infix/Postfix)**
   - Converts between different expression notations
   - Evaluates mathematical expressions
   - Handles operator precedence and associativity

4. **Simulation / Backtracking Helper**
   - Helps in implementing undo operations
   - Tracks state in problems involving backtracking
   - Simplifies path operations in traversals

5. **Min/Max Stack Design**
   - Augmented stack that can retrieve minimum/maximum value in constant time
   - Maintains additional information along with the stack elements

6. **Largest Rectangle in Histogram**
   - Specific pattern for solving histogram-based problems
   - Used for calculating maximum rectangular area in histograms

## Problems by Pattern Type

### Valid Parentheses Matching
- 20\. Valid Parentheses
- 32\. Longest Valid Parentheses
- 921\. Minimum Add to Make Parentheses Valid
- 1249\. Minimum Remove to Make Valid Parentheses
- 1963\. Minimum Number of Swaps to Make the String Balanced

### Monotonic Stack
- 402\. Remove K Digits
- 496\. Next Greater Element I
- 503\. Next Greater Element II
- 739\. Daily Temperatures
- 901\. Online Stock Span
- 907\. Sum of Subarray Minimums
- 962\. Maximum Width Ramp
- 1475\. Final Prices With a Special Discount in a Shop
- 1673\. Find the Most Competitive Subsequence

### Expression Evaluation (RPN/Infix/Postfix)
- 150\. Evaluate Reverse Polish Notation
- 224\. Basic Calculator
- 227\. Basic Calculator II
- 772\. Basic Calculator III

### Simulation / Backtracking Helper
- 71\. Simplify Path
- 394\. Decode String
- 735\. Asteroid Collision

### Min Stack Design
- 155\. Min Stack

### Largest Rectangle in Histogram
- 84\. Largest Rectangle in Histogram
- 85\. Maximal Rectangle

## Implementation Approach

When using a stack to solve problems:

1. **Identify Stack Suitability**: Does the problem involve:
   - Matching pairs
   - Processing elements in reverse order
   - Tracking last-seen elements
   - Implementing undo operations

2. **Choose the Right Stack Variant**:
   - Standard stack
   - Monotonic stack (increasing/decreasing)
   - Augmented stack (with additional data)

3. **Design the Stack Operations**:
   - What to push (sometimes composite data)
   - When to pop
   - What information to extract during pops

4. **Boundary Conditions**:
   - Empty stack handling
   - Stack overflow protection
   - Post-processing remaining stack elements

The implementations in this section demonstrate these patterns with well-commented code examples for each pattern type.
