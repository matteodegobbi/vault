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

## Control



