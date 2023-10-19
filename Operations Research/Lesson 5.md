#opresearch 
10/10/2023
Continuing from [[Lesson 4]]...
<mark style="background: #D2B3FFA6;">Definition</mark>: If $(B^{-1}b)_i=0$ for any $i\in 1,\dots,m$ we have a degenerate basic solution ($B^{-1}b$ has one or more 0 components).

---

<mark style="background: #FFB86CA6;">Theorem</mark>: A point $x\in P$ is a vertex of $P:= \{ x\ge0 : Ax=b \} \ne \emptyset$ (standard form with equations)
if and only if $x$ is a BFS (Basic Feasible Solution) of the system $Ax=b$.

_Proof_ (also at page 37):
First we prove: "$x$ is a BFS $\to$ $x$ is a vertex".
WLOG we put the components $> 0$ at the start of the vector (like we did previously with coloring the components) $x=[x_1,x_2,\dots,x_k,0,0,\dots|,0,\dots,0]^T$ for $k\ge0$ ($m$ components up to the $|$ and $n-m$ after the $|$, $k$ could be less than $m$ because the base could be degenerate) 
$\to A_1,A_2,\dots,A_k$ must be linearly independent because since $x_1,x_2,\dots,x_k$ are basic variables then the corresponding columns in $A$ must also be basic columns (meaning they appear in $B$) in order to be basic they need to be linearly independent.

Assume, by contradiction, $x$ is not a vertex, then by definition of vertex: $\exists y,z, \in P, y\ne z, \lambda \in (0,1): \ x=\lambda y+(1-\lambda)z$ 
I claim:
$y=[y_1,y_2,\dots,y_k,0,0,\dots,0]^T$
$z=[z_1,z_2,\dots,z_k,0,0,\dots,0]^T$
because if one of the $z_i$ or $y_i$ were $\ne 0$ then we would have $x_i \ne 0$ because we are summing two positive numbers when we do a convex combination with $0<\lambda<1$ (this is why we need an open interval for $\lambda$)
$y\in P\to A_1 y_1+\dotsi+A_k y_k = b$ $(\star)$
$z\in P\to A_1 z_1+\dotsi+A_k z_k = b$ $(\star\star)$
(since they belong in $P$ they both satisfy the system in standard form)
$(\star)$-$(\star\star)=A_1(y_1-z_1)+\dotsi+A_k(y_k-z_k)=0$
$\alpha_i\triangleq y_i-z_i$
where $\alpha_1,\dots,\alpha_k$ are NOT ALL $=0$ (because we have $y\ne z$).
$\to A_1+\dotsi+A_k$  are linearly dependent because we are getting 0 for a linear combination with coefficients that are not all zeroes (definition of linear dependence).
This is a contradiction. ↯
This means that $x$ must be a vertex. $\square$

Now we need to prove the other implication (the theorem says _iff_).
We will prove: "$x$ is a vertex $\to x$ is a BFS" (we already know it is feasible because it's a vertex, we need to prove only that it is a basic solution). 

Again we put the $k$ components $>0$ at the start of the vector as we did before.

$x\in P \to A_1 x_1+A_2 x_2+\dotsi+A_k x_k=b$ $(\triangle)$
now we have two possible cases:
i. $A_1,A_2,\dots,A_k$ are linearly independent 
$x=[x_1,x_2,\dots,x_k,0,\dots,0,|0,\dots,0]^T$ 
in presence of degeneracy we dont have all $m$ vectors needed in the basis, we only have $k$ vectors and we need another $m-k$ we can just take another $m-k$ linearly independent vectors (we can always do this because the have $m$ components)
$B=[A_1,A_2,\dots,A_k,A_{k+1},\dots]$ since $x_i=0$ for $i>k$ we have that $x$ is a basic solution associated to $B$.

$B\to \begin{bmatrix}x_B=B^{-1}b\\ \hline x_F=0\end{bmatrix}$
to compute the components of $x$ we take the first $k$ columns and we can compute $x_B$  with $B^{-1} b$, the other $n-m$ non basic components will be 0.

ii. $A_1,A_2,\dots,A_k$ are linearly dependent
$\to \exists \alpha_1,\dots,\alpha_k$, not all =0 such that 
$(\triangle\triangle)$ $A_1 \alpha_1 + A_2 \alpha_2 +\dotsi +A_k \alpha_k=0$

take $\epsilon \gtrsim 0$
$(\triangle)-\epsilon(\triangle\triangle)\to (x_1-\epsilon \alpha_1)A_1+\dotsi+(x_k-\epsilon \alpha_k)A_k=b$
$(\triangle)+\epsilon(\triangle\triangle)\to (x_1+\epsilon \alpha_1)A_1+\dotsi+(x_k+\epsilon \alpha_k)A_k=b$
we define:
$y\triangleq[x_1-\epsilon \alpha_1,\dots,x_k-\epsilon \alpha_k,0,\dotsi,0]$
$z\triangleq[x_1+\epsilon \alpha_1,\dots,x_k+\epsilon \alpha_k,0,\dotsi,0]$

for $\epsilon$ sufficiently small, $y,z \ge 0$ (in every component)
Also:
$Ay=b$
$Az=b$
$\to y,z \in P,\ y\ne z$ 
$x=\frac{1}{2}y+\frac{1}{2}z\to x$ is not a vertex (it can be expressed as a convex combination of two points $\in P$), this is a contradiction ↯.
So case ii) cannot arise $\to A_1,\dots,A_k$ are linearly independent. $\square$

also look at this proof in the book <mark style="background: #FF5582A6;">(annotate it!)</mark>

<mark style="background: #FF5582A6;">GEOMETRIC INTERPRETATION IN THE VIDEO</mark>

---
# The simplex method
In a naive solution we could enumerate all the basic solutions to the problem and identify the feasible one that minimizes the objective function.
We have $m \choose n$ possible choices of $n$ columns out of $m$ to enumerate all the vertices (BFSs)
and we want to use a better algorithm.
George Dantzig developed an algorithm that consists of:
1. Optimality test
2. Change the basis
$Ax=b,\ x\ge 0$, current basis $B$ we rewrite the system in canonical form in respect to (WRT) the current base
$(\diamond)\ \ x_B=B^{-1}b-B^{-1} F x_F$
For every $x\in P:$
$c^Tx=[c_B^T, c_F^T] \begin{bmatrix} x_B\\x_F \end{bmatrix}=c_B^T x_B + c_F^T x_F=^{(\diamond)}$
$=c_B^T(B^{-1}b-B^{-1} F x_F)+c_F^T x_F=\underbrace{c_B^T B^{-1}b}_{c_0}+ 0^T x_B +\underbrace{ (c_F^T -c_B^T B^{-1} F)}_{\overline{c_F}^T} x_F$  

where $c_0$ is the cost of the current BFS and $\overline{c_F}^T$ is the reduced cost vector for out of basis components WRT $B$.

If $\overline {c_F} \ge 0$ (component by component )then $c^T x \ge c_0$ for every $x\ge0$ (add $c_0$ on both sides of equation) 
this is the optimality test (sufficient condition to stop)
because $c_0$ is the cost associated with the BFS $x=\begin{bmatrix}B^{-1}b\\ \hline 0\end{bmatrix}$ 
$\overline {c_F} \triangleq c_F^T -c_B^T B^{-1} F$
Summarizing if $\overline {c_F}^T \ge 0$ then we can stop because we found an optimal solution.

(we don't need to compute the reduced cost vector components for basic components because we already know its 0, in the book this is not clearly stated)

---
