somma = 0
for i in range(9):
    somma+=(2**i)*(2**(i+1))
print(somma*36/1e6)
