b=25
c=15
chisq_obs = ((abs(b-c)-1)^2)/(b+c)
sprintf("Value of observed statistic: %.3f",chisq_obs)
pval = 1-pchisq(chisq_obs,df=1)#P(X^2>observedX^2)
sprintf("p-value: %.3f",pval)

