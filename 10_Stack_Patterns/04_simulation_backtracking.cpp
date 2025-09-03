/**
 * Pattern: Stack - Simulation / Backtracking Helper
 * 
 * Description:
 * This pattern uses a stack to help simulate processes or store state during backtracking.
 * It's particularly useful when you need to track a path, handle undo operations, or
 * implement a depth-first traversal with the ability to backtrack. The stack provides
 * a natural way to store the history of operations or states.
 * 
 * Time Complexity: O(n) where n is the size of the input
 * Space Complexity: O(n) for the stack in the worst case
 * 
 * When to use:
 * - When simulating processes that need to be undone or tracked
 * - When implementing a traversal with backtracking
 * - When manipulating paths in a file system or similar hierarchical structure
 * - When decoding or parsing nested structures
 * 
 * LeetCode Problems:
 * - 71. Simplify Path
 * - 394. Decode String
 * - 735. Asteroid Collision
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Example 1: Simplify Path
// LeetCode 71: https://leetcode.com/problems/simplify-path/
class SimplifyPath {
public:
    string simplify(string path) {
        // Use a stack to track directories
        stack<string> st;
        string directory;
        
        // Append a '/' to the end for easier processing
        path += '/';
        
        for (char c : path) {
            if (c == '/') {
                // Process the directory name when we reach a separator
                if (directory == "..") {
                    // Go up one level (pop from stack)
                    if (!st.empty()) {
                        st.pop();
                    }
                } else if (!directory.empty() && directory != ".") {
                    // Add valid directory to stack
                    st.push(directory);
                }
                // Reset directory for next segment
                directory.clear();
            } else {
                // Build the directory name
                directory += c;
            }
        }
        
        // Construct canonical path from stack
        string result;
        stack<string> reversed;
        
        // Reverse the stack for correct order
        while (!st.empty()) {
            reversed.push(st.top());
            st.pop();
        }
        
        // Build the result
        while (!reversed.empty()) {
            result += "/" + reversed.top();
            reversed.pop();
        }
        
        // Handle root directory case
        return result.empty() ? "/" : result;
    }
    
    // Alternative implementation without reversing the stack
    string simplifyAlternative(string path) {
        vector<string> dirs;  // Use a vector instead of stack for easy traversal
        stringstream ss(path);
        string dir;
        
        // Split by '/'
        while (getline(ss, dir, '/')) {
            if (dir == "" || dir == ".") {
                // Skip empty segments and current directory
                continue;
            } else if (dir == "..") {
                // Go up one level
                if (!dirs.empty()) {
                    dirs.pop_back();
                }
            } else {
                // Add valid directory
                dirs.push_back(dir);
            }
        }
        
        // Construct the canonical path
        string result;
        for (const string& d : dirs) {
            result += "/" + d;
        }
        
        return result.empty() ? "/" : result;
    }
};

// Example 2: Decode String
// LeetCode 394: https://leetcode.com/problems/decode-string/
class DecodeString {
public:
    string decode(string s) {
        stack<string> charStack;  // Stack to hold characters
        stack<int> countStack;    // Stack to hold counts
        string result;
        int index = 0;
        
        while (index < s.length()) {
            if (isdigit(s[index])) {
                // Extract the number
                int count = 0;
                while (isdigit(s[index])) {
                    count = count * 10 + (s[index] - '0');
                    index++;
                }
                countStack.push(count);
            } else if (s[index] == '[') {
                // Start of a new group, push the current result
                charStack.push(result);
                result = "";
                index++;
            } else if (s[index] == ']') {
                // End of a group, repeat the current result
                string temp = charStack.top(); charStack.pop();
                int repeatTimes = countStack.top(); countStack.pop();
                
                // Repeat the current result
                for (int i = 0; i < repeatTimes; i++) {
                    temp += result;
                }
                
                // Update the result
                result = temp;
                index++;
            } else {
                // Regular character, add to result
                result += s[index++];
            }
        }
        
        return result;
    }
};

// Example 3: Asteroid Collision
// LeetCode 735: https://leetcode.com/problems/asteroid-collision/
class AsteroidCollision {
public:
    vector<int> simulateCollision(const vector<int>& asteroids) {
        stack<int> st;
        
        for (int asteroid : asteroids) {
            // Check for collision
            bool destroyed = false;
            
            while (!st.empty() && st.top() > 0 && asteroid < 0) {
                // Collision happens
                if (st.top() < -asteroid) {
                    // Right-moving asteroid is destroyed
                    st.pop();
                    continue;
                } else if (st.top() == -asteroid) {
                    // Both asteroids are destroyed
                    st.pop();
                    destroyed = true;
                    break;
                } else {
                    // Left-moving asteroid is destroyed
                    destroyed = true;
                    break;
                }
            }
            
            // Add asteroid to stack if not destroyed
            if (!destroyed) {
                st.push(asteroid);
            }
        }
        
        // Convert stack to vector in reverse order
        vector<int> result(st.size());
        for (int i = result.size() - 1; i >= 0; i--) {
            result[i] = st.top();
            st.pop();
        }
        
        return result;
    }
};

// Example 4: Maze Solver with Backtracking
class MazeSolver {
public:
    bool solveMaze(vector<vector<char>>& maze, int startX, int startY, int endX, int endY) {
        int rows = maze.size();
        int cols = maze[0].size();
        
        // Check if start and end positions are valid
        if (startX < 0 || startX >= rows || startY < 0 || startY >= cols ||
            endX < 0 || endX >= rows || endY < 0 || endY >= cols ||
            maze[startX][startY] == '#' || maze[endX][endY] == '#') {
            return false;
        }
        
        // Stack to store the path
        stack<pair<int, int>> path;
        // Stack to store visited positions
        stack<pair<int, int>> visited;
        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // Start DFS
        path.push({startX, startY});
        visited.push({startX, startY});
        maze[startX][startY] = 'V'; // Mark as visited
        
        while (!path.empty()) {
            int x = path.top().first;
            int y = path.top().second;
            
            // Check if we've reached the end
            if (x == endX && y == endY) {
                return true;
            }
            
            bool foundPath = false;
            
            // Try all four directions
            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                
                // Check if the new position is valid and not visited
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                    maze[newX][newY] == '.') {
                    // Valid path found
                    path.push({newX, newY});
                    visited.push({newX, newY});
                    maze[newX][newY] = 'V'; // Mark as visited
                    foundPath = true;
                    break;
                }
            }
            
            if (!foundPath) {
                // Backtrack if no valid path
                path.pop();
            }
        }
        
        // Restore maze
        while (!visited.empty()) {
            int x = visited.top().first;
            int y = visited.top().second;
            maze[x][y] = '.';
            visited.pop();
        }
        
        return false;
    }
    
    // Function to print the path if a solution exists
    void printSolution(vector<vector<char>>& maze) {
        for (const auto& row : maze) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
};

// Example 5: Undo/Redo Functionality
class TextEditor {
private:
    string text;
    stack<string> undoStack;
    stack<string> redoStack;
    
public:
    TextEditor() : text("") {
        // Initialize with empty text
    }
    
    void append(string str) {
        undoStack.push(text); // Save current state for undo
        redoStack = stack<string>(); // Clear redo stack
        text += str;
    }
    
    void deleteLastChar() {
        if (!text.empty()) {
            undoStack.push(text); // Save current state for undo
            redoStack = stack<string>(); // Clear redo stack
            text.pop_back();
        }
    }
    
    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(text); // Save current state for redo
            text = undoStack.top();
            undoStack.pop();
        }
    }
    
    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(text); // Save current state for undo
            text = redoStack.top();
            redoStack.pop();
        }
    }
    
    string getText() {
        return text;
    }
};

// Main function to demonstrate the Simulation / Backtracking Helper pattern
int main() {
    // Example 1: Simplify Path
    cout << "Example 1: Simplify Path" << endl;
    
    SimplifyPath sp;
    vector<string> paths = {"/home/", "/../", "/home//foo/", "/a/./b/../../c/"};
    
    for (const string& path : paths) {
        cout << "Original path: \"" << path << "\"" << endl;
        cout << "Simplified path: \"" << sp.simplify(path) << "\"" << endl;
    }
    cout << endl;
    
    // Example 2: Decode String
    cout << "Example 2: Decode String" << endl;
    
    DecodeString ds;
    vector<string> encodedStrings = {"3[a]2[bc]", "3[a2[c]]", "2[abc]3[cd]ef"};
    
    for (const string& encoded : encodedStrings) {
        cout << "Encoded: \"" << encoded << "\"" << endl;
        cout << "Decoded: \"" << ds.decode(encoded) << "\"" << endl;
    }
    cout << endl;
    
    // Example 3: Asteroid Collision
    cout << "Example 3: Asteroid Collision" << endl;
    
    AsteroidCollision ac;
    vector<vector<int>> asteroidSets = {
        {5, 10, -5},
        {8, -8},
        {10, 2, -5},
        {-2, -1, 1, 2}
    };
    
    for (const vector<int>& asteroids : asteroidSets) {
        cout << "Initial asteroids: [";
        for (size_t i = 0; i < asteroids.size(); i++) {
            cout << asteroids[i];
            if (i < asteroids.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        vector<int> result = ac.simulateCollision(asteroids);
        
        cout << "Remaining asteroids: [";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
    
    // Example 4: Maze Solver with Backtracking
    cout << "Example 4: Maze Solver with Backtracking" << endl;
    
    vector<vector<char>> maze = {
        {'.', '.', '#', '#', '.', '.', '.'},
        {'.', '#', '.', '.', '#', '#', '.'},
        {'.', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '#', '#', '.', '.', '.'},
        {'#', '.', '#', '.', '.', '#', '.'},
        {'.', '.', '.', '.', '#', '.', '.'}
    };
    
    cout << "Original Maze:" << endl;
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
    MazeSolver ms;
    bool solvable = ms.solveMaze(maze, 0, 0, 5, 6);
    
    cout << "Is maze solvable from (0,0) to (5,6): " << (solvable ? "Yes" : "No") << endl;
    cout << endl;
    
    // Example 5: Undo/Redo Functionality
    cout << "Example 5: Undo/Redo Functionality" << endl;
    
    TextEditor editor;
    
    cout << "Initial text: \"" << editor.getText() << "\"" << endl;
    
    editor.append("Hello");
    cout << "After append \"Hello\": \"" << editor.getText() << "\"" << endl;
    
    editor.append(" World");
    cout << "After append \" World\": \"" << editor.getText() << "\"" << endl;
    
    editor.deleteLastChar();
    cout << "After delete last char: \"" << editor.getText() << "\"" << endl;
    
    editor.undo();
    cout << "After undo: \"" << editor.getText() << "\"" << endl;
    
    editor.undo();
    cout << "After undo again: \"" << editor.getText() << "\"" << endl;
    
    editor.redo();
    cout << "After redo: \"" << editor.getText() << "\"" << endl;
    
    return 0;
}
