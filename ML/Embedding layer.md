#ml #dl #nlp


> [!abstract] Summary
> An embedding layer is a trainable lookup table that maps discrete, high-dimensional inputs (like word indices) into dense, low-dimensional continuous vector representations (with fixed dimension).

---

Neural networks operate on continuous numbers, but many real-world inputs are discrete and categorical, for example:
- Words in a vocabulary in NLP
- Tokens in a language model

---

A naive solution would be to one-hot encode these discrete inputs. This solution has several problems:
* High dimensionality and sparseness causing inefficiency and increased computational cost
* No similarity between related categories e.g. 'king' and 'queen', which causes OOV problems, no generalization. We want semantic similarity between similar vectors (and vice versa).

Some other solutions were developed like [[Word2Vec,GloVe and FastText|Word2Vec]] or GloVe but while they solve the sparsity and dimensionality problems, and also guarantee semantic structure ('king' and 'queen' will have similar representations), the embeddings give static representations of words, meaning the same word will obtain the same vector representation even in different contexts, for example in the two sentences: "Did you book the hotel?" and "I read that book", the vector representation of “book” is the same.

>[!warning] What we want
>We want to have vector representations that are contextual, meaning that the representation of a word changes based on the context in which it is found, this allows for polysemy. Models like BERT and GPT get this property by using attention between the different embeddings.

---
# How embedding layers work

An embedding uses a matrix $E$ of shape: $E \in \mathbb{R}^{|V| \times d}$
- $|V|$ = vocabulary size
- $d$ = embedding dimension (a hyperparameter)
Given an integer index $i$, the forward pass is:
$$\text{embed}(i) = E[i, :]$$

This is a row lookup, not a matrix multiplication, this makes it extremely efficient.

An important note is that no activation function is needed.

Embeddings are learned end-to-end via backpropagation of the loss used in the downstream task.
>[!note] Note
>This is different from [[Word2Vec,GloVe and FastText]] since they use a proxy training objective to learn fixed word representations which are then froze and given as input to a neural network

For the embedding layer, only the rows corresponding to tokens seen in the current batch receive gradient updates.


> [!tip] Sparse Gradient Updates
> Because only seen tokens get updated per batch, embedding layers are naturally **sparse** in their gradient updates. Frameworks like PyTorch handle this efficiently with sparse optimizers.

# Parameter count 

The dimensionality $d$ of the embedding is a hyperparameter, bigger dimension mean more expressive representations but more parameters and risk of overfitting.

An embedding layer with vocabulary $|V|$ and dimension $d$ has: $|V| \times d\text{ params}$
For GPT-2 small: $50{,}257 \times 768 = 38{,}597{,}376 \approx 38.6\text{M params}$

This is often the largest single layer in a language model, which is why weight tying (sharing the embedding matrix with the output projection but with transposition) is commonly used.

In many language models, the input embedding matrix and the output projection matrix (before softmax) are shared (with transposition):

$$P(\text{next token}) = \text{softmax}(E\cdot h)$$
Same matrix $E$ is used for both lookup and projection. This:
- Halves the parameter count for that component
- Often improves performance (the model must be consistent about word meaning)
This technique is used in: GPT-2, T5, many others

The reason why it makes sense is that:
* In input of the embedding layer i get a one-hot vector $x$ in $\mathbb R^{|V|}$ 
* I compute the embedding $h_{in}=E^T\cdot x$ with $h_{in}$ in $\mathbb R^d$
* I get the output vector of the last decoder stage $h$ in $\mathbb R^d$ 
Then I have that $h$ is a vector in the same space as embeddings, I want to assign probabilities to tokens based on how close their embeddings are to the vector $h$, to do this I can compute $\text{softmax}(E\cdot h)$ where each component $i$ of the logits will be the dot product (a similarity measure in the embedding space) between the embedding of token with index $i$ and the output of the decoder, the softmax just normalizes to obtain a valid probability distribution.

>[!note] Note
>In practice the matrix multiplication is not carried out, we just lookup the row (or column) in the embedding matrix, this is faster and still allows for auto-differentiation

---
# Training from Scratch VS Pre-trained
If we train from scratch: embeddings are randomly initialized and trained with the model, this is best when when we have a large dataset or domain-specific vocabulary
If we use pre-trained embeddings we can:
- Initialize with [[Word2Vec,GloVe and FastText]] vectors (one of these options)
- Then we can either freeze or fine-tune during training, freezing is a sort of regularization, decreasing the overfitting risk but of course freezing may limit model expressiveness

---
#  Practical Considerations

### Padding and `padding_idx`

Sequences of different lengths are padded to the same length. The padding token (usually index `0`) should not contribute to gradients, this is handled by torch with `padding_idx` parameter.

---

