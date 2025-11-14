#rl 
#todo 

Up to now we have always represented the Q and V values in a table, but for high cardinalities of the state set S and the action set A, this is not feasible, e.g. Go has $10^{170}$ states so we don't have enough memory to store this table.

The approaches seen up to now are therefore called tabular RL.

The idea of Value Function Approximation is to estimate an approximation based on some descriptor features of the state,action pair.
$\hat v(s,\vec w)\approx v_\pi(s)$ 
$\hat q(s,a,\vec w)\approx q_\pi(s,a)$ 
![[Pasted image 20251113092608.png]]

An additional advantage of VFA other than the memory saving is that if the approximation is good we may generalize the value function to unseen states.

---

We can look at an example using a grid world:
![[Pasted image 20251113092921.png]]


In this case we used a linear approximation but in principle we can use any available supervised learning method.
Still differentiable approaches (linear regression, neural nets) are preferred because SGD can be applied. 

SGD is a method to find a local minimum of a function that works as follows:
![[Pasted image 20251113130902.png]]

To apply this to reinforcement learning we can use SGD to find the value of the parameter vector $w$ that minimizes the mean squared error between the approximation $\hat v$ and the real $v_\pi$:
![[Pasted image 20251113132059.png]]

![[Pasted image 20251113132131.png]]
In expectation SGD is equal to full GD.

In the full RL problem we cannot apply this formulation directly since we don't have access to the true value function, $v_\pi$.  
Instead we can use as targets the sample return as in MC, the TD target as in TD(0) or the $\lambda$-return as in $\text{TD}(\lambda)$.

An important difference with the tabular case is that we cannot aim to match the exact value function as this might not be reachable with the hypothesis class we chose to use to approximate the value function.

Theoretically we need to define a state distribution $\mu(s)\ge 0$, $\sum\limits_{s\in\cal S}{\mu(s)}=1$ to capture how much we care about each state.

Then we can define the objective function called the Mean-Squared Value Error (VE):
![[Pasted image 20251113140336.png]]






