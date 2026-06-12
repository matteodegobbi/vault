#rl 
#todo 
# What is Actor-Critic and differences with REINFORCE with baseline
A set of approaches that apply value-based and policy-based RL at the same time. In actor-critic we have two components:
1. Actor: improves directly the parametrized policy, taking care of the control task
2. Critic: evaluates how good the policy is, taking care of the prediction task
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

# PPO (Proximal Policy Optimization)

PPO is a policy gradient method that tries to solve the problem of instability in PG methods. Once a bad gradient step collapses the policy, PG methods can be unrecoverable, the idea of PPO is based on TRPO, constraining how much the policy can change (TRPO uses constrained optimization with constraints on KL divergence between old and new policy).

PPO tries to obtain the same result as TRPO by using a clipped surrogate objective that is much simpler to optimize than TRPO's.

The reason why regular PG method are unstable is that the PG theorem is derived under the assumption that the step size is small enough which can be false in practice.
## Importance Sampling and the Surrogate Objective

PPO reuses data collected under an **old policy** $\pi_{\theta_\text{old}}$ to perform multiple gradient updates. To correct for the distributional mismatch this introduces, importance sampling is applied.

Define the probability ratio: $$r_t(\theta) = \frac{\pi_\theta(a_t|s_t)}{\pi_{\theta_\text{old}}(a_t|s_t)}$$

The unclipped surrogate objective becomes: $$L^{\text{CPI}}(\theta) = \mathbb{E}_t\left[r_t(\theta) \hat A_t\right]$$

This is called the Conservative Policy Iteration objective.
Maximizing it without constraints would recover standard policy gradient on the old data, but $r_t(\theta)$ can become arbitrarily large if the new policy diverges from the old one, making the estimate unreliable and high variance (like with off-policy MC using importance sampling).

The **clipped surrogate objective** is used to limit this divergence from the old policy: $$L^{\text{CLIP}}(\theta) = \mathbb{E}_t\left[\min\left(r_t(\theta),\hat A_t,; \text{clip}(r_t(\theta),, 1-\varepsilon,, 1+\varepsilon),\hat A_t\right)\right]$$

The clip removes the incentive to move $r_t(\theta)$ outside $[1-\varepsilon,, 1+\varepsilon]$ (typically $\varepsilon = 0.1$ or $0.2$). 
Taking the $\min$ of the clipped and unclipped versions ensures the objective is a **lower bound** (pessimistic estimate) of the true objective, the policy is only updated when doing so is safe.

Intuitively:
- If $\hat A_t > 0$ (the action was better than expected): we want to increase $\pi_\theta(a_t|s_t)$, but only up to $(1+\varepsilon)\pi_{\theta_\text{old}}$
- If $\hat A_t < 0$ (the action was worse than expected): we want to decrease $\pi_\theta(a_t|s_t)$, but only down to $(1-\varepsilon)\pi_{\theta_\text{old}}$

This is asymmetric in the right direction: the clipping is only active when ignoring it would lead to a large policy change, this is because when $\hat A>0$ $\pi_\theta$ wouldn't get decreased so the lower clip $1-\varepsilon$ is not active (vice-versa for $\hat A<0$).
## Full PPO Objective

This formula is slightly different if actor and critic are two heads of the same backbone network or they are entirely separate nets.
In the more common case they share a backbone and the loss can be combined in a single one, the update signal will be correctly routed by backprop.
$$L^{\text{PPO}}(\theta) = \mathbb{E}_t\left[L^{\text{CLIP}}(\theta) - c_1 L^{\text{VF}}(\theta) + c_2 S\pi_\theta\right]$$

where:

* $L^{\text{CLIP}}$ is the actor (policy net) objective
- $L^{\text{VF}}(\theta) = \left(\hat V_\theta(s_t) - V_t^{\text{target}}\right)^2$ is the critic (value function) loss
- $S\pi_\theta = -\sum_a \pi_\theta(a|s_t)\log\pi_\theta(a|s_t)$ is the entropy bonus, which encourages exploration and prevents premature convergence to a deterministic policy
- $c_1, c_2$ are coefficients (typically $c_1 \approx 0.5$, $c_2 \approx 0.01$)

The way I wrote $L^\text{PPO}$ is a maximization objective, when using torch just change the sign and perform gradient descent.

# Advantage Estimation: GAE

PPO is typically used together with **Generalized Advantage Estimation (GAE)** to compute $\hat A_t$. GAE interpolates between TD(0) and Monte Carlo returns via an exponential decay parameter $\lambda$, this is basically the policy gradient version of [[n-step bootstrapping and TD lambda|TD lambda]]:

$$\hat A_t^{\text{GAE}(\gamma,\lambda)} = \sum_{l=0}^{\infty} (\gamma\lambda)^l \delta_{t+l}$$

where $\delta_t = r_t + \gamma \hat V(s_{t+1}) - \hat V(s_t)$ is the TD error. 

As in TD lambda:
- $\lambda = 0$: pure TD(0), low variance, high bias
- $\lambda = 1$: Monte Carlo, high variance, low bias
* $\gamma\lambda$ product controls the effective horizon: small values favor short-horizon, low-variance estimates.

## PPO Algorithm pseudocode

```
Initialize policy parameters θ, value parameters w
for each iteration:
    Collect trajectories {s_t, a_t, r_t} using π_{θ_old}
    Compute advantages Â_t using GAE(γ, λ) with V̂_w
    Compute value targets V_t^target = Â_t + V̂_w(s_t)
    
    for K epochs:
        for each minibatch:
            Compute r_t(θ) = π_θ(a_t|s_t) / π_{θ_old}(a_t|s_t)
            Compute L^CLIP, L^VF, entropy bonus S
            Update θ by ascending ∇_θ L^PPO
    
    θ_old ← θ
```


Data is collected on-policy using fresh rollouts each iteration, discarding trajectories gathered with previous policies, but used for more than one epoch of gradient ascent. This is done as a controlled form of off-policy reuse to increase sample efficiency.

The only changes inside the K epochs will be 
* The ratio $r_t$ as the numerator changes since we are updating the network's weights
* The new policy, and therefore the three components of the objective function

Typically whitening is applied to advantages before updates.

---

