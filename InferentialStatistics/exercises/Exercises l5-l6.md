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

$T_{n}=\frac{\overline X -\overline Y}{\sqrt{\frac{S_{x}^{2}}{m}+ \frac{S_{y}^{2}}{n}}}$
And we reject $H_{0}$ if $|T_{n}|>t_{\nu,1- \frac{\alpha}{2}}$, with:
$\nu=\frac{{(\frac{S_{x}^{2}}{m}+ \frac{S_{y}^{2}}{n})}^{2}}{\frac{S_{x}^{4}}{m^{2}(m-1)}+\frac{S_{y}^{4}}{n^{2}(n-1)}}$

TODO come si fa senza sample variance?????

---

# Example 5.3
$X_{i}\sim\mathcal N(\mu,\sigma^{2}),i=1,\dots,n$  both parameters are unknown
(a) $H_{0}:\mu=1$ against $H_{1}:\mu\ne1$ and observed sample with $\overline x = 2.1$ and $s^{2}=1.2$ determine $n$ needed for $\beta(2)=0.01$, (since $\mu=2$ we are under $H_{1}$) 

$\beta(2)=P_{\mu=2}(\pmb x \notin R)$ 
if $R$ is defined with a LRT we are in the case of a t-test,
$R=\{\pmb x:|\frac{\sqrt n(\overline x -\mu_{0})}{s}|\ge t_{n-1,1- \frac{\alpha}{2}}\}$
$\beta(2)=1-P_{\mu=2}(\text{reject }H_{0})=P_{\mu=2}(\pmb x \in R)=0.01$  
$\overline x \sim \mathcal N(\mu,\frac{\sigma^{2}}{n})$
$T_{n}\sim\mathcal N(\frac{\sqrt n}{s},\frac{\sigma^{2}}{s^{2}})$
$\beta(2)=1-2\Phi\left(\left(t_{n-1,1- \frac{\alpha}{2}}- \frac{\sqrt n}{s}\right) \frac{s}{\sigma}\right)$
TODO come lo calcolo senza sapere sigma?????
 

---

# Example 5.4
$X_{1},\dots,X_{n}$ iid random sample from $\text{Unif}(0,\theta)$, $\theta>0$. Construct a $1-\alpha$ confidence interval for $\theta$.

We use a LRT, we have that $L(\theta)=\frac{1}{\theta^{n}}$ if $x_{(n)}\le\theta$ and $0$ otherwise.
$R_{\alpha}(\theta_{0})=\{\pmb x: -2\log(\lambda(\pmb x))>\chi_{1,1-\alpha}^{2} \}$
$\hat\theta=x_{(n)}$ 
$\lambda(\pmb x)=x_{(n)}^{n}\cdot \frac{1}{\theta^{n}}$

$R_{\alpha}(\theta_{0})=\{\pmb x: e^{-2\log(\lambda(\pmb x))}<e^{\chi_{1,1-\alpha}^{2}} \}$
