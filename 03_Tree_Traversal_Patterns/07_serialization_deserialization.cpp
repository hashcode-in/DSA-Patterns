/**
 * Pattern: Tree - Serialization and Deserialization
 * 
 * Description:
 * Serialization is the process of converting a data structure or object into a sequence of bits/characters
 * so that it can be stored in a file, buffer, or transmitted across a network. Deserialization is the 
 * reverse process of creating a data structure or object from a sequence of bits/characters.
 * This pattern is essential for storing or transmitting tree structures.
 * 
 * Time Complexity: O(n) for both serialization and deserialization where n is the number of nodes
 * Space Complexity: O(n) for both serialization and deserialization
 * 
 * When to use:
 * - Storing tree structures in databases or files
 * - Transmitting tree structures over a network
 * - Caching tree structures for later use
 * - Comparing tree structures by comparing their serialized forms
 * - Cloning trees
 * 
 * LeetCode Problems:
 * - 297. Serialize and Deserialize Binary Tree
 * - 449. Serialize and Deserialize BST
 * - 428. Serialize and Deserialize N-ary Tree
 * - 652. Find Duplicate Subtrees
 * - 572. Subtree of Another Tree
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <climits>

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

// Example 1: Serialization and Deserialization using preorder traversal
// LeetCode 297: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
class Codec1 {
public:
    // Serialize a tree to a string using preorder traversal
    string serialize(TreeNode* root) {
        // Create a stringstream to store the serialized tree
        ostringstream out;
        serialize(root, out);
        return out.str();
    }
    
    // Helper function for serialization
    void serialize(TreeNode* root, ostringstream& out) {
        if (!root) {
            out << "# "; // Null marker
            return;
        }
        
        // Preorder traversal: root -> left -> right
        out << root->val << " "; // Serialize the current node
        serialize(root->left, out); // Serialize the left subtree
        serialize(root->right, out); // Serialize the right subtree
    }
    
    // Deserialize a string to a tree
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
    
    // Helper function for deserialization
    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        
        if (val == "#") {
            return nullptr; // Null marker encountered
        }
        
        // Create a new node with the current value
        TreeNode* root = new TreeNode(stoi(val));
        
        // Preorder traversal: root -> left -> right
        root->left = deserialize(in); // Deserialize the left subtree
        root->right = deserialize(in); // Deserialize the right subtree
        
        return root;
    }
};

// Example 2: Serialization and Deserialization using level-order traversal (BFS)
// Alternative approach to LeetCode 297
class Codec2 {
public:
    // Serialize a tree to a string using level-order traversal
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        ostringstream out;
        queue<TreeNode*> q;
        q.push(root);
        
        // Level-order traversal
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                out << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                out << "# ";
            }
        }
        
        return out.str();
    }
    
    // Deserialize a string to a tree
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        istringstream in(data);
        string val;
        in >> val;
        
        TreeNode* root = new TreeNode(stoi(val));
        queue<TreeNode*> q;
        q.push(root);
        
        // Level-order traversal to construct the tree
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Read left child
            in >> val;
            if (val != "#") {
                node->left = new TreeNode(stoi(val));
                q.push(node->left);
            }
            
            // Read right child
            in >> val;
            if (val != "#") {
                node->right = new TreeNode(stoi(val));
                q.push(node->right);
            }
        }
        
        return root;
    }
};

// Example 3: Optimized Serialization and Deserialization for Binary Search Trees
// LeetCode 449: https://leetcode.com/problems/serialize-and-deserialize-bst/
class Codec3 {
public:
    // Serialize a BST to a string using preorder traversal
    // Since BST has ordering properties, we don't need to store null markers
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeBST(root, out);
        return out.str();
    }
    
    void serializeBST(TreeNode* root, ostringstream& out) {
        if (!root) return;
        
        // Preorder traversal: root -> left -> right
        out << root->val << " ";
        serializeBST(root->left, out);
        serializeBST(root->right, out);
    }
    
    // Deserialize a string to a BST using the BST property
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        istringstream in(data);
        vector<int> preorder;
        string val;
        
        while (in >> val) {
            preorder.push_back(stoi(val));
        }
        
        int index = 0;
        return deserializeBST(preorder, index, INT_MIN, INT_MAX);
    }
    
    TreeNode* deserializeBST(vector<int>& preorder, int& index, int lower, int upper) {
        // If all nodes are used or current value doesn't fit BST property, return null
        if (index >= preorder.size() || preorder[index] < lower || preorder[index] > upper) {
            return nullptr;
        }
        
        // Create node with current value
        int val = preorder[index++];
        TreeNode* root = new TreeNode(val);
        
        // Values less than current go to left subtree
        root->left = deserializeBST(preorder, index, lower, val);
        
        // Values greater than current go to right subtree
        root->right = deserializeBST(preorder, index, val, upper);
        
        return root;
    }
};

// Example 4: Find Duplicate Subtrees
// LeetCode 652: https://leetcode.com/problems/find-duplicate-subtrees/
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, vector<TreeNode*>> map;
    vector<TreeNode*> duplicates;
    
    // Helper function to serialize subtrees and find duplicates
    function<string(TreeNode*)> serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        
        // Create a unique string representation of the subtree
        string serialized = to_string(node->val) + "," + 
                            serialize(node->left) + "," + 
                            serialize(node->right);
        
        // Add current subtree to the map
        map[serialized].push_back(node);
        
        // If this is the second occurrence, add to result
        if (map[serialized].size() == 2) {
            duplicates.push_back(node);
        }
        
        return serialized;
    };
    
    serialize(root);
    return duplicates;
}

// Example 5: Check if a tree is a subtree of another tree
// LeetCode 572: https://leetcode.com/problems/subtree-of-another-tree/
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    // Helper function to check if two trees are identical
    function<bool(TreeNode*, TreeNode*)> isSameTree = [&](TreeNode* p, TreeNode* q) -> bool {
        if (!p && !q) return true;
        if (!p || !q) return false;
        
        return (p->val == q->val) && 
               isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    };
    
    // Helper function to serialize a tree
    function<string(TreeNode*)> serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        
        return to_string(node->val) + "," + 
               serialize(node->left) + "," + 
               serialize(node->right);
    };
    
    // Check if subtree exists using serialization
    string rootStr = serialize(root);
    string subStr = serialize(subRoot);
    
    // If subStr is a substring of rootStr, it might be a subtree
    // But we need to verify using isSameTree to ensure proper structure
    if (rootStr.find(subStr) != string::npos) {
        // Search for the subtree in the main tree
        function<bool(TreeNode*)> dfs = [&](TreeNode* node) -> bool {
            if (!node) return false;
            
            if (isSameTree(node, subRoot)) return true;
            
            return dfs(node->left) || dfs(node->right);
        };
        
        return dfs(root);
    }
    
    return false;
}

// Example 6: Clone a binary tree
TreeNode* cloneTree(TreeNode* root) {
    if (!root) return nullptr;
    
    // Create a new node with the same value
    TreeNode* newRoot = new TreeNode(root->val);
    
    // Clone left and right subtrees
    newRoot->left = cloneTree(root->left);
    newRoot->right = cloneTree(root->right);
    
    return newRoot;
}

// Example 7: Clone a binary tree using serialization and deserialization
TreeNode* cloneTreeUsingSerialization(TreeNode* root) {
    Codec1 codec;
    string serialized = codec.serialize(root);
    return codec.deserialize(serialized);
}

// Definition for n-ary tree node
class Node {
public:
    int val;
    vector<Node*> children;
    
    Node() {}
    Node(int _val) : val(_val) {}
    Node(int _val, vector<Node*> _children) : val(_val), children(_children) {}
};

// Example 8: Serialize and Deserialize N-ary Tree
// Similar to LeetCode 428: https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/
class NaryCodec {
public:
    // Serialize an N-ary tree to a string
    string serialize(Node* root) {
        if (!root) return "";
        
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }
    
    void serializeHelper(Node* node, ostringstream& out) {
        if (!node) {
            out << "# ";
            return;
        }
        
        // Serialize current node value
        out << node->val << " ";
        
        // Serialize number of children
        out << node->children.size() << " ";
        
        // Serialize each child
        for (Node* child : node->children) {
            serializeHelper(child, out);
        }
    }
    
    // Deserialize a string to an N-ary tree
    Node* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        istringstream in(data);
        return deserializeHelper(in);
    }
    
    Node* deserializeHelper(istringstream& in) {
        string val;
        in >> val;
        
        if (val == "#") return nullptr;
        
        // Create new node with the value
        Node* root = new Node(stoi(val));
        
        // Read number of children
        string childrenCount;
        in >> childrenCount;
        int count = stoi(childrenCount);
        
        // Deserialize each child
        for (int i = 0; i < count; i++) {
            Node* child = deserializeHelper(in);
            if (child) root->children.push_back(child);
        }
        
        return root;
    }
};

// Utility function to build a sample binary tree for testing
TreeNode* buildSampleTree() {
    /* Builds this tree:
            1
           / \
          2   3
         / \   \
        4   5   6
           /
          7
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->right->left = new TreeNode(7);
    
    return root;
}

// Utility function to build a sample binary search tree for testing
TreeNode* buildSampleBST() {
    /* Builds this BST:
            6
           / \
          2   8
         / \ / \
        0  4 7  9
          / \
         3   5
    */
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    
    return root;
}

