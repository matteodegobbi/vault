Alcune [[FFT]] su vettori particolari possono essere calcolate più velocemente.
##### Vettori a componenti uguali
Sia $\vec{a}=(a,a,\dotsb,a)\in \mathbb{C}^n$ allora $FFT(\vec{a})=(a\cdot n,0,\dotsb,0)$
Si prova con matrice di Fourier e ![[Proprietà radici complesse#Lemma di somma]]
##### Vettori con solo la prima componente non nulla

Sia $\vec{b}=(b,0,\dotsb,0)\in \mathbb{C}^n$ allora $FFT(\vec{b})=(b,b,\dotsb,b)$ 
Si prova con la matrice di Fourier.

_I vettori del primo tipo vengono trasformati in vettori del secondo tipo e viceversa_

_Per vettori di questi due tipi nelle trasformate inverse bisogna stare attenti al fattore di scala $\frac{1}{n}$_.

##### Vettori $(n,k)$-sparsi
Siano $n,k$ potenze di 2 con $1\le k \le n$
allora $\vec x$ si dice  $(n,k)$-sparso se $x_i=0$ per $i\ mod\ k\ne 0$ con $0 \le i \le n-1$
Ovvero le uniche componenti di $\vec{x}$ che possono essere diverse da 0 sono quelle di indice multiplo di $k$.
Possiamo usare un algoritmo più efficiente:
Si nota che dato $\vec{x}$ $(n,k)$-sparso allora $\vec{x}^{[1]}=\vec{0}$ e $\vec{x}^{[0]}$ è un vettore $(n/2,k/2)$-sparso. (Prova nel PDF 15.1 indice dispari non può essere multiplo di $k$ che è una potenza di 2).
Avremo $FFT(\vec{0})=\vec{0}$  e quindi  $FFT(\vec{x})=(FFT(\vec{x}^{[0]})|FFT(\vec{x}^{[0]}))$
Come caso base se $k=1$ chiameremo la FFT solita per vettori generici.

Algoritmo:
![[fftSparsa.PNG]]

Ha complessità $T(n,k)=\mathcal{\Theta}(\frac{n}{k}\cdot log\frac{k}{k})$ si può trovare per unfolding con caso base $n=1$.
