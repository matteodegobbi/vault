#todo 
#rl 

We want to find a method that generalizes TD(0) and Monte Carlo, this can be useful to balance the bias-variance trade-off we have between these two methods.

Instead of considering just the bootstrapped value using the value of the next state like in TD(0), or considering the full discounted sum of rewards like in MC, we define the best estimation of the return after some number of steps as:
![[Pasted image 20251109194344.png]]
For $n=1$ we have that this estimate $G_{t:t+1}$ is equal to the TD target in TD(0), if we choose a generic $n$ we can use the estimate $G_{t:t+n}$ as the TD target and obtain a generalized version of TD(0) with an arbitrary number of steps before using the bootstrapped estimate.

We can also see that for $n=\infty$ this is equivalent to MC as we don't use any bootstrapping and we consider the full sum of discounted rewards.
![[Pasted image 20251109194749.png]]

For a generic $n$ we can define:
![[Pasted image 20251110233151.png]]

N.B. $G_{t:t+n}$ is not defined when the episode is shorter than $n$ steps.

We can then use this n-step TD target to write an algorithm for prediction:
![[Pasted image 20251111000504.png]]
Variable $\tau$ stores the time of the state whose estimate we want to update, for this reason it's set to $t-n+1$, whenever we are at $n-1$ time-step after a state we can update its value function as after taking the action we have access to:
1. All the rewards up to $R_\tau=R_{t-n+1+n}=R_{t+1}$ 
2. The state $S_{t+1}$
Which are needed to compute the n-step TD target.
The check for $\tau>0$ is necessary to start updating the value only after at least $n-1$ time-steps have passed for the reasons explained above. 

The whole procedure goes on until $\tau\triangleq t-n+1$ is equal to $T-1$, meaning until $t=T+n+2$, this is because we need to update all the states near the terminal states after the episode ends since they cannot be updated earlier than after $n-1$ time-steps have passed since they've been observed. For these last states close to the terminal state the estimate of the return will just be the sum of the discounted rewards like in MC, in fact we don't have any state after $T$ from which we can bootstrap the estimate. This is the reason for the condition $\tau+n<T$ used to include the bootstrapped V.

This version of the algorithm is not efficient as it recomputes G at every iteration, it can be made more performant but the pseudocode would be more complicated.
