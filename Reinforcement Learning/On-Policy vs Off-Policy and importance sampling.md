#rl 
#todo 
On-policy ("learning on the job"): learn about policy $\pi$ from experience sampled from policy $\pi$.

Off-policy ("look over someone’s shoulder"): learn about policy $\pi$ (target policy) from experience sampled from policy 𝑏 (behavior policy). In off-policy we use the behavior policy to collect data from the environment in order to evaluate an optimal policy.


# Off-Policy learning
There are some reasons why it makes sense to consider off-policy methods:
1. We can leave the exploration to the behavior policy and reach optimal policies, this cannot be the case for example in $\varepsilon$-soft policies as the non-optimal actions taken occasionally imply that the policy is not optimal.
2. We may want to gain experience from observing other agents (or humans)
3. Re-use experience generated from old policies $\pi_1,\pi_2,\dots$ this means that we don't need to rerun the whole simulation whenever we want to change something e.g. the rewards
4. We can learn multiple policies while following one behavior policy, e.g. one policy that follows a path closely but it's not punished if it's slow and another policy that can less precise if it can be fast can both be learned using a single behavior policy.


## Necessary conditions 
To be able to use Off-Policy we need to have:
1. **Knowledge of $b(a|s)$** otherwise we cannot use the math we'll develop in the following ([[Monte Carlo - Off-Policy methods]])
2. **Coverage**: if $\pi(a|s)>0\rightarrow b(a|s)>0$, this is necessary in order to have that the behavior policy explores (state, action) pairs that have non-zero probability in the target policy. This is needed because if this wasn't the case the agent cannot obtain good estimates as it doesn't encounter those (state, action) pairs.

Almost all off-policy methods utilize importance sampling: a general technique for estimating expected values under one distribution given samples from another.

![[Pasted image 20251026213956.png]]
with $\rho(x)=\frac{\pi(x)}{b(x)}$.

Then we can consider $x\rho(x)$ as a new r.v. and we can than estimate that with MC methods as a weighted sample average:
![[Pasted image 20251026214225.png]]
Importance sampling can be useful to also reduce the variance of our estimates (maybe not in the case of RL idk)
[Video on importance sampling by Mutual Information](https://youtu.be/C3p2wI4RAi8?si=wjRh1yNfapNd4Eu9)

The usage of importance sampling for off-policy learning using MC methods is explained in [[Monte Carlo - Off-Policy methods]].

---

All the Monte Carlo RL algorithms we saw can be classified either as on-policy or off-policy.

On-Policy:
- Prediction: First-Visit and Every-Visit MC prediction.
- Control: model free GPI, specifically ES and $\varepsilon$-soft policy
[[Monte Carlo - On-Policy methods]]

Off-Policy:
- Prediction: off-policy MC prediction with importance sampling
- Control: Skipped in lectures, can be found at chapter 5.7 in the book
[[Monte Carlo - Off-Policy methods]]
