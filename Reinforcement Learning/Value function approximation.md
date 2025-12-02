#rl 
#todo 

# Introduction
Up to now we have always represented the Q and V values in a table, but for high cardinalities of the state set S and the action set A, this is not feasible, e.g. Go has $10^{170}$ states so we don't have enough memory to store this table.

The approaches seen up to now are therefore called tabular RL.

The idea of Value Function Approximation is to estimate an approximation based on some descriptor features of the state,action pair.
$\hat v(s,\vec w)\approx v_\pi(s)$ 
$\hat q(s,a,\vec w)\approx q_\pi(s,a)$ 
![[Pasted image 20251113092608.png]]

An additional advantage of VFA other than the memory saving is that if the approximation is good we may generalize the value function to unseen states, making the RL algorithms better for partially observable problems.

---

We can look at an example using a grid world:
![[Pasted image 20251113092921.png]]


In this case we used a linear approximation but in principle we can use any available supervised learning method.
In any case, differentiable approaches (linear regression, neural nets) are preferred because SGD can be applied. 

SGD is a method to find a local minimum of a function that works as follows:
![[Pasted image 20251113130902.png]]

To apply this to reinforcement learning we can use SGD to find the value of the parameter vector $w$ that minimizes the mean squared error between the approximation $\hat v$ and the real $v_\pi$:
![[Pasted image 20251113132059.png]]

![[Pasted image 20251113132131.png]]
In expectation SGD is equal to full GD.


# Prediction 
In the full RL problem we cannot apply the formulation we developed in the introduction directly since we don't have access to the true value function $v_\pi$ (we're not in a supervised learning setting).  
Instead later we will use as targets the sample return as in MC, the TD target as in TD(0) or the $\lambda$-return as in $\text{TD}(\lambda)$. For now let's stick to the true $v_\pi$ as the target for this initial analysis.

An important difference with the tabular case is that we cannot aim to match the exact value function as this might not be reachable with the hypothesis class we chose to use to approximate the value function (like when in ML we relaxed the realizability assumption). So we need to define a way to quantify how important the correctness of the approximation is for each state, e.g. it will be more important to have a good estimate for a frequent state than for a rare state.

To obtain this information we need to define a state distribution $\mu(s)\ge 0$, $\sum\limits_{s\in\cal S}{\mu(s)}=1$ to capture how much we care about each state based on the probability that the agent will be in that state: errors in more common states will be weighted more than in rare states.

Then we can define the objective function called the Mean-Squared Value Error (VE):
![[Pasted image 20251113140336.png]]

To simplify the analysis from now on we will refer only to the on-policy approach with continuing tasks, with these assumptions the state distribution is the stationary distribution under policy $\pi$, (basically if we fix $\pi$ we are just considering a Markov Chain with stationary distribution of states, this is implied by ergodicity assumption).

N.B. We consider the continuing case because in the episodic case we would also need to consider the distribution over the starting state and the average number of time-steps spent in a state per episode. This complicates the notation, so the analysis in the episodic case is not carried out here and can be found in the book.

So with these two assumptions (on-policy, continuing case) we can rewrite VE as the following loss:
![[Pasted image 20251115174815.png]]


Also in the following we will only show the formulas for value function approximation that is linear wrt the features, but in the algorithms' pseudocode we don't assume linear approximation, instead we write the generic version using $\nabla\hat v(S,\textbf{w})$ (or $\nabla\hat q(S,A,\textbf{w})$ in the case of control algorithms).

![[Pasted image 20251115215821.png]]
(Tabular RL can be seen as a special case of linear approximation where the feature vector is a 1-hot vector with all the states, with this representation only the value of the state will be updated, making it equivalent to tabular RL)

## Algorithms using value function approximation
![[Pasted image 20251115220839.png]]

### Monte Carlo
![[Pasted image 20251115234148.png]]
In the linear case MC it converges to a global optimum, in non linear case to a local optimum. These convergence properties are due to the unbiasedness of the MC target. The delta in the update rule for the linear case is the following.
![[Pasted image 20251115234258.png]]

### TD(0)
![[Pasted image 20251115234419.png]]
It's a semi-gradient method and not gradient because the target itself is changed by the update rule so we are not computing the actual gradient, we are only considering the change on the estimate but ignoring the effect on the target.

![[Pasted image 20251115234616.png]]

In the linear case semi-gradient TD(0) the delta has the following equation ($\delta$ is the TD error):
![[Pasted image 20251115234659.png]]

Linear TD(0) converges "close" to the global optimum (it converges to a fixed point of the projected bellman equation, which in practice yields a numerically close result to the global optimum).

### n-step and $\text{TD}(\lambda)$
![[Pasted image 20251115235714.png]]
we can also implement TD lambda:
![[Pasted image 20251116003049.png]]

### Convergence properties summary
![[Pasted image 20251116004630.png]]

---
# How to build features
In the PDF lecture 14 from slide 31
Generalization vs Discrimination
State aggregation
Coarse coding
Tile coding

---
# Control
Similarly to what we saw in TD and MC when dealing with the tabular case for control we need to use $q$ to have a model free approach:

![[Pasted image 20251116005017.png]]

Again we don't have access to the real $q_\pi(s,a)$ so depending on the method we will use a sample quantity ($G_t$ for MC etc...)
We will represent state,action pairs with feature vectors:
![[Pasted image 20251116005058.png]]
again like in prediction we show only examples for the linear approximation but they can be generalized by employing the gradient of the approximation function.

All the targets are the same as in prediction but with q instead of v.

Semi-gradient SARSA:
![[Pasted image 20251116005255.png]]

We can also have optimistic value initialization strategies to foster exploration at the early stages of the episode (???????? episode or training)

TODO aggiungi convergence condtions sum alfa^2\<infinito
