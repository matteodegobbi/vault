#cv #lowlevelprocessing
[[Low, Mid and High level image processing (9)|Low level image processing]].
Local operations:
* Linear and non-linear filters
* The output value depends on the initial values of the pixel + its neighbors
Local operations are defined based on a filter/kernel. The kernel defines a neighborhood and a weight associated with each pixel involved in the computation.
![[Pasted image 20240402143039.png]]
Local operations are performed in the spatial domain of the image. 
Depending on the processing applied to the image the filter can be linear or non-linear:
Several options are available
* Evaluating a correlation/convolution ->Linear filtering
* Calculating the min/max -> Non-linear filtering
* ...
# Correlation/Convolution
The filter is superimposed on each pixel location, evaluation of a weighted average of:
* Pixel value
* Filter weight
![[Pasted image 20240402143644.png]]
Suppose the filter dimensions are 𝑚 × 𝑛
* 𝑚 = 2𝑎 + 1
* 𝑛 = 2𝑏 + 1
Correlation is defined as:
![[Pasted image 20240402143750.png]]
In the CV context, convolution and correlation are often used as synonims but usually, correlation is evaluated.
The filter weights can change the image brightness. Brightness is unchanged if: $\sum\limits_{i}w_{i}=1$, this is obtained by a normalization factor.
# Averaging filter
They evaluate the average over a neighborhood of a pixel. They can be used for smoothing, blurring and restoration.
![[Pasted image 20240402144351.png]]
The size of the filter can be increased. Larger filters: stronger smoothing.

A square filter of size $n\times n$ may be separated in:
* A filter of size $n\times1$
* A filter of size $1\times n$
Separable filters: $w(x,y)\to w_{x}(x)w_{y}(y)$ 
* Can be applied on rows, then columns (or vv)
* O(MN(a+b)) instead of O(MNab) – faster

# Derivative
First order derivative operator
1. Is zero in flat segments
2. Is non-zero on the onset of a step/ramp
3. Is non-zero along ramps
Second order derivative operator
1. Is zero in flat segments
2. Is non-zero on the onset and at the end of a step/ramp
3. Is zero along ramps of constant slope
![[Pasted image 20240402144907.png]]
## 1st order derivative
The derivative operations can be implemented using appropriate filters.
Direct application of the definition or more often different from a direct implementation of the derivative definition but are more stable.
![[Pasted image 20240402145107.png]]
![[Pasted image 20240402144940.png]]
## 2nd order derivative
The Laplacian filter implements the equation:
![[Pasted image 20240402145308.png]]
The filters are:
![[Pasted image 20240402145352.png]]
Left: Laplacian, Right: version of Laplacian that includes diagonal terms
![[Pasted image 20240402145235.png]]
The Laplacian can be used to enhance the transitions in the image. Combination of the image and the Laplacian for sharpening:
![[Pasted image 20240402145529.png]]
# Noise and image restoration
 We can model the acquired image as Ideal image + noise:
 ![[Pasted image 20240402150811.png]]
 The task of removing the noise in an image is often referred to as image restoration:
 * Estimate noise properties
 * Remove noise
![[Pasted image 20240402150903.png]]
![[Pasted image 20240402150939.png]]
# Linear filters
Other than the average and derivative we have other linear filters (often used for image restoration):
Several averaging filters are available:
* Arithmetic mean (and Alpha-trimmed mean which is not linear)
* Geometric mean
* Harmonic mean
	* Dominated by the minimum of its arguments
	* In the general case: harmonic < geometric < arithmetic mean
* Contraharmonic 
![[Pasted image 20240402150250.png]]



# Non-linear filters
Non-linear filters implement non-linear operations.
Non-linear filters can suppress components e.g. a median filter can remove a spike (a single element that is strongly different from the others).
They are used for image restoration.
## Median filter
The output pixel is the median of the pixels in the neighborhood, it can eliminate outliers.
## Min filter and max filter
The output pixel is the min or the max of the pixels in the neighborhood, it can eliminate outliers.
They can be used to remove salt or pepper noise.
Min filter: highlights pepper noise, removes salt noise
Max filter: highlights salt noise, removes pepper noise
## Alpha-trimmed mean
Hybrid between mean and median filter, trade-off between the two regulated by parameter d (d=0 is the mean. d=mn-1 is the median):
![[Pasted image 20240402154313.png]]

![[Pasted image 20240402154334.png]]

# Adaptive filters
The filters discussed so far operate in the same way on every image and every part of the image: smarter behaviors can be designed.
Adaptive filters tune their effect comparing:
* Local image variance - $\sigma^{2}_{L}$ 
* Noise variance - $\sigma^{2}_{\eta}$ 
When $\sigma^{2}_{\eta} \ll \sigma^{2}_{L}$ the filter should be weak e.g. edges / other image elements.
When $\sigma^{2}_{\eta} \approx \sigma^{2}_{L}$  the filter should be strong.

![[Pasted image 20240402155038.png]]
