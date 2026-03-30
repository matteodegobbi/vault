#nlp #ml #dl 

> [!summary] Flash Attention is a technique to improve the efficiency of attention mechanisms in [[Transformers]]


# Reasons for Flash Attention

GPUs have two different sets of memories: HBM memory is big but slower and SRAM is much smaller but faster.
Flash Attention exploits these memories by strategically partitioning the attention matrix and performing computations primarily within the faster SRAM memory.
This avoids having to wait for HBM memory reducing the main bottleneck in [[Transformers]] models (like [[Large Language Models]]).

The reason why regular [[Attention]] is slow is because the GPU needs to:
- read $Q$ and $K$ from HBM
- perform the multiplication 
- write back to HBM
- read from HBM
- compute softmax
- write back to HBM
- read from HBM + read $V$
- matmul 
- write to HBM final result
All these reads and writes end up being the bottleneck.

# How flash attention works

The idea behind Flash Attention is to reduce these HBM accesses by tiling the matrices into smaller blocks, performing computations on these blocks entirely within SRAM, and then merging the results at the end.
There are 2 tricks used in order to optimize this process:
1. Softmax computation is executed in these tiles and then rescaled to obtain the normalization property (this avoids needing the whole matrix to be present in SRAM simultaneously). This trick is necessary in order for tiling to work.
2. Re-computing some intermediate results on the fly instead of storing them in HBM. This increases the amount of computation but reduces number of HBM accesses which are the bottleneck in attention computation. This trick is not necessary for tiling to work but improves performance.

---






