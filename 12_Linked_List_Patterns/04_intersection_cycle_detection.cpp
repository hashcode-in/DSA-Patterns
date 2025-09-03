/**
 * Pattern: Linked List - Intersection/Cycle Detection
 * 
 * Description:
 * This pattern focuses on detecting cycles in linked lists and finding
 * intersection points between two linked lists. It typically employs the
 * two-pointer technique, particularly the Floyd's Cycle Finding Algorithm
 * (slow and fast pointers).
 * 
 * Time Complexity: O(n) where n is the length of the list
 * Space Complexity: O(1) using the two-pointer approach
 * 
 * When to use:
 * - When you need to detect if a linked list has a cycle
 * - When you need to find the start node of a cycle in a linked list
 * - When you need to find the intersection point of two linked lists
 * 
 * LeetCode Problems:
 * - 141. Linked List Cycle
 * - 142. Linked List Cycle II
 * - 160. Intersection of Two Linked Lists
 */

#include <iostream>
#include <vector>
#include <unordered_set>

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
void printLinkedList(ListNode* head, int limit = -1) {
    int count = 0;
    while (head != nullptr && (limit == -1 || count < limit)) {
        cout << head->val;
        if (head->next != nullptr && (limit == -1 || count < limit - 1)) {
            cout << " -> ";
        }
        head = head->next;
        count++;
    }
    if (head != nullptr) {
        cout << " ... ";  // Indicate there are more nodes
    }
    cout << endl;
}

// Helper function to free memory of a linked list (without cycles)
void deleteLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// Example 1: Linked List Cycle
// LeetCode 141: https://leetcode.com/problems/linked-list-cycle/
class LinkedListCycle {
public:
    // Approach 1: Using slow and fast pointers (Floyd's Cycle-Finding Algorithm)
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;  // Empty list or single node can't have a cycle
        }
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Move slow pointer by 1 step and fast pointer by 2 steps
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;         // Move slow pointer by 1
            fast = fast->next->next;   // Move fast pointer by 2
            
            // If there is a cycle, the pointers will meet
            if (slow == fast) {
                return true;
            }
        }
        
        // If fast reaches end of the list, there is no cycle
        return false;
    }
    
    // Approach 2: Using a hash set
    bool hasCycleHashSet(ListNode* head) {
        unordered_set<ListNode*> visited;
        
        ListNode* current = head;
        while (current != nullptr) {
            if (visited.find(current) != visited.end()) {
                return true;  // Found a previously visited node
            }
            
            visited.insert(current);
            current = current->next;
        }
        
        return false;  // Reached the end of the list without finding a cycle
    }
};

// Example 2: Linked List Cycle II (Find the start of the cycle)
// LeetCode 142: https://leetcode.com/problems/linked-list-cycle-ii/
class LinkedListCycleII {
public:
    // Approach 1: Using Floyd's Cycle-Finding Algorithm
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;  // Empty list or single node can't have a cycle
        }
        
        // Phase 1: Detect cycle using slow and fast pointers
        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        if (!hasCycle) {
            return nullptr;  // No cycle found
        }
        
        // Phase 2: Find the start of the cycle
        // Reset slow to head, keep fast at meeting point
        // Both pointers move at the same speed (1 step)
        // They will meet at the start of the cycle
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;  // This is the start of the cycle
    }
    
    // Approach 2: Using a hash set
    ListNode* detectCycleHashSet(ListNode* head) {
        unordered_set<ListNode*> visited;
        
        ListNode* current = head;
        while (current != nullptr) {
            if (visited.find(current) != visited.end()) {
                return current;  // This is the start of the cycle
            }
            
            visited.insert(current);
            current = current->next;
        }
        
        return nullptr;  // No cycle found
    }
};

// Example 3: Intersection of Two Linked Lists
// LeetCode 160: https://leetcode.com/problems/intersection-of-two-linked-lists/
class IntersectionOfTwoLists {
public:
    // Approach 1: Using two pointers with "two-pass" technique
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        
        // Initialize two pointers
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;
        
        // Traverse both lists
        // When one pointer reaches the end, switch to the other list's head
        // This ensures both pointers travel the same total distance
        // If there's an intersection, they will meet at the intersection point
        while (ptrA != ptrB) {
            // If ptrA reaches the end, switch to headB
            ptrA = (ptrA == nullptr) ? headB : ptrA->next;
            
            // If ptrB reaches the end, switch to headA
            ptrB = (ptrB == nullptr) ? headA : ptrB->next;
        }
        
        // ptrA is either the intersection point or nullptr if there's no intersection
        return ptrA;
    }
    
    // Approach 2: Using a hash set
    ListNode* getIntersectionNodeHashSet(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        
        unordered_set<ListNode*> nodesFromA;
        
        // Add all nodes from list A to the set
        ListNode* currentA = headA;
        while (currentA != nullptr) {
            nodesFromA.insert(currentA);
            currentA = currentA->next;
        }
        
        // Check each node in list B against the set
        ListNode* currentB = headB;
        while (currentB != nullptr) {
            if (nodesFromA.find(currentB) != nodesFromA.end()) {
                return currentB;  // Found intersection
            }
            currentB = currentB->next;
        }
        
        return nullptr;  // No intersection found
    }
    
    // Approach 3: Using length difference
    ListNode* getIntersectionNodeLengthDifference(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        
        // Calculate lengths of both lists
        int lengthA = getLength(headA);
        int lengthB = getLength(headB);
        
        // Adjust starting points to account for length difference
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;
        
        // Move the pointer of the longer list ahead by the difference in length
        if (lengthA > lengthB) {
            for (int i = 0; i < lengthA - lengthB; i++) {
                ptrA = ptrA->next;
            }
        } else {
            for (int i = 0; i < lengthB - lengthA; i++) {
                ptrB = ptrB->next;
            }
        }
        
        // Now both pointers are at same distance from the end
        // Move both pointers until they meet or reach the end
        while (ptrA != nullptr && ptrB != nullptr) {
            if (ptrA == ptrB) {
                return ptrA;  // Found intersection
            }
            ptrA = ptrA->next;
            ptrB = ptrB->next;
        }
        
        return nullptr;  // No intersection found
    }
    
