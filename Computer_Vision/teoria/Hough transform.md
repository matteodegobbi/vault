#cv
The classical Hough transform was concerned with the identification of [lines](https://en.wikipedia.org/wiki/Line_(mathematics) "Line (mathematics)") in the image, but later the Hough transform has been extended to identifying positions of arbitrary shapes, most commonly [circles](https://en.wikipedia.org/wiki/Circle "Circle") or [ellipses](https://en.wikipedia.org/wiki/Ellipse "Ellipse"). It's a [[Low, Mid and High level image processing|mid level image processing]] algorithm.
Before using the Hough transform we process the image with an edge detector algorithm like [[Canny Algorithm]].
# Using the Hough transform
A line passing through $x_{i},y_{i}$: $y_{i}= ax_{i}+b$ 
Now consider the ab-plane and rewrite the equation as $b=-x_{i}a+y_{i}$
The ab-plane is called parameter space.

| Original space (x,y)                       | Parameter space (a,b)                      |
| ------------------------------------------ | ------------------------------------------ |
| Bundle of lines passing<br>through a point | Bundle of lines passing<br>through a point |
| Line through 2 points                      | Intersection of two lines                  |
| Line through n points                      | Intersection of n lines                    |

With this parameter space though we can't represent vertical lines (infinite angular coefficient), so we use a different parameter space -> the normal representation:
![[Pasted image 20240402115743.png]]

The parameter space is quantized along $\rho$ and $\theta$


| Few (large) cells                      | Many (small cells)                    |
| -------------------------------------- | ------------------------------------- |
| Handle pixels not<br>perfectly aligned | ==Requires precise==<br>==alignment== |
| ==Poor lines==<br>==localization==     | Accurate lines<br>localization        |

For each edge pixel:
We compute $(\rho,\theta)$ pair values (going along the sinusoidal curve)
We count the crossed cells.
![[Pasted image 20240402125430.png]]
# Generalized Hough trasform
The Hough transform works for more complex shapes
General equation: $g(\vec\nu,\vec c)=0$ 
Where $\vec\nu$ is a vector of coordinates and $\vec c$ a vector of coefficients
E.g. (circle): $(x-c_{1})^{2}+(y-c_{2})^{2}= c_{3}^{2}$
The parameter space might have high dimensionality.