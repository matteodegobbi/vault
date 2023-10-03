#opresearch
3/10/2023
We have a mathematical optimization problem:
$x\in\mathbb{R}^n$
$f:\mathbb{R}^n\to\mathbb{R}$ objective function 
$X \subseteq \mathbb{R}^n$ feasible solution set
$\min_{x\in X} f(x)$, 3 possible outcomes:
1. $X=\emptyset$ "problem infeasible", in this case we can write "$\min=\infty$"
2. $f$ is unbounded from below "problem unbounded", in this case we can write "$\min=-\infty$"
3. An optimal solution $x^* \in X \ f(x^*)\le f(x) \ \  \forall x \in X$

Observation: in some optimization problems we need to search for the maximum but in this course we will always talk about minimization. If we want to maximize an objective function $f$ we can instead minimize $-f$ and we will find the same solution.

A solution $\tilde{x}\in X$ is a local minimum if $f(\tilde{x}) \le f(x) \ \ \forall x \in X : \| x-\tilde{x} \|_2 < \epsilon$ for a given $\epsilon >0$.
Local minima can be "easily" found searching when the gradient is 0 but this is only a locally optimal solution.

If we can assume some regularity conditions the local optimal solution will also be the global optimal solution, for this we need to assume
1. $X$ is convex.
2. the objective function $f$ is convex

Why do we need both?
For example if we have $f(x)=x_2$ and $X$ is not convex we can find a local optimal solution that is not a global optimal solution.
If we have a function that is not convex a locally optimal solution may not be the minimum because the function could "increase again after having decreased".
![[convexXandConvexf.png]]
---
# Convexity of a set
Definition: convex combination: $x,y \in \mathbb{R}^n$ $z=\lambda x+ (1-\lambda)y$ for $\lambda \in [0,1]$

The convex combination is said strict if $\lambda \ne0,1$.

Definition convex combination of $k$ points: $x^1,x^2,\dotsi,x^k \in \mathbb{R}^n$ $z=\sum_{i=1}^{k}{\lambda_i x^i}$, $\lambda_i>0$ and $\sum_{i=1}^{k}{\lambda_i}=1$
![[convComb.png]]
![[convHull.png]]

Definition: a set $X \subseteq \mathbb{R}^n$ is convex if $\forall x,y \in X \ \   \forall \lambda\in[0,1] \ \ z\triangleq\lambda x + (1-\lambda)y,\ \  z\in X$ 

![[convOrNonConvSet.png]]

# Intersection of two convex sets
The intersection of two convex sets is convex. Proof in the book (uses $D=A\bigcap B, \ z\in D \leftrightarrow z\in A,z\in B$)


---
# Convexity of a function
![[convFunc.png]]
Definition: $f:X\to\mathbb{R}$ objective function where $X$ is convex 
We say that $f$ is convex if $\forall x,y \in X\ \ \  \forall \lambda \in [0,1]$:
$z=\lambda x + (1-\lambda)y$
$(*)=\lambda f(x)+ (1-\lambda)f(y)$ to prove this we just need to prove this is correct for x and y (line given 2 points ecc, lambda =1 and lambda = 0)
$f(z)\le \lambda f(x)+ (1-\lambda)f(y)$ for $\lambda \in [0,1]$
$f(\lambda x + (1-\lambda)y)\le \lambda f(x)+ (1-\lambda)f(y)$ for $\lambda \in [0,1]$

---
# Set described by convex inequalities
We can prove a set is convex if it is defined as a set of inequalities:
$X=\{x\in \mathbb{R}^n: g_i(x)\le 0, \ \ \ i=1,\dots,m\}$
Th. 1.1.1: If $g_i(x)$ are convex then $X$ is convex.
(For example in the special case where all $g_i$ are linear $\to$ they are convex, like with the nurses example)
Proof: $X=\bigcap_{i=1}^m X_i$  $X_i\triangleq\{x\in \mathbb{R}^n: g_i(x)\le 0\}$ if we can prove that all $X_i$ are convex their intersection will be convex. 
For any $X_i$ and any two points $x,y\in X_i$ and any $\lambda\in[0,1]$: $z=\lambda x + (1-\lambda)y$ 
$g_i(z)=g_i(\lambda x + (1-\lambda)y)\le \lambda g_i(x)+(1-\lambda)g_i(y)$ the last step because of the convexity of $g_i$
And since $\lambda \ge 0,\ \ (1-\lambda)\ge 0$ because $\lambda \in [0,1]$ and $g_i(x)\le0,\ g_i(y)\le0$ because $x,y \in X_i$
then $g_i(z)\le 0$ which implies $z\in X_i$ and since we said this is true for every $\lambda$ we have that $X_i$ is convex. $\square$ 
   
---
# Local optimal = Global optimal if $f$ and $X$ are convex
Theorem: For the optimization problem $\min\{f(x):x\in X\}$
if $f,X$ are convex every local optimal solution is also globally optimal.
Proof on the pdf and another version is in the book.
![[localGlobalOptimalConvex.png]]

---