// Utility function to build a sample N-ary tree for testing
Node* buildSampleNaryTree() {
    /* Builds this N-ary tree:
            1
          / | \
         3  2  4
        / \
       5   6
    */
    Node* root = new Node(1);
    Node* node3 = new Node(3);
    Node* node2 = new Node(2);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    Node* node6 = new Node(6);
    
    node3->children.push_back(node5);
    node3->children.push_back(node6);
    
    root->children.push_back(node3);
    root->children.push_back(node2);
    root->children.push_back(node4);
    
    return root;
}

// Utility function to print a binary tree in level order
void printLevelOrder(TreeNode* root) {
    if (!root) {
        cout << "Empty tree" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "# ";
            }
        }
    }
    cout << endl;
}

// Utility function to print N-ary tree in level order
void printNaryLevelOrder(Node* root) {
    if (!root) {
        cout << "Empty N-ary tree" << endl;
        return;
    }
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Node* node = q.front();
            q.pop();
            
            cout << node->val << "(";
            
            // Print all children
            for (size_t j = 0; j < node->children.size(); j++) {
                cout << node->children[j]->val;
                if (j < node->children.size() - 1) cout << ",";
            }
            
            cout << ") ";
            
            // Push all children to the queue
            for (Node* child : node->children) {
                q.push(child);
            }
        }
    }
    cout << endl;
}

