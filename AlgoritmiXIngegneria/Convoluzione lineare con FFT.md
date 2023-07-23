Per poter convolvere 2 vettori lunghi $n$ in $\mathcal{O}(n \cdot logn)$ possiamo calcolare la [[FFT]] di entrambi i vettori con un padding di $n$ zeri (per avere la rappresentazione estesa), moltiplicare le due trasformate componente per componente e calcolare la FFT inversa del vettore risultante.

Se la lunghezza dei due vettori $n$ non è una potenza di 2 basta aggiungere un padding di zeri fino a fare arrivare alla prossima potenza di 2. La nuova lunghezza si trova così: ![[Potenza di 2 più vicina a un numero]]
