#ml #dl 
Regularization is a set of techniques in machine learning used to prevent overfitting, it tries to reduce the complexity without adding too much bias.

There are several common types of regularization:
* L1 regularization, explained in this note
* L2 regularization, explained in this note
* ElasticNet, combining L1 and L2 at the same time
* [[Dropout]]
* [[Data augmentation]]
* [[Label smoothing]]
* [[Ensembles]]
* Noise Injection 
* [[Early stopping]]

# L1 regularization 
We add a penalty term to the loss which becomes:
$$L(w, y) = \text{Loss}(w, y) + \lambda ||w||_1$$
$\lambda$ is an hyperparameter that controls the strength of the penalty. 
L1 regularization encourages sparsity, making many weights equal 0
# L2 regularization 
We add a penalty term to the loss which becomes:
$$L_{reg}(w, y) = \text{L}(w, y) + \lambda ||w||_2$$
$\lambda$ is an hyperparameter that controls the strength of the penalty. 
L2 is less strong in encouraging sparsity when compared to L1, because of the square greatly reducing the impact of weights with absolute value <1.
L2 causes the training to yield smaller weights, and a smoother decision boundary.

When using SGD L2 regularization is equivalent with weight decay:
the update becomes: $w=w-\eta(\nabla L+ \lambda w)$.

In the case of some optimizers like [[Adam]] using L2 regularization by adding a term to the less doesn't make sense since the penalty would depend on the 1st and 2nd order moments. Instead weight decay is used directly in the version called AdamW, the same goes for many other optimizers.

# ElasticNet

This is just the combination of L1 and L2 regularization. It tries to combine the sparsity of L1 with the small weight and smoothness of L2. 

---

