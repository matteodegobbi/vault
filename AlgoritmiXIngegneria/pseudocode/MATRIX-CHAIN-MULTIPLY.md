```
//chiamata principale (A,s,1,n)
//A e' la sequenza di matrici la utilizzo come fosse un'array di matrici
MATRIX-CHAIN-MULTIPLY(A,s,i,j)
    if i==j then
        return A[i]
    k=s[i][j]
    return RECT_MUL(MATRIX-CHAIN-MULTIPLY(A,s,i,k),MATRIX-CHAIN_MULTIPLY(A,s,k+1,j)) ```
