#rl 
#todo 
As in [[Monte Carlo - On-Policy methods||Monte Carlo]] in TD we are in the model free case where transition probabilities and reward distributions are unknown, this method can be used for both prediction and control.

TD learning uses bootstrapping, meaning we can use it for incomplete episodes and also in the continuous case.

We'll also see how TD learning is a general framework that also includes [[Monte Carlo - On-Policy methods|MC]] methods but first we'll see the `TD(0)`version and then we'll generalize it later into [[asd|aggiungi link]].

We can understand why TD learning is useful by examining some disadvantages of MC:
1. Assuming we are in the episodic case.
2. MC doesn't exploit new info (rewards) as soon as it's available but we have to wait until the episode is over.

---
# TD(0)
The main idea to understand TD learning is that instead of waiting the end of the episode to utilize the reward information to update the value function it uses it immediately.

![[Pasted image 20251028000647.png]]

We call $R_{t+1}+\gamma V(S_{t+1}-V(S_t))$ the TD error.
We consider the constant step size case and not the sample average case.

We are considering an estimation of $G_t\sim R_{t+1}+\gamma V(S_{t+1})$, this process is called bootstrapping: meaning we use previous estimates to obtain newer estimates as soon as the reward is obtained.

Basically we take an action at time t and obtain the corresponding reward $R_{t+1}$ and the new state $S_{t+1}$ we can then improve out estimate of the previous state by updating it to be closer to the TD Target which uses the current estimate of the value of state $S_{t+1}$ and the reward to estimate $G_t$. 
## Prediction
The algorithm for prediction for TD(0) is:
![[Pasted image 20251028002610.png]]
Unlike MC we break down the episode in time-steps and the value function is update at each time step, not only at the end.

Some advantages over MC are:
![[Pasted image 20251028002925.png]]

We can study the different performance in terms of prediction by considering a case where we know the actual state values of a policy and compare the error that TD makes vs Monte Carlo:
![[Pasted image 20251029091042.png]]
Comparing TD and Monte Carlo in the prediction step is only useful to understand the difference, but the performance of the algorithm can be seen only by control not just prediction by itself as in control we're not interested in perfect estimates if the policy is optimal.

### Bias-Variance trade-off RL vs Monte Carlo
Monte Carlo provides an unbiased estimation as it uses the complete returns to approximate $v_\pi(s)$, this is true also in practice when we use the sample averages of returns as the expectation of the sample average of an r.v. is the same as the expectation of the r.v. itself as per weak LLN.

The true TD-Target $R_{t+1}+\gamma v_\pi(S_{t+1})$ would also be unbiased, but in practice we don't know the actual value function so we cannot use it, we only have the previous approximation $V(s)\sim v_\pi(s)$.
This means that the actual TD target $R_{t+1}+\gamma V(S_{t+1})$ is actually a biased estimate of $v_\pi(S_t)$ .

At the same time the TD target has much lower variance than the return, this is because the returns depends on many random actions, transition and rewards while the TD target depends on one random action, transition and reward.
This can be proven but we didn't.

These considerations imply that:
* MC has high variance and low bias
* TD has low variance and higher bias
* TD(0) is more sensitive to initial values of $V(s)$ while Monte Carlo is less so
* TD(0) converges faster
* MC has good convergence properties even with function approximation, while TD(0) converges to $v_\pi(s)$ but not always if function approximation is used

---


TODO esempio Con 8 episodi soluzione MC vs soluzione TD(0)
### Batch MC and TD
TODO limited amount of data...

TODO TAXONOMY OF RL METHODS SO FAR
## Control

### SARSA
TODO SARSA
### Q-Learning




