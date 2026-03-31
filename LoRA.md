#ml #dl 

> [!abstract] Summary 
> LoRA (Low Rank Adaptation) is a parameter-efficient fine-tuning technique that freezes pre-trained model weights and trains low-rank decomposition matrices into each layer of the model's architecture (or only some layers). Compared to full finetuning it reduces the number of trainable parameters while maintaining model quality, it limits catastrophic forgetting.

---

In LoRA's: weight updates during adaptation (fine-tunign) have a low intrinsic rank.

Instead of learning a full weight update matrix $\Delta W \in \mathbb{R}^{d \times k}$, LoRA decomposes it:
$$\Delta W = BA$$
Where:
- $B \in \mathbb{R}^{d \times r}$
- $A \in \mathbb{R}^{r \times k}$
- $r \ll \min(d, k)$, the rank, a small integer (e.g. 4, 8, 16)

Only $A$ and $B$ are trained. The original weights $W_0$ are frozen.

During inference, the modified layer computes:

$$h = W_0 x + \Delta W x = W_0 x + BA x$$

- At initialization: $A$ is random Gaussian, $B$ is zero this allows the fine-tuning to start with $\Delta W = 0$ meaning the same as the base model

The output is scaled by $\frac{\alpha}{r}$ where $\alpha$ is a constant hyperparameter. This scaling is done in order to keep the same magnitude independently of the rank $r$. The hyperparameter $\alpha$ just weighs how much the LoRA adaptation contributes to the output.

Also dropout can be used in LoRA for regularization.
# LoRA in [[Transformers]]

In [[Transformers]] the original LoRA paper applied the adaptation to the attention layers, specifically the query and value projection matrices within the multi-head attention modules.
Nowadays LoRA is often applied to both attention and feed-forward layers, with some papers showing how LoRA is more beneficial when applied to feed-forward layers, particularly in larger models.

---
# LoRA in practice, pros and cons

>[!tip]  Practical tips
>* often when using LoRA you should use a higher learning rate
>* when using LoRA using large batch sizes is not advised (empirical knowledge no theory for now)

Some pros of LoRA:
- No inference latency $BA$ can be merged into $W_0$ at inference time by computing $W = W_0 + \frac{\alpha}{r}BA$
- Modularity: easy to swap different LoRA adapters for different tasks on the same base model. Also we only have to store the base models and the very small LoRA weights leading to less storage use
- Composable: Multiple LoRA adapters can be merged or switched
- Memory efficiency: Only $A$ and $B$ need gradients

Some cons are:
- Sensitivity to choice of $r$
- Limited expressiveness compared to full fine-tuning

---

# QLoRA
QLoRA is a more advanced version of LoRA which uses [[Quantization]] of the base model to allow LoRA to be applied to large models with much smaller memory requirements.
It quantizes the base model to 4-bit NormalFloat (NF4) a format that splits the space into quantiles of a normal distribution making it more precise for normally distributed numbers compared to standard 4 bit quantization (INT4) which would work better for uniform distributions.
Then it adds LoRA adapters in 16-bit (higher precision for the LoRA than base model).

----

