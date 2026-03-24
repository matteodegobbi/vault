#nlp #ml #dl 
> [!Summary]  
> The idea behind MoE is to only use a subset of the model in the forward pass, depending on which kind of input is being processed. A gating network $G$ selects a small number of “expert” ($E_1,\cdots,E_n$) sub-networks that are most relevant for the given token or data point. This makes the model more computationally efficient, as only a fraction of the total parameters are activated at once, while still benefiting from a very large overall capacity. The idea is that different experts sub-networks will specialize in different skills/domains.
> So the main benefits of using MoE instead of a dense layer are two:
> 1. Computational efficiency
> 2. Specialization 
> MoE models tend to be also more sample efficient then their dense counterparts



---

# Sparse MoE
![[Pasted image 20260323170455.png]]
In Sparse MoEs only the top-k (where k is a hyperparameter) experts are actually used in the weighted sum of the experts, this has the aforementioned advantage that it reduces the computational cost of forward (and by consequence backward) pass. 
Some disadvantages of using Sparse MoEs are training stability, load balancing and communication overhead.
Still Sparse MoE is the version used in modern [[Large Language Models]] because of the computational efficiency.

# Dense MoE

![[Pasted image 20260323170438.png]]

In the Dense version of MoEs all experts are used in the weighted sum, this can solve routing issues and instability of Sparse MoEs but it negates completely the computational efficiency gained by Sparse MoEs as all the experts are activated during each forward pass. This results in a model size and computational cost comparable to a dense model, yet without the specialization benefits.

# MoE in [[Transformers]] and [[Large Language Models]]

In [[Transformers]] and [[Large Language Models]] MoE is an important technique for scaling up model size while maintaining computational efficiency. In these models the MoE approach is used in the feed forward network, 

MoE is used in FFN layers specifically because:
* tokens are processed independently in FFN layers (this is not the case in the attention layers)
* FFN are the most computationally intensive layers so the computational efficiency increase aspect of MoE is more relevant here.
It's simple to implement as it just requires to swap an MLP layer with a gate network and n experts which are n MLP layers.
# Problems with Mixture of Experts
#### Routing collapse
Usually the gate network $G$ and the experts are trained together.
A problem that frequently arises with Mixture of Experts is routing collapse.
Routing collapse is the phenomenon that happens when the gating network $G$ consistently directs all inputs to a single or a few experts, effectively ignoring the rest, this defeats the purpose of using MoE and leads to a highly unbalanced and inefficient system.

There are several methods to try to solve routing collapse, a common one is adding this additional term to the loss, called load balancing term:
![[Pasted image 20260323172345.png]]

The load balancing term encourages the gating network to distribute traffic more evenly across the experts, preventing a single expert from becoming overloaded.

> [!Note]
> There's a reason why we consider both the average routing probability $P_i$ and the actual fraction of samples routed to each expert $f_i$, they might differ substantially due to usage of sparse MoEs which select only the top-k (which can make small changes in $P_i$ have a significant impact on $f_i$ due to the implicit argmax) 

Noisy gating is another alternative to load balancing loss to try to solve routing collapse, we just add some noise to the gate network output to prevent the gating network from becoming overly confident in its decisions, this is a similar idea to [[Dropout]].
#### Memory constraints and expert capacity
For memory constraints it might also be necessary to enforce capacity limits on experts, putting a ceiling on the maximum number of tokens processed by each individual expert sub-network. If a token is processed by an expert beyond this limit, it’s routed to a fallback mechanism, either to another expert or some similar mechanism.

---

