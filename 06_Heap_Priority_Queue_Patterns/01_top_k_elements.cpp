/**
 * Pattern: Heap - Top K Elements (Selection/Frequency)
 * 
 * Description:
 * This pattern is used to find the k largest or smallest elements in a collection or to handle
 * elements based on their frequency. It leverages a heap (priority queue) to efficiently maintain
 * the top/bottom k elements as we process the input.
 * 
 * Time Complexity: 
 * - O(n log k) for processing n elements with a heap of size k
 * - O(k log k) for extracting all k elements from the heap
 * 
 * Space Complexity: O(k) for storing k elements in the heap
 * 
 * When to use:
 * - Finding k largest/smallest elements
 * - Finding most/least frequent elements
 * - Finding elements with highest/lowest priority or value
 * - Processing top k elements by any metric
 * 
 * LeetCode Problems:
 * - 215. Kth Largest Element in an Array
 * - 347. Top K Frequent Elements
 * - 451. Sort Characters By Frequency
 * - 506. Relative Ranks
 * - 703. Kth Largest Element in a Stream
 * - 973. K Closest Points to Origin
 * - 1046. Last Stone Weight
 * - 2558. Take Gifts From the Richest Pile
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Example 1: Kth Largest Element in an Array
// LeetCode 215: https://leetcode.com/problems/kth-largest-element-in-an-array/
class KthLargestElement {
public:
    // Approach 1: Using a Min Heap
    int findKthLargest(vector<int>& nums, int k) {
        // Create a min heap to keep track of the k largest elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        // Process each number in the array
        for (int num : nums) {
            // Add the number to the heap
            minHeap.push(num);
            
            // If the heap size exceeds k, remove the smallest element
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // The top of the heap is the kth largest element
        return minHeap.top();
    }
    
    // Approach 2: Using QuickSelect (more efficient)
    int findKthLargestQuickSelect(vector<int>& nums, int k) {
        // Convert to 0-based index (kth largest = (n-k)th smallest)
        int targetIndex = nums.size() - k;
        return quickSelect(nums, 0, nums.size() - 1, targetIndex);
    }
    
private:
    int quickSelect(vector<int>& nums, int left, int right, int targetIndex) {
        if (left == right) return nums[left];
        
        // Choose a pivot
        int pivotIndex = partition(nums, left, right);
        
        if (pivotIndex == targetIndex) {
            return nums[pivotIndex];
        } else if (pivotIndex > targetIndex) {
            // Search in the left part
            return quickSelect(nums, left, pivotIndex - 1, targetIndex);
        } else {
            // Search in the right part
            return quickSelect(nums, pivotIndex + 1, right, targetIndex);
        }
    }
    
    int partition(vector<int>& nums, int left, int right) {
        // Choose pivot (can be optimized further)
        int pivot = nums[right];
        int i = left;
        
        for (int j = left; j < right; j++) {
            if (nums[j] <= pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        
        swap(nums[i], nums[right]);
        return i;
    }
};

// Example 2: Top K Frequent Elements
// LeetCode 347: https://leetcode.com/problems/top-k-frequent-elements/
class TopKFrequentElements {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Count frequency of each number
        unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }
        
        // Create a min heap based on frequency
        // We use a custom comparison function to compare based on frequency
        auto compare = [&frequencyMap](int a, int b) {
            return frequencyMap[a] > frequencyMap[b]; // Use > for min heap
        };
        
        priority_queue<int, vector<int>, decltype(compare)> minHeap(compare);
        
        // Add elements to the heap
        for (auto& [num, freq] : frequencyMap) {
            minHeap.push(num);
            
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // Extract the result
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        
        // Reverse to get from most frequent to least frequent
        reverse(result.begin(), result.end());
        
        return result;
    }
};

// Example 3: Sort Characters By Frequency
// LeetCode 451: https://leetcode.com/problems/sort-characters-by-frequency/
class SortCharactersByFrequency {
public:
    string frequencySort(string s) {
        // Count frequency of each character
        unordered_map<char, int> frequencyMap;
        for (char c : s) {
            frequencyMap[c]++;
        }
        
        // Create a max heap based on frequency
        auto compare = [&frequencyMap](char a, char b) {
            return frequencyMap[a] < frequencyMap[b]; // Use < for max heap
        };
        
        priority_queue<char, vector<char>, decltype(compare)> maxHeap(compare);
        
        // Add characters to the heap
        for (auto& [ch, freq] : frequencyMap) {
            maxHeap.push(ch);
        }
        
        // Build the result string
        string result = "";
        while (!maxHeap.empty()) {
            char c = maxHeap.top();
            maxHeap.pop();
            
            // Append the character freq times
            result.append(frequencyMap[c], c);
        }
        
        return result;
    }
};

// Example 4: K Closest Points to Origin
// LeetCode 973: https://leetcode.com/problems/k-closest-points-to-origin/
class KClosestPointsToOrigin {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Create a max heap based on distance to origin
        // We use a max heap because we want to discard points that are farther away
        auto compare = [](const vector<int>& a, const vector<int>& b) {
            return calculateDistanceSquared(a) < calculateDistanceSquared(b); // Use < for max heap
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> maxHeap(compare);
        
        // Process each point
        for (const auto& point : points) {
            maxHeap.push(point);
            
            if (maxHeap.size() > k) {
                maxHeap.pop();
            }
        }
        
        // Extract the result
        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            result.push_back(maxHeap.top());
            maxHeap.pop();
        }
        
        return result;
    }
    
private:
    // Calculate the squared Euclidean distance to origin
    static int calculateDistanceSquared(const vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }
};

// Example 5: Kth Largest Element in a Stream
// LeetCode 703: https://leetcode.com/problems/kth-largest-element-in-a-stream/
class KthLargestElementInStream {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min heap to keep k largest elements
    int k;

public:
    KthLargestElementInStream(int k, vector<int>& nums) {
        this->k = k;
        
        // Initialize with the elements from nums
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        // Add the new value
        minHeap.push(val);
        
        // If the heap size exceeds k, remove the smallest element
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        
        // Return the kth largest element
        return minHeap.top();
    }
};

// Example 6: Last Stone Weight
// LeetCode 1046: https://leetcode.com/problems/last-stone-weight/
class LastStoneWeight {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Create a max heap to always pick the two heaviest stones
        priority_queue<int> maxHeap(stones.begin(), stones.end());
        
        // Process until only one or zero stones remain
        while (maxHeap.size() > 1) {
            int stone1 = maxHeap.top();
            maxHeap.pop();
            
            int stone2 = maxHeap.top();
            maxHeap.pop();
            
            // If they're not equal, push the remainder back
            if (stone1 != stone2) {
                maxHeap.push(stone1 - stone2);
            }
        }
        
        // Return the last stone's weight or 0 if no stones remain
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};

// Example 7: Relative Ranks
// LeetCode 506: https://leetcode.com/problems/relative-ranks/
class RelativeRanks {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> result(n);
        
        // Create a max heap with indices based on scores
        priority_queue<pair<int, int>> maxHeap; // (score, index)
        
        for (int i = 0; i < n; i++) {
            maxHeap.push({score[i], i});
        }
        
        // Assign medals and ranks
        int rank = 1;
        while (!maxHeap.empty()) {
            int index = maxHeap.top().second;
            maxHeap.pop();
            
            if (rank == 1) {
                result[index] = "Gold Medal";
            } else if (rank == 2) {
                result[index] = "Silver Medal";
            } else if (rank == 3) {
                result[index] = "Bronze Medal";
            } else {
                result[index] = to_string(rank);
            }
            
            rank++;
        }
        
        return result;
    }
};

// Example 8: Take Gifts From the Richest Pile
// LeetCode 2558: https://leetcode.com/problems/take-gifts-from-the-richest-pile/
class TakeGiftsFromRichestPile {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        // Create a max heap to always pick the richest pile
        priority_queue<int> maxHeap(gifts.begin(), gifts.end());
        
        // Process for k seconds
        while (k > 0 && !maxHeap.empty()) {
            int richestPile = maxHeap.top();
            maxHeap.pop();
            
            // Take square root and put back
            int taken = floor(sqrt(richestPile));
            maxHeap.push(taken);
            
            k--;
        }
        
        // Calculate the sum of remaining gifts
        long long sum = 0;
        while (!maxHeap.empty()) {
            sum += maxHeap.top();
            maxHeap.pop();
        }
        
        return sum;
    }
};

// Example 9: Find K Pairs with Smallest Sums
// LeetCode 373: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
class FindKPairsWithSmallestSums {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty() || k <= 0) return result;
        
        // Create a min heap based on the sum of pairs
        auto compare = [&nums1, &nums2](const vector<int>& a, const vector<int>& b) {
            int sum1 = nums1[a[0]] + nums2[a[1]];
            int sum2 = nums1[b[0]] + nums2[b[1]];
            return sum1 > sum2; // Use > for min heap
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> minHeap(compare);
        
        // Start with pairs formed with the first element of nums2
        for (int i = 0; i < min(k, static_cast<int>(nums1.size())); i++) {
            minHeap.push({i, 0}); // (index in nums1, index in nums2)
        }
        
        // Process k pairs
        while (k > 0 && !minHeap.empty()) {
            auto indices = minHeap.top();
            minHeap.pop();
            
            int i = indices[0];
            int j = indices[1];
            
            // Add the pair to the result
            result.push_back({nums1[i], nums2[j]});
            
            // If there are more elements in nums2, add the next pair
            if (j + 1 < nums2.size()) {
                minHeap.push({i, j + 1});
            }
            
            k--;
        }
        
        return result;
    }
};

// Utility function to print a vector
template <typename T>
void printVector(const vector<T>& vec) {
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Utility function to print a 2D vector
template <typename T>
void print2DVector(const vector<vector<T>>& vec) {
    for (const auto& row : vec) {
        cout << "[";
        for (size_t i = 0; i < row.size(); i++) {
            cout << row[i];
            if (i < row.size() - 1) cout << ", ";
        }
        cout << "] ";
    }
    cout << endl;
}

// Main function to demonstrate Top K Elements pattern
int main() {
    // Example 1: Kth Largest Element in an Array
    cout << "Example 1: Kth Largest Element in an Array" << endl;
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    KthLargestElement kthLargest;
    
    cout << "Array: ";
    printVector(nums1);
    
    cout << "The " << k1 << "nd largest element is: " << kthLargest.findKthLargest(nums1, k1) << endl;
    cout << "Using QuickSelect: " << kthLargest.findKthLargestQuickSelect(nums1, k1) << endl;
    
    // Example 2: Top K Frequent Elements
    cout << "\nExample 2: Top K Frequent Elements" << endl;
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    int k2 = 2;
    TopKFrequentElements topK;
    
    cout << "Array: ";
    printVector(nums2);
    
    vector<int> topKResult = topK.topKFrequent(nums2, k2);
    cout << "The " << k2 << " most frequent elements are: ";
    printVector(topKResult);
    
    // Example 3: Sort Characters By Frequency
    cout << "\nExample 3: Sort Characters By Frequency" << endl;
    string s3 = "tree";
    SortCharactersByFrequency sortChars;
    
    cout << "String: " << s3 << endl;
    cout << "Sorted by frequency: " << sortChars.frequencySort(s3) << endl;
    
    // Example 4: K Closest Points to Origin
    cout << "\nExample 4: K Closest Points to Origin" << endl;
    vector<vector<int>> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    int k4 = 2;
    KClosestPointsToOrigin kClosest;
    
    cout << "Points: ";
    print2DVector(points);
    
    vector<vector<int>> closestPoints = kClosest.kClosest(points, k4);
    cout << "The " << k4 << " closest points to origin are: ";
    print2DVector(closestPoints);
    
    // Example 5: Kth Largest Element in a Stream
    cout << "\nExample 5: Kth Largest Element in a Stream" << endl;
    vector<int> nums5 = {4, 5, 8, 2};
    int k5 = 3;
    
    cout << "Initial array: ";
    printVector(nums5);
    
    KthLargestElementInStream kthLargestStream(k5, nums5);
    cout << "Adding 3, " << k5 << "rd largest becomes: " << kthLargestStream.add(3) << endl;
    cout << "Adding 5, " << k5 << "rd largest becomes: " << kthLargestStream.add(5) << endl;
    cout << "Adding 10, " << k5 << "rd largest becomes: " << kthLargestStream.add(10) << endl;
    cout << "Adding 9, " << k5 << "rd largest becomes: " << kthLargestStream.add(9) << endl;
    cout << "Adding 4, " << k5 << "rd largest becomes: " << kthLargestStream.add(4) << endl;
    
    // Example 6: Last Stone Weight
    cout << "\nExample 6: Last Stone Weight" << endl;
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    LastStoneWeight lastStone;
    
    cout << "Stones: ";
    printVector(stones);
    
    int lastWeight = lastStone.lastStoneWeight(stones);
    cout << "The weight of the last stone is: " << lastWeight << endl;
    
    // Example 7: Relative Ranks
    cout << "\nExample 7: Relative Ranks" << endl;
    vector<int> scores = {5, 4, 3, 2, 1};
    RelativeRanks relativeRanks;
    
    cout << "Scores: ";
    printVector(scores);
    
    vector<string> ranks = relativeRanks.findRelativeRanks(scores);
    cout << "Relative ranks: ";
    for (const string& rank : ranks) {
        cout << rank << " ";
    }
    cout << endl;
    
    // Example 8: Take Gifts From the Richest Pile
    cout << "\nExample 8: Take Gifts From the Richest Pile" << endl;
    vector<int> gifts = {25, 64, 9, 4, 100};
    int k8 = 4;
    TakeGiftsFromRichestPile takeGifts;
    
    cout << "Gifts: ";
    printVector(gifts);
    
    long long remainingGifts = takeGifts.pickGifts(gifts, k8);
    cout << "After taking gifts for " << k8 << " seconds, remaining gifts: " << remainingGifts << endl;
    
    // Example 9: Find K Pairs with Smallest Sums
    cout << "\nExample 9: Find K Pairs with Smallest Sums" << endl;
    vector<int> nums9_1 = {1, 7, 11};
    vector<int> nums9_2 = {2, 4, 6};
    int k9 = 3;
    FindKPairsWithSmallestSums kPairs;
    
    cout << "Arrays: ";
    printVector(nums9_1);
    printVector(nums9_2);
    
    vector<vector<int>> smallestPairs = kPairs.kSmallestPairs(nums9_1, nums9_2, k9);
    cout << "The " << k9 << " pairs with smallest sums are: ";
    print2DVector(smallestPairs);
    
    return 0;
}
