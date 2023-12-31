#statistics
# Useful stuff from L0 and L1

## Covariance and correlation
$\sigma_{ij}=\text{cov}(X_{i},X_{j})=E(X_{i},X_{j})-E(X_{i})E(X_{j})$
$\rho_{ij}=\frac{\sigma_{ij}}{\sqrt{\sigma_{ii}\sigma_{jj}}}$
covariance and correlation matrices have the previous two formulas as elements.
$\rho_{ii}=1$ always

## Change of variable argument

$g:\mathbb R^{k}\to \mathbb R^{k}$ with $g(x)=(g_{1}(x),\dots,g_{k}(x))$ differentiable and bijective. Then $Y=g(X)$ is rve with pdf: $f_{Y}(y)=f_{X}(g^{-1}(y))|\det(J(y))|$ 
where $J(y)=\det([\frac{\partial g^{-1}(y)}{\partial y_{1}},\dots,\frac{\partial g^{-1}(y)}{\partial y_{k}}])$, the Jacobian of the inverse of $g$.
We can also use a $g$ with a 'dummy function' in order to satisfy the hypotheses of this theorem.
It can be useful to call $y_{1}=y,y_{2}=z,\dots$ to simply the notation. 


TODO Multinomial??????
# Inequalities

Markov: $X$ is a non-negative rv s.t. $E(X)<\infty$, $P(X>t)\le \frac{E(x)}{t}$, for any $t>0$.

Chebyshev: $X$ real valued rv st $E(x)=\mu$ and $\text{var}(X)=\sigma^{2}$ are finite, $P(|X-\mu|\ge t)\le \frac{\sigma^{2}}{t^{2}}$, for any $t>0$.

