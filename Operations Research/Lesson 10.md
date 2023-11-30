#opresearch 
# Bland's rule 
(pag 51)
Scan the reduced costs and the first negative element you find will be the column of the pivot (selection of entering variable)
.....
and select the row with the minimum ratio, if there are multiple elements with the same ratio (like in the book) we select the row according to the basic variable with the smallest index.
(in the book example on row 2)

Theorem: if you use Bland's rule $\to$ no loop
Proof: By contradiction, we assume we have a counterexample (so a tableau that when we use Bland's rule loops) we concentrate on counterexamples with min number of rows and columns
Note: I make a pivot on every row and on every column (if i didn't i could drop the column or the rpw and have a smaller counterexample, it's impossible because we chose to have the smallest counterexample) this implies we have all zeroes on the RHS (perchee????)
we also know the objective function stays constant (otherwise we would not be looping)
			   we consider the worst possible iteration for Bland's $x_n$ is leaving the basis
We have this tableau $\mathcal T$  

| = |0 $x_{\beta[1]}$  | - xh |   | 0 xn|
|---|---|---|---|---|
| 0 | 0 | - |   | 0 |  
| 0 | 1 | - |   | 0 |
| 0 | 0 | - |   | 0 |
| 0 | 0 | + |   | 1 |
| 0 | 0 | - |   | 0 |
second to last row is row t 

Notation $\beta$ refers to tableau T, \bar c as well 
(ste robe seguenti spiegate nel libro)
$\bar c < 0$
$\bar a_{ih} \ge 0 \ \forall i \ne t$ 
$\bar b_i=0\ \  \forall i$
$\bar c_{\beta[i]} =0 \ \ \forall i$

new tableau $\tilde{\mathcal T}$ 
is the tableau at iteration when x_n is reentering the basis
$\tilde c_n <0$
$\tilde c_j \ge 0 \ \ \forall j\ne n$
in this iteration beta is referring to the previous tableau
     ...xbeta[i]... x_h.... x_n
| = | +  | + |  + | - |
|---|---|---|---|---|
| ~ | ~ | ~ |  ~ |  ~ |  
only interested in the top of the tableau
We will know find that this pattern of signs in T tildecannot come from T

\[row 0 of $\tilde{\mathcal T}$\]=\[row 0 of ${\mathcal T}$\]+$\sum_{i=1}^m{\mu_i [\text{row }i\text{ of }\mathcal T]}$ (linear comb with coefficient $\mu_i$)
*  $\tilde{c}_{\beta[i]}=\underbrace{\overline{c}_{\beta[i]}}_{=0}+\mu_i\ge0\ \ \to \mu_i\ge0 \ \ \forall i \ne t$
*  $\tilde{c}_{\beta[t]}=\tilde{c}_n=\underbrace{\overline{c}_{\beta[t]}}_{=0}+\mu_i<0\ \ \to \mu_i<0$

$\tilde{c}_h=\overline{c}_h+\sum_{i=1}^m{\mu_i \overline{a_{ih}}}$ (linear comb with coefficient $\mu_i$)
now i split the sum
$\underbrace{\overline{c}_h}_{<0}+\sum_{i:i\ne t}^m{\underbrace{\mu_i}_{\ge0} \underbrace{\overline{a}_{ih}}}_{\le 0}+ \underbrace{\mu_t}_{<0} \underbrace{\overline a_{th}}_{>0} < 0$ 

contradiction

---

# Dealing with bounded variables

$(\triangle) \ \ 0 \le x_j \le q_j \ \  \forall j$

We have a lower bound and an upper bound 
(in general we could have a lower bound bigger than 0 but we can always shift both the variable and the upper bound by the lower bound and go back to $(\triangle)$)

This in principle is not a problem because we can just use $x_i \le q_j$ as a constraint of the problem (adding a slack variable) but this adds a lot of elements to the tableau (because we have wide and short tableaus usually)

We can then consider a better way to solve this common problem, one idea is complementing the variable and having a normal non negativity constraint, this is not done in practice.

In practice we have $\begin{bmatrix}x_{B}\hbar \\ x_{L} \\ x_{U}\end{bmatrix}$
$Ax=b=\begin{pmatrix}B | L | U\end{pmatrix}\begin{pmatrix}x_{B} \\ x_{L} \\ x_{U}\end{pmatrix}=B^{-1}* (B x_{B}+ L x_{L}+ U x_{U}=b)$
$x_B=B^{-1}* (b - L x_{L}- U x_{U})$
Basic solution associated (B,L,U)

$x_L=0$
$x_U=q_U$
$x_{B}= B^{-1}(b - U q_U)$
and we define a new way to do the optimality test:
reduced cost vector
$\bar c^{T}=c^{T}-c_{B}^{T}B^{-1}A$
* $\bar c_{h}\ge 0\  \forall x_h$ non basic at the LB
* $\bar c_{h}\le 0\  \forall x_h$ non basic at the UB
* $\bar c_{h}=0\  \forall$basic variables
2 cases 
1. $\bar c_{h}<0$ and $x_h$ is non basic at its lower bound(=0)
2. $\bar c_{h}>0$ and $x_h$ is non basic at its upper bound(=$q_h$)

case 1.
$x_{h}:0\to\theta_{h}' =\min\{\frac{\bar b_{i}}{\bar a_{ih}}:\bar a_{ih}>0\}$
$\theta_{}' = \dots$
$min\{ \theta_{h',}\theta_{h}'' \}\to$ real threshold
case 2. 
$x_{h}:q_h\to\omega_{h}' =\}$

prendo il min tra omega' e omega''