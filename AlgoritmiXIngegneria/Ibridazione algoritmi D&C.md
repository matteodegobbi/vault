Ho due algoritmi: A D&C che ha $T_A(n)$ asintoticamente minore e B con $T_B(n)$ con una costante minore davanti al termine di grado maggiore.

Ibridazione significa mantenere la  struttura dell'algoritmo A ma utilizzare l'algoritmo B per risolvere tutte le chiamate ricorsive con taglia$\le n_0$, cioè il caso di base sarà l'algoritmo B.

Con l'ibridazione posso ottenere un algoritmo con complessità asintotica uguale ad A ma con una costante più bassa. 

Come trovare la migliore $n_0$ tra i due algoritmi?
1. Risolvo la ricorrenza dell'algoritmo ibridato usando come caso base $n_0$ e $T_0=T(n_0)$ trovando una complessità $T(n)$ espressa in funzione di $n$ e $n_0$.
2. Definisco $g(n_0)$ il coefficiente del termine di grado superiore della complessità dell'algoritmo ibridato.
3. Studio di funzione usando le derivate di $g(n_0)$ e trovo il minimo di $g$.
4. Il minimo trovato però deve rispettare le ipotesi sulla taglia dell'algoritmo, quindi ad esempio se $n$ deve essere una potenza di 2, considero le due potenze di 2 più vicine al minimo e prendo quella che minimizza $g$ tra le due (ad esempio minimo in $n=3$ confronto $g(2),g(4)$ e scelgo $n_0=2$ oppure $n_0=4$)