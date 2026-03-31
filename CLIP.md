#ml #dl #nlp 
>[!summary]
CLIP (Contrastive Language–Image Pre-training) is a ml model that learns to connect images with text. It's trained on a large dataset of image and caption pairs.
It's useful for tasks like image classification and generation and allows tasks like zero-shot learning. 
It also removes the need for specific labels like in regular computer vision classification, this greatly helps when building datasets as images together with a caption describing them are common on the internet (e.g. image and it's alt-text or image and it's description on Wikipedia) this makes it easier to scale to large dataset sizes. 

---
# CLIP
CLIP is inspired by previous models like:
- Virtex (a predictive model) which already used pre-training steps with natural language supervision followed by training on labeled samples called 'gold labels' 
- ConVirt a natural language supervision image model which uses a contrastive learning approach to align text and image representations. This allowed to avoid problems with predicting the exact caption as in Virtex and also to avoid the costly labeling process
So the idea behind ConVirt was that predicting the exact caption is hard (as there are multiple possible captions for the same image) and constrastive learning can be useful.

CLIP builds on this idea by learning through contrastive learning a shared embedding space where images and their corresponding text descriptions are pulled closer together, while dissimilar pairs are pushed further apart.

The approach is very similar to the one outlined in the note: [[Contrastive Text Embeddings, text-embedding-3#How to train Contrastive Text Embeddings|How to train constrastive text embeddings]], using the InfoNCE loss both from x to y and y to x and all the considerations on column and row wise CE still hold for clip. The only difference is that instead of using two text embeddings the model uses a text embedding and an image embedding. 
The only part remaining to explain in CLIP is how to get the text and image embeddings to be used in the InfoNCE loss.

## How to get the text and image embeddings 
### Image embeddings
To get the image embeddings, we need to use an image encoder:
- A CNN like ResNet with the global average pooling layer replaced by an attention pooling layer. This version of CLIP is faster but less accurate.
- A [[ViT, Visual Transformers]], more accurate but slower than the CNN version.

>[!Tip] Attention pooling layer explanation 
>https://github.com/openai/CLIP/blob/main/clip/model.py
>1. First we flatten the spatial dimensions of the input to one vector (the feature maps stay separate though) and permutes the dimensions: meaning from input (N,C,H,W) --> (HW,N,C)
> 2. We add a special summary token at the beginning of the sequence which is used in the same way as `[CLS]` in BERT. This yields (HW + 1, N, C) 
>3. We compute multi head self-attention between the HW+1 tokens (each of them is a vector of length C) the output of the layer is of size (C,N) the same that we would get with GlobalAvgPool
>If we want instead of having the final embeddings of length C we can use the usual final projection that mixes head information (the one called $W_O$ in [[Transformers]]) to get a specified embedding size different from C.

## Text embeddings
For the text embeddings we can use a decoder only transformer like GPT2 using the final hidden-state of `[EOS]` as the embedding. This approach is likely the same as the one used in [[Contrastive Text Embeddings, text-embedding-3#OpenAI's text-embedding-3|OpenAI's text-embedding-3]] .

---

# Uses of CLIP
- Zero shot transfer: generalization to unseen datasets
- Representation learning: e.g. fitting some classifier using CLIP embeddings
- [[Retrieval Augmented Generation]]
- Text2Img in image generation


