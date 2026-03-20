#ml #dl 

Originally Attention was introduced to solve the information bottleneck problem in encoder-decoder [[Recurrent Neural Networks#Attention in RNNs|RNNs]], this note examines the most common version of attention: scaled dot-product attention. Also this note explains [[#Generalized attention]] which generalizes both RNN Bahdanau attention and [[Transformers]] scaled dot-product attention.

More information about [[Transformers]] and it's usage of attention is in the related note (including masked attention, self attention and cross attention).


Attention allows a model to dynamically focus on different parts of the input when producing each element of the output. 

Attention is defined over:
- Query (Q), what we are currently looking for (e.g., the current decoder state). Q has shape $(n, d_k)$, where $n$ is the number of queries
- Keys (K), some information "indexing" the values (e.g., encoder hidden states). K has shape $(m, d_k)$, where $m$ is the number of key-value pairs
- Values (V), the content to be aggregated (sometimes like in RNN V is equal to K). V has shape $(m, d_v)$
N.B. $m$ and $n$ could be different as in [[Transformers#Cross Attention]] or equal as in [[Transformers#Self Attention]]

## Scaled Dot-Product Attention

This is the version of attention used in [[Transformers]]

$$\text{Attention}(Q, K, V) = \text{softmax}\!\left(\frac{QK^\top}{\sqrt{d_k}}\right)V$$

Where:
- $d_k$ is the dimensionality of the keys (the $\sqrt{d_k}$ factor prevents very large dot products, which can cause numerical instability and more commonly vanishing gradients due to the Softmax having an almost 1-hot output for large magnitudes)
- The Softmax produces a probability distribution over input positions (the attention weights)
- The output is a weighted combination of the values


$Q$ and $K$ must share the same inner dimension $d_k$ (so the dot product is valid), while $V$ can have a different dimension $d_v$.
The output dimensionality is determined by $d_v$, not $d_k$.

# Generalized attention
The attention score $e_{ij}$ measures the compatibility between query $i$ and key $j$. Common scoring functions include:

| Name                | Formula                                     |
| ------------------- | ------------------------------------------- |
| Dot-product         | $e_{ij} = q_i \cdot k_j$                    |
| Scaled dot-product  | $e_{ij} = \frac{q_i \cdot k_j}{\sqrt{d_k}}$ |
| Additive (Bahdanau) | $e_{ij} = v^\top \tanh(W_1 q_i + W_2 k_j)$  |

Scores are then normalized with Softmax to yield the attention weights $\alpha_{ij}$ which are used to weigh the values in the weighted combination.

## Complexity


For a sequence of length $n$ and for the case where $d\triangleq d_k=d_v$ standard attention has $O(n^2 \cdot d)$ time and memory complexity $O(n^2)$, which becomes a bottleneck for very long sequences (If multiple head are used change the definition to $d\triangleq h \cdot d_k$). Efficient variants (Sparse Attention, Linformer, Flash Attention) address this.
This is still faster than RNNs even though RNNs are linear in sequence length because of the higher degree of parallelization.


---




---


---

### Multi-Head Attention
