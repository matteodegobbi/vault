#ml #dl 

# Convolutional layer 
A convolutional layer executes the convolution operation (actually cross-correlation as we don't mirror the kernel as in signal convolution) on input data (e.g. an image) with a filter (or kernel) of some dimensions.
The kernel is scrolled across the input and the dot product operation is performed obtaining a scalar that is the output corresponding to that region of the input.

If the input is an image it can be represented as a width x height x channels tensor, in this case the kernel will have dimension WxHxchannels, e.g. for a 256x256x3 image a kernel could be a 5x5x3 kernel.

In CNNs convolutional layers are stacked one after the other, granting bigger receptive field the deeper we go in the network.

## Stride

In convolution, stride refers to how far the kernel moves across the input after each operation. Instead of shifting one pixel at a time, the kernel can move multiple pixels per step. A larger stride reduces the size of the output feature map (more details later on), while a stride of 1 preserves more spatial detail.

## Multiple feature maps

Instead of learning just one kernel we can learn multiple different kernels, yielding multiple feature maps. The kernels are independent from one another. The output feature maps are stacked along the channel dimension. This will yield an output with multiple channels. The idea is that different feature maps will focus on detecting different patterns from the same input, i.e. some feature map focuses on edges, one on corners.

## Size of the output
$W_{out} = \frac{W_{in} - K_{size} + 2P}{S} + 1$, where $W_{in}$ is the input width, $K_{size}$ is the kernel size, $P$ is the padding (usually 0 pad or seldom reflection pad), and $S$ is the stride.

Sometimes we say same-padding to mean that the spatial dimensions of the output are the same as the input's, usually used to shrink the input too much, this allows for deeper networks.

## 1x1 conv
We can use a special 1x1 convolution kernel to adjust the number of feature maps (channels) without changing the other spatial dimensions.
For example take an input 16x16x4 we can learn 5 1x1 kernels such that the output will be 16x16x5

## Properties of convolutional layers
**Sparsity**: with respect to a fully connected layer a convolutional layer is sparse, meaning that it only connects to a local region of the input. This drastically reduces the number of parameters compared to a fully connected layer, which would connect every neuron in the previous layer to every neuron in the current layer.
**Parameter sharing**: focusing on one kernel the same kernel weights are applied across the whole input. meaning that the same weights are used for every spatial location. 
This makes the layer invariant to translation, this often makes sense in image recognition tasks where objects can appear in different locations within an image. Parameter sharing can lead to improved data efficiency as a pattern learned in some region of the input will also be recognized in different parts the image: a fully connected layer would need to relearn the same pattern every time it was seen in a different location (with greater risk of overfitting).

It should be noted that translation invariance applies only to the single layer and not to the whole network.

# Pooling
The other important layer in CNNs other than convolutional layers is the pooling layer. Pooling layers are used to reduce the spatial dimensions of the feature maps produced by the convolutional layers. The utility of pooling mainly lies in reducing the number of parameters and by conferring invariance to small transformation and increasing robustness to local noise.
We use 2 types of pooling average and max pooling.

![[Pasted image 20260303232753.png]]

The same formula as convolution can be used to compute size of outputs (P=0 in the case of pooling, usually stride = kernel size).

The idea behind average pooling is to summarize the information within a small region of the feature map.
In max pooling, the maximum value within that region is selected, highlighting the most important feature.

# Activations for CNNs
If we want to build deep networks, able to learn hierarchical patterns we cannot use sigmoid or tanh [[Activation functions]] due to the vanishing gradient problem.

Other activations like ReLU or others are often used.

# Final layers 
### Flatten+Dense layer
Historically, the final layers of a CNN typically consisted of one or more fully connected layers whose input was the output of the last convolutional or pooling layer flattened into a single vector. These fully connected layers were used to perform the final classification or regression task.

### Global Average pooling
 Nowadays another common approach is to use global average pooling as the last layer.
 GAP takes the feature maps and computes the average value over each channel. This results in a single value per feature map.

For example in the case of classification with n classes, we can make so the last convolutional layer has n feature maps in order to obtain an output with n channels, then we can apply GAP to obtain a 1 dimensional vector of size n.
Applying some activation like Softmax we get the usual classification output without using Dense (fully connected) layers.
GAP allows fewer parameters and potentially less overfitting

---

# Other techniques useful in CNNs
[[Batch normalization]]
Strided convolution (meaning stride S>1) can be used to replace pooling layers.
[[Dropout]]
Regularization
[[Data augmentation]]
Depthwise Separable Convolution
Atrous convolution
Transposed Convolution (Deconvolution)

# Known CNNs
Inception/GoogLeNet
ResNet
DenseNet
EfficientNet
R-CNN and FAST R-CNN
DeepLab
YOLO
U-Net

---

