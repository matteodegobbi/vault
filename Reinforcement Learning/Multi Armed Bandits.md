#rl 
In the multi armed bandits setting we only have 1 state.
The episodes are structured like this:
Fixed state, Action 1 --> Reward 1
Fixed state, Action 2 --> Reward 2
and continues like this, meaning an episode is only made up of an action out of K possible ones (K-armed) followed by a reward then the episode finishes and a new independent episode starts, the state never changes.

This problem allows us to see the exploitation-exploration dilemma and the decision making under uncertainty problem.

---

In this setting we have:
- a single state
- k different possible actions
- Each action provides a stochastic reward (following an unknown probability distribution)
- the q-value of an action $q_* (a)=\mathbb E[R_t|A_t = a]$.
N.B. here t indicates the episode number (that is typically indicated with k), while in typical RL settings t will indicate the discrete time-stamp within an episode.

We want to estimate the q-value of actions, to do this we can use the sample average of the reward when a certain action is executed, meaning:
$$Q(a) = \frac{\sum_{i=1}^{t-1} R_i \cdot \mathbb{1}_{A_i = a}}{\sum_{i=1}^{t-1} \mathbb{1}_{A_i = a}}$$
This can be recomputed every time new data is collected.

# TODO TITOLO
## Greedy policy
Using this policy we select every time the action according to:
$$ A_t =\arg\max_{a}{Q_t(a)} $$
(where $Q_t(a)$ is the sample average at episode t for action a)
This simple policy has a lack of exploration problem, we may be stuck with a suboptimal action.

## $\varepsilon$-Greedy policy
This is a stochastic policy in which we select the greedy action with probability $1-\varepsilon$ and we select a random action with probability $\varepsilon$ with $\varepsilon\in(0,1)$. 
The random (non-greedy) actions are chosen with uniform probability.

The idea behind this policy is to balance exploration with exploitation: we want to explore other actions while often choosing the best current action.
## Upper confidence bound - UCB
TODO
## Gradient bandit 
TODO