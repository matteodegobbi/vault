#opresearch 
18/10/2023

# Convergence of simplex method
If the objective function decreases always by $\Delta z_k\ne0$ we will always have a different basis and we can at most have $n \choose m$ iteration

else if for some$k, \ \Delta z_k$ we could have a base that repeats, if this happens we will get stuck in a loop.

if we are in a iteration where this happens since $|\Delta z|=\underbracket{|\bar c_h|}_{\ne0} \theta$ so it must be $\theta=0$ 
$\theta=\min\{  \frac{\bar b_i}{\bar a_{ih}} : \bar a_{ih}>0\}=0\to \exists i:\bar b_i=0$ which means that there are degeneracies

So if there are no degeneracies simplex method converges in a finite amount of iterations
if there are degeneracies it could either converge or go on in an infinite loop.
We need to solve this infinite loop problem.
# How to deal with degeneracy?
1. pivot element $\to$ random way if we have a non deterministic choice we don't always make the same choice so it's very likely to break out of the loop (but not a mathematical guarantee) also if you use this way you cannot choose the maximum how we said in [[Lesson 7#Choice of the entering variable $x_h to overline{ c_h} <0$|Choice of the entering variable]] (also the numerical errors because of `float` in computers introduce some randomness)
2. Move randomly the constraints by some $\epsilon$, we now have $Ax=b+\delta$ (delta is a vector of epsilons one for each component) (how we see in the drawing ###FIGURA DI ONENOTE CON RETTE SPOSTATE DI EPSILON) in a later iteration we have to remove this perturbation otherwise we wont go to a correct solution (in commercial software we do a perturbation after some number of iteration where the obj function stays the same)
3. Bland's rule (simple way to guarantee no loops) (we will enunciate and prove this in [[Lesson 10]])

# Revised simplex method
A different version that uses less memory.
It's common to have more columns than rows in the tableau (e.g. 1000 rows and 100000 columns)
a lot of times the constraints only involve a few of the variables (sparse format)
####disegno

after a lot of iterations we lose sparsity so it's more difficult to store the tableau

so we develop a revised method where we only update the core part of the tableau

we cut the tableau at $(\triangle)$ and insert an identity matrix ###ONENOTE E PDF , VIDEO
#####
(the statistics say with this method \#(pivot operations) is usually $\approx3m$ )

---

