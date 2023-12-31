---
tags: elettronica
---
![[pnp.png]]
## Modello BJT valido in tutte le regioni di funzionamento
$I_F=I_{S_0}(e^{\frac{V_{EB}}{U_T}}-1)$, $I_R=I_{S_0}(e^{\frac{V_{CB}}{U_T}}-1)$ e $I_{S_0}=\alpha_T I_S$
![[modelloGenericopnp.png]]
## Zona attiva diretta
Condizioni:
$$\begin{cases} i_B>0 \\
V_{CB}\le V_{CBON} \leftrightarrow V_{EC}\ge V_{ECSAT}
\end{cases}$$
con $V_{ECSAT}\triangleq V_{EBON}-V_{ECON}$
![[ZADpnp.png]]
## Cutoff o interdizione
Condizioni:
$$\begin{cases} V_{EB} < V_{EBON} \\
V_{CB} < V_{CBON} = V_{EBON}-V_{ECSAT}
\end{cases}$$
![[cutoffpnp.png]]
## Zona di saturazione
Condizioni: 
$$\begin{cases} i_B>0 \\
i_C < \beta_F i_B 
\end{cases}$$
![[SATpnp.png]]
## Zona attiva inversa 
Non ci interessa un modello per questa zona in quanto non viene utilizzata negli amplificatori.

# Non idealità del BJT 
![[Non idealità nei transistor#BJT Effetto Early]]