#rl 
As in [[Monte Carlo - On-Policy methods||Monte Carlo]] in TD we are in the model free case where transition probabilities and reward distributions are unknown, this paradigm can be used for both prediction and control.

TD learning uses bootstrapping, meaning we can use it for incomplete episodes and also in the continuous case, unlike MC which needs to use finite length episodes.

We'll also see how TD learning is a general framework that also includes [[Monte Carlo - On-Policy methods|MC]] methods but first we'll see the `TD(0)`version and then we'll generalize it later into [[n-step bootstrapping and TD lambda]].

We can understand why TD learning is useful by examining some disadvantages of MC:
1. MC needs to assume we are in the episodic case.
2. MC doesn't exploit new information (rewards) as soon as it's available, we have to wait until the episode is over since we need to compute the complete returns. 

---
# TD(0)
The main idea to understand TD learning is that instead of waiting the end of the episode to utilize the reward information to update the value function it uses it immediately.

![[Pasted image 20251028000647.png]]

We call $R_{t+1}+\gamma V(S_{t+1})-V(S_t)$ the TD error.
We consider the constant step size case and not the sample average case, this is because unlike the return in MC the TD Target is not stationary as it includes $V$ which we are actually changing (also if we don't use this step size we keep the bias from the beginning initialization).

We are considering an estimation of $G_t\sim R_{t+1}+\gamma V(S_{t+1})$, this process is called bootstrapping: meaning we use previous estimates to obtain newer estimates as soon as the reward is obtained.

Basically we take an action at time t and obtain the corresponding reward $R_{t+1}$ and the new state $S_{t+1}$, we can then improve our estimate of the previous state by updating it to be closer to the TD Target which uses the current estimate of the value of state $S_{t+1}$ and the reward to estimate $G_t$. 
## Prediction
The algorithm for prediction for TD(0) is:
![[Pasted image 20251028002610.png]]
Unlike MC we break down the episode in time-steps and the value function is update at each time step, not only at the end.

Some advantages over MC are:
![[Pasted image 20251028002925.png]]

We can study the different performance in terms of prediction by considering a case where we know the actual state values of a policy and compare the error that TD makes vs Monte Carlo:
![[Pasted image 20251029091042.png]]
Comparing TD and Monte Carlo in the prediction step is only useful to understand the difference, but the performance of the algorithm can be seen only by control not just prediction by itself as in control we're not interested in perfect estimates if the policy is optimal.

### Bias-Variance trade-off TD vs Monte Carlo
Monte Carlo provides an unbiased estimation as it uses the complete returns to approximate $v_\pi(s)$, this is true also in practice when we use the sample averages of returns: the expectation of the sample average of an r.v. is the same as the expectation of the r.v. itself as per weak LLN.

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
### Comparison of TD learning with previous methods
#### Convergence
TD converges to the maximum likelihood Markov model, meaning it converges to the MDP that best fits the data.

MC converges the solution with minimum mean squared error, meaning the best fit for observed returns.

TD exploits Markov property and it is usually more efficient in Markov environments. More details in Lecture 9 pdf.

#### Batch MC and TD
If the number of episodes grows both MC and TD converge to $v_\pi$.

In many cases we however have limited amount of experience: a common approach is to present the experience repeatedly until the method converges upon an answer
We repeatedly sample episode $k\in[0,K]$ and we apply MC or TD(0) to that episode. Under this batch training, MC and TD(0) converge to an ‘optimal’ solution, but with different definitions of optimality

![[Pasted image 20251102151903.png]]
In this example we can see the two different solutions obtained by TD and MC with the same data.

#### Taxonomy of RL methods
![[Pasted image 20251101232915.png]]
![[Pasted image 20251101232926.png]]
![[Pasted image 20251101232936.png]]

We can classify the methods seen so far on 2 axes depending on the use of bootstrapping and sampling:
Bootstrapping means that we use a previous estimate to compute the update for the new estimate.
Sampling means we use samples to estimate expectations.
MC and TD sample, DP does not.
TD and DP use bootstraps, MC does not.
![[Pasted image 20251102101720.png]]

---
## Control
As in MC when dealing with control problems we need to use $q$ instead of $v$ since we don't have access to the transition probabilities and the reward distribution of the MDP. (As in MC, GPI over $q$ is model free, over $v$ it's not)

