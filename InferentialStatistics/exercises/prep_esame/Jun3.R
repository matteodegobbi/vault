x = c(3.2, 2.3, 3.3, 2.5, 4.4, 2.3, 1.9)
hist(x,breaks = 3)
m = length(x)
t_obs = sqrt(m)*(mean(x)-2)/sqrt(var(x))
qt(df = m-1,p = 0.05)
qt(df = m-1,p = 0.95)

pt(t_obs,df = m-1)

y= c(1.8, 3.1, 4.1, 2.5, 2.7, 3.3, 4.3)
n = length(y)
s_x_sq = var(x)
s_y_sq = var(y)
sp_sq = ((n-1)*s_y_sq+(m-1)*s_x_sq)/(n+m-2)

t_obs = (mean(x)-mean(y))/sqrt(sp_sq*(1/m+1/n))
t_quantile = qt(df = n+m-2,p = 1-0.05/2)

(mean(x)-mean(y))-t_quantile*sqrt(sp_sq*(1/m+1/n))
(mean(x)-mean(y))+t_quantile*sqrt(sp_sq*(1/m+1/n))
t.test(x=x,y=y,var.equal = TRUE)

var.test(x,y)