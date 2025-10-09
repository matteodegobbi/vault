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
N.B. If the denominator is 0 we define Q with some default value (e.g. 0 or an higher value as in [[#Optimistic initial values]])

$Q(a)$ can be recomputed every time new data is collected, but we can derive an incremental version that is more efficient as it doesn't need to store all past rewards for all actions.

The derivation is in the slides/book:
$$
Q_{n+1} = Q_n + \frac{1}{n}\left[R_n-Q_n\right]
$$

This form of equation will often appear in RL:
$$\texttt{NewEstimate}\leftarrow \texttt{OldEstimate} + \texttt{StepSize}\left[ \texttt{Target} - \texttt{OldEstimate}\right]$$
---

# Non-Stationary setting
If the distribution of rewards changes over time we need to use a different method to compute the sample averages as rewards further away in the past matter less as the distribution might have changed in the meantime. 

To achieve this we can use a constant step size $\alpha\in(0,1]$ instead of $\frac{1}{n}$ which makes it so the step size decreases as the number of episodes increases.

$$
Q_{n+1} = Q_n + \alpha\left[R_n-Q_n\right]
$$

Using a constant $\alpha$ is equivalent to computing an exponential moving average of the rewards, meaning that we weigh rewards in the average with a coefficient exponential in the distance from the current episode.

$$
Q_{n+1} = (1-\alpha)^n Q_1 + \sum\limits_{i=1}^n{\alpha(1-\alpha)^{n-i}Q_i}
$$
For decreasing $i$, $(n-i)$ increases meaning $(1-\alpha)^{n-1}$ decreases exponentially, weighing less rewards in the far past wrt recent rewards. This provides a way to deal with non stationary processes provided they change slowly enough for the system to adapt.

In the books there are some theoretical conditions to guarantee convergence but in practice they are not useful as they would make the system either converge too slow or making it not applicable to non-stationary environments.
# Different strategies to solve multi-armed bandits
## Greedy policy
Using this policy we select the action according to:
$$ A_t =\arg\max_{a}{Q_t(a)} $$
(where $Q_t(a)$ is the sample average at episode t for action a)
This simple policy has a lack of exploration problem, we may be stuck with a suboptimal action.
## $\varepsilon$-Greedy policy
This is a stochastic policy in which we select the greedy action with probability $1-\varepsilon$ and we select a random action with probability $\varepsilon$ with $\varepsilon\in(0,1)$. 
The random (non-greedy) actions are chosen with uniform probability.

The idea behind this policy is to balance exploration with exploitation: we want to explore other actions while often choosing the best current action.

![[Pasted image 20251008085928.png]]
``Implementation of epsilon greedy with incremental computation of sample average``
## Optimistic initial values
Instead of starting with Q=0 if we start with an higher value we encourage exploration by avoiding that the first best action becomes the greedy choice after just one episode.
This is done by setting high initial values for Q, this makes it so the actions that have not been taken many times will have higher values than the Q(a) for actions that have been taken.

>Whichever actions are initially selected, the reward is less than the starting estimates; the learner switches to other actions, being “disappointed” with the rewards it is receiving. The result is that all actions are tried several times before the value estimates converge. The system does a fair amount of exploration even if greedy actions are selected all the time.

This drives exploration only at the beginning as after some episodes the initial value doesn't affect the q-values much. 
Also in some applications we might not know good initial values for Q or this strategy doesn't work well for non stationary problems (distribution changes with time).

## Upper confidence bound - UCB
Instead of choosing uniformly among random actions like in epsilon greedy, we can exploit the information about how many times the action was taken previously (actions that were taken many times will have a better estimates).

We do this with an optimistic heuristic: instead of choosing the action with the highest estimate we choose the action that "potentially" would be the best in the sense that the upper bound of Q using Hoeffding's inequality is the highest.
This encourages exploration because it chooses actions that potentially could be better before trying actions that we are sure about but have less potential reward.

![[Pasted image 20251008091436.png]] ``Policy for UCB, c is an hyperparameter, N_t(a) is the number of times action a was taken up to episode t``

With UCB exploration is reduced over time as the estimates become more confident.

Since we derive this using Hoeffding's it's distribution free.
(HOW CAN WE DEAL WITH NON BOUNDED REWARDS LIKE GAUSSIAN)

[Derivation of the exploration upper bound using Hoeffdings inequality](https://lilianweng.github.io/posts/2018-01-23-multi-armed-bandit )
## Gradient bandit 
In this method we define a preference vector $H_t(a)$ which tells us how preferred a specific action is.
With this preference vector we can obtain a distribution by taking the softmax.

The preference vector is updated with gradient ascent, we maximize $\mathbb E_\pi[R]$
, we compute the gradient using the log-derivative trick. Actually we don't just use gradient ascent but we include a baseline term to reduce variance.

So the final update rule is:
![[Pasted image 20251009165317.png]]
where $\alpha$ is the learning rate and $\bar R_t=\frac{1}{t-1}\sum\limits_{i=0}^{t-1}{r_t}$ which is used as a baseline to reduce variance and update the preferences based on wether they did better than the average of the previous actions.

In the update rule we update both the action we took and all the other ones, based on how well the chosen action did wrt the mean if the action did worse we decrease its preference and increase the one of all the other actions and vice versa.

---

An important observation is how in these methods we are not interested in estimating the reward distributions for the different arms, we only care about picking the best action. We might have that from a point of view of RL a reward distribution estimate with higher MSE might be better than one with a lower MSE because if overvalues the best action. Example in the pdf.