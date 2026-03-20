#ml #dl 

# Why feed-forward and CNNS fail at sequences
To input or output variable length sequences into dense layers we would need to choose a max sequence length and employ padding for input sequences that are shorter. An additional problem is that while position may be important for the meaning of the sequence element (e.g. token), dense layers don't share weights at all between different time-steps, meaning the network would have to learn the weights for the same element at different positions in the sequence independently. This doesn't exploit the prior knowledge that the same element in different positions might bring similar information, also it makes the network more prone to overfitting and increases the necessary number of parameters.

1D Convolutional layers face a different problem, while the weights are shared in different positions in the sequence their receptive fields can only be limited to a fixed number of elements at a time e.g. kernel size 3 looks at 3 tokens at a time, even if stacking multiple convolutional layers on top increases the receptive field it's still not ideal to model sequences as it struggles to model long term dependencies in the sequences. Nevertheless [[Temporal Convolutional Networks]] using Atrous convolution have been applied and obtained some success on time-series data, they also have the big advantage over RNNs to be faster to train and faster at inference due to their better parallelization.

# Introduction and unfolding through time
In recurrent neural networks, connections can either feed back to the same layer or go backward to a previous layer in the network. 
In practice though, Long Short-Term Memory and Gated Recurrent Unit, use recurrent connections that feed the hidden state back into the same layer at the next time step. Connections that go backward to earlier layers are possible but are less commonly used.

With this type of architecture we can deal with sequences of variable length, e.g. text or time-series data.

The RNN weights are shared through time, meaning the same weights are used for each time step when processing the sequence, this reduces the number of parameters, allows us to not have to fix a max sequence length, and also avoids the problem of the network having to learn to treat the same element the same independently at different time steps.

The fact that RNNs have connections back to the same layer in practice means that the network unfolds through time: at each time-step the layer receives some hidden-state vector from the previous time-step $h_{t-1}$ and the current input in the sequence $x_t$.
![[2-21-2018 1-30-41 PM.png]]

The hidden-state serves as a memory of past elements of the sequence, at each time-step the new hidden state is produced considering past hidden-state and current input $h_t=f(h_{t-1},x_t;\theta)$. An example could be $h_t = \sigma( W_h h_{t-1} + W_x x_t + b)$ with $\sigma$ some activation function, the same for $y_t$ with some other weights and activation function (for example in [[Language Modeling]], the activation is something like Softmax to obtain a probability distribution over the next token) 

Two very common patterns of RNNs are:
1. RNNs that produce an output at each time step and have recurrent connections between hidden units, e.g. in machine translation
![[Pasted image 20260313010511.png]]

2. Recurrent networks with recurrent connections between hidden units, that read an entire sequence and then produce a single output, e.g. text classification
![[Pasted image 20260313010553.png]]

For training RNNs we need to use back-propagation through time which means that the error is propagated backward through the unfolded network. This makes the time complexity significantly higher than standard backpropagation as the $O(\tau)$dependence on the length of the sequence $\tau$, this cannot be parallelized as time-steps depend on previous ones.

This problem can be solved if the connections from one time-step to the next are not hidden-to-hidden but between the output-to-hidden, as in this figure:
![[Pasted image 20260313011152.png]]

In this case, we can use [[Teacher Forcing]] and we don't have to wait for forward propagation of previous time-steps in order to do the forward propagation at time $t$ instead of using the predicted $y_{t-1}$ from the previous time-step we use the ground truth value, this allows parallelization also across the time dimension, of course limiting the network to only have output-to-hidden connections limits its representational power.

Using teacher forcing of course could lead to differences in train vs test time performances since it always has the ground truth as input during training but during inference it needs to cope with past mistakes since it works autoregressively. A possible solution to this discrepancy is to train with both ground truth teacher forcing (faster to train) and predicted outputs (slower but similar to test time conditions) allowing the network to learn to cope with auto-regression but also keeping faster training than full auto-regression, usually using ground truth teacher forcing during the initial stages of training and then slowly transitioning to more auto-regressive training. More details in the [[Teacher Forcing]] note (Teacher forcing can also be applied when we have connections between hidden units but of course without the parallelization benefit, it might still be useful for faster convergence especially at the beginning of training where past outputs tend to not be good). 

