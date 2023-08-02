---
tags: elettronica
---
# BJT: Effetto Early
Non idealità del BJT, in regione di attiva diretta nel [[BJT]] la regione di svuotamento base collettore diventa più grande riducendo lo spessore effettivo della base. Moltiplichiamo la espressione della $i_C$ per un termine correttivo $(1+\frac{V_{CE}}{V_A})$ e quindi si ha:
* $i_C\simeq I_{S0}e^\frac{V_{BE}}{U_T}(1+\frac{V_{CE}}{V_A})$
* $i_B\simeq \frac{I_{S0}}{\beta_F}e^\frac{V_{BE}}{U_T}$
$V_A= [V]$
Da notare che l'espressione per $i_B$ non va cambiata con l'effetto Early.
Nella analisi dc spesso l'effetto Early viene trascurato.
# MOSFET: Modulazione di lunghezza di canale
Non idealità del [[Mosfet]], siccome la lunghezza del canale in saturazione/attiva dipende dalla $V_{DS}$ in attiva/saturazione dobbiamo moltiplicare la formula di $i_D$ per il termine correttivo $(1+\lambda |V_{DS}|)$ (il modulo serve nel caso di P-Mos) e quindi si ha:
$i_D=k_p'\frac{W}{L}(\frac{V_{OV}^2}{2})(1+\lambda |V_{DS}|)$ se $V_{GS}<V_t,\ V_{DS}< V_{OV}<0$
$\lambda = [V^{-1}]$
Nella analisi dc spesso la modulazione di lunghezza di canale viene trascurata.