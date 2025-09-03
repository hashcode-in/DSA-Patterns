/**
 * Pattern: Greedy - Task Scheduling (Frequency Based)
 * 
 * Description:
 * This pattern involves scheduling tasks optimally based on their frequencies or other
 * constraints. The greedy approach typically involves sorting tasks by frequency and
 * arranging them to satisfy certain conditions (like cooling periods or avoiding
 * adjacent identical tasks).
 * 
 * Time Complexity: 
 * - O(n log n) for sorting 
 * - O(n) for the scheduling process
 * 
 * Space Complexity: O(n) for tracking frequencies and constructing the schedule
 * 
 * When to use:
 * - Scheduling tasks with cooling periods
 * - Reorganizing characters in a string to avoid repetition
 * - Problems involving frequency-based task arrangement
 * 
 * LeetCode Problems:
 * - 621. Task Scheduler
 * - 767. Reorganize String
 * - 358. Rearrange String k Distance Apart
 * - 1054. Distant Barcodes
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

// Example 1: Task Scheduler
// LeetCode 621: https://leetcode.com/problems/task-scheduler/
class TaskScheduler {
public:
    // Approach 1: Using Priority Queue (Max Heap) and Queue
    int leastInterval(vector<char>& tasks, int n) {
        // Count frequency of each task
        unordered_map<char, int> taskFreq;
        for (char task : tasks) {
            taskFreq[task]++;
        }
        
        // Max heap to store task frequencies
        priority_queue<int> maxHeap;
        for (auto& [task, freq] : taskFreq) {
            maxHeap.push(freq);
        }
        
        int cycles = 0;
        
        // Process tasks until all are scheduled
        while (!maxHeap.empty()) {
            vector<int> temp;
            
            // Process up to n+1 tasks in each cycle
            for (int i = 0; i <= n; i++) {
                if (!maxHeap.empty()) {
                    temp.push_back(maxHeap.top() - 1); // Execute 1 instance of a task
                    maxHeap.pop();
                }
            }
            
            // Add tasks back to the heap if they still have instances left
            for (int count : temp) {
                if (count > 0) {
                    maxHeap.push(count);
                }
            }
            
            // If heap is empty, all tasks are done; otherwise, we need to consider cooling periods
            cycles += maxHeap.empty() ? temp.size() : n + 1;
        }
        
        return cycles;
    }
    
    // Approach 2: Mathematical Formula
    int leastIntervalMath(vector<char>& tasks, int n) {
        // Count frequency of each task
        vector<int> frequencies(26, 0);
        for (char task : tasks) {
            frequencies[task - 'A']++;
        }
        
        // Find the maximum frequency
        int maxFreq = *max_element(frequencies.begin(), frequencies.end());
        
        // Count how many tasks have the maximum frequency
        int maxCount = count(frequencies.begin(), frequencies.end(), maxFreq);
        
        // Calculate total time
        // Formula: (maxFreq - 1) * (n + 1) + maxCount
        // Explanation:
        // - (maxFreq - 1) represents the number of cooling periods needed
        // - (n + 1) represents the length of each period (including 1 execution)
        // - maxCount is added to account for the last cycle where tasks with max frequency are executed
        int result = (maxFreq - 1) * (n + 1) + maxCount;
        
        // Return the max of the formula result and the total number of tasks
        // (to handle cases where idle slots are not needed)
        return max(result, (int)tasks.size());
    }
};

// Example 2: Reorganize String
// LeetCode 767: https://leetcode.com/problems/reorganize-string/
class ReorganizeString {
public:
    string reorganizeString(string s) {
        // Count frequency of each character
        unordered_map<char, int> charFreq;
        for (char c : s) {
            charFreq[c]++;
        }
        
        // Create a max heap based on character frequencies
        priority_queue<pair<int, char>> maxHeap;
        for (auto& [c, freq] : charFreq) {
            // If any character appears more than half the string length, reorganization is impossible
            if (freq > (s.length() + 1) / 2) {
                return "";
            }
            maxHeap.push({freq, c});
        }
        
        string result = "";
        
        // Keep processing until only 0 or 1 character type remains
        while (maxHeap.size() >= 2) {
            // Take the two most frequent characters
            auto [freq1, char1] = maxHeap.top(); maxHeap.pop();
            auto [freq2, char2] = maxHeap.top(); maxHeap.pop();
            
            // Add them to the result
            result += char1;
            result += char2;
            
            // Decrement their frequencies and add back if needed
            if (--freq1 > 0) maxHeap.push({freq1, char1});
            if (--freq2 > 0) maxHeap.push({freq2, char2});
        }
        
        // Handle the case where one character type is left
        if (!maxHeap.empty()) {
            auto [freq, c] = maxHeap.top();
            
            // If more than one occurrence is left, we can't reorganize
            if (freq > 1) {
                return "";
            }
            
            result += c;
        }
        
        return result;
    }
};

// Example 3: Rearrange String k Distance Apart
// LeetCode 358: https://leetcode.com/problems/rearrange-string-k-distance-apart/
class RearrangeStringKDistanceApart {
public:
    string rearrangeString(string s, int k) {
        if (k <= 1) {
            return s;  // No rearrangement needed
        }
        
        // Count frequency of each character
        unordered_map<char, int> charFreq;
        for (char c : s) {
            charFreq[c]++;
        }
        
        // Max heap to get the most frequent character
        priority_queue<pair<int, char>> maxHeap;
        for (auto& [c, freq] : charFreq) {
            maxHeap.push({freq, c});
        }
        
        string result = "";
        
        // Process all characters
        while (!maxHeap.empty()) {
            // Store characters that need cooling
            vector<pair<int, char>> cooling;
            
            // Process up to k characters
            int count = min(k, (int)s.length() - (int)result.length());
            
            // If we can't get 'count' characters, it's impossible to rearrange
            if (count > maxHeap.size()) {
                return "";
            }
            
            // Process 'count' characters
            for (int i = 0; i < count; i++) {
                auto [freq, c] = maxHeap.top(); maxHeap.pop();
                result += c;
                
                // If frequency > 1, add to cooling
                if (--freq > 0) {
                    cooling.push_back({freq, c});
                }
            }
            
            // Add back characters after cooling
            for (auto& [freq, c] : cooling) {
                maxHeap.push({freq, c});
            }
        }
        
        return result.length() == s.length() ? result : "";
    }
};

// Example 4: Distant Barcodes
// LeetCode 1054: https://leetcode.com/problems/distant-barcodes/
class DistantBarcodes {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        
        // Count frequency of each barcode
        unordered_map<int, int> barcodeFreq;
        for (int barcode : barcodes) {
            barcodeFreq[barcode]++;
        }
        
        // Max heap based on frequencies
        priority_queue<pair<int, int>> maxHeap;
        for (auto& [barcode, freq] : barcodeFreq) {
            maxHeap.push({freq, barcode});
        }
        
        vector<int> result(n);
        int index = 0;
        
        while (!maxHeap.empty()) {
            auto [freq, barcode] = maxHeap.top(); maxHeap.pop();
            
            // Fill in even positions first, then odd positions
            while (freq > 0) {
                if (index >= n) {
                    index = 1;  // Start filling odd positions
                }
                
                result[index] = barcode;
                index += 2;
                freq--;
            }
        }
        
        return result;
    }
    
    // Alternative approach: Direct placement
    vector<int> rearrangeBarcodesDirectPlacement(vector<int>& barcodes) {
        int n = barcodes.size();
        
        // Count frequency of each barcode
        unordered_map<int, int> barcodeFreq;
        for (int barcode : barcodes) {
            barcodeFreq[barcode]++;
        }
        
        // Find the most frequent barcode
        int maxFreq = 0;
        int maxBarcode = 0;
        
        for (auto& [barcode, freq] : barcodeFreq) {
            if (freq > maxFreq) {
                maxFreq = freq;
                maxBarcode = barcode;
            }
        }
        
        // Place the most frequent barcode in even positions
        vector<int> result(n, 0);
        int index = 0;
        
        while (barcodeFreq[maxBarcode] > 0) {
            result[index] = maxBarcode;
            index += 2;
            barcodeFreq[maxBarcode]--;
        }
        
        // Place the rest of the barcodes
        for (auto& [barcode, freq] : barcodeFreq) {
            while (freq > 0) {
                if (index >= n) {
                    index = 1;  // Start filling odd positions
                }
                
                result[index] = barcode;
                index += 2;
                freq--;
            }
        }
        
        return result;
    }
};

// Example 5: Reorganize String to Avoid Consecutive Repeating Characters
class AvoidConsecutiveRepeatingChars {
public:
    string reorganizeString(string s) {
        // Count frequency of each character
        unordered_map<char, int> charFreq;
        for (char c : s) {
            charFreq[c]++;
        }
        
        // Max heap to get the most frequent character
        priority_queue<pair<int, char>> maxHeap;
        for (auto& [c, freq] : charFreq) {
            maxHeap.push({freq, c});
        }
        
        string result = "";
        pair<int, char> prev = {0, '#'};  // To hold the previously used character
        
        while (!maxHeap.empty() || prev.first > 0) {
            if (prev.first > 0 && maxHeap.empty()) {
                // If previous character has remaining occurrences but heap is empty,
                // we can't avoid consecutive characters
                return "";
            }
            
            // Get the most frequent character
            auto [freq, c] = maxHeap.top(); maxHeap.pop();
            result += c;
            
            // Decrease its frequency
            freq--;
            
            // Add the previous character back to the heap if it has remaining occurrences
            if (prev.first > 0) {
                maxHeap.push(prev);
            }
            
            // Update the previous character
            prev = {freq, c};
        }
        
        return result;
    }
};

// Example 6: Schedule Tasks to Maximize Profit
class ScheduleTasksForMaxProfit {
public:
    int maxProfit(vector<int>& profit, vector<int>& deadline) {
        int n = profit.size();
        
        // Create a vector of task indices
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        
        // Sort tasks by profit in descending order
        sort(indices.begin(), indices.end(), [&](int i, int j) {
            return profit[i] > profit[j];
        });
        
        // Find the maximum deadline
        int maxDeadline = *max_element(deadline.begin(), deadline.end());
        
        // Track which time slots are filled
        vector<bool> timeSlot(maxDeadline + 1, false);
        
        int totalProfit = 0;
        
        // Schedule tasks greedily
        for (int i = 0; i < n; i++) {
            int task = indices[i];
            
            // Find the latest available time slot before the deadline
            for (int j = deadline[task]; j > 0; j--) {
                if (!timeSlot[j]) {
                    timeSlot[j] = true;
                    totalProfit += profit[task];
                    break;
                }
            }
        }
        
        return totalProfit;
    }
};

// Main function to demonstrate Task Scheduling (Frequency Based) pattern
int main() {
    // Example 1: Task Scheduler
    cout << "Example 1: Task Scheduler" << endl;
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    
    TaskScheduler ts;
    cout << "Tasks: ['A', 'A', 'A', 'B', 'B', 'B'], Cooling Period: 2" << endl;
    
    int leastTime = ts.leastInterval(tasks, n);
    cout << "Least number of units of time needed: " << leastTime << endl;
    
    // Example 2: Reorganize String
    cout << "\nExample 2: Reorganize String" << endl;
    string s = "aab";
    
    ReorganizeString rs;
    cout << "String: \"aab\"" << endl;
    
    string reorganized = rs.reorganizeString(s);
    cout << "Reorganized string: " << (reorganized.empty() ? "Impossible" : reorganized) << endl;
    
    // Example 3: Distant Barcodes
    cout << "\nExample 3: Distant Barcodes" << endl;
    vector<int> barcodes = {1, 1, 1, 2, 2, 2};
    
    DistantBarcodes db;
    cout << "Barcodes: [1, 1, 1, 2, 2, 2]" << endl;
    
    vector<int> rearrangedBarcodes = db.rearrangeBarcodes(barcodes);
    cout << "Rearranged barcodes: ";
    for (int barcode : rearrangedBarcodes) {
        cout << barcode << " ";
    }
    cout << endl;
    
    // Example 4: Avoid Consecutive Repeating Characters
    cout << "\nExample 4: Avoid Consecutive Repeating Characters" << endl;
    string s2 = "aaab";
    
    AvoidConsecutiveRepeatingChars acrc;
    cout << "String: \"aaab\"" << endl;
    
    string rearranged = acrc.reorganizeString(s2);
    cout << "Rearranged string: " << (rearranged.empty() ? "Impossible" : rearranged) << endl;
    
    // Example 5: Schedule Tasks for Maximum Profit
    cout << "\nExample 5: Schedule Tasks for Maximum Profit" << endl;
    vector<int> profit = {50, 10, 15, 30};
    vector<int> deadline = {2, 1, 2, 1};
    
    ScheduleTasksForMaxProfit stfmp;
    cout << "Profits: [50, 10, 15, 30]" << endl;
    cout << "Deadlines: [2, 1, 2, 1]" << endl;
    
    int maxProfit = stfmp.maxProfit(profit, deadline);
    cout << "Maximum profit: " << maxProfit << endl;
    
    return 0;
}
