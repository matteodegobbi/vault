#nlp #ml #dl 

> [!summary]
In NLP a language model is a statistical model that learns the probability distribution of sequences of tokens. 
A language model either computes the probability of a sequence:  
$P(w_1, w_2, w_3, \dots, w_n)$ (generative model in statistics) or predicts the next word given previous words: $P(w_n \mid w_1, w_2, \dots, w_{n-1})$ (discriminative model in statistic)
>
Large Language Models (LLMs) are a specific type of language model built using large neural networks usually transformer architectures with billions of parameters trained on huge amounts of data

---

# Differences with original [[Transformers]] architecture

Modern LLMs use mostly decoder only architecture, foregoing the encoder and the cross-attention block in the decoder stages. The reason for using decoder only models is that empirically they scale better to larger number of parameters and larger datasets. Of course using decoder only means using only the masked self-attention, enforcing causality, this is not a limit for language modeling tasks but it is for other tasks that require bidirectional context. In those cases, encoder only or encoder-decoder architectures might be preferable.

Another difference is the training objective:
Modern LLMS use autoregressive next-token prediction (causal language modeling) as their training objective, maximizing $\mathcal{L} = \sum_{t=1}^{n} \log P(x_t \mid x_1, ..., x_{t-1})$ 
This means it predicts the next token in the sequence using all previous tokens.
Other transformer based text models use different objectives depending on their purpose, for example Masked Language Modeling (like [[BERT]]), text-to-text reconstruction (like T5). 

Modern LLMs also incorporate [[Supervised Finetuning]] and [[Reinforcement Learning From Human Feedback]] to improve their performance and align them with human preferences. More details on their respective notes.

# Training

