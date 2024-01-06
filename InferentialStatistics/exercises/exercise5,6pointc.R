ll_function <- function(obs_x,obs_y,beta_0,beta_1) {
  an <- function(x,y){
    lambdas<- beta_0+beta_1*x
    #print(temp-exp(temp))
    return(lambdas*y-exp(lambdas))
  }
  #print(beta_0)
  #print(beta_1)
  aa <- sum(mapply(an,obs_x,obs_y))-log(prod(sapply(obs_y,factorial)))
  #print(aa)
  return(aa)
}

loglrt<- function(){
  beta_0 <- 3
  beta_1 <- -1.5
  obs_x <- c(0.762 ,1.213 ,1.687 ,1.684 ,1.653 ,1.381 ,0.573 ,1.008 ,1.356, 1.230)
  obs_y <- sapply(exp(beta_1 * obs_x+beta_0),FUN = rpois,n=1)
  #print(obs_y)
  
  result = optim(
    par = c(-1,2),
    fn = function(parameters){-ll_function(obs_x,obs_y, parameters[1], parameters[2])},
    method = "BFGS"
  )
  
  optim_intercept = result$par[1]
  optim_slope = result$par[2]
  
  fixed_beta_1 <- 0
  result_under_theta0 <-  optim(
    par = c(-1),
    fn = function(parameters){-ll_function(obs_x,obs_y,parameters[1],fixed_beta_1)},
    method = "BFGS"
  )
  loglrt_theta <- ll_function(obs_x,obs_y,optim_intercept,optim_slope)
  loglrt_theta0 <- ll_function(obs_x,obs_y,result_under_theta0$par[1],fixed_beta_1)
  xx <- -2*(loglrt_theta0-loglrt_theta)
}
#obs_x <- c(obs_x,obs_x,obs_x,obs_x)
N <- 1e4

generated_llrts <- vector(mode = "double",N)
for (i in 1:N){
  #print(i)
  generated_llrts[i] <- loglrt() 
}

hist(generated_llrts,freq = FALSE,nclass = 100,)
ps <- seq(0,25,0.01)
lines(ps,dchisq(x = ps,df = 1),col='red')
