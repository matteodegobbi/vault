#opresearch 
10/10/2023
Definition: $\{ x\in\mathbb{R}^n:\alpha^Tx\le\alpha_0 \}$ is called an affine half space.
Definition: $\{ x\in\mathbb{R}^n:\alpha^Tx=\alpha_0 \}$ is called an hyperplane.
The set of feasible points $P=\{x\in\mathbb{R}^n:Ax\geqq b\}$ 
($\geqq$ means that for every row it could either be $\le$ or $=$)

Definition: the intersection of a FINITE number of affine half spaces and/or hyperplanes is a convex polyhedron. 
(We need to specify finite because otherwise we can get a smooth surface which is not a polyhedron)

A polyhedron can be unbounded.#########DISEGNO

Sometimes we can show that the polyhedrons of interest are in a ball of radius M for example in the nurses we might constrain M to 1000.

Definition: a polytope is a bounded polyhedron.

Definition: a point $x\in P$ is said to be a vertex of $P$ if it cannot be expressed as the STRICT convex combination of two DISTINCT points $y,z \in P$

(We get to the vertices deleting from the polyhedron all points that can be expressed as a STRICT convex combination of two DISTINCT points)

---

# Theorem of Minkowski-Weyl

We have a polytope (we are then assuming bounded polyhedra) ###DISEGNO with vertices $x^1,x^2,\dotsi,x^k \in P$, For every $y \in P, \exists \lambda_1,\dotsi,\lambda_k \ge 0$
1. $\sum_{i=1}^k{\lambda_i}=1$
2. $y=\sum_{i=1}^k{\lambda_i x^i}$

It is important that it's a polytope because if it's unbounded we have a "missing vertex" and we cannot express ALL points with a convex combination.
(some points in the direction where the polyhedron is unbounded cannot be expressed as a convex combination of two vertices)
no proof.

---
# Optimal solution in LP will always be a vertex
Theorem: $P$ bounded polyhedron (polytope) $\to \min_{x\in P}{c^T x}$ has an optimal solution arising on a vertex of P.

Proof: Let $x^1,x^2,\dotsi,x^k$ be the vertices of $P$.
Compute $z^* = \min\{c^T x^i :i=1,\dotsi,k\}$
(we claim $z^*$ is the optimal solution, we need to prove this)
Now take any $y\in P \to^{MW} \exists\lambda\ge0$, $\sum_{i=1}^k{\lambda_i}=1$, $y=\sum_{i=1}^k{\lambda_i x^i}$
$c^T y=c^T \sum_{i=1}^k{\lambda_i x^i}=\sum_{i=1}^k{\lambda_i c^T x^i}\ge^{(\star)}\sum_{i=1}^k{\lambda_i z^*}=z^*$
$(\star)$ holds because we have $\lambda_i>0,\ \  c^T x^i \ge z^*$. $\square$

---

Example of lesson 3 
$$\begin{cases}
\min -x_1 -x_2 \\
6x_1+4x_2\le 24 (I) \\
3x_1-2x_2\le 6 (II)\\  
x_1\ge 0 \\
x_2\ge 0 \\
\end{cases}
$$but in standard form it becomes: 
$$\begin{cases}
\min -x_1 -x_2 \\
6x_1+4x_2 +x_3 = 24 (I) \\
3x_1-2x_2+x_4 = 6 (II)\\  
x_1,x_2,x_3,x_4\ge 0 \\
\end{cases}
$$
notice how different inequalities need a different slack variable
###DISEGNO
From the drawing we see how we can express the boundaries of the polytope as the points for which a variable (either original or slack) is 0.
Since this is true then we can express any vertex  as the intersection of two of those boundaries.
Vertex A $\to x_1=x_2=0$
Vertex B $\to x_2=x_4=0$
Vertex C $\to x_4=x_3=0$
Vertex D $\to x_1=x_3=0$

But we need to be careful, if we set $x_2=x_3=0$ we get the $\star$ point in the drawing but if we check the other components of this point, we will see that for $\star$ $x_4\le0$ so it violates the non negativity condition so it's not feasible and can't be a vertex.

If when we solve the system to check the other components we get either infinite or no solutions it means the two lines are parallel or coincident and this is of no interest for us because we cannot get a vertex in these two cases.

---
$A\in \mathbb{R}^{m\times n}$ with $m\le n$
In general $Ax=b$ $(x\ge0)$ 
Hp: all the rows of $A$ are linearly independent $\leftrightarrow \text{rank}(A)=m$
Definition: a basis $B$ of $A$ is a set of $m$ linearly independent columns of $A$
$A=\begin{bmatrix} A_1 | A_2 | \dotsi | A_n \end{bmatrix}\to B=\begin{bmatrix} A_{\beta[1]} | A_{\beta[2]} | \dotsi | A_{\beta[m]} \end{bmatrix}$ 
(we need the permutation $\beta[\cdot]$  because otherwise we would get the first $m$ columns)
$B\in \mathbb{R}^{m\times m}$ with $\det{B}\ne0$ because all the columns are linearly independet.

---

$Ax=b$
($A_1 x_1+ \dotsi +A_n x_n$)
Take any basis $B$
###ROBA DEI COLORI DAL FOGLIO
We can rewrite the matrix A and the vector x to divide the columns of two different color 
$A=[B|F]$
$X=\begin{bmatrix}x_B\\ \hline x_F\end{bmatrix}$

$Ax=\begin{bmatrix}B|F\end{bmatrix}\begin{bmatrix} x_B \\ \hline  x_F \end{bmatrix}=B x_B + F x_F=b$ 
For a system basis B since B is not singular we can
$B^{-1}(B x_B  =b-F x_F)\to x_B=B^{-1}b-B^{-1}F x_F$
this is the canonical WRT B


Given B there is a solution where we fix  $x=\begin{bmatrix}x_B=B^{-1}b\\ \hline x_F=0\end{bmatrix}$
1. $x_F=0$
2. $x_B= B^{-1}b$
If these two equalities hold $x$ is called a basic solutions to $B$.
	
And it is said feasible if $B^{-1}b\ge0$.

($B$ has $m$ columns and $F$ has $n-m$ columns)


---
