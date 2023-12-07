x = rnorm(10000,3,3)
sample_average = mean(x)
stat_power = mean(x^2)
MLE  = (-sample_average+sqrt(sample_average^2+4*stat_power))/2
print(MLE)