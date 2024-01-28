hss = matrix(nrow = 3,c(24,300,4900,300,4900,90000,4900,90000,1763020))
beta0 = 29.02
beta1=1.96
beta2=-0.094
times = seq(0,24,0.001)
plot(times,beta0+beta1*times+beta2*times^2)
pm2 = function(t){
  return(-(beta0+beta1*t+beta2*t^2))
}
opt = optim(par = 0,fn = pm2, method = 'BFGS')
invJ = solve(hss)
sebeta2 = sqrt(invJ[3,3])
z = qnorm(1-0.05/2)
sebeta2*z
beta2-sebeta2*z
beta2+sebeta2*z
obs = c(30,23,24,45,24,34,50,52)
ecdfn = ecdf(obs) 