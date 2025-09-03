/**
 * Pattern: Linked List - In-place Reversal
 * 
 * Description:
 * This pattern focuses on reversing a linked list or parts of a linked list in-place
 * without using additional data structures. The key insight is to manipulate the next
 * pointers of nodes to reverse their direction.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the linked list
 * Space Complexity: O(1) for iterative approach, O(n) for recursive approach due to call stack
 * 
 * When to use:
 * - When you need to reverse a linked list or a part of it
 * - When you need to detect palindromes in a linked list
 * - When you need to reorder or rearrange linked list nodes
 * 
 * LeetCode Problems:
 * - 206. Reverse Linked List
 * - 92. Reverse Linked List II
 * - 25. Reverse Nodes in k-Group
 * - 234. Palindrome Linked List
 * - 83. Remove Duplicates from Sorted List
 * - 82. Remove Duplicates from Sorted List II
 */

#include <iostream>
#include <vector>

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

// Example 1: Reverse a linked list iteratively
// LeetCode 206: https://leetcode.com/problems/reverse-linked-list/
class ReverseLinkedList {
public:
    // Approach 1: Iterative reversal
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            // Store next node before we change current->next
            ListNode* next = current->next;
            
            // Reverse the link
            current->next = prev;
            
            // Move prev and current one step forward
            prev = current;
            current = next;
        }
        
        // prev is the new head of the reversed list
        return prev;
    }
    
    // Approach 2: Recursive reversal
    ListNode* reverseListRecursive(ListNode* head) {
        // Base cases: empty list or single node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Recursively reverse the rest of the list
        ListNode* newHead = reverseListRecursive(head->next);
        
        // Reverse the link between head and head->next
        head->next->next = head;
        head->next = nullptr;
        
        return newHead;
    }
};

// Example 2: Reverse a linked list between positions m and n
// LeetCode 92: https://leetcode.com/problems/reverse-linked-list-ii/
class ReverseLinkedListII {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr || m == n) {
            return head;
        }
        
        ListNode dummy(0);  // Dummy node to handle edge cases
        dummy.next = head;
        ListNode* prev = &dummy;  // Node before the start of reversal
        
        // Move to the node just before position m
        for (int i = 1; i < m; i++) {
            prev = prev->next;
        }
        
        // Start of the sublist to be reversed
        ListNode* current = prev->next;
        
        // Reverse nodes from position m to n
        for (int i = 0; i < n - m; i++) {
            // Node to be moved
            ListNode* temp = current->next;
            
            // Remove temp from its current position
            current->next = temp->next;
            
            // Insert temp after prev
            temp->next = prev->next;
            prev->next = temp;
        }
        
        return dummy.next;
    }
};

// Example 3: Reverse Nodes in k-Group
// LeetCode 25: https://leetcode.com/problems/reverse-nodes-in-k-group/
class ReverseKGroup {
public:
    // Helper function to reverse k nodes starting from head
    // Returns the new head after reversal
    pair<ListNode*, ListNode*> reverseKNodes(ListNode* head, int k) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        // Reverse k nodes
        for (int i = 0; i < k && current != nullptr; i++) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        // prev is the new head, current is the node after the k group
        return {prev, current};
    }
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k == 1) {
            return head;
        }
        
        // Count nodes to see if we have at least k nodes
        ListNode* counter = head;
        int count = 0;
        while (counter != nullptr && count < k) {
            counter = counter->next;
            count++;
        }
        
        // If we have fewer than k nodes, don't reverse
        if (count < k) {
            return head;
        }
        
        // Reverse the first k nodes
        auto [newHead, nextGroup] = reverseKNodes(head, k);
        
        // Recursively reverse the remaining groups
        head->next = reverseKGroup(nextGroup, k);
        
        return newHead;
    }
};

// Example 4: Palindrome Linked List
// LeetCode 234: https://leetcode.com/problems/palindrome-linked-list/
class PalindromeLinkedList {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;  // Empty list or single node is a palindrome
        }
        
        // Find the middle of the linked list using slow and fast pointers
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse the second half of the linked list
        ListNode* secondHalf = reverseList(slow->next);
        ListNode* firstHalf = head;
        
        // Compare first half with reversed second half
        ListNode* p1 = firstHalf;
        ListNode* p2 = secondHalf;
        bool result = true;
        
        while (p2 != nullptr) {
            if (p1->val != p2->val) {
                result = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        
        // Restore the list by reversing the second half again
        slow->next = reverseList(secondHalf);
        
        return result;
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

// Example 5: Remove Duplicates from Sorted List
// LeetCode 83: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
class RemoveDuplicates {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;  // Empty list or single node has no duplicates
        }
        
        ListNode* current = head;
        
        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                // Duplicate found, remove it
                ListNode* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;  // Free memory
            } else {
                // Move to next node
                current = current->next;
            }
        }
        
        return head;
    }
};

