/**
 * Pattern: Greedy - Gas Station Circuit
 * 
 * Description:
 * This pattern deals with problems involving a circuit of gas stations where you need
 * to determine if there exists a starting station from which you can travel around
 * the circuit once without running out of fuel. The greedy approach involves finding
 * a valid starting point and analyzing gas and cost patterns.
 * 
 * Time Complexity: O(n) where n is the number of gas stations
 * 
 * Space Complexity: O(1) as we only need a few variables to track states
 * 
 * When to use:
 * - Problems involving circular routes with resource accumulation and consumption
 * - When you need to find a valid starting point in a circular sequence
 * - When there are constraints on carrying resources forward
 * 
 * LeetCode Problems:
 * - 134. Gas Station
 * - 1058. Minimize Rounding Error to Meet Target (similar concept)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Example 1: Gas Station
// LeetCode 134: https://leetcode.com/problems/gas-station/
class GasStation {
public:
    // Approach 1: One pass solution
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        int totalGas = 0;       // Total gas available
        int totalCost = 0;      // Total cost to travel
        int currentGas = 0;     // Current gas available
        int startingPoint = 0;  // Potential starting point
        
        for (int i = 0; i < n; i++) {
            // Add the difference between gas and cost at station i
            totalGas += gas[i];
            totalCost += cost[i];
            
            // Update current gas level
            currentGas += gas[i] - cost[i];
            
            // If we can't reach station i+1, reset the starting point
            if (currentGas < 0) {
                startingPoint = i + 1;
                currentGas = 0;
            }
        }
        
        // If total gas is less than total cost, no solution exists
        if (totalGas < totalCost) {
            return -1;
        }
        
        // Otherwise, the last updated startingPoint is the answer
        return startingPoint;
    }
    
    // Approach 2: Brute force (for understanding)
    int canCompleteCircuitBruteForce(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        // Try each station as starting point
        for (int start = 0; start < n; start++) {
            int fuelRemaining = 0;
            bool canComplete = true;
            
            // Simulate the journey
            for (int i = 0; i < n; i++) {
                int station = (start + i) % n;
                
                // Add gas from current station
                fuelRemaining += gas[station];
                
                // Consume fuel for travel to next station
                fuelRemaining -= cost[station];
                
                // If we run out of fuel, this starting point doesn't work
                if (fuelRemaining < 0) {
                    canComplete = false;
                    break;
                }
            }
            
            if (canComplete) {
                return start;
            }
        }
        
        return -1;  // No valid starting point
    }
    
    // Approach 3: Sum of differences
    int canCompleteCircuitDifferences(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        // Calculate the net gas at each station (gas[i] - cost[i])
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = gas[i] - cost[i];
        }
        
        // If total sum is negative, no solution exists
        if (accumulate(diff.begin(), diff.end(), 0) < 0) {
            return -1;
        }
        
        // Find the starting point
        int total = 0;
        int start = 0;
        
        for (int i = 0; i < n; i++) {
            total += diff[i];
            
            // If we can't reach the next station, update the starting point
            if (total < 0) {
                total = 0;
                start = i + 1;
            }
        }
        
        return start;
    }
};

// Example 2: Ship Packages Within D Days
// LeetCode 1011: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
class ShipPackages {
public:
    // Binary search on the answer (not pure greedy, but related concept)
    int shipWithinDays(vector<int>& weights, int days) {
        // The minimum capacity is the maximum weight (we need to ship each package)
        int left = *max_element(weights.begin(), weights.end());
        
        // The maximum capacity is the sum of all weights (ship all in one day)
        int right = accumulate(weights.begin(), weights.end(), 0);
        
        // Binary search for the minimum capacity
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can ship with this capacity
            if (canShip(weights, days, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
private:
    // Helper function to check if we can ship all packages within 'days' days
    // with a capacity of 'capacity'
    bool canShip(vector<int>& weights, int days, int capacity) {
        int daysNeeded = 1;
        int currentWeight = 0;
        
        for (int weight : weights) {
            // If adding the current package exceeds the capacity,
            // we need to use a new day
            if (currentWeight + weight > capacity) {
                daysNeeded++;
                currentWeight = weight;
                
                // If we need more days than allowed, return false
                if (daysNeeded > days) {
                    return false;
                }
            } else {
                // Add the current package to the current day
                currentWeight += weight;
            }
        }
        
        return true;  // We can ship within the given days
    }
};

// Example 3: Car Pooling
// LeetCode 1094: https://leetcode.com/problems/car-pooling/
class CarPooling {
public:
    // Approach: Sort and Simulate
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // Store events: (location, passenger_change)
        vector<pair<int, int>> events;
        
        for (const auto& trip : trips) {
            int numPassengers = trip[0];
            int from = trip[1];
            int to = trip[2];
            
            // Add pickup and dropoff events
            events.push_back({from, numPassengers});     // Pickup
            events.push_back({to, -numPassengers});      // Dropoff
        }
        
        // Sort events by location
        sort(events.begin(), events.end());
        
        // Simulate the car journey
        int currentPassengers = 0;
        
        for (const auto& event : events) {
            currentPassengers += event.second;
            
            // If at any point we exceed capacity, return false
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;  // We can complete all trips without exceeding capacity
    }
    
    // Alternative approach: Bucket Sort (for when locations have a known range)
    bool carPoolingBucket(vector<vector<int>>& trips, int capacity) {
        // Assuming max location is 1000 (as per problem constraint)
        vector<int> timestamp(1001, 0);
        
        // Record the change in passenger count at each location
        for (const auto& trip : trips) {
            int numPassengers = trip[0];
            int from = trip[1];
            int to = trip[2];
            
            timestamp[from] += numPassengers;    // Pickup
            timestamp[to] -= numPassengers;      // Dropoff
        }
        
        // Simulate the journey
        int currentPassengers = 0;
        
        for (int i = 0; i < timestamp.size(); i++) {
            currentPassengers += timestamp[i];
            
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
};

// Example 4: Circular Array Loop
// LeetCode 457: https://leetcode.com/problems/circular-array-loop/
class CircularArrayLoop {
public:
    // Approach: Fast and Slow Pointers
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            // Skip if already visited or marked
            if (nums[i] == 0) {
                continue;
            }
            
            // Determine the direction of the current potential cycle
            bool isForward = nums[i] > 0;
            
            int slow = i;
            int fast = i;
            
            // Move pointers until we find a cycle or reach an invalid state
            do {
                // Move slow pointer one step
                slow = getNextIndex(nums, slow, isForward);
                
                // If we hit a wall, break
                if (slow == -1) {
                    break;
                }
                
                // Move fast pointer two steps
                fast = getNextIndex(nums, fast, isForward);
                
                if (fast == -1) {
                    break;
                }
                
                fast = getNextIndex(nums, fast, isForward);
                
                if (fast == -1) {
                    break;
                }
                
            } while (slow != fast);
            
            // If we found a cycle, check if it's valid (length > 1)
            if (slow != -1 && slow == fast) {
                // Check cycle length
                int count = 1;
                int next = getNextIndex(nums, slow, isForward);
                
                while (next != slow) {
                    count++;
                    next = getNextIndex(nums, next, isForward);
                }
                
                if (count > 1) {
                    return true;  // Valid cycle found
                }
            }
            
            // Mark this path as visited
            int current = i;
            while (nums[current] != 0) {
                int next = getNextIndex(nums, current, isForward);
                if (next == -1) {
                    break;
                }
                
                nums[current] = 0;  // Mark as visited
                current = next;
            }
        }
        
        return false;  // No valid cycle found
    }
    
private:
    // Helper function to get the next index
    int getNextIndex(const vector<int>& nums, int currentIndex, bool isForward) {
        int n = nums.size();
        
        // Check if the direction is consistent
        bool direction = nums[currentIndex] > 0;
        
        if (direction != isForward) {
            return -1;  // Different direction, invalid
        }
        
        // Calculate next index with modulo for circular behavior
        int nextIndex = (currentIndex + nums[currentIndex]) % n;
        
        // Handle negative numbers for circular behavior
        if (nextIndex < 0) {
            nextIndex += n;
        }
        
        // Check for single-element cycle
        if (nextIndex == currentIndex) {
            return -1;  // Self-loop, invalid
        }
        
        return nextIndex;
    }
};

// Main function to demonstrate Gas Station Circuit pattern
int main() {
    // Example 1: Gas Station
    cout << "Example 1: Gas Station" << endl;
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    
    GasStation gs;
    cout << "Gas: [1, 2, 3, 4, 5]" << endl;
    cout << "Cost: [3, 4, 5, 1, 2]" << endl;
    
    int startingStation = gs.canCompleteCircuit(gas, cost);
    if (startingStation != -1) {
        cout << "Can complete circuit starting from station " << startingStation << endl;
    } else {
        cout << "Cannot complete the circuit" << endl;
    }
    
    // Example 2: Ship Packages Within D Days
    cout << "\nExample 2: Ship Packages Within D Days" << endl;
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;
    
    ShipPackages sp;
    cout << "Weights: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]" << endl;
    cout << "Days: 5" << endl;
    
    int minCapacity = sp.shipWithinDays(weights, days);
    cout << "Minimum capacity needed: " << minCapacity << endl;
    
    // Example 3: Car Pooling
    cout << "\nExample 3: Car Pooling" << endl;
    vector<vector<int>> trips = {{2, 1, 5}, {3, 3, 7}};
    int capacity = 4;
    
    CarPooling cp;
    cout << "Trips: [[2, 1, 5], [3, 3, 7]]" << endl;
    cout << "Capacity: 4" << endl;
    
    bool canComplete = cp.carPooling(trips, capacity);
    cout << "Can complete all trips without exceeding capacity: " << (canComplete ? "true" : "false") << endl;
    
    // Example 4: Circular Array Loop
    cout << "\nExample 4: Circular Array Loop" << endl;
    vector<int> nums = {2, -1, 1, 2, 2};
    
    CircularArrayLoop cal;
    cout << "Nums: [2, -1, 1, 2, 2]" << endl;
    
    bool hasLoop = cal.circularArrayLoop(nums);
    cout << "Has circular array loop: " << (hasLoop ? "true" : "false") << endl;
    
    return 0;
}
