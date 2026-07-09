# Prima parte, testing di modelli di embedding
## Text retrieval
Performance di vari modelli di embedding su dataset testuali come scifact, argument analysis,quora
anche hybrid search
con gemini anche audio queries
con alcuni modelli ho anche provato un reranker

![[plot_20260708_131515.png]]

![[plot_20260708_131501.png]]

![[e88299f2f6aad138.png]]
![[9a318176dff69798.png]]

![[scifact_perf.png]]
### Hybrid Search con RRF
BM25 e splade come modelli sparse 
![[Screenshot from 2026-07-08 17-41-22.png]]

![[plot_20260708_175651.png]]
![[plot_20260708_175655.png]]

In generale per i modelli piccoli hybrid tende ad essere meglio ma con i modelli grandi peggiora le performance, si potrebbe fare tuning degli iperparametri ma non sul dataset di test usato per le misure.

![[b287b34597dd11bf.png]]
## Image retrieval
Dataset MS-COCO per ogni immagine 5 captions scritte da umani
Retrieve di immagini da caption o vice-versa
retrieval di caption umane da caption vlm e vice versa
![[plot_20260708_132423.png]]

Vari tipi di embedder, caching locale per modelli via API
# Seconda parte, percezione umana vs embedding models
partendo da dati umani di https://www.colorado.edu/lab/cowell-lab/sites/default/files/attached-files/Jiang_Sanders_Cowell_2022_VisualAndSemanticSimilarityNorms.pdf

Dati raccolti da form su mechanical turk:
![[Screenshot from 2026-07-08 17-07-11.png]]
Similarita' semantica e visuale, due form diversi.

Dataset e' composto da 4 fold:
- animate objects
- inanimate objects
- indoor scenes
- outdoor scenes
10 ratings per ogni coppia di immagine nel fold

si puo' calcolare una matrice di distanza 60x60 per ogni fold.

Usando tecniche di riduzione di dimensionalita' possiamo avere un plot 2D:

![[MDS with human data semantic.png]]

Posso replicare questa pipeline ma con matrici di distanza calcolate usando modelli di embedding. In piu posso usare una VLM per catalogare gli oggetti con una serie di label predefinite:
![[Animal Map Jina.png]]
![[Animal Map Semantic.png]]
![[Animal Map BGE.png]]
Categorie:
fish, amphibian, reptile, bird, mammal, insect,
cetacean, crustacean
aquatic, flying, herbivore, carnivore, omnivore,
invertebrate, vertebrate,
farm, wild

Finora solo plot, da aggiungere distanze intra-classe e inter-classe.

## Distanza globale 
Tramite test di Mantel posso calcolare correlazione tra varie matrici di distanza, a livello globale.

Correlazione dei modelli con human semantic:
![[Screenshot from 2026-07-08 18-03-47.png]]

Correlazione dei modelli con human visual
![[Screenshot from 2026-07-08 18-04-04.png]]

Ho anche provato Dinov2 modello per feature usate per la segmentazione, feature puramente visuali.

Mix resnet + bge testo arriva come secondo modello
![[Screenshot from 2026-07-08 18-09-26.png]]
## Distanza neighborhood locale
Quando misuro correlazione globale do uguale importanza a paia di immagini molto distanti e paia di immagini vicine nel calcolo di una score per il modello di embedding. Nel contesto di retrieval e' piu' importante che paia vicine di immagini vengano riconosciute come simili.

#### mIoU over all folds vs k :
![[iou.png]]

# Terza parte, esperimento ranking 
## Ranking immagini
Dato 1 fold del dataset, Animate Objects.
Per ogni immagine calcolo:
- top 4 simili secondo Jina
- top 4 simili secondo OpenClip
- top 4 simili secondo dati umani semantici del paper di Jiang 
Prendo l'unione di questi 3 insiemi e ottengo per ogni immagine 1 insieme con $4\le|S|\le12$ immagini.

Vogliamo ottenere un ordine dalla piu' simile alla meno simile con veri ranking umani invece di ottenere ranking impliciti dati da similarita' pairwise.

---

Dopo aver ottenuto i dati possiamo ottenere un ordine totale sul candidate condizionato sull'immagine, contando quante volte un'immagine A "vince" contro B possiamo costruire un grafo.

Ad esempio con anchor:

![[Pasted image 20260709094228.png]]

![[Pasted image 20260709094348.png]]

Se il grafo e' un DAG allora i voti sono consistenti e il ranking e' un total order.

Comparison con il ranking ottenuto dai modelli di embedding guardando anche le categorie a cui appartengono le immagini e.g. wild, aquatic.

## Ranking caption
Dataset di 19 immagini prese da MS-COCO, per ogni immagine 4 captions:
umana e 3 vlm gpt-4o-mini, gemini 2.5 flash, qwen 2.5 7B.

La task per l'umano e' di ordinare le caption dalla migliore alla peggiore come descrizione dell'immagine.

Da questo possiamo ottenere quale captioning VLM e' preferita' tra le 3, e similarita' tra il ranking fatto dagli umani e quello fatto dagli embedding model per le stesse caption.

![[['maria', 'matteo']caption_data.png]]

---