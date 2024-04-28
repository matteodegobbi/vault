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



TODO: 
DA AGGIUNGERE IL RESTO DI ROBA SUI CSP
