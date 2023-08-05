---
tags: elettronica
---
![[npn.png]]
## Modello BJT valido in tutte le zone di funzionamento:
$I_F=I_{S_0}(e^{\frac{V_{BE}}{U_T}}-1)$, $I_R=I_{S_0}(e^{\frac{V_{BC}}{U_T}}-1)$ e $I_{S_0}=\alpha_T I_S$
![[modelloGeneraleBJT.png]]
## Zona attiva diretta
Il diodo BE è in diretta mentre BC è in inversa.
Le condizioni perché valgano queste due ipotesi sono:
$$\begin{cases} i_B>0 \\
V_{BC}\le V_{BCON} \leftrightarrow V_{CE}\ge V_{CESAT}
\end{cases}$$
con $V_{CESAT}\triangleq V_{BEON}-V_{BCON}$
![[zadBJT.png]]
## Cutoff o interdizione
Entrambi i diodi sono in inversa.
Le condizioni sono:
$$\begin{cases} V_{BE} < V_{BEON} \\
V_{BC} < V_{BCON} = V_{BEON}-V_{CESAT}
\end{cases}$$
![[cutoffBJT.png]]
## Zona di saturazione 
Sia il diodo BE che BC sono in diretta.
Le condizioni sono:

$$\begin{cases} i_B>0 \\
i_C < \beta_F i_B 
\end{cases}$$
![[satBJT.png]]
Notiamo come in saturazione si ha che $V_{CE}=V_{CESAT}\triangleq V_{BEON}-V_{BCON}$, ciò da il nome a $V_{CESAT}$.
Negli esercizi è più utile il secondo modello perché spesso viene data $V_{CESAT}$.
Il motivo della seconda condizione è dimostrato sul quaderno (Lezione 10).
## Zona attiva inversa 
Non ci interessa un modello per questa zona in quanto non viene utilizzata negli amplificatori.

# Non idealità del BJT 
![[Non idealità nei transistor#BJT Effetto Early]]