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
In this version we try to obviate the phenomenon of overfitting on the training set, which amounts to learning to reconstruct perfectly every sample in the training set but not working well out of the training set.

To do this during training we inject some noise into the input and try to reconstruct it without the noise. Some examples could be Gaussian noise or masking some parts of the input.

This idea is very similar to [[Dropout]].
# Sparse autoencoder
Another way to reduce overfitting and help generalization is through the imposition of a sparsity constraint on the bottleneck layer, forcing most neurons to be inactive (output 0).
There are multiple ways to achieve this sparsity constraint, one method is to add a penalty to the loss using the KL divergence between the mean activation value for a neuron over the whole training set and a specified sparsity hyperparameter $\rho$. This means that a neuron should fire with probability approximately $\rho$.
(This is done for all neurons in the hidden layer, it forces each neuron individually to have mean activation $\rho$)


---

# Variational Autoencoders
Generative model in machine learning that can use the compressed representation learned in latent space, to generate new samples that resemble the original data.
VAEs don't learn just a deterministic encoding of data, but a distribution over possible latent representations.

Instead of mapping each input to a single fixed point in latent space, a VAE maps inputs to the parameters of a probability distribution (typically a Gaussian's mean and standard deviation). 
During generation, a latent vector is sampled from this distribution and passed through the decoder to produce an output.

Learning a distribution has some advantages over a deterministic mapping:
* The latent space is structured and continuous, points that are close in the latent space are expected to be decoded into similar output
* We can generate new data sampling from the latent distribution and running the decoded on the sampled vector.

## VAE Theory
The idea behind VAE is based on Bayesian variational inference. 

We map the input to a distribution $p_\theta$, with $\theta$ the learned parameters of the decoder.
### Full representation of relationship between $x$ and $z$
#### Prior
Distribution over the latent variable $z$:  $p(z)$
(Often prior is chosen to be a Gaussian $p(z) = \mathcal{N}(0, I)$, meaning latent variables are independent, zero mean, unit variance)

#### Likelihood (decoder)
This models how data $x$ is generated from latent variable $z$, $p_\theta(x|z)$
$\theta$ = parameters of the decoder network, represents the generative model
#### True posterior
It's the actual Bayesian posterior:
$p_\theta(z|x) = \frac{p_\theta(x|z)p(z)}{p_\theta(x)}$
But it is intractable, because computing $p_\theta(x) = \int p_\theta(x|z)p(z)dz$ is difficult.
To compute this integral analytical methods fail because even when $z$ is a simple distribution like Gaussian $p_\theta(x|z)$ is not Gaussian since the decoder is highly non-linear meaning Normality isn't preserved.

Then we could think of using methods like Monte Carlo integration, this is still intractable as it would require sampling of many $z$'s and for each of them we would require a forward pass of the decoder, also for the curse of dimensionality in importance sampling we would require an exponential number of samples (this is because z's pdf puts almost all mass far away from the region where p(x|z) is signficant, this is a similar problem to off-policy MC in RL).

#### Variational posterior (encoder)
We introduce an approximation: $q_\phi(z|x)$, it approximates the true posterior $p_\theta(z|x)$
$\phi$= parameters of the encoder network
We assume the conditional distribution to be Gaussian, $q_\phi(z|x) =  \mathcal{N}(z;\mu_\phi(x), \sigma_\phi(x))$
The encoder outputs: $\mu_\phi(x) \text{ and }\sigma_\phi(x)$
Which will be used to sample $z$.
### ELBO derivation

