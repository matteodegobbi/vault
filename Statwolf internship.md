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
- Move metrics saving to parquet in order to be able to save retrieval scores efficiently
call: usa tts per avere audio dataset

# 7/5/2026
- save retrieval scores and metrics to parquet
- plot retrieval scores dense and sparse?
# 8/5/2026
added gemini multimodal embedder
added manual cache hash that works with LocalFilesStore + non-text embeddings
![[Screenshot from 2026-05-12 16-46-22.png]]
# 11/5/2026 & 12/5/2026
Changed multimodal gemini embedder to try to avoid rate limiting, batched version with at most 100 docs at a time, the full-on bulk batch api is not supported yet by gemini-embedding so the notebook version doesnt work

```
uv run -m text_retrieval.main --search dense --config configs/gemini2_bm25_text.yaml --index 
```

# 13/5/2026
Trying othe APIs by google, doesnt work.
# 14/5/2026 & 15/5/2026
Gemini embeddings work much better than others on scifact
https://agentset.ai/blog/gemini-2-embedding?utm_source=chatgpt.com

Tried audio embeddings vs textual on scifact with gemini2: more separation between rel and non rel for text than audio and better overall performance:

![[plot_20260515_115356.png]]

![[8bf595db2550f894.png]]

![[baf92e2a0271f007.png]]

Downloaded MSCOCO from HF repo, load dataset to be compatible with retriever

# 18/5/2026 & 19/5/2026
Added CLIP text to image search, full support for image embeddings as corpus
![[Screenshot from 2026-05-18 16-52-40.png]]

![[Screenshot from 2026-05-18 16-54-58.png]]

![[Screenshot from 2026-05-18 16-56-34.png]]

!!! Importante Al massimo una immagine relevant per una caption, ho flattened tutte le queries, quindi recall etc sono sul al massimo 1 image  retrieved
![[Screenshot from 2026-05-19 10-34-52.png]]

# 20/5/2026
Local VLM to gen captions

quali combinazioni valide di img, human capt, vlm capt? scritte sotto
Image queries + text corpus ha senso? Si

CALL

CORPUS -- QUERY
1 IMG -- human
2 vlm -- human 
3 human -- vlm 
4 human -- img
5 IMG -- altered image perspective, rotate, color

---

# 21/5/2026
## Continue local VLM for captions
Local VLM to gen captions for coco + text embedder for  **vlm--human** comparison with **IMG--human**

Finished VLM corpus + human queries
## Img search 4 closer images in corpus
![[Screenshot from 2026-05-21 10-27-57.png]]
![[Screenshot from 2026-05-21 10-27-34.png]]


# 22/5/2026
inverted coco dataset with 
human -- img 
human -- vlm

# 25/5/2026
Jinav4 embeddings for IMG--human
**quantized to 4 bits for memory** OTHERWISE DOESNT FIT

For now Jinav4 is only Img--human because I need to specify the prompt name
should i add the others?
Late Interaction multivector?

# 26/5/2026
Plots comparing Jinav4 and openclip
Metrics plot
Hits plots
Hits examples queries

![[plot_20260526_113748.png]]
In ordine:

| Corpus | Queries | Model        | Recall@10 |
| ------ | ------- | ------------ | --------- |
| Image  | Human   | Jinav4       | 0.835     |
| Image  | Human   | openclip     | 0.792     |
| VLM    | Human   | openai large | 0.736     |
| Human  | Image   | openclip     | 0.587     |
| Human  | VLM     | openai large | 0.476     |

![[f61e10ee6aa0246a.png]]

![[9e5d9e4928e734ad.png]]

# 27/5/2026 & 28 & 29
Jinav5 implemented and works
Corrected inverted datasets to have many docs for a single query for coco recomputed all inverted datasets with correct version

# 3/6/2026
Provato gemini per NanoV2 per cambiare immagini, serve la api key
Retrieve closer images to corrupted images 

# 4/6/2026
Look for images similar to changed gemini images
MRR, mIoU and hit metrics for transformed images
plots for these metrics
Gemini Rate limits?

# 5/6/2026
Quora la performance e' troppo buona provo altri dataset:
	Arguana new dataset.

# 8/6/2026 & 9/6/2026 & 10/6/2026
Image ranker website, supabase for db.
Text ranker? caption ranking, text-text ranking
Code for ranking images by image or text models.

# 11-12/6/2026
Added captions in a single html template
Ran Different vlm captions + merge 

# 15/6/2026 - 16/6/2026
Fixed code
add task selection page 
reworked db
# 17/6/2026
"smart sampler" with less info image first maybe improve

![[Screenshot from 2026-06-17 15-11-03.png]]
![[Screenshot from 2026-06-17 15-16-55.png]]

---

# 18-19/6/2026
Jiang dataset added to image ranker, site needs to be fixed
MDS with embeddign and human pairwise data

# 22/6/2026
Fixed bugs with caption and images website
Import data and analysis, convex hull plots

---

Cosine sims human data
Disagreeement
How to sample using disagreement



ANIMAL Categories NEED TO BE FIXED manual CHECK
