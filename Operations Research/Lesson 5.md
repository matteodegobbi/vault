#opresearch 
10/10/2023
Continuing from [[Lesson 4]]...
If $(B^{-1}b)_i=0$ for any $i\in 1,\dots,m$ we have a degenerate basic solution 

---

Theorem A point $x\in P$ is a vertex of $P:= \{ x\ge0 : Ax=b \} \ne \emptyset$ (standard form with equations)
if and only $x$ is a BFS (Basic Feasible Solution) of the system $Ax=b$.

_Proof_:
First we prove: "$x$ is a BFS $\to$ $x$ is a vertex".
WLOG we put the components $> 0$ at the start of the vector (like we did previously with coloring the components) $x=[x_1,x_2,\dots,x_k,0,0,\dots,0]^T$ for $k\ge0$
$\to A_1,A_2,\dots,A_k$ are linearly independent because since $x_1,x_2,\dots,x_k$ are basic variables ........TODO......

Assume, by contradiction, $x$ is not a vertex. $\exists y,z, \in P, y\ne z, \lambda \in (0,1): \ x=\lambda y+(1-\lambda)z$ 
I claim
$y=[y_1,y_2,\dots,y_k,0,0,\dots,0]^T$
$z=[z_1,z_2,\dots,z_k,0,0,\dots,0]^T$
because if one of the $z_i$ or $y_i$ was $\ne 0$ then we would have $x_i \ne 0$ because we are summating two positive numbers when we do a convex combination with $0<\lambda<1$ (this is why we need an open interval for $\lambda$)
$y\in P\to A_1 y_1+\dotsi+A_k y_k = b$ $(\star)$
$z\in P\to A_1 z_1+\dotsi+A_k z_k = b$ $(\star\star)$
$(\star)$-$(\star\star)=A_1(y_1-z_1)+\dotsi+A_k(y_k-z_k)=0$
$\alpha_i\triangleq y_i-z_i$
where $\alpha_1,\dots,\alpha_k$ are NOT ALL $=0$.
$\to A_1+\dotsi+A_k$  are linearly dependent because we are getting 0 for a linear combination with coefficients that are not all zeroes.
This is a contradiction $\contradiction$
This means that $x$ is a vertex. $\square$

Now we need to prove the other implication (the theorem says _iff_).
We will prove: "$x$ is a vertex $\to x$ is a BFS" (we already know it is feasible because it's a vertex, we need to prove only that it is a basic solution) 

Again we put the $k$ components $>0$ at the start of the vector as we did before.

$x\in P \to A_1 x_1,A_2 x_2,\dots,A_k x_k=b$ $(\triangle)$
now we have two possible cases:
i. $A_1,A_2,\dots,A_k$ are linearly independent 
$x=[x_1,x_2,\dots,x_k,0,\dots,0,|0,\dots,0]^T$ 
in presence of degeneracy we dont have all the basis only k vectors we need another m-k
$A=[A_1,A_2,\dots,A_k,A_{k+1},\dots]$

######RIGUARDA STA PARTE

$B\to \begin{bmatrix}x_B=B^{-1}b\\ \hline x_F=0\end{bmatrix}$
to compute the basis we take the first k columns and we compute the other ones with B^-1 b

ii. $A_1,A_2,\dots,A_k$ are lin dependent
$\to \exists \alpha_1,\dots,\alpha_k$, not all =0 such that 
$(\triangle\triangle)$ $A_1 \alpha_1 + A_2 \alpha_2 +\dotsi +A_k \alpha_k$

take $\epsilon \geapprox 0$
$(\triangle)-\epsilon(\triangle\triangle)\to (x_1+\epsilon)###################$

############ contnua dal pdf

for $\epsilon$ suffieciently small, $y,z \ge 0$
Also:
$Ay=b$
$Az=b$
$\to y,z \in P,\ y\ne z$ (spiegazione nel video)
$x=\frac{1}{2}x+\frac{1}{2}z\to x$ is not a vertex, this is a contradiction $\contradiction$.
So case ii) cannot arise $\to A_1,\dots,A_k$ are linearly independent. $\square$

Controllare tutta questa dimostrazione dal libro

---
We have $m \choose n$ possible choices of $n$ columns out of $m$ to enumerate all the vertices
and we want to use a better algorithm.
George Dantzig developed:
1. Optimality test
2. Change the basis
$Ax=b,\ x\ge 0$, current basis $B$ we rewrite the system in canonical form in respect to the current base
$x_B=B^{-1}b-B^{-1} F x_F$
For every $x\in P:$
$c^Tx=[c_B^T, c_F^T] \begin{bmatrix} x_B\\x_F \end{bmatrix}=c_B^T x_B + c_F^T x_F=$
$c_B(B^{-1}b-B^{-1} F x_F)+c_F^T=c_B B^{-1}b + 0^T x_B + (c_F^T -c_B^T B^{-1} F) x_F$  
												c_0              \bar c_F^T
												cost of the      reduced cost vector
												current BFS


If $\bar {c_F} \ge 0$ (component by component )then $c_T x \ge 0$
this is the optimality test (sufficient condition to stop)
$\bar {c_F} \triangleq c_F^T -c_B^T B^{-1} F$
If $\bar {c_F} \ge 0$ then we can stop.

(we dont need to compute the reduced cost vector components for basic components because we already know its 0)