# Bit Manipulation Patterns

This directory contains implementations of common Bit Manipulation patterns used in algorithmic problem solving.

## Patterns Included

1. **Bitwise XOR - Finding Single/Missing Number**
   - Using XOR to find a single number or missing number in a collection
   - Example problems: Single Number, Missing Number

2. **Bitwise AND - Counting Set Bits (Hamming Weight)**
   - Techniques for counting the number of set bits (1s) in a binary representation
   - Example problems: Number of 1 Bits

3. **Bitwise DP - Counting Bits Optimization**
   - Using dynamic programming with bit manipulation
   - Example problems: Counting Bits

4. **Bitwise Operations - Power of Two/Four Check**
   - Efficient ways to check if a number is a power of two or four
   - Example problems: Power of Two, Power of Four

## When to Use These Patterns

Bit manipulation patterns are useful when:

- You need to optimize space usage to the extreme
- You're dealing with problems involving binary representations
- You need to perform operations in constant time regardless of input size
- Working with problems related to finding duplicates or missing numbers
- Implementing low-level operations or optimizations

## Time and Space Complexity

Most bit manipulation operations have:
- Time Complexity: O(1) or O(log n) where n is the number of bits
- Space Complexity: O(1)

## Key Techniques

- Using XOR for finding unique elements
- Bit shifting (>>, <<)
- Bitwise operations (AND, OR, XOR, NOT)
- Bit masking to isolate specific bits
- Brian Kernighan's algorithm for counting set bits
