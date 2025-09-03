/**
 * Pattern: Two Pointers - Fixed Separation (Nth Node from End)
 * 
 * Description:
 * The Fixed Separation pattern maintains a constant gap between two pointers as they traverse
 * a data structure. This allows for finding elements at a specific distance from each other,
 * or locating elements relative to the end of a sequence in a single pass.
 * 
 * Time Complexity: O(n) - where n is the size of the input
 * Space Complexity: O(1) - only requires a constant amount of extra space
 * 
 * When to use:
 * - Finding the Nth node from the end of a linked list
 * - Finding the middle of a linked list
 * - Processing elements in relation to others at a fixed distance
 * - Sliding window operations with fixed window size
 * 
 * LeetCode Problems:
 * - 19. Remove Nth Node From End of List
 * - 876. Middle of the Linked List
 * - 2095. Delete the Middle Node of a Linked List
 */

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Example 1: Remove Nth Node From End of List
// LeetCode 19: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // Edge case: empty list
    if (!head) return nullptr;
    
    // Create a dummy node to handle edge cases (like removing the head)
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    // Initialize two pointers: first and second
    ListNode* first = dummy;
    ListNode* second = dummy;
    
    // Move first pointer n+1 steps ahead
    // This creates a gap of n nodes between first and second
    for (int i = 0; i <= n; i++) {
        if (!first) return head; // Handle invalid n
        first = first->next;
    }
    
    // Move both pointers until first reaches the end
    // This positions second at the node before the one to remove
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    // Delete the nth node from the end
    ListNode* toDelete = second->next;
    second->next = second->next->next;
    delete toDelete;
    
    // Return the new head (skipping the dummy node)
    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}

// Example 2: Find the Middle of a Linked List
// LeetCode 876: https://leetcode.com/problems/middle-of-the-linked-list/
// Note: This can also be solved using fast & slow pointers as shown in 02_fast_slow_pointers.cpp
// Here we demonstrate an alternative approach using fixed separation
ListNode* middleNodeFixedSeparation(ListNode* head) {
    if (!head) return nullptr;
    
    // Count the total nodes
    int count = 0;
    ListNode* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    
    // Find the middle position (for even length, return the second middle)
    int middle = count / 2;
    
    // Traverse to the middle node
    current = head;
    for (int i = 0; i < middle; i++) {
        current = current->next;
    }
    
    return current;
}

// Example 3: Delete Middle Node of a Linked List
// LeetCode 2095: https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
ListNode* deleteMiddle(ListNode* head) {
    // Edge cases: empty list or single node
    if (!head) return nullptr;
    if (!head->next) {
        delete head;
        return nullptr;
    }
    
    // Count the total nodes
    int count = 0;
    ListNode* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    
    // Find the middle position
    int middle = count / 2;
    
    // Traverse to the node before the middle
    current = head;
    for (int i = 0; i < middle - 1; i++) {
        current = current->next;
    }
    
    // Delete the middle node
    ListNode* toDelete = current->next;
    current->next = current->next->next;
    delete toDelete;
    
    return head;
}

// Example 4: Find the K-th node from the end (generic implementation)
ListNode* findKthFromEnd(ListNode* head, int k) {
    if (!head || k <= 0) return nullptr;
    
    ListNode* first = head;
    ListNode* second = head;
    
    // Move first k nodes ahead
    for (int i = 0; i < k; i++) {
        if (!first) return nullptr; // k is larger than list length
        first = first->next;
    }
    
    // Move both pointers until first reaches the end
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    return second; // second is now at the k-th node from the end
}

// Example 5: Finding every nth element in an array
vector<int> everyNthElement(vector<int>& nums, int n) {
    if (n <= 0 || nums.empty()) return {};
    
    vector<int> result;
    for (int i = 0; i < nums.size(); i += n) {
        result.push_back(nums[i]);
    }
    
    return result;
}

// Example 6: Check if a string has all characters separated by at least k positions
// Returns true if every instance of the same character is at least k positions apart
bool checkCharSeparation(string s, int k) {
    const int CHAR_COUNT = 26; // Assuming lowercase English letters
    vector<int> lastSeen(CHAR_COUNT, -1);
    
    for (int i = 0; i < s.length(); i++) {
        int charIndex = s[i] - 'a';
        
        // If we've seen this character before
        if (lastSeen[charIndex] != -1) {
            // Check if separation is at least k
            if (i - lastSeen[charIndex] <= k) {
                return false;
            }
        }
        
        // Update last seen position
        lastSeen[charIndex] = i;
    }
    
    return true;
}

// Utility function to create a linked list for testing
ListNode* createLinkedList(vector<int> values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// Utility function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// Function to free memory of a linked list
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// Main function to demonstrate the Fixed Separation pattern
void demonstrateFixedSeparation() {
    cout << "Example 1: Remove Nth Node From End of List" << endl;
    ListNode* list1 = createLinkedList({1, 2, 3, 4, 5});
    cout << "Original list: ";
    printList(list1);
    
    int n = 2; // Remove 2nd node from the end
    list1 = removeNthFromEnd(list1, n);
    cout << "After removing " << n << "nd node from the end: ";
    printList(list1);
    
    cout << "\nExample 2: Find the Middle of a Linked List" << endl;
    ListNode* list2 = createLinkedList({1, 2, 3, 4, 5, 6});
    cout << "Original list: ";
    printList(list2);
    
    ListNode* middle = middleNodeFixedSeparation(list2);
    cout << "Middle node value: " << middle->val << endl;
    
    cout << "\nExample 3: Delete Middle Node of a Linked List" << endl;
    ListNode* list3 = createLinkedList({1, 3, 4, 7, 1, 2, 6});
    cout << "Original list: ";
    printList(list3);
    
    list3 = deleteMiddle(list3);
    cout << "After deleting middle node: ";
    printList(list3);
    
    cout << "\nExample 4: Find the K-th node from the end" << endl;
    ListNode* list4 = createLinkedList({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << "Original list: ";
    printList(list4);
    
    int k = 4; // Find 4th node from the end
    ListNode* kthNode = findKthFromEnd(list4, k);
    cout << "The " << k << "th node from the end has value: " << kthNode->val << endl;
    
    cout << "\nExample 5: Finding every Nth element in an array" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Original array: ";
    for (int num : nums) cout << num << " ";
    cout << endl;
    
    int step = 3; // Get every 3rd element
    vector<int> everyNth = everyNthElement(nums, step);
    cout << "Every " << step << "rd element: ";
    for (int num : everyNth) cout << num << " ";
    cout << endl;
    
    cout << "\nExample 6: Check character separation in a string" << endl;
    string str1 = "abcbdae";
    string str2 = "abcadeafg";
    int minSeparation = 2;
    
    cout << "String \"" << str1 << "\" has all same characters separated by at least " 
         << minSeparation << " positions: " << (checkCharSeparation(str1, minSeparation) ? "true" : "false") << endl;
    
    cout << "String \"" << str2 << "\" has all same characters separated by at least " 
         << minSeparation << " positions: " << (checkCharSeparation(str2, minSeparation) ? "true" : "false") << endl;
    
    // Clean up memory
    deleteList(list2);
    deleteList(list3);
    deleteList(list4);
}

int main() {
    // Demonstrate the Fixed Separation pattern
    demonstrateFixedSeparation();
    
    return 0;
}
