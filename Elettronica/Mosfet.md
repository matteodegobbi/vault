---
tags: elettronica
---
Definiamo $V_{OV}\triangleq V_{GS}-V_t$
# Regioni di funzionamento canale n
$k_n'=\mu_n C_{ox}$
## Triodo
$i_D=k_n'\frac{W}{L}[V_{OV}\cdot V_{DS}-\frac{V_{DS}^2}{2}]$ se $V_{GS}>V_t,\ V_{DS}<V_{OV}$
## Attiva (Saturazione)
$i_D=k_n'\frac{W}{L}\frac{V_{OV}^2}{2}$ se $V_{GS}>V_t,\ V_{DS}\ge V_{OV}$
## Cutoff/interdizione
$i_D=0$ se $V_{GS}<V_t$
# Regioni di funzionamento canale p
A differenza dell N-Mos si ha:
* $V_{DS}<0$
* $V_{GS}<0$
* $i_D$ è presa uscente
Per le condizioni della zona di funzionamento si può usare il modo di circuiti integrati ovvero: prendo la massima tra $V_{DS}$ e $V_{OV}$ (ovvero la più piccola in valore assoluto) e uso la formula: $i_D=k_p'\frac{W}{L}(V_{OV}-\frac{V_{MAX}}{2})V_{MAX}$ 
lo stesso può essere fatto con un N-Mos ma prendendo la $V_{MIN}$.

$k_p'=\mu_p C_{ox}$
## Triodo
$i_D=k_p'\frac{W}{L}[V_{OV}\cdot V_{DS}-\frac{V_{DS}^2}{2}]$ se $V_{GS}<V_t,\ 0>V_{DS}>V_{OV}$
## Attiva (Saturazione)
$i_D=k_p'\frac{W}{L}\frac{V_{OV}^2}{2}$ se $V_{GS}<V_t,\ V_{DS}< V_{OV}<0$
## Cutoff/interdizione
$i_D=0$ se $V_{GS}>V_t$

# Modulazione di lunghezza di canale
Non idealità del Mosfet, siccome la lunghezza del canale in saturazione/attiva dipende dalla $V_{DS}$ in attiva/saturazione dobbiamo moltiplicare la formula di $i_D$ per il termine correttivo $(1+\lambda |V_{DS}|)$ (il modulo serve nel caso di P-Mos) e quindi si ha:
$i_D=k_p'\frac{W}{L}(\frac{V_{OV}^2}{2})(1+\lambda |V_{DS}|)$ se $V_{GS}<V_t,\ V_{DS}< V_{OV}<0$
$\lambda = [V^{-1}]$