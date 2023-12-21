k = 1 
for(k in seq(1,20,0.01)){
  x <- seq(k-2*k,k+2*k,0.1)
  y <- dchisq(x,df = k)
  plot(x,y,type = 'l')
  Sys.sleep(0.001)
  
}


