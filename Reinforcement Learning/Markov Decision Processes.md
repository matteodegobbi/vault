#rl #todo
From [[Reinforcement Learning Basics]]:
>A state $S_t$ is Markov iff  $\mathbb P[S_{t+1}|S_t]=P[S_{t+1}|S_1,\dots,S_t]$
>In words "the future state is independent from the past states given the present state". You can only keep $S_t$ and you can "throw away" the past history as it's not needed.

Given this, we can define the **state transition matrix** $P$ for a Markov process with $n$ states:

$$
P =
\begin{bmatrix}
P_{11} & P_{12} & \dots & P_{1n} \\
P_{21} & P_{22} & \dots & P_{2n} \\
\vdots & \vdots & \ddots & \vdots \\
P_{n1} & P_{n2} & \dots & P_{nn}
\end{bmatrix}, \quad
P_{ij} = \mathbb{P}[S_{t+1} = S_j \mid S_t = S_i],
$$

where P is a row-stochastic matrix, meaning:

$$
P_{ij} \ge 0, \quad \sum_{j=1}^{n} P_{ij} = 1 \quad \forall i.
$$

The state probability distribution $\mathbf{s}_t$ evolves over time according to

$$
\mathbf{s}_{t+1} = P^T \mathbf{s}_t,
$$

where $\mathbf{s}_t$ is a row vector representing the distribution over states at time $t$.

(Since $\sum\limits_{i=1}^{n}{P_{ij}s_i}$ gives the $j$-th component at time t+1 so we must transpose )

---

Markov process (Markov chain): memoryless random process.
It's a tuple $\langle S,P\rangle$, where $S$ is a finite set of states and $P$ is the state transition probability matrix.
$$
P =
\begin{bmatrix}
P_{11} & P_{12} & \dots & P_{1n} \\
P_{21} & P_{22} & \dots & P_{2n} \\
\vdots & \vdots & \ddots & \vdots \\
P_{n1} & P_{n2} & \dots & P_{nn}
\end{bmatrix}, \quad
P_{ij} = \mathbb{P}[S_{t+1} = S_j \mid S_t = S_i]
$$

In RL the state transition matrix is not known but we don't care about estimating it (even if we could).

Markov processes just provide the transitions but no agent is involved and we cannot affect the transitions with actions (it has no agency), also this formalization does not include rewards so we need to extend this formalism to describe RL.

In the case transition probabilities change over time (non-stationarity) there's a non stationary extension to MPs.

---
# Markov Reward Processes
A Markov reward process is a tuple $\langle S,P,R,\gamma\rangle$, where
- $S$ is a finite set of states like in MPs.
- $P$ is the state transition probability matrix like in MPs.
- $R$ is a reward function $R_s=\mathbb E[R_{t+1}|S_t=s]$ (it is just the immediate reward, in that specific state. Since in this case no agency is involved the reward is associated with the state itself)
- $\gamma$ is a discount factor, $\gamma\in[0,1]$

![[Pasted image 20251010170336.png]]
In RL we are not interested in maximizing the value of a single step, but we want to maximize the return (return = goal of RL), this might entail choosing a temporarily bad reward action in order to obtain a future high reward, yielding a higher total return.

The discount factor is used for multiple reasons:
* near rewards are less uncertain than future rewards
* financial concepts like interest earning
* makes the infinite sum of the return converge
In MRPs rewards are consequences of states not of actions, since this model does not include agency. 
We can define a state value function to determine the long-term value of a state $s$.

![[Pasted image 20251010170943.png]]

We can estimate the value function for state $s$ with the sample average of returns from that state. Of course different values of $\gamma$ will yield different value functions, weighing future rewards more or less.
## Bellman equation for Markov reward processes
To compute the state value function $v(s)$ we can:
![[Pasted image 20251014225101.png]]
Where the law of iterated expectation is applied as $$ \mathbb E[G_t|S_t=s]=\mathbb E[R_{t+1}+\gamma G_{t+1}|S_t=s]=\mathbb E[R_{t+1}+\gamma\mathbb E[G_{t+1}|S_{t+1},S_t=s]|S_t=s]=
$$
and by applying the Markov property we get:
$$\mathbb E[R_{t+1}+\gamma\mathbb E[G_{t+1}|S_{t+1}]|S_t=s]$$
and finally by definition of $v(s)$ 
$$\mathbb E[R_{t+1}+\gamma v(S_{t+1})|S_t=s]$$

![[Pasted image 20251014225122.png]]
The last equation in the previous slide is just the application of the expectation, of course in RL we won't have access to the transition matrix as it's unknown and we are not interested in estimating it.

