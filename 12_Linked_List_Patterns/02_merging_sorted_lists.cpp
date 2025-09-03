/**
 * Pattern: Linked List - Merging Two Sorted Lists
 * 
 * Description:
 * This pattern focuses on merging sorted linked lists into a single sorted list.
 * It commonly uses a dummy head node to simplify edge cases and iteration through
 * multiple lists simultaneously.
 * 
 * Time Complexity: O(n+m) where n and m are the lengths of the input lists
 * Space Complexity: O(1) for in-place merging, O(n+m) for new list creation
 * 
 * When to use:
 * - When you need to merge sorted linked lists
 * - When working with multiple linked lists and need to combine them
 * - As part of other algorithms like merge sort for linked lists
 * 
 * LeetCode Problems:
 * - 21. Merge Two Sorted Lists
 * - 23. Merge k Sorted Lists (combines with Heap pattern)
 * - 148. Sort List (uses merge sort)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

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

// Example 1: Merge Two Sorted Lists
// LeetCode 21: https://leetcode.com/problems/merge-two-sorted-lists/
class MergeTwoSortedLists {
public:
    // Approach 1: Iterative - Create a new list
    ListNode* mergeTwoListsNewList(ListNode* list1, ListNode* list2) {
        // Dummy head to simplify edge cases
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = new ListNode(list1->val);
                list1 = list1->next;
            } else {
                tail->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            tail = tail->next;
        }
        
        // Append any remaining nodes from either list
        while (list1 != nullptr) {
            tail->next = new ListNode(list1->val);
            list1 = list1->next;
            tail = tail->next;
        }
        
        while (list2 != nullptr) {
            tail->next = new ListNode(list2->val);
            list2 = list2->next;
            tail = tail->next;
        }
        
        return dummy.next;
    }
    
    // Approach 2: Iterative - In-place (reusing existing nodes)
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Dummy head to simplify edge cases
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        
        // Append any remaining nodes from either list
        // This is more efficient than a while loop for each
        tail->next = (list1 != nullptr) ? list1 : list2;
        
        return dummy.next;
    }
    
    // Approach 3: Recursive
    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        
        if (list1->val <= list2->val) {
            list1->next = mergeTwoListsRecursive(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoListsRecursive(list1, list2->next);
            return list2;
        }
    }
};

// Example 2: Merge k Sorted Lists
// LeetCode 23: https://leetcode.com/problems/merge-k-sorted-lists/
class MergeKSortedLists {
public:
    // Approach 1: Using priority queue (min heap)
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Custom comparison for ListNode pointers
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val;  // Min heap
        };
        
        // Priority queue to store head nodes of all lists
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);
        
        // Add all non-null heads to the min heap
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }
        
        // Dummy head for the merged list
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        // Process nodes in sorted order
        while (!minHeap.empty()) {
            ListNode* current = minHeap.top();
            minHeap.pop();
            
            // Add the node to the result list
            tail->next = current;
            tail = tail->next;
            
            // Add next node from the same list to heap if it exists
            if (current->next != nullptr) {
                minHeap.push(current->next);
            }
        }
        
        return dummy.next;
    }
    
    // Approach 2: Divide and conquer (merge pairs of lists)
    ListNode* mergeKListsDivideConquer(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        int k = lists.size();
        
        // Keep merging pairs of lists until we have only one list
        while (k > 1) {
            // Calculate new size after merging
            int nextK = (k + 1) / 2;
            
            // Merge pairs of lists
            for (int i = 0; i < k / 2; i++) {
                lists[i] = mergeTwoLists(lists[i], lists[i + (k + 1) / 2]);
            }
            
            // Update the number of lists
            k = nextK;
        }
        
        return lists[0];
    }

private:
    // Helper function to merge two sorted lists
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Dummy head
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        
        // Attach the remaining list
        tail->next = (list1 != nullptr) ? list1 : list2;
        
        return dummy.next;
    }
};

// Example 3: Sort List (using merge sort)
// LeetCode 148: https://leetcode.com/problems/sort-list/
class SortList {
public:
    ListNode* sortList(ListNode* head) {
        // Base cases
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Find the middle of the linked list
        ListNode* mid = findMiddle(head);
        
        // Split the list into two halves
        ListNode* secondHalf = mid->next;
        mid->next = nullptr;  // Break the link
        
        // Recursively sort both halves
        ListNode* left = sortList(head);
        ListNode* right = sortList(secondHalf);
        
        // Merge the sorted halves
        return mergeTwoSortedLists(left, right);
    }
    
private:
    // Helper function to find the middle of the linked list
    // Returns the node before the middle for easy splitting
    ListNode* findMiddle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode* slow = head;
        ListNode* fast = head->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // Helper function to merge two sorted lists
    ListNode* mergeTwoSortedLists(ListNode* left, ListNode* right) {
        // Dummy head
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        // Merge nodes from both lists in sorted order
        while (left != nullptr && right != nullptr) {
            if (left->val <= right->val) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }
        
        // Attach the remaining list
        tail->next = (left != nullptr) ? left : right;
        
        return dummy.next;
    }
};

// Example 4: Merge Sort for Linked Lists (Iterative Bottom-Up Approach)
class MergeSortBottomUp {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Count the length of the linked list
        int length = 0;
        ListNode* current = head;
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        
        // Dummy head to simplify merging
        ListNode dummy(0);
        dummy.next = head;
        
        // Bottom-up merge sort
        // Start with merging sublists of size 1, then 2, 4, 8, ...
        for (int size = 1; size < length; size = size * 2) {
            ListNode* prev = &dummy;
            current = dummy.next;
            
            while (current != nullptr) {
                // Left half: current
                ListNode* left = current;
                
                // Find the end of left half and start of right half
                ListNode* right = split(left, size);
                
                // Update current to the next sublist
                current = split(right, size);
                
                // Merge the two halves and connect to the previous part
                prev = merge(left, right, prev);
            }
        }
        
        return dummy.next;
    }
    
private:
    // Split the list into two parts: first part with 'size' nodes,
    // Return the head of the second part
    ListNode* split(ListNode* head, int size) {
        if (head == nullptr) {
            return nullptr;
        }
        
        // Find the end of the first sublist
        for (int i = 1; head->next != nullptr && i < size; i++) {
            head = head->next;
        }
        
        ListNode* secondHalf = head->next;
        head->next = nullptr;  // Disconnect
        
        return secondHalf;
    }
    
    // Merge two sorted lists and return the tail of the merged list
    ListNode* merge(ListNode* left, ListNode* right, ListNode* prev) {
        // Start merging from prev
        ListNode* current = prev;
        
        // Merge two sorted lists
        while (left != nullptr && right != nullptr) {
            if (left->val <= right->val) {
                current->next = left;
                left = left->next;
            } else {
                current->next = right;
                right = right->next;
            }
            current = current->next;
        }
        
        // Attach the remaining list
        if (left != nullptr) {
            current->next = left;
        } else {
            current->next = right;
        }
        
        // Find the end of the merged list
        while (current->next != nullptr) {
            current = current->next;
        }
        
        // Return the tail of the merged list
        return current;
    }
};

// Main function to demonstrate the Linked List Merging pattern
int main() {
    // Example 1: Merge Two Sorted Lists
    cout << "Example 1: Merge Two Sorted Lists" << endl;
    vector<int> values1 = {1, 3, 5, 7, 9};
    vector<int> values2 = {2, 4, 6, 8, 10};
    
    ListNode* list1 = createLinkedList(values1);
    ListNode* list2 = createLinkedList(values2);
    
    cout << "List 1: ";
    printLinkedList(list1);
    
    cout << "List 2: ";
    printLinkedList(list2);
    
    MergeTwoSortedLists merger;
    ListNode* merged = merger.mergeTwoLists(list1, list2);
    
    cout << "Merged list (in-place): ";
    printLinkedList(merged);
    
    // Create new lists for the recursive approach
    list1 = createLinkedList(values1);
    list2 = createLinkedList(values2);
    
    ListNode* mergedRecursive = merger.mergeTwoListsRecursive(list1, list2);
    
    cout << "Merged list (recursive): ";
    printLinkedList(mergedRecursive);
    
    deleteLinkedList(merged);  // Note: merged and mergedRecursive are the same list
    cout << endl;
    
    // Example 2: Merge K Sorted Lists
    cout << "Example 2: Merge K Sorted Lists" << endl;
    vector<int> kValues1 = {1, 4, 7};
    vector<int> kValues2 = {2, 5, 8};
    vector<int> kValues3 = {3, 6, 9};
    
    ListNode* kList1 = createLinkedList(kValues1);
    ListNode* kList2 = createLinkedList(kValues2);
    ListNode* kList3 = createLinkedList(kValues3);
    
    vector<ListNode*> lists = {kList1, kList2, kList3};
    
    cout << "List 1: ";
    printLinkedList(kList1);
    
    cout << "List 2: ";
    printLinkedList(kList2);
    
    cout << "List 3: ";
    printLinkedList(kList3);
    
    MergeKSortedLists kMerger;
    ListNode* kMerged = kMerger.mergeKLists(lists);
    
    cout << "Merged K lists: ";
    printLinkedList(kMerged);
    
    deleteLinkedList(kMerged);
    cout << endl;
    
    // Example 3: Sort List using Merge Sort
    cout << "Example 3: Sort List using Merge Sort" << endl;
    vector<int> unsortedValues = {4, 2, 1, 3, 5, 6, 8, 7, 9};
    ListNode* unsortedList = createLinkedList(unsortedValues);
    
    cout << "Unsorted list: ";
    printLinkedList(unsortedList);
    
    SortList sorter;
    ListNode* sortedList = sorter.sortList(unsortedList);
    
    cout << "Sorted list: ";
    printLinkedList(sortedList);
    
    deleteLinkedList(sortedList);
    cout << endl;
    
    // Example 4: Iterative Merge Sort for Linked Lists
    cout << "Example 4: Iterative Merge Sort for Linked Lists" << endl;
    vector<int> unsortedValues2 = {5, 1, 9, 3, 7, 2, 8, 4, 6};
    ListNode* unsortedList2 = createLinkedList(unsortedValues2);
    
    cout << "Unsorted list: ";
    printLinkedList(unsortedList2);
    
    MergeSortBottomUp iterativeSorter;
    ListNode* sortedList2 = iterativeSorter.sortList(unsortedList2);
    
    cout << "Sorted list (iterative): ";
    printLinkedList(sortedList2);
    
    deleteLinkedList(sortedList2);
    
    return 0;
}
