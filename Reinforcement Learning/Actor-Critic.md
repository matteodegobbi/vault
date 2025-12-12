#rl 
#todo 
# What is Actor-Critic and differences with REINFORCE with baseline
A set of approaches that apply value-based and policy-based RL at the same time. In actor-critic we have two components:
1. Actor: improves the directly parametrized policy, taking care of the control task
2. Critic: evaluate how good the policy is, taking care of the prediction task
This set of approaches differs from the purely policy-based ones like [[Policy gradient#Reinforce|REINFORCE]] which are not considered actor-critic because even though they can use a learned state value function as a baseline, the error estimate is obtained at the end of the episode by computing $\delta\leftarrow G-\hat v(s,w)$ so no bootstrapping happens in the "actor". Instead in Advantage Actor-Critic $\delta\leftarrow R+ \gamma\hat v(s',w)-\hat v(s,w)$ this also implies that in Actor-Critic the update has bias (even if MC is used to update $\hat v$ the bias comes from the 'bootstrapping' in the actor update) while `REINFORCE` with baseline is unbiased because it uses MC to update the policy after the end of the episode.
[stackexchange post about this](https://stats.stackexchange.com/questions/340987/how-can-i-understand-reinforce-with-baseline-is-not-a-actor-critic-algorithm)

Also like seen before for other algorithms MC has higher variance than bootstrapping approaches, this also applies here.

# QAC
The first actor-critic method we derive uses an expression for the gradient derived from one of the intermediate steps we used in [[Policy gradient]] to derive the Monte Carlo `REINFORCE` algorithm:
![[Pasted image 20251206151958.png]]
And if we directly use our value function approximation estimate of the action value function $\hat q_\pi(s,a,w)$ then the quantity $\nabla \ln\pi(a|s,\theta)\hat q_\pi(s,a,w)$ is on expectation proportional to the gradient $\nabla J(\theta)$ and we can use it in our update rule to update the parametrized policy $\pi_\theta$.
The $\hat q_\pi(s,a,w)$ can be learned with any of the methods we already saw in value-based RL, e.g. TD(0), $\text{TD}(\lambda)$, MC.

The pseudocode for a possible version of QAC with linear function approximation for the critic $\hat q$ that is learned with TD(0) is presented below:
![[Pasted image 20251206152726.png]]
This algorithm can be seen as a sort of value iteration, the policy (the actor) is changed at each step immediately after improving the estimate of the value function (the critic).

# Advantage function
As we already saw with [[Policy gradient#Reinforce|REINFORCE]] introducing a baseline can improve the convergence properties of the algorithm and is very useful in practice
This concept of baseline is included in Advantage Actor-Critic approaches which approximate directly or indirectly the advantage function $A(s,a)$:
$$A_{\pi_\theta}(s,a)\triangleq q_{\pi_\theta}(s,a)-v_{\pi_\theta}(s)  $$where $v$ serves the purpose of the baseline. 
The advantage quantifies how much better an action taken in a specific state is compared to the value of the state itself $v(s)$ (which averages over all possible actions weighting them by the probability assigned to them by the policy $\pi_\theta$, this is by definition of state and action value functions)

If the policy is already optimal the advantage function will be <0 for all actions except for the optimal action for which $A_{\pi^*}(s,a^*)=0$: since the policy is optimal for any state the best value action will be taken (then Bellman optimality equation holds).

We can rewrite the expression proportional to the gradient by considering the advantage function instead of just $q$:
![[Pasted image 20251206161906.png]]

To apply this in practice we have multiple options:
One would consist in estimating both an approximation action value function $\hat q$ and a state value function $\hat v$ obtaining:
![[Pasted image 20251206162048.png]]

This works but it requires two set of parameters $v,w$ for the critic and the usual $\theta$ for the actor.

We can simplify the algorithm by noticing how the TD-Error is actually an unbiased estimate of the advantage function:
![[Pasted image 20251206162225.png]]
So in the update rule we can now use the TD-Error instead of the difference of q and v.

![[Pasted image 20251212160402.png]]
![[Pasted image 20251212160536.png]]

---
# Different time-scales
For both the actor and the critic we can consider different approaches using the different targets we already developed in value-based methods.
## For the critic
![[Pasted image 20251206162751.png]]
Examples of the update $\Delta v$ are in the linear case but the expression generalize by using the gradient of v instead of x.

## For the actor
![[Pasted image 20251206163002.png]]
Where MC policy gradient is the same as REINFORCE.

![[Pasted image 20251206163045.png]]

We can mix actors and critics that work at different time-scales but it doesn't make sense to use critics that are 'slower' than actors, since the change in policy of the actor depends on having improved prediction by the critic.
For this reason it makes little sense to use a TD(0) actor with a MC critic as many update steps of the actor are using old estimates since the MC critic will only be updated when the episode ends.

---

Extension to continuing tasks and continuous action spaces in the lecture's pdf.

---




