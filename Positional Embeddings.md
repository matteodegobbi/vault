#nlp

In sequence models (Transformers), the embedding layer alone has **no notion of order** — `[cat, sat, mat]` and `[mat, sat, cat]` produce the same set of vectors.

The fix: **add positional embeddings** to the token embeddings:

$$\text{input}_i = \text{TokenEmbed}(t_i) + \text{PosEmbed}(i)$$
### Types of Positional Embeddings

| Type              | Description                                                     | Used In              |
| ----------------- | --------------------------------------------------------------- | -------------------- |
| **Sinusoidal**    | Fixed sine/cosine functions of position                         | Original Transformer |
| **Learned**       | Trainable position vectors (same mechanism as token embeddings) | BERT, GPT-2          |
| **Rotary (RoPE)** | Rotates query/key vectors by position angle                     | LLaMA, Mistral       |
| **ALiBi**         | Adds a linear position bias to attention scores                 | MPT, Falcon          |

---