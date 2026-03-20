#ml #dl 
Siamese networks (SNNs) consist of two identical subnetworks which are fed two different inputs, by identical it is meant that they also share parameters.
SNNs don't directly learn to classify the inputs, instead they learn an embedding function $f(x):\cal X \rightarrow\mathbb R^d$,  then the two vectors are compared with some distance function to decide whether they belong to the same class or not.
The loss will include as ground truth not the labels of the two inputs but whether the two inputs belong to the same class or not.
We have two types of formulations in which Siamese nets are used: with contrastive loss and with triplet loss.

![[Pasted image 20260311111501.png]]

We have several distance functions that can be used to compare the embeddings $u$ and $v$:
* Cosine Similarity: $\text{sim} (u, v) = \frac{u \cdot v}{\|u\| \|v\|}$, angle between the vectors (we actually use the distance so 1-sim)
* Euclidean Distance: $d(u, v) = \|u - v\|_2$, often we actually use the squared Euclidean distance to avoid square roots
* Manhattan Distance: $d(u, v) = \sum_{i=1}^d |u_i - v_i|$ 

N.B. In practice we don't have 2 copies of the network, we only use one network and do one pass for each input accumulating the gradients, when we call `backward()` the weights are updated for both inputs' forward passes. 

Also it might make more sense to normalize embeddings before computing the distance to project them into a unit hypersphere, easier for visualization and cosine distance becomes equal to just dot product.
# Losses
The loss function in a Siamese network is designed to encourage similar embeddings for inputs belonging to the same class and dissimilar embeddings for inputs belonging to different classes.

#### In the case of Contrastive loss we have:
$$  
L_\text{contr} = y D(x_1, x_2)^2 + (1 - y)\max(0, \xi - D(x_1, x_2))^2  
$$
with $y=1$ if $x_1$ and $x_2$ belong to the same class, and $y = 0$ if they belong to different classes.
The first term, $y D(x_1, x_2)^2$ makes embeddings of the same class closer together, while the second term, $(1 - y)\max(0, \xi - D(x_1, x_2))^2$, makes embeddings of different classes move further apart.

$\xi$ is a hyperparameter that controls the margin between dissimilar embeddings.  It represents the minimum distance we want to enforce between embeddings of different classes. If $D(x_1, x_2)$ is less than $\xi$, the loss term $(1 - y)\max(0, \xi - D(x_1, x_2))^2$ becomes greater than 0. This makes is it so the network is trained to push away the embeddings of different classes but it makes it so the network cannot improve its loss by pushing away embeddings indefinitely when they are already out of the margin.


#### For Triplet Loss

We define:
- $x_a$ = anchor, feature vector of baseline input    
- $x_p$ = positive, feature vector of same class as the anchor 
- $x_n$ = negative, feature vector of a different class than the anchor

$$  
L_\text{triplet} = \max\left\{0, D(x_a, x_p) - D(x_a, x_n) + \xi \right\}  
$$
The purpose of this loss is to learn a more discriminative embedding space. The goal is to minimize the distance between the anchor $x_a$ and the positive example $x_p$ while simultaneously maximizing (again like in contrastive loss, up to margin $\xi$) the distance between the anchor and the negative example $x_n$.

The choice of the triplets can be sampled in smart ways to avoid easy examples, we can use the hard negative mining strategy to choose triplets where the negative example is the closest one to the anchor.

# Uses of SNNs

- Metric learning: Learn an embedding space where similar samples are close together and dissimilar ones are far apart (distance represents similarity), useful for clustering, dimensionality reduction, retrieval.
- One-shot learning: Recognize a new class from only one (or very few) examples by comparing it to known samples using the learned similarity metric
* Anomaly detection
* Verification (e.g. fingerprint) 

The backbone architecture of SNNs can be any neural net architecture: CNNs, Transformers, RNNs etc

---