## Delta method
Useful to find the limiting distribution of a function of a random variable whose limiting distribution is normal.
Let $X_{n}$ a sequence of rv s.t. $\frac{\sqrt{n} (X_{n}-\mu)}{\sigma} \to^{d}\mathcal N(0,1)$ and that $g$ is differentiable and $g'(\mu)\ne0$. Then $\frac{\sqrt{n}(g(X_{n})-g(\mu))}{|g'(\mu)|\sigma}\to^{d}\mathcal N(0,1)$.
In other terms, if $X_{n}\dot\sim\mathcal N(\mu,\frac{\sigma^{2}}{n})\to g(X_{n})\dot\sim\mathcal N(g(\mu),g'(\mu)^{2} \frac{\sigma^{2}}{n})$

There's also a multivariate version of the delta method

# Symmetrical quantile for $\mathcal N(0,\sigma^{2})$
For distribution which are symmetrical around the origin we have that $x_{1-\alpha}=-x_{alpha}$. 


# L2 - Descriptive statistic, statistical models
## Samples
We call $x_{1},\dots,x_{n}$ the observations of an experiment _observed sample_, with $n$ being the sample size.
We assume they are a realization of the _random sample_ $X_{1},\dots,X_{n}$ with $X_{i}$ mutually independent and with the same marginal pdf $f(x;\theta)$.

Since $X_{i}$ are independent the joint pdf of the sample is: 
$f(x_{1},\dots,x_{n};\theta)=\prod\limits_{i=1}^{n}{f(x_{i};\theta)}$ 
## Summary statistics
* Sample average $\overline X = \frac{1}{n}\sum\limits_{i=1}^{n}X_{i}$ 
* Sample variance $S^{2} = \frac{1}{n-1}\sum\limits_{i=1}^{n}{(X_{i}-\overline X)^{2}}$ 
* Sample k-th moment $\overline{X^{k}} = \frac{1}{n}\sum\limits_{i=1}^{n}X_{i}^{k}$ 
and their observed counterparts (in lowercase). 
### Order statistic
$X_{(1)}=\min\limits_{1\le i\le n}{X_{i}}$ is the smallest observation,
$X_{(i)}$ is the i-th smallest observation,
$X_{(n)}=\max\limits_{1\le i\le n}{X_{i}}$ is the biggest observation,
The list $X_{1},\dots,X_{n}$ is called order statistics and it's used to define the following statistics.
The sample median  
* $Q_{2}=\begin{cases}X_{\left(\frac{n+1}{2}\right) \text{ if } n \text{ is odd }}\\ \frac{X_{(\frac{n}{2})}+X_{(\frac{n}{2}+1)}}{2} \text{ if } n \text{ is even } \end{cases}$
* The first and third quartile $Q_{1} = X_{[0.25(n+1)]}$ and $Q_{3} = X_{[0.75(n+1)]}$
* The p-th sample quantile, $p\in(0,1)$ is $X_{[p(n+1)]}$
* Inter quartile range $\text{IQR}=Q_{3}-Q_{2}$
* Median absolution deviation from the median $\text{MAD}=\text{median}(|X_{1}-Q_{2}|,\dots,|X_{n}-Q_{2}|)$
(where $[x]$ is the floor function)
Be careful to not confuse the sample median $Q_{2}$ with the median of the distribution.

## Histogram
TODO add

## Box plot
TODO
## QQ plot
TODO
## Empirical distribution function
The edf is defined as:
$F_{n}(x)=\sum\limits_{i=1}^{n}{I_{X_{i}}(x)}$ for all $x\in\mathbb R$
where $I_{X_{i}}$ is a Bernoulli rv with success probability $P(X_{i}\le x)$, which means $F_{n}$ is a rv.

The corresponding observed version is $\hat F_{n}(x)=\frac{1}{n}\sum\limits_{i=1}^{n}\mathbb 1_{x_{i}}(x)$ for all $x\in\mathbb R$
the edf targets the population df.

## Multivariate data summaries
Often in real applications we collect data for several variables.
A common question is if the variables from which we sampled the data are related to each other.
We define the sample covariance as: $s_{xy}=\frac{1}{{n-1}}\sum\limits_{i}(x_{i}-\overline x)(y_{i}-\overline y)$ which targets $\sigma_{xy}$.
and the sample Pearson correlation: $r_{xy}=\frac{s_{xy}}{s_{x}s_{y}}$ which targets $\rho_{xy}$.

## Statistic models 
$X_{1},\dots,X_{n}$ random sample with $X\sim F_{\theta}$. If in addition $X_{i}$ are independent we call it iid random sample. 
The statistical model is the set $\{ f(x_{1},\dots,x_{n};\theta):\theta \in \Theta, x_{i}\in\mathcal X \}$ where $\Theta$ is the set of all possible values for $\theta$.
(joint pdf can be factorized in single pdfs thanks to independence)

Linear and logistic regression on the PDF L2.

# L3 - The likelihood function
## Likelihood function
Let $X_{1},\dots,X_{n}$ be an iid sample with $X_i$ having pdf $f(x;\theta)$, the likelihood function is $L:\Theta\to\mathbb R_{\ge0}$ defined as:
$L(\theta)=\prod\limits_{i=1}^{n}{f(X_{i};\theta)}$
for an observed sample it's defined as:
 $L(\theta)=\prod\limits_{i=1}^{n}{f(x_{i};\theta)}$
Be careful it's not a joint pdf because we are holding $X_{i}$ fixed while in a pdf $\theta$ is fixed.
For discrete rvs it's a probability: the probability of observing that sample when the parameter is $\theta$ (under the chosen model).
For continous rvs it's not a probability, but the higher the likelihood the higher the probability of observing that sample.

We can look for the $\theta$ with the largest likelihood, this is called the maximum likelihood estimate: $\hat\theta = \arg\sup\limits_{\theta\in\Theta}L(\theta)$.
Often we will work with the log-likelihood: $\ell(\theta)\triangleq\log{L(\theta)}$ when it can be defined ($L(\theta)\ne0, \forall \theta\in\Theta$).
## Observed information
We can quantify the informativeness of a likelihood function:
$J(\theta)=-\frac{\partial^{2}\ell(\theta)}{\partial\theta^{2}}$
(or $J_{n}(\theta)$ if we want to emphasize $n$)
$J\ge0$ and the higher the $J$ the higher the peakedness of the likelihood.
### Observed information for vector $\theta$
In the case where $\theta$ is a vector then $J(\theta)$ will be a symmetrical matrix where:
$J(\theta)_{ij}=- \frac{\partial^{2}\ell(\theta)}{\partial\theta_{i}\partial\theta_{j}}$ 
this is the Hessian matrix of the log likelihood multiplied by $-1$.

In the following we call:
* $J(\theta)_{ij}$ the cell of $J$
* $J(\theta)^{ij}$ the cell of $J^{-1}$
* $\hat J=J(\hat\theta)$

## Computation of $\hat\theta$
To compute $\hat\theta$ we:
1. Compute the gradient of the log-likelihood and solve the likelihood equation: $\ell'(\theta^{*})=0$
2. Check that $J(\theta^{*})>0$, if so $\hat\theta = \theta^{*}$
(In this way we only check it's a local maximum)
(Sometimes we can have a likelihood that is $=0$ for some values of $\theta$, in this case we cannot use $\ell$)
### Newton-Raphson
In some cases an analytical solution of the likelihood equation is not feasible, we can use a numerical approximation, we build a sequence that converges to $\hat\theta$:
$\tilde\theta_{m+1}=\tilde\theta_{m}+\frac{\ell'(\tilde\theta_{m})}{J(\tilde\theta_{m})}$
we stop after a finite number of iterations.


# L4 - Point estimation

## Statistics
In the following we always assume i.i.d. $Y_1,\dotsi,Y_n$ with $\mathbb E [Y_{i}]=\mu,\ \  \text var[Y_i]=\sigma^2$

If $T_n=T(Y_1,\dots,Y_n)$, with $T_{n}:\mathbb R^{n} \to \mathbb R^d$ does not depend on any unknown quantity then it's called a statistic.

$T_{n}$ is a rve so it has a df

### Sample average
$\overline Y=\frac{1}{n}\sum\limits_{i=1}^{n}{Y_i}$ is a statistic  and:
$\mathbb E[\overline Y]=\mu,\ \ \text var [\overline Y]=\frac{\sigma^2}{n}$ 

Furthermore if $Y_{i}\sim \mathcal N(\mu,\sigma^2)$ then $\overline Y \sim \mathcal N(\mu,\frac{\sigma^2}{n})$

(or  $\frac{\sqrt{n}(\overline Y - \mu)}{\sqrt{\sigma^{2}}}\sim\mathcal N(0,1)$, be careful this last one is NOT a statistic) ^sampleAvgStdNorm

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
## Estimators
If a statistic targets the parameter of the distribution $\theta$ (or a component of it) we call it estimator denoted by $\hat\theta$ . We will look at methods to compute estimators.
### Method of moments
The method consists in equating sample moments, e.g. $\overline{Y} , \overline{Y^2} , \overline{Y^3} , \dots$ with the corresponding population moments, e.g. $\mathbb E (Y), \mathbb E(Y^2), \mathbb E(Y^3)$
and solving these equations in terms of the parameter $\theta$.

For example in the method of moments $\hat\mu_{MM}=\overline Y$ and $\hat\sigma^{2}_{MM}=\hat \sigma^{2}=\frac{1}{n}\sum\limits_{i=1}^{n}{(Y_i-\overline Y)^{2}}=\overline{Y^{2}}- \overline{Y}^{2}$  (version of sample variance with division by $n$)
### Method of least squares
Used for linear regression:
$Y_i=g_i(\beta)+\epsilon_i$  
$g_{i}(\beta)=\beta_0+\beta_{1}x_{i1}+\dotsi+\beta_{p}x_{ip},\ \ i=1,\dots,n$
$\hat \beta_{LS}= \arg\inf\limits_{\beta\in\mathbb R^{p}}{\sum\limits_{i=1}^{n}{(y_i-g_i(\beta))^2}}$ 
normally we compute the derivative and find where it's equal to $0$. (Example in the pdf)
### Method of Maximum Likelihood

MLE is $\hat\theta=\arg\sup\limits_{\theta\in\Theta}{L(\theta)}$ 
under _standard regularity conditions_ the MLE is also defined as the solution of $\frac{\partial \ell(\theta)}{\partial \theta}=0$ (only the case when log-likelihood can be defined)
($\theta$ may be a vector, in which case we need to solve a system of equations)

### Langrange multipier
It's a method to transform the minimization of a function subject to an equality constraint into a minimization of an unconstrained function.

It works by making the constrainst into an equality with $0,\ g(x)=0$. And solving the derivatives of $f(x)+\lambda g(x)$ equal to $0$ (also the derivative wrt $\lambda$). 

[Wikipedia Lagrange Multiplier](https://en.wikipedia.org/wiki/Lagrange_multiplier)

It's useful when for example we need to be careful when estimating parameters that need to sum to 1 because the are probabilitis (Multinomial blood type pdf L4)

## Sufficiency
$T_n$ is a sufficient statistic for $\theta$ if the conditional distribution of the sample $\textbf Y=(Y_1,\dots,Y_n)$ given the value of $T(\textbf Y)$ does not depend on $\theta$.
$P_{\theta}(\textbf Y = \textbf y | T(\textbf Y) = t(\textbf y))=\frac{P_{\theta}(\textbf Y = \textbf y)}{P_{\theta}(T(\textbf Y) = t(\textbf y))}=\frac{f(\textbf y;\theta)}{q(t(\textbf y);\theta)}$ 
where $q$ is the pdf of $T(\textbf Y)$.

This method may be difficult to apply:
the Likelihood factorization criterion is much easier:
A statistic $T(\textbf Y)$ is a sufficient statistic for $\theta$, iff there is a function $g(t; \theta)$
and $h(y)$ such that, for all sample points $y$ and all parameter points $\theta$, $f(\textbf y;\theta)=g(T(\textbf y);\theta)h(\textbf y)$.

## Unbiasedness

Given $\hat\theta$ an estimator of $\theta$, based on a random sample $Y_1 , \dots  , Y_n$ from some distribution $F_{\theta}$ , the bias is defined as: $b(\theta;\hat\theta) = \mathbb E_{\theta}(\hat\theta) - \theta$
We say $\hat\theta$ is an unbiased estimator if $b(\theta;\hat\theta)=0$ for all $\theta$.
Many estimators are not unbiased but are instead asymptotically unbiased, ($n\to\infty$).

## MSE
Mean Squared Error is a measure of performance of an estimator that takes into account both the location and the variability.

$\text{mse}(\theta;\hat\theta)=\mathbb E_{\theta}(\hat\theta - \theta)^{2}= \text{var}(\hat\theta)+(\text{bias}(\theta;\hat\theta))^{2}$
MSE is $\ge 0$ and unbounded, lower MSE is better.
In general it depend on $\theta$.
(Example in the pdf)

## Consistency

An estimator $\hat\theta$ is consistent if it converges in probability to $\theta$:
$\forall \epsilon>0,\ \ \lim\limits_{n\to\infty}{P(|\hat\theta-\theta|>\epsilon)}=0$

TODO controlla se serve anche il bias che tende a 0
To check for consistency we can also alternatively check that:
$\lim\limits_{n\to\infty}{\text{mse}(\theta;\hat\theta)}=0$, this implies $\hat\theta$ is consistent.

## Distribution of estimators
In general directly deriving the distribution of $\hat\theta$ can be difficult, we can use several ways to approximate it, we studied CLT and delta method.
(TODO add link)

## Properties of MLE
For an iid random sample with pdf $f$ satisfying certain regularity conditions (not in this course):
1. If there is a sufficient statistic for $\theta$ then the MLE is a function of a sufficient statistic (and MLE will also be suffcient).
2. The MLE is equivariant, if $\tau=g(\theta)$ for any function $g$ then $\tau = g(\hat\theta)$ 
3. MLE is consistent ($\hat\theta \to^P\theta$) (and mse goes to 0 equivalent definition)
4. MLE is asymptotically efficient (explanation in pdf)
5. MLE is asymptotically normal, $\frac{\hat\theta-\theta}{\sqrt{\text{var}(\hat\theta)}}\to^{d}\mathcal N(0,1)$ for $n\to\infty$

Property 5. tells us that:
${(\hat\theta-\theta)}{\sqrt{I_{n}(\theta)}}\to^{d}\mathcal N(0,1)$ for $n\to\infty$
and since this hold for every $\theta$ also for $\hat\theta$:
$({\hat\theta-\theta}){\sqrt{I_{n}(\hat\theta)}}\to^{d}\mathcal N(0,1)$ for $n\to\infty$

$({\hat\theta-\theta}){\sqrt{J_{n}(\theta)}}\to^{d}\mathcal N(0,1)$ for $n\to\infty$

$({\hat\theta-\theta}){\sqrt{J_{n}(\hat\theta)}}\to^{d}\mathcal N(0,1)$ for $n\to\infty$

Where $J_{n}$ is the observed information, $I_{n}$ is the Fisher information, $\text{se}=\frac{1}{\sqrt{I_{n}}}$ is called standard error , $\hat{\text{se}}=\frac{1}{\sqrt{I_{n}(\hat\theta)}}$

Under reg. cond. the Fisher Information is defined as:
$I_{n}=\text{var}(\frac{\partial\ell(\theta)}{\partial\theta})=\sum\limits_{i}\text{var}\frac{\partial\log{f(Y_{i};\theta)}}{\partial\theta}=nI_{1}$ where $I_{1}$ is the Fisher info for a single observation (variance of the score).
An alternate formula sometimes easier to compute is: $I_{1}(\theta) = -\mathbb E(\frac{\partial^{2}\log f(Y;\theta)}{\partial\theta^{2}})$
(expected value of observed information)
### Multivariate MLE

The limiting normal distribution holds even for a vector-valued parameter.

For $\theta \in \mathbb R^{d}$ under the regularity conditions:
$I_{n}(\hat\theta)^{-\frac{1}{2}}(\hat\theta - \theta)\to^{d}N_{d}(0,\mathcal I)$ 
where $I_{n}(\hat\theta)$ is a $d\times d$ matrix and $\mathcal I$ is the identity matrix. 

$J_{n}(\hat\theta)^{-\frac{1}{2}}(\hat\theta - \theta)\to^{d}N_{d}(0,\mathcal I)$ 

From this we can derive for any element of $\theta$ , $\text{se}(\hat\theta_{i})=\sqrt{J_{n}(\hat\theta)^{ii}}$

$\frac{\hat\theta-\theta}{\text{se}(\hat\theta_{i})}\to^{d}\mathcal N(0,1)$ for $n\to\infty$


---

# L5 - Hypothesis testing 
Let $Y_{1},\dots,Y_{n}$ an iid random sample with $Y_{i}\sim F_{\theta}$ where $\theta\in\Theta$ is the unknown parameter.
We denote $\mathcal Y$ the range of $Y_{i}$.
We want to build a decision rule from a sample to decide:
$H_{0}:\theta\in\Theta_{0}$ against $H_{1}:\theta\in\Theta_{0}^{\mathsf c}$, where $\Theta_{0}\subset\Theta$
we want to find $R\subset\mathcal Y^{n}$ s.t. we reject $H_{0}$ if $\vec y=(y_{1},\dots,y_{n})\in R$  and accept otherwise.

To compute this region we define _test statistics_.

For example we may be interested in testing:
* $H_{0}:\mu\le\mu_{0}$ against $H_{1}:\mu>\mu_{0}$ (one-tailed hypotheses)
* $H_{0}:\mu=\mu_{0}$ against $H_{1}:\mu\ne\mu_{0}$ (two tailed hypotheses)

## Likelihood ratio test

The likelihood ratio test statistic for $H_{0}:\theta\in\Theta_{0}$ against $H_{1}:\theta\in\Theta_{0}^{\mathsf c}$ is:
$\lambda(\pmb y)=\frac{\sup_{\theta\in\Theta_{0}}{L(\theta)}}{\sup_{\theta\in\Theta}{L(\hat\theta)}}=\frac{L(\hat\theta_{0})}{L(\hat\theta)}$ (using MLE notation) and a likelihood ratio test has rejection region:
$R=\{\pmb y: \lambda(\pmb y) < c \}$, where $0\le c\le1$.
(In the case we have a sharp null hypothesis in the numerator the $\sup$ is useless)

## Type I and type II error

The decision taken (accept or reject) can be wrong. 
We call type I error if we reject $H_{0}$ when it's true and type II error when we accept $H_{0}$ and it's false.

We define the size of type I error as:
$\alpha'=\sup\limits_{\theta\in\Theta_{0}}{P(\text{reject }H_{0}| H_{0} \text{ is true})}$ 
and the size of type II error as:
$\beta(\theta)=1-{P(\text{reject }H_{0}| H_{1} \text{ is true})},\ \forall\theta\in\Theta_{0}^{\mathsf c}$ .

We'd like both error sizes to be $0$ but it's impossible. In practice we fix a small $\alpha$ and make sure that $\alpha'\le\alpha$, the maximum size of the type I error allowed Fixed $\alpha$ we have fixed the size of the rejection region.

* If $\alpha' = \alpha$ the test is called a test of size $\alpha$.
* If $\alpha'\le\alpha$, we call it a test of level $\alpha$.
In practice we can often only compute tests of size $\alpha$ asymptotically.

## Likelihood ratio is asymptotically $\chi_{r-q}^{2}$  
$\theta=(\theta_{1}\dots,\theta_{q},\theta_{q+1},\dots,\theta_{r})$ and $\Theta_{0}\subset\Theta$ s.t. $\Theta_{0}=\{ \theta:\theta_{q+1}=\theta_{0,q+1},\dots,\theta_{r}=\theta_{0,r}\}$
Under $H_{0}:\theta\in\Theta_{0}$ and suitable regularity conditions:
$$-2\log{\lambda(\pmb y)}\to^{d}\chi_{r-q}^{2}\ \ \  \text{ as }  n\to\infty$$ 
$q$ is the number of parameters we fixed.
TODO chiedi spiegazione di sta roba

## Wald test

It's a test for testing $H_{0}:\theta=\theta_{0}$ against $H_{1}:\theta\ne\theta_{0}$ when an estimator has a normal distribution (can be a limiting distribution)
Since we saw that MLE is asymptotically normal the Wald test is often used with the MLE.
Since MLE is s.t. $\hat\theta\dot\sim\mathcal N(\theta,I_{n}(\hat\theta)^{-1})$, the Wald test of approximate level $\alpha$ is the to reject $H_{0}$ if:
 $|W|=|\frac{\hat\theta - \theta_{0}}{\widehat{se}}|\ge z_{1-\frac{\alpha}{2}}$, with $\widehat{se}=\sqrt{\frac{1}{I_{n}(\hat\theta)}}$  is the estimated standard error of $\hat\theta$, we can use the asymptotical version $J$ in place of $I$.

 Wald test for multivariate $\theta$ in pdf.

## p-value

The p-value is defined as the smallest $\alpha$ that leads to the rejection of $H_{0}$:
For every $\alpha\in(0,1)$ if $R_{\alpha}$ is a rejection region of size $\alpha$, then $\text{p-value}=\inf\{ \alpha:T(X_{1},\dots,X_{n})\in R_{\alpha}\}$, a small p-value means that $H_{0}$ is incompatible with the data and must be rejected, we usually compare the p-value with $\alpha$ to determine if it's small.
If the rejection region is in the form:$\{X_{1},\dots,X_{n}:T(X_{1},\dots,X_{n})\ge c\}$, then the p-value is:
$\sup\limits_{\theta\in\Theta_{0}}P_{\theta}(T(X_{1},\dots,X_{n})\ge T^{obs})$

If the rejection region is in the form:$\{X_{1},\dots,X_{n}:T(X_{1},\dots,X_{n})\le c\}$, then the p-value is:
$\sup\limits_{\theta\in\Theta_{0}}P_{\theta}(T(X_{1},\dots,X_{n})\le T^{obs})$

If the rejection region is in the form:$\{X_{1},\dots,X_{n}:T(X_{1},\dots,X_{n})\ge c_{1}\}\cup\{X_{1},\dots,X_{n}:T(X_{1},\dots,X_{n})\le c_{2}\}$
then the p-value is: $2\min(\sup\limits_{\theta\in\Theta_{0}}P_{\theta}(T(X_{1},\dots,X_{n})\le T^{obs}),\sup\limits_{\theta\in\Theta_{0}}P_{\theta}(T(X_{1},\dots,X_{n})\ge T^{obs}))$
(In the case which $\Theta_{0}=\{\theta_{0}\}$ we just ignore the sup)

---

t-test and LRT test for the variance in the PDF l5aggiornate.

---
# L6 - Confidence Sets

Point estimates are a good guess for population moments but for example in the WM example $P_{\mu}(\overline X = \mu)=0$ , we may want a set that cointains $\mu$ with a pre-specified  probability.

## Interval estimators

An interval estimate of scalar parameter $\theta$ is a pair of functions $L(\pmb x),U(\pmb x)$ of sample $\pmb x = (x_{1},\dots,x_{n})$ s.t. $L(\pmb x)\le U(\pmb x),\ \forall \pmb x \in \mathcal X$ , in the observed sample we infer that $L(\pmb x)\le \theta \le U(\pmb x)$.

The random interval  $[L(\pmb x),U(\pmb x)]$ based on the random sample $\pmb X = (X_{1},\dots,X_{n})$ is called an interval estimator. (It can also be upper or lower intervals with $\infty$ or $-\infty$ ).

The _coverage probability_ for an interval estimator of $\theta$ is: $P_{\theta}(\theta\in[L(\pmb X),U(\pmb X)])$ (the probability that the interval contains $\theta$).
The _confidence level_ is the smallest coverage probability among all $\theta$: $\inf\limits_{\theta\in\Theta}{P_{\theta}(\theta\in[L(\pmb X),U(\pmb X)])}$ 

## Inverting a test statistics

For two-tailed confidence intervals, the method for constructing a $1-\alpha$ level confidence set consists of:
1. get $R$, the rejection region for $H_{0}:\theta=\theta_{0}$ vs $H_{1}:\theta\ne\theta_{0}$
2. get the acceptance region $R^{\mathsf c}$
3. invert the acceptance region
Examples in the PDF.

### Inverting a Wald test
Let $R=\{ \pmb X: \frac{|\hat\theta-\theta_{0}|}{\widehat{se}}>z_{1- \frac{\alpha}{2}} \}$ be the rejection region of a Wald test of (approx. because asymptotic) size $\alpha$ for $H_{0}$ against $H_{1}$ as usual. Then the corresponding confidence interval of (approx) confidence level $1-\alpha$ is $[\hat\theta-z_{\frac{1-\alpha}{2}}\widehat{se},\hat\theta+z_{\frac{1-\alpha}{2}}\widehat{se}]$, the Wald test always gives symmetrical confidence intervals.

### Inverting a LRT 
Let $R_{\alpha}(\theta_{0})=\{ \pmb X: -2\log{\frac{L(\theta_{0})}{L(\hat\theta)} }>\chi_{1,1-\alpha}^{2} \}$ be the rejection region of size $\alpha$, (using theorem 5 $-2\log{\lambda(\pmb y)}\dot\sim \chi_{r-q}^{2}$).
The confidence set of level $1-\alpha$ is $\{\theta:\theta\in R_{\alpha}(\theta)^{\mathsf c}\}$, holding the data $\pmb X$ fixed.

