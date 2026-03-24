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

# Scaling laws

# Limitations

# Extensions

# Prompt