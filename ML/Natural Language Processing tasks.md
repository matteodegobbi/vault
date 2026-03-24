#nlp 
# Classification tasks
Given an input text we classify the text as a whole.
Some examples of these tasks are: 
* Sentiment extraction, e.g. is this amazon review positive or negative?
* Language detection, e.g. which language is this text in?

[[Metrics|Evaluation metrics]] used are the usual, accuracy, precision, recall, F1-Score etc. 
# Multi-Classification tasks
Given an input text we want to classify parts of the text or classify relationships between different part of the text
Some examples of these tasks are: 
* NER (Named Entity Recognition) sometimes also called NERC (Named Entity Recognition and Classification), e.g. given a text classify for every token (or span of tokens) if it's a drug and if it is which type of drug: anticoagulant, antibiotic, antiviral, beta-blocker etc.
* POS (part of speech) tagging, given a text determine for every word if it's an article, a noun, a verb etc.
* Dependency parsing, grammatical relation between words
* Constituent parsing, divide sentence into sub-phrases

For these tasks the [[Metrics|evaluation metrics]] used are the usual, accuracy, precision, recall, F1-Score etc. , but they are applied at the token level and then summarized in some way to get a performance metric for the whole text.
# Text generation 
Given an input text produce an output text.
Some examples of these tasks are: 
* Machine Translation (MT)
* Question Answering (QA)
* Summarization
* Text Generation

For MT the metrics used are BLEU, ROUGE, Perplexity (exponential of cross-entropy)


