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
* The same state can appear multiple time 
* Outgoing edges from a node -> all possible actions available in the state represented by the node

Leaf node: a node with no children in the tree
Frontier: The set of all leaf nodes available for expansion at any given point

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
