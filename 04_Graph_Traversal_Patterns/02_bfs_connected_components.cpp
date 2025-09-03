/**
 * Pattern: Graph BFS - Connected Components / Island Counting
 * 
 * Description:
 * This pattern involves using breadth-first search (BFS) to identify connected components
 * in a graph or count islands in a 2D grid. BFS explores all nodes at the current depth before
 * moving to nodes at the next depth level, which makes it particularly useful for finding
 * shortest paths in unweighted graphs.
 * 
 * Time Complexity: O(V + E) for graphs, O(M × N) for grids, where:
 * - V is the number of vertices, E is the number of edges
 * - M and N are the dimensions of the grid
 * 
 * Space Complexity: O(V) for graphs (queue size), O(min(M, N)) for grids
 * 
 * When to use:
 * - Finding shortest paths in unweighted graphs
 * - Level-by-level exploration
 * - When distance from a source is needed
 * - Determining the minimum number of steps/moves
 * 
 * LeetCode Problems:
 * - 994. Rotting Oranges
 * - 542. 01 Matrix
 * - 1091. Shortest Path in Binary Matrix
 * - 127. Word Ladder
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <climits> // For INT_MAX

using namespace std;

// Example 1: Rotting Oranges
// LeetCode 994: https://leetcode.com/problems/rotting-oranges/
class RottingOranges {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int freshOranges = 0;
        queue<pair<int, int>> rottenQueue;
        
        // Initialize: count fresh oranges and add initial rotten oranges to queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    freshOranges++;
                } else if (grid[i][j] == 2) {
                    rottenQueue.push({i, j});
                }
            }
        }
        
        // If there are no fresh oranges, return 0
        if (freshOranges == 0) {
            return 0;
        }
        
        // If there are no rotten oranges, but fresh oranges exist, impossible to rot all
        if (rottenQueue.empty()) {
            return -1;
        }
        
        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int minutes = 0;
        
        // BFS to rot oranges level by level
        while (!rottenQueue.empty() && freshOranges > 0) {
            int size = rottenQueue.size();
            
            // Process all rotten oranges at current level
            for (int i = 0; i < size; i++) {
                auto [x, y] = rottenQueue.front();
                rottenQueue.pop();
                
                // Check all 4 adjacent cells
                for (const auto& [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    // If adjacent cell is valid and has a fresh orange
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        // Rot the orange
                        grid[nx][ny] = 2;
                        freshOranges--;
                        rottenQueue.push({nx, ny});
                    }
                }
            }
            
            // Increment minutes after processing all oranges at current level
            minutes++;
        }
        
        // If there are still fresh oranges, it's impossible to rot all
        return freshOranges > 0 ? -1 : minutes;
    }
};

// Example 2: 01 Matrix
// LeetCode 542: https://leetcode.com/problems/01-matrix/
class Matrix01 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) {
            return {};
        }
        
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        
        // Initialize: add all 0s to queue and set their distance to 0
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        
        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // BFS to find distances
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            // Check all 4 adjacent cells
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                
                // If valid and we can provide a shorter path
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        
        return dist;
    }
};

// Example 3: Shortest Path in Binary Matrix
// LeetCode 1091: https://leetcode.com/problems/shortest-path-in-binary-matrix/
class ShortestPathBinaryMatrix {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Check if start or end is blocked
        if (grid[0][0] == 1 || grid[n-1][n-1] == 1) {
            return -1;
        }
        
        // 8 directions: up, up-right, right, down-right, down, down-left, left, up-left
        vector<pair<int, int>> directions = {
            {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
        };
        
        // BFS
        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1; // Mark as visited by setting to 1 (it's already 0, but we can reuse grid for visited status)
        
        int pathLength = 1;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                // If we've reached the bottom-right corner
                if (x == n - 1 && y == n - 1) {
                    return pathLength;
                }
                
                // Check all 8 directions
                for (const auto& [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    // If valid and not visited (cell is 0)
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                        grid[nx][ny] = 1; // Mark as visited
                        q.push({nx, ny});
                    }
                }
            }
            
            pathLength++; // Move to next level
        }
        
        return -1; // No path found
    }
};

// Example 4: Word Ladder
// LeetCode 127: https://leetcode.com/problems/word-ladder/
class WordLadder {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Convert wordList to a set for O(1) lookups
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // Check if endWord is in the wordSet
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        // BFS
        queue<string> q;
        q.push(beginWord);
        int level = 1; // Start at level 1 (beginWord counts as a step)
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                string currentWord = q.front();
                q.pop();
                
                // Try changing each character in the word
                for (int j = 0; j < currentWord.length(); j++) {
                    char originalChar = currentWord[j];
                    
                    // Try all possible characters
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue; // Skip the original character
                        
                        currentWord[j] = c;
                        
                        // If this is the endWord, return the level + 1
                        if (currentWord == endWord) {
                            return level + 1;
                        }
                        
                        // If the word is in the set, add it to the queue and remove from set
                        if (wordSet.find(currentWord) != wordSet.end()) {
                            q.push(currentWord);
                            wordSet.erase(currentWord); // Mark as visited
                        }
                    }
                    
                    // Restore the original character
                    currentWord[j] = originalChar;
                }
            }
            
            level++; // Move to next level
        }
        
        return 0; // No transformation sequence found
    }
};

// Example 5: Find Connected Components in a Graph (BFS version)
class ConnectedComponentsBFS {
private:
    void bfs(vector<vector<int>>& graph, int start, vector<bool>& visited, vector<int>& component) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            component.push_back(node);
            
            // Visit all adjacent nodes
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

public:
    vector<vector<int>> findComponents(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<vector<int>> components;
        
        // Try to start BFS from each unvisited node
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<int> component;
                bfs(graph, i, visited, component);
                components.push_back(component);
            }
        }
        
        return components;
    }
};

// Example 6: Bipartite Graph (Can the graph be colored using only 2 colors?)
// LeetCode 785: https://leetcode.com/problems/is-graph-bipartite/
class BipartiteGraph {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1); // -1: not colored, 0: color A, 1: color B
        
        // Try to color the graph starting from each uncolored node
        for (int start = 0; start < n; start++) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0; // Assign the first color
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    // Try to color all neighbors with the opposite color
                    for (int neighbor : graph[node]) {
                        if (color[neighbor] == -1) {
                            // Uncolored neighbor, assign opposite color
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            // Same color neighbor, graph is not bipartite
                            return false;
                        }
                    }
                }
            }
        }
        
        return true; // All components are bipartite
    }
};

// Utility function to print a 2D vector
template<typename T>
void print2DVector(const vector<vector<T>>& vec) {
    for (const auto& row : vec) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate the BFS connected components pattern
int main() {
    // Example 1: Rotting Oranges
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    
    cout << "Example 1: Rotting Oranges" << endl;
    cout << "Grid:" << endl;
    print2DVector(grid);
    
    RottingOranges solution1;
    int minutes = solution1.orangesRotting(grid);
    cout << "Minutes to rot all oranges: " << minutes << endl;
    
    // Example 2: 01 Matrix
    vector<vector<int>> mat = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 1}
    };
    
    cout << "\nExample 2: 01 Matrix" << endl;
    cout << "Matrix:" << endl;
    print2DVector(mat);
    
    Matrix01 solution2;
    vector<vector<int>> distances = solution2.updateMatrix(mat);
    cout << "Distances:" << endl;
    print2DVector(distances);
    
    // Example 3: Shortest Path in Binary Matrix
    vector<vector<int>> binaryMatrix = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    cout << "\nExample 3: Shortest Path in Binary Matrix" << endl;
    cout << "Grid:" << endl;
    print2DVector(binaryMatrix);
    
    ShortestPathBinaryMatrix solution3;
    int shortestPath = solution3.shortestPathBinaryMatrix(binaryMatrix);
    cout << "Length of shortest clear path: " << shortestPath << endl;
    
    // Example 4: Word Ladder
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    
    cout << "\nExample 4: Word Ladder" << endl;
    cout << "Begin word: " << beginWord << endl;
    cout << "End word: " << endWord << endl;
    cout << "Word list: ";
    for (const auto& word : wordList) {
        cout << word << " ";
    }
    cout << endl;
    
    WordLadder solution4;
    int transformations = solution4.ladderLength(beginWord, endWord, wordList);
    cout << "Shortest transformation sequence length: " << transformations << endl;
    
    // Example 5: Connected Components in a Graph (BFS)
    vector<vector<int>> graph = {
        {1, 2},       // Node 0 is connected to nodes 1 and 2
        {0},          // Node 1 is connected to node 0
        {0},          // Node 2 is connected to node 0
        {4},          // Node 3 is connected to node 4
        {3},          // Node 4 is connected to node 3
        {}            // Node 5 is isolated
    };
    
    cout << "\nExample 5: Connected Components in a Graph (BFS)" << endl;
    cout << "Graph adjacency list:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << "Node " << i << " -> ";
        for (int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    
    ConnectedComponentsBFS solution5;
    vector<vector<int>> components = solution5.findComponents(graph);
    cout << "Connected components:" << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "Component " << i << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    // Example 6: Bipartite Graph
    vector<vector<int>> bipartiteGraph = {
        {1, 3},    // Node 0 is connected to nodes 1 and 3
        {0, 2},    // Node 1 is connected to nodes 0 and 2
        {1, 3},    // Node 2 is connected to nodes 1 and 3
        {0, 2}     // Node 3 is connected to nodes 0 and 2
    };
    
    cout << "\nExample 6: Bipartite Graph" << endl;
    cout << "Graph adjacency list:" << endl;
    for (int i = 0; i < bipartiteGraph.size(); i++) {
        cout << "Node " << i << " -> ";
        for (int neighbor : bipartiteGraph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    
    BipartiteGraph solution6;
    bool isBipartite = solution6.isBipartite(bipartiteGraph);
    cout << "Is the graph bipartite? " << (isBipartite ? "Yes" : "No") << endl;
    
    return 0;
}
