/**
 * Pattern: Graph - Shortest Path (Bellman-Ford / BFS+K)
 * 
 * Description:
 * The Bellman-Ford algorithm finds the shortest paths from a source vertex to all other 
 * vertices in a weighted graph, even when negative edge weights are present. Unlike Dijkstra's 
 * algorithm, Bellman-Ford can handle graphs with negative weight edges and can detect negative 
 * weight cycles. For graphs with constraints on the number of edges allowed in a path, a modified 
 * BFS approach (BFS+K) can be used.
 * 
 * Time Complexity: 
 * - Bellman-Ford: O(V × E) where V is vertices and E is edges
 * - BFS+K: O(E × K) where K is the maximum number of edges allowed
 * 
 * Space Complexity: O(V) for distance array
 * 
 * When to use:
 * - Finding shortest paths when negative edge weights are present
 * - Detecting negative weight cycles in a graph
 * - When there's a constraint on the maximum number of edges in a path
 * - As a fallback when Dijkstra's algorithm cannot be used due to negative weights
 * 
 * LeetCode Problems:
 * - 787. Cheapest Flights Within K Stops
 * - 743. Network Delay Time (can also be solved with Bellman-Ford)
 * - 1514. Path with Maximum Probability (modified approach)
 * - 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Example 1: Basic Bellman-Ford Algorithm Implementation
class BellmanFord {
public:
    // Graph represented as a list of edges (u, v, weight)
    vector<int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        // Initialize distances with infinity
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        
        // Relax all edges |V| - 1 times
        for (int i = 0; i < n - 1; i++) {
            for (const auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                
                // Skip if source vertex is unreachable
                if (dist[u] == INT_MAX) continue;
                
                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        // Check for negative weight cycles
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            // If we can further optimize, then there's a negative cycle
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                // Return a vector of -1s to indicate negative cycle
                return vector<int>(n, -1);
            }
        }
        
        return dist;
    }
    
    // Variant: Find path along with distances
    pair<vector<int>, vector<vector<int>>> shortestPathWithRoutes(
        int n, vector<vector<int>>& edges, int src) {
        
        // Initialize distances and parent pointers
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        dist[src] = 0;
        
        // Relax all edges |V| - 1 times
        for (int i = 0; i < n - 1; i++) {
            for (const auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                
                // Skip if source vertex is unreachable
                if (dist[u] == INT_MAX) continue;
                
                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
        
        // Check for negative weight cycles
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            // If we can further optimize, then there's a negative cycle
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                // Return empty paths to indicate negative cycle
                return {vector<int>(n, -1), {}};
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

// Example 2: Cheapest Flights Within K Stops (BFS+K approach)
// LeetCode 787: https://leetcode.com/problems/cheapest-flights-within-k-stops/
class CheapestFlights {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Initialize distances
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        
        // Run k+1 iterations of Bellman-Ford
        for (int i = 0; i <= k; i++) {
            // Create a copy of distances to avoid using updated values in the same iteration
            vector<int> temp = dist;
            
            for (const auto& flight : flights) {
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];
                
                // Skip if source is unreachable
                if (dist[from] == INT_MAX) continue;
                
                // Relaxation step using old distance values
                temp[to] = min(temp[to], dist[from] + price);
            }
            
            // Update distances for the next iteration
            dist = temp;
        }
        
        // Return the final distance to destination, or -1 if unreachable
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
    
    // BFS+K approach (alternative implementation)
    int findCheapestPriceBFS(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Build adjacency list: [to, price]
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& flight : flights) {
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
        
        // Minimum price to reach each node
        vector<int> minPrice(n, INT_MAX);
        
        // BFS queue: [node, price, stops]
        queue<vector<int>> q;
        q.push({src, 0, 0}); // Start with source node, price 0, and 0 stops
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            int node = curr[0];
            int price = curr[1];
            int stops = curr[2];
            
            // Reached destination
            if (node == dst) {
                return price;
            }
            
            // Exceeded stops limit
            if (stops > k) {
                continue;
            }
            
            // Try all outgoing flights
            for (const auto& [nextNode, cost] : graph[node]) {
                int newPrice = price + cost;
                
                // Skip if we already found a cheaper way with fewer or equal stops
                if (newPrice >= minPrice[nextNode]) {
                    continue;
                }
                
                minPrice[nextNode] = newPrice;
                q.push({nextNode, newPrice, stops + 1});
            }
        }
        
        return -1; // No valid path found
    }
};

// Example 3: Network Delay Time using Bellman-Ford
// LeetCode 743: https://leetcode.com/problems/network-delay-time/
class NetworkDelayTimeBF {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Adjust for 1-indexed nodes
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        // Relax all edges n-1 times
        for (int i = 0; i < n - 1; i++) {
            for (const auto& time : times) {
                int u = time[0];
                int v = time[1];
                int w = time[2];
                
                // Skip if source is unreachable
                if (dist[u] == INT_MAX) continue;
                
                // Relaxation step
                dist[v] = min(dist[v], dist[u] + w);
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

// Example 4: Find the City With the Smallest Number of Neighbors
// LeetCode 1334: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
class FindCity {
public:
    // Using Floyd-Warshall algorithm (easier for all-pairs shortest paths)
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Initialize distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        
        // Set diagonal to 0
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        
        // Initialize with edge weights
        for (const auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            
            // Undirected graph
            dist[from][to] = weight;
            dist[to][from] = weight;
        }
        
        // Floyd-Warshall algorithm
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // Skip if any distance is infinity
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
                    
                    // Update if path through k is shorter
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        // Find city with fewest reachable cities
        int minReachable = n;
        int resultCity = -1;
        
        for (int i = 0; i < n; i++) {
            int reachable = 0;
            
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    reachable++;
                }
            }
            
            // Update result if fewer or equal reachable cities (prefer higher city number)
            if (reachable <= minReachable) {
                minReachable = reachable;
                resultCity = i;
            }
        }
        
        return resultCity;
    }
    
    // Using Bellman-Ford for each city (alternative approach)
    int findTheCityBF(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Convert to edge list format for Bellman-Ford
        vector<vector<int>> edgeList;
        for (const auto& edge : edges) {
            // Undirected graph
            edgeList.push_back({edge[0], edge[1], edge[2]});
            edgeList.push_back({edge[1], edge[0], edge[2]});
        }
        
        int minReachable = n;
        int resultCity = -1;
        
        // Run Bellman-Ford from each city
        for (int city = 0; city < n; city++) {
            // Initialize distances
            vector<int> dist(n, INT_MAX);
            dist[city] = 0;
            
            // Relax edges n-1 times
            for (int i = 0; i < n - 1; i++) {
                for (const auto& edge : edgeList) {
                    int u = edge[0];
                    int v = edge[1];
                    int w = edge[2];
                    
                    // Skip if source is unreachable
                    if (dist[u] == INT_MAX) continue;
                    
                    // Relaxation step
                    dist[v] = min(dist[v], dist[u] + w);
                }
            }
            
            // Count reachable cities within threshold
            int reachable = 0;
            for (int j = 0; j < n; j++) {
                if (city != j && dist[j] <= distanceThreshold) {
                    reachable++;
                }
            }
            
            // Update result if fewer or equal reachable cities (prefer higher city number)
            if (reachable <= minReachable) {
                minReachable = reachable;
                resultCity = city;
            }
        }
        
        return resultCity;
    }
};

// Example 5: Path with Maximum Probability using Modified Bellman-Ford
// LeetCode 1514: https://leetcode.com/problems/path-with-maximum-probability/
class MaxProbabilityBF {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Initialize probabilities
        vector<double> prob(n, 0.0);
        prob[start] = 1.0;
        
        // Run n-1 iterations of modified Bellman-Ford
        for (int i = 0; i < n - 1; i++) {
            bool updated = false;
            
            for (int j = 0; j < edges.size(); j++) {
                int u = edges[j][0];
                int v = edges[j][1];
                double p = succProb[j];
                
                // Update probability if we can get a higher value (maximize instead of minimize)
                if (prob[u] * p > prob[v]) {
                    prob[v] = prob[u] * p;
                    updated = true;
                }
                
                // Undirected graph, check the other way
                if (prob[v] * p > prob[u]) {
                    prob[u] = prob[v] * p;
                    updated = true;
                }
            }
            
            // Early termination if no updates
            if (!updated) break;
        }
        
        return prob[end];
    }
};

// Example 6: SPFA (Shortest Path Faster Algorithm) - An optimization of Bellman-Ford
class SPFA {
public:
    vector<int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            graph[u].push_back({v, w});
        }
        
        // Initialize distances
        vector<int> dist(n, INT_MAX);
        vector<bool> inQueue(n, false);
        dist[src] = 0;
        
        // Queue for processing nodes
        queue<int> q;
        q.push(src);
        inQueue[src] = true;
        
        // Count relaxations for each node to detect negative cycles
        vector<int> relaxCount(n, 0);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            
            // Process all neighbors
            for (const auto& [v, weight] : graph[u]) {
                // Skip if source is unreachable
                if (dist[u] == INT_MAX) continue;
                
                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    
                    // If not in queue, add it
                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = true;
                        
                        // Increment relaxation count
                        relaxCount[v]++;
                        
                        // If relaxed n times, there's a negative cycle
                        if (relaxCount[v] >= n) {
                            return vector<int>(n, -1);
                        }
                    }
                }
            }
        }
        
        return dist;
    }
};

// Utility function to build edge list
vector<vector<int>> buildEdgeList(int n, vector<vector<int>>& edges) {
    return edges;
}

// Utility function to print distances
void printDistances(const vector<int>& dist, int src) {
    cout << "Shortest distances from source " << src << ":" << endl;
    for (int i = 0; i < dist.size(); i++) {
        if (i == src) continue;
        if (dist[i] == INT_MAX) {
            cout << "Node " << i << ": Unreachable" << endl;
        } else if (dist[i] == -1) {
            cout << "Negative cycle detected" << endl;
            break;
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

// Main function to demonstrate Bellman-Ford and related algorithms
int main() {
    // Example 1: Basic Bellman-Ford Algorithm
    vector<vector<int>> edges1 = {
        {0, 1, 4}, {0, 2, 1}, {1, 3, 1}, {2, 1, 2}, {2, 3, 5}, {3, 4, 3}
    };
    
    cout << "Example 1: Basic Bellman-Ford Algorithm" << endl;
    int n1 = 5;
    
    cout << "Graph (edge list):" << endl;
    for (const auto& edge : edges1) {
        cout << "Edge from " << edge[0] << " to " << edge[1] << " with weight " << edge[2] << endl;
    }
    
    BellmanFord solution1;
    vector<int> distances = solution1.shortestPath(n1, edges1, 0);
    
    printDistances(distances, 0);
    
    // With paths
    auto [dist, paths] = solution1.shortestPathWithRoutes(n1, edges1, 0);
    printPaths(paths, 0);
    
    // Example 2: Cheapest Flights Within K Stops
    vector<vector<int>> flights = {
        {0, 1, 100}, {1, 2, 100}, {0, 2, 500}
    };
    
    cout << "\nExample 2: Cheapest Flights Within K Stops" << endl;
    cout << "Flights:" << endl;
    for (const auto& flight : flights) {
        cout << "From " << flight[0] << " to " << flight[1] << " with price " << flight[2] << endl;
    }
    
    CheapestFlights solution2;
    int cheapestPrice = solution2.findCheapestPrice(3, flights, 0, 2, 1);
    
    cout << "Cheapest price from 0 to 2 with at most 1 stop: " << cheapestPrice << endl;
    
    // Example 3: Network Delay Time using Bellman-Ford
    vector<vector<int>> times = {
        {2, 1, 1}, {2, 3, 1}, {3, 4, 1}
    };
    
    cout << "\nExample 3: Network Delay Time using Bellman-Ford" << endl;
    cout << "Network:" << endl;
    for (const auto& time : times) {
        cout << "From " << time[0] << " to " << time[1] << " with time " << time[2] << endl;
    }
    
    NetworkDelayTimeBF solution3;
    int minTime = solution3.networkDelayTime(times, 4, 2);
    
    cout << "Minimum time to reach all nodes: " << minTime << endl;
    
    // Example 4: Find the City With the Smallest Number of Neighbors
    vector<vector<int>> edges4 = {
        {0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}
    };
    
    cout << "\nExample 4: Find the City With the Smallest Number of Neighbors" << endl;
    cout << "Graph:" << endl;
    for (const auto& edge : edges4) {
        cout << "Edge between " << edge[0] << " and " << edge[1] << " with distance " << edge[2] << endl;
    }
    
    FindCity solution4;
    int resultCity = solution4.findTheCity(4, edges4, 4);
    
    cout << "City with fewest neighbors within distance 4: " << resultCity << endl;
    
    // Example 5: Path with Maximum Probability using Modified Bellman-Ford
    vector<vector<int>> edges5 = {
        {0, 1}, {1, 2}, {0, 2}
    };
    vector<double> succProb = {0.5, 0.5, 0.2};
    
    cout << "\nExample 5: Path with Maximum Probability" << endl;
    cout << "Graph:" << endl;
    for (int i = 0; i < edges5.size(); i++) {
        cout << "Edge from " << edges5[i][0] << " to " << edges5[i][1] 
             << " with probability " << succProb[i] << endl;
    }
    
    MaxProbabilityBF solution5;
    double maxProb = solution5.maxProbability(3, edges5, succProb, 0, 2);
    
    cout << "Maximum probability from 0 to 2: " << maxProb << endl;
    
    // Example 6: SPFA (Shortest Path Faster Algorithm)
    vector<vector<int>> edges6 = {
        {0, 1, 4}, {0, 2, 1}, {1, 3, 1}, {2, 1, 2}, {2, 3, 5}, {3, 4, 3}
    };
    
    cout << "\nExample 6: SPFA (Shortest Path Faster Algorithm)" << endl;
    cout << "Graph:" << endl;
    for (const auto& edge : edges6) {
        cout << "Edge from " << edge[0] << " to " << edge[1] << " with weight " << edge[2] << endl;
    }
    
    SPFA solution6;
    vector<int> distancesSPFA = solution6.shortestPath(5, edges6, 0);
    
    printDistances(distancesSPFA, 0);
    
    // Example with negative cycle
    vector<vector<int>> edgesNegCycle = {
        {0, 1, 1}, {1, 2, 2}, {2, 0, -4}
    };
    
    cout << "\nExample with Negative Cycle" << endl;
    cout << "Graph:" << endl;
    for (const auto& edge : edgesNegCycle) {
        cout << "Edge from " << edge[0] << " to " << edge[1] << " with weight " << edge[2] << endl;
    }
    
    vector<int> distancesNegCycle = solution1.shortestPath(3, edgesNegCycle, 0);
    
    if (distancesNegCycle[0] == -1) {
        cout << "Negative cycle detected" << endl;
    } else {
        printDistances(distancesNegCycle, 0);
    }
    
    return 0;
}
