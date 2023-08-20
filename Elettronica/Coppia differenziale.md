Serve a amplificare un segnale differenziale.
################DISEGNO sia con generatore che con specchio di corrente

In modo che funzioni correttamente deve valere che $V_{tn}+V_{OV}+V_{OV4}<V_{IC}<V_{DD}-R_D \frac{I_A}{2}+V_{tn}$
Dall'analisi ac di modo differenziale e di modo comune otteniamo che:
* $R_{id}=\infty$
* $R_{od}=2(r_o//R_D)$
* $A_{dd}=\frac{v_{od}}{v_{id}}\bigr \rvert_{v_{ic}=0}=-g_m (r_o // R_D)$ cioè come uno stadio a source comune senza resistenza di degenerazione (spesso approssimiamo con $r_o=\infty$)
* $A_{cc}=\frac{v_{oc}}{v_{ic}}\bigr \rvert_{v_{id}=0}= - \frac{g_m R_D}{1+g_m 2 r_{o4}}$ ovvero come uno stadio CSR con resistenza di degenerazione uguale a $R_S = 2r_{o4}$ Attenzione $r_{o4}$ è quella dello specchio di corrente 
* $A_{dc}=\frac{v_{od}}{v_{ic}}\bigr \rvert_{v_{id}=0}=0$
* $A_{cd}=\frac{v_{oc}}{v_{id}}\bigr \rvert_{v_{ic}=0}=0$
Attenzione $A_{cd}=A_{dc}=0$ solo se i due transistor sono perfettamente identici.
Il CMRR indica quanto è buona la coppia differenziale: $CMRR \triangleq |\frac{A_{dd}}{A_{cc}}|$.

Molto spesso al posto delle resistenze $R_D$ nei circuiti integrati si usano degli specchi di corrente.
