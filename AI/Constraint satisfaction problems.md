#ai 
In standard [[Problem solving agents and search|search]] problems, states: 
* Atomic (“black box” with no internal structure) 
* Evaluated by domain-specific heuristics
* Tested to see whether they are goal states 
In CSPs: a factored representation for each state  
* State is defined by variables $X_i$ with values from domain $D_i$
* Goal test is a set of constraints specifying allowable combinations of values for subsets of variables
* Solution: one value for each variable that satisfies all the constraints
Allows useful general-purpose algorithms to solve complex problems
* with more power than standard search algorithms
* general-purpose heuristics rather than problem-specific heuristics
The main idea of algorithms for solving CSPs is to eliminate large portions of the search space all at once by identifying variable/value combinations that violate the constraints.

# Definition of a constraint satisfaction problem
* Set of variables $X = \{X_1,X_2,\dots,X_n\}$ 
* Set of domains $D = {D_1,D_2,\dots,D_n}$ 
	* Each domain $D_i$ consists of a set of allowable values for variable $X_i$.
	* In many cases the domain is assumed to be the same for all variables
* Set of constraints $C = \{ c_i =(scope_i , rel_i ) | i=1,\dots,h\}$
	* $scope_i$ : subset of $X$, the variables that are constrained by $c_i$
	* $rel_i$ : is a relation and tells us which simultaneous assignments of values to variables in $scope_i$ are allowed

State: defined by an assignment of values to some or all of the variables, $\{X_i = v_i, X_j = v_j , \dots\}$ 
Assignment can be:
* Consistent: it does not violate any constraints
* Complete: every variable is assigned
* Partial: only some of the variables are assigned
Solution: a consistent and complete assignment.

# Example map coloring
![[Pasted image 20240326140924.png]]
![[Pasted image 20240326140936.png]]
![[Pasted image 20240326140948.png]]
Other examples likes 3-SAT, N-Queens and Cryptarithmetic can be found in [[8_AI6-csp-2024-02.pdf]].
# Why CSP? 
A natural representation for many problem. We already have a CSP-solving system, it is often easier to solve a problem using it than to design a custom solution using another search technique.
CSP solvers are faster than state-space searchers because the CSP solver can quickly eliminate large parts of the search space.
[[7_AI6-csp-2024-01.pdf|Example why they are faster pag 11]].

# Varieties of CSPs
We consider only CSPs with discrete variables and finite domains: 
* n variables, domain size d
* e.g., variables WA, NT, Q, NSW, V, SA, T in the map coloring problem and each variable has the domain Di = {red, blue, green}
# Varieties of constraints 
* Unary constraints involve a single variable, e.g., SA ≠ green
* Binary constraints involve pairs of variables e.g., SA ≠ WA
* Higher-order constraints involve 3 or more variables
* Global constraints involve an arbitrary number of variables e.g., `Alldiff`, which says that all of the variables involved in the constraint must have different values

Binary CSP: CSP where each constraint relates two variables. 
Important: Any CSP can be converted into a CSP with only binary constraints
# Backtracking search
In principle we could use a DFS search starting from an empty assignment and each time assigning a value to an unassigned value, failing when there are no legal assignments and stopping if the assignment is complete. This approach would lead to a tree with $n!d^{n}$ leaves even if only $d^{n}$ complete assignments are possible.

We can use the fact that variable assignments are commutative -> we only need to consider a single variable at each level in the search tree so the number of leaves becomes $d^{n}$.
![[Pasted image 20240430180548.png]]
An example of backtracking:
![[Pasted image 20240430180621.png]]
## Backtracking heuristics 
We can use general purpose methods (heuristics) to improve efficiency of backtracking:
* Which variable should be assigned next?
* In what order should its values be tried?
### Most constrained variable
When we select the unassigned variable to try next we choose the one with the least amount of legal values. The rationale is that this will lead the branches of the tree that don't contain a solution to fail first.
![[Pasted image 20240430181004.png]]
### Most constraining variable 
With this heuristic we choose first the variable that is involved in the most constrains with unassigned variables, we can use this as a tie breaker among most constrained variables (previous heuristic) to improve the efficiency.
![[Pasted image 20240430181248.png]]
### Least constraining value
After having chosen a variable we need to choose an ordering of the domain values: we can choose first the least constraining values -> the ones that rule out the fewest values in the remaining unassigned variables, this leads to succeeding first when it's possible.
This value ordering doesn't matter if we want all the solutions or if there is no solution because we have to consider all values.

