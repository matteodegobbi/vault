#opresearch 
# LP
## Convex programming
Global, local optimality
Convex combination
Convex set
Intersection of convex sets
Convex function
Theorem set described by convex inequalities is convex (1.1.1)
Theorem global optimality for convex programming (1.1.2)
## Linear programming
Linear program
Canonical form and standard form
Conversions, canonical, standard, free variables
## Geometry of linear programming
Affine half-space, hyperplane
Convex polyhedron, polytope
Vertex of a polyhedron
Minkowski-Weyl theorem (no proof) (4.1.1)
Theorem on existence of optimal vertex  (4.1.2)
<mark style="background: #FF5582A6;">Definition of basis, partition of A and x</mark>
<mark style="background: #FF5582A6;">Basic solution, basic feasible solution</mark>
Degenerate basis
<mark style="background: #FF5582A6;">Theorem on equivalence of BFSs and vertices (4.1.3)</mark>
Corollary on optimality of BFSs (just apply 2 previous theorems)
## Simplex method
Reduced cost vector
Theorem on optimality test (4.2.1)
Change of basis
Canonical form wrt basis for a system
Update of inverse of basis matrix
Tableau form of simplex
2-phase method how to do it (including canonical tableau) and possible cases
Convergence and degeneracy
Bland's Rule
Theorem on convergence of Simplex (4.2.2)
## Duality
Valid inequality
<mark style="background: #FF5582A6;">Farkas Lemma (5.1.1)</mark>
<mark style="background: #FF5582A6;">Primal to dual conversions </mark> (practical exercise in the exam)
Proposition Dual of dual (5.3.1)
Theorem Strong duality (5.3.1)
Theorem weak duality (5.3.2)
Corollary on possible combinations primal/dual (5.3.1)
Optimality conditions, both versions
Analysis of primal simplex in light of optimality conditions
Dual simplex
<mark style="background: #FF5582A6;">Sensitivity analysis</mark>

---
# ILP
## Integer linear program
Integer linear program, assumptions
Equivalent and ideal formulations
Convex hull
## Unimodularity
Unimodularity
Theorem on ideal formulation if unimodular (6.2.1)
Total Unimodularity
Theorem on ideal formulation if totally unimodular (6.2.2) (forse proof semplificata)
Theorem on sufficient condition for TUM (6.2.3)
Proposition on equivalent conditions to TUM
## Cutting plane
Definition of cut
Chvatal inequalities
Gomory cuts (integer and fractional form)
## Branch and bound
Branching, branching variable, branching tree
Branching constraints active at a node
Fathoming criteria
Convergence argument (informal)
MANCA PARTE IMPLMENTTION



---
# Graphs
## MST - 7.5
ILP model for MST
Assumptions for MST 
Theorem identifying edges belonging to MST (7.5.1)
?MST algorithm (generic)
Prim's algorithm
Kruskal's algorithm

## Paths - 7.6
?Pathfinding algorithm for reachability
ILP for Shortest Paths
Theorem identifying cost of shortest path when $c_{ij} \ge 0$ (7.6.2)
Dijkstra's algorithm
Theorem on triangular operation (7.6.3)
Floyd-Warshall algorithm
TODO AGGIUNGI PROJECT PLANNING/CPM

## Flow Problems - 7.7
Flow network
Feasible flow
Max flow
Extensions of flow problems
Cut
Flow through a cut and value of flow
Capacity of a cut
Theorem on flow through a cut (7.7.1)
Theorem relating flow through a cut and capacity of cut (weak duality) (7.7.2)
Min Cut, saturated arc and residual network
Theorem identifying flow optimality with residual network (7.7.3)





--- 
Esercizi numerici
Transform LP in Dual with rules
Ford Fulkerson
CPM????
Primal Simplex
Dual Simplex
Gomory cosa?????
sensitivity analysis of a tableau
matrice e' tum?
branch and bound applicazione a un esempio