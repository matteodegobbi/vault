#cv 
#unfinished
Subdivide an image into n regions:
![[Pasted image 20240407112858.png]]

Two main criteria:
* Similarity (between pixels in the same region)
* Discontinuity (between pixels in different regions)

Types:
* Segmentation by thresholding (histogram-based)
* Region growing methods
* Watershed transformation
* Clustering-based methods
* Model-based segmentation
* Edge-based methods
* Graph partitioning methods
* Multi-scale segmentation
* Many others…
---
# Segmentation by thresholding
Selecting the right threshold may be trivial or tricky.The threshold is the only parameter in this kind of segmentation.
(This approach can be extended to multiple thresholds/ranges. One segment per range)
![[Pasted image 20240407150326.png]]
Problems arise in noisy images: where would you place a threshold if the modes in histogram overlap?
Problems arise with illumination changes: the same object can have a different color in different areas because of illumination.
Small regions have very limited impact on the histogram.

Thresholding is effective depending on:
* Distance between peaks
* Image noise
* Relative size of the regions
* Illumination properties (similar effect when the reflectance properties of the objects is not uniform)

Can we make this process of choosing a threshold automatic?

## Otsu optimal threshold

A global thresholding method based on the histogram:
- Assumes that two classes are created by thresholding
- Finds the optimal threshold
- Maximizes inter-class (between-class) variance (A measure of the difference between the two classes)
- Minimize intra-class variance

We compute the normalized histogram:
![[Pasted image 20240407150958.png]]

Set a threshold T(k)=k
It divides the image into two classes:
- Below threshold – class C1
- Above threshold – class C2
![[Pasted image 20240407151107.png]]
![[Pasted image 20240407151151.png]]

the latter is the cumulative mean up to level k normalized over the whole image
What if we want to refer such cumulative mean to C1?
We can further normalize to the number of pixels in C1 i.e. $P_{1}(k)$:
![[Pasted image 20240407151316.png]]

The difference between $m_{1}(k)$ and $m(k)$ is linked to:
- The mean intensity values is referred to the pixels in C1
- The cumulative mean is referred to all the pixels in the image
![[Pasted image 20240407151430.png]]

### The actual Otsu algorithm
Before proceeding, observe that:
$P_{1} + P_{2} = 1$ and $P_{1}m_{1}+P_{2}m_{2}=m_{g}$
![[Pasted image 20240407151751.png]]
![[Pasted image 20240407151819.png]]

$\sigma^{2}_{B} = P_{1}(m_{1}-m_{G})^{2}+P_{2}(m_{2}-m_{G})^{2}=$
$=P_{1}(m_{1}^{2}-2m_{1}m_{G}+m_{G}^{2})+P_{2}(m_{2}^{2}-2m_{2}m_{G}+m_{G}^{2})=$
$=m_{G}^{2}-2m_{G}(P_{1}m_{1}+P_{2}m_{2})+P_{1}m_{1}^{2}+P_{2}m_{2}^{2}=$
$=-m_{G}^{2}+P_{1}m_{1}^{2}+P_{2}m_{2}^{2}=$
$=-P_{1}^{2}m_{1}^{2}-P_{2}^{2}m_{2}^{2}-2P_{1}P_{2}m_{1}m_{2}+P_{1}m_{1}^{2}+P_{2}m_{2}^{2}=$
$=m_{1}^{2}(P_{1}-P_{1}^{2})+m_{2}^{2}(P_{2}-P_{2}^{2})-2P_{1}P_{2}m_{1}m_{2}=$
$=P_{1}P_{2}(m_{1}^{2}-m_{2}^{2}-2m_{1}m_{2})=$
$=P_{1}P_{2}(m_{1}-m_{2})^{2} \ \  \square$

And then we can find a better formulation for efficiency:
$\sigma^{2}_{B} = P_{1}P_{2}(m_{1}-m_{2})^{2}=\frac{(P_{1}P_{2}m_{1}-P_{1}P_{2}m_{2})^{2}}{P_{1}P_{2}}$
$=\frac{(P_{2}m-P_{1}(m_{G}-m))^{2}}{P_{1}P_{2}}=$
$=\frac{(m-P_{1}m_{G})^{2}}{P_{1}P_{2}}\ \ \square$
![[Pasted image 20240407151841.png]]
![[Pasted image 20240407151858.png]]
![[Pasted image 20240407151918.png]]

### Extending Otsu's method
* Smoothing can help Otsu's method by removing noise and making finding the optimal threshold easier.
* The Otsu's method can be combined with other techniques
	* E.g.: edge detection: Compute the histogram and the threshold on the edge image (or combination of edge with the original image) apply the threshold to the original image.
* The Otsu's method can be generalized to:
	* Non-global thresholding: Process different regions of the image using different thresholds (divide the original image in multiple sub images and apply Otsu to each one)
	* Multiple categories
For multiple categories we find multiple tresholds:
![[Pasted image 20240407152309.png]]
![[Pasted image 20240407152322.png]]