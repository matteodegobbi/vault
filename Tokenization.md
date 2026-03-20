#nlp 
In NLP, we need to find a way to represent text that can be used with  machine learning algorithms. The first step is tokenization, that means determining how we should split the text into smaller units, typically words or sub-words, called tokens.

This is necessary because we need to convert text into a numerical representation, and before determining a numerical representation of these unit of text we first first need to determine how to divide the text into these sub-units (the tokens).

---

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

In this approach the tokenization strategy tries to balance between the two previous approaches, often the tokenization process is learned from data and learns to leverage common prefixes and suffixes.
This improves the OOV problem of word level tokenization (even though it doesn't solve it fully).

Also the [[Embedding layer|embeddings]] are more interpretable than character level tokenization (even though they are not as interpretable as with word level tokenization where there is 1 to 1 relation between words and embeddings). 

---

# Tokenization Algorithms

## BPE ( Byte Pair Encoding))

## WordPiece


