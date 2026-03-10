#ml #dl 
Dropout is a [[Regularization]] technique used to easily reduce overfitting in neural networks. It consists of randomly deactivating some neurons during each training update, we set some specified probability $p$ to determine the chance of a neuron being dropped out. (obtained by multiplying the neuron's output by 0, except in some weird neural nets like RBF).

For example, given a layer with 10 neurons, with a dropout rate of 0.5, each neuron has a 50% chance of being deactivated during each training update.

In the implementation we also want to avoid biasing the neuron outputs by using dropout, therefore we adopt this definition:
Each activation $h$ in the layer is replaced by $h'=\begin{cases}0 \text{ with probability } p \\ \frac{h}{1-p} \text{ with probability }1-p \end{cases}$ 
This guarantees that $\mathbb E[h']=h$ .

During inference Dropout is deactivate, it's only used in training as regularization.

---

# Interpretation
One possible interpretation is that dropout acts as a form of ensemble learning. By randomly dropping out neurons during training, we effectively train an [[Ensembles|ensemble]] of many different neural networks. This is slightly different from the usual bagging approach where the networks are independent, since the parameters are shared between the "different networks".
With $n$ neurons in a layer, dropout implicitly trains an approximation of an ensemble of up to $2^n$ subnetworks (although with shared parameters).

The idea behind dropout proposed in the original paper is to force neurons to not depend on other neuron's specific activations in order to output the correct value, making the network more robust to variations in training set.

It's also similar to other techniques that add noise as regularization (e.g. Gaussian noise injection in the input or [[Autoencoders#Denoising autoencoder|denoising autoencoders]]) but in Dropout's case the noise is multiplicative and discrete.

---

# Usage in conjunction with BatchNorm 

In modern large networks it's often not necessary to use Dropout whenever we use [[Batch normalization]] which was invented for training stability but might already provide regularization through both its multiplicative and additive noises due to the batch sampling.

Sometimes using them together can be even harmful: Dropout randomly sets activations to zero and rescales the remaining ones: this changes the distribution of activations during training, BatchNorm, however, is trying to learn stable statistics of those activations, this added noise can make BatchNorm estimates worse.

Even more so during inference we will be using as BatchNorm parameters running averages collected during training which were influenced by the randomly dropped neurons.

It might still be useful to use Dropout especially if using linear layers at the end of the network.
For example, this architecture makes sense and can be used:

```
Conv → BatchNorm → ReLU  
Conv → BatchNorm → ReLU  
Flatten  
Linear  
ReLU  
Dropout  
Linear (output)
```


# Spatial Dropout

Spatial Dropout is used in [[Convolutional neural networks]] and consists in randomly dropping entire feature maps instead of individual neurons.
This is more useful for CNNs since even if a single neuron were dropped out the spatial close ones would still contain most of the info as images are locally very correlated.
