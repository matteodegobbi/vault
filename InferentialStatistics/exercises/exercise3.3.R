o = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)
l_lambda = function(alpha, beta, samples) {
  loglikWei = c()
  for (alpha_i in alpha) {
    for (beta_i in beta) {
      loglikWei = append(loglikWei, sum(log(dweibull(
        samples, shape = alpha_i,scale = beta_i
      ))))
    }
  }
  return(loglikWei)
}
alphas = seq(0.01,6,0.01)
betas = seq(12,22,0.01)
a=l_lambda(alphas,betas,o)