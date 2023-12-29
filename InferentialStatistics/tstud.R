degrees_freedom = 5
x <- seq(-4,4,0.01)
plot(dt(x = x,df = degrees_freedom),x = x)

left_quant = qt(p = 0.05,df = degrees_freedom)
abline(v=left_quant,col = 'blue')

right_quant = qt(p = 0.95,df = degrees_freedom)
abline(v=right_quant,col = 'red')
