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
# right_CI = sample_max * exp(qchisq(p = 1 - alpha, df = 1) / (2 * n))
abline(v = right_CI, col = 'red')
sprintf("[%f,%f]", sample_max, right_CI)