likelihood_f <- function(theta){
  n = 30
  bar_x = 10
  return((1-theta)^n * theta^(n*(bar_x -1)))
}

theta_seq = seq(0.75,1,0.001)
likelihood_theta = likelihood_f(theta_seq)
plot(theta_seq,likelihood_theta,main = 'likelihood')

index_max = which.max(likelihood_theta)
abline(v=theta_seq[index_max],col='red')
abline(h=likelihood_theta[index_max],col='red')
#####################################

rm(list = ls())


ell_f <-function(theta){
  n=30
  bar_x = 10
  n*log(1-theta)+n*(bar_x-1)*log(theta)
}
theta_seq = seq(0.89,0.91,0.00001)

alpha = 0.9
threshold = qchisq(p = 1-alpha,df = 1)
MLE = 0.9
tlambda = -2*ell_f(theta_seq)+2*ell_f(MLE)
plot(theta_seq,tlambda,main = '-2 log(lambda) and chisq_1,1-alpha threshold',lwd=1,lty=1,type = 'l')
abline(h=threshold,col='green')

confidence_interval = theta_seq[tlambda<threshold]
sprintf('[ %f , %f ]',confidence_interval[1],confidence_interval[length(confidence_interval)])
sprintf('[ %f , %f ]',min(confidence_interval),max(confidence_interval))

