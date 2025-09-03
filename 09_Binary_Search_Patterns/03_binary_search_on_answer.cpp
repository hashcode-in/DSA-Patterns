/**
 * Pattern: Binary Search - On Answer / Condition Function
 * 
 * Description:
 * This pattern involves using binary search to find an answer that satisfies certain conditions,
 * rather than searching for a specific value in a sorted array. The key idea is to define a search space
 * of potential answers and then use binary search to efficiently find the optimal value.
 * We use a condition function that checks whether a particular value is a valid answer.
 * 
 * Time Complexity: O(log(range) * f(n)) where range is the size of the search space and f(n) is the 
 *                  complexity of the condition function
 * Space Complexity: O(1) for the binary search itself, plus any space needed for the condition function
 * 
 * When to use:
 * - When you need to find a minimum or maximum value that satisfies certain conditions
 * - When the search space is very large but can be efficiently checked
 * - When the solution has a clear monotonicity property (i.e., if condition(x) is true, 
 *   then condition(x+1) is also true, or vice versa)
 * 
 * LeetCode Problems:
 * - 410. Split Array Largest Sum
 * - 774. Minimize Max Distance to Gas Station
 * - 875. Koko Eating Bananas
 * - 1011. Capacity To Ship Packages Within D Days
 * - 1482. Minimum Number of Days to Make m Bouquets
 * - 1760. Minimum Limit of Balls in a Bag
 * - 2064. Minimized Maximum of Products Distributed to Any Store
 * - 2226. Maximum Candies Allocated to K Children
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // For accumulate
#include <climits>  // For INT_MAX
#include <cmath>    // For ceil

using namespace std;

// Example 1: Split Array Largest Sum
// LeetCode 410: https://leetcode.com/problems/split-array-largest-sum/
class SplitArrayLargestSum {
public:
    int splitArray(vector<int>& nums, int k) {
        // Search space: [max element in nums, sum of all elements in nums]
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        
        // Binary search to find the minimum largest subarray sum
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if it's possible to split the array into k subarrays
            // such that the largest sum is at most mid
            if (canSplit(nums, k, mid)) {
                right = mid;  // Try to find a smaller sum
            } else {
                left = mid + 1;  // Need a larger sum
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can split the array into k subarrays
    // such that each subarray sum is at most maxSum
    bool canSplit(vector<int>& nums, int k, int maxSum) {
        int subarrays = 1;
        int currentSum = 0;
        
        for (int num : nums) {
            if (currentSum + num > maxSum) {
                subarrays++;
                currentSum = num;
                
                if (subarrays > k) {
                    return false;  // Need more than k subarrays
                }
            } else {
                currentSum += num;
            }
        }
        
        return true;  // Can split into k or fewer subarrays
    }
};

// Example 2: Koko Eating Bananas
// LeetCode 875: https://leetcode.com/problems/koko-eating-bananas/
class KokoEatingBananas {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // Search space: [1, max pile size]
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        
        // Binary search to find the minimum eating speed
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if Koko can eat all bananas in h hours at speed mid
            if (canEatAll(piles, h, mid)) {
                right = mid;  // Try to find a smaller speed
            } else {
                left = mid + 1;  // Need a larger speed
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if Koko can eat all bananas in h hours at speed k
    bool canEatAll(vector<int>& piles, int h, int k) {
        int hoursNeeded = 0;
        
        for (int pile : piles) {
            // Ceiling division: (pile + k - 1) / k
            hoursNeeded += (pile + k - 1) / k;
            
            if (hoursNeeded > h) {
                return false;  // Cannot finish in time
            }
        }
        
        return true;  // Can finish in h hours or less
    }
};

// Example 3: Capacity To Ship Packages Within D Days
// LeetCode 1011: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
class ShipPackagesWithinDays {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        // Search space: [max weight, sum of all weights]
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        
        // Binary search to find the minimum capacity
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can ship all packages in days days with capacity mid
            if (canShip(weights, days, mid)) {
                right = mid;  // Try to find a smaller capacity
            } else {
                left = mid + 1;  // Need a larger capacity
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can ship all packages in days days with capacity
    bool canShip(vector<int>& weights, int days, int capacity) {
        int daysNeeded = 1;
        int currentWeight = 0;
        
        for (int weight : weights) {
            if (currentWeight + weight > capacity) {
                daysNeeded++;
                currentWeight = weight;
                
                if (daysNeeded > days) {
                    return false;  // Cannot ship in time
                }
            } else {
                currentWeight += weight;
            }
        }
        
        return true;  // Can ship in days days or less
    }
};

// Example 4: Minimize Max Distance to Gas Station
// LeetCode 774: https://leetcode.com/problems/minimize-max-distance-to-gas-station/ (Premium)
class MinimizeMaxDistanceToGasStation {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        // Sort the stations if they're not already sorted
        sort(stations.begin(), stations.end());
        
        // Search space: [0, max distance between adjacent stations]
        double left = 0;
        double right = stations.back() - stations.front();
        
        // Binary search with precision up to 10^-6
        double epsilon = 1e-6;
        
        while (right - left > epsilon) {
            double mid = left + (right - left) / 2;
            
            // Check if we can place k new stations such that
            // the maximum distance between adjacent stations is at most mid
            if (canPlaceStations(stations, k, mid)) {
                right = mid;  // Try to find a smaller distance
            } else {
                left = mid;  // Need a larger distance
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can place k new stations such that
    // the maximum distance between adjacent stations is at most maxDist
    bool canPlaceStations(vector<int>& stations, int k, double maxDist) {
        int newStationsNeeded = 0;
        
        for (int i = 1; i < stations.size(); i++) {
            int distance = stations[i] - stations[i - 1];
            
            // Number of new stations needed for this segment
            // to ensure distance is at most maxDist
            newStationsNeeded += std::ceil(distance / maxDist) - 1;
            
            if (newStationsNeeded > k) {
                return false;  // Need more than k new stations
            }
        }
        
        return true;  // Can place k or fewer new stations
    }
};

// Example 5: Minimum Number of Days to Make m Bouquets
// LeetCode 1482: https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
class MinimumDaysToMakeBouquets {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        // If we need more flowers than available, return -1
        if (m * k > bloomDay.size()) {
            return -1;
        }
        
        // Search space: [1, max bloom day]
        int left = 1;
        int right = *max_element(bloomDay.begin(), bloomDay.end());
        
        // Binary search to find the minimum days
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can make m bouquets in mid days
            if (canMakeBouquets(bloomDay, m, k, mid)) {
                right = mid;  // Try to find a smaller number of days
            } else {
                left = mid + 1;  // Need more days
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can make m bouquets in days days
    bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int days) {
        int bouquets = 0;
        int flowers = 0;
        
        for (int bloom : bloomDay) {
            if (bloom <= days) {
                // Flower blooms by 'days'
                flowers++;
                
                // Check if we have enough adjacent flowers for a bouquet
                if (flowers == k) {
                    bouquets++;
                    flowers = 0;
                    
                    if (bouquets >= m) {
                        return true;  // Made enough bouquets
                    }
                }
            } else {
                // Reset flowers count if we encounter a flower that hasn't bloomed
                flowers = 0;
            }
        }
        
        return bouquets >= m;  // Check if we made enough bouquets
    }
};

// Example 6: Minimum Limit of Balls in a Bag
// LeetCode 1760: https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/
class MinimumLimitOfBallsInBag {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        // Search space: [1, max number in nums]
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        
        // Binary search to find the minimum penalty
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can make all bags have at most mid balls
            // with at most maxOperations operations
            if (canMakeBagsWithinLimit(nums, maxOperations, mid)) {
                right = mid;  // Try to find a smaller limit
            } else {
                left = mid + 1;  // Need a larger limit
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can make all bags have at most limit balls
    // with at most maxOperations operations
    bool canMakeBagsWithinLimit(vector<int>& nums, int maxOperations, int limit) {
        int operations = 0;
        
        for (int num : nums) {
            // Number of operations needed for this bag
            // (num - 1) / limit is the ceiling of division num / limit
            operations += (num - 1) / limit;
            
            if (operations > maxOperations) {
                return false;  // Need more than maxOperations
            }
        }
        
        return true;  // Can do it within maxOperations
    }
};

// Example 7: Minimized Maximum of Products Distributed to Any Store
// LeetCode 2064: https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/
class MinimizedMaximumOfProducts {
public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        // Search space: [1, max quantity]
        int left = 1;
        int right = *max_element(quantities.begin(), quantities.end());
        
        // Binary search to find the minimum maximum products
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can distribute products so that each store gets at most mid products
            if (canDistribute(n, quantities, mid)) {
                right = mid;  // Try to find a smaller maximum
            } else {
                left = mid + 1;  // Need a larger maximum
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can distribute products so that
    // each store gets at most limit products
    bool canDistribute(int n, vector<int>& quantities, int limit) {
        int storesNeeded = 0;
        
        for (int quantity : quantities) {
            // Number of stores needed for this product
            // (quantity + limit - 1) / limit is the ceiling of division quantity / limit
            storesNeeded += (quantity + limit - 1) / limit;
            
            if (storesNeeded > n) {
                return false;  // Need more than n stores
            }
        }
        
        return true;  // Can distribute to n or fewer stores
    }
};

// Example 8: Maximum Candies Allocated to K Children
// LeetCode 2226: https://leetcode.com/problems/maximum-candies-allocated-to-k-children/
class MaximumCandiesAllocatedToKChildren {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        // If total candies are fewer than k, return 0
        if (accumulate(candies.begin(), candies.end(), 0LL) < k) {
            return 0;
        }
        
        // Search space: [1, max pile of candies]
        int left = 1;
        int right = *max_element(candies.begin(), candies.end());
        
        // Binary search to find the maximum number of candies
        while (left < right) {
            int mid = left + (right - left + 1) / 2;  // Ceiling division to avoid infinite loop
            
            // Check if we can allocate mid candies to each of k children
            if (canAllocateCandies(candies, k, mid)) {
                left = mid;  // Try to find a larger allocation
            } else {
                right = mid - 1;  // Need a smaller allocation
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can allocate target candies to each of k children
    bool canAllocateCandies(vector<int>& candies, long long k, int target) {
        long long children = 0;
        
        for (int pile : candies) {
            // Number of children that can be served from this pile
            children += pile / target;
            
            if (children >= k) {
                return true;  // Can serve at least k children
            }
        }
        
        return false;  // Cannot serve k children
    }
};

// Main function to demonstrate Binary Search on Answer pattern
int main() {
    // Example 1: Split Array Largest Sum
    cout << "Example 1: Split Array Largest Sum" << endl;
    vector<int> nums1 = {7, 2, 5, 10, 8};
    int k1 = 2;
    
    SplitArrayLargestSum sals;
    cout << "Array: [7, 2, 5, 10, 8], k = 2" << endl;
    int minLargestSum = sals.splitArray(nums1, k1);
    cout << "Minimum largest subarray sum: " << minLargestSum << endl;
    
    // Example 2: Koko Eating Bananas
    cout << "\nExample 2: Koko Eating Bananas" << endl;
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    
    KokoEatingBananas keb;
    cout << "Piles: [3, 6, 7, 11], h = 8" << endl;
    int minSpeed = keb.minEatingSpeed(piles, h);
    cout << "Minimum eating speed: " << minSpeed << endl;
    
    // Example 3: Capacity To Ship Packages Within D Days
    cout << "\nExample 3: Capacity To Ship Packages Within D Days" << endl;
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;
    
    ShipPackagesWithinDays spwd;
    cout << "Weights: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], days = 5" << endl;
    int minCapacity = spwd.shipWithinDays(weights, days);
    cout << "Minimum capacity: " << minCapacity << endl;
    
    // Example 4: Minimize Max Distance to Gas Station
    cout << "\nExample 4: Minimize Max Distance to Gas Station" << endl;
    vector<int> stations = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k4 = 9;
    
    MinimizeMaxDistanceToGasStation mmdgs;
    cout << "Stations: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 9" << endl;
    double minMaxDist = mmdgs.minmaxGasDist(stations, k4);
    cout << "Minimized maximum distance: " << minMaxDist << endl;
    
    // Example 5: Minimum Number of Days to Make m Bouquets
    cout << "\nExample 5: Minimum Number of Days to Make m Bouquets" << endl;
    vector<int> bloomDay = {1, 10, 3, 10, 2};
    int m = 3;
    int k5 = 1;
    
    MinimumDaysToMakeBouquets mdtmb;
    cout << "Bloom days: [1, 10, 3, 10, 2], m = 3, k = 1" << endl;
    int minDays = mdtmb.minDays(bloomDay, m, k5);
    cout << "Minimum days: " << minDays << endl;
    
    // Example 6: Minimum Limit of Balls in a Bag
    cout << "\nExample 6: Minimum Limit of Balls in a Bag" << endl;
    vector<int> nums6 = {9};
    int maxOperations = 2;
    
    MinimumLimitOfBallsInBag mlobib;
    cout << "Nums: [9], maxOperations = 2" << endl;
    int minPenalty = mlobib.minimumSize(nums6, maxOperations);
    cout << "Minimum penalty: " << minPenalty << endl;
    
    // Example 7: Minimized Maximum of Products Distributed to Any Store
    cout << "\nExample 7: Minimized Maximum of Products Distributed to Any Store" << endl;
    vector<int> quantities = {11, 6};
    int n = 6;
    
    MinimizedMaximumOfProducts mmop;
    cout << "Quantities: [11, 6], n = 6" << endl;
    int minMaxProducts = mmop.minimizedMaximum(n, quantities);
    cout << "Minimized maximum products: " << minMaxProducts << endl;
    
    // Example 8: Maximum Candies Allocated to K Children
    cout << "\nExample 8: Maximum Candies Allocated to K Children" << endl;
    vector<int> candies = {5, 8, 6};
    long long k8 = 3;
    
    MaximumCandiesAllocatedToKChildren mcatkc;
    cout << "Candies: [5, 8, 6], k = 3" << endl;
    int maxCandies = mcatkc.maximumCandies(candies, k8);
    cout << "Maximum candies per child: " << maxCandies << endl;
    
    return 0;
}
