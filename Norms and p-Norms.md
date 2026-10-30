---
aliases: [norm, p-norm, vector norm, Lp norm, ℓp norm]
tags: [linalg]
---
#linalg

# Norms and p-Norms

> [!summary] TL;DR
> A **norm** is a function that measures the "length" of a vector. The **p-norms** are a family of norms indexed by $p \ge 1$:
> $$\|x\|_p = \Big(\sum_{i=1}^n |x_i|^p\Big)^{1/p}$$
> - $p = 1$ → **Manhattan / taxicab** norm (sum of absolute values)
> - $p = 2$ → **Euclidean** norm (straight-line length)
> - $p = \infty$ → **Chebyshev / max / infinity** norm (largest absolute entry)
> The **Minkowski distance** is just the distance induced by a p-norm: $d_p(x,y) = \|x-y\|_p$.

---

## 1. What is a norm?

A **norm** on a real (or complex) vector space $V$ is a function $\|\cdot\| : V \to \mathbb{R}$ satisfying, for all $x, y \in V$ and scalars $\alpha$:

| Axiom | Statement | Meaning |
|---|---|---|
| **Positive definiteness** | $\lVert x\rVert \ge 0$, and $\lVert x\rVert = 0 \iff x = 0$ | Only the zero vector has zero length |
| **Absolute homogeneity** | $\lVert \alpha x\rVert = \lvert\alpha\rvert\,\lVert x\rVert$ | Scaling a vector scales its length |
| **Triangle inequality** | $\lVert x + y\rVert \le \lVert x\rVert + \lVert y\rVert$ | A detour is never shorter |

> [!note] Seminorm
> If you drop "$\|x\| = 0 \Rightarrow x = 0$" you get a **seminorm** (non-zero vectors may have zero length).

### Norm → distance
Every norm induces a **metric** (distance function):
$$d(x, y) = \|x - y\|$$
So choosing a norm = choosing how you measure distance between points.

### Useful consequence: reverse triangle inequality
$$\big|\,\|x\| - \|y\|\,\big| \le \|x - y\|$$
This shows every norm is a **continuous** function.

---

## 2. The p-norms

For $x = (x_1, \dots, x_n) \in \mathbb{R}^n$ and $1 \le p < \infty$:
$$\boxed{\|x\|_p = \Big(\sum_{i=1}^n |x_i|^p\Big)^{1/p}}$$

and for $p = \infty$:
$$\boxed{\|x\|_\infty = \max_{1 \le i \le n} |x_i|}$$

### Why $p \ge 1$?
Positive definiteness and homogeneity hold for any $p > 0$, but the **triangle inequality fails for $0 < p < 1$**.

> [!example] Counterexample with $p = \tfrac12$
> Let $x = (1, 0)$, $y = (0, 1)$. Then $\|x\|_{1/2} = \|y\|_{1/2} = 1$, but
> $$\|x + y\|_{1/2} = \big(1^{1/2} + 1^{1/2}\big)^2 = 4 > 2 = \|x\|_{1/2} + \|y\|_{1/2}.$$
> Geometrically: the "unit ball" for $p < 1$ is **not convex** (a star / astroid shape).

> [!tip] Key fact
> A function with the first two axioms is a norm **iff its unit ball is convex**. That is exactly why $p \ge 1$ is required.

### The triangle inequality for p-norms = Minkowski's inequality
$$\Big(\sum_i |x_i + y_i|^p\Big)^{1/p} \le \Big(\sum_i |x_i|^p\Big)^{1/p} + \Big(\sum_i |y_i|^p\Big)^{1/p}, \quad p \ge 1$$
It is usually proved via **Hölder's inequality** (see §7).

---

## 3. Special cases

### 3.1 $p = 1$ — Manhattan / taxicab norm
$$\|x\|_1 = \sum_{i=1}^n |x_i|$$
- Distance = total distance travelled along the axes (like city blocks on a grid).
- Unit ball in $\mathbb{R}^2$: a **diamond** (square rotated 45°) with vertices $(\pm1, 0), (0, \pm1)$.
- Used in **LASSO** / L1 regularization: its "pointy" unit ball promotes **sparse** solutions.

