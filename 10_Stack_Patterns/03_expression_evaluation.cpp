/**
 * Pattern: Stack - Expression Evaluation (RPN/Infix/Postfix)
 * 
 * Description:
 * This pattern uses a stack to evaluate mathematical expressions in various notations:
 * - Infix: operators are placed between operands (e.g., 3 + 4)
 * - Postfix (RPN): operators are placed after operands (e.g., 3 4 +)
 * - Prefix: operators are placed before operands (e.g., + 3 4)
 * 
 * Stacks are particularly useful for expression evaluation because:
 * 1. In RPN, we can push operands and evaluate when we encounter operators
 * 2. For infix, we can handle operator precedence and parentheses
 * 3. We can convert between different notations
 * 
 * Time Complexity: O(n) where n is the length of the expression
 * Space Complexity: O(n) for the stack
 * 
 * When to use:
 * - When evaluating mathematical expressions
 * - When parsing expressions with operator precedence
 * - When implementing calculators or expression evaluators
 * - When converting between infix, postfix, and prefix notations
 * 
 * LeetCode Problems:
 * - 150. Evaluate Reverse Polish Notation
 * - 224. Basic Calculator
 * - 227. Basic Calculator II
 * - 772. Basic Calculator III
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype>  // for isdigit, isspace

using namespace std;

// Example 1: Evaluate Reverse Polish Notation (Postfix)
// LeetCode 150: https://leetcode.com/problems/evaluate-reverse-polish-notation/
class EvaluateRPN {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            // If token is an operator, pop two values from stack, apply operator, and push result
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Need at least two operands for an operation
                if (st.size() < 2) {
                    return 0;  // Invalid expression
                }
                
                int val2 = st.top(); st.pop();
                int val1 = st.top(); st.pop();
                
                if (token == "+") {
                    st.push(val1 + val2);
                } else if (token == "-") {
                    st.push(val1 - val2);
                } else if (token == "*") {
                    st.push(val1 * val2);
                } else if (token == "/") {
                    st.push(val1 / val2);
                }
            } else {
                // Token is an operand, push to stack
                st.push(stoi(token));
            }
        }
        
        // The final result should be the only value in the stack
        return st.top();
    }
};

// Example 2: Basic Calculator (Infix with parentheses and +/-)
// LeetCode 224: https://leetcode.com/problems/basic-calculator/
class BasicCalculator {
public:
    int calculate(string s) {
        stack<int> st;
        int result = 0;  // Running result
        int number = 0;  // Current number being parsed
        int sign = 1;    // 1 for positive, -1 for negative
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            
            if (isdigit(c)) {
                // Parse multi-digit numbers
                number = number * 10 + (c - '0');
            } else if (c == '+') {
                // Evaluate the previous expression
                result += sign * number;
                // Reset for the next number
                number = 0;
                sign = 1;
            } else if (c == '-') {
                // Evaluate the previous expression
                result += sign * number;
                // Reset for the next number
                number = 0;
                sign = -1;
            } else if (c == '(') {
                // Save the current result and sign to stack
                st.push(result);
                st.push(sign);
                // Reset the result and sign for the subexpression
                result = 0;
                sign = 1;
            } else if (c == ')') {
                // Evaluate the subexpression
                result += sign * number;
                number = 0;
                
                // Apply the sign from before the parenthesis
                result *= st.top(); st.pop();
                // Add the result from before the parenthesis
                result += st.top(); st.pop();
            }
            // Ignore spaces
        }
        
        // Add the last number
        result += sign * number;
        
        return result;
    }
};

// Example 3: Basic Calculator II (Infix with +, -, *, /)
// LeetCode 227: https://leetcode.com/problems/basic-calculator-ii/
class BasicCalculatorII {
public:
    int calculate(string s) {
        stack<int> st;
        int currentNumber = 0;
        char operation = '+'; // Default start operation
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            
            if (isdigit(c)) {
                // Parse multi-digit numbers
                currentNumber = currentNumber * 10 + (c - '0');
            }
            
            // If current char is an operator or last char of string
            if ((!isdigit(c) && !isspace(c)) || i == s.length() - 1) {
                if (operation == '+') {
                    st.push(currentNumber);
                } else if (operation == '-') {
                    st.push(-currentNumber);
                } else if (operation == '*') {
                    int top = st.top();
                    st.pop();
                    st.push(top * currentNumber);
                } else if (operation == '/') {
                    int top = st.top();
                    st.pop();
                    st.push(top / currentNumber);
                }
                
                // Reset for next number and update operation
                operation = c;
                currentNumber = 0;
            }
        }
        
        // Sum up all values in the stack
        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        
        return result;
    }
};

// Example 4: Basic Calculator III (Infix with +, -, *, /, parentheses)
// LeetCode 772: https://leetcode.com/problems/basic-calculator-iii/ (Premium)
class BasicCalculatorIII {
public:
    int calculate(string s) {
        int i = 0;
        return parseExpression(s, i);
    }
    
private:
    // Parse expression until end of string or closing parenthesis
    int parseExpression(const string& s, int& i) {
        stack<int> st;
        int currentNumber = 0;
        char operation = '+'; // Default start operation
        
        while (i < s.length() && s[i] != ')') {
            char c = s[i++];
            
            if (isdigit(c)) {
                // Parse multi-digit numbers
                currentNumber = currentNumber * 10 + (c - '0');
            } else if (c == '(') {
                // Evaluate the sub-expression
                currentNumber = parseExpression(s, i);
            }
            
            // If current char is an operator or last char of string
            if ((!isdigit(c) && !isspace(c) && c != '(') || i == s.length() || s[i] == ')') {
                if (operation == '+') {
                    st.push(currentNumber);
                } else if (operation == '-') {
                    st.push(-currentNumber);
                } else if (operation == '*') {
                    int top = st.top();
                    st.pop();
                    st.push(top * currentNumber);
                } else if (operation == '/') {
                    int top = st.top();
                    st.pop();
                    st.push(top / currentNumber);
                }
                
                // Reset for next number and update operation
                operation = c;
                currentNumber = 0;
            }
        }
        
        // Skip the closing parenthesis
        if (i < s.length() && s[i] == ')') {
            i++;
        }
        
        // Sum up all values in the stack
        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        
        return result;
    }
};

// Example 5: Infix to Postfix Conversion
class InfixToPostfix {
public:
    string convert(string infix) {
        stack<char> st;
        string postfix = "";
        
        // Define operator precedence
        unordered_map<char, int> precedence;
        precedence['+'] = precedence['-'] = 1;
        precedence['*'] = precedence['/'] = 2;
        precedence['^'] = 3;  // Exponentiation
        
        for (char c : infix) {
            if (isalnum(c)) {
                // Operand, add to output
                postfix += c;
            } else if (c == '(') {
                // Opening parenthesis, push to stack
                st.push(c);
            } else if (c == ')') {
                // Closing parenthesis, pop until matching opening parenthesis
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                }
                // Pop the opening parenthesis
                if (!st.empty()) {
                    st.pop();
                }
            } else {
                // Operator
                // Pop operators with higher or equal precedence
                while (!st.empty() && st.top() != '(' && 
                       (precedence[c] <= precedence[st.top()])) {
                    postfix += st.top();
                    st.pop();
                }
                // Push the current operator
                st.push(c);
            }
        }
        
        // Pop remaining operators
        while (!st.empty()) {
            if (st.top() != '(') {
                postfix += st.top();
            }
            st.pop();
        }
        
        return postfix;
    }
};

// Example 6: Infix to Prefix Conversion
class InfixToPrefix {
public:
    string convert(string infix) {
        // Reverse the infix expression
        reverse(infix.begin(), infix.end());
        
        // Swap '(' and ')'
        for (int i = 0; i < infix.length(); i++) {
            if (infix[i] == '(') {
                infix[i] = ')';
            } else if (infix[i] == ')') {
                infix[i] = '(';
            }
        }
        
        // Get postfix of the modified expression
        InfixToPostfix converter;
        string postfix = converter.convert(infix);
        
        // Reverse the postfix expression to get prefix
        reverse(postfix.begin(), postfix.end());
        
        return postfix;
    }
};

// Example 7: Postfix to Infix Conversion
class PostfixToInfix {
public:
    string convert(string postfix) {
        stack<string> st;
        
        for (char c : postfix) {
            if (isalnum(c)) {
                // Operand, push to stack
                st.push(string(1, c));
            } else {
                // Operator, pop two operands
                string operand2 = st.top(); st.pop();
                string operand1 = st.top(); st.pop();
                
                // Create the infix expression and push back to stack
                string infix = "(" + operand1 + c + operand2 + ")";
                st.push(infix);
            }
        }
        
        // The final result is the only expression in the stack
        return st.top();
    }
};

// Main function to demonstrate the Expression Evaluation pattern
int main() {
    // Example 1: Evaluate Reverse Polish Notation (Postfix)
    cout << "Example 1: Evaluate Reverse Polish Notation" << endl;
    
    EvaluateRPN rpnEvaluator;
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    
    cout << "RPN expression: 2 1 + 3 * (which is (2 + 1) * 3)" << endl;
    cout << "Result: " << rpnEvaluator.evalRPN(tokens1) << endl;
    
    cout << "RPN expression: 4 13 5 / + (which is 4 + (13 / 5))" << endl;
    cout << "Result: " << rpnEvaluator.evalRPN(tokens2) << endl << endl;
    
    // Example 2: Basic Calculator (Infix with parentheses and +/-)
    cout << "Example 2: Basic Calculator" << endl;
    
    BasicCalculator calculator1;
    string expr1 = "1 + 1";
    string expr2 = " 2-1 + 2 ";
    string expr3 = "(1+(4+5+2)-3)+(6+8)";
    
    cout << "Expression: \"" << expr1 << "\"" << endl;
    cout << "Result: " << calculator1.calculate(expr1) << endl;
    
    cout << "Expression: \"" << expr2 << "\"" << endl;
    cout << "Result: " << calculator1.calculate(expr2) << endl;
    
    cout << "Expression: \"" << expr3 << "\"" << endl;
    cout << "Result: " << calculator1.calculate(expr3) << endl << endl;
    
    // Example 3: Basic Calculator II (Infix with +, -, *, /)
    cout << "Example 3: Basic Calculator II" << endl;
    
    BasicCalculatorII calculator2;
    string expr4 = "3+2*2";
    string expr5 = " 3/2 ";
    string expr6 = " 3+5 / 2 ";
    
    cout << "Expression: \"" << expr4 << "\"" << endl;
    cout << "Result: " << calculator2.calculate(expr4) << endl;
    
    cout << "Expression: \"" << expr5 << "\"" << endl;
    cout << "Result: " << calculator2.calculate(expr5) << endl;
    
    cout << "Expression: \"" << expr6 << "\"" << endl;
    cout << "Result: " << calculator2.calculate(expr6) << endl << endl;
    
    // Example 4: Basic Calculator III (Infix with +, -, *, /, parentheses)
    cout << "Example 4: Basic Calculator III" << endl;
    
    BasicCalculatorIII calculator3;
    string expr7 = "1 + 1";
    string expr8 = " 6-4 / 2 ";
    string expr9 = "2*(5+5*2)/3+(6/2+8)";
    
    cout << "Expression: \"" << expr7 << "\"" << endl;
    cout << "Result: " << calculator3.calculate(expr7) << endl;
    
    cout << "Expression: \"" << expr8 << "\"" << endl;
    cout << "Result: " << calculator3.calculate(expr8) << endl;
    
    cout << "Expression: \"" << expr9 << "\"" << endl;
    cout << "Result: " << calculator3.calculate(expr9) << endl << endl;
    
    // Example 5: Infix to Postfix Conversion
    cout << "Example 5: Infix to Postfix Conversion" << endl;
    
    InfixToPostfix infixToPostfix;
    string infix1 = "a+b*c";
    string infix2 = "a+b*(c^d-e)^(f+g*h)-i";
    
    cout << "Infix: \"" << infix1 << "\"" << endl;
    cout << "Postfix: " << infixToPostfix.convert(infix1) << endl;
    
    cout << "Infix: \"" << infix2 << "\"" << endl;
    cout << "Postfix: " << infixToPostfix.convert(infix2) << endl << endl;
    
    // Example 6: Infix to Prefix Conversion
    cout << "Example 6: Infix to Prefix Conversion" << endl;
    
    InfixToPrefix infixToPrefix;
    string infix3 = "a+b*c";
    string infix4 = "(a+b)*(c-d)";
    
    cout << "Infix: \"" << infix3 << "\"" << endl;
    cout << "Prefix: " << infixToPrefix.convert(infix3) << endl;
    
    cout << "Infix: \"" << infix4 << "\"" << endl;
    cout << "Prefix: " << infixToPrefix.convert(infix4) << endl << endl;
    
    // Example 7: Postfix to Infix Conversion
    cout << "Example 7: Postfix to Infix Conversion" << endl;
    
    PostfixToInfix postfixToInfix;
    string postfix1 = "abc*+";
    string postfix2 = "ab+cd-*";
    
    cout << "Postfix: \"" << postfix1 << "\"" << endl;
    cout << "Infix: " << postfixToInfix.convert(postfix1) << endl;
    
    cout << "Postfix: \"" << postfix2 << "\"" << endl;
    cout << "Infix: " << postfixToInfix.convert(postfix2) << endl;
    
    return 0;
}
