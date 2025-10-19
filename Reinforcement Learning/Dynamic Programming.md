#rl #todo 
The goals of dynamic programming are the following:
1. Policy evaluation (also called prediction): to evaluate how good a policy $\pi$ is. This is done by computing the value functions $v_\pi(s)$ and/or $q_\pi(s,a)$ given as input the [[Markov Decision Processes|MDP]] and the policy $\pi$.
2. Policy improvement (also called control): to improve the current policy to reach optimality. We want to obtain $\pi^*$ (and optionally $v_*(s)$ and/or $q_*(s,a)$) given as input the MDP.
In both cases we assume to have access to the transition and reward probabilities of the MDP, this assumption is not true in practice and later we will relax this when we see actual RL methods.

Theoretically the evaluation/prediction problem can be solved in a closed form by solving a system of linear equations, but for big MRPs this is not feasible in practice so we resort to iterative approaches.
For the improvement/control a closed form solution is not even possible as the equation are non-linear due to the max operation so we always need to resort to iterative approaches.

---
# Policy evaluation 
This algorithm takes care of the prediction part, in which we evaluate how good a given policy is.
Input: MDP, $\pi$
Output: $v_\pi(s)$ and/or $q_\pi(s,a)$

The algorithm is based on Bellman expectation equation which is reworked to be formulated as an update rule:
![[Pasted image 20251019001912.png]]
we start with initial guesses of $v$ that then we improve iteratively using the set of linear equations until it converges (it converges because $v_\pi$ is a fixed point). 

![[Pasted image 20251019002136.png]]

Policy evaluation repeatedly updates the value function for all states according to the update rule, until the max change in evaluation of all states is below a threshold $\theta$.

# Policy iteration
This algorithms takes care of the control part, where we improve the policy in order to make it closer to the optimal policy.
Input: MDP
Output: $\pi^*$, possibly also $v_*(s)$ and/or $q_*(s,a)$

