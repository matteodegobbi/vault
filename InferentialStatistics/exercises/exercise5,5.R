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
  print(sprintf("sigma^2 = %f, n of obs = %d, mu = %f", sigma_sq, n_val, mu))
  expect_len_wald <- 0
  coverage_prob_wald <- 0
  expect_len_lrtq <- 0
  coverage_prob_lrtq <- 0
  for (i in 1:N) {
    obs <- rnorm(n_val, mean = 0, sd = sqrt(sigma_sq))
    sample_average <- mean(obs)
    sigma_hat_sq <- mean((obs - sample_average) ^ 2)
    {
      #LRT with quantiles
      chi_left <- qchisq(p = 1 - alpha / 2, df = n_val - 1)
      chi_right <- qchisq(p = alpha / 2, df = n_val - 1)
      CI_lrtq_left <- n_val * sigma_hat_sq / chi_left
      CI_lrtq_right <- n_val * sigma_hat_sq / chi_right
      length_lrtq <- CI_lrtq_right - CI_lrtq_left
      expect_len_lrtq <- expect_len_lrtq + length_lrtq
      if (CI_lrtq_left <= sigma_sq & CI_lrtq_right >= sigma_sq) {
        coverage_prob_lrtq <- coverage_prob_lrtq + 1
      }
    }
    {
      #wald confidence interval
      #asymptotically mle is N(sigma^2,var(mle)) so,
      #se^2=var(mle)=2sigma^4*(n-1)/n^2 and we have:
      se_hat = sqrt(2 * (n_val - 1)) * sigma_hat_sq / n_val
      CI_wald_left <- sigma_hat_sq - z_wald * se_hat
      CI_wald_right <- sigma_hat_sq + z_wald * se_hat
      length_wald <- CI_wald_right - CI_wald_left
      expect_len_wald <- expect_len_wald + length_wald
      if (CI_wald_left <= sigma_sq & CI_wald_right >= sigma_sq) {
        coverage_prob_wald <- coverage_prob_wald + 1
      }
    }
  }
  expect_len_wald <- expect_len_wald / N
  coverage_prob_wald <- coverage_prob_wald / N
  print(
    sprintf(
      "Wald CI: coverage prob=%f, expected length = %f",
      coverage_prob_wald,
      expect_len_wald
    )
  )
  expect_len_lrtq <- expect_len_lrtq / N
  coverage_prob_lrtq <- coverage_prob_lrtq / N
  print(
    sprintf(
      "LRT with quantiles CI: coverage prob=%f, expected length = %f",
      coverage_prob_lrtq,
      expect_len_lrtq
    )
  )
}
print(sigma_hat_sq)