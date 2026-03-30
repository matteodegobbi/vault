#ml #dl 
# Introduction 
Transformers were introduced in the context of machine translation and obtained better performance than [[Recurrent Neural Networks]]. The advantages of transformers mainly lie in the fact that it avoids the vanishing gradients that appear in encoder-decoder RNNs (even when using more advanced models like LSTM and when using attention RNNs), this is because it can directly model dependencies between input and output sequences' elements without having to pass through many hidden-states.
In encoder-decoder RNNs the [[Attention]] mechanism was only used between encoder and decoder hidden-states, but in transformers, attention is used everywhere: transformers use self-attention both in the encoder and in the decoder (for the decoder the masked version to enforce causality) and cross-attention between encoder and decoder.
Also transformers are more parallelizable since they are not recurrent and there's no need to process elements of the sequences sequentially.

# Architecture
In the following this note discusses the usage of transformers as introduced in the original _Attention is all you need_ paper, further developments are not described in this note.
The architecture is represented in this diagram:
![[transformers.webp]]

Original transformers are divided in the encoder and decoder (like [[Recurrent Neural Networks#Encoder-Decoder architectures|RNN encoder-decoder architecture]]) 
Before going in detail about what each component does a general picture of transformers is:
* The model takes as input embeddings obtained from a learnable [[Embedding layer]], this happens both the inputs and the outputs (which during training are the target sequence, using [[Teacher Forcing]])
* It adds positional encodings to these embeddings, which are used to convey information to the following layers about the absolute positions of the elements in the sequence
* Then in the encoder:
	- Multi-Head self-attention is performed on input embeddings
	- Add & Norm, meaning a residual connection followed by Layer Normalization
	- Then a feed-forward network is applied, also with a residual connection and Layer Normalization.
	- This whole process is repeated N times to create the encoder stack.
- In the decoder:
	* Masked Multi-Head self-attention is performed on the output embeddings (we use [[Teacher Forcing]]), masked to enforce causality
	*  Add & Norm, the same as the encoder
	* Multi-Head Cross-Attention, determining keys and values projecting the encoder output taken from last block of encoder and the queries obtained from projecting the decoder output coming from Masked self-attention + Add & Norm in the current block.
	* Finally, a feed-forward network is applied, again with a residual connection and Layer Normalization. 
	* This whole process is repeated N times to create the decoder stack.
	* After the last decoder block, a linear layer and a softmax function are applied to produce a probability distribution over the vocabulary, which is then used to predict the next token in the sequence (during inference this token will be used as the next input of the decoder auto-regressively). 
The model is trained to minimize the cross-entropy loss between the predicted probability distribution and the true target token.

## Embeddings

## Positional Embeddings
[[Positional Embeddings]]

## Attention types
Before explaining the 3 different attention types, used in transformers (Self-Attention, Masked Self-Attention, Cross-Attention) this note explains multi-head attention, all attentions mentioned from now on are assumed to be multi-head.
## Multi-Head Attention

This version of attention was introduced in [[Transformers]] to improve model expressiveness without increasing the number of parameters and the cost too much.
Instead of performing a single attention function, Multi-Head Attention projects $Q$, $K$, $V$ into $h$ different learned subspaces and runs attention in parallel across all heads:

$$\text{MultiHead}(Q, K, V) = \text{Concat}(\text{head}_1, \ldots, \text{head}_h) W^O$$

$$\text{head}_i = \text{Attention}(Q W_i^Q, K W_i^K, V W_i^V)$$
After performing the attention on all heads and concatenating back the result we project the result to mix information across heads using weights $W^O$, the dimension stays  the same after this projection if $d_v=d_k=d_\text{model}/h$ as in the original transformer.

Projection matrices per head $i$:

| Matrix  | Shape                             | Role                                          |
| ------- | --------------------------------- | --------------------------------------------- |
| $W_i^Q$ | $(d_{\text{model}}, d_k)$         | projects queries into head $i$ subspace       |
| $W_i^K$ | $(d_{\text{model}}, d_k)$         | projects keys into head $i$ subspace          |
| $W_i^V$ | $(d_{\text{model}}, d_v)$         | projects values into head $i$ subspace        |
| $W^O$   | $(h \cdot d_v, d_{\text{model}})$ | projects concatenated heads back to model dim |

Shapes through the full computation:

| Expression                                            | Shape                     | Meaning                                  |
| ----------------------------------------------------- | ------------------------- | ---------------------------------------- |
| $Q, K, V$ (input)                                     | $(n, d_{\text{model}})$   | input queries/keys/values in model space |
| $QW_i^Q, KW_i^K$                                      | $(n, d_k)$ and $(m, d_k)$ | projected into head $i$ subspace         |
| $VW_i^V$                                              | $(m, d_v)$                | projected values for head $i$            |
| $\text{head}_i$                                       | $(n, d_v)$                | output of single-head attention          |
| $\text{Concat}(\text{head}_1, \ldots, \text{head}_h)$ | $(n, h \cdot d_v)$        | all heads concatenated                   |
| Final output                                          | $(n, d_{\text{model}})$   | after projection by $W^O$                |

In the original Transformer $h = 8$ heads and $d_k = d_v = d_{\text{model}} / h$, so the per-head dimension is reduced to keep the total compute comparable to single-head attention with the full $d_{\text{model}}$.

The reason for having multiple heads is that each head can learn to attend to different types of relationships (e.g., syntactic vs semantic, local vs long-range) simultaneously, rather than collapsing everything into a single attention distribution, the idea is similar to employing different feature maps in CNNs.

### Self Attention

Self-Attention is carried in the encoder out between embeddings of tokens  in the input sequence (and their transformed representation in blocks after the first one).
This is a new introduction wrt [[Recurrent Neural Networks#Encoder-Decoder architectures|encoder-decoder RNN architectures]] and it's useful to allow the model to incorporate data relating to other tokens in the same sequence. For example in the sentence “The animal didn’t cross the street because it was too tired”, self-attention allows the model to understand the relationship between “animal” and “it”, recognizing that “it” refers to the animal and not the street. 
### Masked Self Attention
Masked Self-Attention is performed in the decoder to enforce causality, preventing the model from using future tokens to predict the current one, this is done because inference is auto-regressive so we don't have the target sequence available. Even if during training we have the target sequence available (using Teacher Forcing), we have to train the model to be causal as during inference we cannot use [[Teacher Forcing]].

To achieve this masked self-attention it's sufficient to substitute the attention scores for future tokens with a very large negative value, after taking the softmax this will lead to the attention weights being 0 for those tokens (numerator $e^{-\infty}=0$ in the Softmax).
![[Pasted image 20260318161255.png]]

The reason why we do this instead of multiplying the attention weights directly by 0 is to preserve normalization (rows of attention weight matrix sum to 1: the attention matrix (after softmax) is a row-stochastic matrix as index of queries is the row while index of keys is the colum).
### Cross Attention

Cross-Attention is performed in the decoder and allows the model to attend to the encoder representations while generating the target sequence.

Unlike self-attention, where queries, keys, and values are all obtained from the same sequence through learned projections, in cross-attention::

- The decoder hidden states are projected into queries (Q)
    
- The encoder output representations (in the last encoder stage) are projected into keys K and values V using projection matrices learned in the decoder stage (each decoder stage will use the same encoder contextual embeddings put will use different learned projection matrices, learning different transformations of the same encoder last hidden-state)
    

So the equations are:
- $Q = H_{\text{decoder}} W_Q$
- $K = H_{\text{encoder}} W_K$
- $V = H_{\text{encoder}} W_V$
(Actually these equations are for one head only, they can easily be generalized for multi-head attention)

This type of attention in transformers is the most similar to the attention mechanism in [[Recurrent Neural Networks#Encoder-Decoder architectures|encoder-decoder RNN architectures]], but instead of computing a single context vector per step, cross-attention computes a full attention distribution over all encoder tokens at each decoding step.

---
## Position wise Feed-Forward Networks
This layer consists of two fully connected feed-forward networks. It is applied independently to all elements of the sequence, meaning that differently from the attention part of transformer the position wise FFN don't mix information between different elements of the sequences.


For each position i:  
$\text{FFN}(x_i) = \max(0, x_i W_1 + b_1) W_2 + b_2$
In this formula I used [[Activation functions#ReLU (Rectified Linear Unit)]] but newer transformers use other activation functions like [[Activation functions#Swish / SiLU]] or [[Activation functions#GELU (Gaussian Error Linear Unit)]].
Summarizing in the position wise FFN layer:
* The same parameters are applied to every position independently
* There is no interaction between different tokens in this step
* It increases the model’s capacity by introducing non-linearity and feature transformation after attention. Usually the first transformation projects the input to a higher dimensional space (in the original transformer it’s 4 times the dimension of the input), and the second transformation projects it back to the original dimension. This allows the network to learn more complex representations of the input data.)
    
## Add & Norm

Each sublayer in the Transformer (self-attention, cross-attention, or FFN) is wrapped in an Add & Norm structure, which consists of a residual connection followed by layer normalization.

Given an input (x) and a sublayer transformation $\text{sublayer}(x)$ (which could be either an attention or FFN in this case the distinction doesn't matter), the output is:  
$\text{LayerNorm}(x + \text{sublayer}(x))$ 

### Residual Connection (Add)

The residual connection adds the input x back to the sublayer output. This serves multiple purposes:
- Makes it easier to learn identity mappings in the case no transformation is needed
- Improves gradient flow, especially in deep architectures

This idea comes from residual [[Convolutional neural networks]] and is necessary to train deep transformers.

### Layer Normalization (Norm)

[[Layer Normalization]] is applied after the addition and normalizes the activations across the feature dimension for each token independently. 
This stabilizes training, also in sequence based models like transformers [[Batch normalization]] has the problem of different length sequences in the same batch so [[Layer Normalization]] is a better fit. (An additional benefit is that LayerNorm is easier to parallelize in the case of distributed training it doesn't need communication with other GPUs as it doesn't need info from other sequences in the batch)

### Pre-Norm vs Post-Norm 
In the original Transformer architecture, normalization is applied after the residual connection:  
$\text{LayerNorm}(x + \text{sublayer}(x)) \quad \text{(Post-Norm)}$ 
However, in most modern Transformers the order is changed to:  
$x + \text{sublayer}(\text{LayerNorm}(x)) \quad \text{(Pre-Norm)}$

This modification improves gradient flow during training, especially in deep models since the residual is not modulated by the LayerNorm. 

---
# Training details
## Loss 
The loss used to train transformers is the usual [[Cross Entropy]] 
$\mathcal{L} = - \sum_{t=1}^{T} \log P(y_t \mid y_{<t}, x)$, in this case the form used is valid for 1-hot target distributions, where $y_t$ is the target token at position $t$, $y_{<t}$ are the previous target tokens, and $x$ is the input sequence.
### Regularization

Transformers typically use several forms of regularization to improve generalization:

#### [[Dropout]]
It's applied to: Attention weights, FFN outputs and to Embeddings
#### [[Label Smoothing]]
    
Softens the target distribution by assigning a small probability to incorrect tokens:  
$P_\text{target}' = (1 - \epsilon) P_\text{one-hot} + \epsilon / |V|$

Set $V$ is the vocabulary.

It reduces overconfidence and improves generalization. In the case label smoothing is used we need to use the full [[Cross Entropy]] formula instead of the one shown above which is only valid for 1-hot encoded targets.
![[Pasted image 20260318194755.png]]
N.B. Different notation with $w_t$ the target token.

#### Weight decay
Often also weight decay is used but it's directly incorporated by using [[Adam#AdamW|AdamW]] instead of adding an L2 penalty to the gradient.

---
### Optimizers
Often [[Adam#AdamW|AdamW]] is used in conjunction with some [[Learning Rate Scheduling]], usually involving:
* Warm-up phase: gradually increase LR from 0 to the target value over a few thousand steps
- Decay phase: LR decreases according to inverse square root or cosine schedules
Warm-up + decay helps stabilize training early on and prevents divergence.

Compared to other models the learning rate scheduling is particularly important in transformers to prevent instability

### Gradient Management

Gradient clipping is often used to prevent exploding gradients, especially in very deep or large Transformers (this is the same as the one used in [[Recurrent Neural Networks]]).
Mixed-precision training (FP16) is common for large models to reduce memory usage and speed up training.

### Weight Initialization
Usually uses [[Xavier and Kaiming-He init]] for linear layers to prevent vanishing/exploding gradients (as in [[Exploding and vanishing gradients]]).

### Other things
Other types of attention (sparse, local etc)
[[Flash Attention]]
Temperature 
Relative position encodings
KV-Caches
Scaling attention
