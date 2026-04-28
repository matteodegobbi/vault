#ml #dl 
For Binary classification:
![[Pasted image 20251210091850.png]]

AUC of ROC is a measure of accuracy that combines Recall(TPR) and FPR: 
![[Pasted image 20251210092006.png]]
there are also multiclass generalizations of AUC, and we can also use precision/recall AUC if classes are imbalanced.
![[Pasted image 20260222233150.png]]

---
For Object detection in Computer Vision IoU is a common metric to determine whether a detection is a true or false positive:
![[Pasted image 20251210092056.png]]
The IoU is compared with some threshold t e.g. 0.5 if IoU>t then TP otherwise FP.

Then we can compute a metric like mAP to determine how well the object detection model did.

---
For multi-label classification: one-error or hamming loss is usually used.

If we only care about the top prediction:
![[Pasted image 20251210092327.png]]
If we care about all labels equally:
![[Pasted image 20251210092240.png]]

To detect patterns in error distribution in multilabel classification:
![[Pasted image 20260222232905.png]]

---

For regression one possible metric is RMSE:
![[Pasted image 20260222232819.png]]
or Coefficient of Determination $R^2$ :
$$R^2 = 1 - \frac{\sum_{i=1}^{N} (y_i - \hat{y}_i)^2}  
{\sum_{i=1}^{N} (y_i - \bar{y})^2}$$
---

# Document retrieval and ranking 
In information retrieval we often compute metric on the top-k selected relevant documents, we refer to these metrics as @k, e.g. Precision@k, AP@k etc.

If we say we have $N$ documents and $Q$ queries.

## Single query metrics
We define all these quantities for a single query and then generalize to the whole set of queries by taking the mean across queries.

$R=\#\{\text{all relevant documents\}}$

**Relevance of a document at rank i**
$$
\mathrm{rel}(i) =
\begin{cases}
1 & \text{if the document at rank } i \text{ is relevant} \\
0 & \text{otherwise}
\end{cases}
$$

**Recall@k** 


$$
\mathrm{Recall@k} = \frac{\sum_{i=1}^{k} \mathrm{rel}(i)}{R}
$$
**Precision@k**
$$
\mathrm{Precision@k} = \frac{\sum_{i=1}^{k} \mathrm{rel}(i)}{k}
$$
**AP@k**
$$\text{AP@k}=\frac{1}{R}\sum\limits_{i=1}^k{\text{Precision@i}\cdot \text{rel}(i)}$$
basically we compute a weighted average of precision with weights 1 if the document is relevant or 0 otherwise.
If there are more relevant documents than k (if $R>k$) then AP@k can never reach 1 (some rarer formulations divide by min(R,k) instead of R but BEIR for example uses the formulation above with R as denominator). 

## Metrics across multiple queries

**Mean Average Precision@k**

$$
\mathrm{MAP@k} = \frac{1}{Q} \sum_{q=1}^{Q} \mathrm{AP@k}_q
$$
basically we just take the mean across multiple queries.

The same applied for precision and recall across multiple queries.

---

