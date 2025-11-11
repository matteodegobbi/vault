#rl 
[[On-Policy vs Off-Policy and importance sampling]]

Monte Carlo methods are model-free full RL solutions, meaning we don't require knowledge of $P,R$ or any model unlike [[Dynamic Programming|dynamic programming]] which requires both a model and knowledge of $P,R$.

Monte Carlo is used for both prediction and control. These methods work with data gathered by the agent interacting with the environment. In Monte Carlo we require that we are in the episodic case as we will use the complete returns, which are available only in the case where the episode terminates in a finite amount of time-steps.

MC methods estimate expectations by averaging over a large number of random samples.

Since in RL we want to estimate $q_\pi(s,a)=\mathbb E[G_t|S_t=s,A_t=a]$ and $v_\pi(s)=\mathbb E[G_t|S_t=s]$ we can take the sample averages of returns to estimate the action and state value functions.
We estimate the value functions instead of transition and reward probabilities because it's more efficient in terms of the amount of data and computing time.

We already saw this idea in [[Multi Armed Bandits|bandits]] but in that case we only needed to estimate the sample reward, not the return as there's no state (also in bandits only $q(a)$ is defined as there's no state).

---

# Prediction
For Monte Carlo prediction we can first follow policy $\pi$ to generate the full data of an episode (a full trajectory of the MDP: $S_0,A_0,R_1,\dots,S_{T-1},A_{T-1},R_T$)
Then we can compute the total discounted return of the episode efficiently: we can compute it backwards starting from $G_T=0$ in the terminal state, this allows us to compute it step by step instead of doing the full forward sum.
At the end of the episode we can have two options to update the value function:
1. First visit MC prediction: for state $S_t$ the return is used to update $V(s)$ only for first time that state is encountered in that trajectory. So for example at time-step $t=2$ we encounter state $S_6$ and then we encounter it again at $t=18$, meaning $S_6=S_{18}$ we will only update $V(S_6)$ at time-step $t=6$ and not anymore at time $t=18$, this can lead to slower convergence but less variance in the estimates.
2. Every visit MC prediction: Instead of updating a state value function estimate at most once per episode we update it every time the state is encountered, this can lead to faster convergence at the expense of a larger variance in the estimates.

Pseudocode for First-Visit MC prediction:
![[Pasted image 20251021145609.png]]

Pseudocode for Every-Visit MC prediction:
![[Pasted image 20251021145745.png]]

In both cases we can use incremental updates of $V(s)$ instead of recomputing the full average every time. This is the same idea we used in [[Multi Armed Bandits|bandits]]:
![[Pasted image 20251021145851.png]]

We can notice how the computational complexity does not depend on the size of the MDP but depends on the size of the episode.

Both the first-visit and every-visit versions can be seen as a model free version of [[Dynamic Programming#Generalized policy iteration |GPI]].

---
# Control
Estimating state value functions is not enough in order to compute a greedy policy, this is because unlike [[Dynamic Programming|DP]] we don't have access to $P,R$ so we cannot use equation:

![[Pasted image 20251024184220.png]]

For this reason we actually need to estimate action value functions $q_\pi(s,a)$ instead of state value functions $v_\pi(s)$

![[Pasted image 20251024184628.png]]

The state-action space is much larger than the state space so this method will need some amount of exploration in order to be able to obtain good estimates of the value function.
(This is also true when considering state value functions but since the search space is bigger with $q$  it's even more important)

If we use a deterministic policy it's not guaranteed we visit all (state,action) pairs so we need to use some stochastic policy.

---
## Monte Carlo ES (Exploring Starts)

With this control method we use exploration in order to obtain more data to be able to estimate the optimal action value function $q_*(s,a)$ in order to obtain the optimal policy $\pi^*$.

In ES the exploration is only limited to the first (state,action) pair of each episode, this is because the first state $S_0$ is chosen randomly, and the first action $A_0$ is chosen randomly out of the set of feasible actions in the state $S_0$, meaning $A_0\in\mathcal{A}(S_0)$.

![[Pasted image 20251026162451.png]]

Where the Policy Evaluation step is the same as MC prediction but with $Q$ instead of $V$, and the Policy Improvement step is done by updating the policy to maximize the current estimate of $Q$.

As in MC prediction instead of the average we could implement it with incremental updates.

The convergence of this method is guaranteed by a policy improvement theorem similar to the one we discussed in [[Dynamic Programming|DP]]:
![[Pasted image 20251026162916.png]]

ES has an important drawback: sometimes is may not be possible to start an episode with all possible (state,action) pairs, for this reason we can look for other methods that guarantee exploration that are not based on ES.

---

## $\varepsilon$-soft policies  
To guarantee exploration without ES we can look at the class of policies called $\varepsilon$-soft: the $\varepsilon$-greedy policy we analyzed in [[Multi Armed Bandits|bandits]] is a specific instance of $\varepsilon$-soft policy ("the greediest of the $\varepsilon$-soft policies").  

A $\varepsilon$-soft policy is a policy for which $\pi(a|s)>0$ $\forall\  a,s$.
In particular we define $\varepsilon$ of the $\varepsilon$-soft  policy as the constant for which $\forall\ a,s\ \pi(a|s)>\frac{\varepsilon}{|A(s)|}$
![[Pasted image 20251026164518.png]]

From this concept of soft policies we can derive an algorithm for MC control to estimate $\pi^*$ without ES:
![[Pasted image 20251026164856.png]]

As we can easily expect even if $\varepsilon$-soft policies allow improvement they are not optimal:
![[Pasted image 20251026165033.png]]

This is the same idea as we saw in bandits how $\varepsilon=0.01$ was initially performing worse than $\varepsilon=0.10$ due to having more exploration in the latter, but then after some amount of time-steps the former was overtaking the latter because it chose the optimal action more often.

---

Both ES and $\varepsilon$-soft MC control are on-policy algorithms, off-policy algorithms are explained in [[Monte Carlo - Off-Policy methods]].
