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
\mathbf{s}_{t+1} = \mathbf{s}_t P,
$$

where $\mathbf{s}_t$ is a row vector representing the distribution over states at time $t$.

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
Markov reward process
It's a tuple $\langle S,P,R,\gamma\rangle$, where
- $S$ is a finite set of states like in MPs.
- $P$ is the state transition probability matrix like in MPs.
- $R$ is a reward function $R_s=\mathbb E[R_{t+1}|S_t=s]$ TODO capire cosa significa che (it is just the immediate reward, in that specific state)
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
![[Pasted image 20251014233938.png]]

Now that the agent can act we can define an action value function and we need to update the state value function to depend on the policy as the actions taken will influence the future return:
![[Pasted image 20251014234002.png]]
Now we also consider how the reward is a MRP where the transition probability between states and the reward expectation $R_s$ are influenced  by the policy:
![[Pasted image 20251014235009.png]]
Similarly to what we did with MRPs we can define a Bellman equation, in this case since we have agency we will define 2 Bellman equations:
1. Bellman expectation equation, to evaluate a policy
2. Bellman optimality equation, to determine the value of the optimal policy

## Bellman expectation equation
## Bellman optimality equation
