#ai
In many optimization problems the path from the start node to the goal is irrelevant, the goal state itself is the solution.
State space = set of "complete" configurations, find configuration satisfying constraints, e.g., n-queens
In such cases, we can use local [[Problem solving agents and search|search]] algorithms
* keep a single "current" state
* try to improve it
[[6_AI4-local-search.pdf|Example n queens pag 4]]

## Landscape
Local search algorithms explore the state-space landscape
A landscape has
* location (defined by the state)
* elevation (defined by the value of heuristic cost function or objective function)
The aim is to find:
* a global minimum (lowest valley) if elevation corresponds to cost
* a global maximum (highest peak ) if elevation corresponds to objective function
# Hill-climbing search
![[Pasted image 20240323092702.png]]
Hill climbing often gets stuck for the following reasons:
* Local maxima: a peak that is
	* higher than each of its neighboring states
	* lower than the global maximum
* Plateaux: a flat area of the state-space landscape
	* flat local maximum, from which no progress is possible
	* shoulder, from which progress is possible
![[state-space-landscape-Lazebnik-2018.png]]
## Hill-climbing variants
* Stochastic hill climbing: chooses at random from the set of all improving neighbors

* First-choice hill climbing jumps to the first improving neighbor found
* Random-restart hill climbing: series of hill climbing runs until a goal is found (It will find a good solution very quickly)
# Simulated annealing

## Hill climbing and Random Walk recap
* Hill-climbing algorithm that never makes “downhill” moves toward states with lower value is incomplete because it can get stuck on a local maximum
* Purely random walk: moving to a successor chosen uniformly at random from the set of successors is complete but extremely inefficient
Idea: to combine hill climbing with a random walk that yields both efficiency and completeness

Simulated annealing: a version of stochastic hill climbing where some downhill moves are allowed
* If the move improves the situation -> always accepted
* Otherwise -> accepted with some probability less than 1
The downhill moves are accepted early in the annealing schedule then accepted less often as time goes on.

![[Screenshot from 2024-03-23 09-38-07.png]]
One can prove: If T decreases slowly enough, then simulated annealing search will find a global optimum with probability approaching 1.

# Local beam search
Keep track of k states rather than just one
* Start with k randomly generated states
* At each iteration all the successors of all k states are generated
	* If any one is a goal state, algorithm stops
	* Else select the k best successors from the complete list and repeat (they could be all successors of the same node)
# Genetic algorithms 

