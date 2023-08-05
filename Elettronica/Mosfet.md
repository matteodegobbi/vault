---
tags: elettronica
---
Definiamo $V_{OV}\triangleq |V_{GS}-V_t|$
# NMOS: Regioni di funzionamento canale n
![[nmos.png]]
* $V_{DS}>0$
* $V_{GS}>0$
* $i_D, i_G$ sono entranti mentre $i_S$ è uscente
* Il contatto di bulk è a massa
$k_n'=\mu_n C_{ox}$
## Triodo
$i_D=k_n'\frac{W}{L}[V_{OV}\cdot V_{DS}-\frac{V_{DS}^2}{2}]$ se $V_{GS}>V_t,\ V_{DS}<V_{OV}$
## Attiva (Saturazione)
$i_D=k_n'\frac{W}{L}\frac{V_{OV}^2}{2}$ se $V_{GS}>V_t,\ V_{DS}\ge V_{OV}$
## Cutoff/interdizione
$i_D=0$ se $V_{GS}<V_t$
# PMOS: Regioni di funzionamento canale p
![[pmos.png]]
A differenza dell N-Mos si ha:
* $V_{DS}<0$
* $V_{GS}<0$
* $i_D$ è presa uscente (tutte le correnti sono prese con verso opposto a quelle nel N-Mos)
* Il contatto di bulk è messo a Vdd
Per le condizioni della zona di funzionamento si può usare il modo di circuiti integrati ovvero: prendo la massima tra $V_{DS}$ e $-V_{OV}$ (ovvero la più piccola in valore assoluto) e uso la formula: $i_D=k_p'\frac{W}{L}(-V_{OV}-\frac{V_{MAX}}{2})V_{MAX}$ 
lo stesso può essere fatto con un N-Mos ma prendendo la $V_{MIN}$ (ricorda che $V_{OV}$ è definita come valore assoluto quindi ci va il meno).

$k_p'=\mu_p C_{ox}$
Attenzione: d'ora in poi tutti i $V_{OV}$ sono con un $-$ davanti perché l'abbiamo definita in valore assoluto.
## Triodo
$i_D=k_p'\frac{W}{L}[-V_{OV}\cdot V_{DS}-\frac{V_{DS}^2}{2}]$ se $V_{GS}<V_t,\ 0>V_{DS}>-V_{OV}$
## Attiva (Saturazione)
$i_D=k_p'\frac{W}{L}\frac{V_{OV}^2}{2}$ se $V_{GS}<V_t,\ V_{DS}< -V_{OV}<0$
## Cutoff/interdizione
$i_D=0$ se $V_{GS}>V_t$

# Non idealità del Mosfet 
![[Non idealità nei transistor#MOSFET Modulazione di lunghezza di canale]]