// Example 6: Remove Duplicates from Sorted List II
// LeetCode 82: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
class RemoveDuplicatesII {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;  // Empty list or single node has no duplicates
        }
        
        // Dummy node to handle the case when head has duplicates
        ListNode dummy(0);
        dummy.next = head;
        
        ListNode* prev = &dummy;
        ListNode* current = head;
        
        while (current != nullptr) {
            // Skip nodes that have the same value as current
            bool duplicateFound = false;
            while (current->next != nullptr && current->val == current->next->val) {
                duplicateFound = true;
                ListNode* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;  // Free memory
            }
            
            if (duplicateFound) {
                // Remove the last duplicate node (current)
                prev->next = current->next;
                delete current;
                current = prev->next;
            } else {
                // No duplicates for current, move forward
                prev = current;
                current = current->next;
            }
        }
        
        return dummy.next;
    }
};

// Main function to demonstrate the Linked List In-place Reversal pattern
int main() {
    // Example 1: Reverse a linked list
    cout << "Example 1: Reverse a linked list" << endl;
    vector<int> values1 = {1, 2, 3, 4, 5};
    ListNode* list1 = createLinkedList(values1);
    
    cout << "Original list: ";
    printLinkedList(list1);
    
    ReverseLinkedList reverser;
    ListNode* reversed1 = reverser.reverseList(list1);
    
    cout << "Reversed list: ";
    printLinkedList(reversed1);
    
    ListNode* reversed1Recursive = reverser.reverseListRecursive(reversed1);
    
    cout << "Re-reversed list (recursive): ";
    printLinkedList(reversed1Recursive);
    deleteLinkedList(reversed1Recursive);
    cout << endl;
    
    // Example 2: Reverse a linked list between positions m and n
    cout << "Example 2: Reverse a linked list between positions m and n" << endl;
    vector<int> values2 = {1, 2, 3, 4, 5};
    ListNode* list2 = createLinkedList(values2);
    
    cout << "Original list: ";
    printLinkedList(list2);
    
    ReverseLinkedListII reverser2;
    ListNode* reversed2 = reverser2.reverseBetween(list2, 2, 4);
    
    cout << "List with positions 2 to 4 reversed: ";
    printLinkedList(reversed2);
    deleteLinkedList(reversed2);
    cout << endl;
    
    // Example 3: Reverse Nodes in k-Group
    cout << "Example 3: Reverse Nodes in k-Group" << endl;
    vector<int> values3 = {1, 2, 3, 4, 5, 6, 7, 8};
    ListNode* list3 = createLinkedList(values3);
    
    cout << "Original list: ";
    printLinkedList(list3);
    
    ReverseKGroup reverser3;
    ListNode* reversed3 = reverser3.reverseKGroup(list3, 3);
    
    cout << "List with nodes reversed in groups of 3: ";
    printLinkedList(reversed3);
    deleteLinkedList(reversed3);
    cout << endl;
    
    // Example 4: Palindrome Linked List
    cout << "Example 4: Palindrome Linked List" << endl;
    vector<int> values4Palindrome = {1, 2, 3, 3, 2, 1};
    vector<int> values4NotPalindrome = {1, 2, 3, 4, 5};
    
    ListNode* list4Palindrome = createLinkedList(values4Palindrome);
    ListNode* list4NotPalindrome = createLinkedList(values4NotPalindrome);
    
    PalindromeLinkedList palindromeChecker;
    
    cout << "List: ";
    printLinkedList(list4Palindrome);
    cout << "Is palindrome: " << (palindromeChecker.isPalindrome(list4Palindrome) ? "Yes" : "No") << endl;
    
    cout << "List: ";
    printLinkedList(list4NotPalindrome);
    cout << "Is palindrome: " << (palindromeChecker.isPalindrome(list4NotPalindrome) ? "Yes" : "No") << endl;
    
    deleteLinkedList(list4Palindrome);
    deleteLinkedList(list4NotPalindrome);
    cout << endl;
    
    // Example 5: Remove Duplicates from Sorted List
    cout << "Example 5: Remove Duplicates from Sorted List" << endl;
    vector<int> values5 = {1, 1, 2, 3, 3, 3, 4, 4, 5};
    ListNode* list5 = createLinkedList(values5);
    
    cout << "Original list: ";
    printLinkedList(list5);
    
    RemoveDuplicates deduplicator;
    ListNode* deduped5 = deduplicator.deleteDuplicates(list5);
    
    cout << "List with duplicates removed: ";
    printLinkedList(deduped5);
    deleteLinkedList(deduped5);
    cout << endl;
    
    // Example 6: Remove Duplicates from Sorted List II
    cout << "Example 6: Remove Duplicates from Sorted List II" << endl;
    vector<int> values6 = {1, 2, 3, 3, 4, 4, 5};
    ListNode* list6 = createLinkedList(values6);
    
    cout << "Original list: ";
    printLinkedList(list6);
    
    RemoveDuplicatesII deduplicator2;
    ListNode* deduped6 = deduplicator2.deleteDuplicates(list6);
    
    cout << "List with all nodes having duplicates removed: ";
    printLinkedList(deduped6);
    deleteLinkedList(deduped6);
    
    return 0;
}
