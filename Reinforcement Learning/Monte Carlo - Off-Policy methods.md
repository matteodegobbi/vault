#rl
# Using importance sampling in MC methods
Difference between on-policy and off-policy and importance sampling: [[On-Policy vs Off-Policy and importance sampling]].

Since we are following policy $b(a|s)$ to generate episodes we have that the value functions of policy $\pi(a|s)$ cannot be estimated as just the sample average of returns, as those returns are obtained with policy $b(a|s)$. For this reason we need to weigh our samples with $\rho(a|s)=\frac{\pi(a|s)}{b(a|s)}$ so we can have the correct estimate of the return when following policy $\pi$ using data gathered from policy $b$. This method is called [[On-Policy vs Off-Policy and importance sampling|importance sampling]].

An important detail from [[On-Policy vs Off-Policy and importance sampling|importance sampling]] is that to obtain good estimates we need to have that the sampling distribution (in the MC RL case the behavior policy) needs to be high in value whenever the quantity we are trying to estimate multiplied by its probability is high (in absolute value), this translates in the context of MC RL to:
- If the behavior policy $b(a|s)$ is small where the target policy times return $\pi(a|s)G_t$ the importance ratio $\rho(a|s)=\frac{\pi(a|s)}{b(a|s)}$ explodes leading to high variance.
- If $b(a|s)$ gives high probability to trajectories that the target policy $\pi$ also favors (especially those leading to high returns), the importance weights stay moderate leading to low variance and good estimates.

---
# Prediction  
Given the current state $S_t$ we can express the probability of the agent following a subsequent (state,action) trajectory as:
![[Pasted image 20251027172230.png]]

To be able to carry out off-policy learning we want to compute the importance ratio between the two policies given a specified trajectory of (state,action) pairs:
![[Pasted image 20251027172425.png]]
The term with the environment transition probability $p$ cancels out, this is good as it is unknown in the Monte Carlo setting.

Finally we can use $\rho$ to estimate the off-policy returns wrt $\pi$:
![[Pasted image 20251027172534.png]]
these importance ratios can be seen as weights of a weighted average.

From this theoretical framework we can define an off-policy MC prediction algorithm to evaluate a policy $\pi$ by following a behavior policy $b$:
![[Pasted image 20251027233128.png]]

In this algorithm both W and G are computed backwards to ensure efficiency.
We can also notice how we follow policy $b(a|s)$ to generate the episode, and also we can see how we are using the importance sampling ratio to correct the weight of the estimated return.

The additional check to improve efficiency is done to 

This case is the every-visit version, it's easy to switch to first-visit by just adding the check.

---

# Control

We need to keep in mind that coverage may shift over time in the case of GPI with off-policy MC control. If for example we use a soft policy as a behavior policy we don't have to worry about this shifting coverage.

Anyway in practice off-policy MC control doesn't work well due to high variance estimates, some of the causes are explained at [[#Using importance sampling in MC methods]]. So we skipped this in the course.

---


