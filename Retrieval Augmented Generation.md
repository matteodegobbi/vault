#nlp #ml #dl 

> [!summary]
Vanilla LLMs have only access to knowledge encoded within their parameters during training, the dataset is large and contains a lot of info but it is static (also catastrophic forgetting makes difficult and expensive retraining the model on new data).
[[Retrieval Augmented Generation]] allows the model to access externally provided knowledge during generation.
> The idea is to augment the prompt with relevant pieces of information which are stored in some vector database, the knowledge base.


---

In principle we could try to add all the information in the prompt but limited context size and the risk of adding useless distracting information (needle in a haystack) make this approach unfeasible in most practical cases or at least the performance is worse than RAG. Also since pricing is often done per token this is wasteful.

The outline of RAG process is:
1. Retrieve: The model receives a user query (the prompt) and uses an embedding model to transform it into a vector representation. This vector is then used to search a vector database for the most semantically similar pieces of information which will be used to augment the original prompt
2. Augment: The original prompt is augmented with the retrieved information from the vector database, usually preprending it to the original query.
3. Generate: The augmented prompt is then fed to the LLM, which generates a response based on both the original query and the retrieved knowledge, using knowledge both stored in the parameters and retrieved from the external knowledge base.


---

# Creation of the knowledge base
We collect a set of documents to use in the RAG process.
Then we divide these documents into chunks of some number of tokens (e.g. 100 tokens), typically using a sliding window approach. 

Then these chunks are converted into a vector representation using an embedding model (some pretrained transformer model). 

This knowledge base creation process has some hyperparameters:
- Chunk Size: The number of tokens in each chunk
- Sliding Window Step: The overlap between consecutive chunks
- Embedding size

# Retrieval
To carry out the retrieval we need to carry out 2 steps:
1. Candidate retrieval: selecting potentially relevant candidate vectors, maximizing [[Metrics|recall]], the methods used for this typically use semantic embeddings and/or keyword based methods
2. Ranking: give a ranking to the candidate vectors to determine the most relevant ones, maximizing [[Metrics|precision]], 
We have a few different methods for searching the vector database, utilizing various techniques both for candidate retrieval and ranking..

### Candidate retrieval techniques
#### Semantic search using embedding based similarity
We already have embeddings for all our chunks in the knowledge base and can directly compute the cosine similarity (or some other measure) between the query embedding and all the chunk embeddings. Usually some approximate nearest neighbor search algorithms like Faiss are used to speed up this step.
To encode both chunks and queries usually some encoder only model like SentenceBERT or similar is used.
![[Pasted image 20260324224033.png]]
[Link to SentenceBERT paper](https://arxiv.org/abs/1908.10084)

#### Keyword search
This approach relies on matching keywords or phrases within the documents and queries, while Semantic Search tries to capture the overall meaning and doesn't care about specific words, keyword search is based on literal matches.
An example of keyword search algorithm often used is Okapi BM25.
Keyword search is sometimes more useful when we want the specific details or exact phrasing from the document:
In this example semantic search could detect that "Where is Cuddly?" is semantically similar to "Where is Paris?" but just searching for "Cuddly" in this case yields a better result for the specific task.
![[Pasted image 20260324224624.png]]

#### Hybrid approaches
In this case we can search combining both semantic and keyword search to obtain the advantages of both.

#### Advanced techniques

Discrepancy mitigation: to mitigate discrepancies between the query embeddings (usually some kind of question in the prompt) and the document embeddings, we can employ techniques like generate a fake query document making the query embedding have the same nature as the document embeddings (like in [this paper](https://arxiv.org/pdf/2212.10496)) or use some data augmentation strategies in the query, e.g. dynamically adding synonyms.

Add context to chunks: to add context to the chunks in the knowledge base Anthropic developed a technique called [contextual retrieval](https://www.anthropic.com/engineering/contextual-retrieval), it consists in prepending to each chunk (before the embedding step) a generated context, based on the whole document, explaining what the chunk is referring to.
To generate the context to prepend to each chunk, we can use an LLM with some prompt along the lines of:
```
<document>
{WHOLE_DOCUMENT}
</document>
Here is the chunk we want to situate within the whole document:
{CHUNK_CONTENT}

Please give a short succinct context to situate this chunk within the overall document for the purposes of improving search retrieval of the chunk. Answer only with the succinct context and nothing else.
```

Since the first part of the prompt is the same for all chunks we can use [[Prompt Caching]] to save a lot of computational power by avoiding re-encoding the same parts of the prompt.

