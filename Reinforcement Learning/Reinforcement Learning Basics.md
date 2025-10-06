#rl
Reinforcement Learning is a machine learning paradigm based on using reward signals to train agents to achieve a certain goal.
The differences with regular ML are:
- No supervisors, only a scalar reward signal
- Feedback is delayed from when the action is taken, not instantaneous
- Time is important, in the sense that we cannot assume iid data, the data is inherently sequential
- The agent's action affect the subsequent data it will receive. e.g. if a robot moves left it will receive different data than if it moves forward

We define the reward $R_t$ as a scalar feedback signal that tells us how good the agent did at time $t$.
The `reward hypothesis` in RL is that all goals can be expressed as the maximization of the expected cumulative reward.

Some important caveats are that action may have long term consequences and may sacrifice immediate reward in order to obtain a large reward in the future. Also rewards may be delayed from when the action is taken anyway.

---

At each time step $t$ an agent executes action $A_t$ , receives observation $O_t$ and receives a scalar reward $R_t$.

The environment at time $t$ receives action $A_t$ and emits the observation $O_{t+1}$ and the reward $R_{t+1}$.

The history up to time $t$ is made up of all observations, rewards and actions up to time $t$, (actions at time $t$ excluded).

$$
H_t = O_1,R_1,A_1,\dots,A_{t-1},O_t,R_t
$$
Saving the complete history is often not feasible so we need to save some state as a function of the history, $S_t=f(H_t)$.

The environment's state $S^e_t$ is the environment's private representation, it's usually not visible to the agent. Meaning the agent doesn't get to see everything about the environment, also some part of $S^e_t$ is irrelevant to the task we want to carry out. 

The agent's state $S^a_t$ is the agent's internal representation, is it our decision for what the agent needs to remember about history in order to be able to pick useful actions using its own state (basically its memory of the history $H_t$, again it can be any function of history).

An information state (or Markov state) contains all useful information from the history.
A state $S_t$ is Markov iff $\mathbb P[S_{t+1}|S_t]=P[S_{t+1}|S_1,\dots,S_t]$

In words "the future state is independent from the past states given the present states". You can only keep $S_t$ and you can "throw away" the past history as it's not needed.


- Fully vs partially obs
- Parts of an agent: policy, value func,

# Parts of an agent
These are the most common parts of an agent, these are not necessarily present in all agents. We could not have them and also we could have other parts, these are just the basic ones that are common.

### Policy
It's the agent's function that determines behaviour.
It's a map from state to action and can be either deterministic, e.g. $\pi(s)=a$ or stochastic e.g. $\pi(a|s)=\mathbb P[A_t=a|S_t=s]$
![[Pasted image 20250815125218.png]]
### Value function
The value function is a prediction of the future reward, that depends on the policy we are using.
$$v_\pi(s)=\mathbb E_\pi[R_t+\gamma R_{t+1}+\gamma^2 R_{t+2},\dots|S_t=s]$$
it evaluates the goodness/badness of the state $s$. The constant $\gamma$ is the discount factor, that tells us to care more about reward in the near future than in the distant future, usually it makes sense to have $0\le\gamma\le 1$.
![[Pasted image 20250815125235.png]]
### Model
The model predict what the environment will do next in terms of state and reward.

We have that for example:
- $\mathcal P_{ss'}^a=\mathbb P[S_{t+1}=s'|S_t = s, A_t=a]$, so in general $\mathcal P$ predicts the next state of the environment.
- $\mathcal R_s^a=\mathbb E[R_t|S_t=s,A_t=a]$, so in general $\mathcal R$ predicts the next immediate reward

In actuality the model can be avoided, and there are a series of RL methods that are "model-free" so we don't build a specific model.
![[Pasted image 20250815125306.png]]

---

# Taxonomy of RL agents
### Taxonomy: `value-based`/ `policy-based`/`actor-critic`
If an agent has a value function and the policy is implicit (meaning we choose the action based on maximizing the value function) then we have no policy, we talk about a `value-based` agent.

If an agent explicitly represent the policy and does not explicitly estimate the value function then we refer to this agent as a `policy-based` agent.

If we store directly both value and policy we are talking about an `actor-critic` RL agent.
### Taxonomy: `model-free`/
With `model-free` agents we don't try to explicitly figure out how the environment works we just directly update either/or value and policy (which of these depends on the previous [[#Taxonomy `value-based`/ `policy-based`/`actor-critic`|taxonomy]])
With `model-based` agents we first need to build a model of the environment and then apply the RL algorithm.

---

# Exploration vs Exploitation

- Exploration is the process of trying new actions to gather more information about the environment, potentially discovering better strategies in the long run
- Exploitation leverages the agent’s current knowledge to choose the action it believes will yield the highest reward
Having the correct balance is necessary to have a good agent. 

---

# Prediciton vs control
### 1. **Prediction**

**Goal:** _Evaluate_ a given policy.  
You’re **not** trying to change the policy — you just want to know how good it is.

- **Input:**
    
    - A fixed policy π\piπ (mapping from states to actions or action probabilities).
        
- **Output:**
    
    - The **value function** vπ(s)v_\pi(s)vπ​(s) or **action-value function** qπ(s,a)q_\pi(s, a)qπ​(s,a), which estimates expected return when following π\piπ.
        
- **Key Question:**
    
    > "If I keep following this policy, how much reward will I get in the long run from each state (or state-action pair)?"
    
- **Examples:**
    
    - Policy evaluation in policy iteration.
        
    - Estimating how good a human-designed navigation policy is for a robot.
        

---

### 2. **Control**

**Goal:** _Find_ an optimal policy.  
Here you **are** trying to improve the policy over time.

- **Input:**
    
    - The environment’s dynamics (or the ability to interact with it).
        
- **Output:**
    
    - An optimal policy π∗\pi^*π∗ that maximizes expected return.
        
- **Key Steps:**
    
    - **Evaluate** the current policy (prediction step).
        
    - **Improve** the policy by acting greedier with respect to the value estimates.
        
    - Repeat until convergence.
        
- **Examples:**
    
    - Q-learning, SARSA, Actor-Critic.
        
    - Training an agent to beat Atari games from scratch.