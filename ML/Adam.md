#ml #dl

It's the most commonly used optimizer. It combines concepts both from momentum and from RMSProp.

The idea is that it adapts the learning rate for each parameter individually (differently from SGD which uses a global lr for all parameters).


Hyperparameters are: 

$$\begin{align}\alpha &\equiv \text{ learning rate}\\ \beta_1 &\equiv \text{ first moment decay}\\ \beta_2 &\equiv \text{ second moment decay}\\ \epsilon &\equiv \text{ small number to avoid overflow}\end{align}$$


We fist compute the gradient for all parameters: 

$$g_t = \nabla_\theta \mathcal{L}(\theta_t)$$

First moment (mean)

$$m_t = \beta_1 m_{t-1} + (1 - \beta_1) g_t$$

Second moment (uncentered variance)

$$v_t = \beta_2 v_{t-1} + (1 - \beta_2) g_t^2$$
The first and second moment are EMAs respectively of the gradient and the square of the gradient.

Bias correction, to debias from the initial value $m_0=0,v_0=0$

$$\hat{m}_t = \frac{m_t}{1 - \beta_1^t} \qquad \hat{v}_t = \frac{v_t}{1 - \beta_2^t}$$

Parameter update:

$$\theta_{t+1} = \theta_t - \frac{\alpha}{\sqrt{\hat{v}_t} + \epsilon} \hat{m}_t$$


Typical default values are:

$$\alpha = 0.001, \quad \beta_1 = 0.9, \quad \beta_2 = 0.999, \quad \epsilon = 10^{-8}$$

The moments are per-parameter, meaning both $m_t$ and $v_t$ are in the same number as $\theta$, this can use a considerable amount of memory since it adds memory overhead approximately equal to 2 times the number of parameters.

Some other optimizers like Adafactor were invented to reduce memory consumption of Adam.

At each step, Adam doesn't just look at the current gradient. It maintains a memory of the past:

- $m_t$​ is a smoothed estimate of "what direction has this parameter been pushed lately"
- $v_t$​ is a smoothed estimate of "how large have this parameter's gradients been lately"

By dividing $\hat{m}_t$​ by $\sqrt{\hat{v}^t}+\varepsilon$, we determine:

- From the numerator which direction to step and roughly how hard
- From the denominator how active this parameter has been historically

If a parameter has been getting large gradients consistently, the denominator is large and the step gets shrunk as it's already learning fast. If a parameter has been getting tiny gradients, the denominator is small and the step is amplified, this parameter has been neglected so we amplify it's gradient.
Also if the gradients changes sign often then the numerator is going to be small while the denominator is EMA of squares so it cannot go lower than 0.

The EMAs are to make current gradients matter more and older gradients matter less and less as time goes on.

Adam also has the big advantage to not need much tuning, on the other side in specific tasks SGD+Momentum with tuning of hyperparameters can outperform it. 

---

# AdamW

For normal Adam adding regularization directly to the loss would mean that the adaptive part of Adam would interfere with the regularization, instead with AdamW we use weight decay directly.
The weight decay is applied directly to the parameters rather than via the gradient. avoiding the interference of regularization with the moments:

$$\theta_{t+1} = \theta_t - \frac{\alpha}{\sqrt{\hat{v}_t} + \epsilon} \hat{m}_t - \alpha \lambda \theta_t$$

where $\lambda$ is the weight decay coefficient.

