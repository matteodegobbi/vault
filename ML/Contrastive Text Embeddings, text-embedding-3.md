#nlp #ml #dl 

>[!summary] 
>Contrastive text embeddings are a type of [[Embedding layer|textual embeddings]] using a specific contrastive training objective. They were introduced in this [paper](https://arxiv.org/abs/2201.10005) and are behind the training strategy of many embedding models like openai's `text-embedding-3-large`.
 ---
# Difference with regular embeddings
Regular [[Embedding layer]]s are single layers inside a larger neural net, and are trained using gradients coming from some downstream tasks (e.g. next token prediction for embedding layers in [[Transformers]] architectures).

Contrastive embeddings instead of a single layer employ some larger model, often a transformer-based encoder only architecture (but not necessarily, for example openai likely uses decoder-only models). This encoder is then trained using a contrastive loss function (same idea as [[Siamese Networks]] even though different formulas).
Also instead of learning representations directly from a downstream task, they learn representations by pushing similar texts closer together in the embedding space and dissimilar texts farther apart. 

This type of embeddings is therefore suited for semantic search, clustering and other similar tasks, this is different from the regular [[Embedding layer|embeddings]] trained for some specific downstream task.
For this reason contrastive embeddings are useful for [[Retrieval Augmented Generation]] and similar tasks.

## How to train Contrastive Text Embeddings

>[!warning]
In the following when saying Cross-Entropy we are using the same convention as torch including also the Softmax already in the cross-entropy, meaning the inputs are raw logits.

Given a pair of related items $(x_i,y_i)$ (for example a docstring documenting a function in code and its related piece of code), we pass both items, one at a time, through an encoder only transformer (in the original formulation, in later implementations we use decoder only instead) getting two embeddings $z_i$ and $z_i'$ (the last layer hidden-state corresponding to the `[CLS]` token is often used as the embedding in encoder only models while the one corresponding to `[EOS]` is used in decoder only models).

Then we compute their cosine similarity: $\text{sim}( z_i, z_i')=\frac{z_i \cdot z_i'}{\|z_i\| \|z_i'\|}$
(or more often a generalized version $\text{sim}( z_i, z_i')/\tau$ with $\tau$ a temperature hyperparameter)

Then the InfoNCE loss is used for training:
$$  
\mathcal{L} = \frac{1}{N} \sum_{i=1}^{N}  
\left(  
\mathcal{L}_i^{(x \to y)} + \mathcal{L}_i^{(y \to x)}  
\right)  
$$
where $N$ is the number of samples in the batch and $\mathcal{L}_i^{(x \to y)}$ is the cross-entropy loss between the embedding of input $x$ and the embedding of its corresponding output $y$, and $\mathcal{L}_i^{(y \to x)}$ is the cross-entropy loss between the embedding of output $y$ and the embedding of its corresponding input $x$.

$$  
\mathcal{L}_i^{(x \to y)} =

- \log  
    \frac{  
    \exp(\text{sim}(z_i, z'_i)/\tau)  
    }{  
    \sum_{j=1}^{N} \exp(\text{sim}(z_i, z'_j)/\tau)  
    }  
    $$

$$  
\mathcal{L}_i^{(y \to x)} =

- \log  
    \frac{  
    \exp(\text{sim}(z_i, z'_i)/\tau)  
    }{  
    \sum_{j=1}^{N} \exp(\text{sim}(z_j, z'_i)/\tau)  
    }  
    $$
Basically if we see the logits as an $N\times N$ matrix with elements $a _{ij}=\text{sim}(z_i,z_j')/\tau$ then:
- $\mathcal{L}_i^{(x \to y)}$ is the row-wise cross-entropy loss with target i
-  $\mathcal{L}_i^{(y \to x)}$ is the column-wise cross-entropy loss with target i 
then $\cal L$ aggregates for all $N$ samples in the batch.


>[!note] 
 If using an encoder only transformer we use bi-directional attention like in [[BERT]] to get context from all tokens and not just from previous ones
#### Why use both the “x to y” and “y to x” losses?

The reason is we want the learned embeddings to be mutually discriminative, meaning that for example we don't have multiple docstring embeddings collapsing to the same piece of code and vice-versa. This symmetry is good for retrieval tasks where we may want to be able to search bi-directionally, e.g. searching docstring from code and finding code from docstring.

Anyway in some implementations the “y to x” loss is omitted if considering the specific task that part is not important.

---
# OpenAI's text-embedding-3 

`text-embedding-3-small` and `text-embedding-3-large` are two text embedding models by openai often used for tasks like [[Retrieval Augmented Generation]].
The exact model used, datasets and training are not known publicly but they are likely based on contrastive text embeddings, probably including some other  techniques.

Some of the additional techniques that might be used in `text-embedding-3` are:
- pooling layers or similar techniques to get a single vector from the encoder output hidden states if the model used is encoder only (might also use the technique with `[CLS]`'s final hidden state)
- if _more likely_ the model is decoder only, the last layer’s hidden-state is used as the embedding, in this case it's unidirectional attention but at the `[EOS]` last layer hidden-state all previous token have been attended to so it still uses info from all other tokens
- Hard negative mining, in the batch difficult negative examples are selected to make training more effective
- Matryoshka Representation Learning, basically some additional losses are uses on subsets of the embeddings for example on the first 64,128,256 etc. elements of the embedding. This allows for better hierarchical representations and also during inference time choose the size of embeddings based on memory/accuracy trade-offs. It also provides a sort of [[Regularization]].
- `text-embedding-3` vectors are normalized to unit length
---



