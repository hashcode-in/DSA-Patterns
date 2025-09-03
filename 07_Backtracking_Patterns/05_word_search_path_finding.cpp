/**
 * Pattern: Backtracking - Word Search / Path Finding in Grid
 * 
 * Description:
 * This pattern involves finding paths in a grid with specific constraints. It's a common
 * backtracking pattern that uses depth-first search (DFS) to explore possible paths in a
 * 2D matrix while maintaining validity constraints.
 * 
 * Time Complexity: 
 * - O(N * 4^L) where N is the number of cells in the grid and L is the length of the word or path
 * - For each starting cell, we potentially explore 4 directions for each character
 * 
 * Space Complexity: O(L) for the recursion stack depth
 * 
 * When to use:
 * - Searching for words or patterns in a grid
 * - Finding paths in mazes or game boards
 * - Exploring connected regions with specific constraints
 * 
 * LeetCode Problems:
 * - 79. Word Search
 * - 212. Word Search II
 * - 980. Unique Paths III
 * - 1219. Path with Maximum Gold
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Example 1: Word Search
// LeetCode 79: https://leetcode.com/problems/word-search/
class WordSearch {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
        // Try each cell as a starting point
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    // Four possible directions: up, right, down, left
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    bool backtrack(vector<vector<char>>& board, const string& word, int row, int col, int index) {
        // If we've matched all characters in the word, we found a solution
        if (index == word.length()) {
            return true;
        }
        
        // Check if current cell is out of bounds or doesn't match the current character
        int rows = board.size();
        int cols = board[0].size();
        
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != word[index]) {
            return false;
        }
        
        // Mark the current cell as visited (by changing to a special character)
        char temp = board[row][col];
        board[row][col] = '#';  // Use a character that won't match any word character
        
        // Explore all four directions
        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;
            
            // If we find a path from here, return true
            if (backtrack(board, word, newRow, newCol, index + 1)) {
                // Restore the original character before returning
                board[row][col] = temp;
                return true;
            }
        }
        
        // Restore the original character (backtrack)
        board[row][col] = temp;
        
        // No valid path found
        return false;
    }
};

// Trie data structure for Word Search II
class Trie {
public:
    struct TrieNode {
        TrieNode* children[26];
        string word;  // Store the complete word at leaf nodes
        
        TrieNode() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            word = "";
        }
    };
    
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->word = word;  // Mark the end of a word
    }
};

// Example 2: Word Search II (using Trie)
// LeetCode 212: https://leetcode.com/problems/word-search-ii/
class WordSearchII {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Build a Trie from the word list
        Trie trie;
        for (const string& word : words) {
            trie.insert(word);
        }
        
        int rows = board.size();
        int cols = board[0].size();
        vector<string> result;
        
        // DFS from each cell
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                backtrack(board, i, j, trie.root, result);
            }
        }
        
        return result;
    }
    
private:
    // Four possible directions: up, right, down, left
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    void backtrack(vector<vector<char>>& board, int row, int col, Trie::TrieNode* node, vector<string>& result) {
        int rows = board.size();
        int cols = board[0].size();
        
        // Check for out of bounds or visited cells
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] == '#') {
            return;
        }
        
        char c = board[row][col];
        
        // Check if this character exists in the current Trie node
        Trie::TrieNode* nextNode = node->children[c - 'a'];
        if (!nextNode) {
            return;
        }
        
        // If we've reached a word, add it to the result
        if (!nextNode->word.empty()) {
            result.push_back(nextNode->word);
            nextNode->word = "";  // Mark as visited to avoid duplicates
        }
        
        // Mark the current cell as visited
        board[row][col] = '#';
        
        // Explore all four directions
        for (const auto& dir : directions) {
            backtrack(board, row + dir.first, col + dir.second, nextNode, result);
        }
        
        // Restore the original character (backtrack)
        board[row][col] = c;
    }
};

// Example 3: Unique Paths III
// LeetCode 980: https://leetcode.com/problems/unique-paths-iii/
class UniquePathsIII {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int startRow = 0, startCol = 0;
        int emptySquares = 0;
        
        // Find the starting point and count empty squares
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    startRow = i;
                    startCol = j;
                } else if (grid[i][j] == 0) {
                    emptySquares++;
                }
            }
        }
        
        int paths = 0;
        backtrack(grid, startRow, startCol, emptySquares + 1, paths);  // +1 to include the starting square
        
        return paths;
    }
    
private:
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    void backtrack(vector<vector<int>>& grid, int row, int col, int remaining, int& paths) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Check if out of bounds or not a valid cell
        if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] == -1) {
            return;
        }
        
        // If we reached the end with all squares visited
        if (grid[row][col] == 2) {
            if (remaining == 1) {  // All empty squares have been visited
                paths++;
            }
            return;
        }
        
        // Mark the current cell as visited
        int temp = grid[row][col];
        grid[row][col] = -1;
        
        // Explore all four directions
        for (const auto& dir : directions) {
            backtrack(grid, row + dir.first, col + dir.second, remaining - 1, paths);
        }
        
        // Restore the original value (backtrack)
        grid[row][col] = temp;
    }
};

// Example 4: Path with Maximum Gold
// LeetCode 1219: https://leetcode.com/problems/path-with-maximum-gold/
class PathWithMaximumGold {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int maxGold = 0;
        
        // Try each cell as a starting point (only cells with gold)
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] > 0) {
                    maxGold = max(maxGold, backtrack(grid, i, j));
                }
            }
        }
        
        return maxGold;
    }
    
private:
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    int backtrack(vector<vector<int>>& grid, int row, int col) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Check if out of bounds or no gold
        if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] == 0) {
            return 0;
        }
        
        // Collect gold from the current cell
        int gold = grid[row][col];
        
        // Mark as visited
        grid[row][col] = 0;
        
        // Track maximum gold from the four directions
        int maxGold = 0;
        for (const auto& dir : directions) {
            maxGold = max(maxGold, backtrack(grid, row + dir.first, col + dir.second));
        }
        
        // Restore the cell (backtrack)
        grid[row][col] = gold;
        
        // Return gold from this cell plus maximum from the best direction
        return gold + maxGold;
    }
};

// Example 5: N-Queens (Grid-based backtracking)
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
    bool isValid(vector<string>& board, int row, int col) {
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
        int n = board.size();
        
        if (row == n) {
            result.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col)) {
                board[row][col] = 'Q';  // Place queen
                
                backtrack(board, row + 1, result);
                
                board[row][col] = '.';  // Remove queen (backtrack)
            }
        }
    }
};

// Example 6: Sudoku Solver
// LeetCode 37: https://leetcode.com/problems/sudoku-solver/
class SudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0, 0);
    }
    
private:
    bool backtrack(vector<vector<char>>& board, int row, int col) {
        // If we've gone through all cells, the puzzle is solved
        if (row == 9) {
            return true;
        }
        
        // Move to the next row when we reach the end of a column
        if (col == 9) {
            return backtrack(board, row + 1, 0);
        }
        
        // Skip cells that are already filled
        if (board[row][col] != '.') {
            return backtrack(board, row, col + 1);
        }
        
        // Try placing digits 1-9
        for (char digit = '1'; digit <= '9'; digit++) {
            if (isValid(board, row, col, digit)) {
                board[row][col] = digit;  // Place digit
                
                if (backtrack(board, row, col + 1)) {
                    return true;  // Solution found
                }
                
                board[row][col] = '.';  // Remove digit (backtrack)
            }
        }
        
        // No valid digit found for this cell
        return false;
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char digit) {
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
        
        for (int i = boxRow; i < boxRow + 3; i++) {
            for (int j = boxCol; j < boxCol + 3; j++) {
                if (board[i][j] == digit) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// Example 7: Crossword Puzzle
// Similar to: https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/
class CrosswordPuzzle {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
        // Try placing the word horizontally (left to right)
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j <= cols - word.length(); j++) {
                if (canPlaceHorizontally(board, word, i, j, 1) ||
                    canPlaceHorizontally(board, word, i, j + word.length() - 1, -1)) {
                    return true;
                }
            }
        }
        
        // Try placing the word vertically (top to bottom)
        for (int i = 0; i <= rows - word.length(); i++) {
            for (int j = 0; j < cols; j++) {
                if (canPlaceVertically(board, word, i, j, 1) ||
                    canPlaceVertically(board, word, i + word.length() - 1, j, -1)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    bool canPlaceHorizontally(vector<vector<char>>& board, const string& word, int row, int startCol, int dir) {
        int cols = board[0].size();
        
        // Check if there's a blocking cell before the word
        if ((dir == 1 && startCol > 0 && board[row][startCol - 1] != '#') ||
            (dir == -1 && startCol < cols - 1 && board[row][startCol + 1] != '#')) {
            return false;
        }
        
        // Check if there's a blocking cell after the word
        int endCol = startCol + (dir * (word.length() - 1));
        if ((dir == 1 && endCol < cols - 1 && board[row][endCol + 1] != '#') ||
            (dir == -1 && endCol > 0 && board[row][endCol - 1] != '#')) {
            return false;
        }
        
        // Check if the word fits
        for (int i = 0; i < word.length(); i++) {
            int col = startCol + (dir * i);
            if (col < 0 || col >= cols || (board[row][col] != ' ' && board[row][col] != word[i])) {
                return false;
            }
        }
        
        return true;
    }
    
    bool canPlaceVertically(vector<vector<char>>& board, const string& word, int startRow, int col, int dir) {
        int rows = board.size();
        
        // Check if there's a blocking cell before the word
        if ((dir == 1 && startRow > 0 && board[startRow - 1][col] != '#') ||
            (dir == -1 && startRow < rows - 1 && board[startRow + 1][col] != '#')) {
            return false;
        }
        
        // Check if there's a blocking cell after the word
        int endRow = startRow + (dir * (word.length() - 1));
        if ((dir == 1 && endRow < rows - 1 && board[endRow + 1][col] != '#') ||
            (dir == -1 && endRow > 0 && board[endRow - 1][col] != '#')) {
            return false;
        }
        
        // Check if the word fits
        for (int i = 0; i < word.length(); i++) {
            int row = startRow + (dir * i);
            if (row < 0 || row >= rows || (board[row][col] != ' ' && board[row][col] != word[i])) {
                return false;
            }
        }
        
        return true;
    }
};

// Function to print 2D grid of characters
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Function to print 2D grid of integers
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate Word Search / Path Finding pattern
int main() {
    // Example 1: Word Search
    cout << "Example 1: Word Search" << endl;
    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word1 = "ABCCED";
    
    cout << "Board:" << endl;
    printBoard(board1);
    cout << "Word: " << word1 << endl;
    
    WordSearch ws;
    bool result1 = ws.exist(board1, word1);
    
    cout << "Word exists in the board: " << (result1 ? "true" : "false") << endl;
    
    // Example 2: Word Search II
    cout << "\nExample 2: Word Search II" << endl;
    vector<vector<char>> board2 = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };
    vector<string> words = {"oath", "pea", "eat", "rain"};
    
    cout << "Board:" << endl;
    printBoard(board2);
    cout << "Words: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;
    
    WordSearchII ws2;
    vector<string> result2 = ws2.findWords(board2, words);
    
    cout << "Words found in the board: ";
    for (const string& word : result2) {
        cout << word << " ";
    }
    cout << endl;
    
    // Example 3: Unique Paths III
    cout << "\nExample 3: Unique Paths III" << endl;
    vector<vector<int>> grid3 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}
    };
    
    cout << "Grid (1=start, 2=end, 0=empty, -1=obstacle):" << endl;
    printGrid(grid3);
    
    UniquePathsIII up3;
    int result3 = up3.uniquePathsIII(grid3);
    
    cout << "Number of unique paths visiting all empty cells: " << result3 << endl;
    
    // Example 4: Path with Maximum Gold
    cout << "\nExample 4: Path with Maximum Gold" << endl;
    vector<vector<int>> grid4 = {
        {0, 6, 0},
        {5, 8, 7},
        {0, 9, 0}
    };
    
    cout << "Gold grid:" << endl;
    printGrid(grid4);
    
    PathWithMaximumGold pmg;
    int result4 = pmg.getMaximumGold(grid4);
    
    cout << "Maximum gold that can be collected: " << result4 << endl;
    
    // Example 5: N-Queens
    cout << "\nExample 5: N-Queens" << endl;
    int n = 4;
    
    cout << "N = " << n << endl;
    
    NQueens nq;
    vector<vector<string>> result5 = nq.solveNQueens(n);
    
    cout << "Solutions for " << n << "-Queens:" << endl;
    for (int i = 0; i < result5.size(); i++) {
        cout << "Solution " << (i + 1) << ":" << endl;
        for (const string& row : result5[i]) {
            cout << row << endl;
        }
        cout << endl;
    }
    
    // Example 6: Sudoku Solver
    cout << "\nExample 6: Sudoku Solver" << endl;
    vector<vector<char>> board6 = {
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
    printBoard(board6);
    
    SudokuSolver ss;
    ss.solveSudoku(board6);
    
    cout << "Sudoku board after solving:" << endl;
    printBoard(board6);
    
    // Example 7: Crossword Puzzle
    cout << "\nExample 7: Crossword Puzzle" << endl;
    vector<vector<char>> board7 = {
        {'#', ' ', '#'},
        {' ', ' ', ' '},
        {'#', ' ', '#'}
    };
    string word7 = "abc";
    
    cout << "Crossword board (# = block):" << endl;
    printBoard(board7);
    cout << "Word to place: " << word7 << endl;
    
    CrosswordPuzzle cp;
    bool result7 = cp.placeWordInCrossword(board7, word7);
    
    cout << "Can the word be placed in the crossword: " << (result7 ? "true" : "false") << endl;
    
    return 0;
}
