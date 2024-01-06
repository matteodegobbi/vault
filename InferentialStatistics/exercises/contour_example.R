x <- -26:16
z <- outer(x, x, FUN = function(x,y){x^2+2*y^2})
#image(x, x, z)
contour(x, x, z, col = "orange",nlevels = 50,)