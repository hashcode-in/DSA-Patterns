/**
 * Pattern: Graph - Union-Find (Disjoint Set Union - DSU)
 * 
 * Description:
 * The Union-Find (or Disjoint Set Union) data structure is used to keep track of a set of elements 
 * partitioned into a number of disjoint (non-overlapping) subsets. It provides near-constant-time 
 * operations to add new sets, merge existing sets, and determine whether elements are in the same set.
 * Optimizations like path compression and union by rank/size make operations very efficient.
 * 
 * Time Complexity:
 * - Find: O(α(n)) amortized
 * - Union: O(α(n)) amortized
 * Where α(n) is the inverse Ackermann function, which grows extremely slowly and is < 5 for any practical n.
 * 
 * Space Complexity: O(n) for storing parent and rank/size arrays
 * 
 * When to use:
 * - Tracking connected components in an undirected graph
 * - Detecting cycles in an undirected graph
 * - Finding Minimum Spanning Trees (Kruskal's algorithm)
 * - Dynamic connectivity problems
 * - Networks, social networks (friend circles)
 * - Image processing (connected components)
 * 
 * LeetCode Problems:
 * - 547. Number of Provinces
 * - 684. Redundant Connection
 * - 721. Accounts Merge
 * - 947. Most Stones Removed with Same Row or Column
 * - 1319. Number of Operations to Make Network Connected
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Example 1: Basic Union-Find Implementation (Path Compression + Union by Rank)
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int count;  // Number of connected components

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        count = n;
        
        // Initialize: each element is its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find root of the set with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    // Union by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank: attach smaller rank tree under root of higher rank tree
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            // If ranks are same, make one as root and increment its rank
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        count--;  // Decrement the number of connected components
    }
    
    // Check if two elements are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    // Return the number of connected components
    int getCount() const {
        return count;
    }
};

// Example 2: Union-Find with Size (Union by Size)
class UnionFindBySize {
private:
    vector<int> parent;
    vector<int> size;
    int count;  // Number of connected components

public:
    UnionFindBySize(int n) {
        parent.resize(n);
        size.resize(n, 1);  // Initial size of each set is 1
        count = n;
        
        // Initialize: each element is its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find root of the set with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    // Union by size: attach smaller size tree under root of larger size tree
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Make smaller tree point to larger tree
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        
        count--;  // Decrement the number of connected components
    }
    
    // Check if two elements are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    // Return the number of connected components
    int getCount() const {
        return count;
    }
    
    // Get the size of the set containing element x
    int getSize(int x) {
        return size[find(x)];
    }
};

// Example 3: Number of Provinces
// LeetCode 547: https://leetcode.com/problems/number-of-provinces/
class NumberOfProvinces {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);
        
        // Connect cities based on the adjacency matrix
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    uf.unionSets(i, j);
                }
            }
        }
        
        return uf.getCount();
    }
};

// Example 4: Redundant Connection
// LeetCode 684: https://leetcode.com/problems/redundant-connection/
class RedundantConnection {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n + 1);  // 1-indexed
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            // If already connected, this is a redundant edge
            if (uf.connected(u, v)) {
                return edge;
            }
            
            uf.unionSets(u, v);
        }
        
        return {};  // Should not reach here if problem is valid
    }
};

// Example 5: Accounts Merge
// LeetCode 721: https://leetcode.com/problems/accounts-merge/
class AccountsMerge {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        UnionFind uf(n);
        
        // Map each email to the account index
        unordered_map<string, int> emailToAccount;
        
        // Connect accounts with shared emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                
                // If email already belongs to an account, union them
                if (emailToAccount.find(email) != emailToAccount.end()) {
                    uf.unionSets(i, emailToAccount[email]);
                } else {
                    emailToAccount[email] = i;
                }
            }
        }
        
        // Group emails by representative (root) account
        unordered_map<int, vector<string>> merged;
        for (const auto& [email, account] : emailToAccount) {
            int root = uf.find(account);
            merged[root].push_back(email);
        }
        
        // Format result
        vector<vector<string>> result;
        for (const auto& [root, emails] : merged) {
            vector<string> account;
            account.push_back(accounts[root][0]);  // Name
            
            // Sort emails
            vector<string> sortedEmails = emails;
            sort(sortedEmails.begin(), sortedEmails.end());
            
            // Add emails to account
            account.insert(account.end(), sortedEmails.begin(), sortedEmails.end());
            result.push_back(account);
        }
        
        return result;
    }
};

// Example 6: Most Stones Removed with Same Row or Column
// LeetCode 947: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/
class MostStonesRemoved {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        UnionFind uf(n);
        
        // Connect stones sharing the same row or column
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // If stones share a row or column, union them
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    uf.unionSets(i, j);
                }
            }
        }
        
        // Number of stones that can be removed = total stones - number of connected components
        return n - uf.getCount();
    }
    
    // Alternative approach with row and column mapping
    int removeStones2(vector<vector<int>>& stones) {
        int n = stones.size();
        
        // Map to store row and column indices
        unordered_map<int, int> rowMap;
        unordered_map<int, int> colMap;
        
        UnionFind uf(n);
        
        for (int i = 0; i < n; i++) {
            int row = stones[i][0];
            int col = stones[i][1] + 10001;  // Offset to avoid collision with row values
            
            // Connect stones with the same row
            if (rowMap.count(row)) {
                uf.unionSets(i, rowMap[row]);
            } else {
                rowMap[row] = i;
            }
            
            // Connect stones with the same column
            if (colMap.count(col)) {
                uf.unionSets(i, colMap[col]);
            } else {
                colMap[col] = i;
            }
        }
        
        return n - uf.getCount();
    }
};

// Example 7: Number of Operations to Make Network Connected
// LeetCode 1319: https://leetcode.com/problems/number-of-operations-to-make-network-connected/
class MakeNetworkConnected {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // We need at least n-1 cables to connect n computers
        if (connections.size() < n - 1) {
            return -1;
        }
        
        UnionFind uf(n);
        
        // Connect computers based on existing cables
        for (const auto& connection : connections) {
            uf.unionSets(connection[0], connection[1]);
        }
        
        // Number of operations needed = number of connected components - 1
        return uf.getCount() - 1;
    }
};

// Example 8: Number of Islands II (Online Query)
// LeetCode 305: https://leetcode.com/problems/number-of-islands-ii/
class NumberOfIslands2 {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> result;
        UnionFind uf(m * n);
        vector<vector<int>> grid(m, vector<int>(n, 0));  // 0: water, 1: land
        int count = 0;  // Current number of islands
        
        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        for (const auto& position : positions) {
            int row = position[0];
            int col = position[1];
            int index = row * n + col;
            
            // Skip if already land
            if (grid[row][col] == 1) {
                result.push_back(count);
                continue;
            }
            
            // Convert to land
            grid[row][col] = 1;
            count++;
            
            // Check adjacent cells
            for (const auto& [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                int newIndex = newRow * n + newCol;
                
                // Skip if out of bounds or water
                if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n || grid[newRow][newCol] == 0) {
                    continue;
                }
                
                // If adjacent cell is land and not already connected, union them
                if (!uf.connected(index, newIndex)) {
                    uf.unionSets(index, newIndex);
                    count--;
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};

// Example 9: Detect Cycle in an Undirected Graph
class CycleDetection {
public:
    bool hasCycle(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            // If already connected, this edge forms a cycle
            if (uf.connected(u, v)) {
                return true;
            }
            
            uf.unionSets(u, v);
        }
        
        return false;
    }
};

// Utility function to print account details
void printAccounts(const vector<vector<string>>& accounts) {
    for (const auto& account : accounts) {
        cout << account[0] << ": ";
        for (int i = 1; i < account.size(); i++) {
            cout << account[i];
            if (i < account.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Main function to demonstrate Union-Find pattern
int main() {
    // Example 1: Basic Union-Find
    cout << "Example 1: Basic Union-Find" << endl;
    UnionFind uf(5);
    
    cout << "Initial components: " << uf.getCount() << endl;
    
    uf.unionSets(0, 1);
    uf.unionSets(2, 3);
    cout << "After union(0,1) and union(2,3): " << uf.getCount() << " components" << endl;
    
    uf.unionSets(1, 3);
    cout << "After union(1,3): " << uf.getCount() << " components" << endl;
    
    cout << "Are 0 and 3 connected? " << (uf.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "Are 0 and 4 connected? " << (uf.connected(0, 4) ? "Yes" : "No") << endl;
    
    // Example 2: Union-Find by Size
    cout << "\nExample 2: Union-Find by Size" << endl;
    UnionFindBySize ufSize(5);
    
    ufSize.unionSets(0, 1);
    ufSize.unionSets(2, 3);
    ufSize.unionSets(1, 3);
    
    cout << "Size of set containing 0: " << ufSize.getSize(0) << endl;
    cout << "Size of set containing 4: " << ufSize.getSize(4) << endl;
    
    // Example 3: Number of Provinces
    cout << "\nExample 3: Number of Provinces" << endl;
    vector<vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    
    cout << "Adjacency Matrix:" << endl;
    for (const auto& row : isConnected) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    NumberOfProvinces solution3;
    int provinces = solution3.findCircleNum(isConnected);
    cout << "Number of provinces: " << provinces << endl;
    
    // Example 4: Redundant Connection
    cout << "\nExample 4: Redundant Connection" << endl;
    vector<vector<int>> edges = {
        {1, 2}, {1, 3}, {2, 3}
    };
    
    cout << "Edges:" << endl;
    for (const auto& edge : edges) {
        cout << edge[0] << " -- " << edge[1] << endl;
    }
    
    RedundantConnection solution4;
    vector<int> redundantEdge = solution4.findRedundantConnection(edges);
    
    if (!redundantEdge.empty()) {
        cout << "Redundant edge: " << redundantEdge[0] << " -- " << redundantEdge[1] << endl;
    }
    
    // Example 5: Accounts Merge
    cout << "\nExample 5: Accounts Merge" << endl;
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };
    
    cout << "Original accounts:" << endl;
    printAccounts(accounts);
    
    AccountsMerge solution5;
    vector<vector<string>> mergedAccounts = solution5.accountsMerge(accounts);
    
    cout << "Merged accounts:" << endl;
    printAccounts(mergedAccounts);
    
    // Example 6: Most Stones Removed with Same Row or Column
    cout << "\nExample 6: Most Stones Removed" << endl;
    vector<vector<int>> stones = {
        {0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}
    };
    
    cout << "Stone positions:" << endl;
    for (const auto& stone : stones) {
        cout << "(" << stone[0] << ", " << stone[1] << ") ";
    }
    cout << endl;
    
    MostStonesRemoved solution6;
    int removableStones = solution6.removeStones(stones);
    cout << "Maximum stones that can be removed: " << removableStones << endl;
    
    // Example 7: Number of Operations to Make Network Connected
    cout << "\nExample 7: Make Network Connected" << endl;
    vector<vector<int>> connections = {
        {0, 1}, {0, 2}, {1, 2}, {3, 4}
    };
    
    cout << "Initial connections:" << endl;
    for (const auto& connection : connections) {
        cout << connection[0] << " -- " << connection[1] << endl;
    }
    
    MakeNetworkConnected solution7;
    int operations = solution7.makeConnected(5, connections);
    cout << "Operations needed to connect all computers: " << operations << endl;
    
    // Example 8: Number of Islands II
    cout << "\nExample 8: Number of Islands II" << endl;
    vector<vector<int>> positions = {
        {0, 0}, {0, 1}, {1, 2}, {2, 1}
    };
    
    cout << "Adding land at positions:" << endl;
    for (const auto& pos : positions) {
        cout << "(" << pos[0] << ", " << pos[1] << ") ";
    }
    cout << endl;
    
    NumberOfIslands2 solution8;
    vector<int> islandCounts = solution8.numIslands2(3, 3, positions);
    
    cout << "Island counts after each addition: ";
    for (int count : islandCounts) {
        cout << count << " ";
    }
    cout << endl;
    
    // Example 9: Detect Cycle in an Undirected Graph
    cout << "\nExample 9: Cycle Detection" << endl;
    vector<vector<int>> graphEdges1 = {
        {0, 1}, {1, 2}, {2, 0}
    };
    
    cout << "Graph 1 edges:" << endl;
    for (const auto& edge : graphEdges1) {
        cout << edge[0] << " -- " << edge[1] << endl;
    }
    
    CycleDetection solution9;
    bool hasCycle1 = solution9.hasCycle(3, graphEdges1);
    cout << "Graph 1 has cycle: " << (hasCycle1 ? "Yes" : "No") << endl;
    
    vector<vector<int>> graphEdges2 = {
        {0, 1}, {1, 2}
    };
    
    cout << "\nGraph 2 edges:" << endl;
    for (const auto& edge : graphEdges2) {
        cout << edge[0] << " -- " << edge[1] << endl;
    }
    
    bool hasCycle2 = solution9.hasCycle(3, graphEdges2);
    cout << "Graph 2 has cycle: " << (hasCycle2 ? "Yes" : "No") << endl;
    
    return 0;
}
