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

In RL the state transition matrix is not known but we don't care about estimating it.

Markov processes just provide the transitions but the agent is not involved and cannot affect the transitions with it's actions, also this formalization does not include rewards so we need to extend this formalism to be better suited for RL.

In the case transition probabilities change over time (non-stationarity) there's a non stationary extension to MPs.

---
# Markov Reward Processes
---reward processes
# Markov Decision Processes
----decision processes

