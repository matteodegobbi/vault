#ai
A problem solving agent is a particular type of [[Agents and environments#Agent types|goal-based agent]] (goal-based agents act to achieve their goals)
Problem-solving agents use [[Agents and environments#Components|atomic representation]] (states of the world have no internal structure visible to the problem-solving algorithm)
Solution: fixed sequence of actions.
It's an important property that in a fully [[Agents and environments#Types of task environments|observable, deterministic, known environment]], the solution to any problem is a ﬁxed sequence of actions:
Search: process of looking for such a sequence
Search algorithm:
* input: problem
* output: an action sequence

The sequence in output can then be executed.

---
# Pseudocode problem solving agent
(pseudocode problem solving agent in pdf [[4_AI3-search-uninf-2023.pdf]] pag 8)
This simple problem-solving agent:
1. Formulates a goal and a problem
2. Searches for a sequence of actions that would solve the problem
3. Executes the actions one at a time
When this is complete, it formulates another goal and starts over
---
# Problem formulation
A problem can be defined formally by:
* Initial state
* Actions
* Transition model
* Goal test
* Path cost
Solution: sequence of actions (path) leading from the initial state to a goal state
Optimal solution: a solution with minimal path-cost
## State space
### Initial state 
initial state that the agent starts in:
Example: `In(Arad)`

### Actions 
Actions available to the agent. Given a state s, `ACTIONS(s)` returns the set of actions that can be executed in s, we say that each of these actions is applicable in s.
Example: from the state `In(Arad)`, the applicable actions are: `{Go(Sibiu), Go(Timisoara), Go(Zerind)}`.

### Transition model 
`RESULT(s,a)` returns the state obtained from doing action a in state s. 
Successor: any state reachable from a given state by a single action
Example: `RESULT(In(Arad),Go(Zerind)) = In(Zerind)`

### Initial state, actions and transition model determine the state space
Problem state space = (initial state, actions, transition model)
State space = the set of all states reachable from the initial state by any sequence of actions.
The state space can be depicted as a directed graph:
nodes -> states
edges -> actions
path -> sequence of states connected by a sequence of actions

## Goal test
The goal test allows to check if a state is a goal.
Example: The agent’s goal in Romania is the singleton set `{In(Bucharest)}`

## Path cost
The path cost is a numeric value associated to each path reflecting the desired performance measure
(e.g., sum of distances, number of actions executed, etc.)
* `c(x,a,y)` is the step cost, for going from state x to state y by performing action a.
* assumed to be ≥ 0
* We assume path costs to be additive: sum of step costs
[[4_AI3-search-uninf-2023.pdf|vacuum example page 21]].

# Search tree

Search algorithms consider possible sequences of actions.
Possible sequences of actions from initial state form a search tree:
* Root -> initial state 
* Nodes -> states 
* Branches -> actions 
* The same state can appear multiple times
* Outgoing edges from a node -> all possible actions available in the state represented by the node

Leaf node: a node with no children in the tree
Frontier: the set of all leaf nodes available for expansion at any given point

![[Pasted image 20240314153834.png]]

• Redundant paths: exist whenever there is more than one way to get from one state to another
• Loopy paths: special case of redundant paths

 Example: Consider the path
• Arad–Sibiu (140)
• Arad–Zerind–Oradea–Sibiu (297) 
the second path is redundant, it’s just a worse way to get to the same state


To avoid exploring redundant paths TREE-SEARCH algorithm is augmented with explored set that remembers every expanded node.
(GRAPH-SEARCH)

# Graph Search
![[Pasted image 20240314154108.png]]


# Data structures for search algorithms

Search algorithms require a data structure to keep track of the search tree 

For each node n of the tree, we have a structure with: 
* n.STATE: the state in the state space to which the node corresponds 
* n.PARENT: the node in the search tree that generated this node 
* n.ACTION: the action that was applied to the parent to generate the node 
* n.PATH-COST: the cost, traditionally denoted by g(n), of the path from the initial state to the node, as indicated by the parent pointers

![[Pasted image 20240314154325.png]]
* A state corresponds to a configuration of the world 
* A node is a data structure used to represent the search tree

Frontier needs to be stored in such a way that the search algorithm can easily choose the next node to expand (queue, FIFO, LIFO or priority queue).

# Search strategies
A search strategy is defined by picking the order of node expansion.
Strategies are evaluated along the following dimensions:
* completeness: does it always find a solution if one exists?
* time complexity: number of nodes generated
* space complexity: maximum number of nodes in memory
* optimality: does it always find a least-cost solution?

Time and space complexity are measured in terms of
* b: branching factor of the search tree (i.e., maximum number of successors of any node)
* d: depth of the least-cost solution
* m: the maximum depth of the state space

# Uninformed search
Uninformed strategies use only the information available
in the problem definition:
* generate successors
* distinguish goal
(e.g Breadth-first search, Uniform-cost search, Depth-first search, Depth-limited search, Iterative deepening search)

# Informed search
Use problem-specific knowledge to speed up the search process
Idea: use an evaluation function f(n) for each node (Best-first search methods)
* Estimate of “desiderability”
* to choose the node selected for expansion 
* is construed as a cost estimate
* Expand node with the lowest f(n) first
Most algorithms use a heuristic function h(n) as a component of f (evaluation function).
We will see:
* Greedy best-first search
* A* search
## Greedy best-first search
Heuristic function h(n) = estimated cost of the cheapest path from the state of the node n to a goal state (depends only on the state associated with n)
Assumptions:
* h(n) is non negative
* h(n)=0 at every goal state

Example: in Romania, we may estimate n the cost of the cheapest path from Arad to Bucharest via the straight-line distance from Arad to Bucharest
$h_{SLD}(n)$ = straight-line distance from n to Bucharest

Evaluation function f(n) = h(n) (heuristic)
h(n): estimated cost of the cheapest path from n to goal
Example: $h_{SLD}(n)$ = straight-line distance from n to Bucharest
Greedy best-first search expands the node that
appears to be closest to goal.
[[5_AI3-search-inf-2024.pdf|Example in the pdf pag 9]]
### Properties of greedy best-first search
* Complete? No (tree-search), consider the problem of going from Iasi to Fagaras: Iasi -> Neamt -> Iasi -> Neamt. The heuristic suggests Neamt be expanded first because it is closest to Fagaras but it is a dead end.
* It is Complete in finite state with repeated-state checking (graph search instead of tree search)
* Time? $O(b^m)$, but a good heuristic can give dramatic improvement
* Space? $O(b^m)$, keeps all nodes in memory
* Optimal? No
With b branching factor and m maximum depth of search space.
## A* search
Idea: avoid expanding paths that are already expensive
Evaluation function f(n) = g(n) + h(n)
* g(n) = path cost from the start node to node n
* h(n) = estimated cost of the cheapest path from n to goal
* f(n) = estimated cost of the cheapest solution through n
A* is like uniform-cost search (~Djikstra without exploring all paths) with f=g+h instead of g.
[[5_AI3-search-inf-2024.pdf|Example in the pdf pag 17]]

## Optimality
### Admissibile heuristic
A heuristic h is admissible if for every node n, h(n) ≤ h*(n)
where h*(n) is the true cost from n to goal.
An admissible heuristic never overestimates the cost to reach the goal.
Example: $h_{SLD}(n)$ is admissable (never overestimates the actual road distance)

Theorem: If h is admissible, A* using TREE-SEARCH is optimal
### Consistent heuristic

A heuristic h is consistent if for every node n, for every successor n' of n generated by an action a, $h(n) \le c(n, a, n') + h(n’)$
It's an instance of triangular inequality
Consistency $\to$ admissibility

Theorem: If h is consistent A* using GRAPH-SEARCH is optimal
![[Screenshot from 2024-03-19 12-25-40.png]]

## Properties of A*
* Complete? Yes (unless there are infinitely many nodes with f ≤ f(G), G being the goal state)
* Time? Exponential
* Space? Keeps all nodes in memory
* Optimal? Yes (with TREE-SEARCH if admissible heuristic; GRAPH-SEARCH if consistent heuristic)
[[5_AI3-search-inf-2024.pdf|Example in the pdf pag 31]]

## Dominance
If $h_2(n)\ge h_1(n)$ for all node n (both admissible) then $h_2$ dominates $h_1$ then h2 is better than h1 for search: h1 will expand all the nodes h2 expands and possibly more.

## Generating admissible heuristics from relaxed problems
A problem with fewer restrictions on the actions is called a relaxed problem:
* A superset of actions is available from each state
* The graph of the relaxed problem is a supergraph of the original
* Any optimal solution of the original problem is also a solution of the relaxed problem
* The cost of an optimal solution of the relaxed problem may be the same or lower than the cost of an optimal solution of the original problem
From these properties we get that:
The cost of an optimal solution to a relaxed problem
is an admissible heuristic for the original problem.
### Example
Admissible heuristics can be derived from
the exact solution cost of a relaxed version of the problem
Admissible heuristics for the 8-puzzle:
* h1 number of misplaced tiles
* h2 Manhattan distance
If the rules of the 8-puzzle are relaxed so that
a tile can move anywhere (instead of just to the adjacent empty square) then h1(n) gives the exact number of steps of the optimal solution
If the rules of the 8-puzzle are relaxed so that a tile can move one square in any direction, even onto an occupied square, then h2(n) gives the exact number of steps of the optimal solution