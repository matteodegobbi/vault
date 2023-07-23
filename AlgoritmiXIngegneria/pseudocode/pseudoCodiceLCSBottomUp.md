codice bottom up LCS
```
LCS(x,y)//solo costi
    m=|x|
    n=|y|
    for i=1 to m
        l[i][0]=0
    for j=1 to n 
        l[0][j]=0

    for i=1 to m
        for j=1 to n
        if y[n]==x[m] then
            l[i][j]=l[i-1][j-1]+1
        else if l[i-1][j]>l[i][j] then
            l[i][j]=l[i-1][j]
        else
            l[i][j]=l[i][j-1]

    return l[m][n]
