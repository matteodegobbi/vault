#crtp 
The **producer-consumer problem** is an example of a multi-process synchronization issue.
It involves two types of processes:
- **producers**, which generate data and add it to a shared buffer
- **consumers**, which take data from the buffer for processing.
The challenge is to make sure that producers don’t add data to a full buffer and consumers don’t remove data from an empty buffer.
This coordination requires synchronization to avoid race conditions that corrupt the data.

We can use a [[Semaphores and passive wait|semaphore]] called `empty` to block producers that are trying to access the buffer when it doesn't have empty slots (`empty==0`).
Symmetrically we can use a [[Semaphores and passive wait|semaphore]] called `full` to block consumers that are trying to access the buffer when it's empty (`full==0`).

`empty` will start with an initial value of N equal to the buffer length. Producers will call `P(empty)` before trying to write data to the buffer and consumers  will call `V(empty)` after reading some data from the buffer, this will either wake up a producer or increase the count by 1 of the `empty` semaphore.
`full` will start with an initial count of 0. The operations done by producers and consumers on this semaphore are symmetric wrt to `empty`.

Other than these two semaphores we also need a mutex to access the buffer one at a time. 