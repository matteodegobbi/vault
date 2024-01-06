ll_function <- function(obs_x,obs_y,beta_0,beta_1) {
  an <- function(x,y){
    lambdas<- beta_0+beta_1*x
    #print(temp-exp(temp))
    return(lambdas*y-exp(lambdas))
  }
  #print(beta_0)
  #print(beta_1)
  aa <- sum(mapply(an,obs_x,obs_y))-log(prod(sapply(obs_y,factorial)))
  print(aa)
  return(aa)
}
information_function <- function(obs_x,beta_0,beta_1){
  m00 <- sum(exp(beta_0+beta_1*obs_x)) 
  m10 <- m01 <- sum(obs_x*exp(beta_0+beta_1*obs_x)) 
  m11 <- sum((obs_x^2)*exp(beta_0+beta_1*obs_x))
  return(rbind(c(m00,m01),c(m10,m11)))
}
obs <-
  rbind(
    c(5, 0.762),
    c(2, 1.213),
    c(5, 1.687),
    c(2, 1.684),
    c(2, 1.653),
    c(3, 1.381),
    c(9, 0.573),
    c(7, 1.008),
    c(6, 1.356),
    c(3, 1.23)
  )
dfobs <- data.frame(y = obs[, 1], x = obs[, 2])
model = glm(formula = y ~ x, family = poisson(), dfobs)
glm_intercept = model$coefficients[1]
glm_slope = model$coefficients[2]


plot(dfobs$x, dfobs$y, ylim = c(-1, 10), main = 'Poisson linear fit')
abline(a = glm_intercept, b = glm_slope)

result = optim(
  par = c(-1,2),
  fn = function(parameters){-ll_function(dfobs$x,dfobs$y, parameters[1], parameters[2])},
  method = "BFGS"
)

optim_intercept = result$par[1]
optim_slope = result$par[2]

abline(a = optim_intercept ,b = optim_slope,col='red')
# the 2 ablines coincide!

print(inf_mat_hat<-information_function(obs_x = dfobs$x,beta_0 = optim_intercept, beta_1 = optim_slope))
#eigen(-inf_mat_hat)#all eigenvalues are negative, local maximum

#Now we compute the likelihood ratio test for beta_1 = 0 with the observed data
fixed_beta_1 <- 0
result_under_theta0 <-  optim(
  par = c(2),
  fn = function(parameters){-ll_function(dfobs$x,dfobs$y,parameters[1],fixed_beta_1)},
  method = "BFGS"
)
loglrt_theta <- ll_function(dfobs$x,dfobs$y,optim_intercept,optim_slope)
loglrt_theta0 <- ll_function(dfobs$x,dfobs$y,result_under_theta0$par[1],fixed_beta_1)

#lrt_test_stat <- exp(loglrt_theta0)/exp(loglrt_theta)
#print(lrt_test_stat)

xx <- -2*(loglrt_theta0-loglrt_theta)
example_alpha <- 1-0.99
threshold <- qchisq(p = 1-example_alpha, df = 1)
print(xx)
print(threshold)
print(sprintf('pvalue:%f',1-pchisq(xx,df=1)))