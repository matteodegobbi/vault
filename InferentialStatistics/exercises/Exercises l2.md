# Exercise 2.1
i) $S^{2}\le \frac{1}{n-1}\sum\limits_{i}^n{(X_{i}-a)^2}$ for any $a\in\mathbb{R}$ 
$S^{2} =\frac{1}{n-1}\sum\limits_{i}^n{(X_{i}-\overline X)^2}\le \frac{1}{n-1}\sum\limits_{i}^n{(X_{i}-a)^2}$
$\sum\limits_{i}^n{(X_{i}-\overline X)^2}\le \sum\limits_{i}^n{(X_{i}-a)^2}$
$\sum\limits_{i}^n{(-2X_{i}\overline X +\overline{X}^2)}\le \sum\limits_{i}^n{(-2X_{i}a +{a}^2)}$
$\sum\limits_{i}^n{(-2X_{i}\overline X )+n\overline{X}^{2}\le -2a\sum\limits_{i}^{n}}{(X_{i}) +{\sum\limits_{i}^{n}(a^2})}$
$-2 n\overline X^{2}+{n\overline X^{2}\le}-2a n \overline X+ {n a^2}$
$-n\overline X^{2} \le -2a n \overline X+ {n a^2}$
$-\overline X^{2} \le -2a \overline X+ {n^2 a^2}$
$0 \le\overline X^{2} -2a \overline X+ {n^{2} a^{2}}(\star)$
if $a$ and $\overline X$ have the opposite sign the inequality $(\star)$ is true because a sum of positive numbers is $\ge 0$.
otherwise:
$\overline X^{2} -2a \overline X+ {n^{2} a^{2}}\ge^{(n\ge1)}\overline X^{2} -2an \overline X+ {n^{2} a^{2}}= (\overline X - na)^2\ge0$ $\square$ 

ii) $\frac{(n-1)S^2}{n}=\frac{1}{n}\sum\limits_{i}^n{(X_{i}-\overline X)^2}$
$=\frac{1}{n}\sum\limits_{i}^n{(X_i^2-2X_{i}\overline X +\overline{X}^2)}$
$=\overline{X^{2}}-2\overline{X}^2+\overline{X}^{2}=\overline{X^2}-\overline{X}^2$
$\square$
---
# Exercise 2.2
$X_1,\dots,X_{n}$ iid random sample with $X_{i} \sim F$ with continuous $F$.
i)
$\min:\mathbb R^{n}\to\mathbb R$ 
I call $Z$ the rv $X_{(1)}$ 
$B_z=\{x_1,\dots,x_n:\min(x_1,\dots,x_{n})\le z\}$
we have that $B_Z$ is the set of points in which at least one component is less than $z$  

${B_z}^C=(z,+\infty)\times\dotsi\times(z,\infty)$
$F_{Z}(z)=1-\int\limits_{{B_{z}^C}}{\prod\limits_{i=1}^{n}{f(x_i)} dx_{1}dx_{2}\dotsi dx_{n}}=1-(1-F(z))^n$ 
Now we can take the derivative:
$f_Z(z)=-n(1-F(z))^{n-1}(-f(z))=n(1-F(z))^{n-1}f(z)\ \ \ \square$
ii) 
$\max:\mathbb R^{n}\to\mathbb R$ 
$B_z=\{x_1,\dots,x_n:\max(x_1,\dots,x_{n})\le z\}$
which means that $B_z$ is the set of points in which all components are smaller than $z$ (definition of minimum)
$B_z=(-\infty,z]\times\dotsi\times(-\infty,z]$

we can find the df of $Z$, $F_{Z}=\int\limits_{B_{z}}{\prod\limits_{i=1}^{n}{f(x_i)} dx_{1}dx_{2}\dotsi dx_{n}}=(F(z))^n$ 
Now we can take the derivative:
$f(z)=n(F(z))^{n-1}f(z) \ \ \ \square$
iii) if they are not independent we cannot factorize the pdfs and we would need the joint pdf to be able to calculate the integrals.
iv) Bz??????

---
# Exercise 2.5
## discrete
* Bernoulli: coin toss that either gives heads (1) with probability $\theta$ or tails (0) with probability $1-\theta$
* Binomial: number of successes in $n$ independent trials (that either succeed or fail) each with probability $\theta$, for example number of heads when tossing a coin $n$ times
* NegBin: it's a generalized version of geometric rv that models the number of failures until $r$ successes happen (in $n$ independent binary trials like the binomial). For example the number of trials until we get $r$ non consecutive heads when tossing a coin
* Poisson: number of events that happen independently from each other in a fixed amount of time. For example the number of connections to a server in a second.
## continuous
* Gaussian: for example the height of humans.
* Exponential: for example the time a client waits in queue before being served by a server.
* Gamma: it's a generalization of the exponential distribution. It is also used to model waiting times.
* Weibull: for example it can model the time an electronic device lasts.
* Uniform: in telecommunications it can model the granular error of a symmetrical quantizer.