The loss used for training VAEs is called ELBO (Evidence Lower BOund):
$$
\begin{aligned}
L_\text{VAE}(\theta, \phi) 
&= -\log p_\theta(\mathbf{x}) + D_\text{KL}( q_\phi(\mathbf{z}\vert\mathbf{x}) \| p_\theta(\mathbf{z}\vert\mathbf{x}) )\\
&= - \mathbb{E}_{\mathbf{z} \sim q_\phi(\mathbf{z}\vert\mathbf{x})} \log p_\theta(\mathbf{x}\vert\mathbf{z}) + D_\text{KL}( q_\phi(\mathbf{z}\vert\mathbf{x}) \| p_\theta(\mathbf{z}) ) \\
\theta^{*}, \phi^{*} &= \arg\min_{\theta, \phi} L_\text{VAE}
\end{aligned}
$$
The way it's derived is starting from the reverse KL divergence between the true posterior $p_\theta(z|x)$ and the approximate posterior $q_\phi(z|x)$ (basically the encoder).
(We use the reverse KL and not the forward because the forward would involve $p_\theta(z|x)$ itself which we don't have access to, the whole point of introducing the $q_\phi$ was that the true posterior is intractable)

The exact steps of the derivation can be found [here at Lilian Weng's blog](https://lilianweng.github.io/posts/2018-08-12-vae/) and at [Eric Jang's blog](https://blog.evjang.com/2016/08/variational-bayes.html).

The reason for the name ELBO is that $-L_\text{VAE}$ is a lower bound for $\log{p_\theta(x)}$ the log of the evidence (aka normalization factor). Which means that by minimizing the loss we are maximizing a lower bound of the probability of generating data from the true distribution.

One more detail to note about ELBO is how the first term of the loss:
$$-\log p_\theta(\mathbf{x}|\mathbf z)$$is equivalent to the MSE reconstruction loss if likelihood $p_\theta(\mathbf{x}|\mathbf z)$ is Gaussian, and is equivalent to BCE if the likelihood is Bernoulli. This is an independent assumption to $q_\phi(z|x)$ being Gaussian which we need to use the reparametrization trick explained below.
In both cases (Bernoulli or Gaussian) this term measures how well the decoder explains the data, given the latent representation how probable is the data, this is the same as regular AE loss. 

The second term of the loss:
$$+ D_\text{KL}( q_\phi(\mathbf{z}\vert\mathbf{x}) \| p_\theta(\mathbf{z}) )$$
Acts as a regularization, penalizing distributions straying too far away from the prior, this structures the latent space around the prior.
### Reparametrization trick

Finally to obtain a usable loss we need to consider a problem in the previous formulation of the loss, in:
$$
L_\text{VAE}(\theta, \phi) 
 = - \mathbb{E}_{\mathbf{z} \sim q_\phi(\mathbf{z}\vert\mathbf{x})} \log p_\theta(\mathbf{x}\vert\mathbf{z}) + D_\text{KL}( q_\phi(\mathbf{z}\vert\mathbf{x}) \| p_\theta(\mathbf{z}) )
$$
there's an expectation, this is a problem because we don't have a way to backpropagate through a sampling operation.

To solve this we use the reparametrization trick that brings us to a form to which backprop can be used. 
So instead of sampling $z$ as: 
$$
\mathbf{z} \sim q_\phi(\mathbf{z}\vert\mathbf{x}^{(i)}) = \mathcal{N}(\mathbf{z}; \boldsymbol{\mu}^{(i)}, \boldsymbol{\sigma}^{2(i)}\boldsymbol{I})
$$ 
we write write $z$ as a function of the deterministic vectors $\mu,\sigma$ and a random vector $\varepsilon$ which is sampled from a standard Normal distribution. 
$$
\mathbf{z} = \boldsymbol{\mu} + \boldsymbol{\sigma} \odot \boldsymbol{\epsilon} \text{, where } \boldsymbol{\epsilon} \sim \mathcal{N}(0, \boldsymbol{I})  \scriptstyle{\text{; Reparameterization trick.}}
$$

Now the sampling doesn't involve the weights of the encoder which means that we can compute gradients:

![[reparameterization-trick.png]]

The final VAE with the Gaussian assumption can be represented with the following diagram:
![[vae-gaussian.png]]

---
