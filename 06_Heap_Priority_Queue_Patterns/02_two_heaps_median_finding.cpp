/**
 * Pattern: Heap - Two Heaps for Median Finding
 * 
 * Description:
 * This pattern uses two heaps to efficiently find the median of a stream of numbers.
 * We maintain a max heap for the smaller half of the elements and a min heap for the
 * larger half. This allows O(1) access to the median element(s) and O(log n) insertions.
 * 
 * Time Complexity: 
 * - O(log n) for adding a number to the heaps
 * - O(1) for finding the median
 * 
 * Space Complexity: O(n) for storing all elements across both heaps
 * 
 * When to use:
 * - Finding the median from a stream of data
 * - Balancing two groups of elements with specific constraints
 * - Problems involving keeping track of two halves of sorted data
 * - Calculating running medians or mid-points
 * 
 * LeetCode Problems:
 * - 295. Find Median from Data Stream
 * - 480. Sliding Window Median
 * - 1825. Finding MK Average
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <functional>

using namespace std;

// Example 1: Find Median from Data Stream
// LeetCode 295: https://leetcode.com/problems/find-median-from-data-stream/
class MedianFinder {
private:
    // Max heap for the smaller half of elements
    priority_queue<int> maxHeap;
    
    // Min heap for the larger half of elements
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder() {
        // Constructor
    }
    
    void addNum(int num) {
        // Strategy:
        // 1. Add to max heap first
        // 2. Balance by moving largest element from max heap to min heap
        // 3. If heaps become unbalanced, move one element back
        
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance the heaps (ensure max heap has n/2 or n/2+1 elements)
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            // Even number of elements, median is average of two middle elements
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            // Odd number of elements, median is in max heap
            return maxHeap.top();
        }
    }
};

// Example 2: Sliding Window Median
// LeetCode 480: https://leetcode.com/problems/sliding-window-median/
class SlidingWindowMedian {
private:
    // Using multisets instead of heaps for easier removal
    multiset<int> smallHalf; // Acts like max heap
    multiset<int> largeHalf; // Acts like min heap
    
    // Function to balance both halves
    void balance() {
        // Ensure smallHalf has either equal elements as largeHalf or one more
        if (smallHalf.size() > largeHalf.size() + 1) {
            // Move largest element from smallHalf to largeHalf
            auto it = prev(smallHalf.end());
            largeHalf.insert(*it);
            smallHalf.erase(it);
        } else if (smallHalf.size() < largeHalf.size()) {
            // Move smallest element from largeHalf to smallHalf
            auto it = largeHalf.begin();
            smallHalf.insert(*it);
            largeHalf.erase(it);
        }
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        
        // Process first k elements
        for (int i = 0; i < k; i++) {
            insert(nums[i]);
        }
        
        // Calculate and store first median
        result.push_back(getMedian(k));
        
        // Process rest of the elements with sliding window
        for (int i = k; i < nums.size(); i++) {
            // Remove leftmost element from window
            remove(nums[i - k]);
            
            // Add new element to window
            insert(nums[i]);
            
            // Calculate median for current window
            result.push_back(getMedian(k));
        }
        
        return result;
    }
    
    // Insert a number into the appropriate half
    void insert(int num) {
        if (smallHalf.empty() || num <= *smallHalf.rbegin()) {
            smallHalf.insert(num);
        } else {
            largeHalf.insert(num);
        }
        
        // Balance halves
        balance();
    }
    
    // Remove a number from the appropriate half
    void remove(int num) {
        if (num <= *smallHalf.rbegin()) {
            smallHalf.erase(smallHalf.find(num));
        } else {
            largeHalf.erase(largeHalf.find(num));
        }
        
        // Balance halves
        balance();
    }
    
    // Get the median based on the number of elements
    double getMedian(int k) {
        if (k % 2 == 0) {
            // Even number of elements
            return (*smallHalf.rbegin() + *largeHalf.begin()) / 2.0;
        } else {
            // Odd number of elements
            return *smallHalf.rbegin();
        }
    }
};

// Example 3: Finding MK Average
// LeetCode 1825: https://leetcode.com/problems/finding-mk-average/
class MKAverage {
private:
    int m, k;
    queue<int> stream; // Queue to keep track of elements in the window
    
    // Three multisets to divide the data into three parts:
    // - bottom k elements
    // - middle m-2k elements (used for average)
    // - top k elements
    multiset<int> small;   // bottom k elements
    multiset<int> middle;  // middle m-2k elements
    multiset<int> large;   // top k elements
    
    // Track sum of middle elements for efficient average calculation
    long long middleSum;
    
    // Balance sets after insertion or removal
    void balance() {
        // Ensure small has exactly k elements (or m if m < k)
        while (small.size() > k) {
            // Move largest element from small to middle
            auto it = prev(small.end());
            middle.insert(*it);
            middleSum += *it;
            small.erase(it);
        }
        
        // Ensure large has exactly k elements (or m - small.size() if m < 2*k)
        while (large.size() > k) {
            // Move smallest element from large to middle
            auto it = large.begin();
            middle.insert(*it);
            middleSum += *it;
            large.erase(it);
        }
        
        // Ensure middle doesn't have elements that should be in small
        while (!middle.empty() && !small.empty() && *middle.begin() < *small.rbegin()) {
            // Swap smallest element from middle with largest from small
            auto smallIt = prev(small.end());
            auto middleIt = middle.begin();
            
            middleSum = middleSum - *middleIt + *smallIt;
            
            middle.insert(*smallIt);
            small.erase(smallIt);
            small.insert(*middleIt);
            middle.erase(middleIt);
        }
        
        // Ensure middle doesn't have elements that should be in large
        while (!middle.empty() && !large.empty() && *middle.rbegin() > *large.begin()) {
            // Swap largest element from middle with smallest from large
            auto middleIt = prev(middle.end());
            auto largeIt = large.begin();
            
            middleSum = middleSum - *middleIt + *largeIt;
            
            middle.insert(*largeIt);
            large.erase(largeIt);
            large.insert(*middleIt);
            middle.erase(middleIt);
        }
    }

public:
    MKAverage(int m, int k) : m(m), k(k), middleSum(0) {
        // Initialize
    }
    
    void addElement(int num) {
        // Add number to stream
        stream.push(num);
        
        // Determine which set to insert into
        if (small.empty() || num <= *small.rbegin()) {
            small.insert(num);
        } else if (large.empty() || num >= *large.begin()) {
            large.insert(num);
        } else {
            middle.insert(num);
            middleSum += num;
        }
        
        // Balance sets
        balance();
        
        // Remove oldest element if stream size exceeds m
        if (stream.size() > m) {
            int toRemove = stream.front();
            stream.pop();
            
            if (small.find(toRemove) != small.end()) {
                small.erase(small.find(toRemove));
            } else if (large.find(toRemove) != large.end()) {
                large.erase(large.find(toRemove));
            } else {
                middle.erase(middle.find(toRemove));
                middleSum -= toRemove;
            }
            
            // Balance sets after removal
            balance();
        }
    }
    
    int calculateMKAverage() {
        // If stream has less than m elements, return -1
        if (stream.size() < m) {
            return -1;
        }
        
        // Return average of middle elements
        return (int)(middleSum / (m - 2 * k));
    }
};

// Example 4: Simple Running Median Tracker
class RunningMedianTracker {
private:
    // Max heap for the smaller half of elements
    priority_queue<int> maxHeap;
    
    // Min heap for the larger half of elements
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    // Add a new number and maintain balance
    void addNumber(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Rebalance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    // Get current median
    double getMedian() {
        if (maxHeap.empty()) {
            return 0; // No elements
        }
        
        if (maxHeap.size() == minHeap.size()) {
            // Even number of elements
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            // Odd number of elements (maxHeap has one more)
            return maxHeap.top();
        }
    }
    
    // Process a vector of numbers and return running medians
    vector<double> computeRunningMedian(const vector<int>& nums) {
        vector<double> result;
        
        // Clear heaps
        while (!maxHeap.empty()) maxHeap.pop();
        while (!minHeap.empty()) minHeap.pop();
        
        // Process each number
        for (int num : nums) {
            addNumber(num);
            result.push_back(getMedian());
        }
        
        return result;
    }
};

// Example 5: Median of Two Sorted Arrays
// LeetCode 4: https://leetcode.com/problems/median-of-two-sorted-arrays/
class MedianOfTwoSortedArrays {
public:
    // Approach 1: Merge and find median (O(m+n) time)
    double findMedianSortedArraysMerge(vector<int>& nums1, vector<int>& nums2) {
        // Merge the arrays
        vector<int> merged;
        int i = 0, j = 0;
        
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] <= nums2[j]) {
                merged.push_back(nums1[i++]);
            } else {
                merged.push_back(nums2[j++]);
            }
        }
        
        // Add remaining elements
        while (i < nums1.size()) {
            merged.push_back(nums1[i++]);
        }
        
        while (j < nums2.size()) {
            merged.push_back(nums2[j++]);
        }
        
        // Find median
        int n = merged.size();
        if (n % 2 == 0) {
            return (merged[n/2 - 1] + merged[n/2]) / 2.0;
        } else {
            return merged[n/2];
        }
    }
    
    // Approach 2: Using two heaps (O(m+n) time, demonstrates the pattern)
    double findMedianSortedArraysHeap(vector<int>& nums1, vector<int>& nums2) {
        // Max heap for the smaller half of elements
        priority_queue<int> maxHeap;
        
        // Min heap for the larger half of elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        // Process all elements from both arrays
        for (int num : nums1) {
            addNum(maxHeap, minHeap, num);
        }
        
        for (int num : nums2) {
            addNum(maxHeap, minHeap, num);
        }
        
        // Calculate median
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            return maxHeap.top();
        }
    }
    
private:
    // Helper function to add a number and maintain balance
    void addNum(priority_queue<int>& maxHeap, 
                priority_queue<int, vector<int>, greater<int>>& minHeap,
                int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
};

// Utility function to print a vector of doubles
void printDoubleVector(const vector<double>& vec) {
    for (double val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function to demonstrate Two Heaps pattern
int main() {
    // Example 1: Find Median from Data Stream
    cout << "Example 1: Find Median from Data Stream" << endl;
    MedianFinder medianFinder;
    
    medianFinder.addNum(1);
    cout << "After adding 1, median is: " << medianFinder.findMedian() << endl;
    
    medianFinder.addNum(2);
    cout << "After adding 2, median is: " << medianFinder.findMedian() << endl;
    
    medianFinder.addNum(3);
    cout << "After adding 3, median is: " << medianFinder.findMedian() << endl;
    
    medianFinder.addNum(4);
    cout << "After adding 4, median is: " << medianFinder.findMedian() << endl;
    
    medianFinder.addNum(5);
    cout << "After adding 5, median is: " << medianFinder.findMedian() << endl;
    
    // Example 2: Sliding Window Median
    cout << "\nExample 2: Sliding Window Median" << endl;
    SlidingWindowMedian swMedian;
    vector<int> nums2 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k2 = 3;
    
    cout << "Array: ";
    for (int num : nums2) cout << num << " ";
    cout << endl;
    
    vector<double> medians = swMedian.medianSlidingWindow(nums2, k2);
    cout << "Sliding window medians (k=" << k2 << "): ";
    printDoubleVector(medians);
    
    // Example 3: MK Average
    cout << "\nExample 3: MK Average" << endl;
    int m3 = 3, k3 = 1;
    MKAverage mkAverage(m3, k3);
    
    cout << "Adding elements 3, 1, 10, 5, 5, 3 to MK Average with m=" << m3 << ", k=" << k3 << endl;
    
    // We need to add m elements before calculating MK average
    mkAverage.addElement(3);
    cout << "MK Average after adding 3: " << mkAverage.calculateMKAverage() << endl;
    
    mkAverage.addElement(1);
    cout << "MK Average after adding 1: " << mkAverage.calculateMKAverage() << endl;
    
    mkAverage.addElement(10);
    cout << "MK Average after adding 10: " << mkAverage.calculateMKAverage() << endl;
    
    mkAverage.addElement(5);
    cout << "MK Average after adding 5: " << mkAverage.calculateMKAverage() << endl;
    
    mkAverage.addElement(5);
    cout << "MK Average after adding 5: " << mkAverage.calculateMKAverage() << endl;
    
    mkAverage.addElement(3);
    cout << "MK Average after adding 3: " << mkAverage.calculateMKAverage() << endl;
    
    // Example 4: Running Median Tracker
    cout << "\nExample 4: Running Median Tracker" << endl;
    RunningMedianTracker runningMedian;
    vector<int> nums4 = {2, 3, 4, 5, 15, 10, 1, 8, 9};
    
    cout << "Array: ";
    for (int num : nums4) cout << num << " ";
    cout << endl;
    
    vector<double> runningMedians = runningMedian.computeRunningMedian(nums4);
    cout << "Running medians: ";
    printDoubleVector(runningMedians);
    
    // Example 5: Median of Two Sorted Arrays
    cout << "\nExample 5: Median of Two Sorted Arrays" << endl;
    vector<int> nums5_1 = {1, 3, 8, 9, 15};
    vector<int> nums5_2 = {7, 11, 18, 19, 21, 25};
    
    MedianOfTwoSortedArrays medianArrays;
    
    cout << "Array 1: ";
    for (int num : nums5_1) cout << num << " ";
    cout << endl;
    
    cout << "Array 2: ";
    for (int num : nums5_2) cout << num << " ";
    cout << endl;
    
    cout << "Median using merge method: " << medianArrays.findMedianSortedArraysMerge(nums5_1, nums5_2) << endl;
    cout << "Median using heap method: " << medianArrays.findMedianSortedArraysHeap(nums5_1, nums5_2) << endl;
    
    return 0;
}
