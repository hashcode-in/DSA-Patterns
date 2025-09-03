/**
 * Pattern: Graph DFS - Connected Components / Island Counting
 * 
 * Description:
 * This pattern involves using depth-first search (DFS) to identify connected components
 * in a graph or count islands in a 2D grid. Connected components are groups of nodes
 * where each node is reachable from any other node in the group.
 * 
 * Time Complexity: O(V + E) for graphs, O(M × N) for grids, where:
 * - V is the number of vertices, E is the number of edges
 * - M and N are the dimensions of the grid
 * 
 * Space Complexity: O(V) for graphs (recursion stack), O(M × N) for grids
 * 
 * When to use:
 * - Finding separate groups of connected nodes
 * - Counting regions/islands in a grid
 * - Identifying isolated components
 * - Flood fill algorithms
 * 
 * LeetCode Problems:
 * - 200. Number of Islands
 * - 547. Number of Provinces
 * - 130. Surrounded Regions
 * - 695. Max Area of Island
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Example 1: Number of Islands (Grid-based Connected Components)
// LeetCode 200: https://leetcode.com/problems/number-of-islands/
class NumberOfIslands {
private:
    // DFS to mark all connected '1's as visited (change '1' to '0')
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Check if current cell is out of bounds or not an island ('0' or already visited)
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
            return;
        }
        
        // Mark current cell as visited
        grid[i][j] = '0';
        
        // Recursively visit all adjacent cells (4-directional)
        dfs(grid, i + 1, j); // Down
        dfs(grid, i - 1, j); // Up
        dfs(grid, i, j + 1); // Right
        dfs(grid, i, j - 1); // Left
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int islands = 0;
        
        // Iterate through each cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find an unvisited island, increment count and explore the island
                if (grid[i][j] == '1') {
                    islands++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return islands;
    }
};

// Example 2: Find Connected Components in a Graph (Adjacency List)
class ConnectedComponents {
private:
    void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<int>& component) {
        // Mark current node as visited
        visited[node] = true;
        component.push_back(node);
        
        // Visit all adjacent nodes
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(graph, neighbor, visited, component);
            }
        }
    }

public:
    vector<vector<int>> findComponents(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<vector<int>> components;
        
        // Try to start DFS from each unvisited node
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<int> component;
                dfs(graph, i, visited, component);
                components.push_back(component);
            }
        }
        
        return components;
    }
};

// Example 3: Surrounded Regions (Capture regions surrounded by 'X')
// LeetCode 130: https://leetcode.com/problems/surrounded-regions/
class SurroundedRegions {
private:
    // DFS to mark all connected 'O's that are not surrounded
    void dfs(vector<vector<char>>& board, int i, int j) {
        int m = board.size();
        int n = board[0].size();
        
        // Check if out of bounds or not an 'O'
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != 'O') {
            return;
        }
        
        // Mark as temporarily visited with a different character
        board[i][j] = 'T';
        
        // Visit all 4 adjacent cells
        dfs(board, i + 1, j);
        dfs(board, i - 1, j);
        dfs(board, i, j + 1);
        dfs(board, i, j - 1);
    }

public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }
        
        int m = board.size();
        int n = board[0].size();
        
        // Step 1: Mark all 'O's connected to boundaries as 'T'
        
        // First and last rows
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') {
                dfs(board, 0, j);
            }
            if (board[m - 1][j] == 'O') {
                dfs(board, m - 1, j);
            }
        }
        
        // First and last columns
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                dfs(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                dfs(board, i, n - 1);
            }
        }
        
        // Step 2: Convert all remaining 'O's to 'X' and 'T's back to 'O'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X'; // Surrounded 'O's become 'X'
                } else if (board[i][j] == 'T') {
                    board[i][j] = 'O'; // 'T's (non-surrounded 'O's) go back to 'O'
                }
            }
        }
    }
};

// Example 4: Number of Provinces (Adjacency Matrix)
// LeetCode 547: https://leetcode.com/problems/number-of-provinces/
class NumberOfProvinces {
private:
    void dfs(vector<vector<int>>& isConnected, int city, vector<bool>& visited) {
        visited[city] = true;
        
        // Visit all connected cities
        for (int i = 0; i < isConnected.size(); i++) {
            if (isConnected[city][i] == 1 && !visited[i]) {
                dfs(isConnected, i, visited);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        
        // Try to start DFS from each unvisited city
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                dfs(isConnected, i, visited);
            }
        }
        
        return provinces;
    }
};

// Example 5: Max Area of Island
// LeetCode 695: https://leetcode.com/problems/max-area-of-island/
class MaxAreaOfIsland {
private:
    // DFS to calculate the area of an island and mark it as visited
    int dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Check if out of bounds or not land
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) {
            return 0;
        }
        
        // Mark as visited
        grid[i][j] = 0;
        
        // Current cell contributes 1 to the area, plus all adjacent land
        return 1 + dfs(grid, i + 1, j) + dfs(grid, i - 1, j) + 
                   dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int maxArea = 0;
        
        // Iterate through each cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // Calculate area of the current island
                    int area = dfs(grid, i, j);
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
};

// Example 6: Number of Closed Islands
// LeetCode 1254: https://leetcode.com/problems/number-of-closed-islands/
class NumberOfClosedIslands {
private:
    // DFS to check if an island is closed and mark it as visited
    bool dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        
        // If we hit the boundary, island is not closed
        if (i < 0 || i >= m || j < 0 || j >= n) {
            return false;
        }
        
        // If we hit water, this path is closed
        if (grid[i][j] == 1) {
            return true;
        }
        
        // Mark as visited
        grid[i][j] = 1;
        
        // Check all 4 directions and ensure all paths are closed
        bool isClosed = true;
        isClosed &= dfs(grid, i + 1, j);
        isClosed &= dfs(grid, i - 1, j);
        isClosed &= dfs(grid, i, j + 1);
        isClosed &= dfs(grid, i, j - 1);
        
        return isClosed;
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int closedIslands = 0;
        
        // Iterate through each cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find an unvisited land cell
                if (grid[i][j] == 0) {
                    // Check if it forms a closed island
                    if (dfs(grid, i, j)) {
                        closedIslands++;
                    }
                }
            }
        }
        
        return closedIslands;
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

// Main function to demonstrate the connected components pattern
int main() {
    // Example 1: Number of Islands
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    
    cout << "Example 1: Number of Islands" << endl;
    cout << "Grid:" << endl;
    print2DVector(grid);
    
    NumberOfIslands solution1;
    int islands = solution1.numIslands(grid);
    cout << "Number of islands: " << islands << endl;
    
    // Example 2: Connected Components in a Graph
    vector<vector<int>> graph = {
        {1, 2},       // Node 0 is connected to nodes 1 and 2
        {0},          // Node 1 is connected to node 0
        {0},          // Node 2 is connected to node 0
        {4},          // Node 3 is connected to node 4
        {3},          // Node 4 is connected to node 3
        {}            // Node 5 is isolated
    };
    
    cout << "\nExample 2: Connected Components in a Graph" << endl;
    cout << "Graph adjacency list:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << "Node " << i << " -> ";
        for (int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    
    ConnectedComponents solution2;
    vector<vector<int>> components = solution2.findComponents(graph);
    
    cout << "Connected components:" << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "Component " << i << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    // Example 3: Surrounded Regions
    vector<vector<char>> board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    
    cout << "\nExample 3: Surrounded Regions" << endl;
    cout << "Before:" << endl;
    print2DVector(board);
    
    SurroundedRegions solution3;
    solution3.solve(board);
    
    cout << "After capturing surrounded regions:" << endl;
    print2DVector(board);
    
    // Example 4: Number of Provinces
    vector<vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    
    cout << "\nExample 4: Number of Provinces" << endl;
    cout << "isConnected matrix:" << endl;
    print2DVector(isConnected);
    
    NumberOfProvinces solution4;
    int provinces = solution4.findCircleNum(isConnected);
    cout << "Number of provinces: " << provinces << endl;
    
    // Example 5: Max Area of Island
    vector<vector<int>> grid2 = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
    };
    
    cout << "\nExample 5: Max Area of Island" << endl;
    cout << "Grid:" << endl;
    print2DVector(grid2);
    
    MaxAreaOfIsland solution5;
    int maxArea = solution5.maxAreaOfIsland(grid2);
    cout << "Maximum area of an island: " << maxArea << endl;
    
    return 0;
}
