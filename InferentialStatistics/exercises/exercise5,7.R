boot_time <-
  c(14.87, 7.13, 6.46, 6.45, 9.41, 8.21, 11.18, 14.28, 6.36, 17.98)
ll_function <- function(x, alpha, beta) {
  return(sum(dgamma(
    x,
    shape = alpha,
    rate = beta,
    log = TRUE
  )))
}
get_ll_vec_function_closure <- function(obs_boot_time){
  return(Vectorize(function(alpha,beta){ll_function(obs_boot_time,alpha,beta)}))
}
result <- optim(
  par = c(0.15, 0.1),
  method = 'BFGS',
  fn = function(params) {
    -ll_function(x = boot_time,
                 alpha = params[1],
                 beta = params[2])
  }
)
#boot_time <- sample(boot_time,500,replace = TRUE)
print(result)
#hist(boot_time,freq = FALSE,nclass = 5)
xx <- seq(0, 20, 0.01)
plot(xx, dgamma(xx, shape = result$par[1], rate = result$par[2]))

mu_hat <- result$par[1] / result$par[2]
#(a)  alpha/beta and mean are the same
print(mu_hat)
print(mean(boot_time))
########

#the esitimates for alpha and beta I found are the same as the fitdistr ones
result_MASS <- MASS::fitdistr(x = boot_time, densfun = 'gamma')
print(result_MASS$estimate)
print(result$par)
###########################
#(b)maybe this plot is useless
confidence <- 0.95
threshold <- qchisq(confidence, df = 1)
logLtheta_hat <-
  ll_function(boot_time, alpha = result$par[1], beta = result$par[2])

print(logLtheta_hat)
x <- seq(2.0,13,0.01)
y <- seq(0.1,1.5,0.01)
z <- outer(x,y,FUN = get_ll_vec_function_closure(boot_time))
z <- -2*(z-logLtheta_hat)
contour(x,y,z,nlevels = 25,zlim =c(0,threshold+50))
contour(x,y,z,nlevels = 1,zlim =c(threshold-0.001,threshold+0.001),add = TRUE,col = 'blue')
points(result$par[1],result$par[2],col='red', pch = 3 )

#(b) using wald test
confidence <- 0.95
#sigma_hat_sq <- mean((boot_time-mean(boot_time))^2)
n <- length(boot_time)
se_hat <- sqrt(sigma_hat_sq/n)
#print(se_hat)
z_quantile <- qnorm(1-(1-confidence)/2)
print(sigma_hat_sq)
left_CI <- mu_hat - z_quantile*se_hat
right_CI <- mu_hat + z_quantile*se_hat
print(sprintf("wald CI for mu_hat=%f ,[%f,%f]",mu_hat,left_CI,right_CI))
#(c)
print('probability that boot takes more than 30s')
print(1 - pgamma(
  q = 30,
  shape = result$par[1],
  rate = result$par[2]
))