### 3.2 $p = 2$ — Euclidean norm
$$\|x\|_2 = \sqrt{\sum_{i=1}^n x_i^2} = \sqrt{x^\top x} = \sqrt{\langle x, x \rangle}$$
- The everyday notion of length — **Pythagoras** in $n$ dimensions.
- Unit ball in $\mathbb{R}^2$: the **circle**; in $\mathbb{R}^3$: the sphere.
- The **only p-norm induced by an inner product**. Equivalently, it is the only p-norm satisfying the **parallelogram law**:
  $$\|x + y\|^2 + \|x - y\|^2 = 2\|x\|^2 + 2\|y\|^2$$
- Therefore the only one where angles, orthogonality and projections make sense:
  $$\cos\theta = \frac{\langle x, y\rangle}{\|x\|_2\,\|y\|_2}$$
- **Rotation invariant**: $\|Qx\|_2 = \|x\|_2$ for any orthogonal matrix $Q$.
- Cauchy–Schwarz: $|\langle x, y\rangle| \le \|x\|_2\,\|y\|_2$.
- Used in least squares, ridge (L2) regularization, Euclidean distance in k-NN/k-means.

> [!warning] Often written without a subscript
> In many texts, $\|x\|$ with no subscript means $\|x\|_2$. Check the convention.

### 3.3 $p = \infty$ — Chebyshev / max / infinity norm
$$\|x\|_\infty = \max_i |x_i|$$
- Only the **largest** component matters.
- Unit ball in $\mathbb{R}^2$: the **axis-aligned square** with corners $(\pm1, \pm1)$.
- **Chebyshev distance** $d_\infty(x, y) = \max_i |x_i - y_i|$: the number of moves a **king** needs on a chessboard to go from one square to another.
- Used for worst-case error bounds, uniform approximation (minimax / Chebyshev approximation), tolerances in engineering.

#### Why is the max the "$p = \infty$" norm?
Because it is the limit of the p-norms:
$$\lim_{p \to \infty} \|x\|_p = \|x\|_\infty$$

> [!proof]- Proof
> Let $M = \max_i |x_i| > 0$. Then
> $$\|x\|_p = M \Big(\sum_{i=1}^n \Big(\frac{|x_i|}{M}\Big)^p\Big)^{1/p}.$$
> Each ratio $|x_i|/M \le 1$, and at least one equals $1$, so the sum lies in $[1, n]$. Hence
> $$M \le \|x\|_p \le n^{1/p} M.$$
> Since $n^{1/p} \to 1$ as $p \to \infty$, the squeeze theorem gives $\|x\|_p \to M$. $\blacksquare$

**Intuition:** raising to a large power $p$ makes the biggest entry dominate the sum completely; the $1/p$ root then "undoes" the power on that entry alone.

---

## 4. Minkowski distance

The **Minkowski distance** of order $p$ is the metric induced by the p-norm:
$$d_p(x, y) = \|x - y\|_p = \Big(\sum_{i=1}^n |x_i - y_i|^p\Big)^{1/p}$$

It is the umbrella name for the whole family:

| $p$ | Name of distance | Formula | Unit ball in $\mathbb{R}^2$ |
|---|---|---|---|
| $1$ | Manhattan / taxicab / city-block | $\sum \lvert x_i - y_i\rvert$ | diamond ◇ |
| $2$ | Euclidean | $\sqrt{\sum (x_i - y_i)^2}$ | circle ○ |
| $\infty$ | Chebyshev / chessboard | $\max \lvert x_i - y_i\rvert$ | square □ |

