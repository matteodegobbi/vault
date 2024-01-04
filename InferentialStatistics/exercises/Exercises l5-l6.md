#statistics 
# Example 5.1

$1=\sum\limits_{x=1}^{\infty}c_{\theta} \theta^x=c_{\theta}(\frac{1}{1-\theta}-1)$ 
and solving the equation we get $f(x;\theta)=(1-\theta)\theta^{x-1}$ a geometric rv with parameter $1-\theta$ .

and solving the equation we get $f(x;\theta)=(1-\theta)\theta^{x-1}$ a geometric rv with parameter $1-\theta$ .
(a) Wald confidence interval for $\theta$ of level $1-\alpha$, $\alpha = 0.9$ $\overline x = 10$ and $n=30$.
$|W|=|\frac{\hat\theta-\theta_{0}}{\widehat{se}}|$

$L(\theta)=\frac{(1-\theta)^{n}}{\theta^{n}}\theta^{\sum\limits_{i=1}^{n}{x_i}}=(1-\theta)^{n}\theta^{n(\overline x -1)}$   
$\ell(\theta)=n\log(1-\theta)+n(\overline x -1)\log\theta$
$J(\theta)=\frac{n(\overline x -1)}{\theta^{2}} + \frac{n}{(1-\theta)^{2}}$ 
$\hat\theta=\frac{\overline x -1}{\overline x}=0.9$
$J(\hat\theta)=3333.3333$
$\widehat{se}=1/\sqrt{\hat J}=0.01732$

$R=\{\pmb X: |W|\ge z_{1- \frac{\alpha}{2}}\}=\{\pmb X:   \theta_{0}\le \hat\theta - z_{1- \frac{\alpha}{2}}\widehat{se}\} \vee \theta_{0}\ge \hat\theta + z_{1- \frac{\alpha}{2}}\widehat{se}\}$
$R^{\mathsf c}=\{\pmb X: \hat\theta - z_{1- \frac{\alpha}{2}}\widehat{se} \le \theta_{0}\le \hat\theta + z_{1- \frac{\alpha}{2}}\widehat{se} \}$ 

$z_{1- \frac{0.1}{2}}=1.644854$
confidence interval of level $1-\alpha=0.9$ : $CI=[0.871511,0.928489]$
TODO CONTROLLA 
(b) I would reject $H_{0}$ since $\theta_{0}=0.5$ is outside the confidence interval.

(c) The likelihood ratio test statistic is $\lambda(\pmb x)=\frac{L(\theta_{0})}{L(\hat\theta)}=\frac{L(\theta_{0})}{4.42\cdot 10^{-43}}$
$R_{\alpha}(\theta_{0})=\{\pmb x: -2\log(\lambda(\pmb x))>\chi_{1,1-\alpha}^{2} \}$
We can use this region because the shipment is made of a very large number of items (asymptotic approximation)
We can compute $-2\log(\lambda(\pmb x))$ and $\chi_{1,1-\alpha}^{2}$ and plot them, then we take the values of $\theta$ for which the sample is in the acceptance region, this is done with the following R script:

```
ell_f <-function(theta){
  n=30
  bar_x = 10
  n*log(1-theta)+n*(bar_x-1)*log(theta)
}
theta_seq = seq(0.75,1,0.00001)

alpha = 0.9
threshold = qchisq(p = 1-alpha,df = 1)
MLE = 0.9
tlambda = -2*ell_f(theta_seq)+2*ell_f(MLE)
plot(theta_seq,tlambda,main = '-2 log(lambda) and chisq_1,1-alpha threshold',lwd=1,lty=1,type = 'l')
abline(h=threshold,col='green')

confidence_interval = theta_seq[tlambda<threshold]
sprintf('[ %f , %f ]',confidence_interval[1],confidence_interval[length(confidence_interval)])


```
that outputs:
```
"[ 0.897810 , 0.902160 ]"
```
which is the confidence interval for $\alpha=0.9$.
![[confidenceIntervals.png]]
![[confidenceIntervals2.png]]
(d) p-value:
$\text{p-value}=P_{\theta}(-2\log(\lambda)\ge-2\log(\lambda_{obs}))$
$\lambda_{obs}= 1$
Take the log on both sides and multiply by $-2$.

$\text{p-value}=P_{\theta}(\chi_{1}^{2}\ge0)=1$.
TODO controlla 

---

# Example 5.2

Let $X_{i} \sim Poi(\theta_{1}), i = 1,\dots, m$ and $Y_{j}∼ Poi(\theta_{2}), j = 1,\dots, n$ , with $X_{i}, Y_{j}$being independent for all $i, j$.


