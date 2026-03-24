#ml #dl 
> [!abstract] Summary
>  Layer Normalization (LayerNorm) is a technique that normalizes activations across the feature dimension within a single sample (differently from [[Batch normalization]]). It stabilizes training, accelerates convergence, and was used in the original [[Transformers]] architecture.

Layer normalization was invented, like [[Batch normalization]] for making the training of deep networks more stable. 
In deep neural nets activations can:
- Explode, gradients blow up, leading to NaN weights
- Vanish, gradients shrink to zero, learning is very slow or stops 
>[!Note] 
>These problems are referred to as [[Exploding and vanishing gradients]]

[[Batch Normalization]] reduces many of these problems by normalizing across the batch dimension. This works for many architectures but it depends on the batch size, leading to problems in the case of:
- [[Recurrent Neural Networks]] (because of variable sequence lengths across a batch)
- Small batches (very noisy estimates of the batch parameters)
- Online / single-sample inference (don't have access to a batch, needing to use running moving averages of training set batch statistics)
- [[Transformers]] (variable-length sequences, the same problem as RNNS)

Layer Normalization fixes this by normalizing over the feature dimension instead, this makes the normalization independent from the batch size.

---
# Layer norm formulas
Given an input vector $\mathbf{x} \in \mathbb{R}^d$ (the activations at one layer for one sample):

$$\text{LayerNorm}(\mathbf{x}) = \gamma \cdot \frac{\mathbf{x} - \mu}{\sigma + \epsilon} + \beta$$

Where:


| Symbol     | Meaning                                                                         |
| ---------- | ------------------------------------------------------------------------------- |
| $\mu$      | Mean of $\mathbf{x}$: $\mu=\frac{1}{d}\sum_{i=1}^{d} x_i$                       |
| $\sigma$   | Std dev of $\mathbf{x}$: $\sigma=\sqrt{\frac{1}{d}\sum_{i=1}^{d}(x_i - \mu)^2}$ |
| $\epsilon$ | Small constant (e.g. $10^{-5}$) for numerical stability                         |
| $\gamma$   | Learned scale parameter (initialized to 1)                                      |
| $\beta$    | Learned shift parameter (initialized to 0)                                      |

First we normalize the activations to be 0 mean and unit variance and then the network learns a scale parameter $\gamma$ and a shift parameter $\beta$, allowing the network to learn the best location and spread parameters for downstream tasks, this makes so the network doesn't lose representational power when using layer norm (if optimal it can relearn the same parameters as the batch statistics).


---


## Numerical example

Suppose a single token in a transformer has a 4-dimensional hidden state:

$$\mathbf{x} = [2, 4, -1, 3]$$

First we compute mean (computed across the 4 dimensions):$$\mu = \frac{2 + 4 + (-1) + 3}{4} = 2$$

then the standard deviation (again across the 4 dimensions):$$\sigma = \sqrt{\frac{(0)^2 + (2)^2 + (-3)^2 + (1)^2}{4}} = \sqrt{\frac{0+4+9+1}{4}} = \sqrt{3.5} \approx 1.87$$

we normalize: $$\hat{\mathbf{x}} = \left[\frac{0}{1.87},\ \frac{2}{1.87},\ \frac{-3}{1.87},\ \frac{1}{1.87}\right] \approx [0,\ 1.07,\ -1.60,\ 0.53]$$

 Scale and shift (using learned parameters, $\gamma=1, \beta=0$ at init): $$\text{output} \approx [0,\ 1.07,\ -1.60,\ 0.53]$$
> [!Warning] 
> This numerical example works for transformer embeddings and other similar features which are vectors, in the case of higher order tensors, like in CNN the behavior is different, to get a complete comparison when considering \[B,C,W,H\] tensors look at the note [[Comparison of normalization layers]] 

> [!tip] Note 
> Usually
> - for vision CNNs use prefer Batch Norm (large batches, spatial data)
> - for NLP / Transformers / RNNs, use Layer Norm or [[RMSNorm]]

---

# Improved versions
From the [[Transformers]] note:
![[Transformers#Pre-Norm vs Post-Norm]]

> [!warning] Pre-LN is now the default convention (used in GPT-2, GPT-3, LLaMA, etc.) because it provides more stable gradient flow during deep training, though it can slightly reduce final model quality compared to well-tuned Post-Norm

Also in modern LLMs (Llama, Mistral) often [[RMSNorm]] is used instead of LayerNorm

---
An improved version now used more commonly in place of LayerNorm is [[RMSNorm]]:

![[RMSNorm]]


# Why LayerNorm Works

LayerNorm can be understood as projecting activations onto a hypersphere (after centering). This constrains the direction of the activation vector while allowing its magnitude to be re-learned via $\gamma$. This geometric constraint regularizes the representational space and prevents activations from drifting into saturated regions of non-linearities like tanh or sigmoid.
It also helps with the loss landscape* normalized activations produce smoother, better-conditioned loss surfaces, making gradient descent more reliable.
Anyway these normalization techniques are used mainly for empirically determined better stability.


---
# Other Normalizations 
Also other notes that regard normalization techniques similar to LayerNorm are [[Batch normalization]], [[Instance Normalization]],[[Group Normalization]] and their comparison [[Comparison of normalization layers]].