## Improving backtracking
### Backjumping
Until now we only saw a version of backtracking called chronological backtracking which backtracks to the previous variable to try another value. Sometimes this leads to useless steps, for example if the conflict isn't between the current and previous variable all the values we try for the previous variable will not lead to a consistent assignment.

If we use backjumping we backtrack to a variable that might fix the problem, the set of these variables is called the conflict set.
This fixes the problem where we kept trying values for a variable that is not in conflict with the assignment.

### No-good
This technique is used to avoid running into the same problem multiple times and avoiding redundant work.
Whenever we encounter a conflict we learn a new constraint by finding the minimum set of variables that cause the problem, this set of variables and their corresponding assignment is called no-good.
We record the no-good by adding the new constraint to the CSP.

### Forward checking 
It's a technique (of constraint propagation) to provide early detection for some failures.
We keep track of remaining legal values for unassigned variables and terminate the search when any variable has no legal values.

Forward checking propagates information from assigned to unassigned variables, but doesn't provide early detection for all failures. Example in the pdf [[10_AI6-csp-2024-04.pdf]].

Constraint propagation is: using constraints to reduce the number of legal values for a variable -> this can reduce the legal values for another variable.
It may be interleaved with search or may be done as a preprocessing step, before search starts. Sometimes it can solve the whole problem, so no search is required.
The key idea is local consistency. By enforcing local consistency in each part of the constraint graph inconsistent values are eliminated.
There are different types of local consistency.

### Node consistency
A variable (node in the constraint graph) is node -consistency if all the values in its domain satisfy the variable unary constraints.
To make a variable node consistent we remove from its domain all the values incompatible with its unary constraint.

A CSP network is node-consistent if every variable in the network is node-consistent

Since all unary constraint can be satisfied by applying node-consistency and all n-ary constraint can be turned into binary constraints we will focus on only the CSPs with binary constraints.

### Arc consistency
Used to make each arc consistent -> variables are arc consistent if its domain satisfies its binary constraints.

If there's is a binary constraint between Xi and Xj, Xi is arc consistent wrt Xj iff for every value in Xi's domain there exists a value in Xj's domain s.t. the binary constraint is satisfied.
(This definition is not symmetric be careful)

Arc consistency detects failure earlier than forward checking. [[10_AI6-csp-2024-04.pdf]]
Can be run as a preprocessor on the CSP or after each assignment.

We can use the AC-3 algorithm to mantain arc consitency:
![[Pasted image 20240503145455.png]]
Complexity of AC-3:
For binary CSPs
* n: number of variables
* c: number of binary constraints (arcs)
* d: domain size

Time: $O(cd^{3})$:
* Each arc (Xk,Xi) inserted in the queue only d times because Xi has at most d values to delete
* Checking consistency of an arc can be done in $O(d^{2})$ time
Thus, $O(cd^{3})$ total worst-case time

Is arc consistency enough?
By using AC we can remove many incompatible values
* Do we get a solution?
* Do we know if there exists a solution?
Unfortunately, the answer to both above questions is NO:
![[Pasted image 20240503145712.png]]

Sometimes we have a solution/failure after AC
* A domain is empty -> no solution exists
* All the domains are singleton -> we have a solution

### Path consistency
Stronger consistency than arc consistency, requires it on more than one constraint.
A two-variable set {Xi, Xj} is path-consistent with respect to
a third variable Xm if ∀ assignment {Xi = a, Xj = b} consistent with the constraints on {Xi , Xj} ∃ assignment to Xm that satisfies:
* the constraints on {Xi , Xm}
* the constraints on{Xm , Xj }

This is called path consistency since it is like considering a path from Xi to Xj with Xm in the middle.

Path consistency does not guarantee that all the constraints among  the variables on the path are satisfied only the constraints between the neighbouring variables must be.
PC is still not a complete technique, but it's stronger than arc consistency.

If forward checking (or a stronger consistency check like AC) is applied then backjumping is not neeeded.



