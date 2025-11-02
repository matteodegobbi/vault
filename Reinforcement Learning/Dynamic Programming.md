	#rl
The goals of dynamic programming are the following:
1. Policy evaluation (also called prediction): to evaluate how good a policy $\pi$ is. This is done by computing the value functions $v_\pi(s)$ and/or $q_\pi(s,a)$ given as input the [[Markov Decision Processes|MDP]] and the policy $\pi$.
2. Policy improvement (also called control): to improve the current policy to reach optimality. We want to obtain $\pi^*$ (and optionally $v_*(s)$ and/or $q_*(s,a)$) given as input the MDP.
In both cases we assume to have access to the transition and reward probabilities of the MDP, this assumption is not true in practice and later we will relax this when we see actual RL methods.

Theoretically the evaluation/prediction problem can be solved in a closed form by solving a system of linear equations, but for big MRPs this is not feasible in practice so we resort to iterative approaches.
For the improvement/control a closed form solution is not even possible as the equation are non-linear due to the max operation, meaning we always need to resort to iterative approaches.

---
# Policy evaluation 
This algorithm takes care of the prediction part, in which we evaluate how good a given policy is.
Input: MDP, $\pi$
Output: $v_\pi(s)$ and/or $q_\pi(s,a)$

The algorithm is based on Bellman expectation equation which is reworked to be formulated as an update rule:
![[Pasted image 20251019001912.png]]
we start with initial guesses of $v_0$ that then we improve iteratively using the set of linear equations until convergence (it converges because $v_\pi$ is a fixed point). 

![[Pasted image 20251019002136.png]]

Policy evaluation repeatedly updates the value function for all states according to the update rule, until the max change in evaluation of all states is below a threshold $\theta$.

### Note on synchronous vs in-place policy evaluation
Theoretically while we are iterating over all the states to update their value function in the sum we should use the value function corresponding to the previous iteration of the policy evaluation.
Meaning that the order in which we update the states doesn't affect the update.
This implementation of policy evaluation is called synchronous as we update all the state evaluations together.
We can contrast this  with the implementation shown in the pseudocode above in which we store only one copy of $V(s)$ and update it in-place, this allows us to save memory and avoid having to copy the whole $V(s)$ at the end of the iteration.
Also since we use already updated values of states that have already been iterated over this makes the convergence faster so in practice we'll always use the in-place version.
![[Pasted image 20251030101339.png]]

# Policy iteration
This algorithm takes care of the control part, where we improve the policy in order to make it closer to the optimal policy.
Input: MDP
Output: $\pi^*$, possibly also $v_*(s)$ and/or $q_*(s,a)$
Policy iteration consists in repeated evaluation of the policy followed by using the greedy choice (based on the last evaluation) to improve the current policy by bringing it closer to the optimal policy $\pi^*(a|s)$
![[Pasted image 20251019143441.png]]

The algorithm will converge to the optimal policy, this can be proven by the Policy improvement theorem.

### Policy Improvement theorem:
We define the greedy policy $\pi'(s)=\arg\max\limits_{a\in \cal A}{q_\pi(s,a)}$, which tells us the action with highest action-value.
Since we take the maximum, the evaluation of $\pi'(s)$ will be $\ge$ than the value function when following the policy $\pi$.
Then we can repeat the same argument iteratively to show how $v_\pi(s)\ge v_{\pi'}(s)$
This is shown here:
![[Pasted image 20251019145335.png]]

The main idea is "if instead of following policy $\pi$ we choose the greedy action for the next action and still follow $\pi$ afterwards we will improve the value function", this argument can be repeated also for the following action and so on, yielding that the value function will always improve if for any of the following action instead of following $\pi$ we follow the greedy policy.

This just shows how by following the greedy policy we can never do worse but we still haven't shown if it leads to the optimal policy:

![[Pasted image 20251019150144.png]]
This means that if the improvement stops we have reached the optimal policy since the policy satisfies Bellman optimality equation, this is just the case where after an iteration the inequality in the previous slide are just equalities.

Pseudocode for policy iteration (the first part is the same as the previous with different notation):
![[Pasted image 20251019150259.png]]

---

# Value iteration

## Generalized policy iteration
Policy iteration can be slow due the fact that we need to wait for the convergence of the policy evaluation step. This means that we need to loop over all the states multiple times until they have all converged to the true value of $v_\pi$.
A possibility to improve the efficiency of the process is to truncate the policy evaluation before convergence, mixing some steps of policy evaluation followed by some steps of policy improvement, this approach still leads to convergence and is called **Generalized Policy Iteration**.

## Value iteration
If we only do one step of evaluation at a time followed by policy improvement through greedy policy we obtain an algorithm called value iteration.
Value iteration consist of just updating the value function for all states once, followed by one sweep of policy improvement through greedy policy, the process is repeated until convergence.

Actually we can rewrite the formulation of value iteration differently:

![[Pasted image 20251019173506.png]]
In this formulation both the prediction and improvement over a state are combined into a single step.

From this formulation we can notice how the update rule coincides with Bellman optimality equation, while the policy iteration updated rule coincided with the Bellman expectation equation:
![[Pasted image 20251019173922.png]]

The only difference between the two is that in policy iteration we average over all possible actions while in value iteration we only consider the best one (instead of first computing the average over the actions and taking the max in the improvement step we directly take the max).

![[Pasted image 20251019174152.png]]

Comparison of policy and value iteration:
![[Pasted image 20251019174231.png]]

# Summary and notes on efficiency

![[Pasted image 20251019174309.png]]

This high complexity can make the algorithms slow so we can use asynchronous DP approaches to make them faster.

We call synchronous approaches the one that repeat $\forall s\in\cal S$, asynchronous approaches are a kind of in-place set of approaches that don't do a whole sweep of the state set per iteration.

We can for example: 
1. Asynchronous DP approaches update the values of states in any order whatsoever, using whatever values of other states happen to be available.
2. ﻿﻿﻿We can select the states to which we apply updates to improve the algorithm's rate of progress in a particular state.
3. ﻿﻿﻿Or we might even try to skip updating some states entirely if they are not relevant to optimal behavior.
4. ﻿We may collect trajectories and see the states that are used by a policy and just update those.
5. ﻿﻿﻿Prioritized Sweeping - Chapter 8: we can try to order the updates to let value information propagate from state to state in an efficient way: some states may not need their values updated as often as others.

﻿﻿Asynchronous DP methods still converge if all states continue to be selected

---
