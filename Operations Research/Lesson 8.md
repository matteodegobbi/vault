#opresearch 
17/10/2023
Original problem:
$$
\begin{cases}
\min c^T x =z\\
Ax =b \\
x\ge0
\end{cases}
$$
WLOG $b\ge0$ (we can just multiply by $-1$).

We need to find an initial basis:
we consider an artificial problem
$$
\begin{cases}
\min w=\sum_{i=1}^m{y_i}\\
Ax+Iy = b \\
x,y\ge0
\end{cases}
$$
$y\in\mathbb{R}^m$ artificial variable $(x,y)$ where if $y=0$ we have a feasible solution to the original problem. 
Solve artificial problem and get an optimal solution $(x^*,y^*)$
If optimal solutions $w^*=0 \to y_1^*=\dotsi=y_m^*=0\to x^*$ is a feasible solution of the original problem. 

---
# Example at page 51.

---
# Degenerate cases
1. What if $w^*>0, (\ne0)$? The original problem is infeasible: $\nexists (x^*,y^*)$ for the original problem with $y^*=0$, at the end of phase 1 we will know if the problem is infeasible.
2. $w^*=0\to y_1^*=\dotsi=y_m^*=0$ we said (SCRITTO A MATITA NEL LIBRO) ~~"all $y^*$ are non basic"~~ what if $y_i$ is basic (degenerate), then we will miss a column to remove
	if $\exists\ \  \overline{a_{th}}$ i can just make a pivot operation on it. ####DISEGNO SUL FOGLIO

3. What if i only have zeroes in row t in x portion of the tableau? 
###FOGLIO CONTROLLA ANCHE LIBRO

---

# Example at page 52 (unfeasible, case 1.)
# Example at page 53 (basic degenerate $y_i$, case 2.)

---
