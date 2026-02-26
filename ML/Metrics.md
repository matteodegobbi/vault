#dl 
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
