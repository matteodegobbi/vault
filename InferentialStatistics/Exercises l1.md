# Exercise 1.1
Since $X\perp Y$  $f_{XY}(x,y)=f_X(x)f_X(y)=e^{-x-y}\mathbb{1}_{x\ge0,y\ge0}$

$Z=(Z_1,Z_2)$
$Z_1=\frac{X}{X+Y}$   
$Z_2=X+Y$   
$g^{-1}(z_1,z_2)=(z_{1} z_{2},z_2-z_{1}z_{2})$

$J(z)=\begin{pmatrix}z_{2}&z_1\\-z_{2}&1-z_{1}\end{pmatrix}$ 
$|\det J|=|z_{2}|=\underbrace{z_2}_{\ge0}$
$f_{Z_{1}Z_{2}}(z_{1},z_{2})\ne0$ when 
$$(\triangle)\begin{cases} 
z_{1} z_{2} \ge0 \\
z_2-z_{1}z_{2}\ge0
\end{cases}\to
\begin{cases}
z_{2}\ge 0 \\
0\le z_{1}\le 1 
\end{cases}$$
$f_{Z_{1}Z_{2}}(z_{1},z_{2})=e^{-z_{1}z_{2}-(z_2-z_{1}z_{2})}z_{2}=z_{2}e^{-z_{2}}$ when $(\triangle)$ else it's $0$

Now we determine the PDFs of $Z_{1}$ and $Z_{2}$ using the marginal rules:
$f_{Z_{1}}(z_{1})=\int_{0}^{+\infty}{z_{2}e^{-z_{2}}\,dz_{2}}=1$
$f_{Z_{2}}(z_{2})=\int_{0}^{1}{z_{2}e^{-z_{2}}\,dz_{1}}=z_{2}e^{-z_{2}}$
We have $Z_{1}\perp Z_{2}$ because:
$f_{Z_{1}Z_{2}}(z_{1},z_{2})=f_{Z_{1}}(z_{1})f_{Z_{2}}(z_{2})$ 
$\square$ 
# Exercise 1.2
$X_{n}\sim Bin(n,\theta)$
$f_{X_{n}(k)}= {n \choose k} \theta^{k}(1-\theta)^{n-k}$
a. we need to prove that $\lim_{n\to\infty}{P(|\frac{X_n}{n}-\theta|>\epsilon)}=0\ \ \forall \epsilon >0(\star)$
$\mathbb{E}(X_n)=\frac{n\theta}{n}=\theta$ from expectation of Bin and linearity
$\sigma_{X_{n}}^{2}= \frac{n\theta(1-\theta)}{n^{2}}=\frac{\theta(1-\theta)}{n}$ from variance of Bin and the property of variance ($\text var(\frac{X}{\alpha})=\frac{1}{\alpha^2}\text var (X)$)
we can use Chebychev inequality:
$0\le{P(|\frac{X_n}{n}-\theta|>\epsilon)}\le \frac{\theta(1-\theta)}{n \epsilon^2}$, the left hand side of this inequality is equal to 0 and the right hand side converges to 0 for $n\to \infty$ so we proved $(\star)$ . $\square$
b. Since in a. we proved that ${X_n/n}\xrightarrow{\text{P}}\theta$ if we take $g(x)=1-x$ we have from the properties of convergence in probability that $g({X_n/n})\xrightarrow{\text{P}}g(\theta)=1-\theta$. $\square$
c. Since we proved b. and a. we can use the property of convergence in probability that states that if $X_n \xrightarrow{P} X,\ Y_n \xrightarrow{P} Y \text{ then } X_nY_n \xrightarrow{P} XY$ .
We apply this property with $\frac{X_n}{n}$ and $1-\frac{X_n}{n}$ and we get 
$\frac{X_n}{n}(1-\frac{X_n}{n})\xrightarrow{P}\theta(1-\theta)$. $\square$

