#rl #todo
Monte Carlo methods are model-free full RL solutions, meaning we don't require knowledge of $P,R$, unlike [[Dynamic Programming|dynamic programming]].

Monte Carlo is used for both prediction and control. These methods work with data gathered by the agent interacting with the environment. In Monte Carlo we require we are in the episodic case as we will use the complete returns which are available only in the case where the episode terminates in a finite amount of time-steps.

MC methods estimate expectations by averaging over a large number of random samples.

Since in RL we want to estimate $q_\pi(s,a)=\mathbb E[G_t|S_t=s,A_t=a]$ and $v_\pi(s)=\mathbb E[G_t|S_t=s]$ we can take the sample averages of returns to estimates the action and state value functions.
We estimate the value functions instead of transition and reward probabilities because it's more efficient in terms of the amount of data and computing time.

We already saw this idea in [[Multi Armed Bandits|bandits]] but in that case we only needed to estimate the sample reward, not the return as there's no state.

---

# Prediction
For Monte Carlo prediction we can follow policy $\pi$ to generate the full data of an episode (a full trajectory of the MDP: $S_0,A_0,R_1,\dots,S_{T-1},A_{T-1},R_T$)
Then we can compute the total discounted return of the episode, we can compute this backwards starting from $G_T=0$ in the terminal state, this is because we can compute it steps by step instead of doing the full forward sum.
At the end of the episode we can have two options to update the value function:
1. First visit MC prediction: for state $S_t$ the return is used to update $V(s)$ only for first time that state is encountered in that trajectory. So for example at time-step $t=2$ we encounter state $S_6$ and then we encounter it again at $t=18$, meaning $S_6=S_{18}$ we will only update $V(S_6)$ at time-step $t=6$ and not anymore at time $t=18$, this can lead to slower convergence but less variance in the estimates.
2. Every visit MC prediction: Instead of updating a state value function estimate at most once per episode we update it every time the state is encountered, this can lead to faster convergence at the expense of a larger variance in the estimates.

Pseudocode for First-Visit MC prediction:
![[Pasted image 20251021145609.png]]

Pseudocode for Every-Visit MC prediction:
![[Pasted image 20251021145745.png]]

In both cases we can use incremental updates of $V(s)$ instead of recomputing the full average every time. This is the same idea we used in [[Multi Armed Bandits|bandits]]:
![[Pasted image 20251021145851.png]]

---
