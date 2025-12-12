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

N.B. $G_{t:t+n}$ is not defined when the episode is shorter than $n$ steps, in practice we use the sum of discounted rewards up to the terminal state if the episode is shorter than $n$.

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
The idea is to use all the n-steps targets in between TD(0) (1 step only) and Monte Carlo (infinite steps) and use a weighted sum of these n-step TD approaches to update the value function.
We will have a $\lambda$ parameter that allows us to weigh differently the various n-step approaches, we can define the $\lambda$-return as:
![[Pasted image 20251111124707.png]]
As the value of $\lambda$ gets closer to 0 we weigh closer updates more and further updates less:
![[Pasted image 20251111124902.png]]

The weights form a geometric decay, that means:
- 1-step return gets the highest weight
- 2-step, 3-step returns get smaller and smaller weights
This expresses how far into the future we trust our rollouts, we don't average them with equal weight because we trust more recent TD errors more than long term ones, also using this decay is useful to balance variance and bias, if we summed all the contributions equally we wouldn't be balancing the trade-off.

N.B. $G_{t:t+n}=G_t$ whenever $t+n\ge T$ by convention meaning no bootstrap happens for those values of $t$.

If we use $\lambda=0$ the algorithm becomes equivalent to TD(0) while for $\lambda=1$ to MC.
We can see this better by decomposing $G^\lambda_t$ into a term containing the n-steps return where the last step is before terminal time $T$ and a term where the episode terminates before the n steps and for which we consider the whole return:
![[Pasted image 20251127224525.png]]
and we can see that for $\lambda=1$ the first term disappears and $G^\lambda_t=G_t$ so it's MC. For $\lambda=0$ the second term disappears and only $G_{t:t+1}$ remains which is equal to the TD target.

To derive the expression in the image just start from the def of lambda return, split the summation for the last value of n for which we consider the n-step return and not the full return, this means that for $\hat n=T-t-1$ $G_{t:t+\hat n}=G_{t:T-1}=R_{t+1}+\dots+\gamma^{\hat n-1}R_{T-1}+\gamma^{\hat n}V(S_{T-1})$ 
and if we considered $\hat n+1$ then we will have $R_T$ and no next state.
After splitting the summation, the second summation is the geometric series translated by $T-t-1$.

## Forward vs Backward view of $\text{TD}(\lambda)$ 
Since in the weighted sum we need to use all the n-steps returns we can only compute $G^\lambda$ at the end of the episode, like we did in MC. This means that we cannot learn along the way like we did in TD(0) and in n-step bootstrapping TD.
This "forward" version of $\text{TD}(\lambda)$ can only be applied offline like MC.
![[Pasted image 20251127171153.png]]
>forward view

To deal with this problem we can change our view to look at the backward version of $\text{TD}(\lambda)$, to do this we need to use eligibility traces.

![[Pasted image 20251127171227.png]]
>backward view

Eligibility traces are a concept used for credit assignment of the reward to different states visited during the trajectory, eligibility traces include both a recency heuristic (states near the reward get more credit) and a frequency heuristic (a state that appears more often should get more credit).

This is the definition of the eligibility trace for tabular $\text{TD}(\lambda)$:
![[Pasted image 20251127171755.png]]
We have a value of $E_t$ for each state in the state space. It includes a frequency heuristic because we increase $E(s)$ by 1 whenever the state $s$ is visited. Furthermore it includes a recency heuristic because it decays the value of $E(s)$ by $\gamma\cdot\lambda$ at every time-step (even when it's visited).

We can then rewrite an update function, that in this case differently from TD(0) will be applied to every state, if we call the TD-Error $\delta_t=R_{t+1}+\gamma V_t(S_{t+1})-V_t(S_t)$ 
we can write the update function $\forall s\in S$ at each time-step as:
![[Pasted image 20251127172559.png]]
This means that the update for a state is weighted by the credit that the state gets according to the eligibility trace. Since we have an eligibility trace for each state we can update all of them by considering the current TD error and they get credit for that current TD error proportional to their eligibility.

### Backward
We can now build an algorithm for backward $\text{TD}(\lambda)$ with online updates:
![[Pasted image 20251127235443.png]]


We also have a theorem that states that the backward and forward versions are equivalent if ran offline, meaning the sum of the updates is the same if ran offline.
When we run it online they are not exactly equivalent but the smaller the $\alpha$ the closer they are, more details in the slides.
![[Pasted image 20251128184816.png]]

N.B. Another way of using TD lambda but with the forward version is by truncating after n steps like in n-step bootstrapping but using the lambda return until for the non-truncated part. More details in the book.
### Other kinds of eligibility traces
Up to now we have considered accumulating traces but there are different versions that change how the update is carried out.
![[Pasted image 20251128184851.png]]


## $\text{SARSA}(\lambda)$
Since we are switching from prediction to control we will use $Q(s,a)$ instead of $V(s)$ and also the eligibility traces will be $E(s,a)$ instead of $E(s)$.
Also $G_{t:t+n}$ from now on will refer to the version using Q instead of V.

As in prediction we can define both a forward and backward view, the latter is more realistic to implement in practice.

Forward version:
![[Pasted image 20251128185158.png]]

Backward version:
![[Pasted image 20251128185212.png]]
![[Pasted image 20251128185232.png]]
![[Pasted image 20251128185257.png]]


# $\text{TD}(\lambda)$ with function approximation
When using [[Value function approximation]] we can derive a different version of $\text{TD}(\lambda)$ defining eligibility traces for the approximation model's weights.
In the book + truncated TD lambda.
TODO continua