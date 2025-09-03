/**
 * Pattern: Linked List - Reordering / Partitioning
 * 
 * Description:
 * This pattern focuses on reordering or partitioning linked lists based on
 * certain criteria. It involves rearranging nodes in the list without creating
 * new nodes, usually by manipulating the next pointers.
 * 
 * Time Complexity: O(n) where n is the length of the linked list
 * Space Complexity: O(1) for in-place operations
 * 
 * When to use:
 * - When you need to reorder a linked list in a specific pattern
 * - When you need to partition a linked list based on a value
 * - When you need to group nodes with similar properties
 * 
 * LeetCode Problems:
 * - 24. Swap Nodes in Pairs
 * - 61. Rotate List
 * - 86. Partition List
 * - 143. Reorder List
 * - 328. Odd Even Linked List
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

// Example 1: Swap Nodes in Pairs
// LeetCode 24: https://leetcode.com/problems/swap-nodes-in-pairs/
class SwapNodesInPairs {
public:
    // Approach 1: Iterative
    ListNode* swapPairs(ListNode* head) {
        // Dummy node to handle the case when head changes
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;
        
        while (head != nullptr && head->next != nullptr) {
            // Nodes to be swapped
            ListNode* first = head;
            ListNode* second = head->next;
            
            // Swap the nodes
            prev->next = second;       // Connect previous node to second node
            first->next = second->next; // Connect first node to node after second
            second->next = first;      // Connect second node to first node
            
            // Move prev and head for the next pair
            prev = first;
            head = first->next;
        }
        
        return dummy.next;
    }
    
    // Approach 2: Recursive
    ListNode* swapPairsRecursive(ListNode* head) {
        // Base case: If the list is empty or has only one node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Nodes to be swapped
        ListNode* first = head;
        ListNode* second = head->next;
        
        // Swap the nodes
        first->next = swapPairsRecursive(second->next);
        second->next = first;
        
        // Return the new head (which is the second node now)
        return second;
    }
};

// Example 2: Rotate List
// LeetCode 61: https://leetcode.com/problems/rotate-list/
class RotateList {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // Edge cases: empty list or single node or no rotation needed
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }
        
        // Calculate the length of the list and find the last node
        int length = 1;
        ListNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
            length++;
        }
        
        // Calculate the effective number of rotations (k % length)
        k = k % length;
        
        // If k % length is 0, no rotation is needed
        if (k == 0) {
            return head;
        }
        
        // Find the node that will become the new tail after rotation
        ListNode* newTail = head;
        for (int i = 0; i < length - k - 1; i++) {
            newTail = newTail->next;
        }
        
        // Perform the rotation
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;  // Break the list
        tail->next = head;        // Connect the original tail to the original head
        
        return newHead;
    }
};

// Example 3: Partition List
// LeetCode 86: https://leetcode.com/problems/partition-list/
class PartitionList {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return nullptr;
        }
        
        // Create two dummy nodes for two separate lists
        ListNode lessDummy(0);   // For nodes with values less than x
        ListNode greaterDummy(0); // For nodes with values greater or equal to x
        
        // Pointers to the current tail of each list
        ListNode* lessTail = &lessDummy;
        ListNode* greaterTail = &greaterDummy;
        
        // Traverse the original list
        ListNode* current = head;
        while (current != nullptr) {
            if (current->val < x) {
                // Add to the "less than x" list
                lessTail->next = current;
                lessTail = lessTail->next;
            } else {
                // Add to the "greater or equal to x" list
                greaterTail->next = current;
                greaterTail = greaterTail->next;
            }
            
            current = current->next;
        }
        
        // Connect the two lists
        greaterTail->next = nullptr; // Ensure the end of the list
        lessTail->next = greaterDummy.next;
        
        return lessDummy.next;
    }
};

// Example 4: Reorder List
// LeetCode 143: https://leetcode.com/problems/reorder-list/
class ReorderList {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return;  // No need to reorder for empty list or lists with less than 3 nodes
        }
        
        // Step 1: Find the middle of the linked list
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Step 2: Reverse the second half of the linked list
        ListNode* middle = slow;
        ListNode* secondHalfHead = reverseList(middle->next);
        middle->next = nullptr;  // Break the first half
        
        // Step 3: Merge the first half and the reversed second half
        ListNode* firstHalfCurrent = head;
        ListNode* secondHalfCurrent = secondHalfHead;
        
        while (secondHalfCurrent != nullptr) {
            // Save the next nodes
            ListNode* firstHalfNext = firstHalfCurrent->next;
            ListNode* secondHalfNext = secondHalfCurrent->next;
            
            // Insert the second half node after the first half node
            firstHalfCurrent->next = secondHalfCurrent;
            secondHalfCurrent->next = firstHalfNext;
            
            // Move to the next nodes
            firstHalfCurrent = firstHalfNext;
            secondHalfCurrent = secondHalfNext;
        }
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

// Example 5: Odd Even Linked List
// LeetCode 328: https://leetcode.com/problems/odd-even-linked-list/
class OddEvenLinkedList {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;  // Empty list or single node
        }
        
        ListNode* oddHead = head;           // Head of the odd-indexed nodes (1st, 3rd, 5th, ...)
        ListNode* evenHead = head->next;    // Head of the even-indexed nodes (2nd, 4th, 6th, ...)
        
        ListNode* oddCurrent = oddHead;
        ListNode* evenCurrent = evenHead;
        
        // Traverse the list and group odd and even indexed nodes
        while (evenCurrent != nullptr && evenCurrent->next != nullptr) {
            // Connect odd node to the next odd node (current->next->next)
            oddCurrent->next = evenCurrent->next;
            oddCurrent = oddCurrent->next;
            
            // Connect even node to the next even node (current->next->next)
            evenCurrent->next = oddCurrent->next;
            evenCurrent = evenCurrent->next;
        }
        
        // Connect the odd list to the even list
        oddCurrent->next = evenHead;
        
        return oddHead;
    }
};

// Example 6: Partition linked list into three parts (Extension of Partition List)
class ThreeWayPartition {
public:
    // Partition the linked list into three parts: less than low, between low and high, and greater than high
    ListNode* threeWayPartition(ListNode* head, int low, int high) {
        if (head == nullptr) {
            return nullptr;
        }
        
        // Create three dummy nodes for three separate lists
        ListNode lessDummy(0);    // For nodes with values less than low
        ListNode betweenDummy(0); // For nodes with values between low and high
        ListNode greaterDummy(0); // For nodes with values greater than high
        
        // Pointers to the current tail of each list
        ListNode* lessTail = &lessDummy;
        ListNode* betweenTail = &betweenDummy;
        ListNode* greaterTail = &greaterDummy;
        
        // Traverse the original list and classify nodes
        ListNode* current = head;
        while (current != nullptr) {
            if (current->val < low) {
                lessTail->next = current;
                lessTail = lessTail->next;
            } else if (current->val <= high) {
                betweenTail->next = current;
                betweenTail = betweenTail->next;
            } else {
                greaterTail->next = current;
                greaterTail = greaterTail->next;
            }
            
            current = current->next;
        }
        
        // Terminate each list
        greaterTail->next = nullptr;
        betweenTail->next = greaterDummy.next;
        lessTail->next = betweenDummy.next;
        
        return lessDummy.next;
    }
};

// Main function to demonstrate the Linked List Reordering / Partitioning pattern
int main() {
    // Example 1: Swap Nodes in Pairs
    cout << "Example 1: Swap Nodes in Pairs" << endl;
    vector<int> values1 = {1, 2, 3, 4, 5, 6};
    ListNode* list1 = createLinkedList(values1);
    
    cout << "Original list: ";
    printLinkedList(list1);
    
    SwapNodesInPairs swapper;
    ListNode* swapped = swapper.swapPairs(list1);
    
    cout << "Swapped pairs: ";
    printLinkedList(swapped);
    
    // Create a new list for the recursive approach
    ListNode* list1Recursive = createLinkedList(values1);
    
    ListNode* swappedRecursive = swapper.swapPairsRecursive(list1Recursive);
    
    cout << "Swapped pairs (recursive): ";
    printLinkedList(swappedRecursive);
    
    deleteLinkedList(swapped);
    deleteLinkedList(swappedRecursive);
    cout << endl;
    
    // Example 2: Rotate List
    cout << "Example 2: Rotate List" << endl;
    vector<int> values2 = {1, 2, 3, 4, 5};
    ListNode* list2 = createLinkedList(values2);
    
    cout << "Original list: ";
    printLinkedList(list2);
    
    RotateList rotator;
    ListNode* rotated = rotator.rotateRight(list2, 2);
    
    cout << "Rotated list (k=2): ";
    printLinkedList(rotated);
    
    // Create a new list for another rotation example
    ListNode* list2Another = createLinkedList(values2);
    ListNode* rotatedAnother = rotator.rotateRight(list2Another, 7); // 7 % 5 = 2, same effect as k=2
    
    cout << "Rotated list (k=7): ";
    printLinkedList(rotatedAnother);
    
    deleteLinkedList(rotated);
    deleteLinkedList(rotatedAnother);
    cout << endl;
    
    // Example 3: Partition List
    cout << "Example 3: Partition List" << endl;
    vector<int> values3 = {1, 4, 3, 2, 5, 2};
    ListNode* list3 = createLinkedList(values3);
    
    cout << "Original list: ";
    printLinkedList(list3);
    
    PartitionList partitioner;
    ListNode* partitioned = partitioner.partition(list3, 3);
    
    cout << "Partitioned list (x=3): ";
    printLinkedList(partitioned);
    
    deleteLinkedList(partitioned);
    cout << endl;
    
    // Example 4: Reorder List
    cout << "Example 4: Reorder List" << endl;
    vector<int> values4 = {1, 2, 3, 4, 5, 6};
    ListNode* list4 = createLinkedList(values4);
    
    cout << "Original list: ";
    printLinkedList(list4);
    
    ReorderList reorderer;
    reorderer.reorderList(list4);
    
    cout << "Reordered list: ";
    printLinkedList(list4);
    
    deleteLinkedList(list4);
    cout << endl;
    
    // Example 5: Odd Even Linked List
    cout << "Example 5: Odd Even Linked List" << endl;
    vector<int> values5 = {1, 2, 3, 4, 5, 6, 7, 8};
    ListNode* list5 = createLinkedList(values5);
    
    cout << "Original list: ";
    printLinkedList(list5);
    
    OddEvenLinkedList oddEven;
    ListNode* oddEvenList = oddEven.oddEvenList(list5);
    
    cout << "Odd-Even list: ";
    printLinkedList(oddEvenList);
    
    deleteLinkedList(oddEvenList);
    cout << endl;
    
    // Example 6: Three-way Partition
    cout << "Example 6: Three-way Partition" << endl;
    vector<int> values6 = {1, 8, 5, 3, 10, 2, 6, 7, 4};
    ListNode* list6 = createLinkedList(values6);
    
    cout << "Original list: ";
    printLinkedList(list6);
    
    ThreeWayPartition threeWayPartitioner;
    ListNode* threeWayPartitioned = threeWayPartitioner.threeWayPartition(list6, 4, 7);
    
    cout << "Three-way partitioned list (low=4, high=7): ";
    printLinkedList(threeWayPartitioned);
    
    deleteLinkedList(threeWayPartitioned);
    
    return 0;
}
