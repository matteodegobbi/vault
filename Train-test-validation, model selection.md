#ml 

In ML with [[Empirical risk minimization]] we split the dataset in:
* Training set: to select hypothesis with lowest empirical risk in class H
* Validation set: model selection, hyperparameter tuning (lr, leaves, regularization coeffs), early stopping
* Test set: evaluating the performance of the final model before deployment
In the context of ERM:
![[Pasted image 20260124000551.png]]

Theory gives us an eps,delta bound on absolute value of true error - test error:
![[Pasted image 20260124001343.png]]
So as expected increasing the test set size increases the accuracy of the estimate of the true error.

---

# Model selection

The validation set is often used for model selection e.g. for choosing among a set of hypothesis classes for example the degree d of the polynomial in polynomial regression.

We can use model selection curves for this purpose when we have discrete set of parameters (like $d\in\mathbb N$ or finite amount of hypotheses classes):
![[Pasted image 20260124001636.png]]

If instead we have to fit some continuous hyperparameter (or more than one) we can use approaches like grid-search:
![[Pasted image 20260124001917.png]]
or we can use other heuristics like greedy or beam search approaches.

