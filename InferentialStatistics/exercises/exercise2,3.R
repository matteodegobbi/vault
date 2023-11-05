x <- c(8.935, 0.492, 6.951, 4.102, 0.111, 2.699, 3.255, 6.254, 2.120, 29.389)
print(x)

#qqplot(x,qdist=qexp(p,rate=1))

#ecdf(x)


p=ppoints(length(x))
q <- quantile(x,p) 
plot(qexp(p,rate=1) ,q, main="qqplot lambda=1",xlab="Theoretical Quantiles",ylab="Sample Quantiles")
#qqline(q, distribution=qexp)

#boxplot(x = x)

fn=ecdf(x)

fn(5.25)