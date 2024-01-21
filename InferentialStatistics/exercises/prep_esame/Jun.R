##q1

obs = c(16.1, 15.6, 21.2, 18.3, 14.8, 39.8, 34.8, 27.6)
hist(obs,breaks = 5)
theta_mm = (mean(obs)*3/gamma(4/3))^3
theta_mm

tau_hat = mean(obs^3)
tau_hat

n = length(obs)
J_hat = -n/tau_hat^2 + 2*(n/tau_hat^2) 

se_hat = 1/sqrt(J_hat)
se_hat^2
  
alpha = 0.05
z = qnorm(1-alpha/2)

(tau_hat-z*se_hat)^(1/3)
(tau_hat+z*se_hat)^(1/3)


#last part of q1
mu = mean(obs)
sigma_sq = var(obs)
qqnorm(y = obs)
abline(a=0,b=1)