The Bellman equation can also be expressed in matrix form:
![[Pasted image 20251014231611.png]]
And in theory we can solve it as follows:
![[Pasted image 20251014231632.png]]

In practice we will never solve it this way as: 
1. For large number of states it's too slow 
2. We don't actually know $P$ and $R$
Actually we will use other efficient techniques to evaluate the Bellman equation (Dynamic programming, TD learning, Monte Carlo evaluation)

IMPORTANT: we can notice how for MRPs, Bellman Equation is linear this is not the case when we try to choose the action with highest return in MDPs as the max is not a linear operation.


# Markov Decision Processes

Markov Decision processes are an extended version of MRPs where agents can take decisions (they have agency) it is defined as follows:![[Pasted image 20251014232225.png]]
Now both the state transition and reward are conditioned on the action taken.

Since the agent can take action we define what's the policy of an agent:
![[Pasted image 20251014232447.png]]

* A policy fully defines the behaviour of an agent
* MDP policies depend on the current state only (Markov property)
* In MDP policies are stationary (do not depend on t), however we can change our policy in future episodes 
* We consider stochastic policies: this allow us for example to deal with  exploration
The policy does not deal directly with rewards, it may be learned or given

Now we also consider how the reward is a MRP where the transition probability between states and the reward expectation $R_s$ are influenced  by the policy:
![[Pasted image 20251014235009.png]]

Now that the agent can act we can define an action value function and we need to update the state value function to depend on the policy as the actions taken will influence the future return:
![[Pasted image 20251014234002.png]]
Similarly to what we did with MRPs we can define a Bellman equation, in this case since we have agency we will define 2 Bellman equations:
1. Bellman expectation equation, to evaluate a policy
2. Bellman optimality equation, to determine the value of the optimal policy

## Bellman expectation equation
Using the definitions of state value function and action value function we can relate $v_\pi(s)$ and $q_\pi(s,a)$.
We can express the 2 functions in terms of the other, then plugging in one of the two original equations for the state or action value functions we can obtain  recursive definitions for state or action value functions.

![[Pasted image 20251015081001.png]]
![[Pasted image 20251015081024.png]]

These steps can be achieved with the Law of Total Expectation to express $v(s)$ in terms of $q(s,a)$ and linearity of expectation to obtain the expression for $q(s,a)$

Again as we did for MRPs we can use the induced MRP by the MDP to write the Bellman expectation equation in matrix form (the only change is that both $P$ and $R$ depend on $\pi$)
## Bellman optimality equation

To be able to take action we want to determine the optimal policy: an MDP can be considered ‘solved’ on a RL perspective when the optimal action-value function is known: we always know the optimal action to take from a certain state, we could just take the action that maximizes $q_*$ for the current state.
![[Pasted image 20251016091554.png]]

To decide what the optimal policy should be we define an order over policies:
$$\pi\ge\pi' \text{ if } v_\pi(s)\ge v_{\pi'}(s) \ \forall s$$
(specifically a partial order since if we take 2 policies it could happen than one is better than the other only in specific cases, still we can define the optimal policy as one that is better in all states)

We have a theorem about the existence of optimal policies:
![[Pasted image 20251016091831.png]]

Also there is always a deterministic optimal policy, one can be determined easily if we have $q_*(s,a)$ for all states and actions, we can just choose $\pi$ to choose the action maximizing $q_*(s,a)$:
$$\pi_*(a|s)=\begin{cases} 
1 \text{ if } a=\arg\max\limits_{a\in A}{q_*{(s,a)}}\\
0 \text{ otherwise }
\end{cases}$$
An intuitive explanation on why there is always an optimal policy is that if we had 2 policies, one that is better on certain states and one that is better on other states we could create a third new policy that mixes the 2 by choosing the best one if the two for the states they are the best and this new policy would be better than either of them.

There might be more than one optimal policy, but all of them share the same optimal state value function and the same action value function.

We can use the Bellman optimality equation to express $v*(s)$ and $q_*(s,a)$ in terms of themselves recursively like we did for the Bellman expectation equation.

![[Pasted image 20251016093046.png]]
```
difference between Bellman optimality and expectation equations
```

For $v_*(s)$ we have :
![[Pasted image 20251016093134.png]]

While for $q_*(s,a)$ we have:
![[Pasted image 20251016093205.png]]

Since in the Bellman optimality equation a max operation is involved it's not linear, this means we cannot obtain a closed form solution even if we know $P$ and $R$. We need to use iterative methods like value iteration, policy iteration, q-learning, SARSA. 

---
