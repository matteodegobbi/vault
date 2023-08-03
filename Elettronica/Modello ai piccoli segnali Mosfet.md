---
tags: elettronica
---
[[Mosfet]]
![[modelloMOSpiccoliSegnali.png]]
# Come si ricava questo modello
Date:
$\cases{v_{GS}(t)=V_{GS}+v_{gs}(t)\\v_{DS}(t)=V_{DS}+v_{ds}(t)}$
$\cases{i_D = \frac{k_n}{2}(v_{GS}-V_{t})^2(1+\lambda v_{DS})\\ i_g=0}$
Le varie $g$ del modello si derivano calcolando le derivate di $i_D(v_{GS},v_{DS})$ perché è una espansione del prim'ordine in serie di Taylor (poi si moltiplica e divide per la stessa quantità in modo da trovare le espressioni sotto).
# Equazioni linearizzate del Mosfet in saturazione/attiva:
$\cases{i_D=I_D+g_m v_{gs}+g_d v_{ds}\\ i_G= 0}$
$g_d=\frac{I_D}{V_A+V_{DS}}\simeq \frac{I_D}{V_A} = \lambda I_D$ con $V_A \triangleq \frac{1}{\lambda}$ 
$g_m=k_n V_{OV}=\frac{2 I_D}{V_OV}=\sqrt{2k_n I_D}$ va scelta la formula in base ai dati dell'esercizio a disposizione
$r_0=\frac{1}{g_d}=\frac{V_{DS}+V_A}{I_D}\simeq \frac{V_A}{I_D}$
# Uguaglianza modello N-Mos e P-Mos
A differenza del modello dc i modelli ai piccoli segnali di N-Mos e P-Mos sono uguali perché basta invertire tutte le correnti e le tensioni.