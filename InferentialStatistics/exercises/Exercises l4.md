# Example 4.1
(a) is there a sufficient statistic for $\theta$?
I use the normalization property of the pdf:
$1=\sum\limits_{x=1}^{\infty}c_{\theta} \theta^x=c_{\theta}(\frac{1}{1-\theta}-1)$ 
and solving the equation we get $f(x;\theta)=(1-\theta)\theta^{x-1}$ a geometric rv with parameter $1-\theta$ .

$f(\vec x;\theta)=\prod\limits_{i=1}^{n}{f(x_{i};\theta)}=(1-\theta)^{n}\theta^{\sum\limits_{i=1}^{n}{x_i}}\theta^{-n}$ 
if we choose $h(x)=1$ and $g(\overline x;\theta)=\frac{(1-\theta)^n}{\theta^{n}}\theta^{n\overline x}$
we see how $f(\vec x;\theta)=h(x)g(\overline x;\theta)$ which means that $\overline x$ is a sufficient statistic because of the factorisation criterion. $\square$

(c) method of moments and asymptotic bias:
Since $X_i$ is a geometric rv with parameter $1-\theta$ we have that $\mathbb E[X]=\frac{1}{1-\theta}$, solving the equation for the 1st moment we find:
$\hat\theta_{MM}=\frac{\overline X -1}{\overline X}$

The asymptotic distribution of $\overline X$ can be computed using CLT $\frac{\overline X - \mathbb E [X_{i}]}{\sqrt{\frac{\text{var}{(X_i)}}{n}}}\dot\sim \mathcal N(0,1)$ we get  that $\overline X \dot\sim \mathcal N(\frac{1}{1-\theta},\frac{\theta}{n(1-\theta)^2})$
....................

It is not an unbiased estimator because $\mathbb E_{\theta}[\hat\theta_{MM}]$......................................   

(d) MLE
$L(\theta)=\frac{(1-\theta)^{n}}{\theta^{n}}\theta^{\sum\limits_{i=1}^{n}{x_i}}=(1-\theta)^{n}\theta^{n(\overline x -1)}$   
$L'(\theta)=-n(1-\theta)^{n-1}\theta^{n(\overline x -1)}+(1-\theta)^{n} n(\overline x -1)\theta^{n(\overline x -1)}$  
we solve $L'(\hat\theta)=0$ and get $\hat\theta=\frac{\overline x -1}{\overline x}$, the same estimator obtained by the method of moments.

For the sample $(8,2,3,1)$ $\overline x=\frac{8+2+3+1}{4}=3.5$, $\hat\theta=0.71428$ 

................................distribution TODO........

(e) The answer is the same as in (d) because the sample is iid.

---

# Example 4.2
$f(x,\sigma^2)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{x^2}{2\sigma^2}}$ pdf of $X_i$
$L(\sigma)=\frac{1}{\sigma^n{(2\pi)}^{n/2}}e^{-\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{2\sigma^2}}$ 
$\ell(\sigma)=\ln(\frac{1}{\sigma^{n}(2\pi)^\frac{n}{2}})-\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{2\sigma^2}=$  
$=-n\ln({\sigma(2\pi)^\frac{1}{2}})-\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{2\sigma^2}=$  
$=-n\ln({\sigma})-(2\pi)^\frac{1}{2}-\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{2\sigma^2}$

$\ell'(\sigma)=\frac{-n}{\sigma}+\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{\sigma^3}$  

solve $\ell'(\hat\sigma)=0$ we get  
$\hat\sigma=\sqrt\frac{\sum\limits_{i=1}^{n}x_{i}^{2}}{n}$

and since MLE is `equivariant` then $\hat\psi=\ln(\hat\sigma)$.

---
# Example 4.3
(a) MLE of $\psi=\frac{\sigma}{\mu}$ and its distribution:

$f(x,\mu,\sigma^2)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{(x-\mu)^2}{2\sigma^2}}$ pdf of $X_i$
$L(\mu,\sigma)=\frac{1}{\sigma^n{(2\pi)}^{n/2}}e^{-\frac{\sum\limits_{i=1}^{n}(x_{i}-\mu)^{2}}{2\sigma^2}}$ 
$\ell(\mu,\sigma)=-n\ln{(\sigma\sqrt{2\pi})}-\frac{\sum\limits_{i=1}^{n}(x_{i}-\mu)^{2}}{2\sigma^2}$

$$\nabla\ell(\mu,\sigma)=[\frac{\sum\limits_{i=1}^{n}(x_{i}-\mu)}{\sigma^2},\frac{-n}{\sigma}+\frac{\sum\limits_{i=1}^{n}(x_{i}-\mu)^{2}}{\sigma^3}]^{\top}$$
Solving $\nabla\ell(\mu,\sigma)=\vec 0$ we get:
$\begin{cases}\hat\mu=\frac{1}{n}\sum\limits_{i=1}^{n}{x_i}=\overline x \\ \hat\sigma=\overline{x^{2}}-\overline x ^2\end{cases}$ 
and for the `equivariant` property $\hat\psi= \frac{\hat\sigma}{\hat\mu}=\frac{\overline{x^{2}}-\overline x ^2}{\overline x}$
..............distribution...................
(b) sample size 10, $\overline x=1.5$ and $\sum\limits_{i=1}^{n}{(x_i-\overline x)^2}=3$
provide an approximation for $P(\hat\psi>1+\psi)$
$\hat\mu=1.5,\hat\sigma=\frac{3}{n}=0.3\rightarrow \hat\psi=0.2$
$P(\hat\psi>1+\psi)=P(\psi<-0.8)$
...... need the distribution..............