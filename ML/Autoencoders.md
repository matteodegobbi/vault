#ml #dl 
Source [article](https://lilianweng.github.io/posts/2018-08-12-vae/) on autoencoders.
# Autoencoders
Models that learn to reconstruct high dimensional data like images, using a bottleneck layer (with much smaller width than input layer).

The idea is that the model will learn a compressed representation of the data. This compressed representation at the bottleneck can have multiple purposes: dimensionality reduction, extracting features to use in other models, generation of similar samples (especially in the case of VAEs) or lossy data compression.

![[autoencoder-architecture.png]]


It's composed of two networks:
1. The encoder compressing the data to a low dimensional vector z
2. The decoder reconstructing the input 
The network is trained to learn the identity function, we can use losses like MSE between output and input or cross entropy if the activation is sigmoid.

# Denoising autoencoder
In this version we try to obviate the phenomenon of overfitting on the training set, learning to reconstruct perfectly every sample in the training set but not working well out of training set.

To do this during training we inject some noise into the input and try to reconstruct it without the noise. Some examples could be Gaussian noise or masking some parts of the input.

This idea is very similar to [[Dropout]].

# Sparse autoencoder
Another way to reduce overfitting and help generalization is through the imposition of a sparsity constraint on the bottleneck layer, forcing most neurons to be inactive (output 0).
There are multiple ways to achieve this sparsity, one method is to add a penalty to the loss using the KL divergence between the mean activation value for a neuron over the whole training set and a specified sparsity hyperparameter $\rho$. This means that a neuron should fire with probability approximately $\rho$.
(This is done for all neurons in the hidden layer, it forces each neuron individually to have mean activation $\rho$)


---

# Variational Autoencoders