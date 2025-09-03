# Graph Traversal Patterns (DFS & BFS)

Graph traversal patterns are essential techniques for navigating through a graph data structure, visiting all nodes and edges systematically. These patterns are fundamental for solving problems involving connected components, paths, cycles, and other graph-based scenarios.

## Patterns in this Category

### Pattern 19: Graph DFS - Connected Components / Island Counting
- **Description**: Use depth-first search to identify connected components in a graph or count islands in a 2D grid.
- **When to use**: Finding separate groups of connected nodes, counting regions in a grid, or identifying isolated components.
- **Files**: [01_connected_components.cpp](./01_connected_components.cpp)
- **LeetCode Problems**: Number of Islands, Surrounded Regions, Number of Provinces

### Pattern 20: Graph BFS - Connected Components / Island Counting
- **Description**: Use breadth-first search to identify connected components or count islands, particularly useful when distance metrics are important.
- **When to use**: Finding shortest paths in unweighted graphs, level-by-level exploration, or when distance from a source is needed.
- **Files**: [02_bfs_connected_components.cpp](./02_bfs_connected_components.cpp)
- **LeetCode Problems**: Rotting Oranges, 01 Matrix, Shortest Path in Binary Matrix

### Pattern 21: Graph DFS - Cycle Detection (Directed Graph)
- **Description**: Use depth-first search with coloring or visited states to detect cycles in directed graphs.
- **When to use**: Checking if a graph has cycles, determining if a directed graph is a DAG, or finding cyclic dependencies.
- **Files**: [03_directed_cycle_detection.cpp](./03_directed_cycle_detection.cpp)
- **LeetCode Problems**: Course Schedule, Find Eventual Safe States

### Pattern 22: Graph BFS - Topological Sort (Kahn's Algorithm)
- **Description**: Use breadth-first search to find a valid ordering of vertices such that for every directed edge (u,v), vertex u comes before v in the ordering.
- **When to use**: Task scheduling, determining a valid sequence of dependent operations, or ordering with prerequisites.
- **Files**: [04_topological_sort.cpp](./04_topological_sort.cpp)
- **LeetCode Problems**: Course Schedule II, Alien Dictionary, Parallel Courses

### Pattern 23: Graph - Deep Copy / Cloning
- **Description**: Create a complete copy of a graph with the same structure but different memory locations.
- **When to use**: When you need to duplicate a graph without modifying the original, or for creating isolated instances of a graph.
- **Files**: [05_graph_cloning.cpp](./05_graph_cloning.cpp)
- **LeetCode Problems**: Clone Graph

### Pattern 24: Graph - Shortest Path (Dijkstra's Algorithm)
- **Description**: Find the shortest path between nodes in a weighted graph using Dijkstra's algorithm.
- **When to use**: Finding the shortest path in graphs with non-negative weights, optimizing routes, or minimizing cost paths.
- **Files**: [06_dijkstra_algorithm.cpp](./06_dijkstra_algorithm.cpp)
- **LeetCode Problems**: Network Delay Time, Path with Maximum Probability, Path with Minimum Effort

### Pattern 25: Graph - Shortest Path (Bellman-Ford / BFS+K)
- **Description**: Find the shortest path in a graph with negative edge weights or with constraints on the number of edges.
- **When to use**: When negative edge weights are present, or when there's a limit on the number of edges in the path.
- **Files**: [07_bellman_ford_algorithm.cpp](./07_bellman_ford_algorithm.cpp)
- **LeetCode Problems**: Cheapest Flights Within K Stops

### Pattern 26: Graph - Union-Find (Disjoint Set Union - DSU)
- **Description**: Track a set of elements partitioned into disjoint subsets, with operations to merge sets and check if elements are in the same set.
- **When to use**: Detecting cycles in undirected graphs, finding connected components, or solving dynamic connectivity problems.
- **Files**: [08_union_find.cpp](./08_union_find.cpp)
- **LeetCode Problems**: Number of Islands II, Redundant Connection, Accounts Merge

## Graph Representation

Graphs can be represented in several ways:

### Adjacency Matrix
- A 2D array where matrix[i][j] = 1 if there's an edge from vertex i to vertex j, otherwise 0.
- Space Complexity: O(V²), where V is the number of vertices.
- Good for dense graphs.

```cpp
vector<vector<int>> graph(n, vector<int>(n, 0)); // For an n-vertex graph
```

### Adjacency List
- An array of lists, where each list contains the neighbors of the corresponding vertex.
- Space Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
- Good for sparse graphs.

```cpp
vector<vector<int>> graph(n); // For an n-vertex graph
```

### Edge List
- A list of all edges in the graph.
- Space Complexity: O(E), where E is the number of edges.
- Good for algorithms that process edges, like Kruskal's algorithm.

```cpp
vector<pair<int, int>> edges; // For storing (u, v) edges
```

## Time and Space Complexity

- **DFS**: O(V + E) time, O(V) space for recursion stack or visited array
- **BFS**: O(V + E) time, O(V) space for queue and visited array
- **Dijkstra's Algorithm**: O((V + E) log V) time with a priority queue
- **Bellman-Ford Algorithm**: O(V × E) time
- **Union-Find**: O(α(n)) time per operation, where α is the inverse Ackermann function (nearly constant)

## Common Graph Problems and Solutions

1. **Connectivity**: Use DFS or BFS to determine if all nodes are reachable from a given node.
2. **Shortest Path**: Use BFS for unweighted graphs, Dijkstra's for weighted graphs with positive weights.
3. **Minimum Spanning Tree**: Use Kruskal's or Prim's algorithm.
4. **Cycle Detection**: Use DFS with color marking or Union-Find for undirected graphs.
5. **Topological Sort**: Use Kahn's algorithm (BFS) or DFS with finish times.
6. **Strongly Connected Components**: Use Kosaraju's or Tarjan's algorithm.

## Common Tricks and Optimizations

- Use bitwise operations for small graphs to reduce space complexity.
- For grid problems, use direction arrays to simplify traversal code:
  ```cpp
  int dx[] = {-1, 0, 1, 0};
  int dy[] = {0, 1, 0, -1};
  ```
- Consider using iterative DFS instead of recursive DFS for very deep graphs to avoid stack overflow.