# Inference
During inference we use the decoder LLM auto-regressively. Meaning we produce the next tokens using as input to decoder the previously generated tokens. We need a starting token to initiate the process and we choose to always start with the `[BOS]`[[Tokenization#Special tokens|special token]].
Then we sample new tokens until we encounter the `[EOS]`token. 

## Sampling process

We have multiple ways to define the sampling process using the Softmax probabilities in output of the decoder:
#### Greedy decoding
In greedy decoding we always sample the token with highest probability according to the softmax output. This leads to a deterministic (other than numerical precision and hardware stuff) decoding, making it so the text produced is always the same if we start from the same input.

Also with greedy decoding, as the name suggests, we are always taking the locally optimal choice but it might not be the globally optimal choice, this is because the joint probability distribution $P(w_1, w_2, w_3, \dots, w_n)$ is not the product of the marginal probabilities as the tokens are not independently distributed. Once a token is chosen, it influences the probability distribution of the subsequent ones.

#### Beam Search
To find the true optimal sequence one would need to employ exhaustive search, at each time-step we track all previous possible sequences, and evaluate them all. This is computationally infeasible as the number of possible sequences grows exponentially with the length of the generated text.

Beam Search is an intermediate approach between greedy decoding and exhaustive search. At each time-step, we consider the $k$ most likely sequences so far.
We then expand each of these $k$ sequences by considering all possible next tokens, generating $k \times n$ candidate sequences ( we can actually use smarter approaches discarding in a online way instead of computing all the possible sequences), where $n$ is the current length of the sequence. 
Finally, we keep only the top $k$ most probable sequences from this expanded set, forming the new beam of $k$ sequences.

There are multiple stopping criteria for beam search:
* We can stop as soon as N sequences are complete, having sampled `[EOS]`
* We can stop when we reach a max length of the generated text.

>[!Note] Important Note
>When using this approach, longer sequences are penalized as the final probability is the result of multiplying more probabilities (which are by definition $\le 1$).
>To solve this problem instead of using product of probabilities we can use the sum of log probabilities  **normalized by length of the sequence**. $$
y = \arg\max_{y \in Y} \frac{1}{|y|^\alpha} \log p(y \mid x)
$$


Beam search is typically used in machine translation but for LLMs sampling methods are more common.

#### Sampling based methods 
This is the most common approach in LLMs where the next token is sampled from the probability distribution predicted by the decoder. This introduces an element of randomness leading to more creative generated text.

There are a few different sampling based methods, mainly restricting the sampling to only the most likely tokens to avoid generating nonsense text.

Top-k sampling samples the next token among the top k most probable in the sampling distribution (renormalized).

Top-p sampling (aka nucleus sampling) samples the next token from the smallest set of tokens whose cumulative probability exceeds p (e.g. p=90%). This truncates the distribution removing tokens with lower probabilities. 

  

## Temperature

Temperature is a parameter that controls how random or deterministic a model’s output is when generating text. It modifies the probability distribution over possible next tokens.

The temperature hyperparameter $T$ is included in the softmax of the last layer in the decoder, during inference. It  rescales the logits before applying softmax:
$P(i)=\frac{e^{z_i / T}}{\sum_j e^{z_j / T}}$
For $T<1$
* Sharpens the distribution
* Makes high-probability tokens even more likely
* Output becomes more deterministic and repetitive
For T approaching 0 it becomes equivalent to enforcing greedy decoding

Using $T>1$
- Flattens the distribution
- Increases randomness
- Output becomes more creative but less reliable

The idea is to only use temperature during inference to decide the degree of creativity/reliability of the model.

It is used in conjunction with the sampling methods (top-k or top-p) to tune the inference behavior of the LLM.
# Scaling laws

---


# Limitations
## Context length
Context length (aka context window) refers to the maximum amount of text an LLM can process in a single inference call including both the input it receives and the output it generates.

Everything passed to the model in one request counts as context:
- The system prompt
- The full conversation history
- Any documents or retrieved chunks ([[Retrieval Augmented Generation]])
- Tool/function call results
- The model's own generated output

All of this competes for the same fixed token budget due to the quadratic attention cost and some kinds of positional encodings that don't extrapolate (or degrade performance) above training sequence lengths (e.g. learned or sinusoidal [[Positional Embeddings]]).

LLMs empirically recall information at the beginning or at the end of the context better than in the middle (Lost in the Middle phenomenon) this means important info like [[Retrieval Augmented Generation|RAG]] data should be placed at either end.

There are several techniques to increasing context size, like using RoPE [[Positional Embeddings]] (which extrapolate to bigger contexts than seen in training), sliding windows, or advanced attention techniques like [[Sparse Attention]].

Also there exists various workarounds like summarization, [[Retrieval Augmented Generation|RAG]] to try to limit the context length needed.

Long context lengths also impact [[KV-Cache]] with longer sequences requiring larger caches possibly more than the available VRAM.


---

# Extensions

## Guided Decoding
Guided decoding is a technique applied to LLMs to obtain structured outputs like JSON (that doesn't depend only on prompting strategies).
It works during the inference process by setting to 0 the probability of tokens that would lead to an invalid output  before sampling is carried out.

For example if we are generating a JSON object the first token's distribution is modified to exclude tokens that would violate the JSON structure, such as closing curly braces before opening ones. 

This does not guarantee that the generated output will always be perfectly valid or semantically correct, but it increases the chances by forcing the model to adhere to the correct structure. The guiding can be carried out with finite state machines or similar techniques.

## Mixture of Experts
Refer to the [[Mixture of Experts]] note and especially its section of [[Mixture of Experts#MoE in Transformers and Large Language Models|MoE in Transformers and LLMs]] 

## Chain of Thought
Performance on many tasks can be increased by prompting the model to think aloud through thinking steps
TODO CONTINUA MAYBE MOVE TO PROMPT?

## RAG

![[Retrieval Augmented Generation]]


---

# Prompts 

A possible template to write prompts can be structured as:
![[Pasted image 20260324170729.png]]


---

# In-Context Learning

One of the unique capabilities of LLMs is their generalization to unseen tasks.

In zero-shot learning, a model is evaluated on a task it has never been explicitly trained on, without providing any examples of the solved task.

In few-shot learning, the model is given a small number of solved examples of the task, this _generally_ (nowadays reasoning zero-shot can outperform few-shot learning)) performs better than zero-shot learning because the examples provide the model with more info about how we want the task to be carried out.

---

