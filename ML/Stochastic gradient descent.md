#ml #dl 
In ERM we want to minimize the true risk, we could think to apply iterative methods like gradient descent, which move the parameters of the model in the direction opposite to the gradient of the objective function.

We have 2 problems in this case:
1. We cannot compute the actual gradient of $L_\cal D$ as $\cal D$ is not known 
2. If the objective function is not convex GD will not reach the empirical risk minimum but likely gets stuck in local minima
Instead we can use SGD as presented later in this note. 
# Gradient descent and sub-gradients

Before analyzing SGD, we look at GD applied to minimization of a convex function $f(w)$.
The gradient, $\nabla f(w)$, represents the direction of the steepest ascent of the function $f$ at a given point $w$,  $\nabla f(w) = \left( \frac{\partial f}{\partial w_1}, \frac{\partial f}{\partial w_2}, ..., \frac{\partial f}{\partial w_n} \right)$.
We start with an initial value of $w$ and update it using the formula: $w_{t+1} = w_t - \eta\nabla f(w_t)$, where $\eta>0$ is the learning rate, a positive scalar that controls the step size.

In the end we can output either the last vector $w_{t+1}$ or the average of all the vectors $\bar{w_t}$ or the best performing (the argmin).
These methods have different theoretical properties, in practice we usually use the last vector.

An upper bound on the error incurred by gradient descent can be derived.

If the function is not-differentiable (e.g. abs or hinge loss) instead we can use sub-gradients and the GD algorithm still works, proof in UML book,

# Stochastic Gradient Descent

SGD approximates the gradient of the objective function by using a single data point (or a small batch of data points) at each iteration, in expectation (since we assume iid samples, the stochastic training sample is chosen uniformly from training set, and gradient is a linear operator) this gives us the true gradient of $L_\cal D$, (or a sub-gradient if non-differentiable).
This avoids the need to calculate the exact gradient of the entire dataset, which is computationally prohibitive for large datasets but works in expectation.

As for GD there are upper bounds on convergence, and it converges to a local minimum.

A version considering regularization, e.g. with $L^2$ regularization, can be developed by taking the gradient of $L_\cal S(w) + \lambda ||w||^2$, where $\lambda$ is the regularization parameter.
