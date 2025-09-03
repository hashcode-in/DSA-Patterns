/**
 * Pattern: Greedy - Interval Merging/Scheduling
 * 
 * Description:
 * This pattern deals with problems involving intervals with start and end times.
 * The key insight is to sort intervals based on start or end times and make local
 * greedy decisions to achieve a global optimum.
 * 
 * Time Complexity: 
 * - Typically O(n log n) due to the sorting step
 * - Processing sorted intervals is usually O(n)
 * 
 * Space Complexity: O(n) or O(1) depending on whether we modify input in-place
 * 
 * When to use:
 * - Merging overlapping intervals
 * - Finding minimum meeting rooms required
 * - Maximizing the number of non-overlapping intervals
 * - Checking if intervals conflict
 * 
 * LeetCode Problems:
 * - 56. Merge Intervals
 * - 57. Insert Interval
 * - 252. Meeting Rooms
 * - 253. Meeting Rooms II
 * - 435. Non-overlapping Intervals
 * - 986. Interval List Intersections
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Helper function to print intervals
void printIntervals(const vector<vector<int>>& intervals) {
    for (const auto& interval : intervals) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
}

// Example 1: Merge Intervals
// LeetCode 56: https://leetcode.com/problems/merge-intervals/
class MergeIntervals {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Edge case: empty input
        if (intervals.empty()) {
            return {};
        }
        
        // Sort intervals based on start time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); i++) {
            // Get the last interval in our merged list
            vector<int>& last = merged.back();
            
            // Current interval
            int currentStart = intervals[i][0];
            int currentEnd = intervals[i][1];
            
            // If current interval overlaps with the last merged interval, update the end
            if (currentStart <= last[1]) {
                last[1] = max(last[1], currentEnd);
            } else {
                // No overlap, add current interval to merged list
                merged.push_back(intervals[i]);
            }
        }
        
        return merged;
    }
};

// Example 2: Insert Interval
// LeetCode 57: https://leetcode.com/problems/insert-interval/
class InsertInterval {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0, n = intervals.size();
        
        // Add all intervals that come before newInterval
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i++]);
        }
        
        // Merge all overlapping intervals with newInterval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        
        // Add the merged interval
        result.push_back(newInterval);
        
        // Add all intervals that come after newInterval
        while (i < n) {
            result.push_back(intervals[i++]);
        }
        
        return result;
    }
};

// Example 3: Meeting Rooms
// LeetCode 252: https://leetcode.com/problems/meeting-rooms/
class MeetingRooms {
public:
    // Returns true if a person can attend all meetings, false otherwise
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        // Sort by start time
        sort(intervals.begin(), intervals.end());
        
        // Check for any overlapping intervals
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i-1][1]) {
                // Overlap found, can't attend all meetings
                return false;
            }
        }
        
        // No overlaps found
        return true;
    }
};

// Example 4: Meeting Rooms II
// LeetCode 253: https://leetcode.com/problems/meeting-rooms-ii/
class MeetingRoomsII {
public:
    // Returns the minimum number of conference rooms required
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // Edge case: empty input
        if (intervals.empty()) {
            return 0;
        }
        
        // Sort by start time
        sort(intervals.begin(), intervals.end());
        
        // Min heap to track the earliest ending meeting
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        // Add the first meeting's end time
        minHeap.push(intervals[0][1]);
        
        // Process the rest of the meetings
        for (int i = 1; i < intervals.size(); i++) {
            // If the current meeting starts after the earliest ending meeting,
            // we can reuse that room. Remove it from heap.
            if (intervals[i][0] >= minHeap.top()) {
                minHeap.pop();
            }
            
            // Add the current meeting's end time
            minHeap.push(intervals[i][1]);
        }
        
        // The size of the heap tells us the minimum rooms needed
        return minHeap.size();
    }
};

// Example 5: Non-overlapping Intervals
// LeetCode 435: https://leetcode.com/problems/non-overlapping-intervals/
class NonOverlappingIntervals {
public:
    // Returns the minimum number of intervals to remove to make all intervals non-overlapping
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // Edge case: empty input
        if (intervals.empty()) {
            return 0;
        }
        
        // Sort by end time (to maximize the number of intervals we can keep)
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int count = 1;  // Count of non-overlapping intervals
        int end = intervals[0][1];  // End time of last interval added to result
        
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= end) {
                // Current interval doesn't overlap with the last added interval
                count++;
                end = intervals[i][1];
            }
            // If there's an overlap, we skip the current interval (equivalent to removing it)
        }
        
        // Return the number of intervals to remove
        return intervals.size() - count;
    }
};

// Example 6: Interval List Intersections
// LeetCode 986: https://leetcode.com/problems/interval-list-intersections/
class IntervalListIntersections {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        
        while (i < firstList.size() && j < secondList.size()) {
            // Find the intersection
            int startMax = max(firstList[i][0], secondList[j][0]);
            int endMin = min(firstList[i][1], secondList[j][1]);
            
            // If there's an intersection, add it to the result
            if (startMax <= endMin) {
                result.push_back({startMax, endMin});
            }
            
            // Move the pointer of the list with the smaller end time
            if (firstList[i][1] < secondList[j][1]) {
                i++;
            } else {
                j++;
            }
        }
        
        return result;
    }
};

// Example 7: Minimum Number of Arrows to Burst Balloons
// LeetCode 452: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
class MinimumArrows {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }
        
        // Sort by end point
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int arrows = 1;
        int end = points[0][1];
        
        for (int i = 1; i < points.size(); i++) {
            // If the current balloon starts after the end of the previous arrow,
            // we need a new arrow
            if (points[i][0] > end) {
                arrows++;
                end = points[i][1];
            }
            // Otherwise, the current balloon can be burst by the previous arrow
        }
        
        return arrows;
    }
};

// Example 8: Maximum Number of Events That Can Be Attended
// LeetCode 1353: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
class MaximumEvents {
public:
    int maxEvents(vector<vector<int>>& events) {
        // Sort events by start time
        sort(events.begin(), events.end());
        
        // Min heap to keep track of end days
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        int i = 0, n = events.size();
        int day = 0, count = 0;
        
        while (i < n || !minHeap.empty()) {
            // If heap is empty, jump to next event's start day
            if (minHeap.empty()) {
                day = events[i][0];
            }
            
            // Add all events that start on or before the current day
            while (i < n && events[i][0] <= day) {
                minHeap.push(events[i][1]);  // Add end day to heap
                i++;
            }
            
            // Attend the event that ends the earliest
            minHeap.pop();
            count++;
            day++;
            
            // Remove events that have already ended
            while (!minHeap.empty() && minHeap.top() < day) {
                minHeap.pop();
            }
        }
        
        return count;
    }
};

// Main function to demonstrate interval merging/scheduling patterns
int main() {
    // Example 1: Merge Intervals
    cout << "Example 1: Merge Intervals" << endl;
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Input intervals: ";
    printIntervals(intervals);
    
    MergeIntervals mi;
    vector<vector<int>> mergedIntervals = mi.merge(intervals);
    
    cout << "Merged intervals: ";
    printIntervals(mergedIntervals);
    
    // Example 2: Insert Interval
    cout << "\nExample 2: Insert Interval" << endl;
    vector<vector<int>> intervals2 = {{1, 3}, {6, 9}};
    vector<int> newInterval = {2, 5};
    cout << "Input intervals: ";
    printIntervals(intervals2);
    cout << "New interval: [" << newInterval[0] << "," << newInterval[1] << "]" << endl;
    
    InsertInterval ii;
    vector<vector<int>> insertResult = ii.insert(intervals2, newInterval);
    
    cout << "Result after insertion: ";
    printIntervals(insertResult);
    
    // Example 3: Meeting Rooms
    cout << "\nExample 3: Meeting Rooms" << endl;
    vector<vector<int>> meetings = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Meeting times: ";
    printIntervals(meetings);
    
    MeetingRooms mr;
    bool canAttend = mr.canAttendMeetings(meetings);
    
    cout << "Can attend all meetings: " << (canAttend ? "true" : "false") << endl;
    
    // Example 4: Meeting Rooms II
    cout << "\nExample 4: Meeting Rooms II" << endl;
    vector<vector<int>> meetings2 = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Meeting times: ";
    printIntervals(meetings2);
    
    MeetingRoomsII mr2;
    int minRooms = mr2.minMeetingRooms(meetings2);
    
    cout << "Minimum number of meeting rooms required: " << minRooms << endl;
    
    // Example 5: Non-overlapping Intervals
    cout << "\nExample 5: Non-overlapping Intervals" << endl;
    vector<vector<int>> intervals5 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Intervals: ";
    printIntervals(intervals5);
    
    NonOverlappingIntervals noi;
    int minRemove = noi.eraseOverlapIntervals(intervals5);
    
    cout << "Minimum intervals to remove: " << minRemove << endl;
    
    // Example 6: Interval List Intersections
    cout << "\nExample 6: Interval List Intersections" << endl;
    vector<vector<int>> firstList = {{0, 2}, {5, 10}, {13, 23}, {24, 25}};
    vector<vector<int>> secondList = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};
    
    cout << "First list: ";
    printIntervals(firstList);
    cout << "Second list: ";
    printIntervals(secondList);
    
    IntervalListIntersections ili;
    vector<vector<int>> intersections = ili.intervalIntersection(firstList, secondList);
    
    cout << "Interval intersections: ";
    printIntervals(intersections);
    
    // Example 7: Minimum Number of Arrows to Burst Balloons
    cout << "\nExample 7: Minimum Number of Arrows to Burst Balloons" << endl;
    vector<vector<int>> balloons = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    cout << "Balloon intervals: ";
    printIntervals(balloons);
    
    MinimumArrows ma;
    int arrows = ma.findMinArrowShots(balloons);
    
    cout << "Minimum arrows needed: " << arrows << endl;
    
    // Example 8: Maximum Number of Events That Can Be Attended
    cout << "\nExample 8: Maximum Number of Events That Can Be Attended" << endl;
    vector<vector<int>> events = {{1, 2}, {2, 3}, {3, 4}, {1, 2}};
    cout << "Events (start, end): ";
    printIntervals(events);
    
    MaximumEvents me;
    int maxEvents = me.maxEvents(events);
    
    cout << "Maximum events that can be attended: " << maxEvents << endl;
    
    return 0;
}
