/**
 * Pattern: Graph BFS - Topological Sort (Kahn's Algorithm)
 * 
 * Description:
 * Topological sorting is a linear ordering of vertices in a directed acyclic graph (DAG) 
 * such that for every directed edge (u, v), vertex u comes before v in the ordering. 
 * Kahn's algorithm uses BFS to find a topological ordering by repeatedly removing 
 * nodes with no incoming edges.
 * 
 * Time Complexity: O(V + E), where:
 * - V is the number of vertices
 * - E is the number of edges
 * 
 * Space Complexity: O(V) for queue and indegree array
 * 
 * When to use:
 * - Task scheduling with dependencies
 * - Course prerequisites sequencing
 * - Build system dependency resolution
 * - Package installation ordering
 * - Any scenario where items must be processed in a specific order
 * 
 * LeetCode Problems:
 * - 207. Course Schedule
 * - 210. Course Schedule II
 * - 269. Alien Dictionary
 * - 1136. Parallel Courses
 * - 2115. Find All Possible Recipes from Given Supplies
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Example 1: Basic Topological Sort (Kahn's Algorithm)
class TopologicalSort {
public:
    vector<int> topoSort(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> inDegree(n, 0);
        vector<int> result;
        
        // Calculate in-degree for each vertex
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                inDegree[v]++;
            }
        }
        
        // Enqueue vertices with in-degree 0
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Process vertices in topological order
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            // Reduce in-degree of adjacent vertices
            for (int v : graph[u]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Check if topological sort is possible
        if (result.size() != n) {
            // Graph has at least one cycle, return empty vector
            return {};
        }
        
        return result;
    }
};

// Example 2: Course Schedule II (Return order of courses to take)
// LeetCode 210: https://leetcode.com/problems/course-schedule-ii/
class CourseScheduleII {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for (const auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            graph[prerequisite].push_back(course); // prerequisite -> course
            inDegree[course]++;
        }
        
        // Find all courses with no prerequisites
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> courseOrder;
        
        // Process courses in topological order
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            courseOrder.push_back(current);
            
            // Reduce in-degree for all courses that depend on current
            for (int nextCourse : graph[current]) {
                if (--inDegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // Check if all courses can be finished
        if (courseOrder.size() != numCourses) {
            return {}; // There's a cycle in the graph
        }
        
        return courseOrder;
    }
};

// Example 3: Alien Dictionary
// LeetCode 269: https://leetcode.com/problems/alien-dictionary/
class AlienDictionary {
public:
    string alienOrder(vector<string>& words) {
        // Create a graph of characters
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> inDegree;
        
        // Initialize graph with all characters
        for (const string& word : words) {
            for (char c : word) {
                graph[c] = unordered_set<char>();
                inDegree[c] = 0;
            }
        }
        
        // Build the graph based on word order
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];
            
            // Check for invalid order (shorter word after longer prefix)
            if (word1.length() > word2.length() && word1.substr(0, word2.length()) == word2) {
                return "";
            }
            
            // Find the first different character
            for (int j = 0; j < min(word1.length(), word2.length()); j++) {
                if (word1[j] != word2[j]) {
                    // Add edge word1[j] -> word2[j]
                    if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                        graph[word1[j]].insert(word2[j]);
                        inDegree[word2[j]]++;
                    }
                    break; // Only the first different character gives ordering info
                }
            }
        }
        
        // Topological sort using BFS
        queue<char> q;
        for (auto& entry : inDegree) {
            if (entry.second == 0) {
                q.push(entry.first);
            }
        }
        
        string result;
        
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;
            
            for (char neighbor : graph[c]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // If not all characters are included, there's a cycle
        if (result.length() != inDegree.size()) {
            return "";
        }
        
        return result;
    }
};

// Example 4: Parallel Courses
// LeetCode 1136: https://leetcode.com/problems/parallel-courses/
class ParallelCourses {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<vector<int>> graph(n + 1); // 1-indexed
        vector<int> inDegree(n + 1, 0);
        
        // Build the graph
        for (const auto& relation : relations) {
            int prereq = relation[0];
            int course = relation[1];
            graph[prereq].push_back(course);
            inDegree[course]++;
        }
        
        // BFS for topological sort
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        int semesters = 0;
        int count = 0; // Number of courses taken
        
        while (!q.empty()) {
            int size = q.size();
            semesters++;
            
            // Process all courses that can be taken in the current semester
            for (int i = 0; i < size; i++) {
                int course = q.front();
                q.pop();
                count++;
                
                // Reduce in-degree of all courses that depend on this course
                for (int nextCourse : graph[course]) {
                    if (--inDegree[nextCourse] == 0) {
                        q.push(nextCourse);
                    }
                }
            }
        }
        
        // Check if all courses were taken
        return count == n ? semesters : -1;
    }
};

// Example 5: Find All Possible Recipes from Given Supplies
// LeetCode 2115: https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/
class FindRecipes {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, 
                                  vector<string>& supplies) {
        unordered_map<string, vector<string>> graph; // item -> items that depend on it
        unordered_map<string, int> inDegree;        // item -> number of dependencies
        
        // Convert supplies to a set for O(1) lookup
        unordered_set<string> supplySet(supplies.begin(), supplies.end());
        
        // Initialize all recipes with in-degree 0
        for (const string& recipe : recipes) {
            inDegree[recipe] = 0;
        }
        
        // Build the graph
        for (int i = 0; i < recipes.size(); i++) {
            string recipe = recipes[i];
            for (const string& ingredient : ingredients[i]) {
                // Skip if the ingredient is a supply
                if (supplySet.find(ingredient) != supplySet.end()) {
                    continue;
                }
                
                // Add an edge: ingredient -> recipe
                graph[ingredient].push_back(recipe);
                inDegree[recipe]++;
                
                // Ensure ingredient is in the inDegree map
                if (inDegree.find(ingredient) == inDegree.end()) {
                    inDegree[ingredient] = 0;
                }
            }
        }
        
        // Start BFS with all available supplies (ingredients not in the inDegree map)
        queue<string> q;
        for (const string& recipe : recipes) {
            if (inDegree[recipe] == 0) {
                q.push(recipe);
            }
        }
        
        vector<string> possibleRecipes;
        
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            
            // Check if this is a recipe
            if (find(recipes.begin(), recipes.end(), current) != recipes.end()) {
                possibleRecipes.push_back(current);
            }
            
            // Process neighbors
            for (const string& neighbor : graph[current]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return possibleRecipes;
    }
};

// Example 6: Minimum Height Trees
// LeetCode 310: https://leetcode.com/problems/minimum-height-trees/
class MinimumHeightTrees {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0}; // Special case: single node
        }
        
        // Build the graph
        vector<unordered_set<int>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].insert(v);
            graph[v].insert(u);
        }
        
        // Find leaf nodes (nodes with only one neighbor)
        vector<int> leaves;
        for (int i = 0; i < n; i++) {
            if (graph[i].size() == 1) {
                leaves.push_back(i);
            }
        }
        
        // Remove leaves level by level until we reach the center(s)
        int remainingNodes = n;
        while (remainingNodes > 2) {
            // Remove current leaves
            remainingNodes -= leaves.size();
            vector<int> newLeaves;
            
            for (int leaf : leaves) {
                // Get the only neighbor
                int neighbor = *graph[leaf].begin();
                
                // Remove the connection from neighbor to leaf
                graph[neighbor].erase(leaf);
                
                // If neighbor becomes a leaf, add it to the new leaves
                if (graph[neighbor].size() == 1) {
                    newLeaves.push_back(neighbor);
                }
            }
            
            // Update leaves for the next iteration
            leaves = newLeaves;
        }
        
        // Remaining leaves are the roots of the minimum height trees
        return leaves;
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

// Main function to demonstrate the topological sort pattern
int main() {
    // Example 1: Basic Topological Sort
    vector<pair<int, int>> edges1 = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
    };
    vector<vector<int>> graph1 = buildDirectedGraph(6, edges1);
    
    cout << "Example 1: Basic Topological Sort" << endl;
    cout << "Graph:" << endl;
    printGraph(graph1);
    
    TopologicalSort solution1;
    vector<int> topoOrder = solution1.topoSort(graph1);
    
    if (topoOrder.empty()) {
        cout << "No valid topological order (graph has a cycle)" << endl;
    } else {
        cout << "Topological sort: ";
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    // Example 2: Course Schedule II
    vector<vector<int>> prerequisites = {
        {1, 0}, {2, 0}, {3, 1}, {3, 2}
    };
    
    cout << "\nExample 2: Course Schedule II" << endl;
    cout << "Prerequisites (course, prerequisite):" << endl;
    for (const auto& prereq : prerequisites) {
        cout << "Course " << prereq[0] << " requires course " << prereq[1] << endl;
    }
    
    CourseScheduleII solution2;
    vector<int> courseOrder = solution2.findOrder(4, prerequisites);
    
    if (courseOrder.empty()) {
        cout << "Cannot finish all courses due to cyclic dependencies" << endl;
    } else {
        cout << "Course order: ";
        for (int course : courseOrder) {
            cout << course << " ";
        }
        cout << endl;
    }
    
    // Example 3: Alien Dictionary
    vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    
    cout << "\nExample 3: Alien Dictionary" << endl;
    cout << "Words: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;
    
    AlienDictionary solution3;
    string alienOrder = solution3.alienOrder(words);
    
    if (alienOrder.empty()) {
        cout << "No valid character order" << endl;
    } else {
        cout << "Character order: " << alienOrder << endl;
    }
    
    // Example 4: Parallel Courses
    vector<vector<int>> relations = {
        {1, 2}, {2, 3}, {3, 4}
    };
    
    cout << "\nExample 4: Parallel Courses" << endl;
    cout << "Course relations (prerequisite, course):" << endl;
    for (const auto& relation : relations) {
        cout << "Course " << relation[0] << " is a prerequisite for course " << relation[1] << endl;
    }
    
    ParallelCourses solution4;
    int minSemesters = solution4.minimumSemesters(4, relations);
    
    if (minSemesters == -1) {
        cout << "Cannot finish all courses due to cyclic dependencies" << endl;
    } else {
        cout << "Minimum semesters needed: " << minSemesters << endl;
    }
    
    // Example 5: Find All Possible Recipes
    vector<string> recipes = {"bread", "sandwich", "burger"};
    vector<vector<string>> ingredients = {
        {"yeast", "flour"},
        {"bread", "meat"},
        {"sandwich", "meat", "bread"}
    };
    vector<string> supplies = {"yeast", "flour", "meat"};
    
    cout << "\nExample 5: Find All Possible Recipes" << endl;
    cout << "Recipes: ";
    for (const string& recipe : recipes) {
        cout << recipe << " ";
    }
    cout << endl;
    
    cout << "Ingredients:" << endl;
    for (int i = 0; i < recipes.size(); i++) {
        cout << recipes[i] << ": ";
        for (const string& ingredient : ingredients[i]) {
            cout << ingredient << " ";
        }
        cout << endl;
    }
    
    cout << "Supplies: ";
    for (const string& supply : supplies) {
        cout << supply << " ";
    }
    cout << endl;
    
    FindRecipes solution5;
    vector<string> possibleRecipes = solution5.findAllRecipes(recipes, ingredients, supplies);
    
    cout << "Possible recipes: ";
    for (const string& recipe : possibleRecipes) {
        cout << recipe << " ";
    }
    cout << endl;
    
    // Example 6: Minimum Height Trees
    vector<vector<int>> edges6 = {
        {1, 0}, {1, 2}, {1, 3}
    };
    
    cout << "\nExample 6: Minimum Height Trees" << endl;
    cout << "Tree edges:" << endl;
    for (const auto& edge : edges6) {
        cout << edge[0] << " -- " << edge[1] << endl;
    }
    
    MinimumHeightTrees solution6;
    vector<int> roots = solution6.findMinHeightTrees(4, edges6);
    
    cout << "Root(s) of minimum height trees: ";
    for (int root : roots) {
        cout << root << " ";
    }
    cout << endl;
    
    return 0;
}
