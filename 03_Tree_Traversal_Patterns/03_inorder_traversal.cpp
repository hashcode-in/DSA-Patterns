/**
 * Pattern: Tree DFS - Recursive Inorder Traversal
 * 
 * Description:
 * Inorder traversal is a depth-first traversal method that visits the left subtree first,
 * then the root node, and finally the right subtree. The traversal order is: Left → Root → Right.
 * For binary search trees, inorder traversal yields nodes in ascending order.
 * 
 * Time Complexity: O(n) where n is the number of nodes in the tree
 * Space Complexity: O(h) where h is the height of the tree (worst case O(n) for skewed trees)
 * 
 * When to use:
 * - Retrieving elements from a BST in sorted order
 * - Validating if a binary tree is a valid BST
 * - Finding the kth smallest element in a BST
 * - Finding predecessors and successors in a BST
 * - Converting a BST to a sorted array/list
 * 
 * LeetCode Problems:
 * - 94. Binary Tree Inorder Traversal
 * - 98. Validate Binary Search Tree
 * - 230. Kth Smallest Element in a BST
 * - 173. Binary Search Tree Iterator
 * - 285. Inorder Successor in BST
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Example 1: Recursive Inorder Traversal
// LeetCode 94: https://leetcode.com/problems/binary-tree-inorder-traversal/
void inorderHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    
    // Traverse left subtree
    inorderHelper(root->left, result);
    
    // Visit root
    result.push_back(root->val);
    
    // Traverse right subtree
    inorderHelper(root->right, result);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

// Example 2: Iterative Inorder Traversal (using stack)
vector<int> inorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* current = root;
    
    while (current || !s.empty()) {
        // Reach the leftmost node of the current subtree
        while (current) {
            s.push(current);
            current = current->left;
        }
        
        // Current is now nullptr, pop from stack
        current = s.top();
        s.pop();
        
        // Add the node's value to the result
        result.push_back(current->val);
        
        // Visit the right subtree
        current = current->right;
    }
    
    return result;
}

// Example 3: Validate Binary Search Tree
// LeetCode 98: https://leetcode.com/problems/validate-binary-search-tree/
bool isValidBSTHelper(TreeNode* root, long long minVal, long long maxVal) {
    if (!root) return true;
    
    // Check if the current node's value is within bounds
    if (root->val <= minVal || root->val >= maxVal) return false;
    
    // Recursively check left and right subtrees with updated bounds
    return isValidBSTHelper(root->left, minVal, root->val) && 
           isValidBSTHelper(root->right, root->val, maxVal);
}

bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
}

// Example 4: Kth Smallest Element in a BST
// LeetCode 230: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
int kthSmallestHelper(TreeNode* root, int& k) {
    if (!root) return -1;
    
    // Search in left subtree
    int left = kthSmallestHelper(root->left, k);
    if (left != -1) return left;  // Found in left subtree
    
    // If this is the kth node
    k--;
    if (k == 0) return root->val;
    
    // Search in right subtree
    return kthSmallestHelper(root->right, k);
}

int kthSmallest(TreeNode* root, int k) {
    return kthSmallestHelper(root, k);
}

// Example 5: Iterative Solution for Kth Smallest Element
int kthSmallestIterative(TreeNode* root, int k) {
    stack<TreeNode*> s;
    TreeNode* current = root;
    
    while (current || !s.empty()) {
        // Reach the leftmost node of the current subtree
        while (current) {
            s.push(current);
            current = current->left;
        }
        
        // Current is now nullptr, pop from stack
        current = s.top();
        s.pop();
        
        // Decrement k as we visit each node
        k--;
        if (k == 0) return current->val;
        
        // Visit the right subtree
        current = current->right;
    }
    
    return -1; // If k is invalid
}

// Example 6: Binary Search Tree Iterator
// LeetCode 173: https://leetcode.com/problems/binary-search-tree-iterator/
class BSTIterator {
private:
    stack<TreeNode*> s;
    
    // Helper function to push all left nodes
    void pushLeftNodes(TreeNode* root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushLeftNodes(root);
    }
    
    // Return the next smallest number
    int next() {
        TreeNode* node = s.top();
        s.pop();
        
        // Push all left nodes of the right subtree
        pushLeftNodes(node->right);
        
        return node->val;
    }
    
    // Return whether we have a next smallest number
    bool hasNext() {
        return !s.empty();
    }
};

// Example 7: Inorder Successor in BST
// LeetCode 285: https://leetcode.com/problems/inorder-successor-in-bst/
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;
    
    while (root) {
        if (p->val >= root->val) {
            // If p's value is greater than or equal to current node,
            // the successor must be in the right subtree
            root = root->right;
        } else {
            // If p's value is less than current node,
            // current node could be the successor,
            // but we need to check the left subtree first
            successor = root;
            root = root->left;
        }
    }
    
    return successor;
}

// Example 8: Convert BST to Sorted Doubly Linked List (in-place)
// Similar to LeetCode 426: Convert Binary Search Tree to Sorted Doubly Linked List
TreeNode* convertBSTToDoublyLinkedList(TreeNode* root) {
    if (!root) return nullptr;
    
    // Global variables to keep track of the previous node in inorder traversal
    // and the head of the resulting doubly linked list
    TreeNode* prev = nullptr;
    TreeNode* head = nullptr;
    
    // Helper function to perform inorder traversal and link nodes
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        // Traverse left subtree
        inorder(node->left);
        
        // Process current node
        if (prev) {
            // Link prev with current node
            prev->right = node;
            node->left = prev;
        } else {
            // If prev is nullptr, this is the leftmost node (head)
            head = node;
        }
        
        // Update prev to current node
        prev = node;
        
        // Traverse right subtree
        inorder(node->right);
    };
    
    // Perform inorder traversal
    inorder(root);
    
    // Connect the head and tail to make it circular (if needed)
    if (head && prev) {
        head->left = prev;
        prev->right = head;
    }
    
    return head;
}

// Example 9: Recover Binary Search Tree
// LeetCode 99: https://leetcode.com/problems/recover-binary-search-tree/
void recoverBST(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    
    // Helper function to perform inorder traversal and find swapped nodes
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        // Traverse left subtree
        inorder(node->left);
        
        // Check for violations of BST property
        if (prev && prev->val > node->val) {
            // If this is the first violation, mark first and second
            if (!first) {
                first = prev;
            }
            // Update second to current node (could be the second violation or the next node of first violation)
            second = node;
        }
        
        // Update prev to current node
        prev = node;
        
        // Traverse right subtree
        inorder(node->right);
    };
    
    // Find the swapped nodes
    inorder(root);
    
    // Swap the values of the two nodes
    if (first && second) {
        swap(first->val, second->val);
    }
}

// Example 10: Find Mode in Binary Search Tree
// LeetCode 501: https://leetcode.com/problems/find-mode-in-binary-search-tree/
vector<int> findMode(TreeNode* root) {
    vector<int> modes;
    int currVal = 0;
    int currCount = 0;
    int maxCount = 0;
    
    // Helper function to perform inorder traversal and find modes
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        // Traverse left subtree
        inorder(node->left);
        
        // Process current node
        if (node->val == currVal) {
            // If current value is the same as previous, increment count
            currCount++;
        } else {
            // If current value is different, reset count
            currVal = node->val;
            currCount = 1;
        }
        
        // Update modes based on current count
        if (currCount > maxCount) {
            // New maximum count, clear previous modes
            maxCount = currCount;
            modes.clear();
            modes.push_back(currVal);
        } else if (currCount == maxCount) {
            // Current count equals maximum, add to modes
            modes.push_back(currVal);
        }
        
        // Traverse right subtree
        inorder(node->right);
    };
    
    // Find modes
    inorder(root);
    
    return modes;
}

// Utility function to build a sample binary tree for testing
TreeNode* buildSampleTree() {
    /* Builds this tree:
            4
           / \
          2   6
         / \ / \
        1  3 5  7
    */
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    
    return root;
}

