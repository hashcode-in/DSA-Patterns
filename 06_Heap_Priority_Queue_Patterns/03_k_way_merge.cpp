/**
 * Pattern: Heap - K-way Merge
 * 
 * Description:
 * This pattern is used to efficiently merge k sorted lists into a single sorted list.
 * It leverages a min heap to always select the smallest element from among the current
 * heads of the k lists, achieving better performance than merging lists one by one.
 * 
 * Time Complexity: 
 * - O(N log k) where N is the total number of elements across all lists and k is the number of lists
 * 
 * Space Complexity: O(k) for storing k elements in the heap
 * 
 * When to use:
 * - Merging multiple sorted arrays or linked lists
 * - Finding the kth smallest/largest element across multiple sorted collections
 * - Processing streams of sorted data from multiple sources
 * 
 * LeetCode Problems:
 * - 23. Merge k Sorted Lists
 * - 373. Find K Pairs with Smallest Sums
 * - 378. Kth Smallest Element in a Sorted Matrix
 * - 632. Smallest Range Covering Elements from K Lists
 * - 719. Find K-th Smallest Pair Distance
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <unordered_map>

using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Example 1: Merge k Sorted Lists
// LeetCode 23: https://leetcode.com/problems/merge-k-sorted-lists/
class MergeKSortedLists {
public:
    // Custom comparator for the min heap
    struct CompareListNodes {
        bool operator()(const ListNode* a, const ListNode* b) {
            return a->val > b->val; // Min heap, so use '>' to get smallest at top
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Create a min heap to store the heads of all lists
        priority_queue<ListNode*, vector<ListNode*>, CompareListNodes> minHeap;
        
        // Add the head of each non-empty list to the min heap
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }
        
        // Create a dummy head for the result list
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        // Process until the heap is empty
        while (!minHeap.empty()) {
            // Get the smallest node
            ListNode* smallest = minHeap.top();
            minHeap.pop();
            
            // Add it to the result list
            current->next = smallest;
            current = current->next;
            
            // If the smallest node has a next node, add it to the heap
            if (smallest->next != nullptr) {
                minHeap.push(smallest->next);
            }
        }
        
        return dummy.next;
    }
};

// Example 2: Find K Pairs with Smallest Sums
// LeetCode 373: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
class FindKPairsWithSmallestSums {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty() || k <= 0) {
            return result;
        }
        
        // Define a custom comparator for the min heap
        auto compare = [&nums1, &nums2](const pair<int, int>& a, const pair<int, int>& b) {
            int sumA = nums1[a.first] + nums2[a.second];
            int sumB = nums1[b.first] + nums2[b.second];
            return sumA > sumB; // Min heap, so use '>' to get smallest at top
        };
        
        // Min heap to store indices of pairs: (index in nums1, index in nums2)
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);
        
        // Push the pairs formed with the first element of nums2
        for (int i = 0; i < min((int)nums1.size(), k); i++) {
            minHeap.push({i, 0});
        }
        
        // Process the k smallest pairs
        while (k > 0 && !minHeap.empty()) {
            auto [i, j] = minHeap.top();
            minHeap.pop();
            
            // Add the current pair to the result
            result.push_back({nums1[i], nums2[j]});
            
            // If there are more elements in nums2, push the next pair
            if (j + 1 < nums2.size()) {
                minHeap.push({i, j + 1});
            }
            
            k--;
        }
        
        return result;
    }
};

// Example 3: Kth Smallest Element in a Sorted Matrix
// LeetCode 378: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
class KthSmallestElementInSortedMatrix {
public:
    // Approach 1: Using Min Heap
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        
        // Define a custom comparator for the min heap
        auto compare = [&matrix](const pair<int, int>& a, const pair<int, int>& b) {
            return matrix[a.first][a.second] > matrix[b.first][b.second]; // Min heap
        };
        
        // Min heap to store indices: (row, col)
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);
        
        // Push the first element of each row
        for (int i = 0; i < min(n, k); i++) {
            minHeap.push({i, 0});
        }
        
        // Process until we find the kth smallest
        int count = 0;
        while (!minHeap.empty()) {
            pair<int, int> top = minHeap.top();
            int row = top.first;
            int col = top.second;
            minHeap.pop();
            count++;
            
            if (count == k) {
                return matrix[row][col];
            }
            
            // If there are more elements in the current row, push the next element
            if (col + 1 < n) {
                minHeap.push({row, col + 1});
            }
        }
        
        return -1; // Should not reach here if k is valid
    }
    
    // Approach 2: Binary Search (alternative approach, not using heap)
    int kthSmallestBinarySearch(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n-1][n-1];
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            int count = 0;
            int j = n - 1;
            
            // Count elements less than or equal to mid in each row
            for (int i = 0; i < n; i++) {
                while (j >= 0 && matrix[i][j] > mid) {
                    j--;
                }
                count += j + 1;
            }
            
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        
        return low;
    }
};

// Example 4: Smallest Range Covering Elements from K Lists
// LeetCode 632: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
class SmallestRangeCoveringElements {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        
        // Custom comparator for min heap
        auto compare = [&nums](const pair<int, int>& a, const pair<int, int>& b) {
            return nums[a.first][a.second] > nums[b.first][b.second]; // Min heap
        };
        
        // Min heap to track the smallest element from each list
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);
        
        // Initialize variables to track the current range
        int rangeStart = 0;
        int rangeEnd = INT_MAX;
        int maxVal = INT_MIN;
        
        // Add the first element from each list to the heap
        for (int i = 0; i < k; i++) {
            if (!nums[i].empty()) {
                minHeap.push({i, 0});
                maxVal = max(maxVal, nums[i][0]);
            }
        }
        
        // Process until any list is exhausted
        while (minHeap.size() == k) {
            auto [listIndex, elemIndex] = minHeap.top();
            minHeap.pop();
            
            int minVal = nums[listIndex][elemIndex];
            
            // Update the range if current range is smaller
            if (maxVal - minVal < rangeEnd - rangeStart) {
                rangeStart = minVal;
                rangeEnd = maxVal;
            }
            
            // If there are more elements in the current list, add the next one
            if (elemIndex + 1 < nums[listIndex].size()) {
                elemIndex++;
                minHeap.push({listIndex, elemIndex});
                maxVal = max(maxVal, nums[listIndex][elemIndex]);
            }
        }
        
        return {rangeStart, rangeEnd};
    }
};

// Example 5: Merge k Sorted Arrays
class MergeKSortedArrays {
public:
    // Custom structure to track elements from different arrays
    struct Element {
        int value;
        int arrayIndex;
        int elementIndex;
        
        Element(int val, int arrIdx, int elemIdx)
            : value(val), arrayIndex(arrIdx), elementIndex(elemIdx) {}
    };
    
    // Custom comparator for the min heap
    struct CompareElements {
        bool operator()(const Element& a, const Element& b) {
            return a.value > b.value; // Min heap
        }
    };
    
    vector<int> mergeArrays(vector<vector<int>>& arrays) {
        vector<int> result;
        
        // Create a min heap
        priority_queue<Element, vector<Element>, CompareElements> minHeap;
        
        // Add the first element from each array to the heap
        for (int i = 0; i < arrays.size(); i++) {
            if (!arrays[i].empty()) {
                minHeap.push(Element(arrays[i][0], i, 0));
            }
        }
        
        // Process until the heap is empty
        while (!minHeap.empty()) {
            // Extract the minimum element
            Element minElement = minHeap.top();
            minHeap.pop();
            
            // Add it to the result
            result.push_back(minElement.value);
            
            // If there are more elements in the same array, add the next one
            if (minElement.elementIndex + 1 < arrays[minElement.arrayIndex].size()) {
                minHeap.push(Element(
                    arrays[minElement.arrayIndex][minElement.elementIndex + 1],
                    minElement.arrayIndex,
                    minElement.elementIndex + 1
                ));
            }
        }
        
        return result;
    }
};

// Example 6: Find K-th Smallest Pair Distance
// LeetCode 719: https://leetcode.com/problems/find-k-th-smallest-pair-distance/
class KthSmallestPairDistance {
public:
    // Using binary search and sliding window (more efficient than heap for this problem)
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // The minimum possible distance is 0, and the maximum is the difference
        // between the largest and smallest elements
        int low = 0;
        int high = nums[n-1] - nums[0];
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            // Count the number of pairs with distance <= mid
            int count = 0;
            int left = 0;
            
            for (int right = 0; right < n; right++) {
                while (nums[right] - nums[left] > mid) {
                    left++;
                }
                count += right - left;
            }
            
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        
        return low;
    }
    
    // Alternative approach using a heap (less efficient but demonstrates the k-way merge pattern)
    int smallestDistancePairHeap(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // Priority queue to store pairs (distance, indices)
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> minHeap;
        
        // Add all adjacent pairs to the heap
        for (int i = 0; i < n - 1; i++) {
            minHeap.push({nums[i+1] - nums[i], {i, i+1}});
        }
        
        // Process until we find the kth pair
        while (--k > 0 && !minHeap.empty()) {
            auto [dist, indices] = minHeap.top();
            int i = indices.first;
            int j = indices.second;
            minHeap.pop();
            
            // Add the next pair from the same starting point if possible
            if (j + 1 < n) {
                minHeap.push({nums[j+1] - nums[i], {i, j+1}});
            }
        }
        
        return minHeap.top().first;
    }
};

// Utility function to create a linked list from a vector
ListNode* createLinkedList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;
    
    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;
    
    for (int i = 1; i < nums.size(); i++) {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    
    return head;
}

// Utility function to print a linked list
void printLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

// Utility function to print a vector
template <typename T>
void printVector(const vector<T>& vec) {
    for (const T& val : vec) {
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
        cout << "]";
        cout << " ";
    }
    cout << endl;
}

// Main function to demonstrate K-way Merge pattern
int main() {
    // Example 1: Merge k Sorted Lists
    cout << "Example 1: Merge k Sorted Lists" << endl;
    
    // Create sorted linked lists
    vector<ListNode*> lists;
    lists.push_back(createLinkedList({1, 4, 5}));
    lists.push_back(createLinkedList({1, 3, 4}));
    lists.push_back(createLinkedList({2, 6}));
    
    cout << "Input lists:" << endl;
    for (int i = 0; i < lists.size(); i++) {
        cout << "List " << i + 1 << ": ";
        printLinkedList(lists[i]);
    }
    
    MergeKSortedLists solution1;
    ListNode* mergedList = solution1.mergeKLists(lists);
    
    cout << "Merged list: ";
    printLinkedList(mergedList);
    
    // Example 2: Find K Pairs with Smallest Sums
    cout << "\nExample 2: Find K Pairs with Smallest Sums" << endl;
    
    vector<int> nums2_1 = {1, 7, 11};
    vector<int> nums2_2 = {2, 4, 6};
    int k2 = 3;
    
    cout << "Array 1: ";
    printVector(nums2_1);
    cout << "Array 2: ";
    printVector(nums2_2);
    
    FindKPairsWithSmallestSums solution2;
    vector<vector<int>> smallestPairs = solution2.kSmallestPairs(nums2_1, nums2_2, k2);
    
    cout << "K pairs with smallest sums (k=" << k2 << "): ";
    print2DVector(smallestPairs);
    
    // Example 3: Kth Smallest Element in a Sorted Matrix
    cout << "\nExample 3: Kth Smallest Element in a Sorted Matrix" << endl;
    
    vector<vector<int>> matrix3 = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int k3 = 8;
    
    cout << "Matrix:" << endl;
    for (const auto& row : matrix3) {
        cout << "  ";
        printVector(row);
    }
    
    KthSmallestElementInSortedMatrix solution3;
    int kthSmallest = solution3.kthSmallest(matrix3, k3);
    
    cout << "The " << k3 << "th smallest element is: " << kthSmallest << endl;
    cout << "Using binary search: " << solution3.kthSmallestBinarySearch(matrix3, k3) << endl;
    
    // Example 4: Smallest Range Covering Elements from K Lists
    cout << "\nExample 4: Smallest Range Covering Elements from K Lists" << endl;
    
    vector<vector<int>> nums4 = {
        {4, 10, 15, 24, 26},
        {0, 9, 12, 20},
        {5, 18, 22, 30}
    };
    
    cout << "Lists:" << endl;
    for (int i = 0; i < nums4.size(); i++) {
        cout << "List " << i + 1 << ": ";
        printVector(nums4[i]);
    }
    
    SmallestRangeCoveringElements solution4;
    vector<int> smallestRange = solution4.smallestRange(nums4);
    
    cout << "Smallest range covering elements from all lists: [" << smallestRange[0] << ", " << smallestRange[1] << "]" << endl;
    
    // Example 5: Merge k Sorted Arrays
    cout << "\nExample 5: Merge k Sorted Arrays" << endl;
    
    vector<vector<int>> arrays5 = {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {0, 9, 10, 11}
    };
    
    cout << "Input arrays:" << endl;
    for (int i = 0; i < arrays5.size(); i++) {
        cout << "Array " << i + 1 << ": ";
        printVector(arrays5[i]);
    }
    
    MergeKSortedArrays solution5;
    vector<int> mergedArray = solution5.mergeArrays(arrays5);
    
    cout << "Merged array: ";
    printVector(mergedArray);
    
    // Example 6: Find K-th Smallest Pair Distance
    cout << "\nExample 6: Find K-th Smallest Pair Distance" << endl;
    
    vector<int> nums6 = {1, 3, 1, 5, 4};
    int k6 = 3;
    
    cout << "Array: ";
    printVector(nums6);
    
    KthSmallestPairDistance solution6;
    int kthDistance = solution6.smallestDistancePair(nums6, k6);
    
    cout << "The " << k6 << "th smallest pair distance is: " << kthDistance << endl;
    
    return 0;
}
