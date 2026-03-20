#ml #dl 

Batch Normalization is a technique that normalizes the inputs to a layer across the mini-batch during training. It is applied before (or after) an activation function, typically inside each layer of a neural network.

Given a mini-batch $\cal{B} = \{x_1, x_2, \ldots, x_m\}$ of activations for a single feature:

First we compute batch mean:

$$\mu_\mathcal{B} = \frac{1}{m} \sum_{i=1}^{m} x_i$$

Then we compute batch variance:

$$\sigma^2_\mathcal{B} = \frac{1}{m} \sum_{i=1}^{m} (x_i - \mu_\mathcal{B})^2$$

Then we normalize all the activations of that feature:

$$\hat{x}_i = \frac{x_i - \mu_\mathcal{B}}{\sqrt{\sigma^2_\mathcal{B} + \epsilon}}$$

where $\epsilon$ is a small constant (e.g. $10^{-8}$) for numerical stability.

Lastly we scale and shift using learnable parameters:

$$y_i = \gamma \hat{x}_i + \beta$$

N.B BatchNorm normalizes over B, H, W but keeps separate scale $\gamma$ and shift $\beta$ parameters for each feature map (other normalization techniques have different behavior in this dimension).

## At Inference Time

During inference there is no batch, so running statistics accumulated during training are used:

$$\hat{x} = \frac{x - \bar \mu}{\sqrt{\bar\sigma^2 + \epsilon}}$$

where $\bar\mu$ and $\bar\sigma^2$ are exponential moving averages computed over training batches.

---

## Why Does It Work? (Current Understanding)

The original paper claimed BatchNorm reduces internal covariate shift: the distribution of each layer's inputs shifts during training as parameters in previous layers change, forcing each layer to continuously re-adapt. This explanation is now mostly shown to be wrong.

#### 1. Smoothing the Loss Landscape
Now it's believed that BatchNorm smooths the optimization landscape. It makes the loss function more Lipschitz-continuous allowing for:
- Larger learning rates without divergence
- More predictable gradient directions
- Faster convergence

#### 2. Implicit Regularization
The randomness introduced by the mini-batch sampling adds noise, a similar idea to [[Dropout]]: this is why often dropout is avoided when using BatchNorm.
By consequence bigger batches with BatchNorm introduces less noise meaning less regularization.
## Practical Notes

Usually BatchNorm is placed before activation. 
Usually bias is not used in the layer preceding BatchNorm as the translation parameter of BatchNorm has already the same effect, making bias redundant.

It often breaks down with very small batch sizes (batch size 1–4), due to too much noise, instead it may be useful to use [[Layer Normalization]] instead.
Problematic for recurrent networks, since activations vary across time steps.
Each feature map is normalized independently, it doesn't do whitening (it would require the whole covariance matrix).

# Other normalizations
When using [[Recurrent Neural Networks|RNNs]] or [[Transformers]] we used instead [[Layer Normalization]], since sequences have different lengths and for example in RNNs the same weights are used at different time-steps the batch statistics are noisy.

Also [[Instance Normalization]] and [[Group Normalization]] are used in different cases.



---

