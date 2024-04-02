#cv
Edge detection is a [[Low, Mid and High level image processing|mid level image processing]].
Canny edge detector is a filter addressing the following targets: 
* Low error rate
* Edge points well localized 
* Single edge point response
Steps:
1. Smoothing with a Gaussian filter 
2. Gradient computation (magnitude and phase) 
3. Quantize the gradient angles 
4. Non-maxima suppression 
5. Hysteresis thresholding
# 1. Smoothing
With a Gaussian filter before evaluating edges, with the purpose of noise reduction. We do this noise reduction before computing the gradient because derivatives amplify noise
# 2. Gradient computation
Edges are calculated using vertical, horizontal and diagonal masks. Edge direction is also calculated.
![[Pasted image 20240401193443.png]]
# 3. Edge quantization
![[Pasted image 20240401193527.png]]
# 4. Non-maxima suppression
Non-maxima suppression reduces the edge thickness
Thin edges are desirable
* Reduce a gradient to a single edge line
* Accurate location of the edge point
Non-maxima suppression is a process that crosses an edge and selects the strongest point.

Consider a neighborhood (e.g., 3×3). Take the quantized direction $d_l$ (closest to $\theta_k$). If (module of the central pixel < at least one of the neighbors along $d_k$) the gradient is set to 0 (suppressed).
![[Pasted image 20240401194005.png]]

# 5. Hysteresis thresholding
Hysteresis thresholding is used to: 
* Keep strong edges
* Keep weak edges connected with strong edges
* Reject isolated weak edges
* Edge strength is measured by means of gradient magnitude
![[Pasted image 20240401194300.png]]

Hysteresis thresholding is based on two thresholds: $T_L,T_H$, two images are obtained: $I_L$ and $I_H$.

[[09_3 - Canny edge detector.pdf||Effects of Canny on the pdf]]

