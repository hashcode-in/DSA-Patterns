/**
 * Pattern: Heap - Scheduling / Minimum Cost (Greedy with Priority Queue)
 * 
 * Description:
 * This pattern combines greedy algorithms with priority queues to make optimal
 * scheduling decisions or allocate resources efficiently. It works by selecting
 * the most optimal choice at each step using a priority queue.
 * 
 * Time Complexity: 
 * - Typically O(n log n) where n is the number of elements
 * - Insertion and extraction from heap take O(log n)
 * - Processing all elements takes O(n log n)
 * 
 * Space Complexity: O(n) for storing elements in the heap
 * 
 * When to use:
 * - Task scheduling problems
 * - Resource allocation problems
 * - Meeting room scheduling
 * - Jobs with deadlines and profits
 * - Minimizing waiting time or maximizing throughput
 * 
 * LeetCode Problems:
 * - 253. Meeting Rooms II
 * - 621. Task Scheduler
 * - 767. Reorganize String
 * - 857. Minimum Cost to Hire K Workers
 * - 1642. Furthest Building You Can Reach
 * - 1834. Single-Threaded CPU
 * - 1882. Process Tasks Using Servers
 * - 2402. Meeting Rooms III
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <numeric>
#include <set>
#include <cfloat> // For DBL_MAX

using namespace std;

// Example 1: Meeting Rooms II
// LeetCode 253: https://leetcode.com/problems/meeting-rooms-ii/
class MeetingRoomsII {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        // Sort intervals based on start time
        sort(intervals.begin(), intervals.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });
        
        // Min heap to track end times of active meetings
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        // Add the end time of the first meeting
        minHeap.push(intervals[0][1]);
        
        // Process the rest of the meetings
        for (int i = 1; i < intervals.size(); i++) {
            // If the room is free (current meeting starts after the earliest ending meeting)
            if (intervals[i][0] >= minHeap.top()) {
                // Remove the earliest ending meeting
                minHeap.pop();
            }
            
            // Add the current meeting's end time
            minHeap.push(intervals[i][1]);
        }
        
        // The size of the heap represents the minimum number of rooms required
        return minHeap.size();
    }
};

// Example 2: Task Scheduler
// LeetCode 621: https://leetcode.com/problems/task-scheduler/
class TaskScheduler {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (tasks.empty()) return 0;
        if (n == 0) return tasks.size(); // No cooldown required
        
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
        
        // Process tasks until the heap is empty
        while (!maxHeap.empty()) {
            // Store tasks that need to cool down
            vector<int> temp;
            
            // Try to schedule tasks within a single cycle (of length n+1)
            for (int i = 0; i <= n; i++) {
                if (!maxHeap.empty()) {
                    int freq = maxHeap.top();
                    maxHeap.pop();
                    
                    // If there are remaining instances of this task, store for later
                    if (freq > 1) {
                        temp.push_back(freq - 1);
                    }
                }
                
                cycles++; // Increment cycle count
                
                // If both heap and temp are empty, we're done
                if (maxHeap.empty() && temp.empty()) break;
                
                // If we've processed n+1 tasks (one cycle) or run out of tasks but still have more coming,
                // we need to wait for the cooldown period to complete
                if (i == n || (maxHeap.empty() && !temp.empty())) {
                    // If we still have tasks in temp, we can't break yet
                    if (!temp.empty()) {
                        // Move tasks from temp back to heap after cooldown
                        for (int freq : temp) {
                            maxHeap.push(freq);
                        }
                        temp.clear();
                    }
                }
            }
        }
        
        return cycles;
    }
};

// Example 3: Reorganize String
// LeetCode 767: https://leetcode.com/problems/reorganize-string/
class ReorganizeString {
public:
    string reorganizeString(string s) {
        if (s.empty()) return "";
        
        // Count frequency of each character
        unordered_map<char, int> charFreq;
        for (char c : s) {
            charFreq[c]++;
            // If any character appears more than half the time, it's impossible to reorganize
            if (charFreq[c] > (s.size() + 1) / 2) return "";
        }
        
        // Max heap to store characters by frequency
        auto compare = [](const pair<char, int>& a, const pair<char, int>& b) {
            return a.second < b.second; // Max heap by frequency
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(compare)> maxHeap(compare);
        
        for (auto& [ch, freq] : charFreq) {
            maxHeap.push({ch, freq});
        }
        
        string result;
        
        // Process characters to ensure no adjacent duplicates
        while (maxHeap.size() >= 2) {
            // Take the two most frequent characters
            auto [char1, freq1] = maxHeap.top();
            maxHeap.pop();
            auto [char2, freq2] = maxHeap.top();
            maxHeap.pop();
            
            // Append to result
            result.push_back(char1);
            result.push_back(char2);
            
            // Decrement frequencies and push back if needed
            if (--freq1 > 0) maxHeap.push({char1, freq1});
            if (--freq2 > 0) maxHeap.push({char2, freq2});
        }
        
        // If there's one character left
        if (!maxHeap.empty()) {
            auto [ch, freq] = maxHeap.top();
            if (freq > 1) return ""; // Can't reorganize if frequency > 1
            result.push_back(ch);
        }
        
        return result;
    }
};

// Example 4: Minimum Cost to Hire K Workers
// LeetCode 857: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/
class MinimumCostToHireKWorkers {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        
        // Create a vector of workers (quality, wage/quality ratio)
        vector<pair<int, double>> workers;
        for (int i = 0; i < n; i++) {
            workers.push_back({quality[i], (double)wage[i] / quality[i]});
        }
        
        // Sort workers by wage/quality ratio (ascending)
        sort(workers.begin(), workers.end(), 
             [](const pair<int, double>& a, const pair<int, double>& b) {
                 return a.second < b.second;
             });
        
        // Max heap to keep track of worker qualities
        priority_queue<int> maxHeap;
        int totalQuality = 0;
        double minCost = DBL_MAX;
        
        // Process workers in order of increasing wage/quality ratio
        for (auto& [q, ratio] : workers) {
            maxHeap.push(q);
            totalQuality += q;
            
            // If we have more than k workers, remove the one with the highest quality
            if (maxHeap.size() > k) {
                totalQuality -= maxHeap.top();
                maxHeap.pop();
            }
            
            // If we have exactly k workers, calculate the cost
            if (maxHeap.size() == k) {
                // Cost = ratio * sum of qualities
                double cost = ratio * totalQuality;
                minCost = min(minCost, cost);
            }
        }
        
        return minCost;
    }
};

// Example 5: Furthest Building You Can Reach
// LeetCode 1642: https://leetcode.com/problems/furthest-building-you-can-reach/
class FurthestBuildingYouCanReach {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        // Min heap to keep track of the ladders used (for the largest height differences)
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for (int i = 0; i < heights.size() - 1; i++) {
            int diff = heights[i + 1] - heights[i];
            
            // If next building is not higher, no resources needed
            if (diff <= 0) continue;
            
            // Add this climb to the heap (allocate a ladder)
            minHeap.push(diff);
            
            // If we've used more ladders than available, use bricks for the smallest climb
            if (minHeap.size() > ladders) {
                bricks -= minHeap.top();
                minHeap.pop();
            }
            
            // If we're out of bricks, this is the furthest we can go
            if (bricks < 0) return i;
        }
        
        // We can reach the last building
        return heights.size() - 1;
    }
};

// Example 6: Single-Threaded CPU
// LeetCode 1834: https://leetcode.com/problems/single-threaded-cpu/
class SingleThreadedCPU {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        
        // Add index to each task for tracking original order
        vector<vector<int>> indexedTasks;
        for (int i = 0; i < n; i++) {
            indexedTasks.push_back({tasks[i][0], tasks[i][1], i}); // {enqueueTime, processingTime, index}
        }
        
        // Sort by enqueue time
        sort(indexedTasks.begin(), indexedTasks.end());
        
        // Min heap ordered by processing time, then by index
        auto compare = [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return a.second > b.second; // If processing times are equal, smaller index first
            return a.first > b.first; // Smaller processing time first
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);
        
        vector<int> result;
        long long currentTime = 0;
        int taskIndex = 0;
        
        while (taskIndex < n || !minHeap.empty()) {
            if (minHeap.empty() && taskIndex < n) {
                // Jump to the next task's enqueue time if CPU is idle
                currentTime = max(currentTime, (long long)indexedTasks[taskIndex][0]);
            }
            
            // Add all tasks that are available at the current time
            while (taskIndex < n && indexedTasks[taskIndex][0] <= currentTime) {
                minHeap.push({indexedTasks[taskIndex][1], indexedTasks[taskIndex][2]});
                taskIndex++;
            }
            
            // Process the next task
            auto [processingTime, index] = minHeap.top();
            minHeap.pop();
            
            // Update current time
            currentTime += processingTime;
            
            // Add task index to result
            result.push_back(index);
        }
        
        return result;
    }
};

// Example 7: Meeting Rooms III
// LeetCode 2402: https://leetcode.com/problems/meeting-rooms-iii/
class MeetingRoomsIII {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Sort meetings by start time
        sort(meetings.begin(), meetings.end());
        
        // Min heap for available rooms (room_id)
        priority_queue<int, vector<int>, greater<int>> availableRooms;
        
        // Initialize all rooms as available
        for (int i = 0; i < n; i++) {
            availableRooms.push(i);
        }
        
        // Min heap for busy rooms (end_time, room_id)
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> busyRooms;
        
        // Count of meetings held in each room
        vector<int> roomCount(n, 0);
        
        // Process each meeting
        for (auto& meeting : meetings) {
            long long start = meeting[0];
            long long end = meeting[1];
            
            // Free up any rooms that have finished by the current meeting's start time
            while (!busyRooms.empty() && busyRooms.top().first <= start) {
                availableRooms.push(busyRooms.top().second);
                busyRooms.pop();
            }
            
            if (!availableRooms.empty()) {
                // If there's an available room, use it
                int roomId = availableRooms.top();
                availableRooms.pop();
                busyRooms.push({end, roomId});
                roomCount[roomId]++;
            } else {
                // All rooms are busy, wait for the earliest finishing meeting
                auto [earliestEnd, roomId] = busyRooms.top();
                busyRooms.pop();
                busyRooms.push({earliestEnd + (end - start), roomId});
                roomCount[roomId]++;
            }
        }
        
        // Find the room that held the most meetings
        int maxCount = 0;
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            if (roomCount[i] > maxCount) {
                maxCount = roomCount[i];
                result = i;
            }
        }
        
        return result;
    }
};

// Example 8: Process Tasks Using Servers
// LeetCode 1882: https://leetcode.com/problems/process-tasks-using-servers/
class ProcessTasksUsingServers {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        // Min heap for free servers (weight, index)
        auto compareWeight = [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return a.second > b.second; // If weights are equal, smaller index first
            return a.first > b.first; // Smaller weight first
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compareWeight)> freeServers(compareWeight);
        
        // Min heap for busy servers (end_time, weight, index)
        auto compareTime = [](const tuple<long long, int, int>& a, const tuple<long long, int, int>& b) {
            if (get<0>(a) == get<0>(b)) {
                if (get<1>(a) == get<1>(b)) {
                    return get<2>(a) > get<2>(b); // If end times and weights are equal, smaller index first
                }
                return get<1>(a) > get<1>(b); // If end times are equal, smaller weight first
            }
            return get<0>(a) > get<0>(b); // Earlier end time first
        };
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, decltype(compareTime)> busyServers(compareTime);
        
        // Initialize all servers as free
        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }
        
        vector<int> result(m);
        long long currentTime = 0;
        
        for (int i = 0; i < m; i++) {
            currentTime = max(currentTime, (long long)i); // Time starts at i for task i
            
            // Free up servers that have finished by the current time
            while (!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                auto [_, weight, index] = busyServers.top();
                busyServers.pop();
                freeServers.push({weight, index});
            }
            
            // If no free servers, wait for the next server to become available
            if (freeServers.empty()) {
                auto [endTime, weight, index] = busyServers.top();
                busyServers.pop();
                currentTime = endTime; // Jump to the time when a server becomes free
                freeServers.push({weight, index});
                
                // Free up any other servers that finish at the same time
                while (!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                    auto [_, w, idx] = busyServers.top();
                    busyServers.pop();
                    freeServers.push({w, idx});
                }
            }
            
            // Assign the current task to the free server with lowest weight/index
            auto [weight, index] = freeServers.top();
            freeServers.pop();
            
            // Record which server processed this task
            result[i] = index;
            
            // Add the server to the busy heap
            long long endTime = currentTime + tasks[i];
            busyServers.push({endTime, weight, index});
        }
        
        return result;
    }
};

// Main function to demonstrate Scheduling / Minimum Cost pattern
int main() {
    // Example 1: Meeting Rooms II
    cout << "Example 1: Meeting Rooms II" << endl;
    vector<vector<int>> intervals = {{0, 30}, {5, 10}, {15, 20}};
    
    cout << "Meetings: ";
    for (auto& interval : intervals) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
    
    MeetingRoomsII solution1;
    cout << "Minimum meeting rooms required: " << solution1.minMeetingRooms(intervals) << endl;
    
    // Example 2: Task Scheduler
    cout << "\nExample 2: Task Scheduler" << endl;
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    
    cout << "Tasks: ";
    for (char task : tasks) cout << task << " ";
    cout << endl;
    cout << "Cooldown: " << n << endl;
    
    TaskScheduler solution2;
    cout << "Least intervals needed: " << solution2.leastInterval(tasks, n) << endl;
    
    // Example 3: Reorganize String
    cout << "\nExample 3: Reorganize String" << endl;
    string s = "aab";
    
    cout << "Input string: " << s << endl;
    
    ReorganizeString solution3;
    string reorganized = solution3.reorganizeString(s);
    cout << "Reorganized string: " << reorganized << endl;
    
    // Example 4: Minimum Cost to Hire K Workers
    cout << "\nExample 4: Minimum Cost to Hire K Workers" << endl;
    vector<int> quality = {10, 20, 5};
    vector<int> wage = {70, 50, 30};
    int k = 2;
    
    cout << "Quality: ";
    for (int q : quality) cout << q << " ";
    cout << endl;
    cout << "Wage: ";
    for (int w : wage) cout << w << " ";
    cout << endl;
    cout << "K: " << k << endl;
    
    MinimumCostToHireKWorkers solution4;
    cout << "Minimum cost to hire " << k << " workers: " << solution4.mincostToHireWorkers(quality, wage, k) << endl;
    
    // Example 5: Furthest Building You Can Reach
    cout << "\nExample 5: Furthest Building You Can Reach" << endl;
    vector<int> heights = {4, 2, 7, 6, 9, 14, 12};
    int bricks = 5;
    int ladders = 1;
    
    cout << "Heights: ";
    for (int h : heights) cout << h << " ";
    cout << endl;
    cout << "Bricks: " << bricks << ", Ladders: " << ladders << endl;
    
    FurthestBuildingYouCanReach solution5;
    cout << "Furthest building index: " << solution5.furthestBuilding(heights, bricks, ladders) << endl;
    
    // Example 6: Single-Threaded CPU
    cout << "\nExample 6: Single-Threaded CPU" << endl;
    vector<vector<int>> tasks6 = {{1, 2}, {2, 4}, {3, 2}, {4, 1}};
    
    cout << "Tasks (enqueue time, processing time): ";
    for (auto& task : tasks6) {
        cout << "[" << task[0] << "," << task[1] << "] ";
    }
    cout << endl;
    
    SingleThreadedCPU solution6;
    vector<int> order = solution6.getOrder(tasks6);
    
    cout << "Order of execution: ";
    for (int idx : order) cout << idx << " ";
    cout << endl;
    
    // Example 7: Meeting Rooms III
    cout << "\nExample 7: Meeting Rooms III" << endl;
    int rooms = 2;
    vector<vector<int>> meetings7 = {{0, 10}, {1, 5}, {2, 7}, {3, 4}};
    
    cout << "Meetings (start, end): ";
    for (auto& meeting : meetings7) {
        cout << "[" << meeting[0] << "," << meeting[1] << "] ";
    }
    cout << endl;
    cout << "Number of rooms: " << rooms << endl;
    
    MeetingRoomsIII solution7;
    cout << "Most booked room: " << solution7.mostBooked(rooms, meetings7) << endl;
    
    // Example 8: Process Tasks Using Servers
    cout << "\nExample 8: Process Tasks Using Servers" << endl;
    vector<int> servers8 = {3, 3, 2};
    vector<int> tasks8 = {1, 2, 3, 2, 1, 2};
    
    cout << "Servers (weight): ";
    for (int s : servers8) cout << s << " ";
    cout << endl;
    
    cout << "Tasks (processing time): ";
    for (int t : tasks8) cout << t << " ";
    cout << endl;
    
    ProcessTasksUsingServers solution8;
    vector<int> assignment = solution8.assignTasks(servers8, tasks8);
    
    cout << "Task assignments (server index): ";
    for (int a : assignment) cout << a << " ";
    cout << endl;
    
    return 0;
}
