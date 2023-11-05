get_theta <- function(x_1,x_2,x_3){
  beta0=0.5
  beta1=-1
  beta2=1
  beta3=0.1
  mu=beta0+beta1*x_1+beta2*x_2+beta3*x_3
  return(1/(1+exp(-mu)))
}


tabella=read.table('C:\\Users\\matteo\\Desktop\\eggs.txt')



number_of_pred_M=0
for(i in (2:101)){
  theta_i=get_theta(as.double(tabella[i,"V1"]),as.double(tabella[i,"V2"]),as.double(tabella[i,"V3"]))
  predictedsex=rbinom(1,1,prob=theta_i)
  cat(predictedsex)
  cat(" ")
  number_of_pred_M=number_of_pred_M+predictedsex
}
print("number of males")
print(number_of_pred_M)


qvolume=as.double(quantile(as.double(tabella[2:101,1]))[2])
qheight=as.double(quantile(as.double(tabella[2:101,2])))[2]
qrough=as.double(quantile(as.double(tabella[2:101,3])))[2]
theta_quartile_egg=get_theta(qvolume,qheight,qrough)
rbinom(1,1,prob=theta_quartile_egg)