- $p$ is a tunable parameter (e.g. in k-NN, `scikit-learn`'s `metric="minkowski", p=...`).
- Valid metric only for $p \ge 1$ (same reason as above).

---

## 5. Geometry: unit balls

The unit ball $B_p = \{x : \|x\|_p \le 1\}$ in $\mathbb{R}^2$:

- $p = 1$: diamond $|x| + |y| \le 1$
- $p = 2$: disc $x^2 + y^2 \le 1$
- $p \to \infty$: square $\max(|x|, |y|) \le 1$
- $0 < p < 1$: non-convex star (not a norm)

As $p$ increases, the ball **grows** and morphs from diamond → circle → square:
$$B_1 \subset B_2 \subset B_\infty$$
More generally, $p < q \implies B_p \subseteq B_q$, because $\|x\|_q \le \|x\|_p$.

---

## 6. Worked example

Let $x = (3, -4, 0)$.

| Norm | Computation | Value |
|---|---|---|
| $\lVert x\rVert_1$ | $3 + 4 + 0$ | $7$ |
| $\lVert x\rVert_2$ | $\sqrt{9 + 16 + 0}$ | $5$ |
| $\lVert x\rVert_3$ | $(27 + 64)^{1/3} = 91^{1/3}$ | $\approx 4.498$ |
| $\lVert x\rVert_\infty$ | $\max(3, 4, 0)$ | $4$ |

Notice: $\|x\|_\infty \le \|x\|_3 \le \|x\|_2 \le \|x\|_1$ — the values **decrease** as $p$ increases.

Distance example: $a = (1, 2)$, $b = (4, 6)$, so $a - b = (-3, -4)$:
- Manhattan $d_1 = 7$
- Euclidean $d_2 = 5$
- Chebyshev $d_\infty = 4$

---

## 7. Important inequalities and relations

### Ordering
For $1 \le p \le q \le \infty$:
$$\|x\|_q \le \|x\|_p \le n^{\frac1p - \frac1q}\,\|x\|_q$$

Most-used special cases in $\mathbb{R}^n$:
$$\|x\|_\infty \le \|x\|_2 \le \|x\|_1$$
$$\|x\|_1 \le \sqrt{n}\,\|x\|_2, \qquad \|x\|_2 \le \sqrt{n}\,\|x\|_\infty, \qquad \|x\|_1 \le n\,\|x\|_\infty$$

### Equivalence of norms
In a **finite-dimensional** space, *all* norms are equivalent: for any two norms $\|\cdot\|_a, \|\cdot\|_b$ there exist constants $c, C > 0$ with
$$c\,\|x\|_a \le \|x\|_b \le C\,\|x\|_a \quad \forall x.$$
**Consequence:** convergence, continuity, open/closed sets and boundedness do not depend on which norm you pick in $\mathbb{R}^n$. (This fails in infinite dimensions.)

### Hölder's inequality
For conjugate exponents $\frac1p + \frac1q = 1$ (with $1 \le p, q \le \infty$):
$$|\langle x, y\rangle| \le \sum_i |x_i y_i| \le \|x\|_p\,\|y\|_q$$
- $p = q = 2$ gives **Cauchy–Schwarz**.
- $p = 1, q = \infty$: $|\langle x, y \rangle| \le \|x\|_1\,\|y\|_\infty$.

### Dual norms
The dual of $\|\cdot\|_p$ is $\|\cdot\|_q$ with $\frac1p + \frac1q = 1$:
$$\|y\|_q = \max_{\|x\|_p \le 1} \langle x, y\rangle$$
So: $\ell_1 \leftrightarrow \ell_\infty$ are dual to each other, and $\ell_2$ is **self-dual**.

---

## 8. Quick reference / cheat sheet

| | $\ell_1$ | $\ell_2$ | $\ell_\infty$ |
|---|---|---|---|
| Formula | $\sum\lvert x_i\rvert$ | $\sqrt{\sum x_i^2}$ | $\max\lvert x_i\rvert$ |
| Names | Manhattan, taxicab | Euclidean | Chebyshev, max, uniform |
| Unit ball (2D) | diamond | circle | square |
| Inner-product norm? | ❌ | ✅ | ❌ |
| Rotation invariant? | ❌ | ✅ | ❌ |
| Differentiable at 0 / at kinks? | not at axes | smooth away from 0 | not where max ties |
| Dual norm | $\ell_\infty$ | $\ell_2$ | $\ell_1$ |
| Typical use | sparsity, robust regression | least squares, geometry | worst-case bounds |

---

## 9. Common pitfalls

- "$\ell_0$ norm" ($\#$ of nonzero entries) is **not a norm** — it fails homogeneity.
- $p < 1$ "norms" are not norms (triangle inequality fails, non-convex ball).
- A larger $p$ gives a **smaller** (or equal) value, not a larger one.
- Matrix norms (Frobenius, operator/induced norms) are a related but separate topic.

---

## Related
- [[Inner Product]]
- [[Cauchy–Schwarz Inequality]]
- [[Hölder's Inequality]]
- [[Metric Spaces]]
- [[Matrix Norms]]
- [[Regularization]]
