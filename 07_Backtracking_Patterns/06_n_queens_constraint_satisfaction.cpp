/**
 * Pattern: Backtracking - N-Queens / Constraint Satisfaction
 * 
 * Description:
 * This pattern deals with placing elements on a grid with specific constraints. It's a classic
 * backtracking problem that involves making decisions about element placement while maintaining
 * validity constraints that eliminate paths that cannot lead to valid solutions.
 * 
 * Time Complexity: 
 * - N-Queens: O(N!), where N is the size of the board
 * - Sudoku: O(9^(N*N)), where N is the number of empty cells
 * 
 * Space Complexity: O(N^2) for the board representation and O(N) for the recursion stack
 * 
 * When to use:
 * - Placing elements on a grid with constraints
 * - Solving puzzles like N-Queens, Sudoku, Crosswords
 * - Problems where decisions at each step must satisfy global constraints
 * 
 * LeetCode Problems:
 * - 51. N-Queens
 * - 52. N-Queens II (counting solutions)
 * - 37. Sudoku Solver
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <bitset>

using namespace std;

// Example 1: N-Queens
// LeetCode 51: https://leetcode.com/problems/n-queens/
class NQueens {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));  // Initialize empty board
        
        backtrack(board, 0, result);
        
        return result;
    }
    
private:
    bool isValid(const vector<string>& board, int row, int col) {
        int n = board.size();
        
        // Check column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        
        // Check left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        // Check right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        return true;
    }
    
    void backtrack(vector<string>& board, int row, vector<vector<string>>& result) {
        // Base case: if we've placed queens in all rows
        if (row == board.size()) {
            result.push_back(board);
            return;
        }
        
        int n = board.size();
        
        // Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col)) {
                board[row][col] = 'Q';  // Place queen
                
                backtrack(board, row + 1, result);  // Move to next row
                
                board[row][col] = '.';  // Remove queen (backtrack)
            }
        }
    }
};

// Example 2: N-Queens II (Optimized with bitsets)
// LeetCode 52: https://leetcode.com/problems/n-queens-ii/
class NQueensII {
public:
    int totalNQueens(int n) {
        // For n > 31, we would need to use a different approach
        if (n > 31) {
            return solveWithStandardApproach(n);
        }
        
        int count = 0;
        backtrack(0, 0, 0, 0, n, count);
        return count;
    }
    
private:
    // Optimized approach using bit manipulation
    void backtrack(int row, int cols, int diag1, int diag2, int n, int& count) {
        if (row == n) {
            count++;
            return;
        }
        
        // Available positions are those that don't have a queen in the same column or diagonal
        int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);
        
        while (available) {
            // Get the rightmost 1 (next available position)
            int pos = available & -available;
            
            // Turn off the rightmost 1
            available -= pos;
            
            // Place queen and continue to next row
            backtrack(
                row + 1,
                cols | pos,             // Add to columns
                (diag1 | pos) << 1,     // Add to diagonal 1 (left to right) and shift
                (diag2 | pos) >> 1,     // Add to diagonal 2 (right to left) and shift
                n,
                count
            );
        }
    }
    
    // Standard approach for larger n
    int solveWithStandardApproach(int n) {
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false);  // / diagonal
        vector<bool> diag2(2 * n - 1, false);  // \ diagonal
        int count = 0;
        
        standardBacktrack(0, n, cols, diag1, diag2, count);
        
        return count;
    }
    
    void standardBacktrack(int row, int n, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, int& count) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            int d1 = row + col;            // / diagonal
            int d2 = row - col + n - 1;    // \ diagonal
            
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                cols[col] = diag1[d1] = diag2[d2] = true;
                standardBacktrack(row + 1, n, cols, diag1, diag2, count);
                cols[col] = diag1[d1] = diag2[d2] = false;  // backtrack
            }
        }
    }
};

// Example 3: Sudoku Solver
// LeetCode 37: https://leetcode.com/problems/sudoku-solver/
class SudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
    
private:
    bool solve(vector<vector<char>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                // Find an empty cell
                if (board[row][col] == '.') {
                    // Try placing digits 1-9
                    for (char digit = '1'; digit <= '9'; digit++) {
                        if (isValid(board, row, col, digit)) {
                            // Place the digit
                            board[row][col] = digit;
                            
                            // Recursively try to solve the rest of the puzzle
                            if (solve(board)) {
                                return true;  // Solution found
                            }
                            
                            // If placing this digit doesn't lead to a solution, backtrack
                            board[row][col] = '.';
                        }
                    }
                    
                    // If no digit works, trigger backtracking
                    return false;
                }
            }
        }
        
        // All cells filled, puzzle solved
        return true;
    }
    
    bool isValid(const vector<vector<char>>& board, int row, int col, char digit) {
        // Check row
        for (int j = 0; j < 9; j++) {
            if (board[row][j] == digit) {
                return false;
            }
        }
        
        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == digit) {
                return false;
            }
        }
        
        // Check 3x3 box
        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[boxRow + i][boxCol + j] == digit) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// Example 4: Optimized Sudoku Solver (with bit manipulation)
class OptimizedSudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // Initialize the constraints
        vector<bitset<9>> rowConstraints(9, bitset<9>());
        vector<bitset<9>> colConstraints(9, bitset<9>());
        vector<bitset<9>> boxConstraints(9, bitset<9>());
        
        // Set up the constraints based on the initial board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int digit = board[i][j] - '1';  // Convert to 0-based index
                    int boxIdx = (i / 3) * 3 + j / 3;
                    
                    // Mark the digit as used in this row, column, and box
                    rowConstraints[i][digit] = true;
                    colConstraints[j][digit] = true;
                    boxConstraints[boxIdx][digit] = true;
                }
            }
        }
        
        solve(board, rowConstraints, colConstraints, boxConstraints);
    }
    
private:
    bool solve(vector<vector<char>>& board,
               vector<bitset<9>>& rowConstraints,
               vector<bitset<9>>& colConstraints,
               vector<bitset<9>>& boxConstraints) {
        // Find the cell with the fewest possibilities
        int minPossibilities = 10;
        int minRow = -1;
        int minCol = -1;
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    // Count possible digits for this cell
                    int boxIdx = (i / 3) * 3 + j / 3;
                    int possibilities = 0;
                    
                    for (int digit = 0; digit < 9; digit++) {
                        if (!rowConstraints[i][digit] && !colConstraints[j][digit] && !boxConstraints[boxIdx][digit]) {
                            possibilities++;
                        }
                    }
                    
                    if (possibilities < minPossibilities) {
                        minPossibilities = possibilities;
                        minRow = i;
                        minCol = j;
                        
                        // Optimization: If there's a cell with only one possibility, choose it immediately
                        if (possibilities == 1) {
                            break;
                        }
                    }
                }
            }
            if (minPossibilities == 1) {
                break;  // Break outer loop too
            }
        }
        
        // If no empty cell found, the puzzle is solved
        if (minRow == -1) {
            return true;
        }
        
        // Try each possible digit
        int boxIdx = (minRow / 3) * 3 + minCol / 3;
        
        for (int digit = 0; digit < 9; digit++) {
            if (!rowConstraints[minRow][digit] && !colConstraints[minCol][digit] && !boxConstraints[boxIdx][digit]) {
                // Place the digit
                board[minRow][minCol] = digit + '1';  // Convert to char
                rowConstraints[minRow][digit] = true;
                colConstraints[minCol][digit] = true;
                boxConstraints[boxIdx][digit] = true;
                
                // Recursively solve the rest
                if (solve(board, rowConstraints, colConstraints, boxConstraints)) {
                    return true;
                }
                
                // Backtrack
                board[minRow][minCol] = '.';
                rowConstraints[minRow][digit] = false;
                colConstraints[minCol][digit] = false;
                boxConstraints[boxIdx][digit] = false;
            }
        }
        
        return false;
    }
};

// Example 5: Map Coloring
class MapColoring {
public:
    // Graph represented as an adjacency list
    bool colorMap(vector<vector<int>>& graph, int numColors, vector<int>& colors) {
        int n = graph.size();
        colors.resize(n, 0);  // Initialize all nodes with no color (0)
        
        return backtrack(graph, numColors, colors, 0);
    }
    
private:
    bool backtrack(vector<vector<int>>& graph, int numColors, vector<int>& colors, int node) {
        // If we've colored all nodes, we have a solution
        if (node == graph.size()) {
            return true;
        }
        
        // Try each color
        for (int color = 1; color <= numColors; color++) {
            if (isValidColor(graph, colors, node, color)) {
                colors[node] = color;
                
                // Recursively color the next node
                if (backtrack(graph, numColors, colors, node + 1)) {
                    return true;
                }
                
                // Backtrack
                colors[node] = 0;
            }
        }
        
        return false;
    }
    
    bool isValidColor(vector<vector<int>>& graph, vector<int>& colors, int node, int color) {
        // Check if any adjacent node has the same color
        for (int neighbor : graph[node]) {
            if (colors[neighbor] == color) {
                return false;
            }
        }
        return true;
    }
};

// Example 6: Knight's Tour
class KnightsTour {
public:
    vector<vector<int>> solveKnightsTour(int n) {
        vector<vector<int>> board(n, vector<int>(n, -1));  // -1 represents unvisited
        
        // Start from the top-left corner
        board[0][0] = 0;  // Mark the starting position as the first move
        
        // Try to solve the tour
        if (backtrack(board, 0, 0, 1)) {
            return board;
        } else {
            return {};  // No solution found
        }
    }
    
private:
    // Possible knight moves
    vector<pair<int, int>> moves = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    bool backtrack(vector<vector<int>>& board, int row, int col, int moveCount) {
        int n = board.size();
        
        // If we've visited all cells, the tour is complete
        if (moveCount == n * n) {
            return true;
        }
        
        // Try each possible knight move
        for (const auto& move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;
            
            // Check if the move is valid
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && board[newRow][newCol] == -1) {
                // Make the move
                board[newRow][newCol] = moveCount;
                
                // Recursively try to complete the tour
                if (backtrack(board, newRow, newCol, moveCount + 1)) {
                    return true;
                }
                
                // Backtrack
                board[newRow][newCol] = -1;
            }
        }
        
        return false;
    }
};

// Example 7: Rat in a Maze
class RatInMaze {
public:
    vector<string> findPath(vector<vector<int>>& maze) {
        int n = maze.size();
        vector<string> paths;
        string path;
        
        // Check if source or destination is blocked
        if (maze[0][0] == 0 || maze[n-1][n-1] == 0) {
            return paths;
        }
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        backtrack(maze, 0, 0, n, visited, path, paths);
        
        return paths;
    }
    
private:
    // Possible moves: Down, Left, Right, Up
    vector<pair<int, int>> moves = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    vector<char> directions = {'D', 'L', 'R', 'U'};
    
    void backtrack(vector<vector<int>>& maze, int row, int col, int n, 
                   vector<vector<bool>>& visited, string& path, vector<string>& paths) {
        // If we've reached the destination
        if (row == n - 1 && col == n - 1) {
            paths.push_back(path);
            return;
        }
        
        // Mark current cell as visited
        visited[row][col] = true;
        
        // Try each possible move
        for (int i = 0; i < 4; i++) {
            int newRow = row + moves[i].first;
            int newCol = col + moves[i].second;
            
            // Check if the move is valid
            if (isValid(maze, newRow, newCol, n, visited)) {
                // Add the direction to the path
                path.push_back(directions[i]);
                
                // Recursively explore this path
                backtrack(maze, newRow, newCol, n, visited, path, paths);
                
                // Backtrack
                path.pop_back();
            }
        }
        
        // Unmark current cell
        visited[row][col] = false;
    }
    
    bool isValid(vector<vector<int>>& maze, int row, int col, int n, vector<vector<bool>>& visited) {
        return row >= 0 && row < n && col >= 0 && col < n && maze[row][col] == 1 && !visited[row][col];
    }
};

// Utility function to print a vector of strings
void printBoard(const vector<string>& board) {
    for (const string& row : board) {
        cout << row << endl;
    }
}

// Utility function to print a 2D vector
void print2DVector(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << cell << "\t";
        }
        cout << endl;
    }
}

// Main function to demonstrate N-Queens / Constraint Satisfaction pattern
int main() {
    // Example 1: N-Queens
    cout << "Example 1: N-Queens" << endl;
    int n = 4;
    cout << "N = " << n << endl;
    
    NQueens nq;
    vector<vector<string>> nQueensResult = nq.solveNQueens(n);
    
    cout << "Number of solutions: " << nQueensResult.size() << endl;
    cout << "First solution:" << endl;
    if (!nQueensResult.empty()) {
        printBoard(nQueensResult[0]);
    }
    
    // Example 2: N-Queens II (Counting solutions)
    cout << "\nExample 2: N-Queens II (Counting solutions)" << endl;
    n = 8;
    cout << "N = " << n << endl;
    
    NQueensII nq2;
    int nQueensCount = nq2.totalNQueens(n);
    
    cout << "Number of solutions for " << n << "-Queens: " << nQueensCount << endl;
    
    // Example 3: Sudoku Solver
    cout << "\nExample 3: Sudoku Solver" << endl;
    vector<vector<char>> sudokuBoard = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    
    cout << "Sudoku board before solving:" << endl;
    for (const auto& row : sudokuBoard) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
    
    SudokuSolver ss;
    ss.solveSudoku(sudokuBoard);
    
    cout << "Sudoku board after solving:" << endl;
    for (const auto& row : sudokuBoard) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
    
    // Example 4: Map Coloring
    cout << "\nExample 4: Map Coloring" << endl;
    vector<vector<int>> graph = {
        {1, 2, 3},      // Region 0 is adjacent to regions 1, 2, and 3
        {0, 2},         // Region 1 is adjacent to regions 0 and 2
        {0, 1, 3},      // Region 2 is adjacent to regions 0, 1, and 3
        {0, 2}          // Region 3 is adjacent to regions 0 and 2
    };
    int numColors = 3;
    vector<int> colors;
    
    cout << "Graph:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << "Region " << i << " is adjacent to: ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j];
            if (j < graph[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    cout << "Number of colors: " << numColors << endl;
    
    MapColoring mc;
    bool canColor = mc.colorMap(graph, numColors, colors);
    
    if (canColor) {
        cout << "Map can be colored. Colors assigned:" << endl;
        for (int i = 0; i < colors.size(); i++) {
            cout << "Region " << i << ": Color " << colors[i] << endl;
        }
    } else {
        cout << "Map cannot be colored with " << numColors << " colors." << endl;
    }
    
    // Example 5: Knight's Tour
    cout << "\nExample 5: Knight's Tour" << endl;
    n = 5;  // 5x5 board
    cout << "Board size: " << n << "x" << n << endl;
    
    KnightsTour kt;
    vector<vector<int>> knightsTourResult = kt.solveKnightsTour(n);
    
    if (!knightsTourResult.empty()) {
        cout << "Knight's Tour solution:" << endl;
        print2DVector(knightsTourResult);
    } else {
        cout << "No Knight's Tour solution found for " << n << "x" << n << " board." << endl;
    }
    
    // Example 6: Rat in a Maze
    cout << "\nExample 6: Rat in a Maze" << endl;
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    
    cout << "Maze (1 = path, 0 = wall):" << endl;
    print2DVector(maze);
    
    RatInMaze rim;
    vector<string> paths = rim.findPath(maze);
    
    if (!paths.empty()) {
        cout << "Paths found: " << paths.size() << endl;
        cout << "Paths:" << endl;
        for (const string& path : paths) {
            cout << path << endl;
        }
    } else {
        cout << "No path found from source to destination." << endl;
    }
    
    return 0;
}