# One-to-many, many-to-one, many-to-many
When we use RNNs depending on the problem the input might be a sequence or a single element, likewise for the output.
This generates three possible cases (one-to-one is excluded since it doesn't need RNNs):
1. In one-to-many we can either use the single input $x$ as the input at every time-step, use it as the initial hidden-state, meaning $h_0=x$ or both. An example of these kind of problems is image captioning: single image $\rightarrow$ text caption of variable length
2. In many-to-one as discussed before we feed $x_t$ at the hidden-unit at time-step $t$, and we only use the output at the last time-step. An example of these kind of problems is text classification
3. In many-to-many, we get an input sequence and generate an output sequence, at each time-step the network takes $x_t$ and $h_{t-1}$ as input and generates the output $y_t$. A very strong limitation of the approach described up to now is that input and output sequence must have the same length, this is fine for problems like POS tagging, but it makes this technique not applicable to machine translation were the sequences likely have different length. An approach to solve this problem is [[#Encoder-Decoder architectures]] explained later in this note
In RNNs where the input is a sequence the initial hidden-state could be random vector or learned.


---

# Bi-directional RNNs
The RNNs we described up to now have an implicit causality, meaning they only consider past information when making predictions, this is a requirement for some tasks like language modeling, where predicting the next token can only depend on past tokens.

In some other scenarios we may want to include information from both previous and next elements in the sequence, for example in sentiment analysis of a sentence, in this case the causality doesn't matter and even hinders performance.

The bi-directionality can be achieved by creating two separate RNNs, one processing the sequence forwards (left-to-right) and the other processing it backwards (right-to-left).

Then to obtain the output sequence we concatenate the forward and backward hidden states at each time step. This combined hidden state, is then used to make the prediction using both past and future context.
![[Pasted image 20260313124244.png]]
Both the forward and backward RNN receive the same input sequence $x_1, x_2, ..., x_\tau$ but one forward and one backwards.

---
# Encoder-Decoder architectures
As discussed previously in standard RNNs we have problems in handling input and output sequences of different lengths, e.g. machine translation, we could deal with this problem by using padding and other tricks, but we have a better way.

![[Pasted image 20260313152714.png]]

In encoder-decoder architecture we divide the network in 2 parts:
#### Encoder
The encoder takes the input sequence and compresses it into a fixed-length context vector, which represents the entire input sequence. Typically we either use the last hidden-state as context or a transformed representation of the last hidden-state.
The encoder is therefore an RNN that aims to produce a fixed-length vector that summarizes the input sequence, keeping relevant information and discarding useless information.

#### Decoder
The decoder takes as input the context vector produced by the encoder (either as first hidden-state, as input at all the time-steps, or both) and generates the output sequence.

This approach works better than tricks using padding and allows to have different input and output sequence lengths.

## Encoder-decoder important details
Often [[Teacher Forcing]] is employed during training especially at the beginning, while usually the decoder work auto-regressively during inference. 
In the case of text generation (e.g. machine translation) special start and end tokens are used in the decoder.

A limitation of the encoder-decoder approach as presented is that if the sequence is long the context vector might not be able to represent all of the necessary information the decoder needs.
To solve this problem we can use an [[Attention]] mechanism, explained in the next paragraph. This mechanism eventually evolved in the [[Transformers|Transformer]] architecture.

# Attention in RNNs 
As explained in [[#Encoder-Decoder architectures|the previous paragraph]] the encoder-decoder architecture can suffer from an information bottleneck problem due to the context vector needing to capture all the relevant information of the input sequence, regardless of sequence length, degrading performance with long sequences.

[[Attention]] was developed to solve this problem, it works by using direct connections to the encoder at every step of the decoding process.

The version of Attention initially introduced in encoder-decoder RNNs is called Bahdhanau Attention and differs slightly from the Attention used in [[Transformers]], The main differences are:
* it only uses encoder-decoder cross attention, no encoder self-attention and no decoder masked self-attention
* In Bahdanau K=V=$h$ and Q=$s$, with no projection plus key and value are the same
* Additive attention score instead of scaled dot-product attention of Tranformers
* No multi-head attention
* In Bahdanau the RNN is still sequential, in transformers the attention computation is parallelized across time-steps

Bahdanau replaces single context vector with a dynamic, step-specific context vector $c_t$ recomputed at every decoder step. 

| Role in Attention | What it is in encoder-decoder RNNs                         |
| ----------------- | ---------------------------------------------------------- |
| Query $q_t$       | The decoder hidden state at the *previous* step: $s_{t-1}$ |
| Keys $k_j$        | Each encoder hidden state: $h_j$                           |
| Values $v_j$      | Each encoder hidden state: $h_j$ (Keys = Values)           |
Keys and Values are the same vectors in encoder-decoder RNNs: $h_j$. The distinction between K and V becomes meaningful in the Transformer, where separate linear projections are applied.

The compatibility between query $s_{t-1}$ and key $h_j$ is computed by a feedforward alignment network:

$$e_{tj} = v_a^\top \tanh(W_1\, s_{t-1} + W_2\, h_j)$$

Where $W_1$, $W_2$, and $v_a$ are learned parameters. This is called additive attention (or concat attention) because the query and key are combined by addition inside the tanh. It is different from the scaled dot-product attention used in Transformers (Attention can be generalized in [[Attention#Generalized attention]] to various score function, both additive and dot-product attentions are a particular case of the generalized version).

The scores are normalized with softmax to get attention weights:

$$\alpha_{tj} = \frac{\exp(e_{tj})}{\sum_{j'} \exp(e_{tj'})}$$

The context vector is then a weighted sum over all encoder hidden states:

$$c_t = \sum_j \alpha_{tj}\, h_j$$

The decoder hidden state is updated as:

$$s_t = f(s_{t-1},\, y_{t-1},\, c_t)$$

This allows the model to look back at the relevant encoder info for each target token in the decoder. 

In practice, bidirectional RNNs are used in the encoder so that each $h_j$ captures context from both directions.

# Gradient problems
In traditional RNNs as explained up to now, which compute only an hidden-state and optionally an output there are several problems regarding long-term dependencies and gradients vanishing or exploding (as in [[Exploding and vanishing gradients]]).

Since the same weights are applied at each time-step, we get that the gradients during backpropagation are repeatedly multiplied by the same matrix, depending on the magnitude of the eigenvalues (<1 or >1) the gradients can either vanish (become extremely small) causing slowing down of training or explode (become extremely large) usually an ever more catastrophic problem leading to destruction of previously learned weights.

More in depth analytical derivations can be found online.

Even in the case where the gradient is stable, this is still a problem for long term dependencies since gradients related to long term dependencies will be exponentially smaller (with exponent the distance between the two elements in the sequence) than gradients related to recent dependencies, effectively making it impossible for the network to learn long-range relationships.

One solution that was tried was to add skip connections to next time-steps, but there are better approaches like LSTM.
# LSTM
Long Short-Term Memory networks were invented to address the vanishing gradient problem of traditional RNNs. The idea is to have some gated mechanisms that allow the network to selectively remember or forget information over long sequences, skipping over the hidden-state processing, this additional info is called the cell-state $c_t$.

![[Pasted image 20260314003042.png]]

The cell-state $c_t$ acts as the model’s long-term memory, allowing information to flow across many time steps with minimal modification. Unlike the hidden state, which is recomputed through non-linear transformations at every step, the cell state is updated through gated additive operations, which helps preserve gradients during training.
At each time step, the model computes three gates: 
1. the forget gate $f_t$, which determines how much of the previous memory $c_{t-1}$ to retain
2. the input gate $i_t$, which controls how much new information enters the memory
3. the output gate $o_t$, which regulates how much of the memory is exposed as the hidden state. 
The candidate memory $\tilde{c}_t$ represents new information proposed for storage.

These vectors are computed as follows:
$f_t = \sigma(W_f x_t + U_f h_{t-1} + b_f)$, how much to remember of old cell-state
$i_t = \sigma(W_i x_t + U_i h_{t-1} + b_i)$
$\tilde{c}_t = \tanh(W_c x_t + U_c h_{t-1} + b_c)$, candidate new cell-state, will be modulated by the input gate, which decides how much of the candidate cell-state should be added to the old cell-state
$c_t = f_t \odot c_{t-1} + i_t \odot \tilde{c}_t$, meaning if $f_t=0$ the previous cell-state is erased, we can also see that if $f_t=1,i_t=0$ then the transformation is the identity which allows for gradients to flow (similar to skip-connections is ResNets)

$o_t = \sigma(W_o x_t + U_o h_{t-1} + b_o)$
$h_t = o_t \odot \tanh(c_t)$, basically the output gate decides what part of the cell-memory to expose in the short term part of the memory

The additive update $c_t = f_t \odot c_{t-1} + i_t \odot \tilde{c}_t$ creates a nearly linear path through time, enabling the network to maintain long-term dependencies while still selectively updating and exposing information through the gates.

The important idea behind LSTM is that the gates can learn when to store useful information in the cell-state based on context, this means that information is stored only when useful.

# GRU

![[0_c3WksH9kuFrQy7rz.webp]]
Gated Recurrent Unit is a RNN inspired by LSTM with the purpose of being simpler and avoiding having to maintain a separate cell-state from the hidden-state.
GRUs combine memory and hidden representation into a single hidden state $h_t$. 
The model uses two gates to control information flow: 
1. the update gate $z_t$, which determines how much of the previous hidden state should be preserved
2. the reset gate $r_t$, which controls how much past information is used when computing the candidate state.
The candidate hidden-state $\tilde{h}_t$ represents new information that could replace the previous memory. 

The equations are: 
$z_t = \sigma(W_z x_t + U_z h_{t-1} + b_z)$
$r_t = \sigma(W_r x_t + U_r h_{t-1} + b_r)$
$\tilde{h}_t = \tanh(W_h x_t + U_h (r_t \odot h_{t-1}) + b_h)$
$h_t = (1 - z_t) \odot h_{t-1} + z_t \odot \tilde{h}_t$, basically each component of the new hidden-state is a convex combination of the old hidden-state and the candidate hidden-state, with coefficients determined by the update gate.

GRU uses less parameters than LSTM and is generally simpler.

# Layer Stacking

![[v2-3a0711c1583d15a258dad8f290ff160e_1440w.png]]
Up to now we only talked about recurrent neural networks with only one recurrent layer, the input sequence is fed one input element per time-step to the recurrent layer and at each time step the hidden-state is updated and, optionally the output is computed: e.g. in encoders, or many-to-one RNNs we don't compute an output.

But nothing is stopping us to use the outputs of previous layers as inputs to a next recurrent layer, creating a stack of recurrent layers. This technique is called layer stacking, and allows the network to learn more complex and hierarchical representations of the data. This is the same as the usual stacking of convolutional or dense layers in neural networks, but it looks different because the particular computation graph unrolling of RNNs.

---

