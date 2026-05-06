#nlp #ml #dl

> [!summary] 
> SPLADE (SParse Lexical AnD Expansion model) is a neural retrieval model that produces sparse representations of queries and documents. Unlike dense retrieval methods, SPLADE outputs sparse vectors in the vocabulary space, similarly to [[BM25]]. But differently from other sparse vector embedders it uses neural networks (namely [[BERT]] with a MLM head) to obtain the vectors.

---

# Why introduce SPLADE over [[BM25]] and dense retrieval

**BM25 lacks semantic understanding**
[[BM25]] uses exact term matches between the query and document. If a query uses `automobile` and a document uses `car`, BM25 will assign zero score to that term despite the clear semantic relationship. This problem is called  vocabulary mismatch.

**Dense models lack interpretability** 
Dense vectors cannot be easily interpreted, they store information in the vector space in smaller but dense vectors.

SPLADE yields sparse vectors in vocabulary space (like BM25), but uses a transformer encoder ([[BERT]]) to achieve term expansion and weighting (like a dense model) which helps with semantic understanding. 

---

# SPLADE's core idea

For text $t$ (either a query or a document), SPLADE computes a sparse weight vector $\mathbf{w} \in \mathbb{R}^{|V|}$ over the full vocabulary $V$ using a [[BERT]] with an MLM head:

$$w_j = \log\left(1 + \text{ReLU}\left(\sum_{i} \mathbf{H}_{ij}\right)\right)$$

Where:

| Symbol               | Meaning                                                                 |
| -------------------- | ----------------------------------------------------------------------- |
| $\mathbf{H}_{ij}$    | Logit of vocabulary term $j$ at token position $i$ from the MLM head    |
| $\text{ReLU}(\cdot)$ | Ensures non-negative weights (zeroes out irrelevant terms)              |
| $\log(1 + \cdot)$    | Applies a saturation effect, analogous to the TF saturation in [[BM25]] |

The sum over positions $i$ allows any position in the input to "vote" for any vocabulary term, enabling **term expansion**: the model can activate vocabulary terms not actually present in the input.

The final retrieval score between query $q$ and document $d$ is the dot product of their sparse vectors:

$$\text{score}(q, d) = \mathbf{w}_q \cdot \mathbf{w}_d = \sum_{j \in V} w_j^{(q)} \cdot w_j^{(d)}$$

(computed efficiently with inverted index as they are sparse vectors)

---

# Sparsity regularisation

Without explicit constraints, the MLM logits would activate many vocabulary terms, producing dense vectors that lose the efficiency benefits of sparse retrieval. SPLADE therefore adds a **FLOPS regularisation** term to the training loss to encourage sparsity:

$$\mathcal{L}_{\text{FLOPS}} = \sum_{j \in V} \left(\frac{1}{N}\sum_{i=1}^{N} w_j^{(i)}\right)^2$$

This penalises terms that are consistently activated across many inputs in a batch, pushing the model to rely on fewer, more discriminative vocabulary entries. The trade-off between retrieval quality and sparsity is controlled by a regularisation coefficient $\lambda$.

---

# Training

SPLADE is trained with a contrastive objective (like InfoNCE [[Contrastive Text Embeddings, text-embedding-3]]). Given a relevant (query, document) pair and one or more negatives:

$$\mathcal{L} = \mathcal{L}_{\text{rank}} + \lambda_q \mathcal{L}_{\text{FLOPS}}^{(q)} + \lambda_d \mathcal{L}_{\text{FLOPS}}^{(d)}$$

Separate $\lambda$ values are often used for the query and document encoders since their optimal sparsity levels differ (queries are typically shorter and sparser).

---
# Variants
SPLADEv2
SPLADEv3
SPLADE distill cocondenser variant



---

# Usage in conjunction with dense retrieval

Because SPLADE outputs are compatible with inverted indices, they can be used in conjunction with dense ANN retrieval in [[Hybrid search for RAG|hybrid search]] (like with [[Reciprocal Rank Fusion]]). 

---

