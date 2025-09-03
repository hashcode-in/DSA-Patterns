/**
 * Pattern: Stack - Min Stack Design
 * 
 * Description:
 * This pattern involves designing a stack that supports push, pop, top, and retrieving
 * the minimum element in constant time. The key challenge is maintaining the minimum
 * value efficiently as elements are pushed and popped, without having to scan the
 * entire stack each time.
 * 
 * Time Complexity: O(1) for all operations (push, pop, top, getMin)
 * Space Complexity: O(n) where n is the number of elements in the stack
 * 
 * When to use:
 * - When you need to track the minimum (or maximum) value in a stack
 * - When you need constant-time access to the extreme value while maintaining LIFO order
 * - When implementing algorithms that require both stack operations and min/max value queries
 * 
 * LeetCode Problems:
 * - 155. Min Stack
 * - Similar concepts in: Stack with max, Queue with min/max
 */

#include <iostream>
#include <stack>
#include <vector>
#include <climits>
#include <utility>  // for std::pair
#include <tuple>    // for std::tuple, std::make_tuple, std::get

using namespace std;

// Example 1: Min Stack - Using Two Stacks
// LeetCode 155: https://leetcode.com/problems/min-stack/
class MinStack {
private:
    stack<int> dataStack;     // Main stack for data
    stack<int> minStack;      // Auxiliary stack to track minimums
    
public:
    MinStack() {
        // No initialization needed for stack
    }
    