private:
    // Helper function to calculate the length of a linked list
    int getLength(ListNode* head) {
        int length = 0;
        ListNode* current = head;
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        return length;
    }
};

// Example 4: Cycle Length and Distance to Start
// Extension of Cycle Detection
class CycleLengthAndDistance {
public:
    // Find the length of the cycle
    int findCycleLength(ListNode* head) {
        // First detect if there is a cycle
        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        if (!hasCycle) {
            return 0;  // No cycle
        }
        
        // Calculate cycle length
        int length = 1;
        fast = slow->next;
        while (fast != slow) {
            length++;
            fast = fast->next;
        }
        
        return length;
    }
    
    // Find distance from head to start of the cycle
    int distanceToStart(ListNode* head) {
        // First detect if there is a cycle
        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        if (!hasCycle) {
            return -1;  // No cycle
        }
        
        // Find the start of the cycle
        slow = head;
        int distance = 0;
        
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
            distance++;
        }
        
        return distance;
    }
};

// Main function to demonstrate the Linked List Intersection/Cycle Detection pattern
int main() {
    // Example 1: Linked List Cycle
    cout << "Example 1: Linked List Cycle" << endl;
    
    // Create a linked list with a cycle: 1->2->3->4->5->3 (cycles back to 3)
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);
    
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node3;  // Creates a cycle
    
    cout << "Linked list with a cycle (cycles back to 3): ";
    printLinkedList(node1, 7);  // Print only the first 7 nodes to avoid infinite loop
    
    LinkedListCycle cycleDetector;
    bool hasCycle = cycleDetector.hasCycle(node1);
    bool hasCycleHashSet = cycleDetector.hasCycleHashSet(node1);
    
    cout << "Has cycle (using Floyd's Algorithm): " << (hasCycle ? "Yes" : "No") << endl;
    cout << "Has cycle (using hash set): " << (hasCycleHashSet ? "Yes" : "No") << endl;
    cout << endl;
    
    // Example 2: Linked List Cycle II (Find the start of the cycle)
    cout << "Example 2: Linked List Cycle II (Find the start of the cycle)" << endl;
    
    LinkedListCycleII cycleStartDetector;
    ListNode* cycleStart = cycleStartDetector.detectCycle(node1);
    ListNode* cycleStartHashSet = cycleStartDetector.detectCycleHashSet(node1);
    
    cout << "Cycle starts at node with value: " << cycleStart->val << endl;
    cout << "Cycle starts at node with value (using hash set): " << cycleStartHashSet->val << endl;
    cout << endl;
    
    // Break the cycle before freeing memory
    node5->next = nullptr;
    
    // Example 3: Intersection of Two Linked Lists
    cout << "Example 3: Intersection of Two Linked Lists" << endl;
    
    // Create two lists that intersect
    vector<int> valuesA = {1, 3, 5, 7, 9};
    vector<int> valuesB = {2, 4, 6};
    
    ListNode* headA = createLinkedList(valuesA);
    ListNode* headB = createLinkedList(valuesB);
    
    // Create an intersection point
    ListNode* intersectionNode = new ListNode(8);
    ListNode* node10 = new ListNode(10);
    ListNode* node12 = new ListNode(12);
    
    // Find the tails of both lists
    ListNode* tailA = headA;
    while (tailA->next != nullptr) {
        tailA = tailA->next;
    }
    
    ListNode* tailB = headB;
    while (tailB->next != nullptr) {
        tailB = tailB->next;
    }
    
    // Connect both tails to the intersection point
    tailA->next = intersectionNode;
    tailB->next = intersectionNode;
    intersectionNode->next = node10;
    node10->next = node12;
    
    cout << "List A: ";
    printLinkedList(headA);
    
    cout << "List B: ";
    printLinkedList(headB);
    
    IntersectionOfTwoLists intersectionDetector;
    ListNode* intersection = intersectionDetector.getIntersectionNode(headA, headB);
    ListNode* intersectionHashSet = intersectionDetector.getIntersectionNodeHashSet(headA, headB);
    ListNode* intersectionLength = intersectionDetector.getIntersectionNodeLengthDifference(headA, headB);
    
    cout << "Intersection at node with value: " << intersection->val << endl;
    cout << "Intersection at node with value (using hash set): " << intersectionHashSet->val << endl;
    cout << "Intersection at node with value (using length difference): " << intersectionLength->val << endl;
    cout << endl;
    
    // Example 4: Cycle Length and Distance to Start
    cout << "Example 4: Cycle Length and Distance to Start" << endl;
    
    // Recreate the cycle for the last example
    node5->next = node3;
    
    CycleLengthAndDistance cycleLengthDetector;
    int cycleLength = cycleLengthDetector.findCycleLength(node1);
    int distance = cycleLengthDetector.distanceToStart(node1);
    
    cout << "Cycle length: " << cycleLength << endl;
    cout << "Distance from head to cycle start: " << distance << endl;
    
    // Break the cycle before freeing memory
    node5->next = nullptr;
    
    // Free the memory
    deleteLinkedList(node1);
    deleteLinkedList(headA);
    
    // Since headB shares nodes with headA after the intersection,
    // we need to prevent double deletion
    tailB->next = nullptr;
    deleteLinkedList(headB);
    
    return 0;
}
