o = c(7, 4, 2, 4, 3, 2, 5, 10, 7, 7, 3, 5, 5, 5, 4, 3, 7, 3, 6, 4)


l_lambda = function(lambda,samples) {
  loglikPoi = c()
  for (lambda_i in lambda) {
    loglikPoi = append(loglikPoi, sum(log(dpois(samples, lambda_i))))
  }
  return(loglikPoi)
}

lambdas = seq(from = 0.01, to = 100, by = 0.01)

plot(lambdas,l_lambda(lambdas,o),xlab = "lambda",ylab = "l(lambda)")

derivative_l_lambda = function(lambda,samples) {
  partial_l_lambda = function(lambda) l_lambda(lambda,samples)
  return(numDeriv::grad(partial_l_lambda, lambda))
}

interval = c(0.01, 100)

uniroot_result = uniroot(function(lambda) derivative_l_lambda(lambda,o), interval = interval)$root

resampled_o = sample(o,20,replace = TRUE)
samples=resampled_o
lines(lambdas,l_lambda(lambdas,resampled_o),col="blue")

maximum_likelihood_vector = c()
for(i in (0:1000)){
  resampled_o = sample(o,20,replace = TRUE)
  ML = uniroot(function(lambda) derivative_l_lambda(lambda,resampled_o), interval = interval)$root
  maximum_likelihood_vector=append(maximum_likelihood_vector,ML)
}

hist(maximum_likelihood_vector,freq = FALSE)