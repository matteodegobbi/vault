#algorithms
Dynamic programming is an algorithmic technique used for solving combinatorial or optimization problems.

It's useful whenever we have problems with:
1. Optimal substructure (Optimal solutions to subproblems can be used to obtain an optimal solution to the whole problem)
2. Overlapping subproblems (repeated instances of the same subproblem)

This technique allows us to get polynomial time algorithms where naïve divide and conquer would yield exponential time algorithms.


---

To solve a problem with dynamic programming we usually follow a few steps: First we visualize the problem to understand how it works
1. Define objective function
2. Find base cases
3. Find a subproblem definition (recurrence relation)
4. Find correct order of computation
5. Location of the answer

Example of these steps for Climbing Stairs:
1. $f(i) = \text{number of distinct ways to reach i-th stair}$
2. $f(0) = 1,f(1)=1$
3. $f(n)=f(n-1)+f(n-2)$
4. bottom-up, we rely on solution to the two previous sub-problems
5. $f(n)$

---
