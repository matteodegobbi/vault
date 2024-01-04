N <- 1e4
mu <- 0
sigma_sq_vals <-  c(0.5)#c(0.5,1,2)
n_vals <- c(10, 30)
confidence <- 0.95#1-alpha
alpha <- 1 - confidence
z_wald <- qnorm(1 - alpha / 2)

n_val <- n_vals[2]
for (sigma_sq in sigma_sq_vals) {
  print('------------------------------------------')
  print(sprintf("sigma^2 = %f, n of obs = %d, mu = %f",sigma_sq,n_val,mu))
  expect_len_wald <- 0
  coverage_prob_wald <- 0
  for (i in 1:N) {
    obs <- rnorm(n_val, mean = 0, sd = sqrt(sigma_sq))
    {
      #LRT with quantiles
      
    }
    {
      #wald confidence interval
      sample_average <- mean(obs)
      sigma_hat_sq <- mean((obs - sample_average) ^ 2)
      #asymptotically mle is N(sigma^2,var(mle)) so,
      #se^2=var(mle)=2sigma^4*(n-1)/n^2 and we have:
      se_hat = sqrt(2 * (n_val - 1)) * sigma_hat_sq / n_val
      CI_wald_left <- sigma_hat_sq - z_wald * se_hat
      CI_wald_right <- sigma_hat_sq + z_wald * se_hat
      length_wald <- CI_wald_right - CI_wald_left
      expect_len_wald <- expect_len_wald + length_wald
      if (CI_wald_left <= sigma_sq & CI_wald_right >= sigma_sq){
        coverage_prob_wald <- coverage_prob_wald + 1
      }
    }
  }
  expect_len_wald <- expect_len_wald / N
  coverage_prob_wald <- coverage_prob_wald / N
  print(sprintf("Wald CI: coverage prob=%f, expected length = %f",coverage_prob_wald,expect_len_wald))
}
print(sigma_hat_sq)