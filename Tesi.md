#tesi #importante 
## Neurons:
Output perceptron: $\langle \vec{w},\vec{x}\rangle+b=\sum_j{w_j x_j}+b$    
Sigmoid: $\sigma(z) \triangleq \frac{1}{1+e^{-z}}$
Output sigmoid neuron: $\sigma(\langle \vec{w},\vec{x}\rangle+b)$ 
## Learning with gradient descent:
MSE Cost function ($x$ is the input, $a$ the output of the network ,$y(x)$ the desired output): 

$C(w,b)\triangleq \frac{1}{2n} \sum_x \| y(x)-a \|^2$  ^a6a5d4

To minimize the cost function we use a technique called gradient descent where we compute the local gradient of the cost function to find the direction of max slope. We search for the max slope in order to descend along it hoping to find an absolute minimum of $C(v)$.  ^c42b79

We have that $\Delta C \approx \nabla C \cdot \Delta v$, if we choose $\Delta v = -\eta \nabla C$ (meaning $v \to v' = v-\eta \nabla C$) with $\eta>0$ we guarantee that $\Delta C < 0$. 
It can be proved with Cauchy-Schwarz inequality that with the norm constraint $\| \Delta v \|=\epsilon$ $\eta = \frac{\epsilon}{\|\nabla C\|}$ is the optimal learning rate (it minimizes $\Delta C$, making it "the most negative"). 
It's important that $\epsilon$ is small enough that the approximation we made is precise but not too small, otherwise the algorithm will take a long time to converge.

## Stochastic gradient descent
To compute: ![[Tesi#^a6a5d4]]We need to calculate the argument of the sum for every $x$in the training dataset, this could take a long time for large datasets.
Stochastic gradient descent can be used to speed up this process: instead of calculating the argument of the sum for every $x$ we can only use a small random subset of the dataset called _mini-batch_ with $m$ data points. 
$\nabla C \approx \frac{1}{m}\sum_{j=1}^m \nabla C_{X_j}$ (instead of $\nabla C \approx \frac{1}{n}\sum_{x} \nabla C_{X}$)
After training with the mini-batch we choose another one and repeat this process until we have exausted the whole dataset, when we finish we say we have completed a training epoch. We repeat this procedure for a fixed amount of epochs.
...............................................





