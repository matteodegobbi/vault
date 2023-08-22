# Specchio di tipo [[Mosfet#NMOS Regioni di funzionamento canale n|n]]
![[specchioMOSN.png]]
$M_1,M_2$ hanno lo stesso $k_n',V_t,L$ e $m \triangleq \frac{W_2}{W_1}$
## dc
$I_O= m\  I_{REF}$  se $I_{REF}>0,\ V_O > V_{OV}$ 
## ac
in ac lo specchio di funziona da amplificatore di corrente con resistenza d'ingresso $R_i=(r_{o1}//\frac{1}{g_m}) \simeq \frac{1}{g_m}$
![[modelloAcSpecchioMOSN.png]]
se $i_R=I_R$ ovvero $i_r=0$ allora in ac lo specchio di corrente si riduce a $r_{o2}$
# Specchio di tipo [[Mosfet#PMOS Regioni di funzionamento canale p|p]]
A differenza dello specchio di tipo n il carico va connesso sotto allo specchio.
Vale sempre $I_O= m\  I_{REF}$ ma con le condizioni se $I_{REF}>0,\ V_O < V_{OV}$ (ricordando che $V_{OV}$ è un valore assoluto) 
![[specchioMOSP.png]]
Il modello ac è uguale allo specchio n.
# Accuratezza del fattore di specchio m
##########################
# Specchio Cascode
Risolve alcuni problemi presenti negli specchi n e p([[#Accuratezza del fattore di specchio m]]):
* Equalizza $V_{DS1}$ e $V_{DS2}$ eliminando l'errore dovuto alla [[Non idealità nei transistor#MOSFET Modulazione di lunghezza di canale | modulazione di lunghezza di canale]].
* Aumenta la resistenza di uscita $R_O \gtrsim 100 r_{02}$.
![[specchioCASCODE.png]]
$I_o= m\  I_{REF} +(\frac{V_o-V_I}{R_O})$
con $R_O \simeq (g_{m4} r_{o4})\cdot r_{o2}$ senza approssimazione sarebbe $r_{o2}+r_{o4}+(g_{m4} r_{o4})\cdot r_{o2}$
# Specchio [[BJT]]
![[specchioBJT.png]]
$Q_1,Q_2$hanno gli stessi $\beta, I_{S0}$ con $I_S = I_{S0}A_E$ e $m=\frac{A_{E2}}{A_{E1}}$ 
dall'analisi dc
$I_o=m I_R \cdot (\frac{1}{1+\frac{1+m}{\beta}})$

Beta helper lo metto?????????????

$I_o=m I_R \cdot (\frac{1}{1+\frac{1+m}{\beta(\beta+1)}})$

