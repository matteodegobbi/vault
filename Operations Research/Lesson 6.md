#opresearch 
11/10/2023
continued from [[Lesson 5]]...
The simplex method is comprised of two steps
1. Optimality test, done in the last lesson.
2. Change the basis
$\bar{c^T}=c^T =u^T A$
where $u^T=c_B^TB^{-1}$
let $h$:
$\bar{c^T_h}=c^T_h =u^T A_h <0$
$c^T x=c_B^T B^{-1}b+\bar c_h x_h+\dotsi\to c^T x = c_B^T B^{-1}b+\bar c_F^T x_F$ 
$x_B=B^{-1}b-B^{-1} F x_F$

$x_h:0\to \theta=$ max increase allowed
to change basis I keep all non basic variables to 0 and increase $x_h$ from 0 to theta in order to move along the edge of the polyhedron.

Assume all other non basic variables stay at 0 level:
$x_B=B^{-1}b-B^{-1}A_h x_h$
we call $\bar b \triangleq B^{-1}b$  and  $\bar A_h \triangleq B^{-1}A_h$ for simplicity of notation.
$x_B=\bar b-\bar A_h x_h$
$x_{\beta[i]}=\bar b_i-\bar a_ih x_h$ for $i=1,\dots,n$
also we need that $x_\beta[i]\ge0$
we can rewrite this last inequality as:
$\bar a_ih x_h\le b_i(\ge 0)$
Now we have two cases:
1. $\bar a_{ih} \le 0 \to x_h$ can increase forever
2.  $\bar a_{ih} \ge 0 \to x_h\le \frac{\bar b_i}{\bar a_{ih}}$ otherwise we are surpassing the hyperplane
$\theta=\min\{  \frac{\bar b_i}{\bar a_{ih}} : \bar a_{ih}>0\}$
we have $x_h:0\to \theta$,$x_{\beta[t]}:\bar b_t\to 0$ 
where $t=argmin\{ \frac{\bar b_i}{\bar a_{ih}} : \bar a_{ih}>0\}$
$A_h$ "enters the basis" and $A_{\beta[t]}$ "leaves the basis".

---

1. Initialization:
Find a starting 
basis $B=[A_{\beta[1]}|\dotsi|A_{\beta[m]}]$
2. Optimality test:
$u_t \triangleq c_B^T B^{-1}$
if $\bar c^T = c^T - u^TA \ge 0$ then "STOP 
$x=\begin{bmatrix}B^{-1}b\\ \hline 0\end{bmatrix}$
3. change of basis 
let $\bar c_h = c_h -u^T A_h <0$
"$x_h$ wants to enter the basis"
$\bar b \triangleq B^{-1}b$  and  $\bar A_h \triangleq B^{-1}A_h$
$t=argmin\{ \frac{\bar b_i}{\bar a_{ih}} : \bar a_{ih}>0\}$
"$x_{\beta[t]}$ must leave the basis"
$\beta[t]\triangleq h$
"CONTINUE" from step 2.

---
Comments on the pseudocode:

Instead of recomputing the inverse everytime we can directly update the inverse (much less expensive).

if the set in which we take the argmin is empty, there is no limit to $\theta \to \infty$ $x_h:0\to\infty$ that means $c^T x:c_0 \to -\infty$, which means that the problem is unbounded.

We will explain in later lessons [[Lesson 7]] the initialization step.

---
# Update of the inverse matrix of the current basis
4.2.3 in the book





