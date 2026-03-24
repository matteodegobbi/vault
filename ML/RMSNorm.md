#ml #dl 

 Modified versions of [[Layer Normalization]] it drops the mean subtraction step and only normalizes by the root mean square:

$$\text{RMSNorm}(\mathbf{x}) = \frac{\mathbf{x}}{\text{RMS}(\mathbf{x})} \cdot \gamma, \quad \text{RMS}(\mathbf{x}) = \sqrt{\frac{1}{d}\sum x_i^2}$$

Compared to [[Layer Normalization]] it's faster (no mean computation) and empirically performs similarly or better

Like [[Layer Normalization]] now it's usually used in the [[Transformers#Pre-Norm vs Post-Norm|Pre-Norm]] fashion for improved stability.

---