// Free memory of the binary tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Free memory of the N-ary tree
void deleteNaryTree(Node* root) {
    if (!root) return;
    for (Node* child : root->children) {
        deleteNaryTree(child);
    }
    delete root;
}

// Main function to demonstrate the Serialization and Deserialization pattern
void demonstrateSerializationDeserialization() {
    // Example 1: Serialization and Deserialization using preorder traversal
    cout << "Example 1: Serialization and Deserialization using preorder traversal" << endl;
    TreeNode* tree1 = buildSampleTree();
    Codec1 codec1;
    string serialized1 = codec1.serialize(tree1);
    cout << "Serialized tree (preorder): " << serialized1 << endl;
    
    TreeNode* deserialized1 = codec1.deserialize(serialized1);
    cout << "Original tree (level order): ";
    printLevelOrder(tree1);
    cout << "Deserialized tree (level order): ";
    printLevelOrder(deserialized1);
    
    // Example 2: Serialization and Deserialization using level-order traversal
    cout << "\nExample 2: Serialization and Deserialization using level-order traversal" << endl;
    TreeNode* tree2 = buildSampleTree();
    Codec2 codec2;
    string serialized2 = codec2.serialize(tree2);
    cout << "Serialized tree (level-order): " << serialized2 << endl;
    
    TreeNode* deserialized2 = codec2.deserialize(serialized2);
    cout << "Original tree (level order): ";
    printLevelOrder(tree2);
    cout << "Deserialized tree (level order): ";
    printLevelOrder(deserialized2);
    
    // Example 3: Optimized Serialization and Deserialization for BST
    cout << "\nExample 3: Optimized Serialization and Deserialization for BST" << endl;
    TreeNode* bst = buildSampleBST();
    Codec3 codec3;
    string serialized3 = codec3.serialize(bst);
    cout << "Serialized BST (preorder, no null markers): " << serialized3 << endl;
    
    TreeNode* deserialized3 = codec3.deserialize(serialized3);
    cout << "Original BST (level order): ";
    printLevelOrder(bst);
    cout << "Deserialized BST (level order): ";
    printLevelOrder(deserialized3);
    
    // Example 6: Clone a binary tree
    cout << "\nExample 6: Clone a binary tree" << endl;
    TreeNode* original = buildSampleTree();
    TreeNode* clone = cloneTree(original);
    cout << "Original tree (level order): ";
    printLevelOrder(original);
    cout << "Cloned tree (level order): ";
    printLevelOrder(clone);
    
    // Example 7: Clone a binary tree using serialization and deserialization
    cout << "\nExample 7: Clone a binary tree using serialization and deserialization" << endl;
    TreeNode* original2 = buildSampleTree();
    TreeNode* clone2 = cloneTreeUsingSerialization(original2);
    cout << "Original tree (level order): ";
    printLevelOrder(original2);
    cout << "Cloned tree (level order): ";
    printLevelOrder(clone2);
    
    // Example 8: Serialize and Deserialize N-ary Tree
    cout << "\nExample 8: Serialize and Deserialize N-ary Tree" << endl;
    Node* naryTree = buildSampleNaryTree();
    NaryCodec naryCodec;
    string serializedNary = naryCodec.serialize(naryTree);
    cout << "Serialized N-ary tree: " << serializedNary << endl;
    
    Node* deserializedNary = naryCodec.deserialize(serializedNary);
    cout << "Original N-ary tree (level order): ";
    printNaryLevelOrder(naryTree);
    cout << "Deserialized N-ary tree (level order): ";
    printNaryLevelOrder(deserializedNary);
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(deserialized1);
    deleteTree(tree2);
    deleteTree(deserialized2);
    deleteTree(bst);
    deleteTree(deserialized3);
    deleteTree(original);
    deleteTree(clone);
    deleteTree(original2);
    deleteTree(clone2);
    deleteNaryTree(naryTree);
    deleteNaryTree(deserializedNary);
}

int main() {
    // Demonstrate the Serialization and Deserialization pattern
    demonstrateSerializationDeserialization();
    
    return 0;
}
