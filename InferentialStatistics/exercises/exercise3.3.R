# o = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)
# l_lambda = function(alpha, beta, samples) {
#   loglikWei = c()
#   for (alpha_i in alpha) {
#     for (beta_i in beta) {
#       loglikWei = append(loglikWei, sum(log(dweibull(
#         samples, shape = alpha_i,scale = beta_i
#       ))))
#     }
#   }
#   return(loglikWei)
# }
# alphas = seq(0.01,6,0.01)
# betas = seq(12,22,0.01)
# a=l_lambda(alphas,betas,o)

observed_samples = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)
like_wei <- function(sample, alpha, beta) {
  return(prod((
    sapply(sample, dweibull, shape = alpha, scale = beta)
  )))
}

log_like_wei <- function(sample, alpha, beta) {
  return(sum(log(
    sapply(sample, dweibull, shape = alpha, scale = beta)
  )))
}


vec_like_wei = Vectorize(function(alpha, beta)
  like_wei(observed_samples, alpha, beta))
vec_log_like_wei = Vectorize(function(alpha, beta)
  log_like_wei(observed_samples, alpha, beta))

alphas = seq(from = 0 + 0.1, to = 10, by = 0.1)
betas = seq(from = 10 + 0.1, to = 28, by = 0.1)
z = outer(
  alphas,
  betas,
  FUN = function(alphas, betas)
    vec_log_like_wei(alpha = alphas, beta = betas)
)
contour(alphas, betas, z, nlevels = 100, zlim = (-70:0))

alphas = seq(from = 1 + 0.1, to = 6, by = 0.1)
betas = seq(from = 12 + 0.1, to = 22, by = 0.1)
z = outer(
  alphas,
  betas,
  FUN = function(alphas, betas)
    vec_like_wei(alpha = alphas, beta = betas)
)
contour(alphas, betas, z, nlevels = 35)

######################
llikeF<-function(v) {
  return(sum(log(dweibull(observed_samples,v[1],v[2]))))
}
hessianLlikeF <- function(v) {
  return(numDeriv::hessian(llikeF, v))
}
gradientLlikeF<- function(v) {
  return(numDeriv::jacobian(llikeF, v))
}
root = c(2,17)
for (i in 0:1000){
  gradient=gradientLlikeF(root)
  inverseHess=solve(hessianLlikeF(root))
  root = root - inverseHess%*%t(gradient) 
}

print(root)