// Utility function to build a sample invalid BST for testing
TreeNode* buildInvalidBST() {
    /* Builds this tree (invalid BST - 6 is in the left subtree of 4):
            4
           / \
          2   7
         / \ / 
        1  6 5  
    */
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6); // This makes it invalid
    root->right->left = new TreeNode(5);
    
    return root;
}

// Utility function to build a sample tree with duplicate values
TreeNode* buildTreeWithDuplicates() {
    /* Builds this tree:
            2
           / \
          1   2
         /     \
        1       3
    */
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(1);
    root->right->right = new TreeNode(3);
    
    return root;
}

// Utility function to print a vector
template<typename T>
void printVector(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Utility function to print a doubly linked list created from BST
void printDoublyLinkedList(TreeNode* head) {
    if (!head) {
        cout << "Empty list";
        return;
    }
    
    TreeNode* current = head;
    bool first = true;
    cout << "[";
    
    // Traverse from head to tail
    do {
        if (!first) cout << ", ";
        first = false;
        cout << current->val;
        current = current->right;
    } while (current && current != head);
    
    cout << "]";
}

// Free memory of the tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function to demonstrate the Inorder Traversal pattern
void demonstrateInorderTraversal() {
    TreeNode* root = buildSampleTree();
    
    cout << "Example 1: Recursive Inorder Traversal" << endl;
    vector<int> inorderResult = inorderTraversal(root);
    cout << "Inorder traversal: ";
    printVector(inorderResult);
    cout << endl;
    
    cout << "\nExample 2: Iterative Inorder Traversal" << endl;
    vector<int> iterativeResult = inorderTraversalIterative(root);
    cout << "Inorder traversal (iterative): ";
    printVector(iterativeResult);
    cout << endl;
    
    cout << "\nExample 3: Validate Binary Search Tree" << endl;
    cout << "Is the tree a valid BST? " << (isValidBST(root) ? "Yes" : "No") << endl;
    
    TreeNode* invalidBST = buildInvalidBST();
    cout << "Is the invalid tree a valid BST? " << (isValidBST(invalidBST) ? "Yes" : "No") << endl;
    
    cout << "\nExample 4: Kth Smallest Element in a BST" << endl;
    int k = 3;
    cout << "The " << k << "rd smallest element is: " << kthSmallest(root, k) << endl;
    
    cout << "\nExample 5: Iterative Kth Smallest Element" << endl;
    cout << "The " << k << "rd smallest element (iterative): " << kthSmallestIterative(root, k) << endl;
    
    cout << "\nExample 6: Binary Search Tree Iterator" << endl;
    BSTIterator iterator(root);
    cout << "BST Iterator output: ";
    while (iterator.hasNext()) {
        cout << iterator.next() << " ";
    }
    cout << endl;
    
    cout << "\nExample 8: Convert BST to Sorted Doubly Linked List" << endl;
    TreeNode* dll = convertBSTToDoublyLinkedList(buildSampleTree());
    cout << "Doubly Linked List: ";
    printDoublyLinkedList(dll);
    cout << endl;
    
    cout << "\nExample 10: Find Mode in Binary Search Tree" << endl;
    TreeNode* treeWithDuplicates = buildTreeWithDuplicates();
    vector<int> modes = findMode(treeWithDuplicates);
    cout << "Modes in the tree: ";
    printVector(modes);
    cout << endl;
    
    // Clean up memory
    deleteTree(root);
    deleteTree(invalidBST);
    // Note: dll was created from a copy of the tree, so it was already deleted
    deleteTree(treeWithDuplicates);
}

int main() {
    // Demonstrate the Inorder Traversal pattern
    demonstrateInorderTraversal();
    
    return 0;
}
