#ml #dl 

# What Is Cross-Entropy?

>[!summary]
>Cross-entropy measures the difference between:
>
>- The true probability distribution $p$
>- The predicted probability distribution $q$
>
>It is the standard loss function for classification problems.
>$$H(p, q) = - \sum_i p(i) \log q(i)$$
>Where:
> - $p(i)$ = true probability
> - $q(i)$ = predicted probability

> [!warning] Unfortunately it uses the same notation as joint entropy from information theory

Cross-entropy decomposes as:

$$  
H(p, q) = H(p) + KL(p | q)  
$$

Minimizing cross-entropy minimizes KL divergence resulting in maximizing likelihood of the data.

---
In the case of 1-hot labels, meaning only one correct class, the formula simplifies to:

$$  
\text{Loss} = -\log(q_{\text{correct class}})  
$$

Only the predicted probability of the correct class matters.

---
# Binary Cross-Entropy (BCE)

The real label is
$$  
y \in \{0,1\}  
$$

The model outputs probability using [[Activation functions#Sigmoid|sigmoid]] (the probability of class 0 will be 1-p by normalization):

$$  
p = \sigma(z) = \frac{1}{1 + e^{-z}}  
$$
We compute binary cross entropy as:
$$  
\text{BCE} = -\left[y \log(p) + (1-y)\log(1-p)\right]  
$$

If $y = 1$:

$$  
\text{Loss} = -\log(p)  
$$

If $y = 0$:

$$  
\text{Loss} = -\log(1-p)  
$$

Penalizing confident wrong predictions heavily.

---

# Categorical Cross-Entropy (CCE)

Used for multi-class classification (meaning for C mutually exclusive classes).
We have $C$ classes, 1-hot target vector, using [[Activation functions#Softmax|softmax]] as activation.

$$  
\text{CCE} = - \sum_{i=1}^C y_i \log(p_i)  
$$

With 1-hot labels:

$$  
\text{CCE} = -\log(p_{\text{correct class}})  
$$


When softmax is used we first convert logits into probabilities:

$$  
p_i = \frac{e^{z_i}}{\sum_j e^{z_j}}  
$$
then substituting softmax into cross-entropy:

$$  
\text{Loss} = -\log\left(\frac{e^{z_y}}{\sum_j e^{z_j}}\right)  
$$

This simplifies to:

$$  
\text{Loss} = -z_y + \log\left(\sum_j e^{z_j}\right)  
$$

The derivative with respect to logits becomes:

$$  
\frac{\partial L}{\partial z_i} = p_i - y_i  
$$
Gradient = Prediction - Target

>[!tip] Note on PyTorch implementation of Cross-Entropy
>In torch CrossEntropyLoss expects raw logits and applies the softmax internally.
>If labels are scalars class indices, meaning only one class at a time is true, then CrossEntropyLoss is equivalent to applying LogSoftmax + NLL Loss.
>
> The differences between NLLL and CEL appears when we have soft labels, i.e. label smoothing or probabilistic labels (e.g. target is \[0.7,0.1,0.2\]). In this case NLLL cannot be used instead we can use CrossEntropyLoss which will do the usual cross entropy computation (in the case we use this vector target version but with 1-hot encoding then it's equivalent to the class indices but it might be slower to run so if we are in this case the class targets indices is better for performance).

---

# Multi-Label

Multiple classes can be true simultaneously and classes are independent
e.g. There are 4 possible classes A,B,C,D and a specific image belongs to both class A and D.


In this case we cannot use softmax since it enforces:

$$  
\sum_i p_i = 1  
$$
Therefore we use multiple sigmoids + BCE for each class, then we take the sum of BCE losses over all classes:

For each class:

$$  
p_i = \sigma(z_i)  
$$

Apply binary cross-entropy independently per class:

$$  
\text{Loss} = - \sum_i \left[y_i \log(p_i) + (1-y_i)\log(1-p_i)\right]  
$$

---

