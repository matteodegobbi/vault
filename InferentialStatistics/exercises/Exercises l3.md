# Exercise 3.1
i) With the R script
```
o = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)
loglikGamma = c()
alphas = seq(from = 0.01, to = 100, by = 0.1)


for (alpha_i in alphas) {
  loglikGamma = append(loglikGamma,sum(log(dgamma(o,alpha_i))))
}

plot(alphas,loglikGamma,xlab = "alpha",ylab = "l(alpha)")
```
we plot the log likelihood of the observed sample:
![[loglikelihood3.1.png]]
