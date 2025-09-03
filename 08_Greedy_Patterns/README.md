# Greedy Algorithm Patterns

Greedy algorithms make locally optimal choices at each step with the hope of finding a global optimum. These patterns are particularly useful when immediate decisions lead to an overall optimal solution without the need to consider the entire future.

## Key Characteristics

- Makes the best choice at the current step without reconsidering previous choices
- Often used for optimization problems
- Generally simpler and more efficient than dynamic programming approaches
- Does not always yield globally optimal solutions (but does for specific problem types)

## Common Patterns

1. **Interval Merging/Scheduling**
   - Problems involving overlapping intervals, scheduling of tasks, or resource allocation
   - Sort intervals by start/end times and process them in order
   - Example problems: Merge Intervals, Meeting Rooms, Activity Selection

2. **Jump Game Reachability/Minimization**
   - Problems requiring minimum number of jumps or determining if end is reachable
   - Make optimal jump decisions at each position
   - Example problems: Jump Game, Jump Game II

3. **Buy/Sell Stock**
   - Problems about maximizing profit by buying and selling at optimal times
   - Track minimum price seen so far and maximize profit
   - Example problems: Best Time to Buy and Sell Stock I & II

4. **Gas Station Circuit**
   - Circular route problems where resources must be managed
   - Find valid starting positions by tracking cumulative resources
   - Example problems: Gas Station

5. **Task Scheduling (Frequency Based)**
   - Problems involving task arrangement to minimize time or maximize efficiency
   - Often use frequency counts and priority queues
   - Example problems: Task Scheduler, Reorganize String

## When to Use

- When the problem has "optimal substructure" (globally optimal solution contains locally optimal solutions)
- When making the locally optimal choice never invalidates the global solution
- When optimization problems can be solved by making a sequence of choices

## Implementation Considerations

- Sort inputs when the order affects greedy decision making
- Consider edge cases and boundary conditions carefully
- Verify your greedy approach with examples (greedy algorithms can be deceptive)
- Sometimes a hybrid approach with dynamic programming is needed
