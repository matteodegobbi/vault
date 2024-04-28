#ai
We can use some heuristic algorithms to obtain more efficient solutions to CSPs, since in [[Local Search|local search]]  we don't generate all assignments systematically we lose completeness.

We start from complete but inconsistent assignments and we construct next assignments in such a way that the constraint violation is smaller, doing only small changes in the process.

# Terminology
The search space is the set of all complete variable assignments.
The set of solutions is a subset of the search space where the assignments satisfy all constraints.
Neighborhood relation: indicating what assignments can be reached by a search step given the current assignment during the search procedure, in CSPs it's all the assignments differing on one value of one variable.
Evaluation function: mapping each assignment to the number of constraints it violates.
Initialization function: returns an initial assignment chosen randomly.
Termination criterion: stopping the search when satisfied, in CSPs when a solution is found or when the max number of steps is exceeded.
Step function: given an assignment, its neighborhood, and the evaluation function returns the new assignment to be explored by the search.
Set of memory states (optional): holding information about the state of the search mechanism.

The different algorithms are characterized by the different step functions and the use of memory.

The point of local search is eliminating violated constraints.

# Algorithms
## Min-Conflicts
We use an heuristic for choosing a new value for a variable: we choose the value that results in the minimum number of conflicts with other variables.

Conflict set of an assignment: set of variables involved in some constraint that assignment is violating.

`Min-conflict LS procedure:`
Starts at a randomly generated assignment
At each step of the search:
* Selects a variable from the current conflict set
* Selects a value for that variable that minimizes the number of violated constraints. If there are multiple choices choose one randomly
neighborhood = different values for the selected variable
neighborhood size = (d-1) (the previous value cannot be chosen).
## Escaping local minima 
The evaluation function can have:
* local minimum - a state that is not minimal and there is no state with better evaluation in its neighbourhood
* strict local minimum - a state that is not minimal and there are only states with worse evaluation in its neighbourhood 
* global minimum - the state with the best evaluation
* plateau - a set of neighbouring states with the same evaluation
![[Pasted image 20240426211724.png]]
A local search procedure may get stuck in a local minima.
Techniques for preventing stagnation:
* restart
* allowing non improving steps -> random walk
* changing the neighborhood -> tabu search
## Restart 
Re-initialize the search after MaxSteps (non-strictly
improving) steps
* New assignment chosen randomly
* Can be combined both with hill-climbing and Min-conflicts
* It is effective if MaxSteps is chosen correctly and often it depends on the instance
## Random walk
Add some “noise” to the algorithm, random walk:
* a new assignment from the neighbourhood is selected randomly (e.g., the value is chosen randomly)
* such technique can hardly find a solution so it needs some guidance
Random walk can be combined with the heuristic guiding the search via probability distribution:
* p: probability of using the random walk (noise setting)
* (1-p) : probability of using the heuristic guide
It's a version of Min-conflicts with random walk

## Tabu search
Being trapped in local minimum can be seen as cycling
How to avoid cycles in general?
Remember already visited states and do not visit them again -> memory consuming (too many states)
It is possible to remember just a few last states to prevent “short” cycles 
We use a Tabu list = a list of forbidden states
* Tabu list has a fix length k (tabu tenure)-> “old” states are removed from the list when a new state is added
* State included in the tabu list is forbidden (it is tabu)
## Constraint weighting
Can help concentrate the search on important constraints
Each constraint is given a numeric weight (initially all 1)
At each step of the search:
* We choose a variable/value pair to change that leads to the lowest total weight of all violated constraints
* Weights are then adjusted by incrementing the weight of each constraint violated by the current assignment
# Structure of CSPs
MANCA TODO
