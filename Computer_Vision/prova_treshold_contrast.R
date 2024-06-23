x = runif(10000,max=255)

print("-------Before thresholding--------")
cat("media di x:",mean(x),"\n")
cat("varianza(RMSC) di x:",var(x),"\n")

print("-------After thresholding--------")
xt = sapply(x, function(xx) if(xx < 127) 0 else 255)
cat("media di x thresholded:",mean(xt),"\n")
cat("varianza(RMSC) di x thresholded:",var(xt),"\n")
