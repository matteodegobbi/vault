#rl

Many [[Value function approximation]] methods and [[Policy gradient]] methods use techniques from supervised learning that assume the dataset used to train them is iid. 
In the case of incremental algorithms used in RL this assumption is violated as subsequent samples are most of the time very correlated.

To reduce this problem we can employ batch methods: instead of doing incremental updates whenever a sample is gathered and then discarding it we can store in a replay buffer.
Then we can sample from this buffer a batch of transitions in the format $\langle S,A,R,S' \rangle$ and apply SGD on this batch.

Another added benefit is that we reuse past experience multiple times: incremental updates make SGD not sample efficient, especially if we discard the sample after the update we are only using it for a small update of the weights. 

This approach where we store transitions in a buffer and the sample a subset of them for each update is called experience replay.

A simple implementation consists in keeping a buffer of fixed size and whenever we push a new transition the buffer we remove the oldest one if the buffer is already full.

Using a buffer for experience replay is equivalent to solving a least squares problem on the batch of sampled transitions using MSE of value function:
![[Pasted image 20251213160422.png]]

![[Pasted image 20251213160549.png]]

Now, it's clear that this formulation cannot be applied directly as it involves the true value function $v_\pi$ as a label.

Instead we use a target we can sample from experience:
![[Pasted image 20251213160633.png]]

Batch approaches with policy gradient are done in a different format:
![[Pasted image 20251213160941.png]]

---

