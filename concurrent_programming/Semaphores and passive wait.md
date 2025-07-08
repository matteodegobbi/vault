#crtp 
## Active vs Passive wait
The solutions for mutual exclusion explored in [[Race conditions - Mutual exclusion]] imply some active wait strategy, similar to the polling used in I/O. In both `test_and_set` and in Peterson's the second task that tries to enter the critical section needs to keep checking if it can enter. This can be wasteful in terms of CPU usage but it has the advantage of having low latency since no context switch happens.

(Also a detail is that if two processes share only 1 processor busy wait will cause deadlock when a context switch happens inside the critical section)

We want to have a method to have a passive wait, meaning that when a process tries to enter a critical section but another process is already in it instead of busy waiting the process gets blocked. The process will be woken up by the OS when the critical section is available again.

For this we will use the OS as an intermediary for mutual exclusion.

---

## Semaphores

A semaphore is an object with:
-  a non negative integer number
- a queue of processes waiting on the semaphores
At init the semaphore starts with an integer number specified by the programmer and an empty queue.

After init the value and queue will be modified only through the functions `P(s)` and `V(s)`.

1. `P(s)` checks whether the semaphores has a number greater than 0. If the condition is true than the semaphore doesn't block and the process can continue freely. If the semaphore has a number equal to 0 the process gets blocked (goes into Wait state) and gets added to the queue of the semaphore.
2. `V(s)` if the queue of the semaphore is empty it increases the number by 1, otherwise if the queue is not empty it takes one of the blocked processes waiting in the queue and makes it ready, meaning it can now run when it gets scheduled by the OS.

To use semaphores for mutual exclusion we can just do the following:
```cpp
Semaphore s = 1;

int main(){
	P(s);
	// ... CRITICAL SECTION HERE
	V(s);
	return 0;
}

```

```cpp
// Implementation of P and V in cpp-like pseudocode
void P(s){
	if(s.val > 0){
		s.val--;
	}else{
		add_curr_process(s.queue);
		preempt_curr_proc();
	}
}
void V(s){
	if(s.queue.is_empty()){
		s.val++;
	}else{
		wake_up(q.pop());
	}
}
```
---
## Condition synchronization with semaphores

Semaphores can be used for more than mutual exclusion. For example for condition synchronization: blocking a task until an event happens in another task.
For example this is useful for the [[Producer Consumer]] problem.


(Binary semaphores unlike [[Race conditions - Mutual exclusion#Naive lock|mutexes]] can be signaled from any thread while mutexes can only be released by a thread that acquired it. This makes binary semaphores more suitable for some synchronization problems like [[Producer Consumer]], this makes a binary semaphore more powerful than a mutex)

