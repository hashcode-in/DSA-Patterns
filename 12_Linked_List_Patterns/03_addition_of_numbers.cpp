/**
 * Pattern: Linked List - Addition of Numbers
 * 
 * Description:
 * This pattern focuses on representing numbers as linked lists (usually one digit per node)
 * and performing arithmetic operations on them. The key insight is handling the carry
 * and propagating it through the calculation.
 * 
 * Time Complexity: O(max(n,m)) where n and m are the lengths of the input lists
 * Space Complexity: O(max(n,m)) for the result list
 * 
 * When to use:
 * - When working with large numbers that don't fit in standard numeric types
 * - When performing arithmetic on numbers represented as linked lists
 * - When digits need to be processed sequentially
 * 
 * LeetCode Problems:
 * - 2. Add Two Numbers
 * - 369. Plus One Linked List
 * - 445. Add Two Numbers II
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// Helper function to print a linked list
void printLinkedList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

// Helper function to free memory of a linked list
void deleteLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// Example 1: Add Two Numbers (lists are stored in reverse order)
// LeetCode 2: https://leetcode.com/problems/add-two-numbers/
class AddTwoNumbers {
public:
    // The input lists represent numbers in reverse order (least significant digit first)
    // e.g., 2->4->3 represents 342
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);  // Dummy head
        ListNode* current = &dummy;
        int carry = 0;
        
        // Process both lists while there are nodes
        while (l1 != nullptr || l2 != nullptr) {
            int x = (l1 != nullptr) ? l1->val : 0;
            int y = (l2 != nullptr) ? l2->val : 0;
            
            int sum = x + y + carry;
            carry = sum / 10;  // Calculate carry for next position
            
            // Create new node with the digit
            current->next = new ListNode(sum % 10);
            current = current->next;
            
            // Move to the next nodes if they exist
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        
        // Handle final carry if there is one
        if (carry > 0) {
            current->next = new ListNode(carry);
        }
        
        return dummy.next;
    }
};

// Example 2: Add Two Numbers II (lists are stored in normal order)
// LeetCode 445: https://leetcode.com/problems/add-two-numbers-ii/
class AddTwoNumbersII {
public:
    // Approach 1: Using stacks to reverse the order
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        
        // Push all digits from first list to stack
        while (l1 != nullptr) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        
        // Push all digits from second list to stack
        while (l2 != nullptr) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        
        int carry = 0;
        ListNode* result = nullptr;  // Result list head
        
        // Process digits from stacks
        while (!s1.empty() || !s2.empty() || carry > 0) {
            int sum = carry;
            
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }
            
            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }
            
            // Create new node and prepend to result
            ListNode* newNode = new ListNode(sum % 10);
            newNode->next = result;
            result = newNode;
            
            carry = sum / 10;  // Update carry for next iteration
        }
        
        return result;
    }
    
    // Approach 2: Reverse the lists, add them, then reverse the result
    ListNode* addTwoNumbersReverse(ListNode* l1, ListNode* l2) {
        // Reverse both input lists
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
        // Add the reversed lists (similar to Example 1)
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;
        
        while (l1 != nullptr || l2 != nullptr || carry > 0) {
            int x = (l1 != nullptr) ? l1->val : 0;
            int y = (l2 != nullptr) ? l2->val : 0;
            
            int sum = x + y + carry;
            carry = sum / 10;
            
            current->next = new ListNode(sum % 10);
            current = current->next;
            
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        
        // Reverse the result back to normal order
        return reverseList(dummy.next);
    }
    
private:
    // Helper function to reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
};

// Example 3: Plus One Linked List
// LeetCode 369: https://leetcode.com/problems/plus-one-linked-list/
class PlusOneLinkedList {
public:
    // Approach 1: Reverse the list, add one, then reverse back
    ListNode* plusOne(ListNode* head) {
        if (head == nullptr) return nullptr;
        
        // Reverse the list
        head = reverseList(head);
        
        // Add one to the first node (least significant digit)
        ListNode* current = head;
        int carry = 1;  // Start with carry = 1 (the "plus one")
        
        while (current != nullptr && carry > 0) {
            int sum = current->val + carry;
            current->val = sum % 10;
            carry = sum / 10;
            
            // If we have a carry but this is the last node
            if (carry > 0 && current->next == nullptr) {
                current->next = new ListNode(carry);
                break;
            }
            
            current = current->next;
        }
        
        // Reverse the list back
        return reverseList(head);
    }
    
    // Approach 2: Using a dummy head and finding the rightmost non-9 digit
    ListNode* plusOneOptimized(ListNode* head) {
        // Use a dummy head in case the first digit becomes 10
        ListNode dummy(0);
        dummy.next = head;
        
        // Find the rightmost non-9 digit
        ListNode* rightmostNon9 = &dummy;
        ListNode* current = head;
        
        while (current != nullptr) {
            if (current->val != 9) {
                rightmostNon9 = current;
            }
            current = current->next;
        }
        
        // Increment the rightmost non-9 digit
        rightmostNon9->val++;
        
        // Set all digits to the right of rightmost non-9 digit to 0
        current = rightmostNon9->next;
        while (current != nullptr) {
            current->val = 0;
            current = current->next;
        }
        
        // If dummy was incremented, return dummy, otherwise return head
        return (dummy.val == 1) ? &dummy : dummy.next;
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
};

// Example 4: Multiply Numbers (represented as linked lists)
// Similar to LeetCode 43 (Multiply Strings), but with linked lists
class MultiplyLinkedLists {
public:
    // Convert linked list to integer, multiply, and convert back
    // Note: This approach has limitations for very large numbers due to integer overflow
    ListNode* multiply(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr || l2 == nullptr) return nullptr;
        
        // Convert linked lists to integers
        long long num1 = linkedListToInteger(l1);
        long long num2 = linkedListToInteger(l2);
        
        // Multiply the integers
        long long result = num1 * num2;
        
        // Convert the result back to a linked list
        return integerToLinkedList(result);
    }
    
    // Approach for handling larger numbers: digit-by-digit multiplication
    ListNode* multiplyLarge(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr || l2 == nullptr) return nullptr;
        
        // Reverse both lists to simplify multiplication
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
        ListNode dummy(0);
        ListNode* result = &dummy;
        
        // Iterate through each digit of the second number
        ListNode* digit2 = l2;
        int position = 0;  // Position offset for each partial product
        
        while (digit2 != nullptr) {
            // Create a partial product by multiplying first number with current digit
            ListNode* partialProduct = multiplyByDigit(l1, digit2->val);
            
            // Add zeros at the beginning based on position
            for (int i = 0; i < position; i++) {
                ListNode* zero = new ListNode(0);
                zero->next = partialProduct;
                partialProduct = zero;
            }
            
            // Add partial product to result
            result->next = addLists(result->next, partialProduct);
            
            digit2 = digit2->next;
            position++;
        }
        
        // Reverse the result back to normal order
        result = reverseList(result->next);
        
        // Remove leading zeros
        while (result != nullptr && result->val == 0) {
            ListNode* temp = result;
            result = result->next;
            delete temp;
        }
        
        return (result == nullptr) ? new ListNode(0) : result;
    }

private:
    // Convert linked list to integer (for smaller numbers only)
    long long linkedListToInteger(ListNode* head) {
        long long result = 0;
        
        while (head != nullptr) {
            result = result * 10 + head->val;
            head = head->next;
        }
        
        return result;
    }
    
    // Convert integer to linked list (for smaller numbers only)
    ListNode* integerToLinkedList(long long num) {
        if (num == 0) return new ListNode(0);
        
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (num > 0) {
            int digit = num % 10;
            num /= 10;
            current->next = new ListNode(digit);
            current = current->next;
        }
        
        // Reverse the list to get the correct order
        ListNode* reversed = reverseList(dummy.next);
        return reversed;
    }
    
    // Multiply a linked list (representing a number) by a single digit
    ListNode* multiplyByDigit(ListNode* list, int digit) {
        if (digit == 0) return new ListNode(0);
        
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;
        
        while (list != nullptr || carry > 0) {
            int x = (list != nullptr) ? list->val : 0;
            int product = x * digit + carry;
            
            carry = product / 10;
            current->next = new ListNode(product % 10);
            current = current->next;
            
            if (list != nullptr) list = list->next;
        }
        
        return dummy.next;
    }
    
    // Add two linked lists (similar to AddTwoNumbers)
    ListNode* addLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;
        
        while (l1 != nullptr || l2 != nullptr || carry > 0) {
            int x = (l1 != nullptr) ? l1->val : 0;
            int y = (l2 != nullptr) ? l2->val : 0;
            
            int sum = x + y + carry;
            carry = sum / 10;
            
            current->next = new ListNode(sum % 10);
            current = current->next;
            
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        
        return dummy.next;
    }
    
    // Reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
};

// Main function to demonstrate the Linked List Addition of Numbers pattern
int main() {
    // Example 1: Add Two Numbers (lists in reverse order)
    cout << "Example 1: Add Two Numbers (lists in reverse order)" << endl;
    // 2->4->3 represents 342
    vector<int> values1 = {2, 4, 3};
    // 5->6->4 represents 465
    vector<int> values2 = {5, 6, 4};
    
    ListNode* l1 = createLinkedList(values1);
    ListNode* l2 = createLinkedList(values2);
    
    cout << "Number 1 (reversed): ";
    printLinkedList(l1);
    
    cout << "Number 2 (reversed): ";
    printLinkedList(l2);
    
    AddTwoNumbers adder;
    ListNode* sum = adder.addTwoNumbers(l1, l2);
    
    cout << "Sum (reversed): ";
    printLinkedList(sum);
    cout << "Represents: 342 + 465 = 807" << endl;
    
    deleteLinkedList(sum);
    cout << endl;
    
    // Example 2: Add Two Numbers II (lists in normal order)
    cout << "Example 2: Add Two Numbers II (lists in normal order)" << endl;
    // 7->2->4->3 represents 7243
    vector<int> values3 = {7, 2, 4, 3};
    // 5->6->4 represents 564
    vector<int> values4 = {5, 6, 4};
    
    ListNode* l3 = createLinkedList(values3);
    ListNode* l4 = createLinkedList(values4);
    
    cout << "Number 1: ";
    printLinkedList(l3);
    
    cout << "Number 2: ";
    printLinkedList(l4);
    
    AddTwoNumbersII adderII;
    ListNode* sumII = adderII.addTwoNumbers(l3, l4);
    
    cout << "Sum: ";
    printLinkedList(sumII);
    cout << "Represents: 7243 + 564 = 7807" << endl;
    
    // Test reversal approach
    ListNode* l3Copy = createLinkedList(values3);
    ListNode* l4Copy = createLinkedList(values4);
    
    ListNode* sumIIReverse = adderII.addTwoNumbersReverse(l3Copy, l4Copy);
    
    cout << "Sum (using reversal): ";
    printLinkedList(sumIIReverse);
    
    deleteLinkedList(sumII);
    deleteLinkedList(sumIIReverse);
    cout << endl;
    
    // Example 3: Plus One Linked List
    cout << "Example 3: Plus One Linked List" << endl;
    // 1->2->3 represents 123
    vector<int> values5 = {1, 2, 3};
    // 9->9->9 represents 999 (edge case)
    vector<int> values6 = {9, 9, 9};
    
    ListNode* l5 = createLinkedList(values5);
    ListNode* l6 = createLinkedList(values6);
    
    cout << "Number 1: ";
    printLinkedList(l5);
    
    PlusOneLinkedList plusOne;
    ListNode* plusOneResult = plusOne.plusOne(l5);
    
    cout << "Plus one: ";
    printLinkedList(plusOneResult);
    cout << "Represents: 123 + 1 = 124" << endl;
    
    cout << "Number 2 (edge case): ";
    printLinkedList(l6);
    
    ListNode* plusOneEdgeCase = plusOne.plusOne(l6);
    
    cout << "Plus one: ";
    printLinkedList(plusOneEdgeCase);
    cout << "Represents: 999 + 1 = 1000" << endl;
    
    deleteLinkedList(plusOneResult);
    deleteLinkedList(plusOneEdgeCase);
    cout << endl;
    
    // Example 4: Multiply Numbers (represented as linked lists)
    cout << "Example 4: Multiply Linked Lists" << endl;
    // 2->3 represents 23
    vector<int> values7 = {2, 3};
    // 4->5 represents 45
    vector<int> values8 = {4, 5};
    
    ListNode* l7 = createLinkedList(values7);
    ListNode* l8 = createLinkedList(values8);
    
    cout << "Number 1: ";
    printLinkedList(l7);
    
    cout << "Number 2: ";
    printLinkedList(l8);
    
    MultiplyLinkedLists multiplier;
    ListNode* product = multiplier.multiply(l7, l8);
    
    cout << "Product: ";
    printLinkedList(product);
    cout << "Represents: 23 * 45 = 1035" << endl;
    
    // Test large multiplication
    ListNode* l7Copy = createLinkedList(values7);
    ListNode* l8Copy = createLinkedList(values8);
    
    ListNode* productLarge = multiplier.multiplyLarge(l7Copy, l8Copy);
    
    cout << "Product (using digit-by-digit): ";
    printLinkedList(productLarge);
    
    deleteLinkedList(product);
    deleteLinkedList(productLarge);
    
    return 0;
}
