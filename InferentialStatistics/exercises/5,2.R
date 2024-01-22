bar_x = 6
bar_y = 2
m=15
n=10
theta_0 = (m*bar_x+n*bar_y)/(m+n/2)

lambda = (exp((-m-n/2)*theta_0)*theta_0^(m*bar_x+n*bar_y)*(1/2)^(n*bar_y))/(exp(-m*bar_x)*bar_x^(m*bar_x)*exp(-n*bar_y)*bar_y^(n*bar_y))
lambda
-2*log(lambda)