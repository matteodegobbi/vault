# 20/4/2026
## Dataset
BEIR dataset: collection of 18 datasets for Information retrieval, **only text, no images**. Datasets in different domains 

Metrics to use for evaluation of retrieval:
- NDCG@k (Normalized Discounted Cumulative Gain) same as the one in [[Retrieval Augmented Generation#Normalized Discounted Cumulative Gain at k (NDCG@k)]]
- MAP (Mean Average Precision)
- Recall@k 
- Precision@k
> [!note]
> For multimodal datasets look for MS COCO, Flickr30k, WebQA, MultimodalQA and DocVQA.


Methods used for retrieval of documents
- BM25
- TD-IDF
- Sentence-BERT + ANN 
- OpenAI embeddings ([[Contrastive Text Embeddings, text-embedding-3]]) + ANN



## Code

Embedder class to abstract away which embedder im using (openai, sentencebert etc), retriever class to load, embed and index the dataset and provide search function

---
# 21/4/2026

Read tutorials on qdrant ui functions
## Code
Added batching for both embedder and indexer to improve performance, could be improved further with async/concurrency.

Added retrieve method to retriever, provides points close in the embedding space to a provided textual query.

tried quora dataset, compute performance measures, refactor 

---

# 22/4/2026
Hybrid Search article explaining how to do it, also multivector with ColBERT to try later for passage searching inside the document
https://qdrant.tech/documentation/tutorials-search-engineering/reranking-hybrid-search/

Fastembed library by qdrant to get sparse vectors TF-IDF or BM25 etc
# Code
Added csv saving of metrics + basic plots of metrics in jupyter

# 23/4/2026

Finished Hybrid search and sparse search implementation. Using bm25 as sparse embedder.

Refactor with yaml config files instead of CLI tool

Theory BM25 and reranking models for retrieval.

# 24/4/2026
Try pipeline with 
1. Candidate retrieval max recall
2. reranking according to a more powerful model (smaller set of candidates) to obtain max precision
We can use two different architectures for reranking
Bi-Encoder: processes document chunk and query independently and then compute some similarity metrics (cosine sim)
Cross-Encoder: query and chunk are processed together it's more powerful as it executes attention between query and chunk tokens direcly, its also more computationally expensive

# 27/4/2026
Implemented candidate reranking
Changed config file implementation

# 28/4/2026
Modello reranking basato su Qwen 2.5 https://www.mixedbread.com/blog/mxbai-rerank-v2
Impl Batched reranking for perf
Moved to cuda or mps (mac) for perf
Changed plotting in 2 types:
1. compare search types: dense, hybrid with RRF, sparse BM25
2. compare reranker vs no reranker using hybrid search only (otherwise too many plots)
# 29/4/2026
## Chiamata David 
## Riassunto cose fatte
- Dense search con i 2 modelli (MiniLM e BGE base, provato anche BGE large ma e' lento), Sparse con BM25, Hybrid con RRF
- scifact, quora e scidocs (scidocs ha un corpus strano probabilmente va chunkato) scifact e quora hanno documenti abbastanza corti in letteratura non vengono chunkati
* reranking con modello qwen 
* evaluation di NDCG, recall precision e MAP, 
- plots comparando reranker vs no reranker e diversi search types
## Domande
- struttura codice
* servono altre metriche, Reverse Rank F1-Score etc? 
* reranking altri modelli? 
* altri sparse models da usare o non serve? e.g. SPLADE anche perche hybrid e' peggio di solo dense come performance
* api key openai e slack
* come fare batch delle api call di openai?
* per le query dovrei salvare l'embedding in qualche modo in qdrant o in locale per evitare re-embedding delle stesse query ogni volta soprattutto per modelli openai

## Altro 
- Title concat to text for scifact? Altri dataset?
- Contextual retrieval di anthropic (augmentation della query in formato doc)? + prompt caching
```
<document>
whole doc
</document>

Chunk we want to retrieve:
<chunk> lkjkjladfklajdflk </chunk>

Write some context helpful to understand this chunk

```

- HyDE? Finto doc risposta alla query, cosi doc nel db e finto doc sono dello stesso tipo --> embedding piu simili
# Code
Added openai embeddings text-embedding-3-small with exponential backoff, no caching yet.

# 4/5/2026


Added caching for API embeddings:
without-caching indexing + eval:
![[Screenshot from 2026-05-04 10-12-19.png]]
cached embeddings indexing + eval:
![[Screenshot from 2026-05-04 10-47-06.png]]
Offline works after firstc run to fill cache.

> [!Warning] 
> La libreria bypassa la cache se si usa embed_query invece di embed_batch quindi se si vuole fare embed di un singolo doc va usato 
`embed_batch([text])[0]`

Refactor project, abs path etc, pip support
Added logger to log to files and stdout across runs


---

# 5/5/2026
* Batch evaluation for speed
- added SPLADE
* changed plotting 

**Plot all models with only hybrid search**
![[plot_20260505_161903.png]]
**Plot bge vs openai small with only hybrid search**![[plot_20260505_162125.png]]
**Plot bge only all types of search**
![[plot_20260505_162222.png]]
# 6/5/2026
- Moved metrics saving to parquet in order to be able to save retrieval scores efficiently
- save retrieval scores
- plot retrieval scores dense and sparse?



---

scores delle query per dist
SPLADE
change two batch sizes for sparse and dense
gemini embedding 2 query vocale speech --> embedding