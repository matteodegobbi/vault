x = c(3.2, 2.3, 3.3, 2.5, 4.4, 2.3, 1.9)
hist(x,breaks = 3)
n = length(x)
t_obs = sqrt(n)*(mean(x)-2)/sqrt(var(x))
qt(df = n-1,p = 0.05)
qt(df = n-1,p = 0.95)

pt(t_obs,df = n-1)