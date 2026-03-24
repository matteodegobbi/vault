#nlp 
>[!summary]
In NLP, we need to find a way to represent text that can be used with  machine learning algorithms. The first step is tokenization, that means determining how we should split the text into smaller units, typically words or sub-words, called tokens.
This is necessary because we need to convert text into a numerical representation, and before determining a numerical representation of these unit of text we first first need to determine how to divide the text into these sub-units (the tokens).

---
# Vocabulary and special tokens
#### Vocabulary
We define the vocabulary $V$ as the set of all tokens known to the model, the vocabulary size $|V|$ guides the trade-off between memory usage, model complexity and ability to represent rare words (if I fix the vocabulary size to 5000 the 5001th most common token will not have a representation). 
If a token is found during inference that was not seen during training it is said to be an out-of-vocabulary (OOV) token.
#### Special tokens
Other than the tokens in the text we may want to define some special tokens used for various purposes, for example some common special tokens are:
- `[UNK]`, for out-of-vocabulary tokens
- `[PAD]`, is the token used to pad sequences to the same lengths if the model requires so (e.g. using a fully connected neural net to process sequences of variable length) 
-  `[CLS]`, is the classification token in transformer models (like BERT) this token is added at the start of a sequence. Its final hidden representation is often used for sentence-level tasks like classification, hence the name
- `[SEP]`, marks the separation between two sentences in a text, used in tasks like QA
- `[BOS]`, beginning-of-sequence token
- `[EOS]`, End-of-sequence token. It's used in generation tasks to know when to stop producing tokens (e.g. in [[Transformers]] when `[EOS]` is sampled from the Softmax distribution the generation is stopped)
- `[MASK]`, mask tokens are used in masked language modeling (MLM) for models like BERT. Some tokens in the input are replaced with `[MASK]` the model’s objective is to predict the original token in the masked position.
# General tokenization approaches 

#### Word tokenization
A first approach could be to split the text into single words as tokens, this is called word tokenization. This approach has some problems: 
* We need to determine how punctuation and sentence boundaries work
* It struggles with OOV (out of vocabulary tokens), meaning if we encounter a word not present in the training set, the model can only treat the word as a completely unknown word. For example if it encounters the word 'unnormalized', which is not in the training set even if the training set contains the word ‘normalize’, the model cannot exploit this information.
* Even for in-vocabulary words, the information between similar words is not exploited (the model needs to learn that 'bear' and 'bears' are similar words).

#### Character tokenization
Just means splitting on every character, this can work but it produces very long sequences, making it expensive to train models and losing all word level information, forcing the model to learn by itself concepts like word boundaries and morphology.
Also the subsequently learned [[Embedding layer|embeddings]] don't convey any meaning as they represent single characters.
#### Sub-word Tokenization

This is the modern approach used in models like GPT.

In this approach the tokenization strategy tries to balance between the two previous approaches, often the tokenization process is learned from data and learns to leverage common prefixes and suffixes.
This improves the OOV problem of word level tokenization (even though it doesn't solve it fully).

Also the [[Embedding layer|embeddings]] are more interpretable than character level tokenization (even though they are not as interpretable as with word level tokenization where there is 1 to 1 relation between words and embeddings). 

---

# Tokenization Algorithms

## BPE ( Byte Pair Encoding))

## WordPiece


