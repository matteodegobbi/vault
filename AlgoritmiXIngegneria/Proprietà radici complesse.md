---
tags: algoritmiXingegneria 
---
##### Radici $n$-esime dell'unità sono a modulo $n$:
${\omega_n^{k}=\omega_n^{k\ mod\ n}}$

##### Modulo numeri negativi:
${-x\ mod \ n= n-x \ mod \ n}$ e se ${1 \le x \le n-1:\ -x\ mod\ n=n-x}$

##### Radici negative dell'unità:
${\omega_n^{-j}=\omega_n^{n-j}=\omega_n^{-j \  mod \  n}}$

##### Radice principale negativa 
(definizione di segnali e sistemi) noi la usiamo nella $DFT^{-1}$ : ${\bar \omega_n=\omega_n^{-1}=\omega_n^{n-1} }$

##### Lemma di cancellazione: ${\forall n, d\in \mathbb{N}^+,\ \forall k \in \mathbb{Z}: \omega_{dn}^{dk}=\omega_n^k}$
corollario: ${\forall n \in \mathbb{N}^+}$ pari ${\omega_n^{n/2}=\omega_2=-1}$

##### Lemma di dimezzamento: 
Sia $n$ pari allora per ${0\le i\le\frac{n}{2}-1:\ (\omega_n^i)^2=((\omega_n^{i+\frac{n}{2}})^2)=\omega_{\frac{n}{2}}^i}$
ovvero sto mettendo in relazione radici $n$-esime e radici $\frac{n}{2}$-esime ![[lemmaDimezzamento.PNG]]

##### Lemma di somma: 
Sia ${n \in \mathbb{N}^+,\  k\in\mathbb{Z}}$ allora:${\displaystyle\sum_{j=0}^{n-1}(\omega_n^k)^j=\cases{n\;\;\;  \text{ se } k \text{ è multiplo di } n  \\ 0\;\;\;  \text{ altrimenti}}}$



