#todo 
#rl 
# n-step bootstrapping
We want to find a method that generalizes [[TD (Temporal Difference) Learning#TD(0)|TD(0)]] and [[Monte Carlo - On-Policy methods|Monte Carlo]], this can be useful to balance the bias-variance trade-off we have between these two methods.

Instead of considering just the bootstrapped value by using the value function of the next state like in TD(0), or considering the full discounted sum of rewards like in MC, we define the best estimation of the return after some number of steps as:
![[Pasted image 20251109194344.png]]
For $n=1$ we have that this estimate $G_{t:t+1}$ is equal to the TD target in TD(0), if we choose a generic $n$ we can use the estimate $G_{t:t+n}$ as the TD target and obtain a generalized version of TD(0) with an arbitrary number of steps before using the bootstrapped estimate.

We can also see that for $n=\infty$ this is equivalent to MC as we don't use any bootstrapping and we consider the full sum of discounted rewards.
![[Pasted image 20251109194749.png]]

For a generic $n$ we can define:
![[Pasted image 20251110233151.png]]

N.B. $G_{t:t+n}$ is not defined when the episode is shorter than $n$ steps, in practice we use the sum discounted rewards up to the terminal state if the episode is shorter than $n$.

## Prediction
We can then use this n-step TD target to write an algorithm for prediction:
![[Pasted image 20251111000504.png]]
Variable $\tau$ stores the time of the state whose estimate we want to update, for this reason it's set to $t-n+1$, whenever we are at $n-1$ time-step after a state we can update its value function as after taking the action we have access to:
1. All the rewards up to $R_\tau=R_{t-n+1+n}=R_{t+1}$ 
2. The state $S_{t+1}$
Which are needed to compute the n-step TD target.
The check for $\tau>0$ is necessary to start updating the value only after at least $n-1$ time-steps have passed for the reasons explained above. 

The whole procedure goes on until $\tau\triangleq t-n+1$ is equal to $T-1$, meaning until $t=T+n-2$, this is because we need to update all the states near the terminal states after the episode ends since they cannot be updated earlier than after $n-1$ time-steps have passed since they've been observed. The last state to update is $S_{T-1}$ and it can be updated when $\tau=T-1$. For these last states close to the terminal state the estimate of the return will just be the sum of the discounted rewards like in MC, in fact we don't have any state after $T$ from which we can bootstrap the estimate. This is the reason for the condition $\tau+n<T$ used to include the bootstrapped V.

This version of the algorithm is not efficient as it recomputes G at every iteration, it can be made more performant but the pseudocode would be more complicated.

---
## Control 
We can also define an n-step version of [[TD (Temporal Difference) Learning#SARSA|SARSA]] by defining the update rule for Q-values:
![[Pasted image 20251111120855.png]]
which is the same as the one used in prediction for V.

From this we can define the algorithm as:
![[Pasted image 20251111120944.png]]
The differences with the prediction algorithms are:
1. Commit to taking action A' in the next iteration like in regular SARSA, meaning that the order of when we compute A and A' is different
2. Q instead of V
3. Update of policy $\pi$ to be $\varepsilon$-greedy wrt Q

---

off-policy n-step control with importance sampling is in the slides and in the book, it's optional for the exam.

---
# $\text{TD}(\lambda)$
The idea is to use all the n-steps targets between TD(0) and Monte Carlo and use a weighted sum of these n-step TD approaches to update the value function.
We will have a $\lambda$ parameter that allows us to weigh differently the various n-step approaches, we can define the $\lambda$-return as:
![[Pasted image 20251111124707.png]]
As the value of $\lambda$ gets closer to 0 we weigh closer updates more and further updates less:
![[Pasted image 20251111124902.png]]

The weights form a geometric decay, that means:
- 1-step return gets the highest weight
- 2-step, 3-step returns get smaller and smaller weights
This expresses how far into the future we trust our rollouts, we don't average them with equal weight because we trust more recent TD errors more than long term ones, also using this decay is useful to balance variance and bias.

## Forward vs Backward view of $\text{TD}(\lambda)$ 
Since in the weighted sum we need to use all the n-steps returns we can only compute $G^\lambda$ at the end of the episode, like we did in MC so we cannot learn along the way like we did in TD(0) and even n-step bootstrapping TD.

To deal with this problem we can change our view to look at the backward version of $\text{TD}(\lambda)$, to do this we need to use eligibility traces.

Eligibility traces are a concept used for credit assignment of the reward to different states visited during the trajectory, eligibility traces include both a recency heuristic (states near the reward get more credit) and a  frequency heuristic (a state that appears more often should get more credit).

TODO continuare da prox lezione
