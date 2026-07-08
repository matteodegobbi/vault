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
![[Screenshot from 2026-07-08 18-09-26.png]]
## Distanza neighborhood locale
Quando misuro correlazione globale do uguale importanza a paia di immagini molto distanti e paia di immagini vicine nel calcolo di una score per il modello di embedding. Nel contesto di retrieval e' piu' importante che paia vicine di immagini vengano riconosciute come simili.

#### mIoU over all folds vs k :
![[iou.png]]



# Terza parte, esperimento ranking 
---
Sul sito