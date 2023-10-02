Introduction to Mathematical Optimization - Matteo Fischetti
https://www.amazon.com/Introduction-Mathematical-Optimization-Matteo-Fischetti/dp/1692792024
Registrazioni sul sito del prof delle lezioni di due anni fa.
Esami: 26 Jan, 20 Feb, 26 Jun, 30 Aug.
---
Esempio pag 11 Turni infermieri
All shifts are 5 days of work and 2 of rest

| Day    | \#nurses|
| -------- | ------- |
| MON  | 17 |
| TUE| 13 |
| WED| 15 |
| ...| ...|
| SUN| 11 |
Input is the number of nurses required for each day (2nd column of the table).
Output: ~~minimum number of nurses required~~ , number of nurses starting on day 1 $x_1$ (MON),number of nurses starting on day 2 $x_2$, $\dots$
these are called decision variables.
If you know all the decision variables you can compute the minimum number of nurses required.
$\min \ x_1+x_2+\dotsi x_7$  this is called the objective function
we need to add some constraints because for example all zeroes is not a solution that makes sense, for example:
$x_1+\cancel{x_2+x_3}+x_4+x_5+x_6+x_7\ge17$ (MON)  (The nurses starting on TUE and WED are home in MON)
$x_1+x_2+\cancel{x_3+x_4}+x_5+x_6+x_7\ge13$ (TUE)  (The nurses starting on WED and THU are home in TUE)
.
.
.
$\cancel{x_1+x_2}+x_3+x_4+x_5+x_6+x_7\ge11$ (SUN)  
also we need to specify that $x_i \ge 0 \ \ \ \ i=1,\dotsi,7$ and also $x_i\in \mathbb{Z}$ because we need an integer number of nurses.







