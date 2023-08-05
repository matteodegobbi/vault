---
tags: elettronica
---
[[BJT]]
![[modelloBJTpiccoliSegnali.png]]
# Come si ricava questo modello
Date:
$\cases{v_{BE}(t)=V_{BE}+v_{be}(t)\\v_{CE}(t)=V_{CE}+v_{ce}(t)}$
$\cases{i_C\simeq I_{S0}e^\frac{v_{BE}}{U_T}(1+\frac{v_{CE}}{V_A})\\ i_B\simeq \frac{I_{S0}}{\beta_F}e^\frac{v_{BE}}{U_T}}$
Le varie $g$ del modello si derivano calcolando le derivate di $i_C(v_{BE},v_{CE})$ e di $i_B(v_{BE})$ perché sono espansioni del prim'ordine in serie di Taylor (poi si moltiplica e divide per la stessa quantità in modo da trovare le espressioni sotto).
# Equazioni linearizzate del BJT in ZAD:
$\cases{i_C=I_C+g_m v_{be}+g_d v_{ce}\\ i_B= I_B + g_\pi v_{be}}$
$g_d=\frac{I_C}{V_A+V_{CE}}\simeq \frac{I_C}{V_A}$
$g_m=\frac{I_C}{U_T}$
$g_\pi\simeq \frac{g_m}{\beta_F}=\frac{I_C}{U_T \beta_F}$
$r_{\pi}=\frac{1}{g_\pi}\simeq\frac{U_T \beta_F}{I_C}=\frac{\beta_F}{g_m}$
$r_0=\frac{1}{g_d}=\frac{V_{CE}+V_A}{I_C}\simeq \frac{V_A}{I_C}$

# Uguaglianza modello npn e pnp 
A differenza del modello dc i modelli ai piccoli segnali di npn e pnp sono uguali perché basta invertire tutte le correnti e le tensioni. 