    void push(int val) {
        dataStack.push(val);
        
        // Push to minStack either the new minimum or the current value
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        } else {
            minStack.push(minStack.top());  // Duplicate the current minimum
        }
    }
    
    void pop() {
        if (dataStack.empty()) {
            return;  // Stack is empty
        }
        
        // Pop from both stacks
        dataStack.pop();
        minStack.pop();
    }
    
    int top() {
        return dataStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// Example 2: Min Stack - Using One Stack with Pairs
class MinStackPairs {
private:
    stack<pair<int, int>> st;  // Stack of (value, current minimum) pairs
    
public:
    MinStackPairs() {
        // No initialization needed for stack
    }
    
    void push(int val) {
        // If stack is empty, the minimum is the value itself
        if (st.empty()) {
            st.push({val, val});
        } else {
            // Otherwise, minimum is either the current minimum or the new value
            int currentMin = min(st.top().second, val);
            st.push({val, currentMin});
        }
    }
    
    void pop() {
        if (!st.empty()) {
            st.pop();
        }
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

// Example 3: Min Stack - Using One Stack with State Change Detection
class MinStackOptimized {
private:
    stack<int> st;        // Main stack
    int minVal;           // Current minimum value
    
public:
    MinStackOptimized() : minVal(INT_MAX) {
        // Initialize minVal to maximum possible value
    }
    
    void push(int val) {
        // If new value is less than or equal to current minimum,
        // push the old minimum first, then update minimum
        if (val <= minVal) {
            st.push(minVal);   // Push old minimum
            minVal = val;      // Update minimum
        }
        
        st.push(val);  // Push the actual value
    }
    
    void pop() {
        if (st.empty()) {
            return;
        }
        
        int poppedVal = st.top();
        st.pop();
        
        // If popped value is the current minimum,
        // restore the previous minimum
        if (poppedVal == minVal) {
            minVal = st.top();  // Restore previous minimum
            st.pop();          // Remove the stored old minimum
        }
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minVal;
    }
};

// Example 4: Max Stack Implementation
class MaxStack {
private:
    stack<int> dataStack;
    stack<int> maxStack;
    
public:
    MaxStack() {
        // No initialization needed for stacks
    }
    
    void push(int val) {
        dataStack.push(val);
        
        // Update maximum value
        if (maxStack.empty() || val >= maxStack.top()) {
            maxStack.push(val);
        } else {
            maxStack.push(maxStack.top());
        }
    }
    
    int pop() {
        int val = dataStack.top();
        dataStack.pop();
        maxStack.pop();
        return val;
    }
    
    int top() {
        return dataStack.top();
    }
    
    int peekMax() {
        return maxStack.top();
    }
    
    int popMax() {
        // Temporary stack to store popped elements
        stack<int> temp;
        int max = peekMax();
        
        // Pop elements until we find the maximum
        while (top() != max) {
            temp.push(pop());
        }
        
        // Remove the maximum element
        pop();
        
        // Push back other elements
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
        
        return max;
    }
};

// Example 5: Min-Max Stack Implementation
class MinMaxStack {
private:
    // Stack to store (value, min, max) tuples
    vector<std::tuple<int, int, int>> stack;
    
public:
    MinMaxStack() {
        // No initialization needed
    }
    
    void push(int val) {
        if (stack.empty()) {
            // First element - min and max are both val
            stack.push_back(std::make_tuple(val, val, val));
        } else {
            // Get current min and max
            int currentMin = std::get<1>(stack.back());
            int currentMax = std::get<2>(stack.back());
            
            // Update min and max
            int newMin = std::min(currentMin, val);
            int newMax = std::max(currentMax, val);
            
            // Push new value with updated min and max
            stack.push_back(std::make_tuple(val, newMin, newMax));
        }
    }
    
    int pop() {
        int val = std::get<0>(stack.back());
        stack.pop_back();
        return val;
    }
    
    int top() {
        return std::get<0>(stack.back());
    }
    
    int getMin() {
        return std::get<1>(stack.back());
    }
    
    int getMax() {
        return std::get<2>(stack.back());
    }
};

// Main function to demonstrate the Min Stack Design pattern
int main() {
    // Example 1: Min Stack - Using Two Stacks
    cout << "Example 1: Min Stack - Using Two Stacks" << endl;
    
    MinStack minStack1;
    minStack1.push(-2);
    minStack1.push(0);
    minStack1.push(-3);
    cout << "Current minimum: " << minStack1.getMin() << " (expected: -3)" << endl;
    
    minStack1.pop();
    cout << "After popping -3, top: " << minStack1.top() << " (expected: 0)" << endl;
    cout << "Current minimum: " << minStack1.getMin() << " (expected: -2)" << endl;
    cout << endl;
    
    // Example 2: Min Stack - Using One Stack with Pairs
    cout << "Example 2: Min Stack - Using One Stack with Pairs" << endl;
    
    MinStackPairs minStack2;
    minStack2.push(-2);
    minStack2.push(0);
    minStack2.push(-3);
    cout << "Current minimum: " << minStack2.getMin() << " (expected: -3)" << endl;
    
    minStack2.pop();
    cout << "After popping -3, top: " << minStack2.top() << " (expected: 0)" << endl;
    cout << "Current minimum: " << minStack2.getMin() << " (expected: -2)" << endl;
    cout << endl;
    
    // Example 3: Min Stack - Using One Stack with State Change Detection
    cout << "Example 3: Min Stack - Using One Stack with State Change Detection" << endl;
    
    MinStackOptimized minStack3;
    minStack3.push(-2);
    minStack3.push(0);
    minStack3.push(-3);
    cout << "Current minimum: " << minStack3.getMin() << " (expected: -3)" << endl;
    
    minStack3.pop();
    cout << "After popping -3, top: " << minStack3.top() << " (expected: 0)" << endl;
    cout << "Current minimum: " << minStack3.getMin() << " (expected: -2)" << endl;
    cout << endl;
    
    // Example 4: Max Stack Implementation
    cout << "Example 4: Max Stack Implementation" << endl;
    
    MaxStack maxStack;
    maxStack.push(5);
    maxStack.push(1);
    maxStack.push(5);
    cout << "Current maximum: " << maxStack.peekMax() << " (expected: 5)" << endl;
    
    cout << "Pop max: " << maxStack.popMax() << " (expected: 5)" << endl;
    cout << "Current top: " << maxStack.top() << " (expected: 1)" << endl;
    cout << "Current maximum: " << maxStack.peekMax() << " (expected: 5)" << endl;
    
    cout << "Pop max again: " << maxStack.popMax() << " (expected: 5)" << endl;
    cout << "Current top: " << maxStack.top() << " (expected: 1)" << endl;
    cout << endl;
    
    // Example 5: Min-Max Stack Implementation
    cout << "Example 5: Min-Max Stack Implementation" << endl;
    
    MinMaxStack minMaxStack;
    minMaxStack.push(5);
    minMaxStack.push(1);
    minMaxStack.push(3);
    minMaxStack.push(2);
    
    cout << "Current minimum: " << minMaxStack.getMin() << " (expected: 1)" << endl;
    cout << "Current maximum: " << minMaxStack.getMax() << " (expected: 5)" << endl;
    
    minMaxStack.pop();
    cout << "After popping 2, top: " << minMaxStack.top() << " (expected: 3)" << endl;
    cout << "Current minimum: " << minMaxStack.getMin() << " (expected: 1)" << endl;
    cout << "Current maximum: " << minMaxStack.getMax() << " (expected: 5)" << endl;
    
    return 0;
}