We only have partial evaluations of $q_\pi$ because we are working with TD(0) for the evaluation which just gives us the newest estimate, this means that our approach for control will be more similar to value iteration and not policy iteration.

We also need to consider exploration as we did in MC.

### SARSA
This control method using TD, is based on GPI. It loops over all the episodes and over all the time steps in an episode updating the estimate of $Q(s,a)$ like we did in TD(0) for $V(s)$. 
It's important to consider that in SARSA the action at next time step is already chosen at the previous time-step following the current policy, this makes it an on-policy method (unlike Q-Learning as we'll see later which always chooses the greedy next eps action after the improvement).FORSE NON GIUSTO CONTROLLA

The exploration is carried out through an $\varepsilon$-greedy policy.
![[Pasted image 20251102102657.png]]
### Q-Learning
![[Pasted image 20251102192838.png]]
This is an off-policy TD method, the two main differences with SARSA are:
1. In the TD Target SARSA uses the next action that will be taken by the agent while following the current policy. Instead Q Learning in the target always considers the greedy action, being optimistic as if the epsilon exploratory action will never be taken
2. Point 1. has a consequence on the pseudocode of the algorithms, in SARSA we store: $S_t$, $A_t$, $R_{t+1}$,$S_{t+1},A_{t+1}$. The current state, action and reward and the next state are also used in Q Learning but $A_{t+1}$ is not computed in Q Learning as we don't consider the actual next action taken in the TD target so we don't need to compute until the next iteration, this rearranges the order of operations: In SARSA the update is done after every $S_t$, $A_t$, $R_{t+1}$,$S_{t+1},A_{t+1}$ tuple while in Q-Learning it's done after every $S_t$, $A_t$, $R_{t+1}$,$S_{t+1}$ tuple.
From these 2 points above we can understand why Q Learning is off-policy, we have a behavior policy (often $\varepsilon$-greedy) and a target policy: the greedy policy (which appears in the TD target in Q learning instead of the eps greedy choice like in SARSA).

Even though Q-Learning is off-policy we don't need to use importance sampling like in MC. This is because we can compute the expected return from any state by considering that the target policy is the greedy policy wrt the action values Q, all non-maximum actions have probability 0, this means that the expected return from a state is equal to the max action value function in that state.

#### Comparison with SARSA
![[Pasted image 20251102223521.png]]

We can say that since both SARSA and Q-Learning use incomplete estimates of Q they act similarly to value iteration in DP, but SARSA update is similar to the Bellman Expectation equation while in Q-Learning the update resembles the Bellman Optimality equation.
An example of the application of the two update rules can be seen below:
![[Pasted image 20251102223846.png]]

### Expected SARSA 
![[Pasted image 20251102224939.png]]
This algorithm is another off-policy modification of SARSA where we consider all the next possible actions weighted by their probability under the current policy instead of sampling the next action like SARSA does or taking the maximum like in Q-Learning.

Basically as the target we consider the reward + the expected value of the Q of the next state when the next action is sampled according to the policy. Equivalently we can say we take the expectation of the Q over policy $\pi$.

Expected SARSA has slower updates, but it is more stable (lower variance than SARSA).

![[Pasted image 20251102225201.png]]
![[Pasted image 20251102225316.png]]


### Considerations on SARSA, Q-Learning and Expected SARSA
In practice Q-Learning often converges faster than SARSA because it takes a smaller number of iterations even if the single iterations are slower in Q-Learning due to the max operation.
It might help to use a smaller value of $\alpha$ in SARSA compared to Q-Learning, this is because SARSA uses the estimate of the next action value in its target: this changes every time the agent takes an exploratory action. A smaller step-
size can help SARSA to avoid overweighting exploratory actions that 'ruin' the estimate of a state.

Sometimes acting off-policy can be detrimental, see cliff world example in Lecture 10.

Expected SARSA moves deterministically in the same direction as SARSA moves in expectation. Thanks to its more stable updates, Expected SARSA can handle higher values of $\alpha$.