(a) Log-likelihood ratio test for $H_{0}:\theta_{1}=\theta_{2}$ against $H_{1}:\theta_{1}\ne\theta_{2}$ at the level $\alpha$. $\overline y = 6, \overline x = 2,m = 15, n = 10$, compute the test and get the p-value.
The joint pdf is $f_{joint}(x_{1},\dots,x_{m},y_{1},\dots,y_{n})=\frac{e^{-m\theta_{1}}\theta_{1}^{\sum\limits_{i=1}^{m}x_{i}}}{\prod\limits_{i=1}^{m}x_{i}!} \frac{e^{-n\theta_{2}}\theta_{2}^{\sum\limits_{i=1}^{n}y_{i}}}{\prod\limits_{i=1}^{n}y_{i}!}$ 
if $\theta_{1}=\theta_{2}$ (null hypothesis) the likelihood is $\frac{e^{-\theta(m+n)}\theta^{\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i}}}{\prod\limits_{i=1}^{m}x_{i}!\prod\limits_{i=1}^{n}y_{i}!}$
and the log likelihood is $\ell(\theta)=-\theta(m+n)+(\log\theta)(\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i})-\log(\prod\limits_{i=1}^{m}x_{i}!\prod\limits_{i=1}^{n}y_{i}!)$ 
we solve the likelihood equation ($\frac{\partial\ell(\theta)}{\partial\theta}=0$) and get $\hat\theta=\frac{\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i}}{m+n}$ under $H_{0}$ 

to find the denominator of $\lambda(\pmb \cdot)$ we can use the equivariance principle of the MLE and $\hat\theta_{1}=\overline x$  and $\hat\theta_{2}=\overline y$.

We have that $\log(\lambda(\pmb \cdot))=-(\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i})+\log(\frac{\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i}}{m+n})(\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i})-\log(\prod\limits_{i=1}^{m}x_{i}!\prod\limits_{i=1}^{n}y_{i}!)-(-m\overline x-n\overline y + (\sum\limits_{i=1}^{m}x_{i})\log(\overline x)+(\sum\limits_{i=1}^{n}y_{i})\log(\overline y)-\log(\prod\limits_{i=1}^{m}x_{i}!\prod\limits_{i=1}^{n}y_{i}!)$
$=\log(\frac{\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i}}{m+n})(\sum\limits_{i=1}^{m}x_{i}+\sum\limits_{i=1}^{n}y_{i})-(\sum\limits_{i=1}^{m}x_{i})\log(\overline x)-(\sum\limits_{i=1}^{n}y_{i})\log(\overline y)=$
$=\log(\frac{m\overline x + n\overline y}{m+n})(m\overline x + n\overline y)-m\overline x\log(\overline x)-n\overline y \log(\overline y)$ we call this $\log(\lambda(\pmb{x,y}))$ 

And we have that the rejection region is $\{ \pmb{x,y}:-2\log(\lambda(\pmb{x,y})) > \chi_{1,1-\alpha}^{2}\}$.

using the observed samples we get
TODO FORSE VA r-q =1 e non 2
( e se df =1 verrebbe ```> 1-pchisq(26.034,df=1)
[1] 3.354574e-07```)

$\{ \pmb{x,y}: 26.03 > \chi_{2,1-\alpha}^{2}\}$.
and we get that $p-value \approx 2.222\cdot 10^{-6}$

(b) If we define $\delta\triangleq\theta_{1}-\theta_{2}$ we have that $\hat\delta = \hat\theta_{1}-\hat\theta_{2}$ for the principle of equivariance.
$\hat\delta = \overline x - \overline y=-4$
and the confidence interval of approximately confidence level $1-\alpha$ is 
$[\hat\delta - z_{1- \frac{\alpha}{2}}\widehat{se}, \hat\delta + z_{1- \frac{\alpha}{2}}\widehat{se}]$
we just need to compute $\widehat{se}$ , we have that asymptotically MLE is normal, $\hat\theta_{1}\dot\sim\mathcal N(\theta_{1},\text{var}(\hat\theta_{1}))$, $\hat\theta_{2}\dot\sim\mathcal N(\theta_{2},\text{var}(\hat\theta_{2}))$ 
and since $\hat\theta_{1}=\overline X$ and $\hat\theta_{2}=\overline Y$ they are independent because they are functions of independent rvs. This means that:
$\hat\delta\dot\sim\mathcal N(\overline X-\overline Y,\text{var}(\overline X)+\text{var}(\overline Y))$
and using the formula for the variance of the sample average and the variance of Poisson rvs we get:
$\hat\delta\dot\sim\mathcal N(\overline X-\overline Y,\frac{\theta_{1}}{m}+\frac{\theta_{2}}{n})$
${se}=\sqrt{\frac{\theta_{1}}{m}+\frac{\theta_{2}}{n}}$
$\widehat{se}=\sqrt{\frac{\overline X}{m}+\frac{\overline Y}{n}}$
using the observed values we get:
$\widehat{se}=0.8563$
$\text{CI}_{1-\alpha} = [-4-z_{1- \frac{\alpha}{2}}0.8563,-4+z_{1- \frac{\alpha}{2}}0.8563]$
and for example for $1-\alpha=99\%$ we can compute with R:

```
> alpha = 1 - 0.99
> z = qnorm(1-alpha/2)
> c(-4-z*0.8563,-4+z*0.8536)
[1] -6.205683 -1.801272
```
which means that $\hat\delta = 0$ is outside of our confidence interval of confidence $99\%$

