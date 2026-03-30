#dl #ml 

# ML Theory
[[Empirical risk minimization]]
[[Train-test-validation, model selection]]
[[Bias-Variance and Bias-Complexity trade-offs]]
[[Metrics]]
[[Stochastic gradient descent]]
# Models ML
OLS/linear reg
GLMs
perceptron
logistic regression
SVM
MLE
decision tree 
random forest

# Deep learning theory

[[Neural networks, backpropagation]]
[[Expressiveness of Neural nets]]TODO
[[Activation functions]]
[[Exploding and vanishing gradients]]
Xavier init, Kaiming-He init
[[Xavier and Kaiming-He init]]
Auto-differentiation
Distribution shift
Distillation
Scaling laws
Gradient checkpointing
[[Regularization]]
[[Data augmentation]] TODO
[[Label smoothing]] TODO
[[Ensembles]] TODO
[[Early stopping]] TODO
Supervised pretraining
Unsupervised pretraining
[[Teacher Forcing]] TODO 
[[Mixed Precision]]

# Architectures (broad)
[[Convolutional neural networks]] 
[[Autoencoders]]
[[Autoencoders#Variational Autoencoders|VAEs]] 
[[Siamese Networks]]
GANs
[[Recurrent Neural Networks]]
[[Transformers]] TODO POS ENCODINGS
ViTs
Diffusion models
TCN con atrous convolution (forse skip)
# Specific layers
[[Convolutional neural networks#Convolutional layer]]
[[Convolutional neural networks#Pooling]]
[[Convolutional neural networks#Global Average pooling]]
[[Dropout]]
[[Attention]]
[[Embedding layer]]
## Normalization techniques
[[Batch normalization]] 
[[Layer Normalization]]
Instance Normalization 
Spectral Normalization 
Group Normalization 
[[RMSNorm]]
[[Comparison of normalization layers]] 
# Losses and optimizers
[[Cross Entropy]], specifically:
* Binary classification [[Cross Entropy#Binary Cross-Entropy (BCE)]]
* Multi class classification [[Cross Entropy#Categorical Cross-Entropy (CCE)]]
* Multi label classification [[Cross Entropy#Multi-Label]]
MSE
MAE

Segmentation losses like Dice and Tversky index
Focal loss

# Optimizers and similar
[[Stochastic gradient descent|SGD]]
[[Adam]]
[[Adam#AdamW]]
[[Learning Rate Scheduling]]
lr annealing
Other optimizers RMSProp, Nesterov, Adagrad etc

---
# NLP AND LLMS??
> [!note]
> Some of these notes were already linked in the deep learning section but are linked again since they are relevant to LLMs

[[Natural Language Processing tasks]]
[[Tokenization]] TODO BPE E WORDPIECE
[[Word2Vec,GloVe and FastText]]
[[Embedding layer]]
[[Positional Embeddings]] TODO
[[Transformers]]
[[Layer Normalization]]
[[RMSNorm]]

[[Large Language Models]]
	[[Supervised Finetuning]]
	[[Reinforcement Learning From Human Feedback]]
	[[Mixture of Experts]]
	[[Retrieval Augmented Generation]]
	[[Tool Calling]]
	[[Sparse Attention]]
	[[KV-Cache]]
	[[Prompt Caching]]
	[[Chain of Thought]]
	TODO FINIRE CHAIN OF THOUGHT AND SELF CONSISTENCY
	[[Flash Attention]]
	[[Mixed Precision]]
[[Agentic LLMs]]

[[Contrastive Text Embeddings, text-embedding-3]], often used for [[Retrieval Augmented Generation|RAG]]


TODO ADD NOTES ON LOCAL + GLOBAL ATTENTION IN DIFFERENT LAYERS LESSON 2 STANFORD COURSE
TODO ADD NOTES ON SHARED KEY AND VALUE PROJECTION MATRICES IN MULTI HEAD LESSON 2 STANFORD COURSE
# Specific Models:
to add to their respective notes
GPT
BeRT
ElMO??
Neural Style Transfer

---

# 🧠 LLM Study Plan (From Transformers → Advanced Systems)

## **Module 1 — Foundations of LLMs (1–2 weeks)**

### 1.1 Language Modeling Objective

- Causal Language Modeling (CLM)
    
- Next-token prediction mechanics
    
- Training vs inference mismatch
    
- Exposure bias
    

### 1.2 Tokenization

- Byte Pair Encoding (BPE)
    
- SentencePiece / Unigram LM
    
- Vocabulary size tradeoffs
    
- Tokenization impact on performance
    

### 1.3 Data for LLMs

- Web-scale datasets (Common Crawl)
    
- Data cleaning & filtering
    
- Deduplication techniques
    
- Data contamination issues
    

---

## **Module 2 — Transformer Scaling (1 week)**

### 2.1 Scaling Laws

- Scaling Laws for Neural Language Models
    
- Loss vs compute vs parameters
    
- Data/parameter optimality
    

### 2.2 Emergent Abilities

- Phase transitions in capability
    
- Few-shot and zero-shot behavior
    
- In-context learning
    

---

## **Module 3 — Training Large Models (2 weeks)**

### 3.1 Optimization

- Adam vs AdamW
    
- Learning rate schedules (warmup + decay)
    
- Gradient clipping
    
- Weight decay
    

### 3.2 Systems & Efficiency

- Data parallelism
    
- Model parallelism (tensor/pipeline)
    
- Mixed precision (FP16, bfloat16)
    
- Gradient checkpointing
    

### 3.3 Training Stability

- Initialization strategies
    
- Loss spikes and divergence
    
- Normalization (LayerNorm variants)
    

---

## **Module 4 — Instruction Tuning & Alignment (2 weeks)**

### 4.1 Supervised Fine-Tuning (SFT)

- Instruction datasets
    
- Prompt-response formatting
    
- Dataset quality vs size
    

### 4.2 Human Alignment

- Reinforcement Learning from Human Feedback
    
- Reward models
    
- Policy optimization (PPO basics)
    

### 4.3 Alternatives to RLHF

- Direct Preference Optimization (DPO)
    
- Reinforcement Learning from AI Feedback (RLAIF)
    

---

## **Module 5 — Inference & Decoding (3–5 days)**

### 5.1 Decoding Methods

- Greedy decoding
    
- Beam search
    
- Sampling methods
    

### 5.2 Sampling Controls

- Temperature
    
- Top-k sampling
    
- Top-p (nucleus sampling)
    

### 5.3 Practical Tradeoffs

- Determinism vs creativity
    
- Hallucination vs diversity
    

---

## **Module 6 — Evaluation of LLMs (1 week)**

### 6.1 Automatic Metrics

- Perplexity (limitations)
    
- Accuracy-based benchmarks
    

### 6.2 Benchmarking

- MMLU
    
- BIG-bench
    
- Task-specific evals
    

### 6.3 Human Evaluation

- Preference ranking
    
- Pairwise comparisons
    

---

## **Module 7 — Retrieval-Augmented Generation (RAG) (1 week)**

### 7.1 Embeddings

- Semantic similarity
    
- Vector representations
    

### 7.2 Retrieval Systems

- Vector databases (FAISS, etc.)
    
- Chunking strategies
    
- Query formulation
    

### 7.3 RAG Pipelines

- Retrieval + generation loop
    
- Context injection
    
- Failure modes
    

---

## **Module 8 — Fine-Tuning Techniques (1 week)**

### 8.1 Full Fine-Tuning

- When to use it
    
- Cost considerations
    

### 8.2 Parameter-Efficient Methods

- LoRA (Low-Rank Adaptation)
    
- Adapters
    
- Prefix / prompt tuning
    

---

## **Module 9 — Safety, Limitations & Interpretability (1 week)**

### 9.1 Failure Modes

- Hallucinations
    
- Bias & toxicity
    
- Overconfidence
    

### 9.2 Safety Techniques

- Moderation layers
    
- Guardrails
    
- Red teaming
    

### 9.3 Interpretability

- Attention analysis
    
- Mechanistic interpretability basics
    

---

## **Module 10 — Advanced Topics (2+ weeks, optional)**

### 10.1 Architecture Variants

- Mixture of Experts (MoE)
    
- Sparse transformers
    

### 10.2 Multimodal Models

- Text + image models
    
- Cross-modal attention
    

### 10.3 Tool Use & Agents

- Function calling
    
- Planning & reasoning loops
    

### 10.4 Long Context Models

- Memory mechanisms
    
- Context window scaling
    

---

# 📅 Suggested Timeline (8–10 weeks total)

- Weeks 1–2 → Foundations
    
- Week 3 → Scaling
    
- Weeks 4–5 → Training
    
- Weeks 6–7 → Alignment
    
- Week 8 → Inference + Evaluation
    
- Week 9 → RAG + Fine-tuning
    
- Week 10 → Advanced topics
    

---

# 🧩 Optional Hands-On Track (Highly Recommended)

Alongside theory:

- Implement a mini GPT (PyTorch)
    
- Train on a small dataset
    
- Add sampling methods
    
- Fine-tune with instructions
    
- Build a simple RAG system
    

---

If you want, I can turn this into:

- a **daily checklist plan**, or
    
- a **project-based roadmap (build your own ChatGPT-like system step by step)**