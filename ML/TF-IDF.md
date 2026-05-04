#nlp 

>[!summary] 
>TF-IDF (Term Frequency Inverse Document Frequency) is a way to compute the importance of a term in a document belonging to a corpus.
>TF-IDF weights a term by its frequency in a document and its rarity across the corpus, giving more importance to terms that are distinctive to that document.
>For example the word `the` might be very frequent in a document but it's importance to identify that document is small as `the` is also common in many other documents. Conversely the word `Beatrice` might be very common in Dante and since it's not found in many other documents it's highly distinctive of that document.
>It can be used to compute vector representations of documents (similar to more modern sentence-[[BERT]] embeddings, averaging of a document's word [[Embedding layer|embeddings]] or [[Contrastive Text Embeddings, text-embedding-3]]) 


# Formula
Given a corpus $\mathcal D = \{d_1,\dots,d_N\}$  of $N$ documents and a term $t$ in the vocabulary $\cal V$ we compute the term frequency for term $t\in\cal V$ for document $d_i$ as:
$$
\text{tf}(t,d_i) = \frac{f(t,d_i)}{\sum_{t'\in\cal V}f(t',d_i)}
$$
where $f(t,d_i)$ is the number of occurrences of $t$ in $d_i$.
Then term-frequency is the relative frequency of a term in a document.

The inverse-document-freqency (IDF) for a term $t\in\cal V$ is:
$$
\text{idf}(t) = \log\left(\frac{N}{\text{df}(t)}\right)
$$
where $\text{df}(t)$ is the number of documents in which term $t$ appears at least once.
 $$\text{tdidf}(t,d_i​)=\text{tf}(t,d_i​)\cdot\text{idf}(t)$$


A (term,document) pair has a higher $\text{tfidf}$  if the term is common in the document relative to other terms and is rare in other documents.

# Vector representation of documents using TF-IDF 

TF-IDF can be used to obtain vector representation of a document in $\mathbb R^{|\cal V|}$ space by computing $v_{d_i}=(\text{tfidf}(t_1,d_i​),\dots,\text{tfidf}(t_{|\cal V|},d_i))^T$
Nowadays other approaches computing dense vectors for documents using deep learning are better but sparse vectors like tf-idf vector can still be used in [[Hybrid search for RAG]] as the sparse vector even though other approaches like [[BM25]] or even moreso SPADE outperform tf-idf as sparse vectors.

---

