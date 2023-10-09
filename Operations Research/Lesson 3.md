#opresearch 
4/10/2023
# Linear programming
## Notation
$f(x)=\sum_{i=1}^n{c_j x_j}$ linear function (particular case of convex function)
$g_i(x)=b_i-\sum_{j=1}^n{c_j x_j}\le0 \ \forall i=1,\dots,m$ affine inequality $(\star)$
we can simplify notation using matrices: $c,x\in \mathbb{R}^n$
$\sum_{i=1}^n{c_j x_j}=\langle c,x \rangle=c^T x$ (row vector $\times$ column vector)

$$\begin{bmatrix}   
a_{11} & \dotsi & a_{1n}\\   
\vdots & a_{ij}& \vdots\\
a_{m1} & \dotsi & a_{mn}\\   
\end{bmatrix}
$$
$A_i$ is the i-th column of the matrix $A=[A_1,\dotsi,A_n]$

We can write $(\star)$ as:
1. $\sum_{j=1}^n{c_j x_j}\ge b_i \ \forall i=1,\dots,m$ 
2. $a_i^T x\ge b_i\ \forall i=1,\dots,m$
3. $A x\ge b\ \ \ b\in \mathbb{R}^m$ in which $Ax=A_1 x_1+ \dotsi +A_n x_n$

---
# Example of a linear programming problem

$$\begin{cases}
\min -x_1 -x_2 \\
6x_1+4x_2\le 24 (I) \\
3x_1-2x_2\le 6 (II)\\  
x_1\ge 0 \\
x_2\ge 0 \\
\end{cases}
$$
##disegno copia

If we keep the same constraints but with a different objective function we can find different optimal solution.
A,B,C,D are called the vertices of the polyhedron and an optimal solution will always be one of these vertices in linear programming. 
If the objective function is $0x_1+0x_2$ every point in $P$ is an optimal solution.

##disegno in R3 pdf 
##Simplex
Canonical form of linear programming:
$$
\begin{cases}
\min c^T x \\
Ax\ge b \\
x\ge0
\end{cases}
$$

Standard form of linear programming:
$$
\begin{cases}
\min c^T x \\
Ax = b \\
x \ge 0
\end{cases}
$$
We can use some tricks to go from inequalities to equalities and back (canonical $\leftrightarrow$ standard)

* $a_i^T x\ge b_i \leadsto a_i^T x -s_i= b_i$
* $a_i^T x\le b_i \leadsto a_i^T x +s_i= b_i$
s_i \ge 0 surplus or slack
* $a_i^T x = b_i \begin{cases}a_i^T x \ge b_i \\ a_i^T x \le b_i\end{cases}$

---
$x_i \lesseqgtr 0$ is free this is not valid for linear programing we need to use another trick:
$x_i=x_i^+ - x_i^-,\ \ \ x_i^+\ge0,\ \ x_i^-\ge0$
if we subsitute every occurence of $x_i$ with this trick we can then use linear programming

---

if we have $a_i^T < b_i$  a strict inequality we would want to get a $\le$ inequalty but we can't because if we have a strict inequality we are excluding the boundary of the polyhedron.
but we can approximate for example we can $< 3 \to \le 2.9999999999999$ 

<p style="color: YELLOW">⚠Important: In linear programming we need non strict inequalities, if we have &lt or &gt IT'S NOT A LINEAR PROGRAMMING PROBLEM </p> 

---
