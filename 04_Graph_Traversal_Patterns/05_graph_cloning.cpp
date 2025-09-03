/**
 * Pattern: Graph - Deep Copy / Cloning
 * 
 * Description:
 * This pattern involves creating a complete copy of a graph with the same structure
 * but different memory locations. When cloning a graph, we need to ensure that
 * all nodes and edges are properly duplicated, and the relationships between nodes
 * are preserved in the clone.
 * 
 * Time Complexity: O(V + E), where:
 * - V is the number of vertices
 * - E is the number of edges
 * 
 * Space Complexity: O(V) for visited map and recursion stack
 * 
 * When to use:
 * - Creating an independent copy of a graph structure
 * - Preserving an original graph while operating on a copy
 * - Immutable data structures that require copies rather than modifications
 * - Snapshot or state preservation scenarios
 * 
 * LeetCode Problems:
 * - 133. Clone Graph
 * - 138. Copy List with Random Pointer (similar concept applied to linked lists)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for a Node in undirected graph
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// Example 1: Clone Graph (DFS Approach)
// LeetCode 133: https://leetcode.com/problems/clone-graph/
class CloneGraph_DFS {
private:
    unordered_map<Node*, Node*> visited; // Maps original node to its clone
    
    Node* dfs(Node* node) {
        if (!node) return nullptr;
        
        // If node already visited, return its clone
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }
        
        // Create a clone of the current node
        Node* clone = new Node(node->val);
        
        // Mark as visited by storing the mapping
        visited[node] = clone;
        
        // Recursively clone all neighbors
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfs(neighbor));
        }
        
        return clone;
    }

public:
    Node* cloneGraph(Node* node) {
        visited.clear();
        return dfs(node);
    }
};

// Example 2: Clone Graph (BFS Approach)
// LeetCode 133: https://leetcode.com/problems/clone-graph/
class CloneGraph_BFS {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        // Maps original node to its clone
        unordered_map<Node*, Node*> visited;
        
        // Create a clone for the first node
        visited[node] = new Node(node->val);
        
        // BFS queue
        queue<Node*> q;
        q.push(node);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            // Process all neighbors
            for (Node* neighbor : curr->neighbors) {
                // If neighbor not visited, create a clone and add to queue
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                
                // Connect current clone with neighbor's clone
                visited[curr]->neighbors.push_back(visited[neighbor]);
            }
        }
        
        return visited[node];
    }
};

// Example 3: Definition for a Node with random pointer in a linked list
class RandomNode {
public:
    int val;
    RandomNode* next;
    RandomNode* random;
    
    RandomNode(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// Example 3: Copy List with Random Pointer
// LeetCode 138: https://leetcode.com/problems/copy-list-with-random-pointer/
class CopyRandomList {
public:
    RandomNode* copyRandomList(RandomNode* head) {
        if (!head) return nullptr;
        
        // Maps original node to its clone
        unordered_map<RandomNode*, RandomNode*> nodeMap;
        
        // First pass: create clones of all nodes
        RandomNode* curr = head;
        while (curr) {
            nodeMap[curr] = new RandomNode(curr->val);
            curr = curr->next;
        }
        
        // Second pass: connect next and random pointers
        curr = head;
        while (curr) {
            nodeMap[curr]->next = nodeMap[curr->next]; // might be nullptr, which is fine
            nodeMap[curr]->random = nodeMap[curr->random]; // might be nullptr, which is fine
            curr = curr->next;
        }
        
        return nodeMap[head];
    }
};

// Example 4: Copy List with Random Pointer (O(1) extra space)
class CopyRandomList_Constant_Space {
public:
    RandomNode* copyRandomList(RandomNode* head) {
        if (!head) return nullptr;
        
        // Step 1: Create new nodes and interweave them with original list
        // Original: A -> B -> C
        // Modified: A -> A' -> B -> B' -> C -> C'
        RandomNode* curr = head;
        while (curr) {
            RandomNode* copy = new RandomNode(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }
        
        // Step 2: Assign random pointers for new nodes
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }
        
        // Step 3: Separate the interweaved lists
        RandomNode dummy(0);
        RandomNode* newCurr = &dummy;
        curr = head;
        
        while (curr) {
            // Extract the copy
            newCurr->next = curr->next;
            newCurr = newCurr->next;
            
            // Restore original list
            curr->next = curr->next->next;
            curr = curr->next;
        }
        
        return dummy.next;
    }
};

// Example 5: Deep Copy a Directed Graph with Weighted Edges
class WeightedNode {
public:
    int val;
    vector<pair<WeightedNode*, int>> neighbors; // (neighbor, weight)
    
    WeightedNode(int _val) {
        val = _val;
    }
};

class CloneWeightedGraph {
private:
    unordered_map<WeightedNode*, WeightedNode*> visited;
    
    WeightedNode* dfs(WeightedNode* node) {
        if (!node) return nullptr;
        
        // If already visited, return the clone
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }
        
        // Create a clone
        WeightedNode* clone = new WeightedNode(node->val);
        visited[node] = clone;
        
        // Clone all neighbors with weights
        for (const auto& [neighbor, weight] : node->neighbors) {
            WeightedNode* clonedNeighbor = dfs(neighbor);
            clone->neighbors.push_back({clonedNeighbor, weight});
        }
        
        return clone;
    }

public:
    WeightedNode* cloneGraph(WeightedNode* node) {
        visited.clear();
        return dfs(node);
    }
};

// Utility functions for graph creation and visualization
Node* createGraph() {
    // Create a graph: 1 -- 2
    //                 |    |
    //                 4 -- 3
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    
    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};
    
    return node1;
}

WeightedNode* createWeightedGraph() {
    // Create a weighted graph:
    // 1 --(5)--> 2
    // |          |
    // |(3)       |(2)
    // v          v
    // 3 --(1)--> 4
    WeightedNode* node1 = new WeightedNode(1);
    WeightedNode* node2 = new WeightedNode(2);
    WeightedNode* node3 = new WeightedNode(3);
    WeightedNode* node4 = new WeightedNode(4);
    
    node1->neighbors = {{node2, 5}, {node3, 3}};
    node2->neighbors = {{node4, 2}};
    node3->neighbors = {{node4, 1}};
    
    return node1;
}

RandomNode* createRandomList() {
    RandomNode* head = new RandomNode(1);
    RandomNode* node2 = new RandomNode(2);
    RandomNode* node3 = new RandomNode(3);
    RandomNode* node4 = new RandomNode(4);
    
    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    // Set random pointers
    head->random = node3;    // 1's random points to 3
    node2->random = head;    // 2's random points to 1
    node3->random = node4;   // 3's random points to 4
    node4->random = node2;   // 4's random points to 2
    
    return head;
}

void printGraph(Node* node) {
    if (!node) return;
    
    unordered_map<int, bool> visited;
    queue<Node*> q;
    q.push(node);
    visited[node->val] = true;
    
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        
        cout << "Node " << curr->val << " -> ";
        for (Node* neighbor : curr->neighbors) {
            cout << neighbor->val << " ";
            
            // Enqueue unvisited neighbors
            if (!visited[neighbor->val]) {
                visited[neighbor->val] = true;
                q.push(neighbor);
            }
        }
        cout << endl;
    }
}

void printWeightedGraph(WeightedNode* node) {
    if (!node) return;
    
    unordered_map<int, bool> visited;
    queue<WeightedNode*> q;
    q.push(node);
    visited[node->val] = true;
    
    while (!q.empty()) {
        WeightedNode* curr = q.front();
        q.pop();
        
        cout << "Node " << curr->val << " -> ";
        for (const auto& [neighbor, weight] : curr->neighbors) {
            cout << neighbor->val << " (weight: " << weight << ") ";
            
            // Enqueue unvisited neighbors
            if (!visited[neighbor->val]) {
                visited[neighbor->val] = true;
                q.push(neighbor);
            }
        }
        cout << endl;
    }
}

void printRandomList(RandomNode* head) {
    while (head) {
        cout << "Node " << head->val;
        if (head->random) {
            cout << ", random -> " << head->random->val;
        } else {
            cout << ", random -> nullptr";
        }
        cout << endl;
        head = head->next;
    }
}

// Check if two graphs are identical in structure
bool areGraphsEqual(Node* original, Node* clone) {
    if (!original && !clone) return true;
    if (!original || !clone) return false;
    
    unordered_map<int, bool> visited;
    queue<pair<Node*, Node*>> q;
    
    q.push({original, clone});
    visited[original->val] = true;
    
    while (!q.empty()) {
        auto [origNode, cloneNode] = q.front();
        q.pop();
        
        // Check if values match
        if (origNode->val != cloneNode->val) return false;
        
        // Check if number of neighbors match
        if (origNode->neighbors.size() != cloneNode->neighbors.size()) return false;
        
        // Create a map of neighbor values to check
        unordered_map<int, bool> origNeighbors;
        for (Node* neighbor : origNode->neighbors) {
            origNeighbors[neighbor->val] = true;
        }
        
        // Check if all clone neighbors exist in original
        for (Node* neighbor : cloneNode->neighbors) {
            if (!origNeighbors[neighbor->val]) return false;
        }
        
        // Enqueue unvisited neighbors
        for (int i = 0; i < origNode->neighbors.size(); i++) {
            Node* origNeighbor = origNode->neighbors[i];
            Node* cloneNeighbor = cloneNode->neighbors[i];
            
            if (!visited[origNeighbor->val]) {
                visited[origNeighbor->val] = true;
                q.push({origNeighbor, cloneNeighbor});
            }
        }
    }
    
    return true;
}

// Free memory of graph nodes
void cleanupGraph(Node* node) {
    if (!node) return;
    
    unordered_map<int, bool> visited;
    queue<Node*> q;
    q.push(node);
    visited[node->val] = true;
    
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        
        for (Node* neighbor : curr->neighbors) {
            if (!visited[neighbor->val]) {
                visited[neighbor->val] = true;
                q.push(neighbor);
            }
        }
        
        // Mark current node for deletion
        visited[curr->val] = true;
    }
    
    // Delete all nodes
    for (auto it = visited.begin(); it != visited.end(); it++) {
        delete node;
    }
}

// Main function to demonstrate graph cloning
int main() {
    // Example 1: Clone Graph using DFS
    cout << "Example 1: Clone Graph (DFS)" << endl;
    Node* originalGraph = createGraph();
    cout << "Original Graph:" << endl;
    printGraph(originalGraph);
    
    CloneGraph_DFS solution1;
    Node* clonedGraph = solution1.cloneGraph(originalGraph);
    
    cout << "Cloned Graph:" << endl;
    printGraph(clonedGraph);
    
    cout << "Are graphs equal? " << (areGraphsEqual(originalGraph, clonedGraph) ? "Yes" : "No") << endl;
    cout << "Are nodes the same objects? " << (originalGraph == clonedGraph ? "Yes" : "No") << endl;
    
    // Example 2: Clone Graph using BFS
    cout << "\nExample 2: Clone Graph (BFS)" << endl;
    CloneGraph_BFS solution2;
    Node* clonedGraph2 = solution2.cloneGraph(originalGraph);
    
    cout << "Cloned Graph (BFS):" << endl;
    printGraph(clonedGraph2);
    
    cout << "Are graphs equal? " << (areGraphsEqual(originalGraph, clonedGraph2) ? "Yes" : "No") << endl;
    cout << "Are nodes the same objects? " << (originalGraph == clonedGraph2 ? "Yes" : "No") << endl;
    
    // Example 3: Copy List with Random Pointer
    cout << "\nExample 3: Copy List with Random Pointer" << endl;
    RandomNode* originalList = createRandomList();
    cout << "Original List:" << endl;
    printRandomList(originalList);
    
    CopyRandomList solution3;
    RandomNode* clonedList = solution3.copyRandomList(originalList);
    
    cout << "Cloned List:" << endl;
    printRandomList(clonedList);
    cout << "Are lists same objects? " << (originalList == clonedList ? "Yes" : "No") << endl;
    
    // Example 4: Copy List with O(1) Space
    cout << "\nExample 4: Copy List with O(1) Space" << endl;
    CopyRandomList_Constant_Space solution4;
    RandomNode* clonedList2 = solution4.copyRandomList(originalList);
    
    cout << "Cloned List (O(1) Space):" << endl;
    printRandomList(clonedList2);
    cout << "Are lists same objects? " << (originalList == clonedList2 ? "Yes" : "No") << endl;
    
    // Example 5: Clone Weighted Graph
    cout << "\nExample 5: Clone Weighted Graph" << endl;
    WeightedNode* originalWeightedGraph = createWeightedGraph();
    cout << "Original Weighted Graph:" << endl;
    printWeightedGraph(originalWeightedGraph);
    
    CloneWeightedGraph solution5;
    WeightedNode* clonedWeightedGraph = solution5.cloneGraph(originalWeightedGraph);
    
    cout << "Cloned Weighted Graph:" << endl;
    printWeightedGraph(clonedWeightedGraph);
    cout << "Are graphs same objects? " << (originalWeightedGraph == clonedWeightedGraph ? "Yes" : "No") << endl;
    
    // Clean up memory
    cleanupGraph(originalGraph);
    cleanupGraph(clonedGraph);
    cleanupGraph(clonedGraph2);
    
    return 0;
}
