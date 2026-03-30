#ml #dl 
>[!summary] 
>Mixed Precision training is a technique used to speed up training by using a combination of lower-precision floats and higher-precision floats.
>It uses lower-precision floats for forward pass activations and backward pass gradients while using higher-precision floats for the model parameters and optimizer states.
>The idea is that the lower-precision floats will lead to some noise but it can be tolerated as input data already has noise.
>It speeds up training while not degrading model's performance too much.

Usually for the lower-precision floats either `fp16`  or `bfloat16` are used, the former is more precise but less range (possibly underflow, overflow or NaN) while the latter has the same range as float32 and is generally preferred since it's more stable (less underflow, overflow, NaN issues).

Activations and gradients usually use lower-precision floats while parameters,  optimizer states and numerically sensitive operations use higher-precision floats.

Modern GPUs include specialized hardware units designed to accelerate mixed-precision computations.

---
#### Loss scaling
When using `fp16` instead of `bfloat16` gradients can underflow (round to 0).
A technique called loss scaling is employed to avoid this problem.
1. Multiply the loss by a large scale factor $S$ before backprop --> Gradients are scaled up by $S$, staying within FP16 range
2. Before the optimizer step, divide gradients by $S$ to restore true values
During this process we check for `inf`/`NaN` and if detected we skip the update and reduce $S$

Loss scaling is not needed when using bfloat16 hence why it's usually preferred to fp16.

---
# Torch
In torch mixed precision training is carried out using `torch.cuda.amp`

---

> [!warning] Common mistakes
>
>- Softmax and layer norm in FP16 are numerically unstable, torch promotes these to FP32 inside autocast
>- Loss spikes: If `nan`/`inf` appear repeatedly, the scale factor S collapses and training stalls.

---
# Others 
[[Quantization]] offers similar benefits for inference
Mixed precision is commonly used to train [[Large Language Models]]

---