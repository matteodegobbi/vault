o = c(5.1, 7.4, 10.9, 21.3, 12.3, 15.4, 25.4, 18.2, 17.4, 22.5)

alphas = seq(from = 0.01, to = 100, by = 0.1)

#i)
l_alpha <- function(alphas) {
  loglikGamma = c()
  for (alpha_i in alphas) {
    loglikGamma = append(loglikGamma, sum(log(dgamma(o, alpha_i))))
  }
  return(loglikGamma)
}
###ALTERNATIVA FUNZIONALE SAREBBE AL POSTO DEL LOOP PRECEDENTE
#logL <- function(alpha,y) sum(dgamma(o,alpha,log=TRUE))
#sapply(alphas,logL,y=o)

plot(alphas,
     l_alpha(alphas),
     xlab = expression(alpha),
     ylab = expression(l(alpha)))

#####################################################################
#ii) and iii)
derivative_l_alpha <- function(alphas) {
  return(numDeriv::grad(l_alpha, alphas))
}
observed_info <- function(alphas) {
  return(-numDeriv::grad(derivative_l_alpha, alphas))
}
newton_raphson <- function(starting_value, n_iterations) {
  alfa = starting_value
  for (i in 0:n_iterations) {
    print(alfa)
    alfa = alfa + (derivative_l_alpha(alfa) / observed_info(alfa))
  }
  return(alfa)
}
interval = c(0.01, 100)
uniroot_result = uniroot(derivative_l_alpha, interval = interval)$root
newton_raphson_result = newton_raphson(1, 100)

####################################################
######ALTERNATIVE WITH ANALITICAL DERIVATIVES#######
####################################################
#i) and ii) 
logL <- function(alpha, y)
  sum(dgamma(o, alpha, log = TRUE))

score <- function(alpha, y) {
  n = length(y)
  sum(log(y)) - n * digamma(alpha)
}

Jfun <- function(alpha, y) {
  length(y) * trigamma(alpha)
}

aa <- seq(10, 34, len = 200)
ll_d = sapply(aa, score, y = o)
plot(aa, ll_d, type = "l")

oo <- uniroot(function(x)
  score(x, y = o) - 0, lower = 10, upper = 30)
abline(h = 0, col = 3)
abline(v = oo$root, col = 2)
oo$root
#Newton-Raphson
N = 20
tilde_alpha <- vector(mode = "numeric", N)
tilde_alpha[1] = 1
for (i in 2:N) {
  tilde_alpha[i] = tilde_alpha[i - 1] + (score(tilde_alpha[i - 1], o) / Jfun(tilde_alpha[i -1], o))
  
}

plot(x=1:N, y=tilde_alpha, pch=20)

abline(h = oo$root, col = 2)
#iii)
Jhat=Jfun(oo$root,o)
print(Jhat)
#iv)
lrs <- function(alpha,y,hat_logL){
  -2 * (logL(alpha,o)-hat_logL)
}

hat_logL=logL(oo$root,o)
x=seq(8,25,len=200)
f=sapply(x,lrs,y=o,hat_logL=hat_logL)

plot(x,f,type="l",xlab = expression(alpha))
abline(h=qchisq(0.95,df=1),lty=2)
#now we find where the two functions intersect to find the interval of alphas wanted
lb<- uniroot(function(x)
  lrs(x, y = o,hat_logL = hat_logL ) - qchisq(0.95,df = 1), lower = 10, upper = oo$root-0.001)


ub<- uniroot(function(x)
  lrs(x, y = o,hat_logL = hat_logL) - qchisq(0.95,df = 1), lower = oo$root, upper = 20)

abline(v=lb$root,col=2)
abline(v=ub$root,col=2)
print(lb$root)
print(ub$root)
 