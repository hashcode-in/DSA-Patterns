/**
 * Pattern: Graph - Shortest Path (Dijkstra's Algorithm)
 * 
 * Description:
 * Dijkstra's algorithm is a greedy algorithm for finding the shortest path from a source node 
 * to all other nodes in a weighted graph with non-negative edge weights. It works by iteratively 
 * selecting the node with the minimum distance, relaxing its outgoing edges, and repeating until 
 * all nodes are processed.
 * 
 * Time Complexity: O((V + E) log V) using a priority queue, where:
 * - V is the number of vertices
 * - E is the number of edges
 * 
 * Space Complexity: O(V + E) for the priority queue and distance array
 * 
 * When to use:
 * - Finding shortest paths in weighted graphs with non-negative edge weights
 * - GPS navigation and route planning
 * - Network routing protocols
 * - Resource allocation optimization
 * - When the exact shortest path is needed (not just an estimate)
 * 
 * LeetCode Problems:
 * - 743. Network Delay Time
 * - 1514. Path with Maximum Probability
 * - 1631. Path With Minimum Effort
 * - 778. Swim in Rising Water
 * - 2290. Minimum Obstacle Removal to Reach Corner
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Example 1: Basic Dijkstra's Algorithm Implementation
class DijkstraAlgorithm {
public:
    // Graph represented as adjacency list of pairs (neighbor, weight)
    vector<int> shortestPath(int n, vector<vector<pair<int, int>>>& graph, int src) {
        // Initialize distances with infinity
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        
        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            // Skip outdated entries
            if (d > dist[u]) continue;
            
            // Explore all neighbors
            for (auto& [v, weight] : graph[u]) {
                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // Variant: Return actual paths, not just distances
    pair<vector<int>, vector<vector<int>>> shortestPathWithRoutes(
        int n, vector<vector<pair<int, int>>>& graph, int src) {
        
        // Initialize distances and parent pointers
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        dist[src] = 0;
        
        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            // Skip outdated entries
            if (d > dist[u]) continue;
            
            // Explore all neighbors
            for (auto& [v, weight] : graph[u]) {
                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Reconstruct paths
        vector<vector<int>> paths(n);
        for (int i = 0; i < n; i++) {
            if (i == src || dist[i] == INT_MAX) continue;
            
            int current = i;
            while (current != -1) {
                paths[i].push_back(current);
                current = parent[current];
            }
            reverse(paths[i].begin(), paths[i].end());
        }
        
        return {dist, paths};
    }
};

// Example 2: Network Delay Time
// LeetCode 743: https://leetcode.com/problems/network-delay-time/
class NetworkDelayTime {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& time : times) {
            int u = time[0];
            int v = time[1];
            int w = time[2];
            graph[u].push_back({v, w});
        }
        
        // Initialize distances
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            // Skip outdated entries
            if (d > dist[u]) continue;
            
            // Explore all neighbors
            for (auto& [v, time] : graph[u]) {
                // Relaxation step
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Find the maximum time
        int maxTime = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) return -1; // Unreachable node
            maxTime = max(maxTime, dist[i]);
        }
        
        return maxTime;
    }
};

// Example 3: Path with Maximum Probability
// LeetCode 1514: https://leetcode.com/problems/path-with-maximum-probability/
class MaxProbability {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Build adjacency list with probabilities
        vector<vector<pair<int, double>>> graph(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];
            graph[u].push_back({v, prob});
            graph[v].push_back({u, prob}); // Undirected graph
        }
        
        // Initialize probabilities
        vector<double> maxProb(n, 0.0);
        maxProb[start] = 1.0;
        
        // Max-heap priority queue: (probability, node)
        // Note: Using negative probabilities to get max-heap behavior from min-heap
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start});
        
        // Modified Dijkstra's algorithm for maximum probability
        while (!pq.empty()) {
            double prob = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            // Reached the end
            if (u == end) return prob;
            
            // Skip outdated entries (lower probability than already known)
            if (prob < maxProb[u]) continue;
            
            // Explore all neighbors
            for (auto& [v, edgeProb] : graph[u]) {
                double newProb = prob * edgeProb;
                
                // Relaxation step (maximize probability)
                if (newProb > maxProb[v]) {
                    maxProb[v] = newProb;
                    pq.push({newProb, v});
                }
            }
        }
        
        return 0.0; // No path exists
    }
};

// Example 4: Path With Minimum Effort
// LeetCode 1631: https://leetcode.com/problems/path-with-minimum-effort/
class MinimumEffortPath {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        
        // Directions: up, right, down, left
        vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // Initialize efforts
        vector<vector<int>> efforts(m, vector<int>(n, INT_MAX));
        efforts[0][0] = 0;
        
        // Min-heap priority queue: (effort, row, col)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, 0, 0});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            auto [effort, row, col] = pq.top();
            pq.pop();
            
            // Reached the destination
            if (row == m - 1 && col == n - 1) return effort;
            
            // Skip outdated entries
            if (effort > efforts[row][col]) continue;
            
            // Explore all directions
            for (auto& [dr, dc] : dirs) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                // Check if within bounds
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
                    // Calculate new effort
                    int newEffort = max(effort, abs(heights[newRow][newCol] - heights[row][col]));
                    
                    // Relaxation step
                    if (newEffort < efforts[newRow][newCol]) {
                        efforts[newRow][newCol] = newEffort;
                        pq.push({newEffort, newRow, newCol});
                    }
                }
            }
        }
        
        return -1; // Should not reach here if the grid is valid
    }
};

// Example 5: Swim in Rising Water
// LeetCode 778: https://leetcode.com/problems/swim-in-rising-water/
class SwimInWater {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Directions: up, right, down, left
        vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // Initialize times
        vector<vector<int>> times(n, vector<int>(n, INT_MAX));
        times[0][0] = grid[0][0];
        
        // Min-heap priority queue: (time, row, col)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({grid[0][0], 0, 0});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            auto [time, row, col] = pq.top();
            pq.pop();
            
            // Reached the destination
            if (row == n - 1 && col == n - 1) return time;
            
            // Skip outdated entries
            if (time > times[row][col]) continue;
            
            // Explore all directions
            for (auto& [dr, dc] : dirs) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                // Check if within bounds
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n) {
                    // Calculate new time
                    int newTime = max(time, grid[newRow][newCol]);
                    
                    // Relaxation step
                    if (newTime < times[newRow][newCol]) {
                        times[newRow][newCol] = newTime;
                        pq.push({newTime, newRow, newCol});
                    }
                }
            }
        }
        
        return -1; // Should not reach here if the grid is valid
    }
};

// Example 6: Minimum Obstacle Removal to Reach Corner
// LeetCode 2290: https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/
class MinimumObstacleRemoval {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Directions: up, right, down, left
        vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // Initialize removals
        vector<vector<int>> removals(m, vector<int>(n, INT_MAX));
        removals[0][0] = grid[0][0]; // Starting cell might have an obstacle
        
        // Min-heap priority queue: (removals, row, col)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({grid[0][0], 0, 0});
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            auto [removal, row, col] = pq.top();
            pq.pop();
            
            // Reached the destination
            if (row == m - 1 && col == n - 1) return removal;
            
            // Skip outdated entries
            if (removal > removals[row][col]) continue;
            
            // Explore all directions
            for (auto& [dr, dc] : dirs) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                // Check if within bounds
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
                    // Calculate new removal count
                    int newRemoval = removal + grid[newRow][newCol];
                    
                    // Relaxation step
                    if (newRemoval < removals[newRow][newCol]) {
                        removals[newRow][newCol] = newRemoval;
                        pq.push({newRemoval, newRow, newCol});
                    }
                }
            }
        }
        
        return -1; // Should not reach here if the grid is valid
    }
};

// Utility function to build weighted graph
vector<vector<pair<int, int>>> buildWeightedGraph(int n, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> graph(n);
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        graph[u].push_back({v, w});
    }
    return graph;
}

// Utility function to print distances
void printDistances(const vector<int>& dist, int src) {
    cout << "Shortest distances from source " << src << ":" << endl;
    for (int i = 0; i < dist.size(); i++) {
        if (i == src) continue;
        if (dist[i] == INT_MAX) {
            cout << "Node " << i << ": Unreachable" << endl;
        } else {
            cout << "Node " << i << ": " << dist[i] << endl;
        }
    }
}

// Utility function to print paths
void printPaths(const vector<vector<int>>& paths, int src) {
    cout << "Shortest paths from source " << src << ":" << endl;
    for (int i = 0; i < paths.size(); i++) {
        if (i == src || paths[i].empty()) continue;
        cout << "Path to " << i << ": ";
        for (int node : paths[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate Dijkstra's algorithm
int main() {
    // Example 1: Basic Dijkstra's Algorithm
    vector<vector<int>> edges1 = {
        {0, 1, 4}, {0, 2, 1}, {1, 3, 1}, {2, 1, 2}, {2, 3, 5}, {3, 4, 3}
    };
    
    cout << "Example 1: Basic Dijkstra's Algorithm" << endl;
    int n1 = 5;
    vector<vector<pair<int, int>>> graph1 = buildWeightedGraph(n1, edges1);
    
    cout << "Graph:" << endl;
    for (int i = 0; i < graph1.size(); i++) {
        cout << "Node " << i << " -> ";
        for (auto& [v, w] : graph1[i]) {
            cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
    
    DijkstraAlgorithm solution1;
    vector<int> distances = solution1.shortestPath(n1, graph1, 0);
    
    printDistances(distances, 0);
    
    // With paths
    auto [dist, paths] = solution1.shortestPathWithRoutes(n1, graph1, 0);
    printPaths(paths, 0);
    
    // Example 2: Network Delay Time
    vector<vector<int>> times = {
        {2, 1, 1}, {2, 3, 1}, {3, 4, 1}
    };
    
    cout << "\nExample 2: Network Delay Time" << endl;
    cout << "Network:" << endl;
    for (const auto& time : times) {
        cout << "From " << time[0] << " to " << time[1] << " with time " << time[2] << endl;
    }
    
    NetworkDelayTime solution2;
    int minTime = solution2.networkDelayTime(times, 4, 2);
    
    cout << "Minimum time to reach all nodes: " << minTime << endl;
    
    // Example 3: Path with Maximum Probability
    vector<vector<int>> edges3 = {
        {0, 1}, {1, 2}, {0, 2}
    };
    vector<double> succProb = {0.5, 0.5, 0.2};
    
    cout << "\nExample 3: Path with Maximum Probability" << endl;
    cout << "Graph:" << endl;
    for (int i = 0; i < edges3.size(); i++) {
        cout << "Edge from " << edges3[i][0] << " to " << edges3[i][1] 
             << " with probability " << succProb[i] << endl;
    }
    
    MaxProbability solution3;
    double maxProb = solution3.maxProbability(3, edges3, succProb, 0, 2);
    
    cout << "Maximum probability from 0 to 2: " << maxProb << endl;
    
    // Example 4: Path With Minimum Effort
    vector<vector<int>> heights = {
        {1, 2, 2}, {3, 8, 2}, {5, 3, 5}
    };
    
    cout << "\nExample 4: Path With Minimum Effort" << endl;
    cout << "Heights grid:" << endl;
    for (const auto& row : heights) {
        for (int h : row) {
            cout << h << " ";
        }
        cout << endl;
    }
    
    MinimumEffortPath solution4;
    int minEffort = solution4.minimumEffortPath(heights);
    
    cout << "Minimum effort path: " << minEffort << endl;
    
    // Example 5: Swim in Rising Water
    vector<vector<int>> grid = {
        {0, 2}, {1, 3}
    };
    
    cout << "\nExample 5: Swim in Rising Water" << endl;
    cout << "Grid:" << endl;
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
    SwimInWater solution5;
    int leastTime = solution5.swimInWater(grid);
    
    cout << "Least time to swim: " << leastTime << endl;
    
    // Example 6: Minimum Obstacle Removal
    vector<vector<int>> obstacles = {
        {0, 1, 1}, {1, 1, 0}, {1, 0, 0}
    };
    
    cout << "\nExample 6: Minimum Obstacle Removal" << endl;
    cout << "Grid (1 = obstacle, 0 = empty):" << endl;
    for (const auto& row : obstacles) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
    MinimumObstacleRemoval solution6;
    int minRemoval = solution6.minimumObstacles(obstacles);
    
    cout << "Minimum obstacles to remove: " << minRemoval << endl;
    
    return 0;
}
