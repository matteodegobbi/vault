bar_y = 0.05
bar_x = 0.1
s_y_sq = 0.15
s_x_sq = 0.05
n = 25
m = 10 
#######assuming equal variances:
s_p_sq = ((n-1)*s_y_sq + (m-1)*s_x_sq)/(n+m-2)
t_obs = abs(bar_x-bar_y)/sqrt(s_p_sq*(1/m+1/n))

p_val = 1 - pt(q = t_obs,df = n+m-2) + pt(q=-t_obs,df = n+m-2)
p_val
#######not assuming
nu = ((s_x_sq/m+s_y_sq/n)^2)/(s_x_sq^2/(m^2 * (m-1))+s_y_sq^2/(n^2 * (n-1))) 
t_obs_prime = abs(bar_x-bar_y)/sqrt(s_x_sq/m + s_y_sq/n)

p_val_prime = 1 - pt(q = t_obs_prime,df = nu) + pt(q=-t_obs_prime,df = nu)
p_val_prime