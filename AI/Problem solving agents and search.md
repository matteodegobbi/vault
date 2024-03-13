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
(pseudocode problem solving agent in pdf [[AI3-search-uninf-2023.pdf]] pag 8)
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
[[AI3-search-uninf-2023.pdf|vacuum example page 21]].

# Search tree
