/**
 * Pattern: Graph DFS - Cycle Detection (Directed Graph)
 * 
 * Description:
 * This pattern involves using depth-first search (DFS) with coloring or visited states
 * to detect cycles in directed graphs. A cycle exists in a directed graph if there is a path
 * that starts and ends at the same vertex and the path length is greater than 0.
 * 
 * Time Complexity: O(V + E), where:
 * - V is the number of vertices
 * - E is the number of edges
 * 
 * Space Complexity: O(V) for recursion stack and visited/color arrays
 * 
 * When to use:
 * - Checking if a directed graph has cycles
 * - Determining if a directed graph is a DAG (Directed Acyclic Graph)
 * - Finding cyclic dependencies in a system
 * - Validating topological sorting is possible
 * 
 * LeetCode Problems:
 * - 207. Course Schedule
 * - 802. Find Eventual Safe States
 * - 1059. All Paths from Source Lead to Destination
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Example 1: Detect Cycle in a Directed Graph using 3-coloring
class CycleDetectionDirected {
private:
    // Colors for DFS:
    // 0: White (not visited)
    // 1: Gray (being visited / in the recursion stack)
    // 2: Black (completely visited)
    bool dfs(vector<vector<int>>& graph, int node, vector<int>& color) {
        // Mark node as being visited
        color[node] = 1;
        
        // Check all adjacent nodes
        for (int neighbor : graph[node]) {
            // If neighbor is in the recursion stack, a cycle is found
            if (color[neighbor] == 1) {
                return true;
            }
            
            // If neighbor is not visited and a cycle is found in DFS from the neighbor
            if (color[neighbor] == 0 && dfs(graph, neighbor, color)) {
                return true;
            }
        }
        
        // Mark node as completely visited
        color[node] = 2;
        return false;
    }

public:
    bool hasCycle(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0); // All nodes start as not visited (white)
        
        // Try to start DFS from each unvisited node
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                if (dfs(graph, i, color)) {
                    return true; // Cycle found
                }
            }
        }
        
        return false; // No cycle found
    }
    
    // Variant: Find all nodes in a cycle (useful for debugging)
    vector<int> findCycleNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0);
        vector<int> parent(n, -1);
        vector<int> cycleNodes;
        
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                if (dfsWithPath(graph, i, color, parent, cycleNodes)) {
                    return cycleNodes;
                }
            }
        }
        
        return {}; // No cycle found
    }
    
private:
    bool dfsWithPath(vector<vector<int>>& graph, int node, vector<int>& color, 
                    vector<int>& parent, vector<int>& cycleNodes) {
        color[node] = 1; // Mark as being visited
        
        for (int neighbor : graph[node]) {
            if (color[neighbor] == 1) {
                // Cycle found, reconstruct the cycle path
                int current = node;
                cycleNodes.push_back(neighbor); // Start with the neighbor that completes the cycle
                
                // Trace back until we reach the neighbor again
                while (current != neighbor) {
                    cycleNodes.push_back(current);
                    current = parent[current];
                }
                
                return true;
            }
            
            if (color[neighbor] == 0) {
                parent[neighbor] = node;
                if (dfsWithPath(graph, neighbor, color, parent, cycleNodes)) {
                    return true;
                }
            }
        }
        
        color[node] = 2; // Mark as completely visited
        return false;
    }
};

// Example 2: Course Schedule (Determine if you can finish all courses)
// LeetCode 207: https://leetcode.com/problems/course-schedule/
class CourseSchedule {
private:
    bool dfs(vector<vector<int>>& graph, int node, vector<int>& state) {
        // Mark as being visited
        state[node] = 1;
        
        // Check all prerequisites
        for (int neighbor : graph[node]) {
            // If the prerequisite is in recursion stack, we found a cycle
            if (state[neighbor] == 1) {
                return false;
            }
            
            // If the prerequisite is not visited and we can't finish it
            if (state[neighbor] == 0 && !dfs(graph, neighbor, state)) {
                return false;
            }
        }
        
        // Mark as completely visited
        state[node] = 2;
        return true;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> graph(numCourses);
        for (const auto& prereq : prerequisites) {
            // prereq[0] depends on prereq[1]
            graph[prereq[0]].push_back(prereq[1]);
        }
        
        // 0: Not visited, 1: Being visited, 2: Completely visited
        vector<int> state(numCourses, 0);
        
        // Check if we can finish all courses
        for (int i = 0; i < numCourses; i++) {
            if (state[i] == 0) {
                if (!dfs(graph, i, state)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// Example 3: Find Eventual Safe States
// LeetCode 802: https://leetcode.com/problems/find-eventual-safe-states/
class EventualSafeStates {
private:
    bool dfs(vector<vector<int>>& graph, int node, vector<int>& color) {
        // If node is already processed
        if (color[node] > 0) {
            return color[node] == 2; // Return true if safe, false if unsafe
        }
        
        // Mark as being visited
        color[node] = 1;
        
        // Check all neighbors
        for (int neighbor : graph[node]) {
            // If neighbor is unsafe or leads to a cycle
            if (color[neighbor] == 1 || !dfs(graph, neighbor, color)) {
                return false;
            }
        }
        
        // All paths from this node are safe
        color[node] = 2;
        return true;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0); // 0: unvisited, 1: visiting, 2: safe
        vector<int> result;
        
        for (int i = 0; i < n; i++) {
            if (dfs(graph, i, color)) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};

// Example 4: All Paths from Source Lead to Destination
// LeetCode 1059: https://leetcode.com/problems/all-paths-from-source-lead-to-destination/
class AllPathsToDestination {
private:
    // 0: not visited, 1: being visited, 2: completely visited
    bool dfs(vector<vector<int>>& graph, int node, int destination, vector<int>& state) {
        // If we reached a leaf node that is not the destination
        if (graph[node].empty()) {
            return node == destination;
        }
        
        // Mark as being visited
        state[node] = 1;
        
        // Check all neighbors
        for (int neighbor : graph[node]) {
            // If there's a cycle, not all paths lead to destination
            if (state[neighbor] == 1) {
                return false;
            }
            
            // If neighbor is not visited or if we've already determined neighbor leads to destination
            if (state[neighbor] == 0 && !dfs(graph, neighbor, destination, state)) {
                return false;
            }
        }
        
        // Mark as completely visited
        state[node] = 2;
        return true;
    }

public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        
        // Destination should be a leaf node (no outgoing edges)
        if (!graph[destination].empty()) {
            return false;
        }
        
        vector<int> state(n, 0);
        return dfs(graph, source, destination, state);
    }
};

// Example 5: Cycle Detection with Back Edge Identification
class CycleWithBackEdges {
private:
    bool dfs(vector<vector<int>>& graph, int node, vector<bool>& visited, 
             vector<bool>& inStack, vector<pair<int, int>>& backEdges) {
        // Mark the current node as visited and part of recursion stack
        visited[node] = true;
        inStack[node] = true;
        
        // Check all adjacent vertices
        for (int neighbor : graph[node]) {
            // If not visited, recursively check
            if (!visited[neighbor]) {
                if (dfs(graph, neighbor, visited, inStack, backEdges)) {
                    return true;
                }
            } 
            // If the neighbor is in the recursion stack, we found a back edge
            else if (inStack[neighbor]) {
                backEdges.push_back({node, neighbor});
                return true;
            }
        }
        
        // Remove the vertex from recursion stack
        inStack[node] = false;
        return false;
    }

public:
    bool hasCycle(vector<vector<int>>& graph, vector<pair<int, int>>& backEdges) {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<bool> inStack(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(graph, i, visited, inStack, backEdges)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// Example 6: Topological Sort using DFS (fails if there's a cycle)
class TopologicalSortDFS {
private:
    void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited, stack<int>& result) {
        // Mark the current node as visited
        visited[node] = true;
        
        // Recursively visit all neighbors
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(graph, neighbor, visited, result);
            }
        }
        
        // Add current node to result after all its descendants
        result.push(node);
    }

public:
    vector<int> topologicalSort(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false);
        stack<int> result;
        
        // Visit all nodes
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(graph, i, visited, result);
            }
        }
        
        // Convert stack to vector
        vector<int> sortedOrder;
        while (!result.empty()) {
            sortedOrder.push_back(result.top());
            result.pop();
        }
        
        return sortedOrder;
    }
    
    bool isValidTopologicalSort(vector<vector<int>>& graph, vector<int>& order) {
        int n = graph.size();
        
        // Create a map of node to its position in the order
        vector<int> position(n);
        for (int i = 0; i < n; i++) {
            position[order[i]] = i;
        }
        
        // Check if the order satisfies all edges
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                // For each edge u->v, u should come before v in the order
                if (position[u] >= position[v]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// Utility functions to build and print graphs
vector<vector<int>> buildDirectedGraph(int n, vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
    }
    return graph;
}

void printGraph(const vector<vector<int>>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << "Node " << i << " -> ";
        for (int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate the directed cycle detection pattern
int main() {
    // Example 1: Basic Cycle Detection
    vector<pair<int, int>> edges1 = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}
    };
    vector<vector<int>> graph1 = buildDirectedGraph(4, edges1);
    
    cout << "Example 1: Basic Cycle Detection" << endl;
    cout << "Graph:" << endl;
    printGraph(graph1);
    
    CycleDetectionDirected solution1;
    bool hasCycle = solution1.hasCycle(graph1);
    cout << "Has cycle: " << (hasCycle ? "Yes" : "No") << endl;
    
    vector<int> cycleNodes = solution1.findCycleNodes(graph1);
    cout << "Nodes in cycle: ";
    for (int node : cycleNodes) {
        cout << node << " ";
    }
    cout << endl;
    
    // Example 2: Course Schedule
    vector<vector<int>> prerequisites = {
        {1, 0}, {0, 2}, {2, 1}
    };
    
    cout << "\nExample 2: Course Schedule" << endl;
    cout << "Prerequisites (course, prerequisite):" << endl;
    for (const auto& prereq : prerequisites) {
        cout << prereq[0] << " requires " << prereq[1] << endl;
    }
    
    CourseSchedule solution2;
    bool canFinish = solution2.canFinish(3, prerequisites);
    cout << "Can finish all courses: " << (canFinish ? "Yes" : "No") << endl;
    
    // Example 3: Eventual Safe States
    vector<pair<int, int>> edges3 = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 5}, {3, 0}, {4, 5}
    };
    vector<vector<int>> graph3 = buildDirectedGraph(6, edges3);
    
    cout << "\nExample 3: Eventual Safe States" << endl;
    cout << "Graph:" << endl;
    printGraph(graph3);
    
    EventualSafeStates solution3;
    vector<int> safeNodes = solution3.eventualSafeNodes(graph3);
    cout << "Safe nodes: ";
    for (int node : safeNodes) {
        cout << node << " ";
    }
    cout << endl;
    
    // Example 4: All Paths to Destination
    vector<pair<int, int>> edges4 = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}
    };
    vector<vector<int>> graph4 = buildDirectedGraph(4, edges4);
    
    cout << "\nExample 4: All Paths to Destination" << endl;
    cout << "Graph:" << endl;
    printGraph(graph4);
    
    AllPathsToDestination solution4;
    // Convert edges to the format expected by leadsToDestination
    vector<vector<int>> edgesFormat;
    for (const auto& edge : edges4) {
        edgesFormat.push_back({edge.first, edge.second});
    }
    bool allPathsLead = solution4.leadsToDestination(4, edgesFormat, 0, 3);
    cout << "All paths from source 0 lead to destination 3: " << (allPathsLead ? "Yes" : "No") << endl;
    
    // Example 5: Topological Sort
    vector<pair<int, int>> edges5 = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
    };
    vector<vector<int>> graph5 = buildDirectedGraph(6, edges5);
    
    cout << "\nExample 5: Topological Sort" << endl;
    cout << "Graph:" << endl;
    printGraph(graph5);
    
    TopologicalSortDFS solution5;
    vector<int> sortedOrder = solution5.topologicalSort(graph5);
    cout << "Topological sort: ";
    for (int node : sortedOrder) {
        cout << node << " ";
    }
    cout << endl;
    
    bool isValid = solution5.isValidTopologicalSort(graph5, sortedOrder);
    cout << "Is valid topological sort: " << (isValid ? "Yes" : "No") << endl;
    
    return 0;
}
