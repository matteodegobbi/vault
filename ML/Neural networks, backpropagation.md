#ml #dl 

Focusing on feed forward networks, a DAG organized in layers.
With each edge $e$ having a weight $w(e)$.
![[Pasted image 20260303004419.png]]

The layers between the input and the output are called hidden layers.
Considering node $v_{t+1,j}$ let:
* $a_ {t+1,j}(x)$ its input when $x$ is the input of the NN
* $o _{t+1,j}(x)$ its output when $x$ is the input of the NN

Now we drop the dependance on x for brevity.
To get the output of a neuron we first take the sum of the weighted outputs of neurons in the previous layer, and then apply an activation function to this sum. 
In formulas, for neuron $v_{t+1,j}$:
1. We compute $a_{t+1,j} = \sum_{k=1}^{n[t]} w_{k,j} o_{t,k}$  ,where $n[t]$ is the number of neurons in the $t$-th layer, $w_{e_{kj}}$ is the weight associated with the edge connecting neuron $k$ in the previous layer to neuron $j$ in the current layer
2. We compute $o_ {t+1,j} = \sigma(a_{t+1,j})$ , where $\sigma$ is the activation function. 

This process is repeated from the first hidden layer to the output layer. Each layer’s output becomes the input to the next layer. We can write this more compactly with matrices.

Finding the [[Empirical risk minimization]] hypothesis for NNs is NP-Hard, so instead we use [[Stochastic gradient descent]]. To be able to compute the gradients for all the weights efficiently we use backpropagation. Implementation details and full analysis in the Onenote file.

