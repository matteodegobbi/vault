---
tags: elettronica
---
![[modelloGeneralePiccoliSegnali.png]]
# Tabella riassuntiva e modello generale
Questo modello è valido sia per [[Modello ai piccoli segnali BJT]] che per [[Modello ai piccoli segnali Mosfet]], usando questa tabella:

| Modello generale| BJT | Mosfet |
| :---: | :---: | :---: |
| $(v_i,i_i)$ | $(v_{be},i_b)$ | $(v_{gs},i_g)$ |
|$(v_o,i_o)$|$(v_{ce},i_c)$|$(v_{ds},i_d)$|
|$g_m$|$\frac{I_C}{U_T}$|$k_n V_{OV}=\frac{2 I_D}{V_{OV}}=\sqrt{2k_n I_D}$|
|$r_i$|$r_\pi=\frac{\beta_F U_T}{I_C}=\frac{\beta_F}{g_m}$|$\infty$|
|$r_o$|$\frac{V_{CE}+V_A}{I_C} \simeq \frac{V_A}{I_C}$|$\frac{V_{DS}+V_A}{I_D}\simeq \frac{V_A}{I_D} = \frac{1}{\lambda I_D}$|

ricordando che per i Mosfet definiamo $V_{OV} \triangleq |V_{GS}-V_t|$ e $V_A=\frac{1}{\lambda}$.
# Limiti di validità del regime di piccoli segnali
TODO aggiungi se serve questa parte.
