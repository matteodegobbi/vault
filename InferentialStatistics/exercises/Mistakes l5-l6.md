#statistics 
# Exercise 1
TO find the fisher info we find the log likelihood for n=1

$\ell_{1}(\theta)=\log(1-\theta)+(X -1)\log\theta$

$J_{1}(\theta)=\frac{(X -1)}{\theta^{2}} + \frac{1}{(1-\theta)^{2}}$ 
$I_{1}(\theta)=\mathbb E(J_{1}(\theta))=\frac{1}{(1-\theta)^{2}}+\frac{\mathbb{E}[x-1]}{\theta^{2}}=\frac{1}{(1-\theta)^{2}\theta}$ 
We also need to derive the answer as well, not just use the formula
$R^{\mathsf c}=\{-z_{1- \frac{\alpha}{2}}\le\frac{\hat\theta-\theta}{\widehat{se}}\le z_{1- \frac{\alpha}{2}}\}$ 
$P(R^{\mathsf c})\dot=1 -\alpha$
and then we invert the acceptance region to find the CI.
$[0.872,0.928]$ is bigger than the one found with J instead of I

# Exercise 2
# Exercise 3
# Exercise 4
# Exercise 5
# Exercise 6
# Exercise 7