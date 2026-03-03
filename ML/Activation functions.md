#ml #dl 
### ReLU (Rectified Linear Unit)

$$  
\text{ReLU}(x) = \max(0, x)  
$$

### Leaky ReLU

$$  
\text{LeakyReLU}(x) =  
\begin{cases}  
x & \text{if } x > 0 \\ 
\alpha x & \text{if } x \le 0  
\end{cases}  
$$
### Softmax
$$  
\text{Softmax}(x_i) = \frac{e^{x_i}}{\sum_{j=1}^{n} e^{x_j}}  
$$
### Sigmoid

$$  
\sigma(x) = \frac{1}{1 + e^{-x}}  
$$

### Hyperbolic Tangent (Tanh)

$$  
\tanh(x) = \frac{e^x - e^{-x}}{e^x + e^{-x}}  
$$

### Swish / SiLU

$$  
\text{Swish}(x) = x \cdot \sigma(x)  
$$

### Parametric ReLU (PReLU)

$$  
\text{PReLU}(x) =  
\begin{cases}  
x & \text{if } x > 0 \\  
a x & \text{if } x \le 0  
\end{cases}  
$$
with a learnable

### ELU (Exponential Linear Unit)

$$  
\text{ELU}(x) =  
\begin{cases}  
x & \text{if } x > 0 \\  
\alpha (e^x - 1) & \text{if } x \le 0  
\end{cases}  
$$
### Softplus

$$  
\text{Softplus}(x) = \ln(1 + e^x)  
$$

### GELU (Gaussian Error Linear Unit)

$$  
\text{GELU}(x) = x \Phi(x)  
$$

where  
$$  
\Phi(x) = \frac{1}{2} \left(1 + \text{erf}\left(\frac{x}{\sqrt{2}}\right)\right)  
$$

---

Others like gated linear unit or SwiGLU, Relu^2 might also be used in practice.