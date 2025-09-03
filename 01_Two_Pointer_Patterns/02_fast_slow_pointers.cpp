/**
 * Pattern: Two Pointers - Fast & Slow (Cycle Detection)
 * 
 * Description:
 * The Fast & Slow pointers pattern (also known as Floyd's Tortoise and Hare algorithm) uses 
 * two pointers that move at different speeds through a sequence. This approach is particularly 
 * useful for cycle detection, finding the middle element, or solving problems that benefit 
 * from this differential speed approach.
 * 
 * Time Complexity: O(n) - where n is the size of the input
 * Space Complexity: O(1) - only requires a constant amount of extra space
 * 
 * When to use:
 * - Detecting cycles in linked lists or arrays
 * - Finding the middle element of a linked list
 * - Determining if a number is happy (LeetCode 202)
 * - Finding a duplicate in an array with values 1 to n
 * 
 * LeetCode Problems:
 * - 141. Linked List Cycle
 * - 142. Linked List Cycle II (Finding the start of the cycle)
 * - 202. Happy Number
 * - 234. Palindrome Linked List (using fast/slow to find middle)
 * - 287. Find the Duplicate Number
 * - 876. Middle of the Linked List
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Example 1: Detect cycle in a linked list
// LeetCode 141: https://leetcode.com/problems/linked-list-cycle/
bool hasCycle(ListNode *head) {
    if (!head || !head->next) {
        return false; // Empty list or single node can't have cycle
    }
    
    ListNode *slow = head;
    ListNode *fast = head;
    
    // Fast pointer moves twice as fast as slow pointer
    // If there's a cycle, fast will eventually catch up to slow
    while (fast && fast->next) {
        slow = slow->next;       // Move slow pointer one step
        fast = fast->next->next; // Move fast pointer two steps
        
        if (slow == fast) {
            return true; // Cycle detected when pointers meet
        }
    }
    
    // If fast reaches the end (null), there's no cycle
    return false;
}

// Example 2: Find the start point of a cycle
// LeetCode 142: https://leetcode.com/problems/linked-list-cycle-ii/
ListNode* detectCycle(ListNode *head) {
    if (!head || !head->next) {
        return nullptr; // No cycle in empty list or single node
    }
    
    ListNode *slow = head;
    ListNode *fast = head;
    bool hasCycle = false;
    
    // Phase 1: Determine if there's a cycle and find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }
    
    // No cycle found
    if (!hasCycle) {
        return nullptr;
    }
    
    // Phase 2: Find the start of the cycle
    // Reset slow to head, keep fast at meeting point
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // When they meet again, it's at the start of the cycle
    return slow;
}

// Example 3: Find the middle of a linked list
// LeetCode 876: https://leetcode.com/problems/middle-of-the-linked-list/
ListNode* middleNode(ListNode* head) {
    if (!head || !head->next) {
        return head; // For empty list or single node, return head
    }
    
    ListNode *slow = head;
    ListNode *fast = head;
    
    // When fast reaches the end, slow will be at the middle
    // For even length lists, returns the second middle node
    while (fast && fast->next) {
        slow = slow->next;       // Move one step
        fast = fast->next->next; // Move two steps
    }
    
    return slow; // Slow is at the middle
}

// Example 4: Happy Number
// LeetCode 202: https://leetcode.com/problems/happy-number/
// Calculates the sum of squares of digits
int getNext(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n;
    int fast = getNext(n); // Fast starts one step ahead
    
    // If the sequence enters a cycle (non-happy), slow and fast will meet
    // If the sequence reaches 1 (happy), the loop will exit
    while (fast != 1 && slow != fast) {
        slow = getNext(slow);           // Move one step
        fast = getNext(getNext(fast));  // Move two steps
    }
    
    return fast == 1; // If fast is 1, it's a happy number
}

// Example 5: Find the Duplicate Number
// LeetCode 287: https://leetcode.com/problems/find-the-duplicate-number/
// Treats array values as pointers to next indices, forming an implicit linked list
int findDuplicate(vector<int>& nums) {
    // Start both pointers at the beginning
    int slow = nums[0];
    int fast = nums[0];
    
    // Phase 1: Find meeting point inside the cycle
    do {
        slow = nums[slow];          // Move one step
        fast = nums[nums[fast]];    // Move two steps
    } while (slow != fast);
    
    // Phase 2: Find the entrance to the cycle (the duplicate)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow; // This is the duplicate number
}

// Example 6: Check if a linked list is a palindrome
// LeetCode 234: https://leetcode.com/problems/palindrome-linked-list/
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) {
        return true; // Empty list or single node is palindrome
    }
    
    // Step 1: Find the middle using fast & slow pointers
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // slow points to the middle node
    
    // Step 2: Reverse the second half of the list
    ListNode* prev = nullptr;
    ListNode* curr = slow->next;
    
    while (curr) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    
    // prev now points to the head of the reversed second half
    
    // Step 3: Compare the first half with the reversed second half
    ListNode* firstHalf = head;
    ListNode* secondHalf = prev;
    
    while (secondHalf) {
        if (firstHalf->val != secondHalf->val) {
            return false; // Not a palindrome
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    return true; // Is a palindrome
}

// Utility function to create a linked list for testing
ListNode* createLinkedList(vector<int> values, int pos = -1) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    ListNode* cycleNode = nullptr;
    
    if (pos == 0) cycleNode = head;
    
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
        
        if (i == pos) cycleNode = current;
    }
    
    // Create cycle if pos is valid
    if (cycleNode) {
        current->next = cycleNode;
    }
    
    return head;
}

// Utility function to print a linked list (up to n nodes to avoid infinite loop)
void printList(ListNode* head, int n = 10) {
    while (head && n--) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << (n < 0 ? "... (more nodes)" : "nullptr") << endl;
}

// Main function to demonstrate the Fast & Slow Pointers pattern
void demonstrateFastSlowPointers() {
    cout << "Example 1: Linked List Cycle" << endl;
    ListNode* cycleList = createLinkedList({3, 2, 0, -4}, 1); // Cycle at position 1
    cout << "Has cycle: " << (hasCycle(cycleList) ? "true" : "false") << endl;
    
    cout << "\nExample 2: Linked List Cycle II (Start of Cycle)" << endl;
    ListNode* cycleNode = detectCycle(cycleList);
    cout << "Cycle starts at node with value: " << (cycleNode ? to_string(cycleNode->val) : "no cycle") << endl;
    
    cout << "\nExample 3: Middle of Linked List" << endl;
    ListNode* regularList = createLinkedList({1, 2, 3, 4, 5});
    cout << "Original list: ";
    printList(regularList);
    ListNode* middle = middleNode(regularList);
    cout << "Middle node value: " << middle->val << endl;
    
    cout << "\nExample 4: Happy Number" << endl;
    int num = 19;
    cout << num << " is " << (isHappy(num) ? "a happy number" : "not a happy number") << endl;
    
    cout << "\nExample 5: Find the Duplicate Number" << endl;
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << "Duplicate number: " << findDuplicate(nums) << endl;
    
    cout << "\nExample 6: Palindrome Linked List" << endl;
    ListNode* palindromeList = createLinkedList({1, 2, 3, 2, 1});
    cout << "Original list: ";
    printList(palindromeList);
    cout << "Is palindrome: " << (isPalindrome(palindromeList) ? "true" : "false") << endl;
    
    // Clean up memory (not handling the cyclic list to avoid infinite loop)
    // In a real application, you would need proper memory management
}

int main() {
    // Demonstrate the Fast & Slow Pointers pattern
    demonstrateFastSlowPointers();
    
    return 0;
}
