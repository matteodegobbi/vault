#statistics
# L4

## Statistics
In the following we always assume i.i.d. $Y_1,\dotsi,Y_n$ with $\mathbb E [Y_{i}]=\mu,\ \  \text var[Y_i]=\sigma^2$

If $T_n=T(Y_1,\dots,Y_n)$, with $T_{n}:\mathbb R^{n} \to \mathbb R^d$ does not depend on any unknown quantity then it's called a statistic.

$T_{n}$ is a rve so it has a df

### Sample average
$\overline Y=\frac{1}{n}\sum\limits_{i=1}^{n}{Y_i}$ is a statistic  and:
$\mathbb E[\overline Y]=\mu,\ \ \text var [\overline Y]=\frac{\sigma^2}{n}$ 

Furthermore if $Y_{i}\sim \mathcal N(\mu,\sigma^2)$ then $\overline Y \sim \mathcal N(\mu,\frac{\sigma^2}{n})$

(or  $\frac{\sqrt{n}(\overline Y - \mu)}{\sqrt{\sigma^{2}}}\sim\mathcal N(0,1)$, be careful this last one is NOT a statistic) ^sampleAvgStdNorm

---
### Sample variances (both versions)
$\mathbb E[S^2]=\sigma^2$
$\mathbb E[\hat \sigma^2]=\frac{n-1}{n}\sigma^2$
(this is the reason why we defined $S^2$ dividing by $n-1$)

$\text var(S^2)=\frac{\mu_{4}-\mu_{2}^2}{n}-\frac{2(\mu_{4}-2\mu_{2}^{2})}{n^2}+\frac{\mu_{4}-3\mu_{2}^2}{n^3}$
where $\mu_{k}$ is the moment of order $k$ of $Y_i$

### Independence of $S^2$ and $\overline Y$
In general $S^{2}$ and $\overline{Y}$ are NOT independent but if $Y_{i}\sim \mathcal N(\mu,\sigma^2)$ they are and:
* $\frac{(n-1)S^2}{\sigma^2}\sim\chi^{2}_{n-1}$ and it follows that $\text var(S^2)=\frac{2\sigma^4}{n-1}$ (from the variance of chi squared and the property of variance of multiplying by a constant)
* Combining the previous point with [[#^sampleAvgStdNorm|this]] we get: $\frac{\frac{\sqrt{n}(\overline Y - \mu)}{\sigma}}{\sqrt{\frac{(n-1)S^{2}}{\sigma^{2(n-1)}}}}=\frac{\sqrt{n}(\overline Y - \mu)}{S} \sim t_{n-1}$
### Estimators
If a statistic targets the parameter of the distribution $\theta$ (or a component of it) we call it estimator denoted by $\hat\theta$ . We will look at methods to compute estimators.
### Method of moments
The method consists in equating sample moments, e.g. $\overline{Y} , \overline{Y^2} , \overline{Y^3} , \dots$ with the corresponding population moments, e.g. $\mathbb E (Y), \mathbb E(Y^2), \mathbb E(Y^3)$
and solving these equations in terms of the parameter $\theta$.

For example in the method of moments $\hat\mu_{MM}=\overline Y$ and $\hat\sigma^{2}_{MM}=\hat \sigma^2=\frac{1}{n}\sum\limits_{i=1}^{n}{(Y_i-\overline Y)^2}$  (version of sample variance with division by $n$)
### Method of least squares
Used for linear regression:
$Y_i=g_i(\beta)+\epsilon_i$  
$g_{i}(\beta)=\beta_0+\beta_{1}x_{i1}+\dotsi+\beta_{p}x_{ip},\ \ i=1,\dots,n$
$\hat \beta_{LS}= \arg\inf\limits_{\beta\in\mathbb R^{p}}{\sum\limits_{i=1}^{n}{(y_i-g_i(\beta))^2}}$ 
normally we compute the derivative and find where it's equal to $0$. 
### Method of Maximum Likelihood

MLE is $\hat\theta=\arg\sup\limits_{\theta\in\Theta}{L(\theta)}$ 
under _standard regularity conditions_ the MLE is also defined to the solution of $\frac{\partial \ell(\theta)}{\partial \theta}$

($\theta$ may be a vector, in which case we need to solve a system of equations)

### Langrange multipier TODO
TODO
### Sufficiency
$T_n$ is a sufficient statistic for $\theta$ if the conditional distribution of the sample $\textbf Y=(Y_1,\dots,Y_n)$ given the value of $T(\textbf Y)$ does not depend on $\theta$.
$P_{\theta}(\textbf Y = \textbf y | T(\textbf Y) = t(\textbf y))=\frac{P_{\theta}(\textbf Y = \textbf y)}{P_{\theta}(T(\textbf Y) = t(\textbf y))}=\frac{f(\textbf y;\theta)}{q(t(\textbf y);\theta)}$ 
where $q$ is the pdf of $T(\textbf Y)$.

This method may be difficult to apply:
the Likelihood factorisation criterion is much easier:
A statistic $T(\textbf Y)$ is a sufficient statistic for $\theta$, iff there is a function $g(t; θ)$
and $h(y)$ such that, for all sample points $y$ and all parameter points $\theta$, $f(\textbf y;\theta)=g(T(\textbf y);\theta)h(\textbf y)$