if we take $\alpha=10^{-6}$ we get the confidence interval $[ -8.1887100,0.1755026]$ which includes $0$.

(c) TODO come si fa paired test con WALD????

---

# Example 5.3
$X_{i}\sim\mathcal N(\mu,\sigma^{2}),i=1,\dots,n$  both parameters are unknown
(a) $H_{0}:\mu=1$ against $H_{1}:\mu\ne1$ and observed sample with $\overline x = 2.1$ and $s^{2}=1.2$ determine $n$ needed for $\beta(2)=0.01$, (since $\mu=2$ we are under $H_{1}$) 

$\beta(2)=P_{\mu=2}(\pmb x \notin R)$ 
if $R$ is defined with a LRT we are in the case of a t-test,
$R=\{\pmb x:|\frac{\sqrt n(\overline x -\mu_{0})}{s}|\ge t_{n-1,1- \frac{\alpha}{2}}\}$
$\beta(2)=1-P_{\mu=2}(\text{reject }H_{0})=P_{\mu=2}(\pmb x \notin R)=0.01$  
$\overline x \sim \mathcal N(\mu,\frac{\sigma^{2}}{n})$
$T_{n}\sim\mathcal N(\frac{\sqrt n}{s},\frac{\sigma^{2}}{s^{2}})$
$\beta(2)=1-2\Phi\left(\left(t_{n-1,1- \frac{\alpha}{2}}- \frac{\sqrt n}{s}\right) \frac{s}{\sigma}\right)$
TODO come lo calcolo senza sapere sigma e alpha?????
 

---

# Example 5.4
$X_{1},\dots,X_{n}$ iid random sample from $\text{Unif}(0,\theta)$, $\theta>0$. Construct a $1-\alpha$ confidence interval for $\theta$.

We use a LRT, we have that $L(\theta)=\frac{1}{\theta^{n}}$ if $x_{(n)}\le\theta$ and $0$ otherwise.
$R_{\alpha}(\theta_{0})=\{\pmb x: -2\log(\lambda(\pmb x))>\chi_{1,1-\alpha}^{2} \}$
$\hat\theta=x_{(n)}$ 
$\lambda(\pmb x)=x_{(n)}^{n}\cdot \frac{1}{\theta^{n}}$ for $\theta\ge x_{(n)}$ 
$\lambda(\pmb x)=0$ for $\theta<x_{(n)}$ (this means that we always reject independently of the sample)
$R_{\alpha}(\theta_{0})=\{\pmb x: e^{-2\log(\lambda(\pmb x))}>e^{\chi_{1,1-\alpha}^{2}} \}$

$R_{\alpha}^{\mathsf C}(\theta_{0})=\{\pmb x: e^{-2\log(\lambda(\pmb x))}\le e^{\chi_{1,1-\alpha}^{2}} \}$
$R_{\alpha}^{\mathsf C}(\theta_{0})=\{\pmb x: (\lambda(\pmb x))^{-2}\le e^{\chi_{1,1-\alpha}^{2}} \}$
$R_{\alpha}^{\mathsf C}(\theta_{0})=\{\pmb x: \frac{\theta_{0}^{2n}}{x_{(n)}^{2n}}\le e^{\chi_{1,1-\alpha}^{2}} \}$
$R_{\alpha}^{\mathsf C}(\theta_{0})=\{\pmb x: \frac{\theta_{0}}{x_{(n)}}\le e^{\frac{\chi_{1,1-\alpha}^{2}}{2n}} \}$
$R_{\alpha}^{\mathsf C}(\theta_{0})=\{\pmb x: \theta_{0}\le x_{(n)}e^{\frac{\chi_{1,1-\alpha}^{2}}{2n}} \}$
also we need to remember that $\theta_{0}\ge x_{(n)}$.
this means that the $\text{CI}_{1-\alpha}=[x_{(n)}, x_{(n)}e^{\frac{\chi_{1,1-\alpha}^{2}}{2n}}]$

an example in R is:
```
likelihood_f <- function(theta, sample_max, n) {
  if (theta < sample_max) {
    return(0)
  } else{
    return(1 / theta ^ n)
  }
}
true_theta <- 10
n <- 9
alpha <- 0.01
obs <- runif(n = n, min = 0, max = true_theta)
sample_max <- max(obs)
thetas <- seq(4, 20, 0.01)
computed_likelihood <-
  sapply(thetas, likelihood_f, sample_max = sample_max, n = n)
plot(thetas,
     computed_likelihood,
     type = 'l',
     col = 'blue')
abline(v = sample_max, col = 'red')
right_CI = sample_max * exp(qchisq(p = 1 - alpha, df = 1) / (2 * n))
abline(v = right_CI, col = 'red')
sprintf("[%f,%f]", sample_max, right_CI)
```
and the CI is `[8.941970,12.927558]` using $\alpha=0.01$,
![[CIunifrom.png]]

---
# Example 5.5

