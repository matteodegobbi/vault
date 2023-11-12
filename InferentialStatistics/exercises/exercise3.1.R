o = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)

alphas = seq(from = 0.01, to = 100, by = 0.1)

l_alpha = function(alphas){
  loglikGamma = c()
  for (alpha_i in alphas) {
    loglikGamma = append(loglikGamma,sum(log(dgamma(o,alpha_i))))
  }
  return(loglikGamma)
}



plot(alphas,l_alpha(alphas),xlab = "alpha",ylab = "l(alpha)")

interval = c(0.01,100)
uniroot(loglikGamma,interval = interval)
