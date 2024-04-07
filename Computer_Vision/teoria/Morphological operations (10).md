#cv 
#lowlevelprocessing 
These operations are [[Low, Mid and High level image processing (9)|low-level]], but operate on the shapes found in an image
They generally work on binary images, are based on set theory.

We use a Set-based description of an image:
* A set is a vector of tuples, each tuple representing the (x, y) coordinates of a point belonging to the set
* E.g.: the set of all white pixels in a binary image
It is possible to process an image working in
this set-based description
An operator can add or remove pixels to/from a set, such operators modify the image working on the shape (Examples: erosion and dilation).
# Structuring elements
![[Pasted image 20240402131008.png]]
# Erosion
Consider two sets, A and B (B being the structuring element)
The erosion of 𝐴 by 𝐵 is a set defined as: 𝐴 ⊝ 𝐵 = {𝑧| 𝐵 𝑧 ⊆ 𝐴}
This means: translate B to point 𝑧, and keep 𝑧 iff the whole structuring element is fully included in A.
Applications: Thinning, separate weakly connected components.
The shape of the structuring element determines in which direction(s) the erosion operates.
![[Pasted image 20240402131232.png]]

# Dilation

Consider two sets, 𝐴 and 𝐵 (𝐵 being the structuring element)
The dilation of 𝐴 by 𝐵 is a set defined as: 𝐴⨁𝐵 = {𝑧| 𝐵 𝑧 ⋂𝐴 ≠ ∅}.
This means: translate 𝐵 to point 𝑧, and keep 𝑧 iff there is at least one pixel overlapping with 𝐴
Applications: Thickening, merging close, unconnected components.
![[Pasted image 20240402131352.png]]

# Opening and Closing
## Opening: erosion + dilation
𝐴 ∘ 𝐵 = 𝐴 ⊝ 𝐵 ⨁𝐵
Effects: Contour smoothing, eliminate thin protrusions without reducing the element size.
## Closing: dilation + erosion
𝐴 ∙ 𝐵 = 𝐴⨁𝐵 ⊝ 𝐵
Effects: Fuse narrow breaks without increasing the element size.

## Noise removal
Complex combinations of morphological operations may effectively remove noise.
