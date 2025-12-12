#rl 
# Introduction
Up to now we have dealt with value-based methods: we learn a value function and then the policy is defined implicitly on the value function, e.g. $\varepsilon$-greedy.
In policy based methods we instead parametrize the policy directly and learn weights $\theta$ to optimize some objective measure that evaluates the policy. We call this parametrized policy $\pi(a|s,\theta)\triangleq\mathbb P[A_t=a|S_t=s,\theta_t=\theta]$, we use differentiable functional forms of the policy like Softmax, this allows to use gradient ascent approaches, taking the name of policy gradient.
Policy gradient methods both include ones that don't learn a value function (e.g. `REINFORCE`) and ones that learn both a value function and a parametrized policy (called [[Actor-Critic]] methods).
![[Pasted image 20251202220922.png]]

## Reasons for policy gradient methods
There are some advantages in using policy gradient approaches instead of inferring implicitly the policy from action value estimates. 
One advantage is that policy-based approaches can learn optimal stochastic policies, while strictly value-based methods could only learn optimal deterministic policies. In some environments like poker or rock paper scissors the optimal policy might be stochastic. Also learning stochastic policies might help in the case of state aggregation, function approximation or partially observable environments e.g. example in lecture 18 pdf with corridor with undistinguishable states.
Another important advantage is that with policy parametrization we can choose functional forms of the policy based on the prior knowledge we have of the environment. Also evaluating the policy directly may be simpler then trying to estimate the states' values.

Some other pros of policy-based approaches compared to strictly value-based ones are:
- Better convergence properties (intuitively: smooth changes in action probabilities instead of jumps like in $\varepsilon$-greedy approaches due to the max operation)
- Effective in high-dimensional/continuous action spaces
- Stochastic OPTIMAL policies can be learned (no max involved), non-optimal stochastic policies could also be learned by strictly value-based (e.g. $\varepsilon$-soft approaches) 
While some cons are:
- Convergence to local optima (usually) and not global optimum
- Evaluating how good a policy is high variance and inefficient (if no value function is learned)

## Possible functional forms
To parametrize the policy we can choose any functional form, with different representation capacities a possible example is the softmax distribution we already saw in gradient bandits. The preferences can be any representation or function of state and action e.g. a neural net or a linear model.
Softmax:
![[Pasted image 20251204225719.png]]

In the case of continuous action spaces we can use instead a continuous distribution e.g. normal distribution with parametrized mean and possibly variance.
# Policy gradient theorem
## Objective functions
In policy gradient the performance measure of the policy $J(\theta)$ is defined differently depending if we are considering the episodic or continuing case.
For the episodic case: 
$$J(\theta)=v_{\pi_{\theta}}(S_0)$$
where $\pi_\theta$ is the policy determined by the parameters and $v$ is the true value-function (that we don't actually have access to so we'll have to sample).
For the continuing case we can define two different objective functions:
the Average Value objective function:
$$J(\theta)=\sum\limits_{s\in \cal S}\mu(s)v_{\pi_\theta}(s)$$
or the Average Reward per time-step 
$$J(\theta)=\sum\limits_{s\in \cal S}\mu(s)\sum\limits_{a\in\cal{A}(s)}\pi_\theta(a|s)\cal R_s^a$$
where $\mu(s)$ is the probability of being a state for an MDP with a given policy $\pi_\theta$, for ergodic continuing MDPs under fixed policy it's the stationary distribution under $\pi_\theta$.

## Gradient ascent
Since we want to maximize one of these objective functions $J(\theta)$, we can compute the gradient $\nabla J(\theta)$ and use gradient ascent to find a local maximum of the objective function:
![[Pasted image 20251203081256.png]]

To compute the gradient we could use finite differences approaches:
![[Pasted image 20251203081350.png]]
but we would need to compute a partial derivative for all components, this would make it computationally expensive: imagine a neural network, we would need to compute the forward pass n+1 times. The advantage of finite differences is that it can still work with non differentiable policies.
Instead of finite differences we develop an analytical form of the gradient expressed as the gradient of the policy itself.
## Theorem and Monte Carlo update
Now we state a theorem that applies for all these objective functions so it can generalize to both the episodic and continuing cases:
![[Pasted image 20251203080531.png]]
In the episodic case it's proportional (by the average number of steps) while in the continuing case it's an equality.

This expression though is not usable directly in the algorithms as both $\mu(s)$ and $q_\pi$ are unknown. We need to able to obtain samples from experience for which the expected value is equal to this theoretical quantity.

To get this 'sample' version we can apply the following steps to manipulate the expression:
![[Pasted image 20251203230155.png]]
# Reinforce
By using the 'sample' version of the policy gradient theorem we can obtain the following update rule to use with Stochastic Gradient Ascent:
![[Pasted image 20251203230331.png]]
From this expression we can observe that:
1. The update increases the parameter vector in the gradient's direction proportionally to the return $G_t$, makes sense as we want to move the parameter the most in directions where the return is the highest
2. The update is inversely proportional to the action probability: this is to compensate for the fact that actions that are selected often are at 'advantage' and might win out even if they don't actually yield the highest return.

Also the update rule can be rewritten as the score function by using the log-derivative trick:
![[Pasted image 20251203230824.png]]

## REINFORCE without baseline 
From this update rule we can obtain the Monte Carlo policy gradient algorithm called `REINFORCE`:
![[Pasted image 20251203230911.png]]
Between the pseudocode of `REINFORCE` and the update rule derived previously there's an important difference $\gamma^t$ this is because in the code we consider the discounted case while in the derivation we considered the undiscounted case.
## REINFORCE with whitening
As the others MC methods, REINFORCE suffers from high variance which can cause unstable learning and slow convergence. One way to mitigate this problem is to employ whitening meaning we normalize the return of each step by:
![[Pasted image 20251203232534.png]]

## REINFORCE with baseline 
An alternative to whitening consists in include a baseline, similarly to gradient bandits:
![[Pasted image 20251203232628.png]]

A possible baseline $b(S_t)$ is the state value function, computed with one of the methods in value-based RL e.g. MC or TD(0).
![[Pasted image 20251203232741.png]]

In this example we use value function approximation to compute $\hat v(s,w)$, using Monte Carlo both for the value function and for the policy gradient.

In general the baseline will help reduce the variance but it won't change the expectation as long the baseline doesn't depend on the action (proof of why in the book). This allows the policy gradient theorem to still hold even with the baseline.
This means it's guaranteed to converge to a local minimum asymptotically.

---

`REINFORCE` with baseline can be extended to [[Actor-Critic]] methods if we learn a critic and use a bootstrapped estimate of the advantage function.

---







