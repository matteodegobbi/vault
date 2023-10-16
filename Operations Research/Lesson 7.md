#opresearch 
16/10/2023
# Tableu format
Original system
$\min c^Tx=z$
$Ax=b$
$x\ge0$



#####ROBA DAL FOGLIO E ESEMPIO DAL LIBRO

---
# Choice of the entering variable $x_h\to\overline{ c_h} <0$ 
(Notation for polyhedra: vertices, edges and facets)
When we choose the $x_h$ we only have local information about the neighboring vertices so we can't have a theorem to find the best edge to move along in order to get to the optimum solution the fastest.
Since we can't have a theorem because we would need global information we develop some rules of thumb:
1. Take the first $\overline{c_h}<0$ when scanning from left to right
2. $|\overline{c_h}|$ is as large as possible (abs because it's a negative reduced cost)
	we have two reasons for this: to avoid numerical problems with reduced costs close to 0, and because the rate of change is $|\Delta z|=|\overline{c_h}|x_h$, so we are going along the steepest edge (the best rate of change locally), in this case we are ignoring how much $x_h$ can increase so $\theta_h$ we only consider the rate of change.
3. If we also consider $\theta_h$ we can consider $\max|\overline{c_h} \theta_h|$  (this is the best edge locally, considering both the rate and the $\theta_h$)
Method 3 is slower to execute because we need to compute all the values but it guarantees the best local choice.
(In practice a mix of 2 and 3 is used)
4. Random choice is also an option (keeping in mind that the reduced cost should be positive)

---
# Initialization of the tableu
We choose $m$ columns that are linearly independent to find a basis.
Then we compute $\bar b=B^{-1} b$ if it is that $\ge 0$ then it's feasible and we can start.
If it's not we need to try again to find a different basis which is feasible.

In the next lesson we will find a better way to initialize the tableau.

---